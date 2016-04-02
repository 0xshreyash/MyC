/* Compute the KMP failure function for a pattern from the
 * command line */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX 100

int
main(int argc, char **argv) {
	int F[MAX], n;
	char *str;
	int pos=2, cnd=0;

	str = argv[1];
	if (!str) {
		printf("Usage: %s string\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	n = strlen(str);

	F[0] = -1;
	F[1] = 0;
	while (pos < n) {
		if (str[pos-1] == str[cnd]) {
			cnd += 1;
			F[pos] = cnd;
			pos += 1;
		} else if (cnd > 0) {
			cnd = F[cnd];
		} else {
			F[pos] = 0;
			pos += 1;
		}

	}

	for (pos=0; pos<n; pos++) {
		printf("  %c", str[pos]);
	}
	printf("\n");
	for (pos=0; pos<n; pos++) {
		printf("%3d", F[pos]);
	}
	printf("\n");
	return 0;
}
