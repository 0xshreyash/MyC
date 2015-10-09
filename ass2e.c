#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

#define MALLOC_MSG "memory allocation"
#define REALLOC_MSG "memory reallocation"



typedef struct node node_t;

struct node 
{
	void *data; 
	int max_match;
	int entry;             /* ptr to stored structure */
	node_t *left;            /* left subtree of node */
	node_t *rght;            /* right subtree of node */
};

typedef struct 
{
	node_t *root; /* root node of the tree, pointer to the very begining 
	of the tree */
	int (*cmp)(void*,void*); /* function pointer, to the comparison function 
	of the tree */
} tree_t;

/* prototypes for the functions in this library */

tree_t *make_empty_tree(int func(void*,void*));
int is_empty_tree(tree_t *tree);
void *search_tree(tree_t *tree, void *key);
tree_t *insert_in_order(tree_t *tree, void *value);
void free_tree(tree_t *tree);

static void *recursive_search_tree(node_t*, void*,
		int(void*,void*));
static node_t *recursive_insert(node_t*, node_t*,
		int(void*,void*));
static void recursive_free_tree(node_t*);
int string_cmp(void *a, void *b);

char *get_inputs();
void exit_if_null(char *ptr, char *message); 
static void
recursive_traverse(node_t *root, void action(void*));

void
print_then_free(void *x);
void
traverse_tree(tree_t *tree, void action(void*)) ;


int
main(int argc, char *argv[])
{
	char *input_file, *new_input_file;
	node_t *new, *locn, *max_locn, *initial;
	tree_t *tree;
	char* current_phrase;
	int i,j,k;
	int count = 0;
	int byte = 0;
	int length = 1; 
	int size = 0;
	int phrase_index = 0;

	tree = make_empty_tree(string_cmp);


	input_file = get_inputs();
	current_phrase = malloc((strlen(input_file)+1)*sizeof(char));
	strcpy(current_phrase,"");

	initial = malloc(sizeof(*new));
	assert(initial!=NULL);
	initial->data = malloc(strlen(current_phrase)+1);
	assert(initial->data!=NULL);
	strcpy(initial->data,current_phrase); 
	initial->entry = size;
	size++;
	initial->max_match = 0; 
	tree = insert_in_order(tree, initial);
	for(i=0; i<strlen(input_file)-1; i++)
	{
		current_phrase[phrase_index] = input_file[i];
		current_phrase[phrase_index + 1] = '\0';
		new = malloc(sizeof(*new));
		new->max_match = 0;
		new->data = current_phrase;
		locn = search_tree(tree, new);
		printf()
		if(!locn)
		{
			new->data = malloc(strlen(current_phrase)+1);
			strcpy(new->data, current_phrase);
			new->entry = size;
			tree = insert_in_order(tree, new);
			/* free(new->data);
			free(new); */
			size++;
			strcpy(current_phrase, "");
			phrase_index = 0;

		}
		else
		{
			max_match = locn->entry;
			phrase_index++;
		}

	}











	/*printf("%s",input_file);*/


	return 0 ;


}
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
void
exit_if_null(char *ptr, char *message) 
{
	if (!ptr) 
	{
		printf("Unexpected null pointer encountered during: %s\n", message);
		exit(EXIT_FAILURE);
	}
}
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

int
is_empty_tree(tree_t *tree) 
{
	assert(tree!=NULL);
	return tree->root==NULL;

}


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

/* Returns a pointer to the tree node storing object "key",
   if it exists, otherwise returns a NULL pointer. */
void
*search_tree(tree_t *tree, void *key) 
{
	assert(tree!=NULL);
	return recursive_search_tree(tree->root, key, tree->cmp);
} /* The interface function that can be called from the other side it in 
     turn calls the recursive function */




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



static void
recursive_traverse(node_t *root, void action(void*)) {
	if (root) {
		recursive_traverse(root->left, action);
		action(root->data);
		recursive_traverse(root->rght, action);
	}
} 

 /*Applies the "action" at every node in the tree, in
   the order determined by the cmp function. */
void
traverse_tree(tree_t *tree, void action(void*)) 
{
	assert(tree!=NULL);
	recursive_traverse(tree->root, action);
}
void
print_then_free(void *x) {
	node_t *p=x;
	printf("%4d %4d  %s\n", p->max_match, p->entry, p->data);
	free(p->data);
	free(p);

}



static void
recursive_free_tree(node_t *root) 
{
	if (root) {
		recursive_free_tree(root->left);
		recursive_free_tree(root->rght);
		free(root);
	}
}

/* Release all memory space associated with the tree
   structure. */
void
free_tree(tree_t *tree) 
{
	assert(tree!=NULL);
	recursive_free_tree(tree->root);
	free(tree);
}
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






