#include<stdio.h>
#include<stdlib.h>
#define N 100
void hanoi(char from,char via,char to,int n);




int 
main(int argc,char* argv[])
{
	int n;
	printf("Here we attempt to solve the towers of hanoi ");
	printf("\nPlease enter the value of n for which the towers of hanoi are to be calculated\n");
	scanf("%d",&n);
	hanoi('A','B','C',n);
}
void
hanoi(char from,char via,char to,int n)
{
	int i;
	if(n<=0)
	{
		return ;
	}
	hanoi(from,to,via,n-1);
	for(i=1;i<n;i++)
	{
		printf(" ");
	}
	printf("\nMove from %c to %c\n",from,to);
	hanoi(via,from,to,n-1);
}
	