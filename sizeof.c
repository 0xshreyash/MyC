/* Show the use of sizeof.
*/
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[]) {
	double A[10]; char *p="mary mary quite contrary";
	printf("sizeof(char)   = %2lu\n", sizeof(char));
	printf("sizeof(int)    = %2lu\n", sizeof(int));
	printf("sizeof(float)  = %2lu\n", sizeof(float));
	printf("sizeof(double) = %2lu\n", sizeof(double));
	printf("sizeof(A)      = %2lu\n", sizeof(A));
	printf("sizeof(*A)     = %2lu\n", sizeof(*A));
	printf("sizeof(p)      = %2lu\n", sizeof(p));
	printf("sizeof(*p)     = %2lu\n", sizeof(*p));
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
