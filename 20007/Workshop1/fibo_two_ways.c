#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

long fibo1(int n);
long fibo2(int n);

int main( int argc, char *argv[])
{
	clock_t begin, end;
	double time_spent;

	begin = clock();

	long ans; 
	int n = atoi(argv[2]);
	long (*F[2])(int);
	F[0] = fibo1;
	F[1] = fibo2;
	int m = atoi(argv[1]);

	if(m == 1)
	{

		ans = F[0](n);	
	} 
	else if(m == 2)
	{
		ans = F[1](n);
	}
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

