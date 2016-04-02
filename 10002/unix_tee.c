/* Exercise 11.3: The Unix tee program, that replicates stdin into a
   set of files specified on the commandline.
   Alistair Moffat, November 2013.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_FILES 10

int
main(int argc, char *argv[]) {
	int c, i;
	FILE *fp[MAX_FILES];

	if (argc>MAX_FILES) {
		fprintf(stderr, "Too many files, limit is %d\n", MAX_FILES);
		exit(EXIT_FAILURE);
	}

	/* open the files */
	for (i=1; i<argc; i++) {
		fp[i] = fopen(argv[i], "w");
		if (fp[i]==NULL) {
			fprintf(stderr, "Unable to open %s\n", argv[i]);
		}
	}

	/* now read characters, and replicate each one to each file
	   that got opened */
	while ((c=getchar()) != EOF) {
		for (i=1; i<argc; i++) {
			if (fp[i]) {
				putc(c, fp[i]);
			}
		}
		putc(c, stdout);
	}

	/* then close the files */
	for (i=1; i<argc; i++) {
		if (fp[i]) {
			fclose(fp[i]);
			fp[i] = NULL;
		}
	}

	return 0;
}
