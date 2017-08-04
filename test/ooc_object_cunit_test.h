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
 * @fn	void TestObjectNew();
 *
 * @brief	Tests object new
 * @warning	Object is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void TestObjectNew();

/**********************************************************************************************//**
 * @fn	void TestObjectDelete();
 *
 * @brief	Tests object delete
 * @warning	Object is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void TestObjectDelete();

/**********************************************************************************************//**
 * @fn	void TestObjectConstructor();
 *
 * @brief	Tests object constructor
 **************************************************************************************************/

void TestObjectConstructor();

/**********************************************************************************************//**
 * @fn	void TestObjectCopyConstructor();
 *
 * @brief	Tests object copy constructor
 **************************************************************************************************/

void TestObjectCopyConstructor();

/**********************************************************************************************//**
 * @fn	void TestObjectdestructor();
 *
 * @brief	Tests object destructor
 **************************************************************************************************/

void TestObjectDestructor();

/**********************************************************************************************//**
 * @fn	void TestObjectVFTableObjectToString();
 *
 * @brief	Tests object vf table ObjectToString  is pointing to the correct function
 **************************************************************************************************/

void TestObjectVFTableObjectToString();

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



