/*
** COMP200007 Design of Algorithms
** Data structure to store an array of (void *)
**
** Author: Andrew Turpin
** Adapted and updated by Clement Poh
*/
#ifndef ARRAY_H
#define ARRAY_H

#include <stdbool.h>

typedef struct array {
    int size;
    void **vals;
} array_t;

/* Create an empty array */
array_t *array_create(void);

/* Add v to A */
void array_insert(array_t **A, void *k);

/* Add v to A at the start of the array */
void array_insert_MTF(array_t **A, void *k);

/* Returns a pointer to a value eq to v in A, NULL otherwise */
void *array_find(bool (*eq)(void *, void *), array_t *A, void *v);

/* Returns a pointer to a value eq to v in A, and moves it to the front */
void *array_find_MTF(bool (*eq)(void *, void *), array_t *A, void *v);

/* Delete v from A */
void array_delete(bool (*eq)(void *, void *), array_t *A, void *k);

/* Use print to print each element of A to f */
void array_fprint(void (*)(FILE *f, void *data), FILE *f, array_t *A);

#endif
