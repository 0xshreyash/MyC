#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#include<strings.h>


int main(int argc, char* argv[])
{
	char string1[10]="HELLO";
	char string2[2]="";
	printf("%d",strcmp(string1,string2));
	return 0;	
}