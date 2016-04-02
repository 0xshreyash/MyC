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

#define DEBUG 1
#define VOLUBLE 1



typedef struct 
{
	char line[MAX_LINE_LEN];
	double counter;
	int rank;
	int lno;
}ranker_t;
void intialize(ranker_t ranked[]);
void printer(ranker_t ranked[]);
void ranking(ranker_t ranked[],char strtmp[],double max_count,int count_l);
void inarr(int arr[][MAX_QLEN],int q_len);
void prinarr(int arr[][MAX_QLEN],int q_len,char q[]);
double comparr(int arr[][MAX_QLEN],int n,int cq);

int main(int argc, char *argv[])
	{
		
		char str[MAX_LINE_LEN],query[MAX_QLEN];
		char strtmp[MAX_LINE_LEN];
		int i=0,j=0,k=0,count=0,count_l=1,count_b=0,m,z;
		int q_len=0,s_len=0,n=0,cq=0,p,sl;
		int q_index=0,arr[MAX_QLEN][MAX_QLEN];
		char c,str2[MAX_LINE_LEN],q[MAX_QLEN];
		ranker_t ranked[MAX_LINES_OUT];
		double count_same=0.0,max_count=0.0;
		double count_s=0.0,max_c=0.0,count_al=0.0;
		q_len=strlen(argv[1]);
		inarr(arr,q_len);
		strcpy(query,argv[1]);
		intialize(ranked);
		/*Stage 0*/
		while((c=getchar())!=EOF)
		{
			str[i]=c;
			i++;
		}
		s_len=strlen(str);
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
		if(s_len==0)
		{
			printf("Enter a valid string");
			exit(EXIT_FAILURE);
		}
		
		if(s_len>MAX_LINE_LEN)
		{
			
			printf("The string is too long");
			exit(EXIT_FAILURE);
		}
		
		printf("S0: query = %s",query);	
		printf("\n---\n");
		
		/*Stage 1*/
		for(i=0;str[i]!='\0';i++)
		{ 
			/*Stage 1*/
			count_b++;
			if(str[i]!='\n')
			{
				strtmp[count++]=str[i];
			}
			printf("%c",str[i]);
			/*Stage 2*/
			for(j=0;query[j]!='\0';j++)
			{
				k=i;
				count_same=0.0;
				q_index=j;		
				while(tolower(str[k])==tolower(query[q_index])&&str[k]!='\0'&&
					query[q_index]!='\0'&&str[k]!='\n'&&
					query[q_index]!='\n')
				{
					
					count_same++;
					k++;
					q_index++;	
				}
				
				
				
				if(max_count<count_same)
				{
					max_count=count_same;
				}
			}
			if(str[i]=='\n')
			{
				strtmp[count]='\0';
				ranking(ranked,strtmp,max_count,count_l);
			
				printf("S1: line %4d, bytes = %d\n",count_l,count_b-1);
				printf("S2: line %4d, score= %7.3f\n",count_l,max_count);
				printf("---\n");
				count=0;
				strcpy(strtmp,"");
				count_l++;
				count_b=0;
				max_count=0;
			}
		}
		/*Stage 3*/
		printf("-----------------------------------------------------\n");
		printer(ranked);
		/*End of Stage 3*/
		//Stage 4 starts here
		inarr(arr,cq);
		count_l=1;
		int count2=0.0;double score=0.0;
		n=0;
		for(i=0;str[i]!='\0';i++)
		{
			if(isalnum(str[i]))
			{
				str2[count2++]=str[i];
			}
			if(str[i]=='\n')
			{
				str2[count2++]=str[i];
			}
			
		}
		
		str2[count2]='\0';
		sl=strlen(str2);
		count2=0;
		for(i=0;i<q_len;i++)
		{
			if(isalnum(query[i]))
				{
					q[count2++]=query[i];
				}
		}
		cq=strlen(q);
		int tmpr=0,tmpc=0;
		
		for(i=0;str[i]!='\0';i++)
		{ 
			n++;
			for(j=0;q[j]!='\0';j++)
			{
				k=i;
				q_index=j;
				while((tolower(q[q_index]))==(tolower(str[k])))
				{
						arr[j][q_index]++;
						q_index++;
						k++;
				}
			}
			if(str[i]=='\n')
			{
				if(DEBUG)
				{	
				prinarr(arr,cq,q);
				}
				score=comparr(arr,n-1,cq);
				printf("S4: line %4d, score= %7.3f\n",count_l,score);
				printf("---\n");
				count=0;
				strcpy(strtmp,"");
				count_l++;
				score=0.0;
				inarr(arr,cq);
				n=0;
			}
		}
			
		
		return 0;
	}
	void intialize(ranker_t ranked[])
	{
		int i;
		for(i=0;i<MAX_LINES_OUT;i++)
		{
			strcpy(ranked[i].line,"");
			ranked[i].counter=0.0;
			ranked[i].rank=i+1;
			ranked[i].lno=0;
		}
		return ;
		
	}
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
	double comparr(int arr[][MAX_QLEN],int n,int cq)
	{
		int i,j;
		double score=0.0;
		
			for(i=0;i<=cq-3;i++)
			{
				for(j=i+2;j<cq;j++)
				{
					if(arr[i][j]!=0)
					{
						
						score=score+((j-i-1)*(j-i-1)*(log2(2+arr[i][j])));
					}
				}
			}
			score=score/(log2(30+n));		
			return score;
	}
					

				
		


	
	

			
	
		
	
		
			
		
				
					
				
			
		
			
		
		
	
		
		
		
		
		
		
