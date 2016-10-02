#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INIT_SIZE 10

int main()
{
	int *fibo, i = 0, n;
	int current_size = INIT_SIZE;
	fibo = malloc(INIT_SIZE*sizeof(int));
	fibo[0] = 0;
	fibo[1] = 1;
	printf("Enter how many fibonacci number you want:");
	scanf("%d", &n);

	for( i = 2; i < n; i++)
	{
		if(i == (current_size -10))
		{
			current_size *= 2;
			fibo = realloc(fibo, current_size*sizeof(int));
		}
		fibo[i] = fibo[i-1] + fibo[i-2];
	}

	for( i = 0; i < n; i++)
	{
		printf("%d\n", fibo[i]);
	}

	return 0;

}