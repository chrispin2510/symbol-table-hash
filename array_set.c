/*
 * array_set.c
 *
 * Name: 
 */

#include "array_set.h"
#include <stdlib.h>
#include <time.h>


/***********************************
 *  HELPER FUNCTIONS
 ***********************************/
static size_t hash(data_t value)
{
    return (1103515245 * (size_t)(value) + 12345) % (1<<31);
}

static size_t hash_address(size_t the_hash_value, size_t capacity)
{
    return the_hash_value % capacity;
}

static data_t* probe(array_set_t* array_set, size_t capacity, data_t value) 
{
    size_t index = hash_address(value, capacity);
    data_t* data_entry_position = &array_set->array[index];

    if (data_entry_position != NULL)
    {
        return data_entry_position;
    }
    return NULL;
}
/***********************************
 *  END
 ***********************************/

void array_set_init(array_set_t *set, size_t capacity)
{
    set->array = (data_t*)malloc(sizeof(data_t) * capacity); 
    set->capacity = capacity;
}

void array_set_clear(array_set_t *set)
{
    for (size_t i = 0; i < set->capacity; i++)
    {
        set->array[i] = 0;
    }
    set->size = 0;
}

size_t array_set_size(array_set_t *set)
{
    return set->size;
}

void array_set_free(array_set_t *set)
{
    free(set->array);
    set->array = NULL;
    set->capacity = 0;
    set->size = 0;
}

void array_set_add(array_set_t *set, data_t value)
{
    data_t* data_entry_position = probe(set, set->capacity, value);

    if (*data_entry_position != value)
    {
        *data_entry_position = value;
        set->size++;
    }
}

void array_set_remove(array_set_t *set, data_t value)
{
    data_t* data_entry_position = probe(set, set->capacity, value);

    if (*data_entry_position != 0)
    {
        *data_entry_position = 0;
        set->size--;
    }
}

data_t array_set_pop(array_set_t *set)
{
    data_t temp_data = 0;
    srand(time(0));         // Seed at current time
    size_t index = rand() % set->capacity; 
    data_t* arbitrary_entry_position = probe(set, set->capacity, set->array[index]);  

    if (*arbitrary_entry_position != 0)
    {
        temp_data = *arbitrary_entry_position;
        *arbitrary_entry_position = 0;
        set->size--;
    }
    return temp_data;
}

bool array_set_contains(array_set_t *set, data_t value)
{
    data_t index = hash_address(hash(value), set->capacity);

    if (value == set->array[index])
    {
        return true;
    }
    else 
    {
        return false;
    }
}

array_set_iter_t array_set_begin(array_set_t *set)
{
    return set->array;
}

array_set_iter_t array_set_end(array_set_t *set)
{
    return (set->array + (set->capacity - 1));
}

array_set_iter_t array_set_next(array_set_iter_t iter)
{
    return ++iter;
}

bool array_set_is_subset(array_set_t *set1, array_set_t *set2)
{
    bool flag = true;
    size_t index = 0;

    if (set1->size <= set2->size)
    {
        while (index != set1->capacity && flag == true)
        {
            if (set1->array[index] != 0) 
            {
                if (array_set_contains(set2, set1->array[index]) == false)
                {
                    flag = false;
                }
            }
            index++;
        }
    }
    return flag;
}

bool array_set_is_superset(array_set_t *set1, array_set_t *set2)
{
    bool flag = true;
    size_t index = 0;

    if (set1->size >= set2->size)
    {
        while (index != set2->capacity && flag == true)
        {
            if (set2->array[index] != 0)
            {
                if (!array_set_contains(set1, set2->array[index]))
                {
                    flag = false;
                }
            }
            index++;
        }
    }
    return flag;
}

bool array_set_is_equal(array_set_t *set1, array_set_t *set2)
{
    bool flag = true;
    size_t index1 = 0, index2 = 0;

    if (set1->size != set2->size)
    {
        flag = false;
    }
    else
    {
        while (index1 <= set1->capacity && index2 <= set2->capacity && flag == true)
        {
            if (set1->array[index1] == 0)
            {
                index1++;
            }
            else if (set2->array[index2] == 0)
            {
                index2++;
            }
            else 
            {
                if (!array_set_contains(set1, set2->array[index2]) || !array_set_contains(set2, set1->array[index1]))
                {
                    flag = false;
                }
                else
                {
                    index1++; index2++;
                }
            }
        }
    }
    return flag;
}

bool array_set_is_disjoint(array_set_t * set1, array_set_t *set2)
{
    bool flag = true;
    size_t index1 = 0, index2 = 0;

    while (index1 <= set1->capacity && index2 <= set2->capacity && flag == true)
    {
        if (set1->array[index1] == 0)
        {
            index1++;
        }
        else if (set2->array[index2] == 0)
        {
            index2++;
        }
        else
        {
            if (array_set_contains(set1, set2->array[index2]) || array_set_contains(set2, set1->array[index1]))
            {
                flag = false;
            }
            else
            {
                index1++; index2++;
            }
        }
    }
    return flag;
}

void array_set_copy(array_set_t *dest, array_set_t *src)
{
    for (size_t i = 0; i < src->capacity; i++)
    {
        if (src->array[i] != 0)
        {
            dest->array[i] = src->array[i];
        }
    }
    dest->size = src->size;
}


void array_set_union(array_set_t *dest, array_set_t *set1, array_set_t *set2)
{
    size_t index1 = 0, index2 = 0, index = 0;

    while (index1 != set1->capacity && index2 != set2->capacity)
    {
        if (set1->array[index1] == 0)
        {
            index1++;
        }
        else if (set2->array[index2] == 0)
        {
            index2++;
        }
        else
        {
            if (!array_set_contains(dest, set1->array[index1]) || !array_set_contains(dest, set2->array[index2]))
            {
                index = hash_address(set1->array[index1], dest->capacity);
                dest->array[index] = set1->array[index1];
                index = hash_address(set2->array[index2], dest->capacity);
                dest->array[index] = set2->array[index2];
            }
        }
    }

    while (index1 != set1->capacity)
    {
        if (set1->array[index1] != 0 && !(array_set_contains(dest, set1->array[index1])))
        {
            index = hash_address(set1->array[index1], dest->capacity);
            dest->array[index] = set1->array[index1++];
        }
    }

    while (index2 != set2->capacity)
    {
        if (set2->array[index2] != 0 && !(array_set_contains(dest, set1->array[index1])))
        {
            index = hash_address(set2->array[index2], dest->capacity);
            dest->array[index] = set2->array[index1++];
        }
    }
}

void array_set_intersect(array_set_t *dest, array_set_t *set1, array_set_t *set2)
{
    size_t index1 = 0, index2 = 0, index = 0;

    while (index1 <= set1->capacity && index2 != set2->capacity)
    {
        if (set1->array[index1] == 0)
        {
            index1++;
        }
        else if (set2->array[index2] == 0)
        {
            index2++;
        }
        else 
        {
            if (array_set_contains(set1, set2->array[index2]) && !array_set_contains(dest, set2->array[index2]))
            {
                index = hash_address(set2->array[set2->array[index2]], dest->capacity);
                dest->array[index] = set2->array[index2++];
            }
            else if (array_set_contains(set2, set1->array[index1]) && !array_set_contains(dest, set1->array[index1]))
            {
                index = hash_address(set1->array[set1->array[index1]], dest->capacity);
                dest->array[index] = set1->array[index1++];
            }
        }
    }
}

void array_set_diff(array_set_t *dest, array_set_t *set1, array_set_t *set2)
{
    size_t index1 = 0, index = 0;
    while (index <= set1->capacity)
    {
        if (set1->array[index1] == 0 || array_set_contains(set2, set1->array[index]))
        {
            index1++;
        }
        else
        {
            index = hash_address(hash(set1->array[index1]), dest->capacity);
            dest->array[index] = set1->array[index1++];
        }
    }
}

void array_set_sym_diff(array_set_t *dest, array_set_t *set1, array_set_t *set2)
{
    array_set_t* dest_aux = (array_set_t*)malloc(sizeof(array_set_t));
    dest_aux->capacity = dest->capacity;
    dest_aux->size = 0;
    array_set_init(dest_aux, dest->capacity);

    array_set_intersect(dest_aux, set1, set2);
    array_set_union(dest, set1, set2);
    array_set_diff(dest, dest, dest_aux);
}