/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 *
 * This provides all the functionality related to hash tables.
 *
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdbool.h>

#include "hash.h"

/* Some type definitions for convenience */

/* Remember HT is a pointer to a hash_table_t! */
typedef struct hash_table_t *HT;

/* Elements that can be inserted into hash tables are arbitrary */
typedef void *Elem;

/* Each bucket is an arbitrary data structure */
typedef void *Bucket;

/* Typedefing functions allow for quick casting */

/* *********************************************
 * Functions to operate on individual elements
 * *********************************************/

/* Hash functions take the key, the table size */
typedef unsigned int (*Hash)(Elem e, unsigned int size);

/* Return true if arguments are equal */
typedef bool (*Eq)(Elem e1, Elem e2);

/* Parses an element from a string */
typedef Elem (*Parse)(char *str);

/* Prints an element to file */
typedef void (*Print)(FILE *file, Elem e);

/* ******************************************************
 * Functions to operate on buckets for separate chaining
 * ******************************************************/

/* Searches a b for e, returns NULL if not found */
typedef Elem (*bucket_search_fn)(Eq eq, Bucket b, Elem e);

/* Searches b for e, and moves it the front, b is updated */
typedef Elem (*bucket_search_MTF_fn)(Eq eq, Bucket *b, Elem e);

/* Insert e into b */
typedef Elem (*bucket_insert_fn)(Bucket *b, Elem e);

/* Prints the whole contents of b to f, using print on each element */
typedef void (*bucket_print_fn)(Print print, FILE *f, Bucket b);

/* The hash table collision resolution method, used for printing */
typedef enum {
    LIST,
    ARRAY,
    LINEAR,
    DOUBLE,
} Chain;

/* The interfaces a hash table expects */
/* Keep track of them in a struct */
typedef struct {
    Eq eq;
    Parse parse;
    Print print;
} Type;

struct hash_table_t {
    /* Number of elements */
    unsigned int size;

    /* An array of buckets, either array of array_t* or list_t* */
    Bucket *table;

    /* Mimicking parametric polymorphism in C
     *
     * The interfaces that a hash table expects
    */

    /* Hash function */
    Hash hash1;

    /* Second hash function for double hashing */
    Hash hash2;

    /* Functions to operate on individual elements */
    Eq eq;
    Parse parse;
    Print print;

    /* Functions to operate on buckets for separate chaining */
    bucket_search_fn _search;
    bucket_search_MTF_fn _search_MTF;
    bucket_insert_fn _insert;
    bucket_print_fn _print;

    /* The following fields aren't necessary, useful for printing */
    Chain method;
    bool MTF;
};

/* Create a new hash table, separate chaining with arrays */
extern HT new_hash_array(unsigned int size, Hash hash, Type t);

/* Create a new hash table, separate chaining with arrays and move-to-front */
extern HT new_hash_array_MTF(unsigned int size, Hash hash, Type t);

/* Create a hash table, separate chaining with linked lists */
extern HT new_hash_list(unsigned int size, Hash hash, Type t);

/* Create a hash table, separate chaining with linked and move-to-front */
extern HT new_hash_list_MTF(unsigned int size, Hash hash, Type t);

/* Create a  hash table with open addressing using linear probing */
extern HT new_hash_linear(unsigned int size, Hash hash, Type t);

/* Create a  hash table with open addressing using double hashing */
extern HT new_hash_double(unsigned int size, Hash h1, Hash h2, Type t);

/* Load data into ht from file */
extern void hash_load(HT ht, FILE *file);

/* Search ht for each elem in file */
extern void hash_search_file(HT ht, FILE *file);

/* print the whole table */
extern void hash_print(HT ht, FILE *file);

/* Search table for e and return its pointer if found, else NULL */
extern Elem hash_search(HT ht, Elem e);

/* insert element into table */
extern void hash_insert(HT ht, Elem e);

#endif
