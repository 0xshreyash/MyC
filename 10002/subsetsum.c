#include <stdio.h>
#include <stdlib.h>

int subsetsum(int A[], int n, int k);

int main(int argc, char *argv[])
{
	int size =40;
	int sum = 1000;
	int A[]={34, 38, 39, 43, 55, 66, 67, 84, 85, 91, 101, 117, 128, 138, 165, 168, 169, 182, 184, 186, 234, 238, 241, 276, 279, 288, 386, 387, 388, 389, 413, 444, 487, 513, 534, 535, 616, 722, 786, 78};
 	int ans = subsetsum(A, size, sum);
 	printf("%d\n", ans);
 	return 0;

}

int subsetsum(int A[], int n, int k) 
{
	if (k==0)
	{ 
		return 1;
	} 
	else if (n==0) 
	{ 
		return 0;
	}
	 else 
	{ 
		return subsetsum(A, n-1, k-A[n-1]) || subsetsum(A, n-1, k);
	}

}
