#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef double number;

number
f(number x) {
	return  x * (sqrt(x+1) - sqrt(x));  /* It pretty much takes the difference to be zero */
}

number
g(number x) {
	return x / (sqrt(x+1) + sqrt(x));
}

int
main(int argc, char **argv) {
	number x, fx, gx;
	printf("Using %d-byte floating point\n", (int)sizeof(number));
	for (x=1; x<=1e30; x*=10) {
		fx = f(x);
		gx = g(x);
		printf("x = %.3e, f(x) = %.10e, g(x) = %.10e\n",
			(double)x, (double)fx, (double)gx);
	}
	return 0;
}