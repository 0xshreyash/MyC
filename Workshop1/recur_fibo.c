#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long fibo(int n);

int main( int argc, char *argv[])
{
	int n = atoi(argv[1]);
	printf("%d\n", n);
	long ans = fibo(n);
	printf("%ld\n", ans);

}

long fibo(int n)
{
	if (n<=2)
	{
		return 1;
	}
	return (fibo(n-1) + fibo(n-2));
}

