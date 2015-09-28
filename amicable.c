#include<stdio.h>
#include<stdlib.h>
#define min 220
int
main(int charc, char* charv[])
{
	int i,j;
	int sum1=0,sum2=0;
	for(i=min;i<10000000;i++)
	{
		sum1=0;
		sum2=0;
		for(j=1;j<(i/2+1);j++)
		{
			if(i%j==0)
			{
				sum1=sum1+j;
			}
		}
		for(j=1;j<(sum1/2+1);j++)
		{
			if(sum1%j==0)
			{
				sum2=sum2+j;
			}
		} 

		if(sum2==i)
		{
			printf("%d and %d are amicable pairs\n",i,sum1);
		
		}
	
	}
}
	
	
