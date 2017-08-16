#include "ooc_casts_cuint_test.h"

int CastsInitializeSuite()
{
	return 0;
}

int CastsCleanUpSuite()
{
	return 0;
}

void TestValidUpcast()
{
	Vector(int) vector = New(Vector(int));

	Call(Vector(int), set, vector, INITIALIZER_LIST(int, 5, 5, 5, 5, 6));

	Object vObject = Upcast(Object, vector);

	CU_ASSERT_STRING_EQUAL(Call(Object, toString, vObject), "Object");
	CU_ASSERT_STRING_EQUAL(Call(Object, toString, vector), "Object");

	Delete(Vector(int), vector);
}

void TestValidDowncast()
{
	Vector(int) vector = New(Vector(int));

	Call(Vector(int), set, vector, INITIALIZER_LIST(int, 5, 5, 5, 5, 6));

	Object vObject = Upcast(Object, vector);

	CU_ASSERT_STRING_EQUAL(Call(Object, toString, vObject), "Object");
	CU_ASSERT_STRING_EQUAL(Call(Object, toString, vector), "Object");

	vector = (Vector(int))Downcast(Vector(int), vObject);

	CU_ASSERT_STRING_EQUAL(Call(Object, toString, vector), "Vectorint");

	Delete(Vector(int), vector);
}

void TestMoveSemantics()
{
	Vector(String) vector = New(Vector(String));

	String something = New(String);

	SafeCall(String, set, something, "HEYYYY");

	CU_ASSERT_TRUE(MoveCall(Vector(int), insert, Move(vector), something));

	//should have no leaks since string is moved into vector

	Delete(Vector(int), vector);
}