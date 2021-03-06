/**
* @file ooc_container_cunit_test.h
* @brief Container class testing header file
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
int ContainerInitializeSuite();

/* 
 * Clean up test suite.
 * @return zero on success, non-zero otherwise.
 */
int ContainerCleanUpSuite();

/**********************************************************************************************//**
 * @fn	void TestContainerVFTableUninitializedCompleteObjectLocator();
 *
 * @brief	Tests container vf table uninitialized complete container locator  is pointing to NULL
 **************************************************************************************************/

void TestContainerVFTableUninitializedCompleteObjectLocator();

/**********************************************************************************************//**
 * @fn	void TestContainerVFTableInitializedCompleteObjectLocator();
 *
 * @brief	Tests container vf table initialized complete container locator  is pointing to NULL
 **************************************************************************************************/

void TestContainerVFTableInitializedCompleteObjectLocator();

/**********************************************************************************************//**
 * @fn	void TestContainerNew();
 *
 * @brief	Tests container new
 * @warning	Container is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void TestContainerNew();

/**********************************************************************************************//**
 * @fn	void TestContainerDelete();
 *
 * @brief	Tests container delete
 * @warning	Container is an abstract class, so
 * 			<b>DO NOT CALL THIS FUNCTION</b>
 **************************************************************************************************/

void TestContainerDelete();

/**********************************************************************************************//**
 * @fn	void TestContainerConstructor();
 *
 * @brief	Tests container constructor
 **************************************************************************************************/

void TestContainerConstructor();

/**********************************************************************************************//**
 * @fn	void TestContainerCopyConstructor();
 *
 * @brief	Tests container copy constructor
 **************************************************************************************************/

void TestContainerCopyConstructor();

/**********************************************************************************************//**
 * @fn	void TestContainerDestructor();
 *
 * @brief	Tests container destructor
 **************************************************************************************************/

void TestContainerDestructor();

/**********************************************************************************************//**
 * @fn	void TestContainerVFTableEquals();
 *
 * @brief	Tests container vf table equals() is pointing to the correct function
 **************************************************************************************************/

void TestContainerVFTableEquals();

/**********************************************************************************************//**
 * @fn	void TestContainerVFTableCompareTo();
 *
 * @brief	Tests container vf table compareTo() is pointing to the correct function
 **************************************************************************************************/

void TestContainerVFTableCompareTo();

/**********************************************************************************************//**
 * @fn	void TestContainerVFTableContainerToString();
 *
 * @brief	Tests container vf table ContainerToString  is pointing to the correct function
 **************************************************************************************************/

void TestContainerVFTableContainerToString();



