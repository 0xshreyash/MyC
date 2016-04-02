/* Show the use of the library qsort function.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
string_ascending(const void *v1, const void *v2) {
	return strcmp(*(char**)v1,*(char**)v2);
}

int
main(int argc, char *argv[]) {
	int i;
	char *S[] = {"koala", "kangaroo", "quoll", "quokka",
		"wombat", "goanna", "wallaby", "bilby"};
	qsort(S, sizeof(S)/sizeof(*S), sizeof(*S), 
			string_ascending);
	for (i=0; i<sizeof(S)/sizeof(*S); i++) {
		printf("%s\n", S[i]);
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
