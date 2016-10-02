/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 *
 * This module provides fundamental functionality used to
 * interpret generic pointers into typed data.
 *
*/
#ifndef TYPES_H
#define TYPES_H

#include <stdio.h>
#include <stdbool.h>

/* Returns whether n1 is equal to n2 */
bool int_eq(long n1, long n2);

/* Prints n to file */
void int_print(FILE *file, long n);

/* Returns whether str1 is equal to str2 */
bool str_eq(char *str1, char *str2);

/* Returns a copy of str */
char *str_copy(char *str);

/* Prints str to file */
void str_print(FILE *file, char *str);

#endif
