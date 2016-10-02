#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_INITIAL_SIZE 200

typedef struct item
{

	unsigned dataIndex; 
	float key;

} HeapItem;

typedef struct heap
{

	HeapItem *H;
	unsigned int *map;
	unsigned int n;
	unsigned int size;

} Heap;

Heap *createHeap()
{
	Heap *heap = (Heap *)malloc(sizeof(Heap));
  	(*heap)->H = (HeapItem *)malloc(sizeof(heap->H))

}
