/* Break the input up into a sequence of words, and only report
   the unique ones. Uses malloc and realloc to help cope with very
   large input files.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAXCHARS 1000    /* max chars per word */
#define INITIAL   100    /* initial size of word array */

typedef char word_t[MAXCHARS+1];
int getword(word_t W, int limit);
void exit_if_null(void *ptr, char *msg);

int
main(int argc, char *argv[]) {
	word_t one_word;
	char **all_words;
	size_t current_size=INITIAL;
	int numdistinct=0, totwords=0, i, found;
	all_words = (char**)malloc(INITIAL*sizeof(*all_words));
	exit_if_null(all_words, "initial allocation");
	while (getword(one_word, MAXCHARS) != EOF) {
		totwords = totwords+1;
		/* linear search in array of previous words... */
		found = 0;
		for (i=0; i<numdistinct && !found; i++) {
			found = (strcmp(one_word, all_words[i]) == 0);
		}
		if (!found) {
			/* a new word exists, but is there space? */
			if (numdistinct == current_size) {
				current_size *= 2;
				all_words = realloc(all_words, 
					current_size*sizeof(*all_words));
				exit_if_null(all_words, "reallocation");
			}
			/* ok, there is definitely space in array */
			all_words[numdistinct] =
				(char*)malloc(1+strlen(one_word));
			exit_if_null(all_words[numdistinct],
				"string malloc");
			/* and there is also a space for the new word */
			strcpy(all_words[numdistinct], one_word);
			numdistinct += 1;
		}
	}
	printf("%d words read\n", totwords);
	for (i=0; i<numdistinct; i++) {
		printf("word #%d is \"%s\"\n", i, all_words[i]);
		free(all_words[i]);
		all_words[i] = NULL;
	}
	free(all_words);
	all_words = NULL;
	return 0;
}

void
exit_if_null(void *ptr, char *msg) {
	if (!ptr) {
		printf("unexpected null pointer: %s\n", msg);
		exit(EXIT_FAILURE);
	}
}

#include "getword.c"

/* =====================================================================
   Program written by Alistair Moffat, as an example for the book
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ================================================================== */
