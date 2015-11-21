#include<stdio.h>
int main()
{
	int n,i,j,c=1;
	printf("Enter number of rows");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
		{
		for(j=(2*i-1);j<(2*n-1);j++)
			printf(" ");
		for(j=1;j<=i;j++)
			{
				printf("%d ",c);
				c++;
			}
		for(j=i;j>1;j++)
			{
				c--;
				printf("%d",c);
			}
		c=1;
		}return 0;
}
	

