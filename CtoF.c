
#include<stdio.h>
void main()

{	char c;float f,d;
	printf("What do you want to enter temperature in ");
	scanf("%c",&c);
	printf("Enter temperature\n");
	scanf("%f",&f);
	if(c=='F')
	{
				
	d=(5.0*(f-32.0))/9.0;
	}
	else
	{
	d=((9.0/5.0)*f)+32.0;
	}
	
	printf("\nTemperature is %0.3f\n",d);
} 
