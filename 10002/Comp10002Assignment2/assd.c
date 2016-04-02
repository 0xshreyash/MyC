/* Decoding program for LZ78-style compression regime. Input is a text
   file, with each line composed of two components:
   	-- a single character, the "extension"
	-- a single integer, the "copystring"
   Lines are terminated by a newline, and have no other content.
   In particular, the extension is always the first character in
   the line, and the integer copystring always starts in character
   two of the line through until the terminating newline.  The first
   copystring must always be 0, thereafter, the copystring must
   always be less than or equal to the current line number in the
   file.

   For example,
   	a0
	b0
	b1
	b2
	a2
   is a valid input sequence, and represents the original text "ababbbba".

   Written by Alistair Moffat, ammoffat@unimelb.edu.au, September 2015,
   as part of a comp10002 programming assignment (students to write the
   corresponding encoder program, see the handout).
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* generate additional output while debugging */
#define DEBUG 0

/* initial size of dictionary of strings */
#define	INITSIZE 10

/* growth rate on dictionary of strings */
#define MULTIPLY 2

/* number of bits needed for a single printable ASCII character */
#define EXTENSION_BITS 7

/* number of bits in a standard byte */
#define BITS_PER_BYTE 8

/* struct used in decoder, with character values stored as an int */
typedef struct {
	int copystring;
	int extension;
} decoder_t;

/* functions used */
int rec_print(decoder_t *D, int strnum);
int comp_len(int x);
int bits2bytes(int nbits);
