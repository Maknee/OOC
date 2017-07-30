#include "ooc_cunit_test.h"

int initialise_suite(void)
{
   return 0;
}

int cleanup_suite(void)
{
    return 0;
}

void test_fibonacci_1(void)
{
    CU_ASSERT_EQUAL(1, 1);
}

void test_fibonacci_2(void)
{
    CU_ASSERT_EQUAL(1, 1);
}

void test_fibonacci_3(void)
{
    CU_ASSERT_EQUAL(2, 2);
}

void test_fibonacci_30(void)
{
    CU_ASSERT_EQUAL(30, 30);
}
