#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define CHOICES 4
#define LARGE_START 50
#define LARGE_END 100
#define MEDIUM_START 10
#define MEDIUM_END 49
#define SMALL_START 1
#define SMALL_END 9
#define ADD_TO_RAND 1


int input_taker();
void printing_choices(int choices[]);
void assigning_functions(int choices[]);
int divide(int a,int b);
int multiply(int a,int b);
int subtract(int a,int b);
int add(int a,int b);
int find_answers(int (*F[])(int,int),int choices[],int buddy,int sum,int make);


int main(int argc, char *argv[])
{
	int i=0,j=0,make=0;
	int choices[CHOICES];

	printf("Now we will ask you to give your inputs:\n");
	for(i=0;i<CHOICES;i++)
	{

		choices[i]=input_taker();
		
	}

	printf("Your choices are:\n");
	printing_choices(choices);

	make= 500 + ADD_TO_RAND+ rand() % (500);
	printf("You meed to make the numbers %d",make);
	//find_answers(F,choices,j,sum),make;

	return 0;


}
int input_taker()
{
	int a;int choice=0;
	printf( "What magnitude do you want your first choice to be ??\n" );
	printf( "1.Large\n2.Medium\n3.Small\n" );
	scanf("%d",&a);
	switch(a)
	{ 
		case 1: choice=ADD_TO_RAND + LARGE_START + rand() % (LARGE_END - LARGE_START);
		break;
		case 2: choice=ADD_TO_RAND + MEDIUM_START + rand() % (MEDIUM_END - MEDIUM_START);
		break;
		case 3: choice=ADD_TO_RAND + SMALL_START + rand() % (SMALL_END - SMALL_START);
		break;
	}
	return choice;
}
void printing_choices(int choices[])
{
	int i=0;
	for(i=0;i<CHOICES;i++)
	{
		printf("%d choice is %d\n",(i+1),choices[i]);
	}
	return;
}
void assigning_functions(int choices[])
{
	int (*F[4])(int,int);
	int sum=0;
	F[0]=add;
	F[1]=subtract;
	F[2]=multiply;
	F[3]=divide;
	

}
int add(int a,int b)
{
	return a+b;
}
int subtract(int a,int b)
{
	return (a-b);

}
int multiply(int a,int b)
{
	return (a*b);
}
int divide(int a,int b)
{
	if(a%b==0)
		return a/b;
	return 0;
}
int  find_answers(int (*F[])(int,int),int choices[],int buddy,int sum,int make)
{
	int i=0,j=0;
	
	if(buddy==4||sum==make)
	{
		return sum;
	}
	for(i=0;i<CHOICES;i++)
	{
		if(i!=buddy)
		{
			for(j=0;j<4;j++)
			{
				sum=sum+F[j](choices[buddy],choices[j]);
				buddy++;
				sum=find_answers(F,choices,buddy,sum);

			}
		}
	}

	


}




