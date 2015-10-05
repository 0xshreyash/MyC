#include<stdio.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
	int n;
	scanf("%d",&n);
	
for(int i=1;i<=n;i++)
{
	printf(" ");
	for(int j=1;j<=3*(n-i);j++)
	{
		printf(" ");
	}
	for(int j=1;j<=i;j++)
	{
		printf("%3d",(i*j));
	}
	printf("\n");
}
return 0;
}