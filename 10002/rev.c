
int main()
{
	int i,j,n,c=1;
	printf("Enter number");
		scanf("%d",&n);
		for(i=n;i>=1;i--)
	{
		for(j=1;j<=i;j++)
		{
			printf("%d",i);
			c++;
		}
		printf("\n");

	}
	return 0;
}
