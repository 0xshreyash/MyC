#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#include<strings.h>

#define  MAX_CHAR 100


char* string_dupe(char* str);

int main(int argc, char* argv[])
{
	char *str,*str2,c;
	int i=0;
	if((str=(char*)malloc(MAX_CHAR*sizeof(char)))==NULL)
		{
			
			exit(EXIT_FAILURE);
		}
		while((c=getchar())!=EOF)
		{
			if(i>=MAX_CHAR)
			{
				str=realloc(str,2*i*sizeof(char));
			}
			str[i++]=c;
		}
		str2=string_dupe(str);	
		printf("%s",str2);
		
	return 0;	
}
char* string_dupe(char* str)
{
	char* str2;int i=0;
	str2=(char*)malloc(MAX_CHAR*sizeof(char));
	while(*(str+i)!='\0')
	{
	
		if(i>=MAX_CHAR)
			{
				str2=realloc(str2,2*i*sizeof(char));
			}
			*(str2+i)=*(str+i);
	}
	return str2;
}
char** string_set_dupe(char **str)
{
	char** str;
	
