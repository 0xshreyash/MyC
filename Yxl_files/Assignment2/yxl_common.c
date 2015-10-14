/*
Author: Xiaoliang Yu
Create time: 01/09/2015

Description: This file provides useful functions


Special Notes for developer:

This file follows the C99 standard (compatible with gun11).
please don't use -ansi option to compile it
(Dimefox uses the default setting which does not use -ansi)
According to gcc official https://gcc.gnu.org/onlinedocs/gcc/Standards.html,
the current default standard used is gun11

const is used for function arguments where possible to avoid careless
mistake(unintended assignments)

__inline__ is used for function arguments where sensible to increase performance
*/

//Libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "yxl_common.h"

/****************************************************************/

//Macros definitions

#ifndef TRYMALLOC_MAX_TRIAL

    #define TRYMALLOC_MAX_TRIAL 3

#endif // TRYMALLOC_MAX_TRIAL

/****************************************************************/

//To convert every character in src to lowercase
//sizeof(src) should be <= sizeof(dest)
//Terminator must exist in src
__inline__ void strtolower(const char src[const], char * const dest)
{
    int i;
    size_t sz_src = strlen(src);

    for(i=0; i < sz_src; i++)
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
    size_t len_src = strlen(src);

    while(i < len_src)
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
    size_t sz_str = strlen(str);

    for(i=0; i < sz_str; i++)
    {
        //checking blank or non-printable characters
        if(str[i] != ' ' && str[i] != '\n' && str[i] != '\t' && str[i] != '\r')
            return 0;
    }

    return 1;
}

/****************************************************************/

//Check whether the char array is null-terminated
__inline__ bool __attribute__((pure))
IsNullTerminated(const char str[const], const size_t size_str)
{
    size_t i;
    for(i=size_str - 1; i >= 0; i--)
    {
        if(str[i] == '\0')
            return true;
    }

    return false;
}

/****************************************************************/

//Try to malloc, if failed, terminate the program
__inline__ void __attribute__((malloc)) *trymalloc(const size_t size_var)
{
    void *mem;
    unsigned int count_trial = 0;


    while(((mem = malloc(size_var)) == NULL) && (count_trial++) <= TRYMALLOC_MAX_TRIAL)
        ;

    if(mem)
        return mem;
    else
        exit_with_error("Memory allocation(malloc) failed");
        return false;
}

/****************************************************************/

//Try to realloc, if failed, terminate the program
__inline__ void __attribute__((malloc)) *tryrealloc(void * const ptr, const size_t size_var)
{
    void *mem;
    unsigned int count_trial = 0;


    while(((mem = realloc(ptr, size_var)) == NULL) && (count_trial++) <= TRYMALLOC_MAX_TRIAL)
        ;

    if(mem)
        return mem;
    else
        exit_with_error("Memory allocation(realloc) failed");
        return false;
}


/****************************************************************/

//output out the error message to stderr and Terminate the execution

__inline__ void exit_with_error(const char str_err[const])
{
    fprintf(stderr, "FATAL: %s\n",str_err);
    exit(EXIT_FAILURE);
}
