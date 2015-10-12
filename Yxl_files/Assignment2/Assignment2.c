//Algorithms are fun

/*

Comp10002 Assignment 2

Author: Xiaoliang Yu
Create time: 5/10/2015

Description: This is a compression program using LZ78 compression algorithm


Special Notes for developer:


This program follows the C99 standard (compatible with gun11).
please don't use -ansi option to compile it
(Dimefox uses the default setting which does not use -ansi)
According to gcc official https://gcc.gnu.org/onlinedocs/gcc/Standards.html,
the current default standard used is gun11

I used const for function arguments where possible to avoid careless
mistake(unintended assignments)


*/

/****************************************************************/
//Libraries

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "yxl_common.h" //My custom library
#include "LZ78.h" //Library for supporting the implementation of LZ78

/****************************************************************/
//Macros

//Settings
#define LEN_INPUT_INITIAL 1024
#define LEN_INPUT_STEP 512

#define SIZE_FACTORS_INITIAL 128
#define SIZE_FACTORS_STEP 64

//Constants




//For Internal use
#define SIZE_INPUT_INITIAL LEN_INPUT_INITIAL+1
#define SIZE_INPUT_STEP LEN_INPUT_STEP


/****************************************************************/
//Type Definitions





/****************************************************************/
//Function Prototypes

void Readtext(char ** const text);


/****************************************************************/

//The main function which control the flow of program

int main(void)
{
    char *input;

    Readtext(&input);

    LZ78Compress(input);

    return 0;
}


/****************************************************************/

//Read the whole text and store to array

//Return: (size_t) The size of the input string
__inline__ void Readtext(char ** const text)
{
    size_t index = 0;
    size_t sz_nextfetch, sz_current_iteration;
    int i=0;
    sz_nextfetch = SIZE_INPUT_INITIAL;
    *text = (char *)trymalloc(sizeof(char) * SIZE_INPUT_INITIAL);


    while(fgets((*text) + index, sz_nextfetch, stdin) != NULL)
    {
        printf("%Iu, %d \n",sz_nextfetch, i++);
        fflush(stdout);
        if(!IsNullTerminated((*text) + index, sz_nextfetch))
        {
            index += sz_nextfetch;
            sz_nextfetch = SIZE_INPUT_STEP;
            *text = (char *)tryrealloc(*text, sizeof(char) * (index + SIZE_INPUT_STEP));
        }
        else
        {
            sz_current_iteration = strlen((*text) + index);
            index += sz_current_iteration;
            sz_nextfetch -=  sz_current_iteration;
        }
    }


    if(!IsNullTerminated(*text, sz_nextfetch))
    {
        *text = (char *)tryrealloc(*text, (index + sz_nextfetch + 1) * sizeof(char));
        (*text)[index + sz_nextfetch] = '\0';
    }
    else
    {
        *text = (char *)tryrealloc(*text, strlen(*text) + 1);
    }

}


