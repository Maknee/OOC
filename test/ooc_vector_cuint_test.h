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
int VectorInitializeSuite();

/* 
 * Clean up test suite.
 * @return zero on success, non-zero otherwise.
 */
int VectorCleanUpSuite();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableUninitializedCompleteObjectLocator();
 *
 * @brief	Tests string vf table uninitialized complete string locator  is pointing to NULL
 **************************************************************************************************/

void TestVectorStringVFTableUninitializedCompleteObjectLocator();

/**********************************************************************************************//**
 * @fn	void TestVectorStringNew();
 *
 * @brief	Tests string new
 * @warning	VectorString is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void TestVectorStringNew();

/**********************************************************************************************//**
 * @fn	void TestVectorStringDelete();
 *
 * @brief	Tests string delete
 * @warning	VectorString is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void TestVectorStringDelete();

/**********************************************************************************************//**
 * @fn	void TestVectorStringCopyConstructor();
 *
 * @brief	Tests string copy constructor
 **************************************************************************************************/

void TestVectorStringCopyConstructor();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableEquals();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestVectorStringVFTableEquals();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableNotSameSizeEquals();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestVectorStringVFTableNotSameSizeEquals();


/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableNotEquals();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestVectorStringVFTableNotEquals();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableToString();
 *
 * @brief	Tests string vf table VectorStringToVectorString  is pointing to the correct function
 **************************************************************************************************/

void TestVectorStringVFTableToString();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableAdd();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestVectorStringVFTableAdd();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableClear();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestVectorStringVFTableClear();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableRemove();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestVectorStringVFTableRemove();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableContains();
 *
 * @brief	Tests string vf table string add newly allocated.
 **************************************************************************************************/

void TestVectorStringVFTableContains();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringAddAlreadyAllocated();
 *
 * @brief	Tests string vf table string add already allocated.
 **************************************************************************************************/

void TestVectorStringVFTableCopy();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringClear();
 *
 * @brief	Tests string vf table string clear statically allocated.
 **************************************************************************************************/

void TestVectorStringVFTableIsEmpty();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableSize();
 *
 * @brief	Tests string vf table string clear dynamically allocated.
 **************************************************************************************************/

void TestVectorStringVFTableSize();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableSet();
 *
 * @brief	Tests string vf table string remove.
 **************************************************************************************************/

void TestVectorStringVFTableSet();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableGet();
 *
 * @brief	Tests string vf table string remove allocated
 **************************************************************************************************/

void TestVectorStringVFTableGet();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTablePushFront();
 *
 * @brief	Tests string vf table string remove npos
 **************************************************************************************************/

void TestVectorStringVFTablePushFront();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTablePushBack();
 *
 * @brief	Tests string vf table string contains.
 **************************************************************************************************/

void TestVectorStringVFTablePushBack();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableInsert();
 *
 * @brief	Tests string vf table string copy.
 **************************************************************************************************/

void TestVectorStringVFTableInsert();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableInsertOutOfBounds();
 *
 * @brief	Tests string vf table string copy.
 **************************************************************************************************/

void TestVectorStringVFTableInsertOutOfBounds();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableFind();
 *
 * @brief	Tests string vf table string empty.
 **************************************************************************************************/

void TestVectorStringVFTableFind();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableReplace();
 *	
 * @brief	Tests string vf table string size.
 **************************************************************************************************/

void TestVectorStringVFTableReplace();

