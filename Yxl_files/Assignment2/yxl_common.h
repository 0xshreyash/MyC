/*
Author: Xiaoliang Yu
Create time: 10/10/2015
*/

//Libraries
#include <stdlib.h>
#include <stdbool.h>

/****************************************************************/
//Macro Definitions


/****************************************************************/
//Function Prototypes

void strtolower(const char src[], char *dest);
void Str_AlphanumericOnly(const char src[], char *dest);
int IsEmpty(const char str[]);
bool IsNullTerminated(const char str[], size_t size_str);
void *trymalloc(size_t size_var);
void *tryrealloc(void *ptr, size_t size_var);
void exit_with_error(const char str_err[]);
