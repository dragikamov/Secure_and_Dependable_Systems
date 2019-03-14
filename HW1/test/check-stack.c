/*
 * gcd/test/check-stack.c --
 */

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "../src/rpn.h"
#include "../src/rpn-stack.h"

START_TEST(my_test)
{
    rpn_stack_t *a = rpn_stack_new();
    ck_assert(a != NULL);

    int arr[4] = {39, 2, 10 ,15};

    printf("________________________________________________\n");
    printf("Running test: rpn_stack_push and rpn_stack_peek\n");
    rpn_stack_push(a, &(arr[0]));
    ck_assert(arr[0] == *(int *)rpn_stack_peek(a));
    printf("Test passed\n");

    printf("________________________________________________\n");
    printf("Running test: rpn_stack_push and rpn_stack_peek\n");
    rpn_stack_push(a, &(arr[1]));
    ck_assert(arr[1] == *(int*)rpn_stack_peek(a));
    printf("Test passed\n");

    printf("________________________________________________\n");
    printf("Running test: rpn_stack_push and rpn_stack_peek\n");
    rpn_stack_push(a, &(arr[2]));
    ck_assert(arr[2] == *(int *)rpn_stack_peek(a));
    printf("Test passed\n");

    printf("________________________________________________\n");
    printf("Running test: rpn_stack_pop\n");
    ck_assert(arr[2] == *(int *)rpn_stack_pop(a));
    printf("Test passed\n");

    printf("________________________________________________\n");
    printf("Running test: rpn_stack_push and rpn_stack_peek\n");
    ck_assert(0 == rpn_stack_empty(a));
    printf("Test passed\n");

    printf("________________________________________________\n");
    printf("Running test: rpn_stack_pop\n");
    ck_assert(arr[1] == *(int *)rpn_stack_pop(a));
    printf("Test passed\n");

    printf("________________________________________________\n");
    printf("Running test: rpn_stack_pop\n");
    ck_assert(arr[0] == *(int *)rpn_stack_pop(a));
    printf("Test passed\n");

    printf("________________________________________________\n");
    printf("Running test: rpn_stack_empty\n");
    ck_assert(1 == rpn_stack_empty(a));
    printf("Test passed\n");

    rpn_stack_del(a);
}
END_TEST


static Suite*
gdb_suite(void)
{
    Suite *s;
    TCase *tc_stack;

    s = suite_create("all");
    tc_stack = tcase_create("rpn-stack-check-testcase");

    tcase_add_test(tc_stack, my_test);
    suite_add_tcase(s, tc_stack);
    return s;
}


int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = gdb_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
