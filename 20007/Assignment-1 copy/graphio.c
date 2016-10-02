/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 * Shreyash Patodia (spatodia@student.unimelb.edu.au)
 *
 * This module provides all the IO functionality related to graphs.
 *
 *
*/

/****************************************************************/
                    /* Header files */ 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "graphio.h"

/****************************************************************/
                   /* Hash Defines */

/* Length of longest label */
#define MAX_LINE_LEN 256 

/****************************************************************/
                /* Function definitions */

static void initialize_vertex(Graph graph, int id);

/****************************************************************/
                    /* Functions */ 

/* 
 * Load the graph from the input file 
 *
 * Input Parameter : string with the name of the input file
 * 
 * Returned Value : pointer to the new graph (graph_t)
 */

Graph load_graph(char *input) 
{
    
    FILE *input_file;   
    int i = 0;
    
    input_file = fopen(input, "r");
    assert(input_file != NULL);

    Graph graph;

    int order = 0;

    /* The \n gets rid of hassle of removing the new line
     * at the end of each line */ 
  	fscanf(input_file, "%d\n", &order);

    graph = new_graph(order);

    for(i=0; i<graph->order; i++)
    {
        /* Initialize a vertex by allocating memory to store the
         * label and also make the list of incoming and outgoing
         * edges NULL
         */
    	initialize_vertex(graph, i);

        /* Giving each vertex it's unique name and id */
        graph->vertices[i].id = i;

        /* The \n makes sure there are no unwanted newlines
         * in our string
        */ 
        fscanf(input_file, "%s\n", graph->vertices[i].label);
    }

    /* v1 is the vertex an edge originates from and v2 is the vertex the
     * edge goes to */
    int v1, v2;

    /* Read edges from the input file and add it's edges on the 
     * graph */  
    while((fscanf(input_file, "%d %d\n", &v1, &v2)) == 2)
    {
        add_edge(graph, v1, v2) ;
    }

    fclose(input_file);

    return graph;

}

/****************************************************************/

/* Initializes a vertex by allocating space for the label and 
 * setting the List out and List in to null 
 *
 * Input Parameters : The graph and the subscript of the vertex
 * we want to initialize
 * 
 * Returned Values : void, since we have a pointer to the graph
 */

static void initialize_vertex(Graph graph, int id)
 {
    graph->vertices[id].label = (char *)malloc(sizeof(char)*MAX_LINE_LEN);
    graph->vertices[id].in = graph->vertices[id].out = NULL;
 }

/****************************************************************/

/* Prints the graph to the output file who's name has been 
 * provided as a parameter to the function
 *
 * Input Parameters : The name of the output file and the graph 
 * that we want to print
 *
 *  Returned Value : void, only prints the graph using fprintf
 */

void print_graph(char *output, Graph graph) 
{
	FILE *output_file;
    int i;

    output_file = fopen(output, "w");
    assert(output_file != NULL);

    /* Formatting for the .dot file */
    fprintf(output_file, "digraph {\n");
    
    /* Printing each vertex and the vertices it has
     * outgoing edges to
     */
    for(i=0; i<graph->order; i++)
    {

        fprintf(output_file, " ");

        /* Print label of current vertex */
        print_vertex_label(output_file, &graph->vertices[i]);

        /* Print all the vertices it has outgoing edges to */
        if(graph->vertices[i].out != NULL)
        {
            fprintf(output_file, "-> {");   

            /* Calling print_list from list.c and passing print_vertex_label()
             * as one of it's arguments 
             */
            print_list(print_vertex_label, output_file,
                                     graph->vertices[i].out);
            fprintf(output_file, "}"); 

        }
        
        /* Formatting */
        fprintf(output_file, "\n");
    }

    /* Formatting */
    fprintf(output_file, "}\n");

    fclose(output_file);
    return;

}

/****************************************************************/

/* 
 * Prints the label of the vertex surrounded by spaces to the
 * file specified as it's parameter
 * 
 * Input Parameters : the file in which vertex label must be
 * printed to, vertex who's id we will print into the file
 *
 * Returned Value : void
 */

void print_vertex_label(FILE *file, void *vertex) 
{
	if(vertex)
    {
		fprintf(file, " %s ", ((Vertex)vertex)->label);
	}
	return;
}

/****************************************************************/

/*
 * Prints the id of a vertex then a newline to the file specified
 * as an input parameter
 *
 * Input Paramters: file that output is going to be printed to, 
 * the vertex who's id we will print into the file 
 *
 * Returned Values : void 
 */

void print_vertex_id(FILE *file, void *vertex) 
{
    if (vertex)
    {
        fprintf(file, "%d\n", ((Vertex)vertex)->id);
    }
    return;
}

/****************************************************************/

/*
 * Returns a sequence of vertices read from file 
 *
 * Input Parameters : file that will be use to load vertex
 * sequence from, our graph taken from input
 *
 * Returned Values : A list of vertices read from the input 
 * file  
 */
List load_vertex_sequence(FILE *file, Graph graph) {
    const char *err_duplicate = "Error: duplicate vertex %d %s\n";
    const char *err_order = "Error: graph order %d, loaded %d vertices\n";
    List list = NULL;
    int id;

    while(fscanf(file, "%d\n", &id) == 1) 
    {
        assert(id >= 0);
        assert(id < graph->order);

        if (!insert_if(id_eq, graph->vertices + id, &list)) {
            fprintf(stderr, err_duplicate, id, graph->vertices[id].label);
            exit(EXIT_FAILURE);
        }
    }

    if (len(list) != graph->order) {
        fprintf(stderr, err_order, graph->order, len(list));
        exit(EXIT_FAILURE);
    }

    return list;
}
                   /* Module complete */
/****************************************************************/
