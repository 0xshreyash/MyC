#include<stdio.h>
#include<stdlib.h>
int
main(int charc, char*charv[])
{
	int n;
	while(scanf("%d",&n)==1)
	{
		printf("%d  |",n);
		for(int i=1;i<=n;i++)
		{
			printf("*");
		}
		printf(" \n");
	}
}
