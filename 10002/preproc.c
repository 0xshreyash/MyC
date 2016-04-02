/* Show some facilities of the preprocessor.
*/
#include <stdio.h>

#define DEBUG

#define MUDDLE(x,y)  (((x)<<(y))|((y)&((y)-1)))

#ifdef DEBUG
#define DEBUG_INT(x) printf("line %3d: %s=%d\n", \
		__LINE__, #x, x)
#else
#define DEBUG_INT(x)
#endif

int
main(int argc, char *argv[]) {
	int i=2, j=3;
	i = MUDDLE(i,j);
	DEBUG_INT(i);
	j = MUDDLE(j,i);
	DEBUG_INT(j);
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
