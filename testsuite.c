#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "hash_set.h"

/*
 * Print the contents of a set.
 */
void print_set(hash_set_t *set)
{
    bool print_comma = false;
    printf("[ ");
    for (size_t i=0; i < set->capacity; i++) {
        if (print_comma) {
            printf(", ");
        } else {
            print_comma = true;
        }
        if (!set->table[i].is_empty) {
            printf("%d", set->table[i].value);
        } else {
            printf("_");
        }
        bucket_t *b = set->table[i].next;
        while (b != NULL) {
            printf("->%d", b->value);
            b = b->next;
        }
    }
    printf(" ]\n");
}

START_TEST (test_hash_set)
{
    hash_set_t set1;
    hash_set_init(&set1);
    print_set(&set1);
    for (int i=1; i<10; i+=2) {
        hash_set_add(&set1, i);
        print_set(&set1);
    }
    printf("contains 1? %s\n", (hash_set_contains(&set1, 1) ? "yes" : "no"));
    printf("contains 2? %s\n", (hash_set_contains(&set1, 2) ? "yes" : "no"));
    printf("contains 4? %s\n", (hash_set_contains(&set1, 4) ? "yes" : "no"));
    printf("contains 5? %s\n", (hash_set_contains(&set1, 5) ? "yes" : "no"));
    printf("contains 8? %s\n", (hash_set_contains(&set1, 8) ? "yes" : "no"));
    printf("contains 9? %s\n", (hash_set_contains(&set1, 9) ? "yes" : "no"));
    ck_assert_int_eq(hash_set_contains(&set1, 1), (int)true);
    ck_assert_int_eq(hash_set_contains(&set1, 2), (int)false);
    ck_assert_int_eq(hash_set_contains(&set1, 4), (int)false);
    ck_assert_int_eq(hash_set_contains(&set1, 5), (int)true);
    ck_assert_int_eq(hash_set_contains(&set1, 8), (int)false);
    ck_assert_int_eq(hash_set_contains(&set1, 9), (int)true);
}
END_TEST

/** GENERIC TEST SUITE CODE **/

Suite * test_suite(void)
{
    Suite *s;
    TCase *tc_core;
    s = suite_create("Default");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_hash_set);

    suite_add_tcase(s, tc_core);
    return s;
}

int run_testsuite()
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    if (number_failed == 0) {
        printf("SUCCESS: All current tests passed!\n");
    } else {
        printf("FAILURE: At least one test failed or crashed.\n");
    }

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

int main(int argc, char* argv[])
{
    return run_testsuite();
}

