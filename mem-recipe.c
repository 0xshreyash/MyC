type_t *tptr;
     /* figure how big the array needs to be */
     n = ... ;
     /* and ask for the right amount of space */
     tptr = (type_t*)malloc(n*sizeof(*tptr));
     if (!tptr) {
         printf("Error: no memory available\n");
         exit(EXIT_FAILURE);
     }
     /* or */
     assert(tptr);
     /* then */
     do stuff with *tptr and/or tptr[0..n-1]
     /* and finally */
     free(tptr);
     tptr = NULL;
lec07
Structures
Dynamic memory
Lists, stacks, and queues
Trees Dictionaries