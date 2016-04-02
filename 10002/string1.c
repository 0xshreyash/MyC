/* Show string manipulation, example 1.
*/
#include <stdio.h>

int
main(int argc, char *argv[]) {
	char *p = "Cheshire:-)";
	while (*p) {
		printf("p = %12p, string at p = %s\n", p, p);
		p = p+1;
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
