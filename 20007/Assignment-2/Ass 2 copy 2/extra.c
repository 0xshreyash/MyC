/*
 * COMP20007 Design of Algorithms
 * Semester 1, 2016
 *
 * Shreyash Patodia (spatodia@student.unimelb.edu.au) | 767336
 * Assignment - 2
 * 
 * This module provides functions that can be used to determine
 * a suitable size for a hash table and also generate collisions
 * in the hash table
 */

/****************************************************************/
                       /* Header Files */ 

#include "extra.h"
#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/****************************************************************/
 					   /* Hash Defines */

#define MAXSTRLEN 256                   
#define ASCII_SMALLEST_PRINTABLE 33 /* I don't include space */
#define ASCII_LARGEST_PRINTABLE 126


/****************************************************************/
 				   /* Function prototypes */

static unsigned int next_prime(unsigned int num);
static int is_prime(unsigned int nxt_num);

void print_rndm(unsigned int size);

/****************************************************************/
				  /* Function Definitions */
/* 
 * Function takes the expected number of inputs as argument and
 * then generates a size which is the lowest prime number greater 
 * than twice the size of the hash table
 *
 * Input Parameter : the expected number of inputs to the hash
 * function, unsigned int n
 *
 * Returned Value : the determined size of the input which is
 * bigger the first prime after the current expected input size
 */

unsigned int determine_size(unsigned int n) 
{
	unsigned int det_size = next_prime(2*n);

    return det_size;
}

/****************************************************************/

/* 
 * Function takes the size of the hash table, the seed and the
 * number of collisions to be generated as input and generates
 * those collisions in a seemingly dumb way and flags if it fails
 * to do so
 *
 * Input Parameter : the unsigned int size of the hash table, the 
 * seed of type int and the number of collisions, n of type int
 *
 * Returned Value : void return val
 */

void collide_dumb(unsigned int size, unsigned int seed, int n) 
{
	int count = 0;
	unsigned char str[MAXSTRLEN];
	int len = 0;

	str[len] = ASCII_SMALLEST_PRINTABLE;
	str[len + 1] = '\0';

	srand(seed);
	print_rndm(size);
	
	int i = 0;
	while(count < n)
	{
		for(i=0; i<=(ASCII_LARGEST_PRINTABLE - ASCII_SMALLEST_PRINTABLE); i++)
		{
			str[len] = ASCII_SMALLEST_PRINTABLE + i;
			str[len + 1] = '\0';

			if(universal_hash(str, size) == 0)
			{
				printf("%s\n", str);
				count ++;
				if(count == n)
				{
					break;
				}
			} 
		}

		str[len] = 'a';
		str[len + 1] = '\0';

		if(len == MAXSTRLEN - 1)
		{
			fprintf(stderr, "Cannot generate more strings for collision !! Sorry !!\n");
			exit(EXIT_FAILURE);
		}
		len++;
	}

	return;
}

/****************************************************************/

/* 
 * Function takes the size of the hash table, the seed and the
 * number of collisions to be generated as input and generates
 * those collisions in a seemingly clever way and flags if it fails
 * to do so
 *
 * Input Parameter : the expected number of inputs to the hash
 * function, unsigned int n
 *
 * Returned Value : the determined size of the input which is
 * bigger the first prime after the current expected input size
 */

void collide_clever(unsigned int size, unsigned int seed, int n) 
{
	int ascii_val = size;
	int count = 0;
	char check_str[MAXSTRLEN];

	srand(seed);
	print_rndm(size);

	while(ascii_val <= 33)
	{
		ascii_val *= 2;
	}
	while(count < n)
	{
		check_str[count] = ascii_val;
		check_str[count + 1] = '\0';
		if (universal_hash((unsigned char *)check_str, size) == 0)
		{
			printf("%s\n", check_str);
		}
		count ++ ;
		if(count >= MAXSTRLEN - 1)
		{
			printf("Cannot generate more strings for collision !! Sorry !!\n");
			exit(EXIT_FAILURE);
		}
	}

	return;
}

/****************************************************************/

/*
 * The next_prime code used here is similar to the
 * code Alastair Moffat uses in his code in the book
 * Programming, Problem Solving and Abstration with C. 
 * although it is not a copy of his code and is essentially
 * my own implementation of it
 *
 * Input - An unsigned integer as input
 * Output - The first prime number after input
 *
 * Function takes a number as input and and returns the
 * first prime number after the input as output
 *
 */

static unsigned int next_prime(unsigned int num)
{
	/* One more than the 2*(expected number of inputs)
	 * since 2*n is anyways even
	 */
	unsigned int nxt_num = num + 1;
	while(is_prime(nxt_num) != 1)
	{
		nxt_num++;
	}

	return nxt_num; 
}

/****************************************************************/

/* 
 * Input - An unsigned integer, nxt_num
 * Output - 1 or 0
 *
 * Function takes a number, nxt_num as input and returns
 * 1 if it is prime and 0 if it is not
 */

static int is_prime(unsigned int nxt_num)
{
	unsigned int j = 2;

	/* Handling exceptional cases */
	if(nxt_num <= 1)
	{
		return 0;
	}
	if(nxt_num == 2)
	{
		return 1;
	}

	/* Finding a divisor of the number */
	for(j = 2; j*j<=nxt_num; j++)
	{
		if(nxt_num % j == 0)
		{
			return 0;
		}
	}
	return 1; 
}

/****************************************************************/

/*
 * Function takes the size of the hash table as input and displays
 * all the random numbers generated during the hashing process
 *
 * Input Parameter : size of the hash table as an unsigned int
 *
 * Returned Value : void
 */

void print_rndm(unsigned int size)
{
	printf("%d\n", MAXSTRLEN - 1);
	int i = 0;
	for(i = 0; i<MAXSTRLEN - 1; i++)
	{
		fprintf(stderr, "%u\n", rand()%size);

	}

	return;
}

/****************************************************************/
				         /* Ta-Da */





