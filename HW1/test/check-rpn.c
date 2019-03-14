/*
 * gcd/test/check-rpn.c --
 */

#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "../src/rpn.h"
#include "../src/rpn-stack.h"

/*
 * We introduce a simple data structure so that we can make test cases
 * for the rpn function data driven.
 */

typedef struct {
    char x[15];	/* input x */
    int r;	/* result r */
} abr_t;

START_TEST(test_rpn)
{
    abr_t tests[] = {
	{ "42", 0 },
	{ "2 3 +", 0 },
	{ "2 3 *", 0 },
	{ "6 2 /", 0 },
	{ "2 3 + 5 *", 0 },
	{ "word", -1 },
	{ "2 +", -2 },
	{ "2 4", -3 },
	{ "2 0 /", -4 }
    };

    char *res[] = {
        "42",
        "5",
        "6",
        "3",
        "25",
        "word",
        "None",
        "None",
        "None"
    };

    for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++) {
        char *t = "None";
        char **result = &t;

        printf("_________________________________");
        printf("\nRunning test: %s\n", tests[i].x);
        ck_assert_int_eq(rpn_eval_expr(tests[i].x, result), tests[i].r);
        printf("Test passed\n");
        ck_assert_str_eq(*result, res[i]);
        printf("Result passed\n");
    }
}
END_TEST

static Suite*
rpn_suite(void)
{
    Suite *s;
    TCase *tc_rpn;

    s = suite_create("all");
    tc_rpn = tcase_create("rpn");

    tcase_add_test(tc_rpn, test_rpn);
    suite_add_tcase(s, tc_rpn);
    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = rpn_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}