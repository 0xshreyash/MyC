/*
 * COMP20007 Design of Algorithms
 * Semester 1, 2016
 *
 * Shreyash Patodia (spatodia@student.unimelb.edu.au) | 767336
 * Clement Poh (cpoh@unimelb.edu.au)
 * Assignment - 2
 * 
 * Module contains different flavours of hash functions and
 * other functions related to generating hashes
 * 
*/

/****************************************************************/ 
                     /* Header Files */

#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/****************************************************************/ 
                     /* Hash Defines */

#define MAXSTRLEN 256

/****************************************************************/ 
 				 /* Functions Prototypes */

unsigned int *create_random_list(unsigned int size);


/****************************************************************/ 
 			    /* Functions Definitions */

/*
 * Function takes an element as input and the size of
 * the hash table in order to implement a hash function
 * that would cause a double hash with it to degenerate into a 
 * linear probe of the hash function 
 *
 * Input Parameters : a pointer to a void type which is the element 
 * and an unsigned int which is the size of the hash table 
 *
 * Returned Value : unsigned int value of 1
 */

unsigned int linear_probe(void *e, unsigned int size) 
{
	(void) e;
	(void) size;
    return 1;
}

/****************************************************************/ 

/*
 * Function takes an element as input and the size of
 * the hash table in order to implement a hash function 
 * that would return 0 no matter what the size of the hash function
 * is
 *
 * Input Parameters : a pointer to a void type which is the element
 * and an unsigned int which is the size of the hash table
 *
 * Returned Value : unsigned int value of 0
 */

unsigned int worst_hash(void *e, unsigned int size) 
{
	/* Getting rid of warnings */
    (void) e;
    (void) size;

    return 0;
}

/* Basic numeric hash function */
unsigned int num_hash(long n, unsigned int size) {
    return n % size;
}

/****************************************************************/ 

/*
 * Function takes a char *(string) as input and the size of the hash
 * table, initializes a random value and returns a valid
 * hash value based on the first character of the string, the random
 * value and the size of the hash table
 *
 * Input Parameters : The string key to be hashed and an unsigned
 * int size which is the size of the hash table
 *
 * Returned Value : An unsigned int hash value based on the size, 
 * a random number generated and the char* key's first letter 
 */

unsigned int bad_hash(char *key, unsigned int size) 
{
	/* Using static keyword in order to make sure a is the same */
	static unsigned int a = 0;
	static int is_initialized = 0; 

	if(is_initialized == 0)
	{
		a = rand() % size;
		is_initialized = 1;
	}
	
	return (a * key[0]) % size;
}

/****************************************************************/ 

/*
 * Function takes a char* (string) as input along with an unsigned
 * int size of the hash table, and returns a hash value based on
 * the universal hash function described in DPV et al 1.5.2
 *
 * Input Parameters : The string key to be hashed and an unsigned
 * int size which is the size of the hash table
 *
 * Returned Value : An unsigned int hash value based on the universal 
 * hash function based on DPV et al 1.5.2
 */

unsigned int universal_hash(unsigned char *key, unsigned int size) 
{

	unsigned int hash_val = 0; 
	static int is_initialized = 0;

	/* i is the index key */
	int i = 0;

	static unsigned int *rndm;

	if(is_initialized == 0)
	{
		is_initialized = 1; 
		rndm = create_random_list(size);
	}	

	//print_rndm(rndm, size);
	while(key[i] != '\0')
	{
		hash_val = hash_val + rndm[i]*key[i];
		i++; 
	}

	/*
	 * Making sure we hash to a value which is less than the
	 * size of our string 
	 */

	hash_val = hash_val % size; 

    return hash_val;
}

/****************************************************************/ 

/*
 * Function takes the size of the hash table as input and
 * generates as many random numbers as the max. possible input 
 * size and mods it by size in order to maintain co-primality
 * (assuming size is also a prime)
 *
 * Input Parameter : size of the hash table as a unsigned int
 *
 * Returned Value : A list of random numbers stored in an array
 */

unsigned int *create_random_list(unsigned int size)
{
	int i = 0;

	static unsigned int rndm[MAXSTRLEN - 1];

	for(i = 0; i <MAXSTRLEN - 1; i++)
	{
		rndm[i] = rand()%size;
	}

	return rndm;
}

/****************************************************************/
					    /* Ta-Da */
