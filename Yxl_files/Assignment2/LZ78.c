/*

Comp10002 Assignment 2

Author: Xiaoliang Yu
Create time: 5/10/2015

Description: This is a compression program using LZ78 compression algorithm


Special Notes for developer:


This program follows the C99 standard (compatible with gun11).
please don't use -ansi option to compile it
(Dimefox uses the default setting which does not use -ansi)
According to gcc official https://gcc.gnu.org/onlinedocs/gcc/Standards.html,
the current default standard used is gun11

I used const for function arguments where possible to avoid careless
mistake(unintended assignments)
*/

//Libraries

#include "LZ78.h"

/****************************************************************/

//use LZ78 to compress the input string inputted and print out the factors

void LZ78Compress(const char * const input, const size_t sz_input)
{
    size_t index_input = 0;
    size_t index_dictionary_current_node, index_dictionary_previous_node;

    dictionary_t *dictionary = dictionary_create();

    index_dictionary_previous_node = 0;

    //process through the whole string except the last character
    for(index_input = 0; index_input < sz_input - 1; index_input++)
    {
        if(!(index_dictionary_current_node =
             dictionary_direct_next_node(dictionary, input[index_input]) ))
        {
            //The current phrase doesn't exist in dictionary
            //Add this phrase to dictionary

            dictionary_insert(dictionary, input[index_input]);

            factor_print(&((factor_t){.ch = input[index_input], .index =index_dictionary_previous_node}));

            dictionary_reset_current_node(dictionary);


        }
        else ;//Found a match, continue matching to find the longest matching phrase in dictionary

        index_dictionary_previous_node = index_dictionary_current_node;
    }


    //Special handling for the last factor
    //For ensuring the last character can be decoded
    factor_t temp = (factor_t){.ch = input[sz_input], .index = index_dictionary_previous_node};
    factor_print(&temp);

}

