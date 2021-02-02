/**************************************
 *
 * hash_set.h
 *
 * JMU CS 240 Fall 2015
 * LAB 14: Hash Set
 * Type and function declarations
 *
 *************************************/


#ifndef HASH_SET_H
#define HASH_SET_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/**************************************
 * TYPE DECLARATIONS
 *************************************/

typedef int data_t;

typedef struct bucket {
    bool is_empty;
    data_t value;
    struct bucket *next;    // for chaining only
} bucket_t;

typedef struct hash_set {
    bucket_t *table;
    size_t capacity;
    size_t size;
} hash_set_t;


/**************************************
 * HELPER FUNCTIONS
 *************************************/

/*
 * Calculate a hash code for the given value.
 */
size_t hash(data_t value);

/*
 *  Calculate the hash address for a given LCG value of a key 
 */

size_t hash_address(size_t the_hash_value, size_t capacity);

/*
 * Allocate space for a new hash table (array of buckets) on the heap.
 */
bucket_t* malloc_buckets(size_t capacity);

/*
 * Probe for the given value in a hash table.
 */
bucket_t* probe(bucket_t table[], size_t capacity, data_t value);

/*
 * Insert a new value into a hash table.
 */
void insert(bucket_t table[], size_t capacity, data_t value);


/**************************************
 * BASIC SET OPERATIONS
 *************************************/

/*
 * Initializes a new empty set.
 */
void hash_set_init(hash_set_t *set);

/**
 * Rehash the hash_set
 */
void rehash(hash_set_t *set);

/**
 * Returns the size of a set.
 */
size_t hash_set_size(hash_set_t *set);

/*
 * Deallocate all memory associated with a set.
 */
void hash_set_free(hash_set_t *set);

/*
 * Adds an element to a set.
 */
void hash_set_add(hash_set_t *set, data_t value);

/*
 * Returns true if the element is a member of the set; false otherwise.
 */
bool hash_set_contains(hash_set_t *set, data_t value);


#endif
