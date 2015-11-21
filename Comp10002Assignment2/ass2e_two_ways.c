/****************************************************************/ 
                        /* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

/****************************************************************/

/* Common to both implementations */
#define MALLOC_MSG "memory allocation"
#define REALLOC_MSG "memory reallocation"
/* Messages that indicate macclocing and reallocing have 
 * been unsuccessful */
#define INITIAL_INPUT_SIZE 128
/* Initial size of the variable assigned to take input */ 

/*********************************/
/* Specific to hash tables */

#define FIRST_BUCKET_SIZE 4 /* First size of bucket when it is created  */
#define HTAB_DEFAULT 10000  /* Table size */
#define NVALUES 20          /* Number of prime values created for hash 
                               function */
      
/*********************************/
/****************************************************************/
                    /* Typedef of structures */
 
/*********************************/
/* For BST */
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

/*********************************/
/* For hash tables */

typedef struct
{
	unsigned nvalues; /* No. of prime values generated */
	unsigned *values; /* Array that stores prime values */
	unsigned tabsize; /* table size */

}hashfunc_t; /* Structure for the hashing function */

typedef struct 
{
	char *phrase; /* The string stored as a factor or phrase */
	int entry;	  /* The entry number of factors into the table */
	
}data_t;  /* Struvture that stores the data in each element of the 
             bucket */

typedef struct
{
	int bucket_limit; /* Max size of the bucket */
	int bucket_size;  /* Current size of bucket */
	data_t *ptrs;	  /* Pointer to the data structure */
	
}hash_bucket_t; /* Structure for each bucket of the table */

typedef struct 
{
	int table_size;   /* Table size */
	hash_bucket_t *buckets;   /* Pointer to the array of buckets */
	hashfunc_t *hash; /* Hashing function to create key */
}hash_table_t; /* Structure for the table itself */

/*********************************/

/****************************************************************/
	/* prototypes for the functions in this program */

/*********************************/
             /* Common to both implementations */
char *get_inputs();
void exit_if_null(char *ptr, char *message); 

/*********************************/

     /* Function prototypes for binary search tree */

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



node_t *initialize_first_node(char *current_phrase, int dict_size);
node_t *assign_node_values(char *current_phrase, node_t *new, 
	                       int dict_size);

void encode_dictionary(dictionary_t *dictionary, char *input_file, 
	                   int dict_size);
int string_cmp(void *a, void *b);

/**********************************/

         /* Function prototypes for hash tables*/
 /* Most functions are the same as Alistair's hash table implmentation
    apart from the fact that each element of my buckets is a struct 
    that stores a string and an entry number and Alistair's only 
    stored a string */
hash_table_t *create_hash_table(int size);
int table_search(hash_table_t *dict, char *key);
hash_table_t *table_insert(hash_table_t *dict, char *key, int entry);


int isprime(int n);
int nextprime(int n);
hashfunc_t *hash_func_create(unsigned tabsize);
unsigned hash_func_calculate(hashfunc_t *h, char *key);

int string_cmp(void *a, void *b);
void printf_dict(hash_table_t *dict);
hash_table_t *encode_first_entry(hash_table_t *dict, int current_size);
hash_table_t *encode_inputs(char *input_file, hash_table_t *dict, 
	                        int current_size);

void  hash_func_free(hashfunc_t *h);
void free_table(hash_table_t *dict);

/****************************************************************/
/*******************************************************************/
/* Main function is the calling function it calls all the functions 
   carry out various tasks */
int main(int argc, char* argv[])
{
	srand(8645222);
	/* seeding random number */ 
	char *input_file;
	int current_size = 0;
	hash_table_t *dict;
	int htable_size = HTAB_DEFAULT;

	input_file = get_inputs(); /* Getting input file from stdin */

	dict = create_hash_table(htable_size);

	/* Put "" into dictionary as first element */
	dict = encode_first_entry(dict, current_size);
	current_size ++;

	/* Process input files and put factors into dictionary */
	dict = encode_inputs(input_file, dict, current_size);
    free_table(dict);
	return 0;	
}

/*******************************************************************/
/*******************************************************************/
             /* Common to both Implementations */
/* get_inputs- takes inputs from stdin and returns the input file 
   provided by the user */

char
*get_inputs()
{
	char *input_file, c;
	int n = 0, size = INITIAL_STRING_SIZE;
	

	input_file = malloc(size);
	exit_if_null(input_file,MALLOC_MSG);

	while((c=getchar())!=EOF)
	{
		
		input_file[n]=c;
		n++;
		if(n == size) /* Checking if the max length of input_file
		                 is reached and then doubling size if it
		                 is */
		{ 
			input_file = realloc(input_file, 2*n);
			size = 2*n;
		}
		
	}
	input_file[n]='\0';  /* Inserting null byte at the end */
	return input_file;
}

/*******************************************************************/
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
/*******************************************************************/
/*******************************************************************/

/* Function that takes the empty dictionary and the current size of
   the dictionary in order to implement a "" into the dictionary */
hash_table_t 
*encode_first_entry(hash_table_t *dict, int current_size)
{
	;
	char *initial_phrase;
	initial_phrase = malloc(sizeof(char));
	strcpy(initial_phrase,"");	
	dict = table_insert(dict, initial_phrase, current_size);
	return dict;
}

/*******************************************************************/

/* Function that takes the input file, the hash dictionary and the current
   size of the of the dictionary and process dictionary in order to create
   the processed dictionary */
hash_table_t
*encode_inputs(char *input_file, hash_table_t *dict, int current_size)
{
	int i, found, phrase_index = 0, max_match = 0;
	int len = strlen(input_file);
	char *current_phrase = malloc(sizeof(char)*(strlen(input_file)+1));
	
	for(i=0; i<len ; i++)
	{
		current_phrase[phrase_index] = input_file[i];
		current_phrase[phrase_index + 1] = '\0';
		found = table_search(dict, current_phrase);

		if(!found) /* If no match found insert  current_phrase */
		{
			
			dict = table_insert(dict, current_phrase, current_size);
			printf("%c%d\n", current_phrase[phrase_index], max_match);
			current_size++;
			strcpy(current_phrase, "");
			phrase_index = 0;
			max_match = 0;
		}
		else
		{
			if(input_file[i+1] == '\0')
			/* If a match is found but the next element is a null in the 
			   string then don't look for a bigger match than the match 
			   with the penultimate element */
			{
				
				dict = table_insert(dict, current_phrase, current_size);
				printf("%c%d\n", current_phrase[phrase_index], max_match);
				strcpy(current_phrase, "");
				current_size++;
				phrase_index = 0;
				max_match = 0;

			}
			/* I have inserted the last factor into the dictionary but it 
			   would not make a difference even if we didnt insert it into
			   the dictionay */

			else /* else the entry of locn is the largest match, continue*/
			{
				max_match = found;
				phrase_index++;
			}
		}
	}

	fflush(stdout);
    fprintf(stderr, "encode: %6d bytes input\n", len);
    fprintf(stderr, "encode: %6d factors generated\n", current_size-1);

    /* current_size-1 since the first factor is "" and we don't consider
       it accrding to Alistair's output */

    return dict;

}

/*******************************************************************/

/* Function creates a empty hash table, it takes in the size of the hash
   table, which is assigned in maim, it reutrns the empty hash table
 */

hash_table_t
*create_hash_table(int size)
{
	int i;
	hash_table_t *dict;

	dict = malloc(sizeof(*dict));
	assert(dict);

	dict->table_size = size;
	/* Assigning table size */

	dict->buckets = malloc(size*sizeof(hash_bucket_t));
	assert(dict->buckets);

	for(i = 0; i<size; i++)
	{
		dict->buckets[i].bucket_size = 0;
		dict->buckets[i].bucket_limit = 0;
		dict->buckets[i].ptrs = NULL;	
	}
	/* Initializes each bucket */

	dict->hash = hash_func_create(size);
	/* creates the hash function */

	return dict;
}
/*******************************************************************/
/*******************************************************************/

/* Function takes pointer to the hash table and the character to be 
   searched for as input and returns the location of the found item
   or else returns zero */

int
table_search(hash_table_t *dict, char *key)
{
	int i; 
	unsigned hash;
	hash_bucket_t *p;
	hash = hash_func_calculate(dict->hash, key);
	/* calculates the index of where element should be */

	p = dict->buckets + hash; /* The bucket the element should be in */

	for(i=0; i<p->bucket_size; i++)
	{
		assert(p->ptrs[i].phrase);
		/* Only check if there is a phrase in ptrs[i] */

		if(strcmp(key, p->ptrs[i].phrase)==0)
		{
			return p->ptrs[i].entry;
			/* Reutrn the entry number if match is found */ 
		}

	}
	return 0;
}
/*******************************************************************/
/*******************************************************************/

/* Function takes the hash table, key to be inserted and the size of 
   the dictionary as input and return the dictionary with the key
   inserted */

hash_table_t
*table_insert(hash_table_t *dict, char *key, int size)
{
	hash_bucket_t *p;
	unsigned hash;

	hash = hash_func_calculate(dict->hash, key);
	/* hash is the unique hash index for key */

	p = dict->buckets + hash; 
	/* p points to  which bucket the key should go in */

	/* if bucket does not exist create it */
	if(p->bucket_limit == 0)
	{
		p->bucket_limit = FIRST_BUCKET_SIZE;
		p->ptrs = malloc(p->bucket_limit*sizeof(data_t));
		assert(p->ptrs);
	}

	/* If buckt reaches its limit change limit to twice its
	    previous value */
	if(p->bucket_size == p->bucket_limit)
	{
		p->bucket_limit *= p->bucket_size;
		p->ptrs = realloc(p->ptrs, p->bucket_limit*sizeof(data_t));
		assert(p->ptrs);
	}

	p->ptrs[p->bucket_size].phrase = malloc(strlen(key)+1);
	strncpy(p->ptrs[p->bucket_size].phrase, key, strlen(key) + 1);
	/* put key into the phrase of the last element of the bucket */

	p->ptrs[p->bucket_size].entry = size;
	/* Record which entry of the table the phrase is */
	
	p->bucket_size++;
	return dict;
}

/*******************************************************************/
/*******************************************************************/

 /* Following functions free the memory allocated by the program and
    is the same as Alistair's functions for freeing apart from the 
    fact that I have a struct instead of a string as my data_t in each
    function so we free both the pointer to the data_t as well as the 
    string associated with the data_t */
/*******************************************************************/

 /* free_table takes the dictionary as input and frees it */   
void
free_table(hash_table_t *dict)
{
	hash_bucket_t *p;
	int i, j;
	for(i=0; i<dict->table_size; i++)
	{
		p = dict->buckets + i;
		if(p->ptrs)
		{
			for(j=0; j<p->bucket_size; j++)
			{

				/* free pointervto phrase of p[i] if it is allocated */
				if(p->ptrs[j].phrase)
				{
					free(p->ptrs[j].phrase);
				}
			}
			/* free pointer to ptrs */
			free(p->ptrs);
		}
	}

	free(dict->buckets);
	hash_func_free(dict->hash);
	free(dict);
	return;
}

/*******************************************************************/
/* Function takes pointer to hash function and frees the nvalues 
   pointer and the pointer to the function itself */
void 
hash_func_free(hashfunc_t *h)
{
	free(h->values);
	free(h);
	return;
}

/*******************************************************************/
/*******************************************************************/

/* This part contains the functions associated with hashing 
   function, it is the same as Alistair Moffat's creation 
   of the hashing function. */ 

/*******************************************************************/

/* 	Function takes a number as input and checks whether it is 
	prime or not, return 1 if it is prime, 0 if it is not. */

int isprime(int n)
{
	int divisor;
	if(n<2)
	{
		return 0;	
	}
	for(divisor=2; divisor*divisor<n; divisor++)
	{
		if(n%divisor == 0)
		{
			return 0;
		}
	}
	return 1;
}

/*******************************************************************/

/* Function that takes a number as input, uses isprime function to
   find the next prime number and returns it */

int nextprime(int n)
{
	n = n+1;
	while(!isprime(n))
	{
		n = n+1;
	}
	return n;
}

/*******************************************************************/

/* Function takes the table size as input and returns the pointer to
   the hash function */

hashfunc_t
*hash_func_create(unsigned tabsize)
{
	int i;
	hashfunc_t *h;

	h = malloc(sizeof(*h));
	assert(h!=NULL);

	h->values = malloc(NVALUES*sizeof(*(h->values)));
	assert(h->values != NULL);

	h->nvalues = NVALUES;
	/* Initializing table elements */

	for(i=0; i<NVALUES; i++)
	{
		h->values[i] = nextprime(tabsize + rand()%tabsize);
	}
	/* Finds  NVALUES prime numbers and puts it into the 
	   values array in the hash function */
	h->tabsize = tabsize; 
	return h;
}

/*******************************************************************/

/* Functions that takes a string called key and pointer to the hashing
   function as input and returns the position generated using the hash
   function and the charactera in the key */

unsigned
hash_func_calculate(hashfunc_t *h, char *key)
{
	unsigned i, k=0, hval=0;
	for(i=0; key[i]!='\0';i++)
	{
		hval = hval + key[i] * h->values[k];
		k++;
		if(k==NVALUES)
		{
			k=0;
		}
	}
	/* Using Alistair's hashing method to give unique index to the 
	   key */
	return hval % h->tabsize; 
}

/*******************************************************************/
/*******************************************************************/







