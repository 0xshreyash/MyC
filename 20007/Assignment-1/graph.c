/*
 * COMP20007 Design of Algorithms
 * Semester 1, 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 * Shreyash Patodia (spatodia@student.unimelb.edu.au) | 767336
 * 
 * This module provides functions for graph(graph_t) manipulation 
 * 
*/

/****************************************************************/ 
 					  /* Header Files */
#include <stdlib.h>
#include <assert.h>

#include "graph.h"

/****************************************************************/
/****************************************************************/ 
 					   /* Functions */

/*
 * Creates a pointer to the new graph by allocating space to it
 * and assigning graph->size as 0 and order to graph->order
 * graph->size = no. of edges
 *
 * Input Parameter : order of the graph (no. of vertices)
 *
 * Returned Value : A pointer to a graph(graph_t)  
 *
 */

Graph new_graph(int order) 
{
	
	Graph graph; 

	/* Allocating space for graph of type Graph(graph_t *) */
	graph = (Graph)malloc(sizeof(*graph));
	assert(graph);

	graph->order = order;
	graph->size = 0;

	/* Allocating space for vertices of the graph */
    graph->vertices = (Vertex)malloc(order*sizeof(*graph->vertices));
	assert(graph->vertices);

    return graph;
}

/****************************************************************/

/*
 * Checks if aim and vertex are pointers to the same memory address
 * 
 * Input Parameters : aim and vertex which are polymorphic inputs
 *
 * Returned Value : true if aim and vertex point to the same 
 * location, otherwise false
 * 
 */

bool ptr_eq(void *aim, void *vertex) 
{

	if((Vertex)aim == (Vertex)vertex)
	{
		return true;
	}
	return false;
}

/****************************************************************/

/*
 * Checks if aim and vertex have the same vertex id 
 * 
 * Input Parameters : aim and vertex which are polymorphic inputs
 *
 * Returned Value : true if aim and vertex have the same 
 * id, otherwise false
 * 
 */

bool id_eq(void *aim, void *vertex) 
{
	if(((Vertex)aim)->id == ((Vertex)vertex)->id)
	{
		return true;
	}
    return false;
}

/****************************************************************/

/*
 * Adds an edge to a graph from v1 to v2
 * 
 * Input Parameters : graph of type Graph, source vertex of edge
 * v1 and the sink vertex of the edge v2
 *
 * Returned Value : void return value
 * 
 */

void add_edge(Graph graph, int v1, int v2) 
{
	/* Inserting v2 to the list of vertices v1 has outgoing edges 
       to */
	graph->vertices[v1].out = push(graph->vertices[v1].out,
	                                   &graph->vertices[v2].id);

	/* Inserting v1 to the list of vertices v2 has incoming edges
	   from */
    graph->vertices[v2].in = push(graph->vertices[v2].in, 
    	                               &graph->vertices[v1].id);
    graph->size++;
}

/****************************************************************/

/*
 * Frees the memory allocated in the graph 
 * 
 * Input Parameters : graph of type Graph
 *
 * Returned Value : void return value
 * 
 */

void free_graph(Graph graph) 
{
	int i;

	for(i=0; i<graph->order; i++)
	{
		/* Free memory allocated for each vertex */
		if(graph->vertices[i].out != NULL)
		{
			free_list(graph->vertices[i].out);
		}
		if(graph->vertices[i].in != NULL)
		{
			free_list(graph->vertices[i].in);
		}
		free(graph->vertices[i].label);
	}

	/* Free the pointer to the array of vertices */
	free(graph->vertices);

	/* Free graph */
	free(graph);
	
	/* Ta-da done !! */	
}

                   /* Module complete */
/****************************************************************/
