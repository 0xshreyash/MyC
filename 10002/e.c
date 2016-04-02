#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define E0 1


double func(int n,int x);
double fact(int n);



int
main(int argc,char* argv[])
{
	int n,x;
	double e;
	printf("Here I try to compute the approximate value of e^x\n");
	printf("Enter number of times you want to summation to be worked out and also the power of x\n");
	if(scanf("%d %d",&n,&x)!=2)
	{
		printf("Enter valid input");
		exit(EXIT_FAILURE);
	}
	if(x==0)
	{
		printf("The value of e^0 is %d",E0);
		exit(EXIT_SUCCESS);
	}
	
	e=func(n,x);
	printf("\nThe value of e^x is %f\n",e);
	
}
double fact(int n)
{
	if(n==1)
	{
		return n;
	}
	else
	{
		return (n*fact(n-1));
		
	}
	return 0;
}
double func(int n,int x)
{
	if(n==0)
	{
		return 0;
	}
	else
	{
		return ((pow(x,n)/fact(n)) + func(n-1,x));
	}
	return -1;
}
