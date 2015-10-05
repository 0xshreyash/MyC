#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define CHOICES 4
#define LARGE_START 50
#define LARGE_END 100
#define MEDIUM_START 10
#define MEDIUM_END 49
#define SMALL_START 1
#define SMALL_END 9
#define ADD_TO_RAND 1



void printing_choices(int choices[]);
int divide(int a,int b);
int multiply(int a,int b);
int subtract(int a,int b);
int add(int a,int b);


int main(int argc, char *argv[])
{
	srand ( time(NULL) );
	int i=0,j=0,make=0;
	int choices[CHOICES];
	int gen = -1;
	int to_make = 0;
	char operators[4];
	char inp[20];
	int inpnum[10];
	char inpchar[10];

	printf("Game on: \n");

	choices[0]=ADD_TO_RAND+rand()%(SMALL_END - SMALL_START);
	choices[1]=ADD_TO_RAND + MEDIUM_START + rand()%(MEDIUM_END - MEDIUM_START);
	choices[2]=ADD_TO_RAND + MEDIUM_START + rand()%(MEDIUM_END - MEDIUM_START);
	choices[3]=ADD_TO_RAND + LARGE_START + rand()%(LARGE_END - LARGE_START);

	printf("Your choices are:\n");
	printing_choices(choices);


	int (*F[4])(int,int);
	int sum=0;
	F[0]=add;
	F[1]=subtract;
	F[2]=multiply;
	F[3]=divide;

	while(j<3)
	{
		gen=rand()%4;
		if(F[gen](choices[j],choices[j+1])>0 && gen != 3)
		{
			to_make = F[gen](choices[j],choices[j+1]);
			printf("%d\n",to_make);
			j++;
			if(gen==0)
			{
				printf("+\n");

			}
			else if(gen==1)
			{
				printf("-\n");

			}
			else if(gen==2)
			{
				printf("*\n");

			}
			else if(gen==3)
			{
				printf("//\n");

			}
		}
		else if(F[gen](choices[j],choices[j+1])>0 && gen == 3)
		{
			if(choices[j]%choices[j+1]==0)
			{
				to_make = F[gen](choices[j],choices[j+1]);
				printf("%d\n",to_make);
				j++;
				if(gen==0)
				{

					printf("+\n");

				}
				else if(gen==1)
				{
					printf("-\n");

				}
				else if(gen==2)
				{
					printf("*\n");

				}
				else if(gen==3)
				{
					printf("//\n");

				}
			}
		}
	
			/* else if((choices[j+1]%choices[j]==0))
			{
				to_make = F[gen](choices[j+1],choices[j]);
				printf("%d\n",to_make);
				j++;
				if(gen==0)
				{
					printf("+\n");

				}
				else if(gen==1)
				{
					printf("-\n");

				}
				else if(gen==2)
				{
					printf("*\n");

				}
				else if(gen==3)
				{
					printf("//\n");

				}
			*/
	}

	printf("You need to make the number %d\n",to_make);

    /*printf("Please enter how you want answer:\n")

    while((c=getchar())!=EOF)
    {

    	inp[i++]=c;

    }
    inp[i]='\0';   
    int num_count=0;
    int char_count=0;
    int sum=0;
    for(i=0;inp[i]!='\0';i++)
    {
    	if(inp[i]>48 && inp[i]<58)
    	{
    		inpnum[num_count++]=atoi(inp[i]);
    	} 
    	else if(inp[i]==42 || inp[i]==43 || inp[i]==45 || inp[i]==47)
    	{

    		inpchar[char_count++]=inp[i];

    	}
    	else
    	{
    		printf("Enter valid characters only\n");
    		exit(EXIT_FAILURE);

    }
    	}

    	for(i=o;i<strlen(inp);i++)
    	{
    		if(i%4==0 && i!=0)
    		{
    			sum=sum + ()
    		}
    	}


*/

	return 0;


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

