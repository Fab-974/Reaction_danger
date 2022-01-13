#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "danger.h"

#include "CUnit.h"
#include "Basic.h"

/* Test Suite setup and cleanup functions: */

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }



/************* Test case functions ****************/

void danger_test_1(void)
{
    struct coordonnee c1 = {45, 60, 4};
    struct CSC_rep csc1 = Chassy_safety_controller(25, 0, 60, c1);
    struct CSC_rep csc2 = Chassy_safety_controller(60, 0, 60, c1);
    CU_ASSERT_EQUAL(csc1.danger.envoye, 1);
    CU_ASSERT_NOT_EQUAL(csc1.danger.envoye, 0);
    CU_ASSERT_EQUAL(csc2.danger.envoye, 0);
    CU_ASSERT_NOT_EQUAL(csc2.danger.envoye, 1);
}

void danger_test_2(void)
{
    struct coordonnee c1 = {45, 60, 4};
    struct CSC_rep csc1 = Chassy_safety_controller(25, 0, 60, c1);
    struct CSC_rep csc2 = Chassy_safety_controller(60, 0, 60, c1);
    CU_ASSERT_EQUAL(csc1.act, freinage);
    CU_ASSERT_EQUAL(csc2.act, deceleration);
}

void danger_test_3(void)
{
    struct coordonnee c1 = {45, 60, 4};
    struct CSC_rep csc1 = Chassy_safety_controller(25, 0, 60, c1);
    struct CSC_rep csc2 = Chassy_safety_controller(60, 0, 60, c1);
    // Failed surement probleme de typage float/double
    CU_ASSERT(csc1.danger.vitesse < (float)60);
    CU_ASSERT_EQUAL(csc2.danger.vitesse, (float)60.0);
}

void danger_test_4(void)
{
    struct coordonnee c1 = {45, 60, 4};
    struct CSC_rep csc1 = Chassy_safety_controller(25, 0, 60, c1);
    CU_ASSERT_EQUAL(csc1.danger.priorite, 1);
}

/************* Test Runner Code goes here **************/

int main(void)
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    /* add a suite to the registry */
    pSuite = CU_add_suite("danger_test_suite", init_suite, clean_suite);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /* add the tests to the suite */
    if ((NULL == CU_add_test(pSuite, "danger_test_1", danger_test_1)) ||
        (NULL == CU_add_test(pSuite, "danger_test_2", danger_test_2)) ||
        (NULL == CU_add_test(pSuite, "danger_test_3", danger_test_3)) ||
        (NULL == CU_add_test(pSuite, "danger_test_4", danger_test_4)))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run all tests using the basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    printf("\n");
    CU_basic_show_failures(CU_get_failure_list());
    printf("\n\n");
    /*
       // Run all tests using the automated interface
       CU_automated_run_tests();
       CU_list_tests_to_file();

       // Run all tests using the console interface
       CU_console_run_tests();
    */
    /* Clean up registry and return */
    CU_cleanup_registry();
    return CU_get_error();
}
