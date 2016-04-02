/*	Sample answer for q9.3 of
	"Programming, Problem Solving and Abstraction in C"
	Written by Jesse Neave, 29/04/2004
	Modified by Alistair Moffat, November 2013

	A program to simulate dealing a whole bunch of poker hands, and
	print statistics about different types of hands.
	As always, there are many ways writing this program.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define PLAYERS		4
#define CARDSINHAND	5
#define SUITS		4
#define	FACEVALS	13
#define CARDS		(SUITS * FACEVALS)
#define NUMROUNDS	10000
#define PRINT_LIM	3
#define TRUE		1
#define FALSE		0


/* These arrays are used for the printing code */
/* global array to hold possible card values */
char *facevals[FACEVALS] = {"Ac", " 2", " 3", " 4", " 5", " 6", " 7",
		 	" 8", " 9", "10", "Ja", "Qu", "Ki"};

/* possible suits */
char suits[SUITS] = {'S', 'C', 'D', 'H'};


/* This functions stores ints between 0 and 51 in each element of the array */
void deal_round(int cards[PLAYERS][CARDSINHAND]);
void print_round(int cards[PLAYERS][CARDSINHAND]);
int has_pair(int hand[CARDSINHAND]);
int has_triple(int hand[CARDSINHAND]);
int has_fullhouse(int hand[CARDSINHAND]);

int main(void) {
	int i, j;
	int total_pairs = 0;
	int total_triples = 0;
	int total_fullhouses = 0;
	int cards[PLAYERS][CARDSINHAND];

	/* initialize random number generator with process id */
	srand((int)getpid());

	for (i=0; i<NUMROUNDS; i++) {
		deal_round(cards);

		/* print out the first few rounds of hands... */
		if (i<PRINT_LIM) {
			printf("Hand number %d:\n", i);
			print_round(cards);
		}

		for (j=0; j<PLAYERS; j++) {
			total_pairs += has_pair(cards[j]);
			total_triples += has_triple(cards[j]);
			total_fullhouses += has_fullhouse(cards[j]);
		}
	}

	printf("Over %6d hands of cards:\n", NUMROUNDS*PLAYERS);
	printf("%6d (%5.2f%%) have a pair (or better)\n",
		total_pairs, 100.0*total_pairs/NUMROUNDS/PLAYERS);
	printf("%6d (%5.2f%%) have three of a kind (or better)\n",
		total_triples, 100.0*total_triples/NUMROUNDS/PLAYERS);
	printf("%6d (%5.2f%%) have a full house (or better)\n",
		total_fullhouses, 100.0*total_fullhouses/NUMROUNDS/PLAYERS);

	return 0;
}

/* puts values into the cards array to represent the cards dealt.
   The cards to be dealt are randomly determined using the rand()
   function, and a second array is used to allow duplicate values to
   be detected and prevented easily */ 

void
deal_round(int cards[PLAYERS][CARDSINHAND]) {
	int i, j;
	int cardsused[CARDS] = {0}; /* to store which cards have been dealt */
	for (i=0; i < PLAYERS; i++) {
		for (j=0; j < CARDSINHAND; j++) {
			/* pick a card between 0 and 51, that has not
			   yet been dealt this round */
			cards[i][j] = rand()%CARDS;
			while (cardsused[cards[i][j]] == 1) {
				/* nope, that one used, get another */
				cards[i][j] = rand()%CARDS;
			}
			/* now set that assigned card to used */
			cardsused[cards[i][j]] = 1;
		}
	}
	return;
}

void
print_round(int cards[PLAYERS][CARDSINHAND]) {
	int i, j;
	for (i=0; i<PLAYERS; i++) {
		printf("player %d:   ", i + 1);
		for (j=0; j<CARDSINHAND; j++) {
			printf("%s-%c",
				facevals[cards[i][j]%FACEVALS],
					 suits[cards[i][j]/FACEVALS]);
			if (j<CARDSINHAND-1)
				printf(", ");
			else
				printf("\n");
		}
	}
	printf("\n");
	return;
}

/* compares every card against every other to look for pairs, returns TRUE if
   a pair is found, FALSE otherwise */
int
has_pair(int hand[CARDSINHAND]) {
	int i, j;
	for (i=0; i<CARDSINHAND-1; i++) {
		for (j=i+1; j<CARDSINHAND; j++) {
			/* do cards have the same face value */
			if (hand[i]%FACEVALS == hand[j]%FACEVALS)
				return TRUE;
		}
	}
	return FALSE;
}

/* when checking for more than two matches, code like that used in the frequency
   counting program for question 7.4 becomes useful */
int has_triple(int hand[CARDSINHAND]) {
	int i;
	int countcards[FACEVALS] = {0};

	for (i=0; i<CARDSINHAND; i++) {
		countcards[hand[i]%FACEVALS]++;
	}

	for (i=0; i<FACEVALS; i++) {
		if(countcards[i] >= 3)
			return TRUE;
	}
	return FALSE;
}

/* this could probably be written more elegantly, but this will do the job.
   Uses the same idea as in has_triple */
int has_fullhouse(int hand[CARDSINHAND]) {
	int i, triple_found = FALSE, pair_found = FALSE;
	int countcards[FACEVALS] = {0};

	for (i=0; i<CARDSINHAND; i++) {
		countcards[hand[i]%FACEVALS]++;
	}

	for (i=0; i<FACEVALS; i++) {
		triple_found += (countcards[i] == 3);
		pair_found += (countcards[i] == 2);
			
	}
	return triple_found && pair_found;
}
