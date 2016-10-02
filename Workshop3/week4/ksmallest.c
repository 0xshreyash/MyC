#include "ksmallest.h"
#include <stdlib.h>
#include <stdio.h>


int ksmallest(int *A, int n, int k)
{
	int i;
	for(i =0; i<n; i++)
	{
		printf("%d\n", A[i]);
	}

	int pivot = A[(rand()%n)];
	printf("Value of Pivot:%d\n", pivot);
	int next = 0, fe =0, fg = n;
	int temp;

	
	while(next < fg)
	{
		if(A[next] < pivot)
		{
			temp = A[next];
			A[next] = A[fe];
			A[fe] = temp;
			fe = fe + 1;
			next = next + 1;
			
		}
		else if(A[next] > pivot)
		{
			fg = fg - 1;
			temp = A[fg];
			A[fg] = A[next];
			A[next] = temp;
		}
		else
		{
			next++;
		}
	}
	for(i =0; i<n; i++)
	{
		printf("%d\n", A[i]);
	}

	printf("fe = %d, fg = %d, A[fe] = %d, A[fg] = %d\n", fe, fg, A[fe], A[fg]);
	printf("Now k = %d\n", k);


	if(fe >= k)
	{
		return ksmallest(A, fe, k);
	}
	else if( k <= fg)
	{
		return pivot;

	}
	else if( k >
	 fg)
	{
		return ksmallest(A + fg, n - fg, k - fg);
	}

}