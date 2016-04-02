/* Show the use of masking operations.
   to extract the bit pattern of a float variable.
*/
#include <stdio.h>
#include <stdlib.h>
int
main(int argc, char **argv) {
	int i;
	float fval;
	unsigned uval;
	if (argc<2) {
		exit(EXIT_FAILURE);
	}
	fval = atof(argv[1]);
	uval = *((unsigned *)(&fval));

	printf("\t");
	for (i=8*sizeof(unsigned)-1; i>=0; i--) {
		if (uval & (1<<i)) {
			printf("1");
		} else {
			printf("0");
		}
		if (i%8==0) {
			printf(" ");
		}
	}
	printf("\n");
	return EXIT_SUCCESS;
}