/**
* @file ooc_string_cunit_test.h
* @brief VectorString class testing header file
*
* @date	8/4/2017
*/

#pragma once

#include "CUnit/Automated.h"
#include "CUnit/Basic.h"
#include "../src/ooc.h"

/*
 * Initialise test suite.
 * @return zero on success, non-zero otherwise.
 */
int CastsInitializeSuite();

/* 
 * Clean up test suite.
 * @return zero on success, non-zero otherwise.
 */
int CastsCleanUpSuite();

/**********************************************************************************************//**
 * @fn	void TestValidUpcast();
 *	
 * @brief	Tests if an object can be upcasted to a valid type
 **************************************************************************************************/

void TestValidUpcast();

/**********************************************************************************************//**
 * @fn	void TestValidDowncast();
 *	
 * @brief	Tests if an object can be downcasted to a valid type
 **************************************************************************************************/

void TestValidDowncast();

/**********************************************************************************************//**
 * @fn	void TestInvalidDowncast();
 *	
 * @brief	Tests if an object can be downcasted to a valid type
 **************************************************************************************************/

void TestInvalidDowncast();

/**********************************************************************************************//**
 * @fn	void TestMoveSemantics();
 *	
 * @brief	Tests if an object can be downcasted to a valid type
 **************************************************************************************************/

void TestMoveSemantics();
