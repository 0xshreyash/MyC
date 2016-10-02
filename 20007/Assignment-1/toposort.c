/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 * Shreyash Patodia (spatodia@student.unimelb.edu.au) | 767336
 *
 * This module contains functions useful for the Topological 
 * Sorting of a graph. 
 *
 * It implements topological sort in two ways, using DFS and Kahn's
 * sorting method and also verifies whether a list is Topologically
 * sorted given a graph and the list iteslf
 *
 * References : https://en.wikipedia.org/wiki/Topological_sorting
 *
*/

/****************************************************************/ 
 					  /* Header Files */
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "toposort.h"

/****************************************************************/ 
 			      /* Function Declarations */

/* Function that is called in order to visit each vertex in the graph 
 * while performing Depth First Search */
static void dfs_visit(Graph graph, char *visited, List *order, int *id);

/* Returns a list with every vertex marked white i.e. unvisited */
static char *mark_vertices_unvisited(Graph graph);

/* Returns a list of source vertices */
static List find_source_vertices(Graph graph);

/* Returns an array containing the length of list in for
 * each vertex */
static long *find_in_lengths(Graph graph);


/****************************************************************/
/****************************************************************/ 
                       /* Functions */

/* 
 * Function performs the topological sorting of a graph using DFS
 * method, this code is based on the pseudo code given in the 
 * wikipedia reference above
 *
 * Input Parameters : graph who's topological sorting needs to be
 * found
 * 
 * Returned Values : returns a list of vertex ids sorted in
 * topological order
 */

List dfs_sort(Graph graph) 
{
	List sorted = NULL; /* List of topologically sorted vertices */

	/* 
	 * char *visited is an array that stores if the 
	 * vertex has been visted, vertex id is the array
	 * subscript ->
	 * 'w' -> white if it has not been visited 
	 * "g" -> grey if it has been visited and we are currently 
	 * visitng on of it's children i.e. it has been pre-visited
	 * but not post-visited or it's still in the stack
	 * 'b' -> black if it has been completed i.e. it has been pre-
	 * visited and post-visited
	 * 
	 * I used a char array instead of two arrays of bools in 
	 * order to save memory
	 *
	 * We mark every vertex as being unvisited and initialize it
	 * to be white i.e. unvisited
	 */
	char *visited = mark_vertices_unvisited(graph);
	
	
	/* Calling DFS visit till all the vertices have been visited 
	 */
	int i; 
	for(i = 0; i<graph->order; i++)
	{
		if(visited[i] !=  'b')
		{
			dfs_visit(graph, visited, &sorted, &graph->vertices[i].id);
		}
	}
	
	/* Freeing the list that tells us if a vertex has been 
	 * visited or not
	 */
	free(visited); 

	return sorted; 
}

/****************************************************************/

/* Function is used to mark every vertex of the graph as being 
 * unvisited i.e white or 'w' 
 *
 * Input Parameters : graph of type graph
 * 
 * Returned Values : An array of chars which holds the visited 
 * status of all the vertices where the array subscript 
 * corresponds to the vertex id
 */

static char *mark_vertices_unvisited(Graph graph)
{
	int i;
	char *visited = (char *)malloc(sizeof(char)*graph->order);
	
	/* Mark all the vertices as white i.e.
	 * unvisited initially */
	for(i = 0; i< graph->order; i++)
	{
		visited[i] = 'w'; 
	}

	return visited;
}

/****************************************************************/

/* Function checks if there are any cycles in the graph, and traverses
 * the graph following DFS and then adds the vertex to the topologically
 * sorted list after all of it's children have been explored 
 *
 * Input Parameters : the graph, the char array storing the visited
 * status for the graph vertices, the list of topologically sorted 
 * vertices and the id of the current vertex being visited
 *
 * Returned Value : void
 */

static void dfs_visit(Graph graph, char *visited, List *sorted, int *id)
{

	/* If a vertex is currently unfinished i.e. gray and we come back
	 * to it then we have a cycle thus there is no possible 
	 * topological ordering
	 */
	if(visited[*id] == 'g')
	{
		fprintf(stderr, "Not a DAG, sorry can't topologically sort it. :)\n");
		exit(EXIT_FAILURE);
	}
	
	/* *adj_node_id stores the id of the next node to be traversed 
	 * using DFS
	 */
	int *adj_node_id;

	/* If the vertex is unvisited i.e. white then mark it as visited and 
	 * active i.e. grey, then go visit vertices it has outgoing edges to
	 * in order to proceed with the depth first search 
	 */
	if(visited[*id] == 'w')
	{
		visited[*id] = 'g';

		while(graph->vertices[*id].out != NULL)
		{
			adj_node_id = pop(&graph->vertices[*id].out);
			dfs_visit(graph, visited, sorted, adj_node_id);
		}

		/* Add the current vertex to the head of list of sorted vertices
		 */ 
		(*sorted) = push((*sorted), id);

		/* Mark the current vertex as being completed i.e. black */
		visited[*id] = 'b';
	}
		
}

/****************************************************************/
/****************************************************************/

/* 
 * Function topologically sorts a graph using Kahn's method of 
 * topological sorting. The code in this function is based on 
 * the wikipedia reference give on top of this module.
 * 
 * Input Parameters : graph to be topologically sorted
 *
 * Returned Values : The list of topologically sorted vertices
 *
 */

List kahn_sort(Graph graph) 
{

	int *current_vertex;

	int *to_node;

	/* We decrement no_of_edges to signify that one edge has
	 * been deleted, all the edges need to be deleted for 
	 * a successful topological sorting
	 */
	int no_of_edges = graph->size;
	
	/* Will contain the list of topologically sorted vertices
	 */
	List sorted = NULL;

	/* List of all source vertices in the original graph 
	 */
	List no_incoming = find_source_vertices(graph);


	/* Length of List in of each vertex
	 * in_length[0] will give the length of
	 * in list of vertex id = 0
	 */
	long *in_lengths = find_in_lengths(graph);

	while(no_incoming != NULL)
	{

		current_vertex = pop(&no_incoming); 

		/* the statement to add the vertices to the tail 
		 * of sorted would be :
		 * insert(current_vertex, &sorted);
		 *
		 * but we will add to the head and reverse it later,
		 * better for running times
		 */
		sorted = push(sorted, current_vertex);
		
		while(graph->vertices[*current_vertex].out != NULL)
		{
			/* Deleting the head of list out for the
			 * current vertex using del function 
			 * I could have also used pop function
			 */
			to_node = del(id_eq, graph->vertices[*current_vertex].out->data, 
				          &graph->vertices[*current_vertex].out);

			/* Decrementing the number of edges is like decreasing an edge 
			 * from the graph this helps us check for validity of toposort
			 * later 
			 */
			no_of_edges--;

			/* Decreasing in_lengths[*to_node] is like deleting an incoming
			 * edge to *to_node, if we go to delete the edge by sifting
			 * through the list in then it would be complexity of O(|V|) for 
			 * each deletion which is undesirable 
			 */
			in_lengths[*to_node] -= 1;

			/* If there are no incoming edges then in_lengths[*to_node] 
			 * is zero and we can add it to the list with no incoming 
			 * edges
			 */
			if(in_lengths[*to_node] == 0)
			{
				no_incoming = push(no_incoming, &graph->vertices[*to_node].id);
			}
		}

	}

	/* Reverse the list to sort it the right way around */
	List old_sorted = sorted;
	sorted = reverse(sorted);
	/* We free the old pointer since reverse returns a 
	 * copy of the original list 
	 */
	free_list(old_sorted);
	free(in_lengths);

	/* If no_of_edges is not zero then we do not have a DAG
	 */
	if(no_of_edges != 0)
	{
		fprintf(stderr, "Error. The graph is probably not a DAG\n");
		exit(EXIT_FAILURE);

	}
    return sorted;
}

/****************************************************************/

/* Function finds all vertices in the graph which are sources
 * i.e. have no incoming edges and returns the list of sources.
 *
 * Input parameters : the graph
 *
 * Returned Value : A list of vertices with no incoming edges
 */

static List find_source_vertices(Graph graph)
{
	int i;
	/* Contains all the vertices that have no incoming edge */
	List no_incoming = NULL;
	
	/* Adding all the veritces with List in empty to the list of 
	 * vertices that have no incoming edge */
	for(i=0; i<graph->order; i++)
	{
		if(graph->vertices[i].in == NULL)
		{
			no_incoming = push(no_incoming, &graph->vertices[i].id);
		}
	}

	return no_incoming;
}

/****************************************************************/

/* This function finds the length of the list of incoming vertices
 * List in for each vertex.
 *
 * Input Parameter : graph to be topologically sorted
 *
 * Returned Value : the length of the incoming list of each 
 * vertex where in_lengths[0] stores the length of the in 
 * list for the 0th vertex in the graph
 */
static long *find_in_lengths(Graph graph)
{
	int i;
	long *in_lengths = (long *)malloc(sizeof(long)*graph->order);

	for(i = 0; i<graph->order; i++)
	{
		/* Using len function from list.c 
		 */
		in_lengths[i] = len(graph->vertices[i].in);
		
	}
	return in_lengths;
}

/****************************************************************/

/* Function cross-references the graph and the provided list to
 * check if the ordering in the list is a valid topological
 * sort. Implementation : We create a vertex position array
 * where we store the position of each vertex in the list i.e.
 * the subscript of the vertex position array would be the id
 * of a vertex id and the value contained would be 
 * it's position in the possibly topologically sorted list
 * provided as input. We then know that if a vertex A 
 * depends on another vertex B i.e. B.out has A then the position
 * of B should be before A in the topologically sorted list
 *
 * Input Paramter : graph and the proposed valid topological sort
 * of the list
 *
 * Returned Value : true if the list is a valid topological
 * ordering and false if it's not
 */

bool verify(Graph graph, List vertices) 
{
	/* Stores the id of a vertex adjacent to the current vertex
	 */
	int *adj_vertex_id;

	

	/* Array who's subscripts correspond to vertex ids and stores
	 * the position of each id in List vertices, the proposed
	 * topological ordering 
	 */
	int *(vertex_position_array) = (int *)malloc(sizeof(int)*graph->order);

	/* Pointer to the first element in the list, we use this
	 * pointer to create the vertex position array
	 */
	List ptr = vertices;

	/* current vertex is a pointer to the vertex we will 
	 * be working with in our computations 
	 */
	Vertex current_vertex = NULL; 

	int i = 0;

	while(ptr != NULL)
	{
		/* While we have vertices in List ptr assign
		 * each vertex a position on the basis of the 
		 * order of occurence in the list
		 * For eg, vertex_position_array[20] will be 
		 * 0 if it is the first item in the list and so
		 * on
		 */
		current_vertex = (Vertex)ptr->data;
		vertex_position_array[current_vertex->id] = i;
		ptr = ptr->next;
		i++;

	}

	while(vertices != NULL)
	{
		

		current_vertex = (Vertex)vertices->data;
		
		/* Check if any elements in the out list of the 
		 * current vertex are positioned before it in 
		 * list, and if they are then the ordering is not
		 * a valid topological ordering since if Vertex A 
		 * depends on Vertex B then it must lie after B 
		 * in a topological sort
		 */ 
		while(graph->vertices[current_vertex->id].out != NULL)
		{
			/* id of the vertex that current vertex has an edge to */
			adj_vertex_id = pop(&graph->vertices[current_vertex->id].out);
			
			if(vertex_position_array[current_vertex->id] >= 
								vertex_position_array[*adj_vertex_id])
			{
				return false;
			}
			
		}
		
		/* Iterate for each vertex */
		vertices = vertices->next;
	}

	/* If control reaches here then no invalid values have been found
	 * thus the ordering is true
	 */
    return true;
}
					/* Module complete */
/****************************************************************/
