#include<stdio.h>
 void main()
 {
 	int n,i,x=1,j;
 	double sum=0.0;
 	scanf("%d",&n);
 	for(i=1;i<=n;i++)
 	{
 		if(i%2==0)
 		sum=sum+(4.0*(-x*(1.0/(2*i-1))));
 	else
 		sum=sum+(4.0*(x*(1.0/(2*i-1))));
 	}
 	printf("%5.4f",sum);
 }