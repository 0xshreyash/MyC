/*
 * COMP20007 Design of Algorithms
 * Semester 1 2016
 * Assignment 2 driver
 *
 * Clement Poh (cpoh@unimelb.edu.au)
 *
 * This module processes and runs the program.
 *
*/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <assert.h>

#include "extra.h"
#include "types.h"
#include "hashtable.h"

#define DEFAULT_SIZE 11
#define NUM_COLLISIONS 10

/* Store the configuration options from the command line */
typedef struct {
    char *bin;
    char *insert;
    char *find;
    Hash hash;
    unsigned int size;
    Chain method;
    int seed;
    bool MTF;
    bool string;
    bool print;
    void (*coll)(unsigned int, unsigned int, int);
} Options;

/* Print usage message and exit */
static void usage_exit(char *bin);

/* Load the command line options into opts */
static Options load_options(int argc, char *argv[]);

static HT create_table(Options opts, int size);

/* Returns a pointer to file */
static FILE *safe_open(char *filename, const char *mode);

/* Print usage message and exit */
static void usage_exit(char *bin) {
    fprintf(stderr, "%s [options] <insert.in>\n", bin);
    fprintf(stderr, "insert.in  File containing values to be inserted\n");
    fprintf(stderr, "\nOptions:\n");
    fprintf(stderr, "  -f file  File containing values to be found\n");
    fprintf(stderr, "  -m       Move-to-front for separate chaining\n");
    fprintf(stderr, "  -s seed  Random seed [default: 0]\n");
    fprintf(stderr, "  -t s     Expect strings as input\n");
    fprintf(stderr, "  -p       Print the hash table to stdout\n");
    fprintf(stderr, "  -n size  Expected input size [default: 11]\n");
    fprintf(stderr, "Collision resolution method:\n");
    fprintf(stderr, "  -r c     Chaining with a linked list [default]\n");
    fprintf(stderr, "  -r a     Chaining with an array\n");
    fprintf(stderr, "  -r d     Open addressing with double hashing\n");
    fprintf(stderr, "  -r l     Open addressing with linear probing\n");
    fprintf(stderr, "Hash functions:\n");
    fprintf(stderr, "  -h w     hash with: worst_hash [default]\n");
    fprintf(stderr, "  -h n     hash with: num_hash, for ints\n");
    fprintf(stderr, "  -h b     hash with: bad_hash, for strings\n");
    fprintf(stderr, "  -h u     hash with: universal_hash, for strings\n");
    fprintf(stderr, "Generate universal hash collisions:\n");
    fprintf(stderr, "  -c d     hash collisions with dumb_collisions\n");
    fprintf(stderr, "  -c c     hash collisions with clever_collisions\n");

    exit(EXIT_FAILURE);
}

/* Load the command line options into opts */
static Options load_options(int argc, char *argv[]) {
    extern char *optarg;
    extern int optind;
    int c;
    Options opts = {
        .bin    = argv[0],
        .size   = DEFAULT_SIZE,
        .insert = NULL,
        .find   = NULL,
        .method = LIST,
        .MTF    = false,
        .string = false,
        .seed   = 0,
        .hash   = worst_hash,
        .print  = false,
        .coll   = NULL,
    };

    while ((c = getopt(argc, argv, "c:f:h:mn:pr:s:t:")) != -1) {
        switch (c) {
            case 'h':
                switch (optarg[0]) {
                    case 'n': opts.hash = (Hash) num_hash;        break;
                    case 'b': opts.hash = (Hash) bad_hash;        break;
                    case 'u': opts.hash = (Hash) universal_hash;  break;
                    default: opts.hash = (Hash) worst_hash;
                } break;
            case 'c':
                switch (optarg[0]) {
                    case 'd': opts.coll = collide_dumb;   break;
                    case 'c': opts.coll = collide_clever; break;
                    default: usage_exit(opts.bin);
                } break;
            case 'r': switch (optarg[0]) {
                    case 'a': opts.method = ARRAY;      break;
                    case 'c': opts.method = LIST;       break;
                    case 'd': opts.method = DOUBLE;     break;
                    case 'l': opts.method = LINEAR;     break;
                    default: usage_exit(opts.bin);
                } break;
            case 'f': opts.find = optarg;       break;
            case 'm': opts.MTF = true;          break;
            case 'n': opts.size = atoi(optarg); break;
            case 'p': opts.print = true;        break;
            case 's': opts.seed = atoi(optarg); break;
            case 't': opts.string = optarg[0] == 's'; break;
            case '?':
            default: usage_exit(opts.bin);
        }
    }

    if (optind > argc) {
        fprintf(stderr, "Missing input keys\n");
        usage_exit(opts.bin);
    }

    if (opts.coll && opts.hash != (Hash) universal_hash) {
        fprintf(stderr, "-c: changing hash to universal hash\n");
        opts.hash = (Hash) universal_hash;
    }

    opts.insert = argv[optind];

    return opts;
}

int main(int argc, char *argv[]) {
    Options opts = load_options(argc, argv);

    int size = determine_size(opts.size);
    HT ht = create_table(opts, size);

    /* Seed the random number generator */
    srand(opts.seed);

    FILE *insert = safe_open(opts.insert, "r");
    hash_load(ht, insert);
    fclose(insert);

    if (opts.find) {
        FILE *find = safe_open(opts.find, "r");
        hash_search_file(ht, find);
        fclose(find);
    }

    if (opts.coll)
        opts.coll(ht->size, opts.seed, NUM_COLLISIONS);

    if (opts.print)
        hash_print(ht, stdout);

    return 0;
}

/* Create the hash table from the program options */
static HT create_table(Options opts, int size) {
    Type t = { .eq    = opts.string ? (Eq)    str_eq    : (Eq) int_eq
             , .parse = opts.string ? (Parse) str_copy  : (Parse) atoi
             , .print = opts.string ? (Print) str_print : (Print) int_print };

    HT ht = NULL;
    switch (opts.method) {
        case ARRAY:
            ht = opts.MTF
                ? new_hash_array_MTF(size, opts.hash, t)
                : new_hash_array(size, opts.hash, t);
            break;
        case LIST:
            ht = opts.MTF
                ? new_hash_list_MTF(size, opts.hash, t)
                : new_hash_list(size, opts.hash, t);
            break;
        case DOUBLE:
            /* No way to choose the second hash function */
            ht = new_hash_double(size, opts.hash, opts.hash, t);
            break;
        case LINEAR: ht = new_hash_linear(size, opts.hash, t);
            break;
        default:
            fprintf(stderr, "Invalid collision resolution method\n");
            exit(EXIT_FAILURE);
    }

    return ht;
}

/* Returns a pointer to file */
static FILE *safe_open(char *filename, const char *mode) {
    const char *err = "Could not open file: %s\n";
    FILE *file = fopen(filename, mode);

    if (file) {
        return file;
    } else {
        fprintf(stderr, err, filename);
        exit(EXIT_FAILURE);
    }
}
