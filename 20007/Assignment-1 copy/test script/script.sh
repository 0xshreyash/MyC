#!/bin/bash

COUNTER=100
MAXEDGES=100
MAXCOUNTER=3000
EDGES=0
EXE="ass1"
SORT=$1

while [ $EDGES -le $MAXEDGES ]; do
    let COUNTER=100
    while [ $COUNTER -le $MAXCOUNTER ]; do
        ../daggen $COUNTER $EDGES > ../test/tmp.txt
        ../$EXE -m $SORT ../test/tmp.txt > ../test/tmp.out
        # ./$EXE -v test/tmp.txt < test/tmp.out
        let COUNTER+=100
    done
    let EDGES+=10
done
