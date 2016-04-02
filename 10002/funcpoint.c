/* Show the declaration and use of function pointers.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double plus1(double x);

double 
plus1(double x){
	return x+1.0;
}

int
main(int argc, char *argv[]) {
	double (*F)(double), x=2.0;  /* Pointer to a function */
	/* double (*F)(double) where double is the return type and *F is the
	   pointer to a function F and double is the argument type */
	/* The function is not yet pointing to anything */
	F = sqrt; /*Pointer to the function sqrt */
	printf("x=%.4f, F(x)=%.4f\n", x, F(x)); /* In an array when you dereference
	toy get an element of the array and when you dereference a function you
	call the function */
	F = sin;
	printf("x=%.4f, F(x)=%.4f\n", x, F(x));
	F = log;
	printf("x=%.4f, F(x)=%.4f\n", x, F(x));
	printf("x=%.4f, (*F)(x)=%.4f\n", x, (*F)(x));
	F = plus1;
	printf("x=%.4f, F(x)=%.4f\n", x, F(x));
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
