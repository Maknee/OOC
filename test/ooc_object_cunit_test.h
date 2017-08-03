#pragma once

#include "CUnit/Automated.h"
#include "CUnit/Basic.h"
#include "../src/object.h"

/*
 * Initialise test suite.
 * @return zero on success, non-zero otherwise.
 */
int ObjectInitializeSuite();

/* 
 * Clean up test suite.
 * @return zero on success, non-zero otherwise.
 */
int ObjectCleanUpSuite();

/**********************************************************************************************//**
 * @fn	void TestObjectVFTableUninitializedCompleteObjectLocator();
 *
 * @brief	Tests object vf table uninitialized complete object locator  is pointing to NULL
 **************************************************************************************************/

void TestObjectVFTableUninitializedCompleteObjectLocator();

/**********************************************************************************************//**
 * @fn	void TestObjectVFTableInitializedCompleteObjectLocator();
 *
 * @brief	Tests object vf table initialized complete object locator is pointing to the correct struct
 **************************************************************************************************/

void TestObjectVFTableInitializedCompleteObjectLocator();

/**********************************************************************************************//**
 * @fn	void TestObjectVFTableEquals();
 *
 * @brief	Tests object vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestObjectVFTableEquals();

/**********************************************************************************************//**
 * @fn	void TestObjectVFTableObjectToString();
 *
 * @brief	Tests object vf table ObjectToString  is pointing to the correct function
 **************************************************************************************************/

void TestObjectVFTableObjectToString();



