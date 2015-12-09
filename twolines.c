/* Print the first few lines of a set of files.
*/
#include <stdio.h>
#include <stdlib.h>

#define LINE_LIMIT 2
#define SEPARATOR "======================================="

void first_lines(FILE *fp, int n);

int
main(int argc, char *argv[]) {
	int fnum;
	FILE *fp;
	/* process the list of command line arguments */
	for (fnum=1; fnum<argc; fnum++) {
		fprintf(stderr, "Opening %s: ", argv[fnum]);
		if ((fp = fopen(argv[fnum], "r")) == NULL) {
			fprintf(stderr, "............failed\n");
		} else {
			fprintf(stderr, "\n");
			printf("%s %s\n", SEPARATOR, argv[fnum]);
			first_lines(fp, LINE_LIMIT);
			fclose(fp);
		}
	}
	return 0;
}

/* Copy the first few lines of the file fp to stdout.
   Follow them with a count of the lines in the file.
*/
void
first_lines(FILE *fp, int n) {
	int c;
	int lines=0;
	while ((c = getc(fp)) != EOF) {
		if (lines < n) {
			putchar(c);
		}
		lines += (c=='\n');
	}
	printf("[%d lines in total]\n", lines);
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
