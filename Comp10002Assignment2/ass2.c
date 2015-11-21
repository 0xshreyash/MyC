
/****************************************************************/ 
                        /* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

/****************************************************************/
						 /* #defines */

#define MALLOC_MSG "memory allocation"
#define REALLOC_MSG "memory reallocation"

/****************************************************************/
                    /* Typedef of structures */
 
typedef struct node node_t; /* node_t - Each node of the tree */

struct node 
{
	void *data; 			 /* String or phrase stored in the node */
	int entry;            	 /* Entry or index of each string */	
	node_t *left;            /* left subtree of node */
	node_t *rght;            /* right subtree of node */
};

typedef struct 
{
	node_t *root;            /* root node of the tree, pointer to the very begining 
	                          * of the tree */
	int (*cmp)(void*,void*); /* function pointer, to the comparison function 
	                          * of the tree */
} tree_t;

/****************************************************************/

/* prototypes for the functions in this program */

       /*****************************************/
          /* treeops function declarations */

tree_t *make_empty_tree(int func(void*,void*));
void *search_tree(tree_t *tree, void *key);
tree_t *insert_in_order(tree_t *tree, void *value);
void free_tree(tree_t *tree);

static void *recursive_search_tree(node_t*, void*,
		int(void*,void*));
static node_t *recursive_insert(node_t*, node_t*,
		int(void*,void*));
static void recursive_free_tree(node_t*);

       /*****************************************/
  /* functions made for this program to supplement treeops*/


int string_cmp(void *a, void *b);
char *get_inputs();
void exit_if_null(char *ptr, char *message); 
node_t *initialize_first_node(char *current_phrase, int size);
void encode_tree(tree_t *tree, char *input_file,int size);

/****************************************************************/
/* main function- control centre of the program to creates the tree
   takes inputs and create the dictionary */
int
main(int argc, char *argv[])
{
	char *input_file; 
	node_t *initial; 
	tree_t *tree;
	char* current_phrase;
	int size = 0;

	tree = make_empty_tree(string_cmp);


	input_file = get_inputs();
	current_phrase = malloc((strlen(input_file)+1)*sizeof(char));
	strcpy(current_phrase,"");

	initial = initialize_first_node(current_phrase, size);
	size++;
	tree = insert_in_order(tree, initial);

	encode_tree(tree, input_file, size); 

	return 0 ;
	/* Ta-da dictionary done */

}

/****************************************************************/
/* get_inputs- takes inputs from stdin and returns the input file 
   provided by the user */
char
*get_inputs()
{
	char *input_file, c;
	int n = 0, size = 100;
	

	input_file =  malloc(size);
	exit_if_null(input_file,MALLOC_MSG);

	while((c=getchar())!=EOF)
	{
		
		input_file[n]=c;
		n++;
		if(n == size)
		{
			input_file = realloc(input_file, 2*n);
			size = 2*n;
		}
		
	}
	input_file[n]='\0';
	return input_file;
}

/****************************************************************/
/* Function is called if space has been allocated to the string,
   takes the ptr to the string and relavent error messag as input 
   arguments and exits program if memory allocation/reallocation
   is unsuccessful */
void
exit_if_null(char *ptr, char *message) 
{
	if (!ptr) 
	{
		printf("Unexpected null pointer encountered during: %s\n", message);
		exit(EXIT_FAILURE);
	}
}

/****************************************************************/
/* The functions takes two void pointers, converts them to a type node_t
   and then compares the strings associated with the nodes and returs 1 
   if x->data >  y->data, -1 if x->data < y->data and 0 if they are equal*/

int
string_cmp(void *a, void *b)
{
	node_t *x = a, *y = b;
	if(strcmp(x->data,y->data)>0)
	{
		return  1;
	}
	else if(strcmp(x->data,y->data)==0)
	{
		return  0;
	}
	else
	{
		return -1;
	}
}

/****************************************************************/
/* Function takes the a pointer to the first phrase and size of 
   as argument and initializes the first node of the tree as a 
   "" string */

node_t
*initialize_first_node(char *current_phrase, int size)
{
	node_t *initial; 
	initial = malloc(sizeof(*initial));
	assert(initial!=NULL);
	initial->data = malloc(strlen(current_phrase)+1);
	assert(initial->data!=NULL);
	strcpy(initial->data,current_phrase); 
	initial->entry = size;
	return initial;

}

/****************************************************************/
/* Function takes the tree, input file and the current size of the 
   tree as arguments and encodes the tree according to the LV78 
   compression technique */
void
encode_tree(tree_t *tree, char *input_file,int size)
{
	int i = 0, phrase_index = 0, temp = 0;
	node_t *new, *locn;

	char *current_phrase; 
	current_phrase = malloc((strlen(input_file)+1)*sizeof(char));
	int len = strlen(input_file);

	for(i=0; i<len; i++)
	{
		new = malloc(sizeof(*new));
		current_phrase[phrase_index] = input_file[i];
		current_phrase[phrase_index + 1] = '\0';
		new->data = current_phrase;
		locn = search_tree(tree, new);

		if(!locn)
		{
			new->data = malloc(strlen(current_phrase)+1);
			strcpy(new->data, current_phrase);
			new->entry = size;
			tree = insert_in_order(tree, new); 
			printf("%c%d\n", current_phrase[phrase_index], temp);
			size++;
			strcpy(current_phrase, "");
			phrase_index = 0;
			temp = 0;
			continue;

		}
		else
		{
			if(input_file[i+1] == '\0')
			{
				
				printf("%c%d\n", current_phrase[phrase_index], temp);
				size++;
				strcpy(current_phrase, "");
				phrase_index = 0;
				temp = 0;

			}


			else
			{
				temp = locn->entry;
				phrase_index++;
			}

			
		}
	}
	free_tree(tree);
	return; 
}

/****************************************************************/
         /******* Alistair's treeops module **********/ 

tree_t
*make_empty_tree(int func(void*,void*)) 
{
	tree_t *tree;
	tree = malloc(sizeof(*tree));
	assert(tree!=NULL);
	/* initialize tree to empty */
	tree->root = NULL;
	/* and save the supplied function pointer */
	tree->cmp = func;    /* Into the cmp field of the the tree */     
	return tree;
}

/****************************************************************/

int
is_empty_tree(tree_t *tree) 
{
	assert(tree!=NULL);
	return tree->root==NULL;

}

/****************************************************************/

static void
*recursive_search_tree(node_t *root,
		void *key, int cmp(void*,void*)) 
{
	int outcome;
	if (!root) {
		return NULL; /* Return null if there is no root */
	}
	if ((outcome=cmp(key, root->data)) < 0) {
		return recursive_search_tree(root->left, key, cmp);
	} else if (outcome > 0) {
		return recursive_search_tree(root->rght, key, cmp);
	} else {
		/* hey, must have found it! */
		return root->data; 
	}
}

/****************************************************************/

/* Returns a pointer to the tree node storing object "key",
   if it exists, otherwise returns a NULL pointer. */
void
*search_tree(tree_t *tree, void *key) 
{
	assert(tree!=NULL);
	return recursive_search_tree(tree->root, key, tree->cmp);
} /* The interface function that can be called from the other side it in 
     turn calls the recursive function */

/****************************************************************/

/* Returns a pointer to an altered tree that now includes
   the object "value" in its correct location. */
tree_t
*insert_in_order(tree_t *tree, void *value) 
{
	node_t *new;
	/* make the new node */
	new = malloc(sizeof(*new));
	assert(tree!=NULL && new!=NULL);
	new->data = value;
	new->left = new->rght = NULL; /* Multiple assignment statements together */
	/* and insert it into the tree */
	tree->root = recursive_insert(tree->root, new,
		tree->cmp); /* All three are pointers */
	return tree;
}

/****************************************************************/

static node_t
*recursive_insert(node_t *root, node_t *new,
		int cmp(void*,void*)) {
	if (root==NULL) 
	{
		return new;
	}
	else if (cmp(new->data, root->data) < 0) 
	{
		root->left = recursive_insert(root->left, new, cmp);
	}
	else if(cmp(new->data, root->data) > 0)
	{
		root->rght = recursive_insert(root->rght, new, cmp);
	}
	return root;
}

/****************************************************************/

static void
recursive_traverse(node_t *root, void action(void*)) {
	if (root) {
		recursive_traverse(root->left, action);
		action(root->data);
		recursive_traverse(root->rght, action);
	}
} 

/****************************************************************/

 /*Applies the "action" at every node in the tree, in
   the order determined by the cmp function. */
void
traverse_tree(tree_t *tree, void action(void*)) 
{
	assert(tree!=NULL);
	recursive_traverse(tree->root, action);
}

/****************************************************************/

static void
recursive_free_tree(node_t *root) 
{
	if (root) {
		recursive_free_tree(root->left);
		recursive_free_tree(root->rght);
		free(root);
	}
}

/****************************************************************/

/* Release all memory space associated with the tree
   structure. */
void
free_tree(tree_t *tree) 
{
	assert(tree!=NULL);
	recursive_free_tree(tree->root);
	free(tree);
}

/****************************************************************/






