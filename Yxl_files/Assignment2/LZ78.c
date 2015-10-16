/*
Author: Xiaoliang Yu
Create time: 5/10/2015

Description: This files provides the LZ78 compression functionality

             *Specially customized for Comp10002 Assignment 2


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

#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include "LZ78.h"

/****************************************************************/

//use LZ78 to compress the input string inputted and print out the factors

void LZ78Compress(const char * const input)
{
    size_t index_input = 0;
    size_t index_dictionary_current_node, index_dictionary_previous_node;
    size_t num_factors = 0;

    const size_t len_input = strlen(input);

    dictionary_t * const dictionary = dictionary_create();

    index_dictionary_previous_node = 0;

    //process through the whole string except the last character
    for(index_input = 0; index_input < len_input - 1; index_input++)
    {
        if(!(index_dictionary_current_node =
             dictionary_direct_next_node(dictionary, input[index_input]) ))
        {
            //The current phrase doesn't exist in dictionary
            //Add this phrase to dictionary

            dictionary_insert(dictionary, input[index_input]);

            factor_print(&((factor_t){.ch = input[index_input],
                           .index =index_dictionary_previous_node}));

            num_factors++;


            dictionary_reset_current_node(dictionary);


        }
        else
        {
        //Found a match, continue matching to find the longest matching phrase
        //in dictionary
        }

        index_dictionary_previous_node = index_dictionary_current_node;
    }


    //Special handling for the last factor
    //For ensuring the last character can be decoded correctly
    factor_print(&((factor_t){.ch = input[index_input],
                   .index = index_dictionary_previous_node}));
    num_factors++;


    dictionary_delete(dictionary);


    //To make sure factors are printed out before the encode information
    fflush(stdout);


    fprintf(stderr, "encode:%7"PRIuFAST64" bytes input\n",
            (uint_fast64_t)len_input);
    fprintf(stderr, "encode:%7"PRIuFAST64" factors generated\n",
            (uint_fast64_t)num_factors);


}

