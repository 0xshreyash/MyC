/*
Author: Xiaoliang Yu
Create time: 10/10/2015
*/

//Libraries

#include <stdlib.h>

/****************************************************************/
//Type definitions

typedef struct{

    void *location;
    size_t sz_memory;

} Memory_t;


typedef struct{

    void *ptr_pool;
    size_t sz_pool;
    size_t step_sz_pool;
    Memory_t *memblocks;

} MemoryPool_t;


/****************************************************************/
//Function definitions

MemoryPool_t MemoryPool_create(size_t initial_sz_pool, size_t step_sz_pool);
void *MemoryPool_malloc(MemoryPool_t *mempool, size_t sz_mem);
void *MemoryPool_realloc(MemoryPool_t *mempool, void *mem, size_t new_sz_mem); //Not being implemented yet
void *MemoryPool_free(MemoryPool_t *mempool, void *mem); //Not being implemented yet
void MemoryPool_destory(MemoryPool_t *mempool);
