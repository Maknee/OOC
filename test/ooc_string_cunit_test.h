/**
* @file ooc_string_cunit_test.h
* @brief String class testing header file
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
int StringInitializeSuite();

/* 
 * Clean up test suite.
 * @return zero on success, non-zero otherwise.
 */
int StringCleanUpSuite();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableUninitializedCompleteObjectLocator();
 *
 * @brief	Tests string vf table uninitialized complete string locator  is pointing to NULL
 **************************************************************************************************/

void TestStringVFTableUninitializedCompleteObjectLocator();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableInitializedCompleteObjectLocator();
 *
 * @brief	Tests string vf table initialized complete string locator  is pointing to NULL
 **************************************************************************************************/

void TestStringVFTableInitializedCompleteObjectLocator();

/**********************************************************************************************//**
 * @fn	void TestStringNew();
 *
 * @brief	Tests string new
 * @warning	String is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void TestStringNew();

/**********************************************************************************************//**
 * @fn	void TestStringDelete();
 *
 * @brief	Tests string delete
 * @warning	String is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void TestStringDelete();

/**********************************************************************************************//**
 * @fn	void TestStringConstructor();
 *
 * @brief	Tests string constructor
 **************************************************************************************************/

void TestStringConstructor();

/**********************************************************************************************//**
 * @fn	void TestStringCopyConstructor();
 *
 * @brief	Tests string copy constructor
 **************************************************************************************************/

void TestStringCopyConstructor();

/**********************************************************************************************//**
 * @fn	void TestStringdestructor();
 *
 * @brief	Tests string destructor
 **************************************************************************************************/

void TestStringDestructor();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringToString();
 *
 * @brief	Tests string vf table StringToString  is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableStringToString();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableEquals();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableEquals();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringToString();
 *
 * @brief	Tests string vf table StringToString  is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableStringToString();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringSet();
 *
 * @brief	Tests string vf table StringSet is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableStringSet();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringC_Str();
 *
 * @brief	Tests string vf table StringC_Str is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableStringC_Str();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringAppend();
 *
 * @brief	Tests string vf table StringAppend is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableStringAppend();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringFind();
 *
 * @brief	Tests string vf table StringFind is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableStringFind();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringSubString();
 *
 * @brief	Tests string vf table SubString is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableStringSubString();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringSubString();
 *
 * @brief	Tests string vf table SubString is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableStringSubString();
