/* Quicksort on an integer array.
*/
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define SIZE 100000

typedef int data_t;

/* This needs to be included rather than compiled, because the use
   of data_t as the array that is being sorted. */
#include "sortscaffold.c"

/* Amongst other things, sortscaffold.c defines these two :
	int cmp(data_t *p1, data_t *p2);
	void swap_data(data_t *p1, data_t *p2);
*/

/* And these are the functions specific to quicksort. */
void partition(data_t A[], int n, data_t *pivot, int *fe, int *fg);
void quick_sort(data_t A[], int n);
data_t choose_pivot(data_t A[], int n);

void
quick_sort(data_t A[], int n) {
	data_t pivot;
	int first_eq, first_gt;
	if (n<=1) {
		return;
	}
	/* array section is non-trivial */
	pivot = choose_pivot(A, n);
	partition(A, n, &pivot, &first_eq, &first_gt);
	quick_sort(A, first_eq);
	quick_sort(A+first_gt, n-first_gt);
}

void
partition(data_t A[], int n, data_t *pivot,
		int *first_eq, int *first_gt) {
	int next=0, fe=0, fg=n, outcome;
	while (next<fg) {
		if ((outcome = cmp(A+next, pivot)) < 0) 
		{
			swap_data(A+fe, A+next);
			fe += 1;
			next += 1;
		} else if (outcome > 0) {
			fg -= 1;
			swap_data(A+next, A+fg);
		} else {
			next += 1;
		}
	}
	assert(0<=fe && fe<fg && fg<=n);
	*first_eq = fe;
	*first_gt = fg;
	return;
}

data_t
choose_pivot(data_t A[], int n) {
	return A[rand()%n];
}


int
main(int argc, char *argv[]) {
	int n=SIZE;
	if (argc>1) {
		n = atoi(argv[1]);
	}
	printf("Testing quick sort\n");
	do_sort_tests(quick_sort, n);
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
