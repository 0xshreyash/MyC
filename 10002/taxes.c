#include<stdio.h>
#include<stdlib.h>

#define rate0 0.000
#define rate1 0.190
#define rate2 0.325
#define rate3 0.370
#define rate4 0.450
#define ratem 0.015

#define thresh0 18200.0
#define thresh1 37000.0
#define thresh2 80000.0
#define thresh3 180000.0

#define tax0 0.00
#define tax1 (tax0 + ((thresh1-thresh0)*rate1))
#define tax2 (tax1 + ((thresh2-thresh1)*rate2))
#define tax3 (tax2 + ((thresh3-thresh2)*rate3))





int
main(int argc, char* argv[]){
	double inc=0.0,tax=0.0;
	printf("Enter income of the given person:");
	if(scanf("%lf",&inc)!=1)
	{
		printf("Incorrect number of inputs program terminated");
        exit(EXIT_FAILURE);
	}
	if(inc<thresh0)
	{
		tax=tax0;
	}
	
	else if(inc>=thresh0 && inc<=thresh1)
	{
		tax= tax0+ rate1*(inc-thresh0);
	}
	else if(inc<=thresh2)
	{
		tax= tax1+ rate2*(inc-thresh1);
	}
	else if(inc<=thresh3)
	{
		tax= tax2+ rate3*(inc-thresh2);
	}
	else
	{
		tax= tax3 + rate4*(inc-thresh3);
	}
	double medicare=ratem*inc;
	double net=inc-tax-medicare;
	printf("%f\n",inc);
	printf("%f\n",tax);
printf("%f\n",medicare);
printf("%f\n",net);
}