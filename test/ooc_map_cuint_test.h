/**
* @file ooc_string_cunit_test.h
* @brief MapString class testing header file
*
* @date	8/4/2017
*/

#pragma once

#define OOC_V1

#include "CUnit/Automated.h"
#include "CUnit/Basic.h"
#include "../src/ooc.h"

/*
 * Initialise test suite.
 * @return zero on success, non-zero otherwise.
 */
int MapInitializeSuite();

/* 
 * Clean up test suite.
 * @return zero on success, non-zero otherwise.
 */
int MapCleanUpSuite();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableUninitializedCompleteObjectLocator();
 *
 * @brief	Tests string vf table uninitialized complete string locator  is pointing to NULL
 **************************************************************************************************/

void TestMapStringVFTableUninitializedCompleteObjectLocator();

/**********************************************************************************************//**
 * @fn	void TestMapStringNew();
 *
 * @brief	Tests string new
 * @warning	MapString is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void TestMapStringNew();

/**********************************************************************************************//**
 * @fn	void TestMapStringDelete();
 *
 * @brief	Tests string delete
 * @warning	MapString is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void TestMapStringDelete();

/**********************************************************************************************//**
 * @fn	void TestMapStringCopyConstructor();
 *
 * @brief	Tests string copy constructor
 **************************************************************************************************/

void TestMapStringCopyConstructor();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableEquals();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestMapStringVFTableEquals();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableNotSameSizeEquals();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestMapStringVFTableNotSameSizeEquals();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableNotEquals();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestMapStringVFTableNotEquals();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableCompareTo();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestMapStringVFTableCompareTo();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableNotSameSizeCompareTo();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestMapStringVFTableNotSameSizeCompareTo();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableNotCompareTo();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestMapStringVFTableNotCompareTo();


/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableToString();
 *
 * @brief	Tests string vf table MapStringToMapString  is pointing to the correct function
 **************************************************************************************************/

void TestMapStringVFTableToString();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableAdd();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestMapStringVFTableAdd();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableClear();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestMapStringVFTableClear();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableRemove();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestMapStringVFTableRemove();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableRemoveLots();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestMapStringVFTableRemoveLots();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableContains();
 *
 * @brief	Tests string vf table string add newly allocated.
 **************************************************************************************************/

void TestMapStringVFTableContains();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableNotContains();
 *
 * @brief	Tests string vf table string add newly allocated.
 **************************************************************************************************/

void TestMapStringVFTableNotContains();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableMapStringAddAlreadyAllocated();
 *
 * @brief	Tests string vf table string add already allocated.
 **************************************************************************************************/

void TestMapStringVFTableCopy();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableMapStringClear();
 *
 * @brief	Tests string vf table string clear statically allocated.
 **************************************************************************************************/

void TestMapStringVFTableIsEmpty();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableSize();
 *
 * @brief	Tests string vf table string clear dynamically allocated.
 **************************************************************************************************/

void TestMapStringVFTableSize();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableMap();
 *
 * @brief	Tests string vf table string remove.
 **************************************************************************************************/

void TestMapStringVFTableSet();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableMoveInsert();
 *
 * @brief	Tests string vf table string copy.
 **************************************************************************************************/

void TestMapStringVFTableMoveInsert();

void TestMapStringVFTableMoveInsertLots();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableInsert();
 *
 * @brief	Tests string vf table string copy.
 **************************************************************************************************/

void TestMapStringVFTableInsert();

void TestMapStringVFTableInsertLots();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableFind();
 *
 * @brief	Tests string vf table string empty.
 **************************************************************************************************/

void TestMapStringVFTableFind();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableNPOSFind();
 *
 * @brief	Tests string vf table string empty.
 **************************************************************************************************/

void TestMapStringVFTableNPOSFind();

/**********************************************************************************************//**
 * @fn	void TestMapStringVFTableReplace();
 *	
 * @brief	Tests string vf table string size.
 **************************************************************************************************/

void TestMapStringVFTableReplace();

/**********************************************************************************************//**
 * @fn	void TestMapIterator();
 *	
 * @brief	Tests string vf table string size.
 **************************************************************************************************/

void TestMapIterator();
