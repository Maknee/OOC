#pragma once

#include "CUnit/Automated.h"
#include "CUnit/Basic.h"
#include "ooc.h"

/*
 * Initialise test suite.
 * @return zero on success, non-zero otherwise.
 */
int initialise_suite(void);

/* 
 * Clean up test suite.
 * @return zero on success, non-zero otherwise.
 */
int cleanup_suite(void);

/* 
 * Test fibonacci(1).
 */
void test_fibonacci_1(void);

/* 
 * Test fibonacci(2).
 */
void test_fibonacci_2(void);

/* 
 * Test fibonacci(3).
 */
void test_fibonacci_3(void);

/* 
 * Test fibonacci(30).
 */
void test_fibonacci_30(void);

