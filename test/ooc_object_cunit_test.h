#pragma once

#include "CUnit/Automated.h"
#include "CUnit/Basic.h"
#include "../src/object.h"

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

//object vftable tests

void TestObjectVFTableCompleteObjectLocator();

void TestObjectVFTableEquals();

void TestObjectVFTableObjectToString();



