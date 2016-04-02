#include<stdio.h>
#include<stdlib.h>
#define n 1000
int
main(int charc, char *charv[]){
	int arr[n],i,j,size=0,num,freq=0;
	printf("Enter as many as 1000 characters upto ^D:\n");
	while(scanf("%d",&num)==1)
	{
		if(size<1000)
		{
			arr[size]=num;
			size++;
		}
		else
		{
			printf("Too many characters entered");
			exit(EXIT_FAILURE);
		}
	}
		printf("VALUES     FREQUENCIES\n");
		for(i=0;i<size;i++)
		{freq=1;
			for(j=i+1;j<size;j++)
			{
				if(j==(size-1))
				{
					size=size-1;
				}
				if(arr[i]==arr[j])
				{
					freq++;
					for(int k=j;k<size-1;k++)
					{
						arr[k]=arr[k+1];
						size=size-1;
					}
					
				}
			}
			printf("%3d      %3d\n",arr[i],freq);
		}
	}
			
	