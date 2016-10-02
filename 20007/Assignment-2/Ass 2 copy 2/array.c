/*
** COMP200007 Design of Algorithms
** Data structure to store an array of (void *)
**
** Author: Andrew Turpin
** Adapted and updated by Clement Poh
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "array.h"

/* Move value at pos to front of array */
static void move_to_front(array_t *A, int pos);

/* Create an empty array */
array_t *array_create(void) {
    array_t *A = malloc(sizeof(array_t));
    assert(A != NULL);

    A->size = 0;
    A->vals = NULL;

    return A;
}

/* Move value at pos to front of array */
static void move_to_front(array_t *A, int pos) {
    void *head = A->vals[pos];

    for(int j = pos; j > 0; j--) {
        void *tmp = A->vals[j];
        A->vals[j] = A->vals[j - 1];
        A->vals[j - 1] = tmp;
    }

    A->vals[0] = head;
}

/* Add v to A */
void array_insert(array_t **A, void *v) {
    if (!*A)
        (*A) = array_create();

    (*A)->size += 1;
    (*A)->vals = realloc((*A)->vals, sizeof((*A)->vals) * (*A)->size);
    assert((*A)->vals != NULL);

    (*A)->vals[(*A)->size - 1] = v;
}

/* Add v to A at the start of the array */
void array_insert_MTF(array_t **A, void *v) {
    array_insert(A, v);
    move_to_front((*A), (*A)->size - 1);
}

/* Returns a pointer to a value eq to v in A, NULL otherwise */
void *array_find(bool (*eq)(void *v, void *d), array_t *A, void *v) {
    if (!A)
        return NULL;

    for (int i = 0; i < A->size; i++) {
        if (eq(v, A->vals[i]))
            return A->vals[i];
    }

    return NULL;
}

/* Returns a pointer to a value eq to v in A, and moves it to the front */
void *array_find_MTF(bool (*eq)(void *v, void *d), array_t *A, void *v) {
    if (!A)
        return NULL;

    int i = 0;
    for (i = 0; i < A->size; i++) {
        if (eq(v, A->vals[i]))
            break;
    }

    /* Could not find v in A */
    if (i == A->size) {
        return NULL;
    } else if (i > 0) {
        move_to_front(A, i);
    }

    return A->vals[0];
}

/* Delete v from A */
void array_delete(bool (*eq)(void *v, void *d), array_t *A, void *v) {
    if (!A)
        return;

    int i = 0;
    for (i = 0 ; i < A->size; i++) {
        if (eq(v, A->vals[i]))
            break;
    }

    for (int j = i + 1; j < A->size; j++) {
        A->vals[j - 1] = A->vals[j];
    }

    A->size -= 1;
    A->vals = realloc(A->vals, sizeof(A->vals) * A->size);
}

/* Use print to print each element of A to f */
void array_fprint(void (*print)(FILE *f, void *data), FILE *f, array_t *A) {
    if (A) {
        for (int i = 0; i < A->size; i++) {
            print(f, A->vals[i]);
        }
    }
}
