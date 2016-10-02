/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 * Shreyash Patodia (spatodia@student.unimelb.edu.au) | 767336
 * Assignment - 2
 * 
 * This module provides fundamental functionality used to
 * interpret generic pointers into typed data.
 *
 */

/****************************************************************/ 
                     /* Header Files */

#include "types.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>

/****************************************************************/ 
 				      /* Functions Definitions */

/*
 * Function checks if two long values are equal or not, returns
 * true if they are and false if they are not
 *
 * Input Parameters : Two long variables, e1 and e2 to be compared
 * 
 * Returned Value : true if inputs are equal and false if they are
 * not
 */

bool int_eq(long e1, long e2) 
{
    return e1 == e2;
}

/****************************************************************/ 

/*
 * Function takes a file as a input and a variable of type long 
 * and prints the variable to the file with a preceeding
 * space
 *
 * Input Parameters : A pointer to a file and a long variable e
 *
 * Returned value : void return type 
 */

void int_print(FILE *file, long e) 
{
    fprintf(file, " %ld", e);
    return;
}

/****************************************************************/ 

/*
 * Function checks if two string values are equal or not, returns
 * true if they are and false if they are not
 *
 * Input Parameters : Two strings to be compared
 *
 * Returned Value : true if input strings are equal and false
 * if they are not
 */

bool str_eq(char *str1, char *str2) 
{

	if(strcmp(str1, str2) == 0)
	{
    	return true;
	}

   return false; 
}

/****************************************************************/ 

/*
 * Function takes a string as input and return a copy of
 * the string replacing the new line with a null byte
 *
 * Input Parameters : A string src to be copied
 *
 * Returned Value :  A copy of the string with the new line
 * replaced by a null byte
 */

char *str_copy(char *src) 
{
	/* Find length of the src string including the null byte */
	size_t str_len = strlen(src) + 1;

	char *cpy = (char *)malloc((str_len)*sizeof(char));

	strcpy(cpy, src);

	/* Removing the newline character */
    if(cpy[str_len - 2] == '\n')
    {
    	cpy[str_len - 2] = '\0';
    }

    return cpy;
}

/****************************************************************/ 

/* 
 * Function takes a string and a file as input and prints
 * the string to the file
 *
 * Input Parameters : File, file and a string, str to be written
 * to the file
 * 
 * Returned Value : void return type 
 */

void str_print(FILE *file, char *str) 
{
	//assert(file != NULL);
	//assert(str != NULL);

	fprintf(file, " %s", str);
	return;
}

/****************************************************************/ 
						/* Ta-Da */ 
