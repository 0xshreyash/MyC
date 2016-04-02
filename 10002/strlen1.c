#include<stdio.h>
#include<stdlib.h>

void ato(char c[]);

int main(int argc,char *argv[])
{
	char c[1000];
	gets(c);
	ato(c);
}
void ato(char c[])
{
	int i,j;int a[2000];
	for(i=0;c[i]!='\0';i++);
	printf("The length of the string is %d\n",i);
	for(j=0;j<i;j++)
	{
		a[j]=c[j];
	}
	
	for(j=0;j<i;j++)
	{
		printf("%d",a[j]);
	}
	return;
}