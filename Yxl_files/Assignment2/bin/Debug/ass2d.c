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

/* this main program and the loop it contains is probably just a little
   long for comfort, and you need to understand that I'm allowed to break
   the rules, and you are not :-) */

int
main(int argc, char *argv[]) {

	decoder_t *D=NULL;	/* pointer to decoding table */
	int current_size=0;	/* current decode table capacity */
	int nstrings=0;		/* current decode table actual size */
	char extension;		/* one extension character */
	int copystring;		/* index of the string it builds on */
	char dummybyte;		/* reads the newline at end of each line */

	int i_bits=0, o_bytes=0;
				/* count of input bits (estimated) and
				   output bytes (exact) */

	/* create initial decode array */
	D = (decoder_t*)malloc(INITSIZE*sizeof(*D));
	current_size = INITSIZE;
	assert(D);

	/* and insert the first string, the empty string */
	D[0].extension = '\0';
	D[0].copystring = 0;
	nstrings = 1;

	/* now process extension,copystring pairs from the input */
	while ((extension=getchar()) != EOF) {
		/* have got the extension character, so there really
		   should be a matching copystring value and then a 
		   newline */
		assert(scanf("%d%c", &copystring, &dummybyte)==2);
		assert(copystring>=0 && copystring<=nstrings);
#if DEBUG
		printf("DB: extension = %c, copystring = %d\n",
			extension, copystring);
#endif
		/* check if decode array has enough space */
		if (nstrings==current_size) {
			/* and if not, extend it */
			current_size *= MULTIPLY;
			D = (decoder_t*)realloc(D, current_size*sizeof(*D));
			assert(D);
#if DEBUG
			printf("DB: D now %d entries\n", current_size);
#endif
		}

		/* add the new string to the decode array */
		assert(nstrings<current_size);
		D[nstrings].extension = extension;
		D[nstrings].copystring = copystring;
		
		/* and then print out the string it represents,
		   return value indicayes how long it was */
		o_bytes += rec_print(D, nstrings);
		/* and how many bit could the two inputs have fitted in to? */
		i_bits += EXTENSION_BITS + comp_len(nstrings);
#if DEBUG
		printf("\n");
#endif
		/* and finally, now ready to iterate with a new phrase
		   installed in the dictionary */
		nstrings++;
	}

	/* print some final summary statistics to the screen, but first make
	   sure that all of the stdout output has been emitted */
	fflush(stdout);
	fprintf(stderr, "\n");
	fprintf(stderr, "decode: %6d factors processed\n", nstrings-1);
	fprintf(stderr, "decode: %6d bytes output\n", o_bytes);
	fprintf(stderr, "decode: %6d bits = %5d bytes sufficient as input\n",
		i_bits, bits2bytes(i_bits));
	fprintf(stderr, "decode: %6.3f bits/byte achieved by encoder\n",
		1.0*i_bits/o_bytes);

	/* not strictly necessary to do this, but good housekeeping habit */
	free(D);
	D = NULL;
	return 0;
}

/* recursively generate the target string by tracing back through the
   decoding dictionary, appending one character to the previous output
   as the last step in each recursive call */
int
rec_print(decoder_t *D, int strnum) {
	int len;
	if (strnum==0) {
		/* base case for all tracebacks, every string starts with
		   an empty string, and doing nothing will print that... */
		return 0;
	} else {
		/* print the string's prefix by tracing it back */
		len = rec_print(D, D[strnum].copystring);
		/* and then append the last character of the string
		   we were asked for in this call */
		putchar(D[strnum].extension);
		return len+1;
	}
}

/* compute the length in bits of a tailored bit-coded integer in range
   0..nstrings-1. Could call log() and round to the right value, but this
   is also a reasonable way to do it, with
   	1     mapping to 0
	2     mapping to 1
	3-4   mapping to 2
	5-8   mapping to 3
	9-16  mapping to 4
	17-32 mapping to 5
   etc */
int
comp_len(int nstrings) {
	int bitlen=0;
#if DEBUG
	printf("DB: comp_len, nstrings=%d, ", nstrings);
#endif
	while (nstrings>1) {
		nstrings = (nstrings+1)/2;
		bitlen++;
	}
#if DEBUG
	printf(", bitlen=%d\n", bitlen);
#endif
	return bitlen;
}

/* convert size in bits to size in bytes, rounding up */
int
bits2bytes(int nbits) {
	return (nbits+BITS_PER_BYTE-1)/BITS_PER_BYTE;
}
