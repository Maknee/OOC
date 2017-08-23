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
 * @fn	void TestStringDestructor();
 *
 * @brief	Tests string destructor
 **************************************************************************************************/

void TestStringDestructor();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableEquals();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableEquals();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableCompareTo();
 *
 * @brief	Tests string vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableCompareTo();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringToString();
 *
 * @brief	Tests string vf table StringToString  is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableStringToString();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringAdd();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestStringVFTableStringAdd();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringAddFirstAllocatedSecondNot();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestStringVFTableStringAddFirstAllocatedSecondNot();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringAddSecondAllocatedFirstNot();
 *
 * @brief	Tests string vf table string add statically allocated.
 **************************************************************************************************/

void TestStringVFTableStringAddSecondAllocatedFirstNot();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringAddAllocated();
 *
 * @brief	Tests string vf table string add newly allocated.
 **************************************************************************************************/

void TestStringVFTableStringAddAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringAddAlreadyAllocated();
 *
 * @brief	Tests string vf table string add already allocated.
 **************************************************************************************************/

void TestStringVFTableStringAddAlreadyAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringClear();
 *
 * @brief	Tests string vf table string clear statically allocated.
 **************************************************************************************************/

void TestStringVFTableStringClear();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringClearAllocated();
 *
 * @brief	Tests string vf table string clear dynamically allocated.
 **************************************************************************************************/

void TestStringVFTableStringClearAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringRemove();
 *
 * @brief	Tests string vf table string remove.
 **************************************************************************************************/

void TestStringVFTableStringRemove();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringRemoveAllocated();
 *
 * @brief	Tests string vf table string remove allocated
 **************************************************************************************************/

void TestStringVFTableStringRemoveAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringRemoveNPOS();
 *
 * @brief	Tests string vf table string remove npos
 **************************************************************************************************/

void TestStringVFTableStringRemoveNPOS();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringContains();
 *
 * @brief	Tests string vf table string contains.
 **************************************************************************************************/

void TestStringVFTableStringContains();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringCopy();
 *
 * @brief	Tests string vf table string copy.
 **************************************************************************************************/

void TestStringVFTableStringCopy();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringCopyAllocated();
 *
 * @brief	Tests string vf table string copy.
 **************************************************************************************************/

void TestStringVFTableStringCopyAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringIsEmpty();
 *
 * @brief	Tests string vf table string empty.
 **************************************************************************************************/

void TestStringVFTableStringIsEmpty();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringSize();
 *
 * @brief	Tests string vf table string size.
 **************************************************************************************************/

void TestStringVFTableStringSize();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringSet();
 *
 * @brief	Tests string vf table StringSet with statically allocated string
 **************************************************************************************************/

void TestStringVFTableStringSet();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringSetAllocated();
 *
 * @brief	Tests string vf table StringSet with newly allocated string
 **************************************************************************************************/

void TestStringVFTableStringSetAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringSetAlreadyAllocated();
 *
 * @brief	Tests string vf table StringSet with newly allocated string
 **************************************************************************************************/

void TestStringVFTableStringSetAlreadyAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringC_Str();
 *
 * @brief	Tests string vf table StringC_Str is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableStringC_Str();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringAppend();
 *
 * @brief	Tests string vf table StringAppend static
 **************************************************************************************************/

void TestStringVFTableStringAppend();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringAppendAllocated();
 *
 * @brief	Tests string vf table StringAppend newly allocated
 **************************************************************************************************/

void TestStringVFTableStringAppendAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringAppendAlreadyAllocated();
 *
 * @brief	Tests string vf table StringAppend already allocated
 **************************************************************************************************/

void TestStringVFTableStringAppendAlreadyAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringInsert();
 *
 * @brief	Tests string vf table StringInsert static
 **************************************************************************************************/

void TestStringVFTableStringInsert();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringInsert();
 *
 * @brief	Tests string vf table StringInsert static
 **************************************************************************************************/

void TestStringVFTableStringInsert();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringInsertAllocated();
 *
 * @brief	Tests string vf table StringInsert newly allocated
 **************************************************************************************************/

void TestStringVFTableStringInsertAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringInsertOtherStringAllocated();
 *
 * @brief	Tests string vf table StringInsert newly allocated other string
 **************************************************************************************************/

void TestStringVFTableStringInsertOtherStringAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringInsertOtherStringAllocatedNewlyAllocated();
 *
 * @brief	Tests string vf table StringInsert newly allocated other string
 **************************************************************************************************/

void TestStringVFTableStringInsertOtherStringAllocatedNewlyAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringInsertAlreadyAllocated();
 *
 * @brief	Tests string vf table StringInsert already allocated
 **************************************************************************************************/

void TestStringVFTableStringInsertAlreadyAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringInsertAlreadyAllocatedInsertionStringAllocated();
 *
 * @brief	Tests string vf table StringInsert already allocated
 **************************************************************************************************/

void TestStringVFTableStringInsertAlreadyAllocatedInsertionStringAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringInsertOutOfBounds();
 *
 * @brief	Tests string vf table StringInsert out of bounds
 **************************************************************************************************/

void TestStringVFTableStringInsertOutOfBounds();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringInsertNPOS();
 *
 * @brief	Tests string vf table StringInsert npos
 **************************************************************************************************/

void TestStringVFTableStringInsertNPOS();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringReplace();
 *
 * @brief	Tests string vf table string replace.
 **************************************************************************************************/

void TestStringVFTableStringReplace();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringReplaceAllocated();
 *
 * @brief	Tests string vf table string replace.
 **************************************************************************************************/

void TestStringVFTableStringReplaceAllocated();

void TestStringVFTableStringErase();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringFind();
 *
 * @brief	Tests string vf table StringFind haystack - static | needle - static
 **************************************************************************************************/

void TestStringVFTableStringFind();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringFindHayStackAllocated();
 *
 * @brief	Tests string vf table StringFind haystack - allocated | needle - static
 **************************************************************************************************/

void TestStringVFTableStringFindHayStackAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringFindNeedleAllocated();
 *
 * @brief	Tests string vf table StringFind haystack - static | needle - allocated
 **************************************************************************************************/

void TestStringVFTableStringFindNeedleAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringFindHayStackAllocatedNeedleAllocated();
 *
 * @brief	Tests string vf table StringFind haystack - allocated | needle - allocated
 **************************************************************************************************/

void TestStringVFTableStringFindHayStackAllocatedNeedleAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringFindNull();
 *
 * @brief	Tests string vf table StringFind with a not found string
 **************************************************************************************************/

void TestStringVFTableStringFindNull();


/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringSubString();
 *
 * @brief	Tests string vf table SubString is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableStringSubString();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringSubStringAllocated();
 *
 * @brief	Tests string vf table SubString is pointing to the correct function
 **************************************************************************************************/

void TestStringVFTableStringSubStringAllocated();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringSubStringLessThanZero();
 *
 * @brief	Tests string vf table SubString for user mistakes like < 0
 **************************************************************************************************/

void TestStringVFTableStringSubStringLessThanZero();

/**********************************************************************************************//**
 * @fn	void TestStringVFTableStringSubStringOutOfBounds();
 *
 * @brief	Tests string vf table substring out of bounds
 **************************************************************************************************/

void TestStringVFTableStringSubStringOutOfBounds();

/**********************************************************************************************//**
 * @fn	void TestStringIterator();
 *
 * @brief	Tests string iterator
 **************************************************************************************************/

void TestStringIterator();

/**********************************************************************************************//**
 * @fn	void TestStringIteratorAllocated();
 *
 * @brief	Tests string iterator allocated
 **************************************************************************************************/

void TestStringIteratorAllocated();
