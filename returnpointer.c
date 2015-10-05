#include<stdio.h>
#include<stdlib.h>

char* rtrnstrng();

#define N 1000

int
main(int argc, char* argv[])
{
	char *d[N]; int i=0;
	d= rtrnstrng();
	for(i=0;d[i]!='\0';i++)
	{
		printf("%s",d[i]);
	}
	printf("\n");
	return 0;
}

char* rtrnstrng()
{
	char c[N];
	gets(c);
	puts(c);
	return c;
}
