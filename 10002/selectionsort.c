#include<stdio.h>
#include<stdlib.h>
#define N 100
void selection(int A[],int i);
int
main(int argc,char *argv[])
{
	int A[N],n=0,next=0,excess=0,i;
	int *p;
	printf("Enter upto %d values and enter ^D for termination",N);
	while(scanf("%d",&next)==1)
	{
		if(n<N)
		{
			A[n]=next;
			n++;
		}
		else{
			excess++;
			printf("We have an excess of elements");
		}
	}	
i=n-1;
selection(A,i);
for(i=0;i<n;i++)
{
	printf("\n %d",*(p+i));
}
}

void selection(int[] array, int startIndex)
{
    if ( startIndex >= array.length - 1 )
        return;
    int minIndex = startIndex;
    for ( int index = startIndex + 1; index < array.length; index++ )
    {
        if (array[index] < array[minIndex] )
            minIndex = index;
    }
    int temp = array[startIndex];
    array[startIndex] = array[minIndex];
    array[minIndex] = temp;
    selectionSort(array, startIndex + 1);

	
}
	
	

