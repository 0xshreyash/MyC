/* Show the use of function arguments.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Just the name of the function is a pointer to the function */

int is_sorted(void *A, size_t nelem, size_t size, 
			int (*cmp)(void*,void*));

int
double_ascending(void *v1, void *v2) {
	double *d1=v1, *d2=v2; /* Cast is taking place */
	if (*d1<*d2) return -1;
	if (*d1>*d2) return +1;
	return 0;
}

int
double_descending(void *v1, void *v2) {
	double *d1=v1, *d2=v2;
	return *d2 - *d1;
}

int
string_ascending(void *v1, void *v2) {
	char **s1=v1, **s2=v2;  /* Pointer to a pointer, ask sir about this.  */
	return strcmp(*s1,*s2);
}

int
string_descending(void *v1, void *v2) {
	char **s1=v1, **s2=v2;
	return -strcmp(*s1,*s2);
}

int
main(int argc, char *argv[]) {
	double X[] = {1.87, 3.43, 7.64, 7.68, 8.16, 9.86};
	char *S[] = {"wombat", "wallaby", "quoll", "quokka",
		"koala", "kangaroo", "goanna", "bilby"}; /* Array of pointers to
		characters and thus array of strings, S points to the first character
		of of the first string */
	if (is_sorted(X, sizeof(X)/sizeof(*X)/*No. of elements*/, sizeof(*X)
		/* Size of each pointer to the element */,double_ascending)) {
		printf("Array X is ascending\n");
	}
	if (is_sorted(S, sizeof(S)/sizeof(*S), sizeof(*S),
			string_descending)) {
		printf("Array S is descending\n");
	}
	return 0;
}

int
is_sorted(void *A/*Array to be tested*/, size_t nelem, size_t size
	/*Size of each element */,int (*cmp)(void*,void*)/* Function that compares
	this shit*/) {         /* Point to a unction ^ */ 
	char *Ap=(char *)/* Converting A to a character pointer */A;
	while (nelem>1) {
		if (cmp(Ap, Ap+size) > 0) {
			/* these two are out of order */
			return 0;
		}
		Ap += size; /* Incrementing to check for each pair of elements */
		nelem -= 1;
	}
	/* all elements have been checked, and are ok */
	return 1;
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
