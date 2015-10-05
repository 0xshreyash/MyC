//Algorithms are fun

/*
File name: Assignment 1.c

Author: Yu Xiaoliang

Purpose:
To search a particular string in a text
This program will return the most relevant lines from the text
The interested string will be passed as a program argument
The text will be inputted on stdin


Special Notes:

Some of the functions are declared as __inline__ in order to improve the
performance

Some of the variables are declared with static in order to improve the
performance

Some of the parts have more than one implementation, we use macro to
control which one should be used

There're two variables which are not freed since the program needs to keep
using them.

This program follows the C99 standard (compatible with gun11).
please don't use -ansi option to compile it
(Dimefox uses the default setting which does not use -ansi)
According to gcc official https://gcc.gnu.org/onlinedocs/gcc/Standards.html,
the current default standard used is gun11


*/

/****************************************************************/

/* Libraries */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <inttypes.h>

/****************************************************************/

/* Macros */

#define DEBUG 0 //Toggle for debugging mode
#define Stage4Implementation 2 //Switcher for implementation for stage4

//Maximum characters we should receive from stdin per line
#define MAX_LINELEN 1000

#define MAX_INPUTARRLEN MAX_LINELEN + 1 //+ 1 because of the '\0'
#define NUM_INTERESTEDLINES 10 //Maximum number of interested lines
#define NUM_PROG_ARGS 1 //Number of required Program arguments

//To specific which n-th program argument stores the query string
#define NUM_ARG_QUERY 1

#define STDIN_BUF_SIZE 3 * 1024 * sizeof(char) //Custom buffer size for stdin
#define STDOUT_BUF_SIZE 6 * 1024 * sizeof(char) //Custom buffer size for stdout

/****************************************************************/

/* Type definitions */

//Standard type for every line received from stdin
typedef char inputstr_t[MAX_INPUTARRLEN];


//Structure for the interested lines (lines with top 10 score)
typedef struct
{
    inputstr_t text;
    double score;
    int num;
} linedata;

/****************************************************************/

/* function prototypes */

void Validation(const int argc, char *  const args[const]);
//void Readtext(inputstr_t **text,  int *Count_line);
int Readline(inputstr_t line);
void Initialise_linedataArray(linedata *  const lInedata);

void Stage0(const char query[const]);
void Stage1(const inputstr_t line, const int No_line);
void Stage2(const inputstr_t line, const char query[const], const int No_line);
void Stage3(const linedata lInedata[const]);

void Stage4(const inputstr_t original_line, const inputstr_t line,
            const char query[const], const int No_line
            ,linedata lInedata[const]);

int Calculate_Fij(const int i, const int j, const inputstr_t line,
                              const inputstr_t interestedpart_query);

void SortLineDataArray(linedata lInedata[const], const inputstr_t original_line,
                             const int No_line, const double score);



void strtolower(const char src[const], char * const dest);
void Str_AlphanumericOnly(const char src[const], char * const dest);
int IsEmpty(const char str[const]);
int IsNullTerminated(const char str[const], const size_t size_str);
void *trymalloc(size_t size);

/****************************************************************/


// The main function which calls functions to do work

int main(int argc, char *args[])
{
#define QUERY args[1] //To use this argument easier


    int Count_line = 0;
    inputstr_t line,lowercase_line;
    char *lowercase_query;
    linedata lInedata[NUM_INTERESTEDLINES];

    Initialise_linedataArray(lInedata);

    //Check whether the input arguments are correct
    Validation(argc, args);

    //Manually set the buffer size to big number to improve performance
    setvbuf(stdin, NULL, _IOFBF, STDIN_BUF_SIZE);
    setvbuf(stdout, NULL, _IOFBF, STDOUT_BUF_SIZE);

    Stage0(QUERY);

    lowercase_query = trymalloc(sizeof(char) * (strlen(QUERY) + 1));

    //Convert to lower letter for further use
    strtolower(QUERY, lowercase_query);

    //Start processing
    while(Readline(line))
    {
        Count_line++;

        if(IsEmpty(line))
            continue;


        Stage1(line, Count_line);

        strtolower(line, lowercase_line);

        Stage2(line, QUERY, Count_line);

        Stage4(line, lowercase_line, lowercase_query, Count_line, lInedata);

    }

    printf("------------------------------------------------\n");

    Stage3(lInedata);

#undef QUERY
    return 0;
}

/****************************************************************/

//Initialize the linedata Array which stores the interested lines
__inline__ void Initialise_linedataArray(linedata * const lInedata)
{
    int i;
    for(i=0; i < NUM_INTERESTEDLINES; i ++)
    {
        /*only linedata.score will be used to check whether a
          linedata variable has valid line stored */

        lInedata[i].score = 0.0;
    }
}

/****************************************************************/

//Validate whether the program arguments are correct
__inline__ void Validation(const int argc, char * const args[])
{

    if(argc != NUM_PROG_ARGS + 1) //the name of the executable is args[0]
    {
        printf("Invalid argument passed to program...\n");
        printf("Exit now...\n");
        exit(EXIT_FAILURE);
    }
    else if(strlen(args[NUM_ARG_QUERY]) == 0)
    {
        printf("The query is empty...\n");
        printf("Exit now...\n");
        exit(EXIT_FAILURE);
    }

}

/****************************************************************/

//Read the whole text and store to array
/*__inline__ void Readtext(inputstr_t **text, int *Count_line)
{

    *Count_line = 0;

    while(fgets((*text)[*Count_line], sizeof(inputstr_t), stdin) != 0)
    {
        if(!IsNullTerminated((*text)[*Count_line], sizeof(inputstr_t)))
        {
            (*text)[*Count_line][sizeof(inputstr_t) - 1] = '\0';
        }
        else if((*text)[*Count_line][strlen((*text)[*Count_line]) - 1] == '\n')
            (*text)[*Count_line][strlen((*text)[*Count_line]) - 1] = '\0';

#if DEBUG
        //ensure the lines are inputted correctly
        printf("%s\n",text[*Count_line]);
#endif

        (*Count_line)++;
        if(((*text) =
            (inputstr_t *)
            realloc((*text), sizeof(inputstr_t) * ((*Count_line)+1)))
             == NULL)
        {
            printf("Memory Allocation Failed...\nExit now...\n");
            exit(EXIT_FAILURE);
        }


    }


    (*text) = (inputstr_t *)
                realloc((*text), sizeof(inputstr_t) * (*Count_line));

}*/

/****************************************************************/

//Read a line and store to array
__inline__ int Readline(inputstr_t line)
{
    static char *Point_newline_char;

    if(fgets(line, sizeof(inputstr_t), stdin) == 0)
    {
        //no further input
        return 0;
    }
    else
    {
        //successfully get a line from stdin
        //post-processing...
        if(!IsNullTerminated(line, sizeof(inputstr_t)))
        {
            line[sizeof(inputstr_t) - 1] = '\0';
        }

        //It must use short-circuit OR in order to get the value in Point_newline_char correct
        //This compatible with Unix(\n), Windows(\r\n) and Macs(\r)
        //Note! \r will be treated as newline character
        else if((Point_newline_char = strchr(line, '\r')) != NULL || (Point_newline_char = strchr(line, '\n')) != NULL)
        {
            Point_newline_char[0] = '\0';
        }

        return 1;
    }

}

/****************************************************************/

//Implementation of the stage 0
__inline__ void Stage0(const char query[const])
{
    printf("S0: query = %s\n", query);
}


/****************************************************************/

//Implementation of the stage 1
__inline__ void Stage1(const inputstr_t line, const int No_line)
{
    printf("---\n");
    printf("%s\n", line);
    //cast size_t to uint_fast64_t maximize the portability
    printf("S1: line%6d, bytes =%3"PRIuFAST64"\n", No_line, (uint_fast64_t) strlen(line));
}


/****************************************************************/

//Implementation of the stage 2
__inline__ void Stage2(const inputstr_t line,
                       const char query[const], const int No_line)
{

    static double score, temp_score;
    static int char_counter_line,char_counter_query;
    static int i;


#if DEBUG
    printf("DB: Converted line : %s\n", line);
#endif // DEBUG

    char_counter_line = 0;
    score = 0.0;

    //Loop through all the chars in line
    while(char_counter_line < strlen(line))
    {
        char_counter_query = 0;

        //Loop through all the chars in query
        while(char_counter_query < strlen(query))
        {
            //Found a match of a char
            if(line[char_counter_line] == query[char_counter_query])
            {
                temp_score = 1.0;

                //Continue looking for chars behind in both line and query
                for(i=1; char_counter_query + i < strlen(query) &&
                        (char_counter_line + i) < strlen(line); i++)
                {
                    if(line[char_counter_line + i] ==
                            query[char_counter_query + i])
                    {
                        temp_score++;
                    }
                    else break;
                }

                if(temp_score > score)
                    score = temp_score;
            }


            char_counter_query++;
        }

        char_counter_line++;
    }


    printf("S2: line%6d, score =%7.3f\n", No_line,score);

}


/****************************************************************/

//Implementation of the stage 3
__inline__ void Stage3(const linedata lInedata[const])
{
    static int i;

    for(i=0; i < NUM_INTERESTEDLINES && lInedata[i].score != 0; i++)
    {
        if(i != 0)
            printf("\n");

        printf("S3: line%6d, score =%7.3f\n",
               lInedata[i].num,lInedata[i].score);

        printf("%s\n",(char *)lInedata[i].text);
        printf("---");
    }

}


/****************************************************************/

//Implementation of the stage 4
__inline__ void Stage4(const inputstr_t original_line, const inputstr_t line,
                       const char query[const], const int No_line
                       , linedata lInedata[const])
{

    static int i,j,m,F,n;
    static char * interestedpart_query = NULL;
    static char * newquery = NULL;
    static double score;

    if(newquery == NULL)
    {
        //space for newquery is not allocated yet
        //dynamically allocate memory for saving memory space
        //it won't be freed since we don't know when the last line is read
        newquery = trymalloc(sizeof(char) * (strlen(query)+1));
        Str_AlphanumericOnly(query, newquery);
    }

    if(interestedpart_query == NULL)
    {
        //space for interestedpart_query is not allocated yet
        //dynamically allocate memory for saving memory space
        //it won't be freed since we don't know when the last line is read
        interestedpart_query = trymalloc(sizeof(char) * (strlen(query)+1));
    }

    m = strlen(newquery);
    n = strlen(line);
    score = 0.0;

    //numbers are retrieved from the formula given
    for(i=0; i <= m -3; i++)
    {
        //numbers are retrieved from the formula given
        for(j = i+2; j <= m - 1; j++)
        {

            strncpy(interestedpart_query, &(newquery[i]), j-i+1);

            interestedpart_query[j-i+1] = '\0';

            F = Calculate_Fij(i, j, line, interestedpart_query);

            if(!F)
            {
                //F i,j is zero, skipping further score calculations
                continue;
            }
            else
            {
                score += pow(j-i-1,2) * log2(2+F);
            }

        }
    }

    //According to the formula given
    score /= log2((double)30+n);

    printf("S4: line%6d, score =%7.3f\n", No_line,score);

    SortLineDataArray(lInedata, original_line, No_line, score);
}

/****************************************************************/

//For calculating F i,j
//required by the function Stage4
__inline__ int __attribute__((pure)) Calculate_Fij(const int i, const int j,
                              const inputstr_t line,
                              const inputstr_t interestedpart_query)

{
int F = 0;
#if Stage4Implementation == 1
    static int flag,char_counter_line,char_counter_query;
#elif Stage4Implementation == 2
    static char const * current_ptr;
#endif // Stage4Implementation


#if Stage4Implementation == 1
    char_counter_line = 0;
    char_counter_query = 0;

    //Loop through all the chars in line
    while(char_counter_line < strlen(line))
    {

        if(line[char_counter_line] == interestedpart_query[0])
        {
            //Found a match of a char
            flag = 1;
            char_counter_query = 1;

            //Loop through all the chars in query
            while(char_counter_query < strlen(interestedpart_query))
            {
                if(interestedpart_query[char_counter_query] !=
                        line[char_counter_line + char_counter_query] ||
                        char_counter_line + char_counter_query >=
                        strlen(line))
                {
                    //Not a valid match
                    flag = 0;
                    break;
                }
                char_counter_query++;
            }

            if(flag)
            {
                F++;
            }
        }



        char_counter_line++;
    }

#elif Stage4Implementation == 2

    //use strstr(From string.h) to implement this function
    current_ptr = line;
    while(current_ptr <= &(line[strlen(line) - 1]))
    {
        if((current_ptr = strstr(current_ptr, interestedpart_query))
                == NULL)
        {
            //No further matches found
            break;
        }

        F++;
        current_ptr += j-i+1;
    }

#endif

return F;
}

/****************************************************************/

//Sorting the interested lines by their scores and the number of the lines
//required by the function Stage4
__inline__ void SortLineDataArray(linedata lInedata[const], const inputstr_t original_line,
                             const int No_line, const double score)
{
    int i,j;

    for(i=0; i < NUM_INTERESTEDLINES; i++)
    {
        //Check if the score is greater than one of the current top 10 scores
        if(score > lInedata[i].score)
        {
            //The whole array shift towards positive infinity by one unit
            for(j=NUM_INTERESTEDLINES-2; j >= i; j--)
            {
                if(lInedata[j].score == 0)
                    continue;

                memcpy(lInedata[j+1].text, lInedata[j].text,
                       strlen(lInedata[j].text) + 1);

                lInedata[j+1].score = lInedata[j].score;
                lInedata[j+1].num = lInedata[j].num;
            }

            memcpy(lInedata[i].text, original_line, strlen(original_line) + 1);
            lInedata[i].score = score;
            lInedata[i].num = No_line;

            break;
        }
    }
}

/****************************************************************/

//To convert every character in src to lowercase
//sizeof(src) should be <= sizeof(dest)
//Terminator must exist in src
__inline__ void strtolower(const char src[const], char * const dest)
{
    int i;

    for(i=0; i < strlen(src); i++)
    {
        //tolower handles non-alphabetic characters
        dest[i] = tolower(src[i]);
    }

    dest[i] = '\0';

}

/****************************************************************/

//To eliminate the non-alphanumeric characters
//sizeof(src) should be <= sizeof(dest) to ensure safety
__inline__ void Str_AlphanumericOnly(const char src[const], char * const dest)
{
    int i = 0, j = 0;

    while(i < strlen(src))
    {
        if(isalnum(src[i]))
        {
            dest[j] = src[i];
            j++;
        }
        //if not alphanumeric, skip it
        i++;
    }

    dest[j] = '\0';
}

/****************************************************************/

//For checking whether a string only contains blanks or contains nothing
__inline__ int __attribute__((pure)) IsEmpty(const char str[const])
{
    int i;
    for(i=0; i < strlen(str); i++)
    {
        //checking blank or non-printable characters
        if(str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\r')
            return 0;
    }

    return 1;
}

/****************************************************************/

//Check whether the char array is null-terminated
__inline__ int __attribute__((pure)) IsNullTerminated(const char str[const], const size_t size_str)
{
    int i;
    for(i=size_str - 1; i >= 0; i--)
    {
        if(str[i] == '\0')
            return 1;
    }

    return 0;
}

/****************************************************************/

//Try to malloc, if failed, terminate the program
__inline__ void *trymalloc(size_t size)
{
    void *mem;

    if((mem = malloc(size)) != NULL)
        return mem;
    else
    {
        //It failed...
        printf("Memory allocation failed\n");
        printf("Exit now...");
        exit(EXIT_FAILURE);
    }
}
