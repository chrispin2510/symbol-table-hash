/**************************************
 *
 * array_set.h
 *
 * JMU CS 240 Fall 2015
 * PA 2: Array Set
 * Type and function declarations
 *
 *************************************/


#ifndef ARRAY_SET_H
#define ARRAY_SET_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


/**************************************
 * TYPE DECLARATIONS
 *************************************/

typedef int data_t;

typedef struct array_set {
    data_t *array;
    size_t capacity;
    size_t size;
} array_set_t;

typedef data_t* array_set_iter_t;


/**************************************
 * PART 1: BASIC SET OPERATIONS
 *************************************/

/*
 * Initializes a new empty set.
 */
void array_set_init(array_set_t *set, size_t capacity);

/**
 * Removes all elements from a set (doesn't deallocate anything!).
 */
void array_set_clear(array_set_t *set);

/**
 * Returns the size of a set.
 */
size_t array_set_size(array_set_t *set);

/*
 * Deallocate memory associated with a set.
 */
void array_set_free(array_set_t *set);

/*
 * Adds an element to a set. If the set already contains the given value, no
 * changes take place.
 */
void array_set_add(array_set_t *set, data_t value);

/*
 * Removes an element from a set. If the set does not contain the given value,
 * no changes take place.
 */
void array_set_remove(array_set_t *set, data_t value);

/*
 * Returns and removes an arbitrary element from a set. The behavior is
 * undefined if the set contains zero elements.
 */
data_t array_set_pop(array_set_t *set);

/*
 * Returns true if the element is a member of the set; false otherwise.
 */
bool array_set_contains(array_set_t *set, data_t value);


/**************************************
 * PART 2: ITERATORS AND COMPARISONS
 *************************************/

/*
 * Returns an iter for a set that represents the beginning of the set.
 */
array_set_iter_t array_set_begin(array_set_t *set);

/*
 * Returns an iter for a set that represents the end of the set.
 */
array_set_iter_t array_set_end(array_set_t *set);

/*
 * Advances and returns a set iterator.
 */
array_set_iter_t array_set_next(array_set_iter_t iter);

/*
 * Returns true if and only if set1 is a subset of set2.
 */
bool array_set_is_subset(array_set_t *set1, array_set_t *set2);

/*
 * Returns true if and only if set1 is a superset of set2.
 */
bool array_set_is_superset(array_set_t *set1, array_set_t *set2);

/*
 * Returns true if and only if set1 and set2 contain the same items.
 */
bool array_set_is_equal(array_set_t *set1, array_set_t *set2);

/*
 * Returns true if and only if set1 and set2 don't contain any of the same
 * items.
 */
bool array_set_is_disjoint(array_set_t *set1, array_set_t *set2);


/**************************************
 * PART 3: SET CONSTRUCTORS
 *************************************/

/*
 * Make dest a copy of src; i.e., dest should contain all elements in src and
 * no extra elements.
 */
void array_set_copy(array_set_t *dest, array_set_t *src);

/*
 * Calculates the union of set1 and set2, storing it in dest.
 */
void array_set_union(array_set_t *dest, array_set_t *set1, array_set_t *set2);

/*
 * Calculates the intersection of set1 and set2, storing it in dest.
 */
void array_set_intersect(array_set_t *dest, array_set_t *set1, array_set_t *set2);

/*
 * Calculates the difference between set1 and set2, storing it in dest.
 */
void array_set_diff(array_set_t *dest, array_set_t *set1, array_set_t *set2);

/*
 * Calculates the symmetric difference between set1 and set2, storing it in
 * dest.
 */
void array_set_sym_diff(array_set_t *dest, array_set_t *set1, array_set_t *set2);


#endif

