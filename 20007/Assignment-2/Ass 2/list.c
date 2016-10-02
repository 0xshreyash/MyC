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
#include <stdlib.h>
#include <assert.h>

#include "list.h"

/* An abstraction of recursively traversing a list from right to left */
static void *foldl(void *(*f)(void *acc, void *data), void *acc, List list);

/* An abstraction of recursively traversing a list from left to right */
static void *foldr(void *(*f)(void *data, void *res), void *res, List list);

/* Add one to accumulator */
static void *plus_one(void *acc, void *data);

/* Pushes data as the new head of list. May be used to create a new list:
 * new_list = push(NULL, data) */
List list_push(List list, void *data) {
    List node = malloc(sizeof(*node));
    assert(node);

    node->data = data;
    node->next = list;

    return node;
}

/* Pop the head off the list */
void *list_pop(List *list) {
    if (!*list) {
        return NULL;
    } else {
        void *data = (*list)->data;
        List ptr = *list;

        /* Update list to point at the next element */
        *list = (*list)->next;

        /* Free the memory allocated to the list node */
        free(ptr);
        return data;
    }
}

/* Return the length of the list */
int list_len(List list) {
    return (long) foldl(plus_one, 0, list);
}

/* Returns a reversed copy of list */
List list_reverse(List list) {
    return (List) foldl((void *(*)(void *, void *))list_push, NULL, list);
}

/* Prepend data to list and update list */
List list_prepend(List *list, void *data) {
    *list = list_push(*list, data);
    return *list;
}

/* Append l1 to the end of l2 */
void list_append(List l1, List *l2) {
    if (!*l2)
        *l2 = l1;
    else
        list_append(l1, &(*l2)->next);
}

/* Inserts data into the tail of list */
void list_insert(List *list, void *data) {
    list_insert_by(NULL, list, data);
}

/* Inserts data into the tail of list or position equal to the next element */
void list_insert_by(bool (*eq)(void *data, void *node), List *list, void *data) {
    if (!*list)
        *list = list_push(NULL, data);
    else if (eq && eq(data, (*list)->data))
        (*list)->next = list_push((*list)->next, data);
    else
        list_insert_by(eq, &(*list)->next, data);
}

/* Inserts data into the tail of list: returns true if sucessful,
 * false if it finds an element already equal to data */
bool list_insert_if(bool (*eq)(void *data, void *node), List *list, void *data) {
    if (!*list) {
        *list = list_push(NULL, data);
        return true;
    } else return (eq && eq(data, (*list)->data))
        ? false
        : list_insert_if(eq, &(*list)->next, data);
}

/* Returns a pointer to key in list, returns NULL if not found */
void *list_find(bool (*eq)(void *key, void *node), List list, void *key) {
    return !list
        ? NULL
        : eq(key, list->data)
            ? list->data
            : list_find(eq, list->next, key);
}

/* Returns a pointer to key in list, changes state of list */
void *list_find_MTF(bool (*eq)(void *key, void *node), List *list, void *key) {
    void *data = list_del(eq, list, key);
    if (data) {
        list_prepend(list, data);
    }
    return data;
}

/* Removes and returns the element equal to key in list,
 * returns NULL if not found */
void *list_del(bool (*eq)(void *key, void *node), List *list, void *key) {
    return !*list
        ? NULL
        : eq(key, (*list)->data)
            ? list_pop(list)
            : list_del(eq, &(*list)->next, key);
}

void list_print(void (*print)(FILE *f, void *data), List list) {
    list_fprint(print, stdout, list);
}

/* Print list to file by applying print to each node that is not NULL */
void list_fprint(void (*print)(FILE *f, void *data), FILE *f, List list) {
    if (list) {
        print(f, list->data);
        list_fprint(print, f, list->next);
    }
}

/* Free the memory allocated to each list node */
void list_free(List list) {
    if (list) {
        list_free(list->next);
        free(list);
    }
}


/* Add one to accumulator */
static void *plus_one(void *acc, void *data) {
    (void) data; /* data is unused */
    return (void *)((long)acc + 1);
}

/* An abstraction of recursively traversing a list from right to left */
static void *foldr(void *(*f)(void *data, void *res), void *res, List list) {
    return !list
        ? res
        : f(list->data, foldr(f, res, list->next));
}

/* An abstraction of recursively traversing a list from left to right */
static void *foldl(void *(*f)(void *acc, void *data), void *acc, List list) {
    return !list
        ? acc
        : foldl(f, f(acc, list->data), list->next);
}

