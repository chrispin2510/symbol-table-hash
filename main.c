#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hash_set.h"
#include "skip_set.h"
#include "array_set.h"

#define TIME_DIFF ((double)(end-begin)/(double)CLOCKS_PER_SEC)

/*
 * Run a series of additions, removals, and containment checks.
 */
void run_benchmark(int input_size)
{
    char *fmt = "%-5s %-8s %10d %10f\n";

    // generate random numbers
    int *input = (int*)malloc(sizeof(int) * input_size * 10);
    for (int i=0; i<input_size; i++) {
        input[i] = rand() % input_size;
    }

    // initialize array and skip list
    array_set_t array_set;
    skip_set_t  skip_set;
    hash_set_t  hash_set;
    array_set_init(&array_set, (size_t)input_size);
//   skip_set_init (&skip_set, (size_t)input_size);
    hash_set_init (&hash_set);

    clock_t begin, end;
    printf("\n");

    //  test add method
    begin = clock();
    for (int i=0; i<input_size; i++) {
        array_set_add(&array_set, input[i]);
    }
    end = clock();
    printf(fmt, "ARRAY", "ADD", input_size, TIME_DIFF);
    //begin = clock();
    //for (int i=0; i<input_size; i++) {
        //skip_set_add(&skip_set, input[i]);
    //}
    //end = clock();
    //printf(fmt, "SKIP", "ADD", input_size, TIME_DIFF);
    begin = clock();
    for (int i=0; i<input_size; i++) {
        hash_set_add(&hash_set, input[i]);
    }
    end = clock();
    printf(fmt, "HASH", "ADD", input_size, TIME_DIFF);

    // test contains method
    begin = clock();
    for (int i=0; i<input_size; i++) {
        array_set_contains(&array_set, i);
    }
    end = clock();
    printf(fmt, "ARRAY", "CONTAINS", input_size, TIME_DIFF);
    //begin = clock();
    //for (int i=0; i<input_size; i++) {
        //skip_set_contains(&skip_set, i);
    //}
    //end = clock();
    //printf(fmt, "SKIP", "CONTAINS", input_size, TIME_DIFF);
    begin = clock();
    for (int i=0; i<input_size; i++) {
        hash_set_contains(&hash_set, i);
    }
    end = clock();
    printf(fmt, "HASH", "CONTAINS", input_size, TIME_DIFF);

    // free memory
    array_set_free(&array_set);
    //skip_set_free (&skip_set);
    hash_set_free (&hash_set);
    free(input);
}

int main()
{
    // seed random number generator
    srand((unsigned)time(0));

    run_benchmark(1000);
    run_benchmark(10000);
    run_benchmark(100000);
    run_benchmark(1000000);

    return EXIT_SUCCESS;
}

