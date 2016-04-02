/* Exercise 8 in lec06, Foundations of Algorithms (COMP10002)

   An inverted index for a text is an alphabetical listing of all of
   the words that appear, together with the line numbers(s) at which
   they appear: Write a program that generates an inverted index for
   the text that is provided as input.
   Words should be case-folded.
   You may assume that at most 10,000 words will be input.

   The code is adapted from realloc.c and getword.c, a word
   frequency counting program.

   Jianzhong Qi, October 2012,
   further modified by
   Alistair Moffat, October 2012
*/ 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

	/* max chars per word */
#define MAXCHARS 1000	
	/* initial size of word array and line number array */
#define INITIAL 10		
	/* maximum number of words */
#define MAXWORDS 10000	

typedef char word_t[MAXCHARS+1];

typedef struct {
	word_t word;			/* the word */
	int* line_nums;			/* array of line numbers */ 
	int line_count;			/* line number count */
	size_t line_array_size;		/* line number array size */
} word_index_t;

typedef struct {
	word_index_t** word_idx;	/* the different words in the index*/
	int num_distinct;		/* number of the different words */
	size_t current_size;		/* the size of the word_idx array */
} inverted_index_t;

/* function prototypes */
int word_index_cmp(const void*, const void*);
int get_word(word_t, int, int*);

inverted_index_t create_index(void);
void output_index(inverted_index_t);
void free_index(inverted_index_t);

int
main(int argc, char **argv) {
	inverted_index_t index;
	/* make raw index from stdin */
	index = create_index();
	/* sort into word order */
	qsort(index.word_idx, index.num_distinct,
		sizeof(*(index.word_idx)), word_index_cmp); 
	/* output it */
	output_index(index);
	/* and release it */
	free_index(index);
	return 0;
}
	
/* Create an inverted index */
inverted_index_t 
create_index() {
	inverted_index_t index;
	
	word_t one_word;
	int i, found;
	int line_num;
	word_index_t *w;

	/* initialise the inverted index array */
	index.current_size = INITIAL;
	index.num_distinct = 0;
	index.word_idx = malloc(INITIAL * sizeof(word_index_t*));
	assert(index.word_idx);
	
	while (get_word(one_word, MAXCHARS, &line_num) != EOF) {
		/* linear search in array of previous words... */
		found = 0;
		for (i = 0; i < index.num_distinct && !found; i++) {
			found = (strcmp(one_word, index.word_idx[i]->word) == 0);
		}
		if (!found) {
			/* a new word exists, but is there space? */
			if (index.num_distinct == index.current_size) {
				index.current_size *= 2;
				index.word_idx = realloc(index.word_idx, 
					index.current_size * sizeof(char*));
				assert(index.word_idx);
			}
			/* ok, there is definitely space in array */
			index.word_idx[index.num_distinct] =
				malloc(sizeof(word_index_t));
			assert(index.word_idx[index.num_distinct]);
			/* insert the new word, and its first line number */
			w = index.word_idx[index.num_distinct];
			/* use w as pointer to the site of all the action */
			strcpy(w->word, one_word);
			w->line_count = 1;
			w->line_array_size = INITIAL;
			w->line_nums = 
				malloc(w->line_array_size * sizeof(int));
			w->line_nums[0] = line_num;
			
			index.num_distinct += 1;
		} else {
			/* i is pointing one past the found location */
			w = index.word_idx[i-1];
			/* and w is pointing at where the action will happen */
			/* do we need the new line number? */
			if (w->line_nums[w->line_count-1] == line_num) {
				/* already got it, no need to store again  */
			} else {
				/* is there space for the new line number? */
				if (w->line_count == w->line_array_size) {
					/* line number array is full, 
					   so reallocate */
					w->line_array_size *= 2;
					w->line_nums = realloc(w->line_nums,
						w->line_array_size *
							sizeof(int));				
				} 
				/* line number array now has space available, 
				   attach the new line number to the end */
				w->line_nums[w->line_count] = line_num;
				w->line_count++;
			}
		}
	}
	
	
	return index;
}

/* Output the indexed words and the line numbers, 
   and release the allocated memory. 
*/	
void 
output_index(inverted_index_t index) {
	int i, j;
	
	for (i = 0; i < index.num_distinct; i++) {
		printf("%s\t: %d", index.word_idx[i]->word, 
			index.word_idx[i]->line_nums[0]);
		for (j = 1; j < index.word_idx[i]->line_count; j++) {
			printf(", %d", index.word_idx[i]->line_nums[j]);	
		}
		printf("\n");
	}
}

/* Release all allocated memory.
*/	
void 
free_index(inverted_index_t index) {
	int i;
	for (i = 0; i < index.num_distinct; i++) {
		free(index.word_idx[i]->line_nums);
		index.word_idx[i]->line_nums = NULL;
		free(index.word_idx[i]);
		index.word_idx[i] = NULL;
	}
	free(index.word_idx);
	index.word_idx = NULL;
}

/* Function to compare two word indices when presented with pointers
   to pointers to them */
int
word_index_cmp(const void *p1, const void *p2) {
	word_index_t *w1, *w2;
	w1 = *(word_index_t **)(p1);
	w2 = *(word_index_t **)(p2);
	return strcmp(w1->word, w2->word);
}

/* Extract a single word out of the standard input, but not
   more than limit characters. Argument array W must be
   limit+1 characters or bigger. 
*/
int
get_word(char *W, int limit, int* line_num) {
	/* this static variable holds its value between calls */
	static int line=1;
	int c;
	/* first, skip over any non alphabetics */
	while ((c = getchar()) != EOF && !isalpha(c)) {
		/* if a '\n' is seen, increase the line number */
		line += (c=='\n');
	}
	if (c == EOF) {
		return EOF;
	}
	/* ok, first character of next word has been found */
	*W = tolower(c);
	W += 1;
	limit -= 1;
	while (limit > 0 && (c = getchar()) != EOF && isalpha(c)) {
		/* another character to be stored */
		*W = tolower(c);
		W += 1;
		limit -= 1;
	}
	/* now close off the string */
	*W = '\0';
	/* store the line number it appears on */
	*line_num = line;
	/* and that last char might have been another '\n', of course */
	line += (c=='\n');
	return 0;
}
