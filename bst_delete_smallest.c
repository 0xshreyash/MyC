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
/* Messages that indicate macclocing and reallocing have 
 * been unsuccessful */
#define INITIAL_INPUT_SIZE 128
/* Initial size of the variable assigned to take input */   

/****************************************************************/
                    /* Typedef of structures */
 
typedef struct node node_t;  /* node_t - Each node of the dictionary */

struct node 
{
	void *data; 	         /* String or phrase stored in the node */
	int entry;            	 /* Entry number of each string into 
							  * the dictionary */	
	node_t *left;            /* left subdictionary of node */
	node_t *rght;            /* right subdictionary of node */
};

typedef struct 
{
	node_t *root;            /* root node of the dictionary, 
                              * pointer to the very begining 
	                          * of the dictionary */
	int (*cmp)(void*,void*); /* function pointer, 
                              * to the comparison function 
	                          * of the dictionary */
} dictionary_t;

/****************************************************************/

     /* prototypes for the functions in this program */

       /*****************************************/
    /* Alistair Moffats's treeops function declarations */
    /* I have not made any changes apart from changing  */
           /* tree to dictionary for my program */

dictionary_t *make_empty_dictionary(int func(void*,void*));

void *search_dictionary(dictionary_t *dictionary, void *key);
dictionary_t *insert_in_order(dictionary_t *dictionary, void *value);
void free_dictionary(dictionary_t *dictionary);

static void *recursive_search_dictionary(node_t*, void*,
		int(void*,void*));
static node_t *recursive_insert(node_t*, node_t*,
		int(void*,void*));
static void recursive_free_dictionary(node_t*);

       /*****************************************/
  /* functions made for this program to supplement treeops */


void exit_if_null(char *ptr, char *message); 

node_t *initialize_first_node(char *current_phrase, int dict_size);
node_t *assign_node_values(char *current_phrase, node_t *new, 
	                       int dict_size);

void encode_dictionary(dictionary_t *dictionary, char *input_file, 
	                   int dict_size);
int string_cmp(void *a, void *b);

/****************************************************************/
/* main function- control centre of the program to creates the dictionary
   takes inputs and create the dictionary */
int
main(int argc, char *argv[])
{
	char *input_file;          /* Input string from stdin */
	node_t *initial;           /* First node or root of dictionary tree */
	dictionary_t *dictionary;  /* Our dictionary of phrases */ 
	char c, *locn; 
	int i;

	int dict_size =0;
	int n = 0, input_size = INITIAL_INPUT_SIZE;

	input_file =  malloc(input_size);
	exit_if_null(input_file,MALLOC_MSG);

	dictionary = make_empty_dictionary(string_cmp);
	node_t *new; char *found;

	while((c=getchar())!=EOF)
	{
		
		input_file[n]=c;
		n++;
		if(input_file[n]=='\n')
		{
			input_file[n]='\0';
			new = malloc(sizeof(*new));
			new->data = input_file;
			found = search_dictionary(dictionary, new);
			if(!found)
			{
				new->data = malloc(sizeof(input_file)+1);
			    new->entry = dict_size++;
				dictionary = insert_in_order(dictionary, new);

			}
			n = 0;
		}
		if(n == input_size) /* Checking if the max length of input_file
		                       is reached and then doubling size if it
		                       is */
		{
			input_file = realloc(input_file, 2*n);
			input_size = 2*n;
		}
		
	}

	input_file[n]='\0'; 


	/* Ta-da dictionary done */

}

/****************************************************************/
/* get_inputs- takes inputs from stdin and returns the input file 
   provided by the user in the variable input_file */


/****************************************************************/
/* Function is called to check if space has been allocated to the 
   string,takes the ptr to the string and relavent error message 
   as input arguments and exits program if memory 
   allocation/reallocation is unsuccessful */
void
exit_if_null(char *ptr, char *message) 
{
	if (!ptr) 
	{
		printf("Unexpected null pointer encountered during: %s\n", message);
		exit(EXIT_FAILURE);
	}

	return;
}

/****************************************************************/
/* The functions takes two void pointers, converts them to a type node_t
   and then compares the strings associated with the nodes and returns the
   strcmp value of x->data, y->data */

int
string_cmp(void *a, void *b)
{
	node_t *x = a, *y = b;

	return strcmp(x->data,y->data);
}

/****************************************************************/
/* Function takes the a pointer to the first phrase and dict_size of 
   as argument and initializes the first node as a "" string 
   ready to be inserted */

node_t
*initialize_first_node(char *first_phrase, int dict_size)
{
	node_t *initial; 
	initial = malloc(sizeof(*initial));
	assert(initial!=NULL);

	initial->data = malloc(strlen(first_phrase)+1);
	assert(initial->data!=NULL);

	strcpy(initial->data, first_phrase); 
	initial->entry = dict_size;
	return initial;

}

/****************************************************************/
/* Function takes the dictionary, input file and the current size of the 
   dictionary as arguments and encodes the dictionary according to the LV78 
   compression technique */
/* P.S. - The function is only 30 odd statements it looks big because of the
   spaces and large comments */   
void
encode_dictionary(dictionary_t *dictionary, char *input_file, int dict_size)
{
	int i = 0, phrase_index = 0, max_match = 0, len = strlen(input_file);

	node_t *new, *locn;
	/* max_match is the position or entry number of the longest phrase
	   that the current_phrase matches with */
	/* locn is a pointer to the node with the longest string match
	   of the current_phrase */

	char *current_phrase; 
	current_phrase = malloc((strlen(input_file)+1)*sizeof(char));

	for(i=0; i<len; i++)
	{
		new = malloc(sizeof(*new));
		current_phrase[phrase_index] = input_file[i];
		current_phrase[phrase_index + 1] = '\0';
		new->data = current_phrase;
		locn = search_dictionary(dictionary, new); /* Searching dictionary */

		if(!locn) /* If no match found insert  current_phrase */
		{
			new = assign_node_values(current_phrase, new, dict_size);
			dictionary = insert_in_order(dictionary, new); 
			printf("%c%d\n", current_phrase[phrase_index], max_match);

			strcpy(current_phrase, "");
			phrase_index = 0;
			max_match = 0;
			dict_size++;	
		}
		else
		{
			if(input_file[i+1] == '\0')
			/* If a match is found but the next element is a null in the 
			   string then don't look for a bigger match than the match 
			   with the penultimate element */
			{
				new = assign_node_values(current_phrase, new, dict_size);
				dictionary = insert_in_order(dictionary, new); 
				printf("%c%d\n", current_phrase[phrase_index], max_match);
				strcpy(current_phrase, "");
				phrase_index = 0;
				max_match = 0;
				dict_size++;
			}
			/* I have inserted the last factor into the dictionary but it 
			   would not make a difference even if we didnt insert it into
			   the dictionay */

			else /* else the entry of locn is the largest match, continue*/
			{
				max_match = locn->entry;
				phrase_index++;
			}	
		}
	}

	/* Printing the encoded message through stderr */

	fflush(stdout);
    fprintf(stderr, "encode: %6d bytes input\n", len);
    fprintf(stderr, "encode: %6d factors generated\n", dict_size-1);
    /* dict_size-1, since the first factor is "" and we don't consider
       it according to Alistair's output */
	free(current_phrase);
	return; 
}

/****************************************************************/
/* Function that assigns to node_t new the current_phrase and the
   size of the dictionary. Input arguments are the node_t new, 
   current_phrase and the dictionary size. Output is the prepared
   node */

node_t
*assign_node_values(char *current_phrase, node_t *new, int dict_size)
{
	new->data = malloc(strlen(current_phrase)+1);
	strcpy(new->data, current_phrase);
	new->entry = dict_size;
	return new;
}

/****************************************************************/
         /******* Alistair's treeops module **********/ 
/* I have modified the recursive free function to free the pointers
   to the phrases as well */

/* Function that makes empty dictionary, takes pointer to comparison
   function as input arguments and outputs the empty dictionary */

dictionary_t
*make_empty_dictionary(int func(void*,void*)) 
{
	dictionary_t *dictionary;
	dictionary = malloc(sizeof(*dictionary));
	assert(dictionary!=NULL);
	/* initialize dictionary to empty */
	dictionary->root = NULL;
	/* and save the supplied function pointer */
	dictionary->cmp = func;    /* Into the cmp field of the the 
	                              dictionary */     
	return dictionary;
}

/****************************************************************/
/* Function that takes the root node, key to be searched for and 
   comparison function and recusrively searches for the key */
static void
*recursive_search_dictionary(node_t *root,
		void *key, int cmp(void*,void*)) 
{
	int outcome;
	if (!root) {
		return NULL; /* Return null if there is no root */
	}
	if ((outcome=cmp(key, root->data)) < 0) {
		return recursive_search_dictionary(root->left, key, cmp);
	} else if (outcome > 0) {
		return recursive_search_dictionary(root->rght, key, cmp);
	} else {
		/* hey, must have found it! */
		return root; 
	}
}

/****************************************************************/

/* Returns a pointer to the dictionary node storing object "key",
   if it exists, otherwise returns a NULL pointer.
   Takes dictionary and key to be searched for as input */
void
*search_dictionary(dictionary_t *dictionary, void *key) 
{
	assert(dictionary!=NULL);
	return recursive_search_dictionary(dictionary->root, key,
	                                   dictionary->cmp);
} 

/****************************************************************/

/* Returns a pointer to an altered dictionary that now includes
   the object "value" in its correct location.
   Takes dictionry and value to be inserted as input */
dictionary_t
*insert_in_order(dictionary_t *dictionary, void *value) 
{
	node_t *new;
	/* make the new node */
	new = malloc(sizeof(*new));
	assert(dictionary!=NULL && new!=NULL);
	new->data = value;
	new->left = new->rght = NULL; 
	/* and insert it into the dictionary */
	dictionary->root = recursive_insert(dictionary->root, new,
		dictionary->cmp); /* All three are pointers */
	return dictionary;
}

/****************************************************************/
/* Takes root of the dictionary, the new node to be inserted and the 
   comparison function and looks for the the current position 
   recursively */ 
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

/* Function takes root of dictionary and recursively frees the 
   dictionary*/
static void
recursive_free_dictionary(node_t *root) 
{
	if (root) {
		recursive_free_dictionary(root->left);
		recursive_free_dictionary(root->rght);
		free(root->data);
		free(root);
	}
}

/****************************************************************/

/* Release all memory space associated with the dictionary
   structure. 
   Takes dictionary as input in order to free it by calling
   recursive free tree */
void
free_dictionary(dictionary_t *dictionary) 
{
	assert(dictionary!=NULL);
	recursive_free_dictionary(dictionary->root);
	free(dictionary);
}

/****************************************************************/         
/* The End */  
/* That's all for Comp10002 folks, see you when we design algorithms,
   because algorithms are fun */       






