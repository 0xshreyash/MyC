/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 *
 * This module provides the functionality related to hash functions.
 *
*/
#ifndef HASH_H
#define HASH_H

/* Used as the second hashing function on double hash */
unsigned int linear_probe(void *e, unsigned int size);

/* Very simple hash */
unsigned int worst_hash(void *e, unsigned int size);

/* Bad hash function */
unsigned int bad_hash(char *key, unsigned int size);

/* Basic numeric hash function */
unsigned int num_hash(long n, unsigned int size);

/* Universal hash function as described in Dasgupta et. al 1.5.2 */
unsigned int universal_hash(unsigned char *key, unsigned int size);

#endif
