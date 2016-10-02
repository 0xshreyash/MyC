/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 *
 * This module contains useful functions for list manipulation and creation.
 *
 * XXX: This module may be used as a black box. It is not necessary to
 * XXX: understand the implementation details of the functions to use them.
 * XXX: The intrepid student is welcome to explore and learn the dark arts.
 *
*/
#ifndef LIST_H
#define LIST_H

#include <stdbool.h>
#include <stdio.h>

/* List is a pointer to a list_t struct */
typedef struct list_t* List;

struct list_t {
    void *data;
    List next;
};

/* Pushes data as the new head of list. May be used to create a new list:
 * new_list = push(NULL, data) */
List list_push(List list, void *data);

/* Pop the head off the list */
void *list_pop(List *list);

/* Return the length of the list */
int list_len(List list);

/* Returns a reversed copy of list */
List list_reverse(List list);

/* Prepend data to list and update list */
List list_prepend(List *list, void *data);

/* Append l1 to the end of l2 */
void list_append(List l1, List *l2);

/* Inserts data into the tail of list */
void list_insert(List *list, void *data);

/* Inserts data into the tail of list or position equal to the next element */
void list_insert_by(bool (*eq)(void *data, void *node), List *list, void *data);

/* Inserts data into the tail of list. Returns true if sucessful,
 * false if it finds an element already equal to data */
bool list_insert_if(bool (*eq)(void *data, void *node), List *list, void *data);

/* Returns a pointer to key in list, returns NULL if not found */
void *list_find(bool (*eq)(void *key, void *node), List list, void *key);

/* Returns a key in list and moves it to the head, NULL if not found */
void *list_find_MTF(bool (*eq)(void *key, void *node), List *list, void *key);

/* Removes and returns the element equal to key in list,
 * returns NULL if not found */
void *list_del(bool (*eq)(void *key, void *node), List *list, void *key);

/* Returns a new list that passes the predicate p */
List list_filter(bool (*p)(void *data), List list);

/* Print list to f to stdout by applying print to each node that is not NULL */
void list_print(void (*print)(FILE *f, void *data), List list);

/* Print list to f by applying print to each node that is not NULL */
void list_fprint(void (*print)(FILE *f, void *data), FILE *f, List list);

/* Free the memory allocated to each list node */
void list_free(List list);

#endif
