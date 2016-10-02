#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "list.h"
#include "queue.h"


int main()
{
	queue_t *q;
	int *num;

	int a = 1;
	q = add_node(q, &a);	
	a = 2;
	q = add_node(q, &a);
	a = 5;
	q = add_node(q, &a);

	num = (int *)delete_node(q);
	printf("\n%d\n", *num);
	num = (int *)delete_node(q);
	printf("%d\n", *num);
	num = (int *)delete_node(q);
	printf("%d\n", *num);









	return 0;
}