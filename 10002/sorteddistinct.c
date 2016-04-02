#include<stdio.h>
#include<stdlib.h>
#define n 100
int
main(int charc,char* charv[])
{
	
	int size,i,j,temp,arr[n];
	printf("Enter array size:\n");
	scanf("%d",&size);
	for(i=0;i<size;i++)
	{
		scanf("%d",&arr[i]);
		printf("\n");
	}
	printf("The array before is:\n");
	for(i=0;i<size;i++)
	{
		
		printf("%d\n",arr[i]);
	}
	for(i=0;i<size;i++)
	{
		for(j=i+1;j<size;j++)
		{
			if(arr[i]>arr[j])
			{
				temp=arr[i];
				arr[i]=arr[j];
				arr[j]=temp;
			}
			else if(arr[i]==arr[j])
			{
				for(int k=j;k<size-1;k++)
				{
					arr[k]=arr[k+1];
				}
				size=size-1;
			}
		}
	}
	printf("The array after sorting and leeching is:\n");
	for(i=0;i<size;i++)
	{
	
		printf("%d\n",arr[i]);
	}
}
