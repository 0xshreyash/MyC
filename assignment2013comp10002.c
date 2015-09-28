/* Extended precision integer calculator program
 * Implements + and * operations
 *
 * Sample solution written by Alistair Moffat, October 2013
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#define INTSIZE	100	/* max number of digits per integer value */
#define LINELEN	102	/* maximum length of any input line */
#define NVARS	26	/* number of different variables */

#define CH_BLANK ' '    /* character blank */
#define CH_ZERO  '0'    /* character zero */
#define CH_ONE   '1'    /* character one */
#define CH_NINE  '9'    /* character nine */
#define CH_A     'a'    /* character 'a', first variable name */
#define CH_PL    '+'    /* character '+' */
#define CH_NE    '-'    /* character '-' */
#define CH_COM   ','    /* character ',' */

#define INT_TEN  10	/* integer 10 */

#define ERROR	(-1)	/* error return value from some functions */

#define PRINT	'?'	/* the print operator */
#define ASSIGN	'='	/* the assignment operator */
#define PLUS	'+'	/* the addition operator */
#define MULT	'*'	/* the multiplication operator */
#define POWER	'^'	/* the power-of operator */
#define ALLOPS  "?=+*^" /* list of all valid operators */
#define SGNCHRS "+-"    /* the two sign characters */
#define NUMCHRS ",0123456789"
			/* list of characters legal within numbers */
#define POSI	0	/* indication of positive number */

typedef struct {
	int nega;	/* zero for positive, non-zero for negative */
	int ndig;
	char digs[INTSIZE];
} longint_t;
			/* one extended-precision "variable" */

#define LONG_ZERO {0,POSI,{0}}
			/* and an initializer for variables that are zero */

/****************************************************************/

/* function prototypes */

char add_to_digit(char d1, int val, int *carry);
void do_assign(longint_t *var1, longint_t *var2);
void do_mult(longint_t *var1, longint_t *var2);
void do_plus(longint_t *var1, longint_t *var2);
void do_power(longint_t *var1, longint_t *var2);
void do_print(longint_t *var);
int get_second_value(longint_t vars[], char *rhsarg, longint_t *second_value);
int mag_cmp(longint_t *var1, longint_t *var2);
void mult_one_digit(longint_t *var, int digit);
void mult_ten(longint_t *var);
void overflow_abort(void);
longint_t parse_num(char *rhs);
void print_prompt(void);
void process_line(longint_t vars[], char *line);
int read_line(char *line, int maxlen);
void simple_plus(longint_t *var1, longint_t *var2);
void simple_suba(longint_t *var1, longint_t *var2);
char sub_digit(char d1, int val, int *borrow);
char to_digit(int number);
int to_int(char digit);
int to_varnum(char ident);
void zero_vars(longint_t vars[]);

/****************************************************************/

/* main program controls all the action
 */

int
main(int argc, char **argv) {
	char line[LINELEN+1];
	longint_t vars[NVARS];

	zero_vars(vars);
	print_prompt();
	while (read_line(line, LINELEN)) {
		if (strlen(line)>0) {
			/* non empty line, so process it */
			process_line(vars, line);
		}
		print_prompt();
	}

	/* all done, so pack up and go home */
	printf("\n");
	return 0;
}

/****************************************************************/

/* prints the prompt indicating ready for input
 */

void
print_prompt(void) {
	printf("> ");
}

/****************************************************************/

/* read a line of input into the array passed as argument
 * returns false if there is no input available
 * all whitespace characters are removed
 */

int
read_line(char *line, int maxlen) {
	int i=0, c;
	while (((c=getchar())!=EOF) && (c!='\n')) {
		if (i<maxlen && !isspace(c)) {
			line[i++] = c;
		}
	}
	line[i] = '\0';
	return ((i>0) || (c!=EOF));
}

/****************************************************************/

/* process a command by parsing the input line into parts
 */

void
process_line(longint_t vars[], char *line) {
	int varnum, optype, status;
	longint_t second_value;

	/* determine the LHS variable, it
	 * must be first character in line
	 */
	varnum = to_varnum(line[0]);
	if (varnum==ERROR) {
		printf("Invalid LHS variable\n");
		return;
	}

	/* more testing for validity 
	 */
	if (strlen(line)<2) {
		printf("No operator supplied\n");
		return;
	}

	/* determine the operation to be performed, it
	 * must be second character in line
	 */
	optype = line[1];
	if (strchr(ALLOPS, optype) == NULL) {
		printf("Unknown operator\n");
		return;
	}

	/* determine the RHS argument (if one is required),
	 * it must start in third character of line
	 */
	if (optype != PRINT) {
		if (strlen(line)<3) {
			printf("No RHS supplied\n");
			return;
		}
		status = get_second_value(vars, line+2, &second_value);
		if (status==ERROR) {
			printf("RHS argument is invalid\n");
			return;
		}
	}

	/* finally, do the actual operation
	 */
	if (optype == PRINT) {
		do_print(vars+varnum);
	} else if (optype == ASSIGN) {
		do_assign(vars+varnum, &second_value);
	} else if (optype == PLUS) {
		do_plus(vars+varnum, &second_value);
	} else if (optype == MULT) {
		do_mult(vars+varnum, &second_value);
	} else if (optype == POWER) {
		do_power(vars+varnum, &second_value);
	}
	return;
}

/****************************************************************/

/* convert a character variable identifier to a variable number
 */

int
to_varnum(char ident) {
	int varnum;
	varnum = ident - CH_A;
	if (0<=varnum && varnum<NVARS) {
		return varnum;
	} else {
		return ERROR;
	}
}

/****************************************************************/

/* process the input line to extract the RHS argument, which
 * should start at the pointer that is passed
 */

int
get_second_value(longint_t vars[], char *rhsarg,
			longint_t *second_value) {
	char *p;
	int varnum2;
	if (strchr(NUMCHRS, *rhsarg) != NULL ||
				strchr(SGNCHRS, *rhsarg) != NULL) {
		/* first character is a digit or a sign, so RHS 
		 * should be a number
		 */
		p = rhsarg+1;
		while (*p) {
			if (strchr(NUMCHRS, *p) == NULL) {
				/* nope, found an illegal character */
				return ERROR;
			}
			p++;
		}
		*second_value = parse_num(rhsarg);
		return !ERROR;
	} else {
		/* argument is not a number, so might be a variable */
		varnum2 = to_varnum(*rhsarg);
		if (varnum2==ERROR || strlen(rhsarg)!=1) {
			/* nope, not a variable either */
			return ERROR;
		}
		/* is a variable, so can use its value to assign to
		 * second_value
		 */
		*second_value = vars[varnum2];
		return !ERROR;
	}
	return ERROR;
}

/****************************************************************/

/* create an internal-format number out of a string
 */

longint_t
parse_num(char *rhs) {
	int i=0;
	longint_t num = LONG_ZERO;
	char t;
	while (*rhs && *rhs==CH_BLANK) {
		rhs++;
	}
	if (*rhs==CH_NE) {
		num.nega = !POSI;
		rhs++;
	}
	if (*rhs==CH_PL) {
		rhs++;
	}
	while (*rhs) {
		if (*rhs==CH_COM || *rhs==CH_BLANK) {
			rhs++;
		} else {
			if (i!=0 || *rhs!=CH_ZERO) {
				if (i==INTSIZE) {
					overflow_abort();
				}
				num.digs[i++] = *rhs;
			}
			rhs++;
		}
	}
	num.ndig = i;
	/* now reverse so that low order digit is in first position */
	for (i=0; i<num.ndig/2; i++) {
		t = num.digs[i];
		num.digs[i] = num.digs[num.ndig-1-i];
		num.digs[num.ndig-1-i] = t;
	}
	return num;
}

/****************************************************************/

/* convert a character digit to the int equivalent, but null bytes
 * stay as zero integers
 */

int
to_int(char digit) {
	if (digit != '\0') {
		return digit - CH_ZERO;
	} else {
		return 0;
	}
}

/****************************************************************/

/* and back again to a digit
 */

char
to_digit(int number) {
	return number + CH_ZERO;
}

/****************************************************************/

/* print out a longint value
 */

void
do_print(longint_t *var) {
	int i;
	if (var->ndig==0) {
		/* special case for zero */
		printf("0\n");
		return;
	}
	if (var->nega) {
		printf("-");
	}
	for (i=var->ndig-1; i>=0; i--) {
		printf("%c", var->digs[i]);
		if (i%3==0 && i>0) {
			printf("%c", CH_COM);
		}
	}
	printf("\n");
	return;
}

/****************************************************************/

/* update the indicated variable var1 by doing an assignment
 * using var2
 */

void
do_assign(longint_t *var1, longint_t *var2) {
	/* hey, this is trivial in this representation
	 */
	*var1 = *var2;
}

/****************************************************************/

/* add val to the character and the  possible carry to get a new
 * character as their sum, and a new integer carry
 */

char
add_to_digit(char d1, int val, int *carry) {
	int d;
	d = d1 + val + *carry;
	*carry = 0;
	while (d > CH_NINE) {
		d -= INT_TEN;
		*carry += 1;
	}
	return (char)d;
}

/****************************************************************/

/* substract val to the character and also the borrow to get a new
 * character as their sum, and a new integer borow
 */

char
sub_digit(char d1, int val, int *borrow) {
	int d;
	d = d1 - val - *borrow;
	*borrow = 0;
	if (d<CH_ZERO) {
		d += INT_TEN;
		*borrow = 1;
	}
	return (char)d;
}

/****************************************************************/

/* update the indicated variable var1 by doing an addition
 * using var2 to compute var1 = var1 + var2
 */

void
do_plus(longint_t *var1, longint_t *var2) {
	longint_t temp;
	if (var1->nega == var2->nega) {
		/* same signs, can just add */
		simple_plus(var1, var2);
	} else {
		/* different signs, need to get them right way round */
		temp = *var2;
		if (mag_cmp(var1, var2)>=0) {
			/* can process in this order */
			simple_suba(var1, &temp);
		} else {
			/* need to reverse the order */
			simple_suba(&temp, var1);
			*var1 = temp;
		}
	}
}

/****************************************************************/

/* return negative if magnitude of first arg is smaller than second,
 * zero if first arg has same magnitude as second
 * positive if magnitude of first arg is greater than second
 */

int
mag_cmp(longint_t *var1, longint_t *var2) {
	int i;
	if (var1->ndig != var2->ndig)  {
		return var1->ndig - var2->ndig;
	}
	for (i=var1->ndig-1; i>=0; i--) {
		if (var1->digs[i] != var2->digs[i]) {
			return var1->digs[i] - var2->digs[i];
		}
	}
	return 0;
}

/****************************************************************/

/* simple plus situation where var1 and var2 have the same sign
 */

void
simple_plus(longint_t *var1, longint_t *var2) {
	int i, carry=0, ndig;
	/* insert zeros to make the two numbers the same length */
	ndig = var1->ndig;
	if (var2->ndig > ndig) {
		ndig = var2->ndig;
	}
	for (i=var1->ndig; i<ndig; i++) {
		var1->digs[i] = CH_ZERO;
	}
	for (i=var2->ndig; i<ndig; i++) {
		var2->digs[i] = CH_ZERO;
	}
	/* do the addition over ndig digits */
	for (i=0; i<ndig; i++) {
		var1->digs[i] = add_to_digit(var1->digs[i],
				to_int(var2->digs[i]), &carry);
	}
	/* been a carry out of the top digit? */
	if (carry) {
		if (i>=INTSIZE) {
			/* nope, would overflow arrays */
			overflow_abort();
		}
		var1->digs[i++] = CH_ONE;
	}
	/* number of digits in the output */
	var1->ndig = i;
}

/****************************************************************/

/* simple subtraction situation where var2 is less than var1
 * and can be subtracted from it
 */

void
simple_suba(longint_t *var1, longint_t *var2) {
	int i, borrow=0, ndig;
	/* put zeros in to second argument to match first */
	for (i=var2->ndig; i<var1->ndig; i++) {
		var2->digs[i] = CH_ZERO;
	}
	ndig = i;
	/* do the subtraction */
	for (i=0; i<ndig; i++) {
		var1->digs[i] = sub_digit(var1->digs[i],
				to_int(var2->digs[i]), &borrow);
	}
	/* check for emergence of leading zeros */
	while (ndig>0 && var1->digs[ndig-1]==CH_ZERO) {
		ndig--;
	}
	var1->ndig = ndig;
}

/****************************************************************/

/* multiply argument by ten by shifting, and adding a zero
 */

void
mult_one_digit(longint_t *var, int digit) {
	longint_t working=LONG_ZERO;
	int i, carry;
	carry = 0;
	for (i=0; i<var->ndig; i++) {
		working.digs[i] = add_to_digit(CH_ZERO,
			to_int(var->digs[i])*digit,
			&carry);
	}
	if (carry) {
		if (i==INTSIZE) {
			overflow_abort();
		}
		working.digs[i++] = to_digit(carry);
	}
	working.ndig = i;
	*var = working;
	return;
}

/****************************************************************/

/* multiply argument by ten by shifting, and adding a zero
 */

void
mult_ten(longint_t *var) {
	int i;
	if (var->ndig==INTSIZE) {
		overflow_abort();
	}
	for (i=var->ndig; i>0; i--) {
		var->digs[i] = var->digs[i-1];
	}
	var->digs[0] = CH_ZERO;
	var->ndig++;
	return;
}

/****************************************************************/

/* update the indicated variable var1 by doing a multiplication
 * using var2 to compute var1 = var1 * var2
 */

void
do_mult(longint_t *var1, longint_t *var2) {
	longint_t product = LONG_ZERO;
	longint_t oneterm;
	int i;
	for (i=var2->ndig-1; i>=0; i--) {
		/* process one digit from var2 */
		oneterm = *var1;
		mult_one_digit(&oneterm, to_int(var2->digs[i]));
		mult_ten(&product);
		do_plus(&product, &oneterm);
	}
	/* now sort out the sign */
	product.nega = var1->nega != var2->nega;
	*var1 = product;
	return;
}

/****************************************************************/

/* update the indicated variable var1 by raising it to the
 * power of variable var2, var1 = var1 ^ var2
 */

void
do_power(longint_t *var1, longint_t *var2) {
	printf("Power-of operator not implemented\n");
	return;
}

/****************************************************************/

/* set the vars array to all zero values
 */

void
zero_vars(longint_t vars[]) {
	int i;
	longint_t zero = LONG_ZERO;
	for (i=0; i<NVARS; i++) {
		do_assign(vars+i, &zero);
	}
	return;
}

/****************************************************************/

/* exit if numbers are going to get too big
 */

void
overflow_abort() {
	fprintf(stderr, "Integer overflow, program terminated\n");
	exit(EXIT_FAILURE);
}