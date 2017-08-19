/**
* @file ooc_string_cunit_test.h
* @brief SetString class testing header file
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
int SetInitializeSuite();

/* 
 * Clean up test suite.
 * @return zero on success, non-zero otherwise.
 */
int SetCleanUpSuite();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableUninitializedCompleteObjectLocator();
 *
 * @brief	Tests string vf table uninitialized complete string locator  is pointing to NULL
 **************************************************************************************************/

void TestSetStringVFTableUninitializedCompleteObjectLocator();

/**********************************************************************************************//**
 * @fn	void TestSetStringNew();
 *
 * @brief	Tests string new
 * @warning	SetString is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void TestSetStringNew();

/**********************************************************************************************//**
 * @fn	void TestSetStringDelete();
 *
 * @brief	Tests string delete
 * @warning	SetString is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void TestSetStringDelete();

/**********************************************************************************************//**
 * @fn	void TestSetStringCopyConstructor();
 *
 * @brief	Tests string copy constructor
 **************************************************************************************************/

void TestSetStringCopyConstructor();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableEquals();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestSetStringVFTableEquals();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableNotSameSizeEquals();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestSetStringVFTableNotSameSizeEquals();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableNotEquals();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestSetStringVFTableNotEquals();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableCompareTo();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestSetStringVFTableCompareTo();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableNotSameSizeCompareTo();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestSetStringVFTableNotSameSizeCompareTo();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableNotCompareTo();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestSetStringVFTableNotCompareTo();


/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableToString();
 *
 * @brief	Tests string vf table SetStringToSetString  is pointing to the correct function
 **************************************************************************************************/

void TestSetStringVFTableToString();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableAdd();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestSetStringVFTableAdd();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableClear();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestSetStringVFTableClear();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableRemove();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestSetStringVFTableRemove();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableContains();
 *
 * @brief	Tests string vf table string add newly allocated.
 **************************************************************************************************/

void TestSetStringVFTableContains();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableNotContains();
 *
 * @brief	Tests string vf table string add newly allocated.
 **************************************************************************************************/

void TestSetStringVFTableNotContains();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableSetStringAddAlreadyAllocated();
 *
 * @brief	Tests string vf table string add already allocated.
 **************************************************************************************************/

void TestSetStringVFTableCopy();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableSetStringClear();
 *
 * @brief	Tests string vf table string clear statically allocated.
 **************************************************************************************************/

void TestSetStringVFTableIsEmpty();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableSize();
 *
 * @brief	Tests string vf table string clear dynamically allocated.
 **************************************************************************************************/

void TestSetStringVFTableSize();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableSet();
 *
 * @brief	Tests string vf table string remove.
 **************************************************************************************************/

void TestSetStringVFTableSet();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableMoveInsert();
 *
 * @brief	Tests string vf table string copy.
 **************************************************************************************************/

void TestSetStringVFTableMoveInsert();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableInsert();
 *
 * @brief	Tests string vf table string copy.
 **************************************************************************************************/

void TestSetStringVFTableInsert();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableFind();
 *
 * @brief	Tests string vf table string empty.
 **************************************************************************************************/

void TestSetStringVFTableFind();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableNPOSFind();
 *
 * @brief	Tests string vf table string empty.
 **************************************************************************************************/

void TestSetStringVFTableNPOSFind();

/**********************************************************************************************//**
 * @fn	void TestSetStringVFTableReplace();
 *	
 * @brief	Tests string vf table string size.
 **************************************************************************************************/

void TestSetStringVFTableReplace();

/**********************************************************************************************//**
 * @fn	void TestSetIterator();
 *	
 * @brief	Tests string vf table string size.
 **************************************************************************************************/

void TestSetIterator();
