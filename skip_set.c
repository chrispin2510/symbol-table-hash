/*
 * skip_set.c
 *
 * Name: 
 */

#include "skip_set.h"

void skip_set_init(skip_set_t *set, size_t max_height)
{
    set = (skip_set_t*)malloc(sizeof(skip_set_t));
    set->head = (skip_node_t*)malloc(sizeof(skip_node_t));
    set->max_height = max_height;
    set->size = 0;
}

void skip_set_clear(skip_set_t *set)
{
    skip_node_t* curr;

    if (set != NULL)
    {
        if (set->head != NULL)
        {
            curr = set->head;
            while (curr != NULL)
            {
                curr->data = 0;
                curr->height = 0;
                curr = curr->next;
            }
        }
    }
    set->size = 0;
}

size_t skip_set_size(skip_set_t *set)
{
    return set->size;
}

void skip_set_free(skip_set_t *set)
{
    skip_node_t* curr, *temp;

    if (set != NULL)
    {
        if (set->head != NULL)
        {
            curr = set->head;
            while (curr != NULL)
            {
                temp = curr;
                curr = curr->next;
                free(temp);
            }
        }
    }
    set->head = NULL;
    set->max_height = 0;
    set->size = 0;
    free(set);
    set = NULL;
}

void skip_set_add(skip_set_t *set, data_t value)
{
    skip_node_t *curr;
    skip_node_t *new_skip_node = (skip_node_t*)malloc(sizeof(skip_node_t));
    new_skip_node->data = value;

    if (set->head == NULL)
    {
        new_skip_node->next = NULL;
        set->head = new_skip_node;
        set->size++;
    }
    else
    {
        curr = set->head;
        while (curr->next != NULL && curr->data != value)
        {
            curr = curr->next;
        }
        if (curr->next == NULL)
        {
            new_skip_node->next = NULL;
            curr->next = new_skip_node;
        }
    }
}

void skip_set_remove(skip_set_t *set, data_t value)
{
    skip_node_t *curr, *prev;
    if (set != NULL)
    {
        if (set->head != NULL)
        {
            prev = NULL;
            curr = set->head;
            while (curr->next != NULL && curr->data != value)
            {
                prev = curr;
                curr = curr->next; 
            }
            prev->next = curr->next; 
            free(curr);
            set->size--;
        }
    }
}

data_t skip_set_pop(skip_set_t *set)
{
    skip_node_t *temp;
    data_t value;

    if (set != NULL)
    {
        if (set->head != NULL)
        {
            temp = set->head;
            set->head = set->head->next;
            value = temp->data;
            free(temp);
            set->size--;
        }
    }
    return value;
}

bool skip_set_contains(skip_set_t *set, data_t value)
{
    skip_node_t *curr;
    bool flag = true;

    if (set != NULL)
    {
        if (set->head != NULL)
        {
            curr = set->head;
            while (curr != NULL && curr->data != value)
            {
                curr = curr->next;
            }
            if (curr == NULL)
            {
                flag = false;
            }
        }
    }
    return flag;
}

skip_set_iter_t skip_set_begin(skip_set_t *set)
{
    if (set != NULL)
    {
        return set->head;
    }
}

skip_set_iter_t skip_set_end(skip_set_t *set)
{
    skip_node_t *curr;

    if (set != NULL)
    {
        if (set->head != NULL)
        {
            curr = set->head;
            while (curr->next != NULL)
            {
                curr = curr->next;
            }
        }
        else 
        {
            curr = NULL;
        }
    }
    return curr;
}

skip_set_iter_t skip_set_next(skip_set_iter_t iter)
{
    return iter->next;
}

bool skip_set_is_subset(skip_set_t *set1, skip_set_t *set2)
{
    bool flag = true;
    skip_node_t *curr;

    if  (set1 && set2 && set1->size <= set2->size)
    {
        if (set1->head && set2->head)
        {
            curr = set1->head;
            while (curr != NULL && flag == true)
            {
                if (!skip_set_contains(set2, curr->data))
                {
                    flag = false; 
                }
                curr = curr->next;
            }
        }

    }
    return flag;
}

bool skip_set_is_superset(skip_set_t *set1, skip_set_t *set2)
{
    bool flag = true;
    skip_node_t *curr;

    if (set1 && set2 && set1->size >= set2->size)
    {
        if (set1->head && set2->head)
        {
            curr = set2->head;
            while (curr != NULL && flag == true)
            {
                if (!skip_set_contains(set1, curr->data))
                {
                    flag = false;
                }
                curr = curr->next;
            }
        }
    }
    return flag;
}

bool skip_set_is_equal(skip_set_t *set1, skip_set_t *set2)
{
    bool flag = true;
    skip_node_t *curr1, *curr2;
    
    if (set1->size != set2->size)
    {
        flag = false;
    }   
    else 
    {
        curr1 = set1->head;
        curr2 = set2->head;
        while (curr1 && curr2) 
        {
            if (!skip_set_contains(set1, curr2->data) ||
                !skip_set_contains(set2, curr1->data))
                {
                    flag = false;
                }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
    }
    return flag;
}

bool skip_set_is_disjoint(skip_set_t *set1, skip_set_t *set2)
{
    bool flag = true;
    skip_node_t *curr1, *curr2;

    if (set1 && set2)
    {
        curr1 = set1->head;
        curr2 = set2->head;

        while (curr1 != NULL && curr2 != NULL)
        {
            if (skip_set_contains(set1, curr2->data) ||
            skip_set_contains(set2, curr1->data))
            {
                flag = false;
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
    }
    return flag;
}


void skip_set_copy(skip_set_t *dest, skip_set_t *src)
{
    skip_node_t *curr;

    if (src && src->head)
    {
        dest->head = src->head;
        dest->size = src->size;
    }
}

void skip_set_union(skip_set_t *dest, skip_set_t *set1, skip_set_t *set2)
{
    skip_node_t *curr1, *curr2;
    
    if (set1 && set2 && set1->head && set2->head)
    {
        curr1 = set1->head;
        curr2 = set2->head;

        while (curr1 != NULL && curr2 != NULL)
        {
            if (!skip_set_contains(dest, curr1->data))
            {
                skip_set_add(dest, curr1->data);
                curr1 = curr1->next;
            }
            else if (!skip_set_contains(dest, curr2->data))
            {
                skip_set_add(dest, curr2->data);
                curr2 = curr2->next;
            }
        }
        if (curr1 != NULL)
        {
            while (curr1 != NULL)
            {
                if (!skip_set_contains(dest, curr1->data))
                {
                    skip_set_add(dest, curr1->data);
                    curr1 = curr1->next;
                }
            }
        }
        if (curr2 != NULL)
        {
            while (curr2 != NULL)
            {
                if (!skip_set_contains(dest, curr2->data))
                {
                    skip_set_add(dest, curr2->data);
                    curr2 = curr2->next;
                }
            }
        }
    }
}

void skip_set_intersect(skip_set_t *dest, skip_set_t *set1, skip_set_t *set2)
{
    skip_node_t *curr1, *curr2;

    if (set1 && set2 && set1->head && set2->head)
    {
        curr1 = set1->head;
        curr2 = set2->head;
        while (curr1 != NULL && curr2 != NULL)
        {
            if (skip_set_contains(set1, curr2->data) && !skip_set_contains(dest, curr2->data))
            {
                skip_set_add(dest, curr2->data);
                dest->size++;
            }
            if (skip_set_contains(set2, curr1->data) && !skip_set_contains(dest, curr1->data))
            {
                skip_set_add(dest, curr1->data);
                dest->size++;
            }
            curr1 = curr1->next;
            curr2 = curr2->next;
        }
    }
}

void skip_set_diff(skip_set_t *dest, skip_set_t *set1, skip_set_t *set2)
{
    skip_node_t *curr;

    if (set1 && set2 && set1->head && set2->head)
    {
        curr = set1->head;
        while (curr != NULL)
        {
            if (!skip_set_contains(set2, curr->data) && !skip_set_contains(dest, curr->data))
            {
                skip_set_add(dest, curr->data);
                dest->size++;
            }
            curr = curr->next;
        }
    }
}

void skip_set_sym_diff(skip_set_t *dest, skip_set_t *set1, skip_set_t *set2)
{
    skip_set_t *aux;
    skip_set_init(aux, dest->max_height);

    skip_set_intersect(aux, set1, set2);
    skip_set_union(dest, set1, set2);
    skip_set_diff(dest, dest, aux);
}