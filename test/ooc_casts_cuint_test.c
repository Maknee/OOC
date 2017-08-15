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
