#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void main()
{
	int **hello; 
	

	if(hello != NULL)
	{

		printf("Hi");
	}
	
	hello = malloc(sizeof(int *));
	hello[0] = malloc(sizeof(int));

	return;
}