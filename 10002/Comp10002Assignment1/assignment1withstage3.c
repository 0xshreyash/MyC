#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<strings.h>
#include<ctype.h>
#include<math.h>

#define MAX_LINE_LEN 1000

#define MAX_LINES_OUT 10

#define MAX_QLEN 100

#define LINE_OK 0
#define LINE_DONE (-1)

#define DEBUG 0
#define VOLUBLE 1

int main(int argc, char *argv[])
	{
		char *query,c,*str;
		int q_len=0,i=0,str_len=0,count_b=0,count_l=1;
		query=argv[1];
		while((c=getchar())!=EOF)
		{
			str[i]=c;
			i++;
		}
		if(!*query)
		{
			printf("The query is empty, program shall be terminated");
			exit(EXIT_FAILURE);
		}
		q_len=strlen(query);
		if(q_len>MAX_QLEN)
		{
			printf("The query is too long, Please try with a shorter query");
			exit(EXIT_FAILURE);
		}
		
		str_len=strlen(str);
		if(!*str)
		{
			printf("The string is empty, program shall be terminated");
			exit(EXIT_FAILURE);
		}
		if(str_len>MAX_LINE_LEN)
		{
			printf("The query is too long, Please try with a shorter query");
			exit(EXIT_FAILURE);
		}
		/*Stage:0 starts*/
		printf("S0: query = %s",query);	
		printf("\n---\n");
		/*Stage:0 ends*/
		/*Stage 1 starts*/
		for(i=0;str[i]!='\0';i++)
		{ 
			count_b++;
			if(str[i]=='\n')
			{
				printf("\nS1: line %4d, bytes = %d\n---\n",count_l,count_b);
				count_b=0;
				count_l++;
			}	
			printf("%c",str[i]);
			}
		}
		
			
		
		