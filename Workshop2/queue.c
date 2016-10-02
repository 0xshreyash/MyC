#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "list.h"
#include "queue.h"




queue_t *add_node(queue_t *q, void *data)
{
	List new;
	assert( q != NULL);

	insert(data, &q->head);
	printf("%d\n", *((int *)((q->head)->data)));
	
	/*new = push(q->foot, data);

	q->foot = new;*/
	return q;
}
void *delete_node(queue_t *q)
{
	assert(q!=NULL);
	List old_head;
	void *val;


	if(q->head == NULL)
	{
		return NULL;

	}
	else
	{
		 val = pop(&q->head);
	}
	return val;
}

/*void free_queue(queue_t *q)
{
	assert(q!=NULL);
	List curr, prev;
	curr = q->head;
	while(curr)
	{
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(q);

}*/