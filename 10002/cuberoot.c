#include<stdio.h>
#include<stdlib.h>

double cube( double cv,double n,int i);
int
main(int argc,char *argv[])
{
	double n,cv=1.0;
	int i=4;
	
	printf("Enter number who's cube roo is to be calculated");
	scanf("%lf",&n);
	cv=cube(1.0,n,i);
	printf("The cube root in the end is :%f\n",cv);
}
double cube(double cv,double n,int i)
{
	
	
	if(i>1)
	{
		return cube(((2*cv)+(n/(cv*cv)))/3,n,i-1);
	}
	return cv;
}