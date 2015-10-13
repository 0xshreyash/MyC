#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <strings.h>
#include <assert.h>

#define MALLOC_MSG "memory allocation"
#define REALLOC_MSG "memory reallocation"
#define FIRST_SIZE 4
#define HTAB_DEFAULT 10000
#define NVALUES 20

typedef struct
{
	unsigned nvalues; 
	unsigned *values;
	unsigned tabsize;
}hashfunc_t;


typedef struct 
{
	char *phrase; 
	int entry;
	/* data */
}data_t;

typedef struct
{
	int bucket_limit; 
	int bucket_size;
	data_t *ptrs;
	
}hash_bucket_t;



typedef struct 
{
	int table_size;
	hash_bucket_t *buckets;
	hashfunc_t *hash;/* data */
}hash_table_t;



void
free_table(hash_table_t *dict);
char
*get_inputs();
void
exit_if_null(char *ptr, char *message);
hash_table_t
*create_hash_table(int size);
int
table_search(hash_table_t *dict, char *key);
hash_table_t
*table_insert(hash_table_t *dict, char *key, int entry);
unsigned
hash_func_calculate(hashfunc_t *h, char *key);
void 
hash_func_free(hashfunc_t *h);
hashfunc_t
*hash_func_create(unsigned tabsize);
int nextprime(int n);
int isprime(int n);
int string_cmp(void *a, void *b);



int main(int argc, char* argv[])
{
	char *input_file, *current_phrase; 
	input_file = get_inputs();
	hash_table_t *dict;
	int htable_size = HTAB_DEFAULT;
	int size=0;
	unsigned tabsize = 4;
	int i, found, phrase_index = 0, temp = 0;
	int str_len = strlen(input_file);
	 
	current_phrase = malloc(sizeof(char)*(str_len + 1));
	dict = create_hash_table(htable_size);
	strcpy(current_phrase,"");	
	dict = table_insert(dict, current_phrase, size);
	size ++;
	data_t *new;
	for(i=0; input_file[i] !='\0'; i++)
	{
		current_phrase[phrase_index] = input_file[i];
		current_phrase[phrase_index + 1] = '\0';
		found = table_search(dict, current_phrase);
		if(found == 0)
		{
			
			dict = table_insert(dict, current_phrase, size);
			printf("%c%d\n", current_phrase[phrase_index], temp);
			size++;
			strcpy(current_phrase, "");
			phrase_index = 0;
			temp = 0;
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
				temp = found;
				phrase_index++;

			}
		}
	}
	return 0;	
}
/****************************************************************/
/* get_inputs- takes inputs from stdin and returns the input file 
   provided by the user */
char
*get_inputs()
{
	char *input_file, c;
	int n = 0, size = 1000;
	

	input_file = malloc(size);
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
hash_table_t
*create_hash_table(int size)
{
	int i;
	hash_table_t *dict;
	dict = malloc(sizeof(*dict));
	assert(dict);
	dict->table_size = size;
	dict->buckets = malloc(size*sizeof(hash_bucket_t));
	assert(dict->buckets);
	for(i = 0; i<size; i++)
	{
		dict->buckets[i].bucket_size = 0;
		dict->buckets[i].bucket_limit = 0;
		dict->buckets[i].ptrs = NULL;

		
	}
	dict->hash = hash_func_create(size);
	return dict;
}
/*****************************************************************/
int
table_search(hash_table_t *dict, char *key)
{
	int i; 
	unsigned hash;
	hash_bucket_t *p;
	hash = hash_func_calculate(dict->hash, key);
	p = dict->buckets + hash; 
	for(i=0; i<p->bucket_size; i++)
	{
		assert(p->ptrs[i].phrase);
		if(strcmp(key, p->ptrs[i].phrase)==0)
		{
			return p->ptrs[i].entry;
		}

	}
	return 0;
}
/******************************************************************/
hash_table_t
*table_insert(hash_table_t *dict, char *key, int size)
{
	hash_bucket_t *p;
	unsigned hash;

	hash = hash_func_calculate(dict->hash, key);
	p = dict->buckets + hash; 
	if(p->bucket_limit == 0)
	{
		p->bucket_limit = FIRST_SIZE;
		p->ptrs = malloc(p->bucket_limit*sizeof(data_t));
		assert(p->ptrs);
	}
	if(p->bucket_size == p->bucket_limit)
	{
		p->bucket_limit *= p->bucket_size;
		p->ptrs = realloc(p->ptrs, p->bucket_limit*sizeof(data_t));
		assert(p->ptrs);
		p->ptrs->phrase = malloc(strlen(key)+1);
	}
	p->ptrs[p->bucket_size].phrase = malloc(strlen(key)+1);
	p->ptrs[p->bucket_size].phrase = key;
	p->ptrs[p->bucket_size].entry = size;
	p->bucket_size++;
	return dict;
}

/*******************************************************************/
void
free_table(hash_table_t *dict)
{
	hash_bucket_t *p;
	int i, j;
	for(i=0; i<dict->table_size; i++)
	{
		p = dict->buckets +i;
		if(p->ptrs)
		{
			for(j=0; j<p->bucket_size; j++)
			{
				free(p->ptrs[i].phrase);

			}
			free(p->ptrs);
		}
		free(dict->buckets);
		hash_func_free(dict->hash);
		free(dict);
	}
	return;
}
/*******************************************************************/
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
	for(i=0; i<NVALUES; i++)
	{
		h->values[i] = nextprime(tabsize + rand()%tabsize);
	}
	h->tabsize = tabsize; 
	return h;
}
/*******************************************************************/

void 
hash_func_free(hashfunc_t *h)
{
	free(h->values);
	free(h);
	return;
}

/*******************************************************************/

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
	return hval % h->tabsize; 
}

/*******************************************************************/

/*******************************************************************/
