/*
Author: Xiaoliang Yu
Create time: 13/10/2015

Description: This file provides memory pool functionality
             *Currently this doesn't support free specified memory block in the pool
             *Currently this doesn't support


Special Notes for developer:

This file follows the C99 standard (compatible with gun11).
please don't use -ansi option to compile it
(Dimefox uses the default setting which does not use -ansi)
According to gcc official https://gcc.gnu.org/onlinedocs/gcc/Standards.html,
the current default standard used is gun11

const is used for function arguments where possible to avoid careless
mistake(unintended assignments)

__inline__ is used for function arguments where possible to increase performance
*/

//Libraries


#include "yxl_Memorypool.h"
#include "yxl_common.h" //My custom library

/****************************************************************/
//Get the memory space from system

MemoryPool_t MemoryPool_Create(size_t initial_sz_pool, size_t step_sz_pool)
{
    return (MemoryPool_t){.ptr_pool = trymalloc(initial_sz_pool), .sz_pool = initial_sz_pool, .step_sz_pool = step_sz_pool, .memblocks = trymalloc(sizeof(Memory_t))};
}


/****************************************************************/
//Get the memory space from system

void *MemoryPool_Malloc(MemoryPool_t *mempool, size_t sz_mem)
{

}
