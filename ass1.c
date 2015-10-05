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

#define STR_SIZE 1000000

#define MIN_LEN 2

#define CONST1 30
#define CONST2 2

#define MIN_LEN 2
#define UP_B 3


#define LINE_OK 0
#define LINE_LONG (-1)

#define DEBUG 0



typedef struct 
{
	char line[MAX_LINE_LEN];
	double counter;
	int lno;
}ranker_t; 

int instr(char str[]);

void intialize(ranker_t ranked[]); 
void printer(ranker_t ranked[]);
void ranking(ranker_t ranked[],char strtmp[],double score,int count_l);

void inarr(int arr[][MAX_QLEN],int q_len);
void prinarr(int arr[][MAX_QLEN],int q_len,char q[]);
double comparr(int arr[][MAX_QLEN],int n,int cq);

double stage2(int i,int j,char str[],char query[]);
void stage4(int i,int j,char str[],char q[],int arr[][MAX_QLEN]);

int main(int argc, char *argv[])
	{
		char str[STR_SIZE],query[STR_SIZE],cq[STR_SIZE],c;  
		/*query is the original pattern and q is the pattern after removal of
		non alnum characters*/
		char strtmp[STR_SIZE];
		/*Variable to pass each line into ranking()*/
		
		int i=0,j=0,count=0,count_l=1,count_b=0,q_len=0,s_len=0,n=0;
		int cql=0,line_stat=LINE_OK;
		double count_same=0.0,max_count=0.0,score=0.0;
		int arr[MAX_QLEN][MAX_QLEN],count2=0.0;
		/*Array to store the f of each i,j pair*/
		
		ranker_t ranked[MAX_LINES_OUT];
		/*Array of structure to give ranks*/
		
		q_len=strlen(argv[1]);
		strcpy(query,argv[1]);
		inarr(arr,q_len);
		/*Intialising arr to zero*/
		
		intialize(ranked);
		/*Initalizing the structure*/
		
		line_stat=instr(str);
		/*Taking Inputs*/
		
		if(line_stat==LINE_LONG)
			{
				printf("A line in the string is too long");
				exit(EXIT_FAILURE);
			}
		/*Checking if a line is too long and abortin if it is */	
		s_len=strlen(str);
		
		if(s_len==0)
		{
			printf("Enter a valid string");
			exit(EXIT_FAILURE);
		}
		
		if(q_len==0)
		{
			printf("Enter a valid query");
			exit(EXIT_FAILURE);
		}
		
		if(q_len>MAX_QLEN)
		{
			
			printf("The query is too long");
			exit(EXIT_FAILURE);
		}
		
		
		/*Here we print the query i.e S0*/
		printf("S0: query = %s",query);	
		printf("\n---");
		
		/*Here we find the part of query which requires us to make 
		the pattern without non alphanumeric characters*/
		for(i=0;i<q_len;i++)
		{
			if(isalnum(query[i]))
				{
					cq[count2++]=query[i];
				}
		}
		cql=strlen(cq);
		
		for(i=0;str[i]!='\0';i++)
		{ 
			
			if(!(str[i]=='\n')&&(count_b==0)) 
			{
				printf("\n");
			}
			/*To print a new line character after S0 and every S4*/
	
			if(!(str[i]=='\n'))
			{
				count_b++;
				strtmp[count++]=str[i];
				printf("%c",str[i]);
				
			}
			/*Printing every line*/
		
			for(j=0;query[j]!='\0';j++)
			{
				count_same=0.0; 
				count_same=stage2(i,j,str,query);
				/*Geting matches for the given pattern*/
				
				if(max_count<count_same)
				{
					max_count=count_same;
				}
				/*Assigning the highest number of matches to max_count*/
				
				stage4(i,j,str,cq,arr);
				/*Putting values into the debugging array, f(i,j)*/
			}
			if(str[i]=='\n')
			{
				strtmp[count]='\0';
				if(count_b!=0)
				/*Printing only if line has more than one bytes*/
				{
					printf("\nS1: line %4d, bytes = %d\n",count_l,count_b);
					printf("S2: line %4d, score = %7.3f\n",count_l,max_count);
					/*Printing S1 and S2*/
					
					if(DEBUG)
					{	
					prinarr(arr,cql,cq);
					}
					/*Using DebugGING only when DEBUG is non-zero*/
					
					score=comparr(arr,count_b,cql);
					printf("S4: line %4d, score = %7.3f\n",count_l,score);\
					/*Computing and printing S4*/
					
					ranking(ranked,strtmp,score,count_l);
					/*Giving the line a rank*/
					
					printf("---");
				}
				count=0;
				strcpy(strtmp,"");
				score=0.0;
				inarr(arr,cql);
				n=0;
				count_l++;
				count_b=0;
				max_count=0;
				/*Re-intializing all the variables*/
			}
		}
		
		printf("-----------------------------------------------------\n");
		printer(ranked);
		/*Printing S3*/	
		return 0;
	}
	
	int instr(char str[])
	{
		int i=0,k=0,line_stat=LINE_OK;
		char c;
		while((c=getchar())!=EOF)
		{
			
			k++;
			str[i]=c;
			if(k>MAX_LINE_LEN)
			{
				line_stat=LINE_LONG;
			}
		
			if(str[i]=='\n')
			{
				k=0;
			}
			i++;	
		}
		return line_stat;
	}
		
	void intialize(ranker_t ranked[])
	{
		int i;
		for(i=0;i<MAX_LINES_OUT;i++)
		{
			strcpy(ranked[i].line,"");
			ranked[i].counter=0.0;
			ranked[i].lno=0;
		}
		return ;	
	}
	/*Function that initializes the structure*/
	
	void printer(ranker_t ranked[])
	{
		int i;
		for(i=0;i<MAX_LINES_OUT;i++)
		{
			if(ranked[i].counter>0)
			{
				printf("S3: line %4d, score = %7.3f\n%s\n---\n",ranked[i].lno,
				ranked[i].counter,ranked[i].line);
			}
		}
		return ;	
	}
	/*Function that prints the ranked lines*/
	
	void ranking(ranker_t ranked[],char st[],double max_count,int count_l)
	{
		int i;
		double temp;
		int temp2;
		char strtmp[MAX_LINE_LEN];
		for(i=0;i<MAX_LINES_OUT;i++)
		{
			if(ranked[i].counter<max_count)
			{
				strcpy(strtmp,ranked[i].line);
				strcpy(ranked[i].line,st);
				strcpy(st,strtmp);
				temp=ranked[i].counter;
				ranked[i].counter=max_count;
				max_count=temp;
				temp2=ranked[i].lno;
				ranked[i].lno=count_l;
				count_l=temp2;
			}
		}
		return;
	}
	/*Function that gives us the ranking of the lines*/
	
	void inarr(int arr[][MAX_QLEN],int q_len)
	{
		int i,j;
		for(i=0;i<q_len;i++)
		{
			for(j=0;j<q_len;j++)
			{
				arr[i][j]=0;
			}
		}
		return;
	}
	/*Function to intialize the array to 0*/
	
	void prinarr(int arr[][MAX_QLEN],int q_len,char q[])
	{
		int i,j;
		printf("DB:\t  ");
		for(i=0;i<q_len;i++)
		{
			printf("%c   ",q[i]);
		}
		printf("\n");
		for(i=0;i<q_len;i++)
		{
			printf("DB:\t");
			for(j=0;j<q_len;j++)
			{
				printf("%3d ",arr[i][j]);
			}
			printf("\n");
		}
	}
	/*Function to print the debugger in the program*/
	
	double comparr(int arr[][MAX_QLEN],int n,int cq)
	{
		int i,j;
		double score=0.0;
		
			for(i=0;i<=cq-UP_B;i++)
			{
				for(j=i+MIN_LEN;j<cq;j++)
				{
					if(arr[i][j]!=0)
					{
						
						score=score+((j-i-1)*(j-i-1)*(log2(CONST2+arr[i][j])));
					}
				}
			}
			score=score/(log2(CONST1+n));		
			return score;
	}
	/*Function to compute the score in S4*/
	
	double stage2(int i,int j,char str[],char query[])
	{
		double count_same=0.0;
		int k=i,q_index=j;
		while(tolower(str[k])==tolower(query[q_index])&&str[k]!='\0'&&
		query[q_index]!='\0'&&str[k]!='\n'&&query[q_index]!='\n')	
		{
			count_same++;
			k++;
			q_index++;	
		}
		return count_same;
	}
	/*Function to count the number of consecutive successful matches*/
	
	void stage4(int i,int j,char str[],char q[],int arr[][MAX_QLEN])
	{
		int k=i,q_index=j;
		while(tolower(str[k])==tolower(q[q_index])&&str[k]!='\0'&&
		q[q_index]!='\0'&&str[k]!='\n'&&q[q_index]!='\n')
		{
			arr[j][q_index]++;
			k++;
			q_index++;
		}
		return;
	}
	/*Function to compute the value of the array elements i.e f(i,j)*/	
					

				
		