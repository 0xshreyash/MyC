/* Show the use of malloc and free.
*/
#include <stdio.h>
#include <stdlib.h>

#include <stdlib.h>
#define PTRS 5

int
main(int argc, char *argv[]) {

	char *p[PTRS];
	size_t nbytes=10;
	int i;
	/* try to allocate an array of pointers */
	for (i=0; i<PTRS; i++) {
		printf("malloc of %10lu bytes ", nbytes);
		if ((p[i] = (char *)malloc(nbytes)) == NULL) {
			printf("failed\n");
		} else {
			printf("succeeded\n");
		}
		nbytes *= 100;
	}
	/* now free all the memory that did get allocated */
	for (i=0; i<PTRS; i++) {
		if (p[i]) {
			free(p[i]);
			p[i] = NULL;
		}
	}
	return 0;
}

/* =====================================================================
   Program written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ================================================================== */
