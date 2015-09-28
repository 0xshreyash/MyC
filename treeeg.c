/* Use a binary search tree to count words, and print
   a sorted list of words and their frequencies.
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "treeops.h"
#include "getword.h"

typedef struct {
	char *word;      /* pointer to a word */
	int  freq;       /* frequency of that word */
} data_t;

int
compare_string_parts(void *x1, void *x2) {
	data_t *p1=x1, *p2=x2;
	return strcmp(p1->word, p2->word);
}

void
print_then_free(void *x) {
	data_t *p=x;
	printf("%4d  %s\n", p->freq, p->word);
	free(p->word);
	free(p);
}

int
main(int argc, char *argv[]) {
	data_t *new, *locn;
	tree_t *tree;
	word_t oneword;
	tree = make_empty_tree(compare_string_parts);/* We want the tree ordered in
	a certain way */
	while (getword(oneword, MAXCHARS) != EOF) {
		new = malloc(sizeof(*new));
		assert(new!=NULL);
		new->word = oneword;
		new->freq = 1;
		locn = search_tree(tree, new);
		if (!locn) {
			/* not in tree, so create a new string */
			new->word = malloc(1+strlen(oneword));
			assert(new->word!=NULL);
			strcpy(new->word, oneword);
			/* and insert into tree */
			tree = insert_in_order(tree, new);
		} else {
			/* already in tree, so increment count */
			locn->freq += 1;
			/* and release the temporary node */
			free(new);
		}
	}
	/* now print all the words, freeing on the way */
	traverse_tree(tree, print_then_free);
	/* and release the tree itself */
	free_tree(tree);
	tree = NULL;
	/* ta daaa! */
	return 0;
}



