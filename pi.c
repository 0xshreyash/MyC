#include<stdio.h>
int main()
{
	int i;float pi=0;int n;
	printf("Enter number of terms");
	scanf("%d",&n);
	for(i=0;i<=n;i++)
	{
		if(i%2==0)
			pi=pi+(4/((2*i)+1));
		else
			
			pi=pi-(4/((2*i)+1));
	}
	printf("%f",pi);
	return 0;
}
