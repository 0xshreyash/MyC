#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#include<strings.h>

#define SIZE 100

void compute_F(char P[],int F[]);
int check(char T[],char P[],int F[]);

int main(int argc, char* argv[])
{
	int s=-1,f[SIZE];
	compute_F(argv[1],f);
	s=check(argv[2],argv[1],f);
	printf("%d\n",s);
	return 0;	
}
void compute_F(char P[],int F[])
{
	int s=2,c=0;
	F[0]=-1;
	F[1]=0;
	while(s<strlen(P))
	{
		if(P[c]==P[s-1])
		{
			F[s]=c+1;
			c=c+1;
			s=s+1;
		}
		else if(c>0)
		{
			c=F[c];
		}
		else
		{
			F[s]=0;
			s=s+1;
		}
	}
	return;
}
int check(char T[],char P[],int F[])
{
	int s=0,i=0;
	while(s<(strlen(T)-strlen(P)))
	{
		if(T[s+i]==P[i])
		{
			i++;
			if(i==strlen(P))
			{
				return s;
			}
		}
		else
		{
			s=s+i-F[i];
			if(F[i]>0)
			{
				i=F[i];
			}
			else
			{
				i=0;
			}
		}
	}
	return -1;
}

			
	
	