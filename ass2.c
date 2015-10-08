#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <strings.h>
#include <ctype.h>


#define MALLOC_MESSAGE "Memory allocation"
#define REALLOC_MESSAGE "Memory reallocation"

typedef struct node node_t;

struct node {
	char *data;              /* data stores the phrase */
	int entry;               /* entry stores the entry number of current phrase */
	node_t *left;            /* left subtree of node */
	node_t *rght;            /* right subtree of node */
};

typedef struct 
{
	node_t *root;            /* root node of the tree, pointer to the very begining 
                              * of the dictionary */
	int (*cmp)(void*,void*); /* function pointer, to the comparison function 
	                          * of the  dictionary */
} dictionary_t;


char* get_inputs();

dictionary_t *make_empty_dictionary(int func(void*,void*));

node_t *initialize_first_node(char *current_phrase);

void *search_dictionary(dictionary_t *dict, void *key);
void *recursive_search_dictionary(node_t*, void*, int(void*,void*));

dictionary_t *insert_in_order(dictionary_t *dict, void *value);
node_t *recursive_insert(node_t*, node_t*, int(void*,void*));

void free_dictionary(dictionary_t *dict);
void recursive_free_dictionary(node_t*);

void traverse_tree(dictionary_t *dict, void action(void*));
void recursive_traverse(node_t*, void action(void*));

int string_cmp(void *a, void *b);

void print_then_free(void *x);


int
main(int argc, char *argv[]) 
{
	char *input_file;
	char *current_phrase;
	char *new_string;
    int i,j,k;
    int count = 1;


	dictionary_t *dict;

	dict = make_empty_dictionary(string_cmp);

	node_t *new, *initial, *locn, *longest_locn;
	input_file = get_inputs();
	
    current_phrase = malloc((strlen(input_file)+1)*sizeof(char));
    strcpy(current_phrase,"\0");

    initial = initialize_first_node(current_phrase);
	dict = insert_in_order(dict, initial);

	strcpy(current_phrase,"Hello\0");
	new = malloc(sizeof(new));
	new->data= current_phrase;
	locn = search_dictionary(dict, new);
	if(!locn)
	{
		new->data = malloc(strlen(current_phrase)+1);
		new->entry = count; 
		count ++;
		dict = insert_in_order(dict, new);
		free(new->data);
		free(new);
	}

	strcpy(current_phrase,"Hi\0");
	new->data= current_phrase;
	locn = search_dictionary(dict, new);
	if(!locn)
	{
		new->data = malloc(strlen(current_phrase)+1);
		new->entry = count; 
		count ++;
		dict = insert_in_order(dict, new);
	}

	strcpy(current_phrase,"Hello\0");
	new->data= current_phrase;
	locn = search_dictionary(dict, new);
	if(!locn)
	{
		new->data = malloc(strlen(current_phrase)+1);
		new->entry = count; 
		count ++;
		dict = insert_in_order(dict, new);
	}

	traverse_tree(dict,print_then_free);
	free_dictionary(dict);

	return 0;
}
void
exit_if_null(void *ptr, char *message) 
{
	if (!ptr) 
	{
		printf("Unexpected null pointer encountered during: %s\n", message);
		exit(EXIT_FAILURE);
	}
}
char
*get_inputs()
{
	char *input_file, c;
	int n = 0, size = 1;
	

	input_file = (char *) malloc(size*sizeof(char *));
	exit_if_null(input_file,MALLOC_MESSAGE);

	while((c=getchar())!=EOF)
	{
		input_file = (char*) realloc(input_file, (size+1)*sizeof(char *));
		exit_if_null(input_file,REALLOC_MESSAGE);
		input_file[n]=c;
		n++;
		size++;
	}
	input_file[n]='\0';
	return input_file;
}

dictionary_t
*make_empty_dictionary(int func(void*,void*))
 {
	dictionary_t *dict;
	dict = malloc(sizeof(*dict));
	assert(dict!=NULL);
	/* initialize tree to empty */
	dict->root = NULL;
	/* and save the supplied function pointer */
	dict->cmp = func;    /* Into the cmp field of the the tree */     
	return dict;
}

/* int
is_empty_tree(tree_t *tree) 
{
	assert(tree!=NULL);
	return tree->root==NULL;
}
*/

void
*search_dictionary(dictionary_t *dict, void *key)
{
	assert(dict!=NULL);
	return recursive_search_dictionary(dict->root, key, dict->cmp);
} /* The interface function that can be called from the other side it in 
     turn calls the recursive function */

void
*recursive_search_dictionary(node_t *root,
		void *key, int cmp(void*,void*))
{
	int outcome;
	if (!root)
	{
		return NULL; /* Return null if there is no root */
	}
	if ((outcome=cmp(key, root->data)) < 0)
	{
		return recursive_search_dictionary(root->left, key, cmp);
	}
	else if (outcome > 0)
	{
		return recursive_search_dictionary(root->rght, key, cmp);
	}
	else 
	{
		/* must have found it! */
		return root->data; 
	}
}

node_t
*initialize_first_node(char *current_phrase)
{
	node_t *initial;
	initial = malloc(sizeof(*initial));
	initial->data = current_phrase;
	initial->entry = 0;
	return initial;
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

dictionary_t
*insert_in_order(dictionary_t *dict, void *phrase) 
{
	node_t *new;
	static int ent = 1;
	/* make the new node */
	new = malloc(sizeof(*new));
	assert(dict!=NULL && new!=NULL);
	new->data = phrase;
	new->entry = ent;
	ent++;
	new->left = new->rght = NULL; /* Multiple assignment statements together */
	/* and insert it into the tree */
	dict->root = recursive_insert(dict->root, new, dict->cmp); /* All three are pointers */
	return dict;
}

node_t
*recursive_insert(node_t *root, node_t *new,
		int cmp(void*,void*))
{
	if (root==NULL) {
		return new;
	} else if (cmp(new->data, root->data) < 0) {
		root->left = recursive_insert(root->left, new, cmp);
	} else {
		root->rght = recursive_insert(root->rght, new, cmp);
	}
	return root;
}


void
recursive_traverse(node_t *root, void action(void*)) {
	if (root) {
		recursive_traverse(root->left, action);
		action(root->data);
		recursive_traverse(root->rght, action);
	}
}

/* Applies the "action" at every node in the tree, in
   the order determined by the cmp function. */
void
traverse_tree(dictionary_t *dict, void action(void*)) {
	assert(dict!=NULL);
	recursive_traverse(dict->root, action);
}
void
print_then_free(void *x) {
	node_t *p=x;
	printf("%s %d\n", p->data, p->entry);
	free(p->data);
	free(p);
}
void
free_dictionary(dictionary_t *dict) {
	assert(dict!=NULL);
	recursive_free_dictionary(dict->root);
	free(dict);
}
void
recursive_free_dictionary(node_t *root) 
{
	 if(root) 
	 {
		recursive_free_dictionary(root->left);
		recursive_free_dictionary(root->rght);
		free((void *)root);
	 }
}














