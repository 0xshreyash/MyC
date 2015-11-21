#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef float number;

number
h1(int n) {
	int i;
	number sum=0.0;
	for (i=1; i<=n; i++) {
		sum += 1.0/i;
	}
	return sum;
}

number
h2(int n) {
	int i;
	number sum=0.0;
	for (i=n; i>=1; i--) {
		sum += 1.0/i;
	}
	return sum;
}

int
main(int argc, char **argv) {
	int n;
	printf("Using %d-byte floating point\n", (int)sizeof(number));
	for (n=1; n<=1000000000; n*=2) {
		printf("n=%11d, h1 = %18.15f, h2 = %18.15f\n",
				n, (double)h1(n), (double)h2(n));
	}
	return 0;
}