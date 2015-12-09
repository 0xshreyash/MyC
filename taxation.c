/* Exercises 1-3 in lec07 slides,
   Foundations of Algorithms (COMP10002)

   Andrew Chester, October 2012

*/
#include <stdio.h>
#include <assert.h>

#define MAXCHARS 50
#define MAXMARRIAGES 10
#define MAXWORKING 100
#define TRUE (1==1)
#define FALSE (1==0)

#define AUSCITIZEN 30000000
#define NZLCITIZEN 6000000

/* Holds a date in dd/mm/yyyy format */
typedef struct {
    int dd, mm, yyyy;
} date_t;

/* Holds all components of a person's name */
typedef struct {
    char title[MAXCHARS+1], given[MAXCHARS+1];
    char middle[MAXCHARS+1], last[MAXCHARS+1];
} name_t;

/* Contains information about a marriage. Note the potential for abuse of 
   the divorce field: behaviour is undefined if marriage has not ended. */
typedef struct {
    date_t married;
    name_t spouse;
    date_t divorced;
} marriage_t; 

/* Information about each year the person worked */
typedef struct {
    int year;
    double income, tax;
    date_t paid;
} taxyear_t;

/* The person structure. This is far from the only way of implementing this.
   I have opted for a quite heirarchical approach, declaring many component
   structures above. This is a reasonable general purpose representation*/
typedef struct {
    name_t name;
    marriage_t marriages[MAXMARRIAGES];
    int num_marriages;
    int dead;
    date_t dob, dod;
    taxyear_t work[MAXWORKING];
    int years_worked;
} person_t;    

double life_expectancy(person_t* country, int n);
int age(date_t dob,date_t dod);
double tax_revenue(person_t* country, int n, int year);

int
main(int argc, char** argv) {
    /* These are not typedef, since there will likely only be one australia in
       existence in any given time. Defining a country type would be wasteful,
       as they vary greatly in size, and 24 million entries would be empty
       for nz. Were multiple copies of a single country being used at once,
       then defining types for them might be appropriate. */
    person_t persons_aus[AUSCITIZEN];
    int npersons_aus=0;
    person_t persons_nzl[NZLCITIZEN];
    int npersons_nzl=0;

    /* test cases have been left as an exercise to the reader */

    return 0;
}


/* Calculates the average age of death (in years) for citizens of the given
   country. */
double
life_expectancy(person_t* country, int n) {
    int dead=0, years=0, i;
    for (i=0; i<n; i++) {
        /* only count dead people */
        if (country[i].dead==TRUE) {
            dead++;
            /* add their age at death - consider why we can't just use:
                country[i].dod.yyyy-country[i].dob.yyyy;
            */
            years += age(country[i].dob,country[i].dod);
        }
    }
    return ((double) years)/dead;
}

/* Calculates the age of a person in years, given their birthdate and the
   current date. Needs to check if they have had their birthday this year */
int
age(date_t dob, date_t now) {
    int years;
    years = now.yyyy-dob.yyyy;
    /* if it is before their birthday, then subtract a year*/
    if (dob.mm<now.mm || (dob.mm==now.mm && dob.dd<=now.dd)) {
        years--;
    }
    return years;
}

/* Calculates the total tax revenue for a given country in the specified year.
   This is a naive approach which takes worst case O(nm) time, where n is the
   number of people in the country, and m is the number of years people work.

   How can we do better? Perhaps check to see if they were even alive in that
   year, before searching all their tax records, but this is not that helpful.
   To make this search feasible, we would want to have the taxyear list be 
   sorted. Then, we could do an initial bounds check on the first and last
   years they worked, and if it succeeds, binary search for the correct year,
   reducing the time to worst case O(n log(m)). If this was a very important
   function which was being called often, it might be worth changing the 
   data structure to speed this up, but any additional savings will likely
   come at the expense of space.
   */
double
tax_revenue(person_t* country, int n, int year) {    
    /* Tax could easily exceed a few billion dollars */
    double collected=0;
    int i, j;
    /* loop over every person */
    for (i=0; i<n; i++) {
        /* and every year that they worked */
        for (j=0; j<country[i].years_worked; j++) {
            if (country[i].work[j].year==year) {
                collected += country[i].work[j].tax;
            }
            /* simple optimisation: people won't pay tax twice in one year,
               so when we find their record we can skip to the next person. */
            break;
        }
    }
    return collected;
}
