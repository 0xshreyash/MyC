#include <stdio.h>
#include <stdlib.h>


typedef struct answers
{
	int parts[4];
}answers_t;

int subsetsum(int A[], int n, int k, answers_t ans[], int i);


int main(int argc, char *argv[])
{
	int size = 4;
	int sum = 80;
	answers_t *ans; 
	int i=0;
	int A[]={40, 30, 50, 40};
 	int val = subsetsum(A, size, sum, ans, i);
 	printf("%d\n", val);
 	return 0;

}

int subsetsum(int A[], int n, int k, answers_t ans[], int i) 
{
	static int a=0;
	if (k==0)
	{ 
		for(int j=0; j<i;j++)
		{
			if(ans[a].parts[j] != 0)
			{
				printf("%d ",ans[a].parts[j]);
			}
		}
		printf("\n");
		a++;

	} 
	else if(n==0) 
	{ 
		return 0;
	}
	 else 
	{
		ans[a].parts[i] = A[n-1];
		return subsetsum(A, n-1, k-A[n-1], ans, i+1)||subsetsum(A, n-1, k, ans, i);

	}

}
