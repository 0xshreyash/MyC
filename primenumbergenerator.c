#include <stdio.h>
#include <stdlib.h>


int nextprime(int n);
int isprime(int n);

int main()
{
	int n, start = 2;
	while(start < 1000000)
	{
		n = nextprime(start);
		if(n<1000000)
		{
			printf("%d\n", n);
		}
		start = n +1;
	}	
	return 0;
}

int nextprime(int n)
{
	if(n==2)
	{
		return n;
	}
	while(!isprime(n))
	{
		 n++;
	}
	return n;
}

int isprime(int n)
{
	int divisor =3;
	if(n<=1)
	{
		return 0;
	}
	for(divisor = 2; divisor*divisor <= n; divisor++)
	{
		if(n%divisor == 0)
		{
			return 0;
		}

	}
	return 1;
}

