/*                   LZ78 Compression Mechanism                 */
/*     Authorship: Shreyash Patodia, Assignment 2, Comp10002    */
/*                      (Alogrithms are fun)                    */
/* Program that compresses a given text file using the LZ-78
   compression mechanism in order to save space
   involved in storing a given text file. 
   The LZ78 mechanism works in the following manner:
   If we have a file containing ab:ab:ab:ab: -> We would get the
   following encoded dictionary of factors:
   a0
   b0
   :0
   b1
   a3
   :2
   :4
   This mechanism becomes more effective as the size of text file
   increases. 
   I use hash tables in order to implement the dictionary
   structure that stores the factors. The functions implementing 
   the operations on the dictionary are taken from the material taught
   in Comp10002 by Alistair Moffat(Semseter 2, 2015) 
   The only difference between the manipulation of the hash table is
   that Alistair's code has bucket elements as strings and mine has
   them to be structures which contain a string and an entry 
   number */
   /* P.S- We create random prime values in the hashing function
      to provide each string a unique bucket in the table which it
      wil be an element of */
   /* P.P.S I use hash tables beause on implementation hash table 
      was found to be faster than my tree and trie for pg2600 */   
/****************************************************************/ 
                       /* Header Files */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <assert.h>

/*******************************************************************/   
                        /* # defines */

#define MALLOC_MSG "memory allocation"
#define REALLOC_MSG "memory reallocation"
/* Messages that indicates where the program failed whether memory
   allocation or reallocation */  

#define FIRST_BUCKET_SIZE 4 /* First size of bucket when it is created */
#define HTAB_DEFAULT 10000  /* Table size */
#define NVALUES 20          /* Number of prime values created for hash 
                               function */
#define INITIAL_STRING_SIZE 128 /* Initial length of string */

/*******************************************************************/


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
	data_t *ptrs;	  /* pointer to array of the data_t structure */
	
}hash_bucket_t; /* Structure for each bucket of the table */

typedef struct 
{
	int table_size;   /* Table size */
	hash_bucket_t *buckets;   /* Pointer to the array of buckets */
	hashfunc_t *hash; /* Hashing function to create unique index */
}hash_table_t; /* Structure for the table itself */

/*******************************************************************/
				   /* Function Prototypes */

char *get_inputs();
void exit_if_null(char *ptr, char *message);

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

/*******************************************************************/
/* Main function is the calling function it calls all the functions 
   that carry out various tasks */
int 
main(int argc, char* argv[])
{
	srand(86421357);
	/* seeding random number */ 

	char *input_file; /* Input file */
	int current_size = 0;  /* size of dictionary */
	hash_table_t *dict;    /* table that forms dictionary */
	int htable_size = HTAB_DEFAULT; /* Setting table size */

	input_file = get_inputs(); /* Getting input file from stdin */

	dict = create_hash_table(htable_size);

	/* Put "" into dictionary as first element */
	dict = encode_first_entry(dict, current_size);
	current_size ++;

	/* Process input files and put factors into dictionary */
	dict = encode_inputs(input_file, dict, current_size);
    free_table(dict);

    /* Ta-Da done */

	return 0;	
}
/*******************************************************************/
/*******************************************************************/

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
/* Function is called when space is allocated to the string,to check
   if memory allocation or reallocation is successful or not,
   it is similar to one of Alistair Moffats programs in class */

/* It takes the ptr to the string and relavent error message as input 
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

	char *initial_phrase;
	initial_phrase = malloc(sizeof(char));
	strcpy(initial_phrase,"");	
	dict = table_insert(dict, initial_phrase, current_size);
	free(initial_phrase);
	return dict;
}

/*******************************************************************/

/* Function that takes the input file, the hash dictionary and the current
   size of the of the dictionary and process dictionary in order to create
   the processed dictionary */
/* P.S - The function is only 30 statements but it looks longer due to 
   white spaces and comments that try to explain it */

hash_table_t
*encode_inputs(char *input_file, hash_table_t *dict, int current_size)
{
	int i, found, phrase_index = 0, max_match = 0; 
	/* phrase_index indicates which index of the current phrase will 
	   the next elemnt of the input file will go into */
	/* max_match is the position of the largest match of the current
	   phrase */

	int len = strlen(input_file); /* length of string */

	char *current_phrase = malloc(sizeof(char)*(strlen(input_file)+1));
	
	for(i=0; i<len ; i++)
	{
		current_phrase[phrase_index] = input_file[i];
		/* putting element into the current phrase */
		current_phrase[phrase_index + 1] = '\0';

		/* Look for a match */
		found = table_search(dict, current_phrase);

		if(!found) /* If no match found insert  current_phrase */
		{
			
			dict = table_insert(dict, current_phrase, current_size);
			printf("%c%d\n", current_phrase[phrase_index], max_match);
			/* printing in given format the mismatch char and 
			   max match */
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
				/* printing in given format the mismatch char and 
			       max match */
				strcpy(current_phrase, "");
				current_size++;
				phrase_index = 0;
				max_match = 0;

			}
			/* I have inserted the last factor into the dictionary but it 
			   would not make a difference even if we didnt insert it into
			   the dictionay */

			else 
			/* else the current phrase is already in the dictionary and
			   try to look for a longer one */
			{
				max_match = found; /*positon of match */
				phrase_index++;   
				/* put next element after present element in current
				   phrase */
			}
		}
	}

	/* Printing the stderr to show the bytes encoded and factorsc
	   processed */
	fflush(stdout);
    fprintf(stderr, "encode: %6d bytes input\n", len);
    fprintf(stderr, "encode: %6d factors generated\n", current_size-1);

    /* current_size-1 since the first factor is "" and we don't consider
       it according to Alistair's output */

    return dict;

}

/*******************************************************************/
/*******************************************************************/

/* Function creates a empty hash table, it takes in the size of the hash
   table, which is assigned in maim, it reutrns the empty hash table */

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

/* Following function is the same as Alistair Moffat's with the only
   difference being that I store the key in the string called 
   phrase which is an element of the struct which is the element
   of each bucket and thus compare with the phrase */

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
		/* ptrs[] is the array of elements in the bucket */
		assert(p->ptrs[i].phrase);
		/* Only check if there is a phrase in ptrs[i] */

		if(strcmp(key, p->ptrs[i].phrase)==0)
		{
			return p->ptrs[i].entry;
			/* Return the entry number if match is found */ 
		}

	}
	return 0;
}

/*******************************************************************/
/*******************************************************************/

/* Following function is the same as Alistair Moffat's with the only
    difference being that I store the key in the string called 
    phrase which is an element of the struct which is the element
    of each bucket */

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
		/* ptrs is pointer to the array of data_t */
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
		p = dict->buckets + i; /* p is current bucket */
		if(p->ptrs)
		{
			for(j=0; j<p->bucket_size; j++)
			{
				/* p->ptrs[] is the array of the structure data_t */
				/* free pointer to phrase of p[i] if it is allocated */
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

/* Function takes the tabsize as input and returns the pointer to the
   hash function */

hashfunc_t
*hash_func_create(unsigned tabsize)
{
	int i;
	hashfunc_t *h; /* h is the pointer to the hash function */

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

	/* Generating index for key */
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
/*                  The End                                        */
/* Thats all for Comp10002 folks, see you next year in design of
   algorithms because algorithms are fun */


