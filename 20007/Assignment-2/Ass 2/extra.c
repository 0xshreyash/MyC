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
#define MAX_TRY_PERLEN 1000000


/****************************************************************/
 				   /* Function Protoypes */

static unsigned int next_prime(unsigned int num);
static int is_prime(unsigned int nxt_num);
int check_and_add_to_collided(char **collided_strings, char *check_str);
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
 * the first prime after twice the expected input size
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
 * Returned Value : void return value
 */

void collide_dumb(unsigned int size, unsigned int seed, int n) 
{
	srand(seed);
	print_rndm(size);
	int count = 0;
	int length = 1;
	unsigned int codes_per_len = 0;
	int i = 0;
	int is_there = 0;

	char **collided_strings = malloc(sizeof(collided_strings[0])*n);

	/* Assigning collided_strings to null before using them */
	for(int i = 0; i < n;i++)
	{
		collided_strings[i] = NULL;
	}

	/* We will use the strings to generate our strings to hash to zero */
	const char domain_str[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";

	unsigned char check_str[MAXSTRLEN];


	/* Generating n strings to hash to zero */
	while(count < n)
	{
		/* We only try MAX_TRY_PERLEN times in order to make sure we do not have a infinite loop */
		if(codes_per_len == MAX_TRY_PERLEN)
		{
			length++;
			codes_per_len = 0;
		}
		for(i = 0; i<length; i++)
		{
			check_str[i] = domain_str[rand()%strlen(domain_str)];

		}
		check_str[length] = '\0';

		/* the universal_hash checks if it hashes to 0 */
		if(universal_hash(check_str, size) == 0)
		{
			is_there = check_and_add_to_collided(collided_strings,(char *)check_str);
			if(is_there == 1)
			{
				printf("%s\n", (char *)check_str);
				is_there = 0;
				count++;
			}
			
		} 
		/* We only go up to MAXSTRLEN -2 */
		if(length == MAXSTRLEN - 2)
		{
			fprintf(stderr, "Cannot generate more strings for collision !! Sorry !!\n");
			exit(EXIT_FAILURE);

		}
		
		codes_per_len++; 

	}

	/* Freeing the memory that was allocated in function execution */
	free(check_str);
	i = 0;

	while(i < n && collided_strings[i] != NULL)
	{
		free(collided_strings[i]);
		i++;
	} 
	free(collided_strings);

	return;
}

/****************************************************************/

/* 
 * Function takes as input the array of strings that stores the 
 * strings that have already collided and the string that has 
 * currently been generated, if they are the same we return 0, if not 
 * we add the string to the array and return 1
 *
 * Input Parameter : the array of strings that have already been
 * collided to and the current string generated which hashes to 
 * zero
 *
 * Returned Value : 1 if the new string is unique and 0 if the
 * new string is not unique
 * unique means that it hasnt been hashed to 0 before and thus
 * has not be printed
 */

int check_and_add_to_collided(char **collided_strings, char *check_str)
{
	int i = 0;
	while((collided_strings[i]) != NULL)
	{
		if(strcmp(collided_strings[i], check_str) == 0)
		{
			return 0;
		}
		i++;
	}
	collided_strings[i] = (char *)malloc(sizeof(char)*(MAXSTRLEN + 1));
	strcpy(collided_strings[i], check_str);
	collided_strings[i][strlen(check_str)] = '\0';
	return 1;

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
 * Returned Value : void
 */

void collide_clever(unsigned int size, unsigned int seed, int n) 
{
	int ascii_val = size;
	int count = 0;
	char check_str[MAXSTRLEN];

	srand(seed);
	print_rndm(size);

	while(ascii_val < 33)
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
		count ++;
		if(count == MAXSTRLEN - 2)
		{
			fprintf(stderr, "Cannot generate more strings for collision !! Sorry !!\n");
			exit(EXIT_FAILURE);
		}
	}

	return;
}

/****************************************************************/

/*
 * The next_prime code used here is similar to the
 * code Alastair Moffat uses in his book
 * Programming, Problem Solving and Abstration with C. 
 * although it is not a copy of his code and is essentially
 * my own implementation of it
 *
 * Input - An unsigned integer as input
 * Output - The first prime number after input
 *
 * Function takes a number as input and and returns the
 * first prime number after the input as output
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
	/* We generate only 254 values since we may have some issues
	 * with the buffer if we generate strings of length 255 because
	 * of the use of fgets in the code
	 */

	printf("%d\n", MAXSTRLEN - 2);

	int i = 0;

	for(i = 0; i<MAXSTRLEN - 2; i++)
	{
		printf("%u\n", rand()%size);

	}

	return;
}

/****************************************************************/
				         /* Ta-Da */





