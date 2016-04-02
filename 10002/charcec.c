#include<stdio.h>
#include<stdlib.h>
int
main(int charc, char* charv[])
{
	char c;
	int wc=0,lc=0;
	while((c = getchar())!= EOF)
	{
		if(c=='\n')
		{
			lc++;
		}
		else
		{
			wc++;
		}
		if(c
	}
	printf("Word Count:%d\n",wc);
	printf("Line Count:%d\n",lc);
	return 0;
}