/*
Author: Xiaoliang Yu
Create time: 10/10/2015
*/

//Libraries
#include <stdlib.h>

/****************************************************************/
//Macro Definitions


/****************************************************************/
//Function Prototypes

void strtolower(const char src[const], char * const dest);
void Str_AlphanumericOnly(const char src[const], char * const dest);
int IsEmpty(const char str[const]);
int IsNullTerminated(const char str[const], const size_t size_str);
void *trymalloc(size_t size_var);
void *tryrealloc(void * const ptr, size_t size_var);
void exit_with_error(const char str_err[const]);
