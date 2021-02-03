/**************************************
 *
 * skip_set.h
 *
 * JMU CS 240 Fall 2015
 * PA 3: Skip List Set
 * Type and function declarations
 *
 *************************************/


#ifndef SKIP_SET_H
#define SKIP_SET_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/**************************************
 * TYPE DECLARATIONS
 *************************************/

typedef int data_t;

typedef struct skip_node {
    data_t data;
    size_t height;
    struct skip_node *next;
} skip_node_t;

typedef struct skip_set {
    skip_node_t *head;
    size_t max_height;
    size_t size;
} skip_set_t;

typedef skip_node_t* skip_set_iter_t;


/**************************************
 * PART 1: BASIC SET OPERATIONS
 *************************************/

/*
 * Initializes a new empty set.
 */
void skip_set_init(skip_set_t *set, size_t max_height);

/**
 * Removes all elements from a set.
 */
void skip_set_clear(skip_set_t *set);

/**
 * Returns the size of a set.
 */
size_t skip_set_size(skip_set_t *set);

/*
 * Deallocate all memory associated with a set.
 */
void skip_set_free(skip_set_t *set);

/*
 * Adds an element to a set.
 */
void skip_set_add(skip_set_t *set, data_t value);

/*
 * Removes an element from a set. If the set does not contain the given value,
 * no changes take place.
 */
void skip_set_remove(skip_set_t *set, data_t value);

/*
 * Returns and removes an arbitrary element from a set. The behavior is
 * undefined if the set contains zero elements.
 */
data_t skip_set_pop(skip_set_t *set);

/*
 * Returns true if the element is a member of the set; false otherwise.
 */
bool skip_set_contains(skip_set_t *set, data_t value);


/**************************************
 * PART 2: ITERATORS AND COMPARISONS
 *************************************/

/*
 * Returns an iter for a set that represents the beginning of the set.
 */
skip_set_iter_t skip_set_begin(skip_set_t *set);

/*
 * Returns an iter for a set that represents the end of the set.
 */
skip_set_iter_t skip_set_end(skip_set_t *set);

/*
 * Advances and returns a set iterator.
 */
skip_set_iter_t skip_set_next(skip_set_iter_t iter);

/*
 * Returns true if and only if set1 is a subset of set2.
 */
bool skip_set_is_subset(skip_set_t *set1, skip_set_t *set2);

/*
 * Returns true if and only if set1 is a superset of set2.
 */
bool skip_set_is_superset(skip_set_t *set1, skip_set_t *set2);

/*
 * Returns true if and only if set1 and set2 contain the same items.
 */
bool skip_set_is_equal(skip_set_t *set1, skip_set_t *set2);

/*
 * Returns true if and only if set1 and set2 don't contain any of the same
 * items.
 */
bool skip_set_is_disjoint(skip_set_t *set1, skip_set_t *set2);


/**************************************
 * PART 3: SET CONSTRUCTORS
 *************************************/

/*
 * Make dest a copy of src; i.e., dest should contain all elements in src and
 * no extra elements.
 */
void skip_set_copy(skip_set_t *dest, skip_set_t *src);

/*
 * Calculates the union of set1 and set2, storing it in dest.
 */
void skip_set_union(skip_set_t *dest, skip_set_t *set1, skip_set_t *set2);

/*
 * Calculates the intersection of set1 and set2, storing it in dest.
 */
void skip_set_intersect(skip_set_t *dest, skip_set_t *set1, skip_set_t *set2);

/*
 * Calculates the difference between set1 and set2, storing it in dest.
 */
void skip_set_diff(skip_set_t *dest, skip_set_t *set1, skip_set_t *set2);

/*
 * Calculates the symmetric difference between set1 and set2, storing it in
 * dest.
 */
void skip_set_sym_diff(skip_set_t *dest, skip_set_t *set1, skip_set_t *set2);


#endif
