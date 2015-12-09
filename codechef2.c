#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <strings.h>

int find_gcd(int a, int b);

int main(int argc, char* argv[])
{
	int N, k, array[500000], run=0, max=0, gcd=1, current_gcd=1;
	printf("Input\n");
	scanf("%d %d", N, K);
	
	if(N <= 0 && N > 500000)
	{
		printf("Incorrect Input");
		exit(EXIT_FAILURE);
	}
	for(i=0; i<N;i++)
	{
		scanf("%d ",array[i]);

	}
	for(i=0;i<N-1;i++)
	{
		if((gcd=find_gcd(array[i], array[i+1]))>K && run==0)
		{
			current_gcd = gcd;
			run++;
		}
		else if(gcd>K && gcd=current_gcd && run != 0)
		{
			run++;

		}
		else if((gcd>K && gcd!=current_gcd && run != 0))
		{
			if(run>max)
			{
				max = run;

			}
			run =0;
			current_gcd = 1;
		}
	}
	printf("Output\n");
	printf("%d", gcd);

	return 0;	
}

int find_gcd(int a, int b)
{
	int i = 0;
	gcd = 1;
	for(i=0;i<a; i++)
	{
		if( a%i==0 && b%i==0)
		{
			gcd = i;
		}
	}
	return gcd;
}