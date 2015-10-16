/*
Author: Xiaoliang Yu
Create time: 10/10/2015

Description: This file supports the storage of the
             dictionary required for LZ78 compression algorithm

             *we are using trie tree to store the dictionary


Special Notes for developer:

This file follows the C99 standard (compatible with gun11).
please don't use -ansi option to compile it
(Dimefox uses the default setting which does not use -ansi)
According to gcc official https://gcc.gnu.org/onlinedocs/gcc/Standards.html,
the current default standard used is gun11

const is used for function arguments where possible to avoid careless
mistake(unintended assignments)

__inline__ is used for function arguments where sensible to increase performance
*/


//Libraries
#include <stdbool.h>
#include <string.h>

#include "GlobalSetting.h"
#include "yxl_common.h" //My custom library
#include "LZ78Dictionary.h"



/****************************************************************/

//Insert a new node to the trie tree of the dictionary

/*
Return: (bool) True if successful
              False if it's already existent
*/

__inline__ bool dictionary_insert(dictionary_t * const dictionary,
                                  const size_t index)
{
#define NEXT_NODE (dictionary->current_node->next[index])

    #if DEBUG
    if(NEXT_NODE)
    {
        exit_with_error("NEXT_NODE != NULL In dictionary_insert");
        return false;
    }
    #endif //DEBUG

    NEXT_NODE = trie_node_create(dictionary->num_elements);

    dictionary->num_elements ++;

    return true;
#undef NEXT_NODE
}


/****************************************************************/

//Direct to a new node

/*
Return: (size_t) The index of the new current_node
        NULL if the node is not existent
*/

__inline__ size_t dictionary_direct_next_node(dictionary_t * const dictionary,
                                              const size_t key)
{
#define NEXT_NODE (dictionary->current_node->next[key]) //A pointer
#define CURRENT_NODE (dictionary->current_node) // //A pointer

    if(NEXT_NODE)
    {
        CURRENT_NODE = NEXT_NODE;
        return CURRENT_NODE->index;
    }
    else
        return false;


#undef NEXT_NODE
#undef CURRENT_NODE
}


/****************************************************************/

//Create a new dictionary
//*The dictionary created by this function should be freed
//by dictionary_delete later

/*
Return: (dictionary_t *) the pointer to the new dictionary_t variable
*/

__inline__ dictionary_t *dictionary_create(void)
{
    dictionary_t * const dictionary =
            (dictionary_t *)trymalloc(1 * sizeof(dictionary_t));


    //Initialize the dictionary
    dictionary->num_elements = 1;
    dictionary->root = trie_node_create(0);

    dictionary_reset_current_node(dictionary);


    return dictionary;
}

/****************************************************************/

//Create a new trie node

/*
Return: (trie_node_t *) the pointer to the new trie_node_t variable
*/

__inline__ trie_node_t *trie_node_create(const size_t index)
{
    trie_node_t *trie_node = (trie_node_t *)trymalloc(1 * sizeof(trie_node_t));


    //Initialize the members of the trie tree
    trie_node->index = index;

    //equivalent to set all elements in the array to NULL pointer
    //with better performance
    memset(trie_node->next,0, sizeof(trie_node->next));

    return trie_node;
}


/****************************************************************/

//Delete the trie tree

__inline__ void trie_node_delete(trie_node_t * const trie_node)
{
    size_t i;

    //Delete all the child notes first
    for(i = 0; i < sizeof(trie_node->next)/sizeof(*(trie_node->next)); i++)
    {
        if(trie_node->next[i] != NULL)
            trie_node_delete(trie_node->next[i]);
    }

    //Finally, it can be freed
    free(trie_node);
}


/****************************************************************/

//Set current_node to the root of the trie tree

__inline__ void dictionary_reset_current_node(dictionary_t * const dictionary)
{
    dictionary->current_node = dictionary->root;
}


/****************************************************************/

//Delete the dictionary

__inline__ void dictionary_delete(dictionary_t * const dictionary)
{

    //Delete the nodes first
    trie_node_delete(dictionary->root);

    free(dictionary);

}
