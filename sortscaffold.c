/* Support routines for testing sorting functions.
*/

/* All standard #include lines are in the other files that
   include this one. Done this way to allow easy switching between
   sort modules, but wouldn't normally be like this */

#define NRUNS 20

int comps, copys;

int
cmp(data_t *x1, data_t *x2) {
	comps += 1;
	return *x1-*x2;
}

void
copy_data(data_t *to, data_t *fr) {
	*to = *fr;
	copys += 1;
}

void
swap_data(data_t *x1, data_t *x2) {
	data_t t;
	copy_data(&t, x1);
	copy_data(x1, x2);
	copy_data(x2, &t);
}

void
fill_sorted(data_t A[], int n) {
	int i;
	for (i=0; i<n; i++) {
		A[i] = i;
	}
}

void
fill_reverse(data_t A[], int n) {
	int i;
	for (i=0; i<n; i++) {
		A[i] = n-i;
	}
}

void
fill_same(data_t A[], int n) {
	int i;
	for (i=0; i<n; i++) {
		A[i] = 1;
	}
}

void
fill_random(data_t A[], int n) {
	int i;
	for (i=0; i<n; i++) {
		A[i] = i;
	}
	for (i=n-1; i>0; i--) {
		swap_data(A+i, A+rand()%i);
	}
}

void
print_array(data_t A[], int n) {
	int i;
	if (n>17) {
		return;
	}
	for (i=0; i<n; i++) {
		printf("%4d", A[i]);
	}
	printf("\n");
}

void
do_sort_tests(void sortalg(data_t[],int), int n) {
	data_t *A;
	/* yes, this next one is an array of function pointers! */
	void ((*fill[])(data_t[], int)) = 
		{fill_sorted, fill_reverse, fill_same, fill_random};
	char *data[] = {"sorted", "reverse", "uniform", "random"};
	int i, j, nfuncs=4, nruns=NRUNS;
	A = (data_t *)malloc(n*sizeof(*A));
	assert(A!=NULL);
	srand(n);
	for (i=0; i<nfuncs; i++) {
		copys = comps = 0;
		for (j=0; j<nruns; j++) {
			(fill[i])(A, n);
			print_array(A, n);
			sortalg(A, n);
			print_array(A, n);
		}
		printf("%d runs, %d %s items\n", nruns, n, data[i]);
		printf("\tcomparisons = %4.1f per item, ",
				(double)comps/n/nruns);
		printf("copys = %4.1f per item\n",
				(double)copys/n/nruns);
	}
	free(A);
	A = NULL;
	return;
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
