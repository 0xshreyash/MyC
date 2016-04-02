/* Create a KWIC index for an input string.
   Uses qsort to order a set of pointersinto the string to
   make a suffix array, and then prints out in suffix array order.

   Not terribly challenging intellectually, but fiddly to get the
   details right. Hardest thing is to arrange for pointers to point
   only at the start of words.

   Alistair Moffat, October 2012.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>


	/* Maximum string that can be processed */
#define MAXBYTES 1000000
	/* Size of window to be presented */
#define WINDOW 25
	/* index marker */
#define MARKER '*'


/* function to compare two strings when presented with pointers
   to pointers to them */

int
strptrcmp(const void *p1, const void *p2) {
	char *s1, *s2;
	s1 = *(char **)(p1);
	s2 = *(char **)(p2);
	return strcasecmp(s1, s2);
}


/* where it all happens */

int
main(int argc, char **argv) {
	/* the string */
	char C[MAXBYTES+1];
	/* the suffix array */
	char *S[MAXBYTES+1];
	int nbytes, nptrs=0, i;
	char *p;

	/* get the input string */
	nbytes = fread(C, sizeof(*C), MAXBYTES, stdin);
	C[nbytes] = '\0';
	fprintf(stderr, "# %d bytes read\n", nbytes);

	for (i=0; i<nbytes; i++) {
		/* replace any newlines, tabs, etc by blanks,
		   to keep the output tidy
		*/
		if (isspace(C[i])) {
			C[i] = ' ';
		}
		/* pick out and index the places where alphabetic follows
		   non-alpha */
		if (isalpha(C[i]) && (i==0 || !isalpha(C[i-1]))) {
			S[nptrs++] = C+i;
		}
	}

	/* sort those critical locations */
	qsort(S, nptrs, sizeof(*S), strptrcmp);

	/* now print out the KWIC index, by stepping through the array
	   and extracting a window around each location */
	for (i=0; i<nptrs; i++) {
		p = S[i] - WINDOW;
		while (p<C) {
			/* can't print if to left of start of string */
			putchar(' ');
			p++;
		}
		while (p<S[i]) {
			/* but can print characters that are there */
			putchar(*p);
			p++;
		}
		putchar(MARKER);
		while (p<S[i]+WINDOW && p<C+nbytes) {
			/* and print to the right too, if characters
			   exist */
			putchar(*p);
			p++;
		}
		putchar('\n');
	}

	/* and yes, you are right, this main loop is too long, it 
	   should have been broken into some functions.
	   You can do that now :-)
	*/

	return 0;
}
