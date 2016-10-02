/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 *
 * This module is for the implementation of tasks specific to assignment 2
 *
*/
#ifndef EXTRA_H
#define EXTRA_H

/* Determine appropriate size of a hash table given input size n */
unsigned int determine_size(unsigned int n);

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_dumb(unsigned int size, unsigned int seed, int n);

/* Print n strings that are hashed to 0 by universal_hash seeded with seed */
void collide_clever(unsigned int size, unsigned int seed, int n);

#endif
