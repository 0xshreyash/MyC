# Makefile 
# Andrew Turpin, Steven Bird
# March 2016

OBJ     = main.o ksmallest.o
CC      = gcc

ksm: $(OBJ) Makefile
	$(CC) -o ksm $(OBJ)

random: 
	od -t u /dev/random | awk '{print $$2}' | head -10000 > t1

main.o: ksmallest.h Makefile
ksmallest.o: ksmallest.h 

