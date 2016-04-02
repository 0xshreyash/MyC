/*The program has been developed by Shreyash Patodia. A lot of
time has been spent into making the program efficient and not 
complex as ALGORITHMS ARE FUN and should not be confusing*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<ctype.h>
#include<math.h>

#define MAX_LINE_LEN 1000

#define MAX_LINES_OUT 10

#define MAX_QLEN 100

#define MIN_LEN 2

#define DIV_CONST 30
#define MULT_CONST 2

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
}ranker_t;  //Structure that stores the ranked lines

void check_line(char str[]);
void manip(char str[],char query[],int bytes,
				int count_l,ranker_t ranked_lines[]);

void check_query(char query[]);
void compute_changed_query(char query[],char cq[]);

void initialize_ranked(ranker_t ranked_lines[]); 
void print_rankedlines(ranker_t ranked_lines[]);
void rank_lines(ranker_t ranked_lines[],char strtmp[],
	            			  double score,int count_l);

double stage2_score(int i,int j,char str[],char query[]);

void initialize_debug(int arr[][MAX_QLEN],char query[]);
void print_debug(int debug[][MAX_QLEN],char cq[]);
void compute_debug(int i,int j,char str[],char q[],
	               				int debug[][MAX_QLEN]);

double compute_score(int debug[][MAX_QLEN],int n,char cq[]);

/*main() function takes inputs*/
/*main()-26 statements*/
int
main(int argc, char *argv[])
{
	char str[MAX_LINE_LEN],query[MAX_QLEN],c;
	strcpy(query,argv[1]);
	int bytes=0,count_l=1;
	ranker_t ranked_lines[MAX_LINES_OUT];
	initialize_ranked(ranked_lines);
	
	/*Checking if no command line argument is given*/
	if(argc<2)
	{
		printf("Sorry !! But the query is cannot be empty !!");
		exit(EXIT_FAILURE);
	}
	check_query(query);
	
	/*Printing the query*/
	printf("S0: query = %s",query);
	printf("\n---");
	
	/*Taking each line as input*/
	while((c=getchar())!=EOF)
	{	
		if(c=='\n')
		{
			/*Checking if each line is valid*/
			check_line(str);
			str[bytes]='\0';
			/*Manipulating to compute the S1,S2 AND S4*/
			manip(str,query,bytes,count_l,ranked_lines);
			strcpy(str,"");
			bytes=0;
			count_l++;
		}
		else
		{
			str[bytes]=c;
			bytes++;
		}		
	}
	printf("-----------------------------------------------------\n");
	print_rankedlines(ranked_lines);
	return 0;
}

/*Function that takes input from main() and allows us to call other
functions to manipulate the score*/
/*manip()-25 statement*/
void 
manip(char str[],char query[],int bytes,
	   int count_l,ranker_t ranked_lines[])
{  
	int debug[MAX_QLEN][MAX_QLEN],i=0,j=0;
	double max_count=0.0,score=0.0,count_same=0.0;
	char changed_q[MAX_QLEN];
	
	strcpy(changed_q,"");
	compute_changed_query(query,changed_q);
	initialize_debug(debug,changed_q);
	
	for(i=0;str[i]!='\0';i++)
	{
		if(i==0&&str[i]!='\n')
		{
			printf("\n");
		}//printf() for formatting
		
		printf("%c",str[i]);
		
		for(j=0;query[j]!='\0';j++)
		{
			count_same=stage2_score(i,j,str,query);
			
			if((max_count-count_same)<0)
			{
				max_count=count_same;
			}
			
			compute_debug(i,j,str,changed_q,debug);
		}		
	}
	
	if(bytes!=0)
		{
			printf("\nS1: line %4d, bytes = %d\n",count_l,bytes);
			printf("S2: line %4d, score =%7.3f\n",count_l,max_count);
			
			if(DEBUG)
			{
				print_debug(debug,changed_q);
			}
			
			score=compute_score(debug,bytes,changed_q);
			printf("S4: line %4d, score =%7.3f\n",count_l,score);\
			rank_lines(ranked_lines,str,score,count_l);
			printf("---");
		}
	return;
}

/*Function to check if a line has length greater than
MAX_LINE_LEN*/
/*check_line()-5 statements*/
void 
check_line(char str[])
{
	int str_len=strlen(str);
	
	if(str_len>MAX_LINE_LEN)
	{
		printf("Sorry !! But the line is too long !!");
		exit(EXIT_FAILURE);
	}
	
	return;
}

/*Function to check if the query is empty or if it
is too long*/
/*check_query()-8 statements*/
void 
check_query(char query[])
{
	int q_len=strlen(query);
	
	if(q_len>MAX_QLEN)
	{
		
		printf("Sorry !! But the query is too long !!");
		exit(EXIT_FAILURE);
	}
	
	return;
}

/*Function to compute the query for stage4*/
/*compute_changed_query()-5 statements*/
void
compute_changed_query(char query[],char cq[])
{
	int i=0,count=0;
	
	for(i=0;query[i]!='\0';i++)
	{
		if(isalnum(query[i]))
			{
				cq[count++]=query[i];
			}
	}
	
	return;
}

/*Function to intialize the ranker_t structure*/
/*initialize_ranked()-6 statements*/
void
initialize_ranked(ranker_t ranked_lines[])
{
	int i;
	
	for(i=0;i<MAX_LINES_OUT;i++)
	{
		strcpy(ranked_lines[i].line,"");
		ranked_lines[i].counter=0.0;
		ranked_lines[i].lno=0;
	}
	
	return ;	
}

/*Function to print the lines with ranks*/
/*print_rankedlines()-7 statements*/
void 
print_rankedlines(ranker_t ranked_lines[])
{
	int i;
	
	for(i=0;i<MAX_LINES_OUT;i++)
	{
		if(ranked_lines[i].counter>0)
		{
			printf("S3: line %4d, score = %7.3f\n%s\n",ranked_lines[i].lno,
			ranked_lines[i].counter,ranked_lines[i].line);
			printf("---\n");
		}
	}
	
	return ;	
}

/*Function to rank lines and store top 10
lines*/
/*rank_lines()-16 statements*/
void
rank_lines(ranker_t ranked_lines[],char st[],
		   double max_count,int count_l)
{
	int i;
	double temp;
	int temp2;
	char strtmp[MAX_LINE_LEN];
	
	for(i=0;i<MAX_LINES_OUT;i++)
	{
		if(ranked_lines[i].counter<max_count)
		{
			strcpy(strtmp,ranked_lines[i].line);
			strcpy(ranked_lines[i].line,st);
			strcpy(st,strtmp);
			temp=ranked_lines[i].counter;
			ranked_lines[i].counter=max_count;
			max_count=temp;
			temp2=ranked_lines[i].lno;
			ranked_lines[i].lno=count_l;
			count_l=temp2;
		}
	}
	
	return;
}

/*Function to intialize the array to 0*/
/*initialize_debug()-6 statements*/
void
initialize_debug(int debug[][MAX_QLEN],char query[])
{
	int q_len=strlen(query);
	int i,j;
	
	for(i=0;i<q_len;i++)
	{
		for(j=0;j<q_len;j++)
		{
			debug[i][j]=0;
		}
	}
	
	return;
}

/*Function to print the debugger in the program*/
/*print_debug()-11 statements*/
void 
print_debug(int debug[][MAX_QLEN],char cq[])
{
	int i,j;
	int cq_len=strlen(cq);
	printf("DB:\t  ");
	for(i=0;i<cq_len;i++)
	{
		printf("%c   ",cq[i]);
	}
	printf("\n");
	for(i=0;i<cq_len;i++)
	{
		printf("DB:\t");
		for(j=0;j<cq_len;j++)
		{
			printf("%3d ",debug[i][j]);
		}
		printf("\n");
	}
	return;
}

/*Function to compute the score S4*/
/*compute_score()-10 statements*/
double 
compute_score(int arr[][MAX_QLEN],int n,char changed_query[])
{
	int cq_len=strlen(changed_query);
	int i,j;
	double score=0.0;
	
	for(i=0;i<=cq_len-UP_B;i++)
	{
		for(j=i+MIN_LEN;j<cq_len;j++)
		{
			if(arr[i][j]!=0)
			{	
				score=score+((j-i-1)*(j-i-1)*
				(log2(MULT_CONST+arr[i][j])));
			}
				
		}
			
	}
	score=score/(log2(DIV_CONST+n));
	
	return score;
}

/*Function to compute the score in S2*/
/*stage2_score()-8 statements*/
double 
stage2_score(int i,int j,char str[],char query[])
{
	double count_same=0.0;
	int k=i,q_index=j;
	
	while((str[k])==(query[q_index])&&str[k]!='\0'&&
	query[q_index]!='\0')	
	{
		count_same++;
		k++;
		q_index++;	
	}
	
	return count_same;
}

/*Function to compute the debugging array*/
/*compute_debug()-7 statements*/
void 
compute_debug(int i,int j,char str[],char changed_q[],
			  int arr[][MAX_QLEN])
{
	
	int s=0,k=0;
	
	while(s<=(str_len-q_len))
		if(str[i+s+k]==P[j+k])
		{
			k++;
			if(j+k==q_len)
			{
				return s;
			}
		}
		else
		{
			s=s+i-F[i+k];
			if(F[i]
		
	/*while(tolower(str[str_index])==tolower(changed_q[cq_index])&&
		          str[str_index]!='\0'&&changed_q[cq_index]!='\0')
	{
		arr[j][cq_index]++;
		str_index++;
		cq_index++;
	}
	*/
	return;
}
void create_F(int F[],int query[])
{
	int s=2,c=0;
	while (str[s]!='\0')
	{
		if(query[c]=query[s-1])
		{
			c=c+1;
			F[s]=c+1;
			s=s+1;
		}
		else if (c>0)
		{
			c=F[c];
		}
		else
		{
			F[s]=0;
			s=s+1;
		}
	}
	return;
}
			
void 

		
