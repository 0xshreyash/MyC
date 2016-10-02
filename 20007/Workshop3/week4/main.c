/*
** COMP20007 Design of Algorithms
** Semester 1 2016
** Week 4 Workshop
**
** Steven Bird (sbird@unimelb.edu.au)
** Thu 17 Mar 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ksmallest.h"

#define MAX_NUMBER_STRING_LEN 64  /* maximum length in chars of number */

/*
** Print usage message
*/
void
usage(char *exeName) { 
  fprintf(stderr,"Usage: %s k < filename\n", exeName);
  fprintf(stderr,"  k: rank of item to find\n");
  fprintf(stderr,"  filename: a text file of numbers, one per line\n");
}

/*
** Read input, call ksmallest, print time
*/
int 
main(int argc, char *argv[]) {

    if (argc != 2) {
        usage(argv[0]);
        return(-1);
    }

    int k;
    sscanf(argv[1], "%d", &k);

    /*
    ** Read in the numbers, and keep increasing the array size
    ** if necessary (from Andrew Turpin)
    */
    int maxArraySize = 64;  /* any number > 0 */
    int n  = 0;
    int *A = (int *)malloc(sizeof(int) * maxArraySize);
    if (A == NULL) {
        fprintf(stderr, "Out of memory for A\n");
        return -1;
    }
    char buff[MAX_NUMBER_STRING_LEN];
    while (fgets(buff, MAX_NUMBER_STRING_LEN, stdin) != NULL) {
        if (n >= maxArraySize) {
            maxArraySize *= 2;  /* double the size of the array */
            A = (int *)realloc(A, sizeof(int) * maxArraySize);
            if (A == NULL) {
                fprintf(stderr, "Out of memory for A\n");
                return -1;
            }
        }
        sscanf(buff, "%d", &A[n]);
        n++;
    }
    
    printf("Read %d numbers\n",n);

    clock_t startTime = clock();
    int m = ksmallest(A, n, k);
    clock_t endTime = clock();
    printf("Time taken to find %d smallest element (%20d) on %10d elements = %ldms\n", k, m, n, (endTime-startTime+500)/1000);
    
    return 0;
}
