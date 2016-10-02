/*
 * Approximate text match score generating prrogram
 * Implemented in 4 stages
 * Written by Shreyash Patodia for Comp10002,(Algorithms are fun) in 2015
 *
 */
 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<ctype.h>
#include <math.h>

#define STR_SIZE 10000   /* Max string size to avoid abort trap */

#define MAX_LINE_LEN 1000 /* max length of each line */
#define MAX_QLEN 100      /* max length of the query */

#define MAX_LINES_OUT 10/* max number of lines to be outputted in S3 */

#define DIV_CONST 30	/* Constant used in score calculation of S4 */
#define MULT_CONST 2	/* Constant used in score calculation of S4 */

#define MIN_LEN 2       /* The min length of a match required in S4 */
#define UP_B 3		    
/* The value which control the upperbound of of outer loop in S4 */
			
#define DEBUG 0         /* When 1 will print the debugging array */

typedef struct 
{
	char line[MAX_LINE_LEN];/* line that is stored */
	double score;			/* stores the score */
	int lno;				/* stores the line no. */
}ranker_t;  		  /* Structure that stores the ranked lines */

/****************************************************************/

/* function prototypes */

void check_line(char str[]);
void manip(char str[],char query[],int count_l,
		   ranker_t ranked_lines[]);

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

/****************************************************************/

/* main() function takes inputs and calls for implementation of 
 * stages */
/* main()-25 statements */
int
main(int argc, char *argv[])
{
	
	char str[STR_SIZE],query[STR_SIZE],c;
	int bytes=0,count_l=1;
	ranker_t ranked_lines[MAX_LINES_OUT];
	initialize_ranked(ranked_lines);
	
	/* Checking if no command line query is given as input */
	if(argc<2)
	{
		printf("Sorry !! But the query is cannot be empty !!");
		exit(EXIT_FAILURE);
	}
	strcpy(query,argv[1]);
	check_query(query);
	
	/* Printing the query for S0 */
	printf("S0: query = %s",query);
	printf("\n---");
	
	/*Taking each line as input */
	while((c=getchar())!=EOF)
	{	
		/* Checking for end of each line */
		if(c=='\n') 
		{
			str[bytes]='\0';
			
			/* Checking if each line is valid */
			check_line(str);
			
			/* Manipulations to give the S1,S2,S3 AND S4*/
			manip(str,query,count_l,ranked_lines);
			strcpy(str,"");
			bytes=0;
			count_l++;
		}
		else
		{
			str[bytes]=c; /* Putting characters into the string */
			bytes++;
		}		
	}
	
	printf("---------------------------------------------");
	print_rankedlines(ranked_lines);
	/* All done !! Thank You. */
	return 0;
}

/****************************************************************/

/* Takes arguments from main() and allows us to call other
 * functions to calculate S2 and S4 scores and also prints them.
 * Also finds the ranked lines */
/* manip()-27 statements */
void 
manip(char str[],char query[],
	  int count_l,ranker_t ranked_lines[])
{  
	int debug[MAX_QLEN][MAX_QLEN],i=0,j=0,bytes=0;
	double max_count=0.0,score=0.0,count_same=0.0;
	char changed_q[STR_SIZE];
	bytes=strlen(str);
	
	strcpy(changed_q,"");
	compute_changed_query(query,changed_q);
	initialize_debug(debug,changed_q);
	
	for(i=0;str[i]!='\0';i++)
	{
		/* So that no new lines are printed when the line is empty */
		if(i==0&&str[i]!='\0') 
		{
			printf("\n");
		}
		
		printf("%c",str[i]);
		
		for(j=0;query[j]!='\0';j++)
		{
			/* Checking each str and query combination */
			count_same=stage2_score(i,j,str,query); 
			
			/* Highest score for each line determined */
			if(max_count<count_same)
			{
				max_count=count_same;
			}
			
			/* Computing the debugging array for S4 */
			compute_debug(i,j,str,changed_q,debug);
		}		
	}
	
	/* Printing only non-empty lines */
	if(bytes!=0) 
	{
		printf("\nS1: line %5d, bytes =%3d\n",count_l,bytes);
		printf("S2: line %5d, score =%7.3f",count_l,max_count);
		printf("\n");
		
		#if(DEBUG==1) /*Only printing debugger when debug is 1*/
		{
			print_debug(debug,changed_q);
		}
		#endif
		
		/* Computing S4 score */
		score=compute_score(debug,bytes,changed_q);
		printf("S4: line %5d, score =%7.3f\n",count_l,score);
		
		/* Ranking the line and storing it if required */
		rank_lines(ranked_lines,str,score,count_l);
		printf("---");
	}
	return;
}

/****************************************************************/

/* checks if a line has length greater than 1000 */
/* check_line()-5 statements */
void 
check_line(char str[])
{
	int str_len=strlen(str);
	
	if(str_len>(MAX_LINE_LEN))
	{
		printf("\nSorry !! But the next line is too long !!\n");
		exit(EXIT_FAILURE);
	}
	
	return;
}

/****************************************************************/

/* checks if the query is too long*/
/* check_query()-5 statements */
void 
check_query(char query[])
{
	int q_len=strlen(query);
	
	if(q_len>(MAX_QLEN))
	{
		
		printf("\nSorry !! But the query is too long !!\n");
		exit(EXIT_FAILURE);
	}
	
	return;
}

/****************************************************************/

/* Function to compute the query for stage4 */
/* compute_changed_query()-5 statements */
void
compute_changed_query(char query[],char changed_q[])
{
	int i=0,count=0;
	
	for(i=0;query[i]!='\0';i++)
	{
		if(isalnum(query[i])) /* Query for S4, only alpha-numeric */
			{
				changed_q[count++]=query[i];
			}
	}
	
	changed_q[count]='\0';    /* Adding the null byte in the end */
	
	return;
}

/****************************************************************/

/* Intialize the ranker_t structure */
/* Initialize_ranked()-6 statements */
void
initialize_ranked(ranker_t ranked_lines[])
{
	int i;
	
	for(i=0;i<MAX_LINES_OUT;i++)
	{
		strcpy(ranked_lines[i].line,""); /* Initializing each element */
		ranked_lines[i].score=0.0;
		ranked_lines[i].lno=0;
	}
	
	return ;	
}

/****************************************************************/

/* prints the lines with ranks */
/* print_rankedlines()-7 statements */
void 
print_rankedlines(ranker_t ranked_lines[])
{
	int i;
	
	for(i=0;i<MAX_LINES_OUT;i++)
	{
		if(ranked_lines[i].score>0) /* prints only if score is not 0 */
		{
			printf("\nS3: line %5d, score =%7.3f\n%s\n",
			ranked_lines[i].lno,ranked_lines[i].score,
			ranked_lines[i].line); 
			printf("---");
		}
	}
	
	return ;	
}

/****************************************************************/

/* ranks lines and store top 10 lines */
/* rank_lines()-16 statements */
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
		if(ranked_lines[i].score<max_count)
		{
			/* Checking if the score of the line is less than
			 * max_count and giving the line its rank */
			strcpy(strtmp,ranked_lines[i].line); 
			strcpy(ranked_lines[i].line,st);
			strcpy(st,strtmp);
			temp=ranked_lines[i].score;
			ranked_lines[i].score=max_count;
			max_count=temp;
			temp2=ranked_lines[i].lno;
			ranked_lines[i].lno=count_l;
			count_l=temp2;
		}
	}
	
	return;
}

/****************************************************************/

/* Function to intialize the array to 0 */
/* initialize_debug()-6 statements */
void
initialize_debug(int debug[][MAX_QLEN],char query[])
{
	int q_len=strlen(query);
	int i,j;
	
	for(i=0;i<q_len;i++)
	{
		for(j=0;j<q_len;j++)
		{
			debug[i][j]=0; /* Initializing debug to 0 */        
		}
	}
	
	return;
}

/****************************************************************/

/* Function to print the debugger in the program */
/* print_debug()-12 statements */
void 
print_debug(int debug[][MAX_QLEN],char changed_q[])
{
    int i,j;
	int cq_len=strlen(changed_q);
	printf("DB:\t  ");
	
	for(i=0;i<cq_len;i++)
	{
		printf("%c   ",changed_q[i]); /*Printing the changed query */
	}
	printf("\n");
	
	for(i=0;i<cq_len;i++)
	{
		printf("DB:\t");
		for(j=0;j<cq_len;j++)
		{
			printf("%3d ",debug[i][j]); 
		    /* Printing the elements of Debug */
		}
		printf("\n");
	}
	
	return;
}

/****************************************************************/

/* Function to compute the score S4 */
/* compute_score()-10 statements */
double 
compute_score(int arr[][MAX_QLEN],int n,char changed_query[])
{
	/* n is the length of each line */
	
	int cq_len=strlen(changed_query);
	int i,j;
	double score=0.0;
	
	for(i=0;i<=cq_len-UP_B;i++)        /* i in f(i,j) */
	{
		for(j=i+MIN_LEN;j<cq_len;j++)  /* j in f(i,j) */
		{
			if(arr[i][j]!=0)  /* Only adding non-zero scores */
			{	
				score=score+((j-i-1)*(j-i-1)*
				(log2(MULT_CONST+arr[i][j])));
			}		
		}	
	}
	
	score=score/(log2(DIV_CONST+n));
	
	return score;
}

/****************************************************************/

/* Function to compute the score in S2 */
/* stage2_score()-8 statements */
double 
stage2_score(int str_index,int q_index,char str[],char query[])
{
	double count_same=0.0;
	
	while((str[str_index])==(query[q_index])&&str[str_index]!='\0'&&
	query[q_index]!='\0') /* Checking for the number of matches */
	{
		count_same++;     /* Incrementing count_same accordingly */
		str_index++;			
		q_index++;	
	}
	
	return count_same;
}

/****************************************************************/

/* Function to compute the debugging array */
/* compute_debug()-7 statements */
void 
compute_debug(int str_index,int j,char str[],char changed_q[],
			  int debug[][MAX_QLEN])
{
	int cq_index=j;/* To preserve j as the row and cq_index as 
					* column of the debug */
	
	while(tolower(str[str_index])==tolower(changed_q[cq_index])&&
		          str[str_index]!='\0'&&changed_q[cq_index]!='\0')
		  /* Checking for the number of matches */
	{
		debug[j][cq_index]++;/* Incrementing corresponding element */
		str_index++;
		cq_index++;
	}
	
	return;
}

/****************************************************************/
  /* Can't wait for assignment-2 because Algorithms are fun */


		
		
	
		
	
	

		
		
		
		
		
		
		