/*
Author: Xiaoliang Yu
Create time: 10/10/2015

Description: This file supports the process related to Factor required by LZ78

             *Currently we only support printing out the factor!!!


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
#include <stdio.h>
#include <inttypes.h>

#include "GlobalSetting.h"
#include "LZ78Factor.h"


/****************************************************************/

//To print out the factor following the format specified
//for COMP10002 assignment 2

__inline__ void factor_print(const factor_t * const factor)
{
    //To be compatible with Windows (Maybe other OS as well),
    //size_t will be converted to
    //64 bit unsigned integer

    #if DEBUG
    if(sizeof(size_t) > sizeof(uint_fast64_t))
    {
        puts("Warning: The size of 'size_t' is larger than 'uint_fast64_t', "
             "overflow may occur.");
    }
    #endif //DEBUG

    printf("%c%"PRIuFAST64"\n", factor->ch, (uint_fast64_t)factor->index);
}


/****************************************************************/

//Insert factor to the factors array

/*
__inline__ void factors_insert(factor_t * const *factors,
                               const size_t index_factors, size_t *sz_factor,
                               const char ch, const size_t index)
{
    if(index_factors == *sz_factor)
    {
        *factors = (factor_t *)tryrealloc((sz_factor + SIZE_FACTORS_STEP) *
                                          sizeof(factor_t));
        *sz_factor = sz_factor + SIZE_FACTORS_STEP;
    }

    factors[index_factors] = {.ch = ch, .index = index};
}
*/
