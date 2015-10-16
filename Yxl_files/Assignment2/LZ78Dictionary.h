/*
Author: Xiaoliang Yu
Create time: 10/10/2015
*/

//Libraries
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/****************************************************************/
//Macro Definitions

//The number of distinct values will be stored in the dictionary
#define NUM_DISTINCT_VALUE CHAR_MAX - CHAR_MIN + 1


/****************************************************************/
//Type Definitions

typedef struct trie_node trie_node_t;

struct trie_node
{

    size_t index;
    trie_node_t *next[NUM_DISTINCT_VALUE];

};


typedef struct
{

    trie_node_t *root;
    trie_node_t *current_node;
    size_t num_elements;

} dictionary_t;


/****************************************************************/
//Function Prototypes

bool dictionary_insert(dictionary_t *dictionary, size_t index);
size_t dictionary_direct_next_node(dictionary_t *dictionary, size_t key);
dictionary_t *dictionary_create(void);
trie_node_t *trie_node_create(size_t index);
void dictionary_reset_current_node(dictionary_t *dictionary);
void trie_node_delete(trie_node_t * const trie_node);
void dictionary_delete(dictionary_t * const dictionary);
