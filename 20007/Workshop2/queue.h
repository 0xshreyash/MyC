#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "list.h"

typedef struct 
{
	List head;
}queue_t;


queue_t *make_empty_queue();
queue_t *add_node(queue_t *q, void *data);
void  *delete_node(queue_t *q);
//void free_queue(queue_t *q);
