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
int VectorStringInitializeSuite();

/* 
 * Clean up test suite.
 * @return zero on success, non-zero otherwise.
 */
int VectorStringCleanUpSuite();

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
 * @fn	void TestVectorStringVFTableVectorStringAddSecondAllocatedFirstNot();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringAddSecondAllocatedFirstNot();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringAddAllocated();
 *
 * @brief	Tests string vf table string add newly allocated.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringAddAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringAddAlreadyAllocated();
 *
 * @brief	Tests string vf table string add already allocated.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringAddAlreadyAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringClear();
 *
 * @brief	Tests string vf table string clear statically allocated.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringClear();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringClearAllocated();
 *
 * @brief	Tests string vf table string clear dynamically allocated.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringClearAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringRemove();
 *
 * @brief	Tests string vf table string remove.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringRemove();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringRemoveAllocated();
 *
 * @brief	Tests string vf table string remove allocated
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringRemoveAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringRemoveNPOS();
 *
 * @brief	Tests string vf table string remove npos
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringRemoveNPOS();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringContains();
 *
 * @brief	Tests string vf table string contains.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringContains();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringCopy();
 *
 * @brief	Tests string vf table string copy.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringCopy();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringCopyAllocated();
 *
 * @brief	Tests string vf table string copy.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringCopyAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringIsEmpty();
 *
 * @brief	Tests string vf table string empty.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringIsEmpty();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringSize();
 *
 * @brief	Tests string vf table string size.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringSize();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringSet();
 *
 * @brief	Tests string vf table VectorStringSet with statically allocated string
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringSet();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringSetAllocated();
 *
 * @brief	Tests string vf table VectorStringSet with newly allocated string
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringSetAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringSetAlreadyAllocated();
 *
 * @brief	Tests string vf table VectorStringSet with newly allocated string
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringSetAlreadyAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringC_Str();
 *
 * @brief	Tests string vf table VectorStringC_Str is pointing to the correct function
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringC_Str();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringAppend();
 *
 * @brief	Tests string vf table VectorStringAppend static
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringAppend();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringAppendAllocated();
 *
 * @brief	Tests string vf table VectorStringAppend newly allocated
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringAppendAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringAppendAlreadyAllocated();
 *
 * @brief	Tests string vf table VectorStringAppend already allocated
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringAppendAlreadyAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringInsert();
 *
 * @brief	Tests string vf table VectorStringInsert static
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringInsert();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringInsert();
 *
 * @brief	Tests string vf table VectorStringInsert static
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringInsert();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringInsertAllocated();
 *
 * @brief	Tests string vf table VectorStringInsert newly allocated
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringInsertAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringInsertOtherVectorStringAllocated();
 *
 * @brief	Tests string vf table VectorStringInsert newly allocated other string
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringInsertOtherVectorStringAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringInsertOtherVectorStringAllocatedNewlyAllocated();
 *
 * @brief	Tests string vf table VectorStringInsert newly allocated other string
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringInsertOtherVectorStringAllocatedNewlyAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringInsertAlreadyAllocated();
 *
 * @brief	Tests string vf table VectorStringInsert already allocated
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringInsertAlreadyAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringInsertAlreadyAllocatedInsertionVectorStringAllocated();
 *
 * @brief	Tests string vf table VectorStringInsert already allocated
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringInsertAlreadyAllocatedInsertionVectorStringAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringInsertOutOfBounds();
 *
 * @brief	Tests string vf table VectorStringInsert out of bounds
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringInsertOutOfBounds();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringInsertNPOS();
 *
 * @brief	Tests string vf table VectorStringInsert npos
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringInsertNPOS();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringReplace();
 *
 * @brief	Tests string vf table string replace.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringReplace();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringReplaceAllocated();
 *
 * @brief	Tests string vf table string replace.
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringReplaceAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringFind();
 *
 * @brief	Tests string vf table VectorStringFind haystack - static | needle - static
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringFind();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringFindHayStackAllocated();
 *
 * @brief	Tests string vf table VectorStringFind haystack - allocated | needle - static
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringFindHayStackAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringFindNeedleAllocated();
 *
 * @brief	Tests string vf table VectorStringFind haystack - static | needle - allocated
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringFindNeedleAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringFindHayStackAllocatedNeedleAllocated();
 *
 * @brief	Tests string vf table VectorStringFind haystack - allocated | needle - allocated
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringFindHayStackAllocatedNeedleAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringFindNull();
 *
 * @brief	Tests string vf table VectorStringFind with a not found string
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringFindNull();


/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringSubVectorString();
 *
 * @brief	Tests string vf table SubVectorString is pointing to the correct function
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringSubVectorString();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringSubVectorStringAllocated();
 *
 * @brief	Tests string vf table SubVectorString is pointing to the correct function
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringSubVectorStringAllocated();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringSubVectorStringLessThanZero();
 *
 * @brief	Tests string vf table SubVectorString for user mistakes like < 0
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringSubVectorStringLessThanZero();

/**********************************************************************************************//**
 * @fn	void TestVectorStringVFTableVectorStringSubVectorStringOutOfBounds();
 *
 * @brief	Tests string vf table SubVectorString for user mistakes like out of bounds
 **************************************************************************************************/

void TestVectorStringVFTableVectorStringSubVectorStringOutOfBounds();
