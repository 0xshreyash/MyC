#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

long fibo1(int n); // Implements fibonacci series recursively
long fibo2(int n); // Implements fibonacci series iteratively

/* Program takes input through the command line -> First argument is: 1 for recursion, 2 for iteration Second argument is: the number of the fibonacci term that you want */

int main( int argc, char *argv[])
{
	clock_t begin, end;
	double time_spent;  // clock just measures the running time of the program

	begin = clock();

	long ans;  // Our ans to the nth fibonacci number 
	int n = atoi(argv[2]); // nth fibonacci number needed, atoi converts the strings from command line to numbers
	long (*F[2])(int);  //array of function pointers, keep in mind the brackets. 
	F[0] = fibo1;   
	F[1] = fibo2;
	int m = atoi(argv[1]);  /// the function the user wants us to use.
	
	ans = F[m-1](n);	
	printf("%ld\n", ans);


	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%lf\n", time_spent);

	return 0;
}

long fibo1(int n)
{
	if (n<=2)
	{
		return 1;
	}
	return (fibo1(n-1) + fibo1(n-2));
}

long fibo2(int n)
{
	int i; 
	int fibo[3];
	fibo[1] = fibo[0] = 1;
	int temp; 
	for( i = 2; i < n; i++)
	{
		fibo[i%3] = fibo[(i-1)%3] + fibo[(i-2)%3];

	}

	return fibo[(i-1)%3];
}

