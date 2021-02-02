/*
 * hash_set.c
 *
 * Name: 
 */

#include "hash_set.h"


/**************************************
 * HELPER FUNCTIONS
 *************************************/

size_t hash(data_t value)
{
    // basic linear congruential generator (LCG) algorithm
    // (see https://en.wikipedia.org/wiki/Linear_congruential_generator)
    return (1103515245 * (size_t)(value) + 12345) % (1<<31);
}

size_t hash_address(size_t the_hash_value, size_t capacity)
{
    return the_hash_value % capacity;
}

bucket_t* malloc_buckets(size_t capacity)
{
    bucket_t *table = (bucket_t*)malloc(sizeof(bucket_t)*capacity);
    if (table == NULL) {
        printf("Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i=0; i<capacity; i++) {
        table[i].is_empty = true;
        table[i].value = (data_t)0;
        table[i].next = NULL;
    }
    return table;
}

bucket_t* probe(bucket_t table[], size_t capacity, data_t value)
{
    size_t index = hash_address(value, capacity);
    bucket_t* storage_bucket = &table[index];

    if (storage_bucket)
    {
        return storage_bucket;
    }
    return NULL;
}

void insert(bucket_t table[], size_t capacity, data_t value)
{
    bucket_t* storage_bucket = probe(table, capacity, value);

    if (storage_bucket->is_empty)
    {
        storage_bucket->value = value;
        storage_bucket->is_empty = false;
    }
}

/**************************************
 * BASIC SET OPERATIONS
 *************************************/

void hash_set_init(hash_set_t *set)
{
    set->capacity = 4;
    set->table = malloc_buckets(set->capacity);
    set->size = 0;
}

void hash_set_rehash(hash_set_t *set)
{
    bucket_t* old_set_table = set->table;
    set->table = NULL;
    set->table = malloc_buckets(2 * set->capacity);     
    set->capacity = 2 * set->capacity;
    for (size_t i = 0; i < set->size; i++)
    {
        if (old_set_table[i].is_empty == false)
        {
            insert(set->table, set->capacity, old_set_table[i].value);
        }
    }
    free(old_set_table);
    old_set_table = NULL;
}

size_t hash_set_size(hash_set_t *set)
{
    return set->size;
}

void hash_set_free(hash_set_t *set)
{
    free(set->table);
    set->table = NULL;
    set->capacity = 0;
    set->size = 0;
}

void hash_set_add(hash_set_t *set, data_t value)
{
    if (hash_set_size(set) >= (set->capacity)/2)    
    {
        hash_set_rehash(set);
    }
    insert(set->table, set->capacity, value);
    set->size += 1;
}

bool hash_set_contains(hash_set_t *set, data_t value)
{
    bool found = false;
    bucket_t* storage_bucket = probe(set->table, set->capacity, value);
    if (storage_bucket && storage_bucket->is_empty == false)
    {
        if (storage_bucket->value == value);
        {
            found = true; 
        }
    }
    return found;
}

