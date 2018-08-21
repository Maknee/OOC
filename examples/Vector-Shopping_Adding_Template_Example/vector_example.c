#define OOC_V2

#include "ooc.h"
#include "assert.h"

int main()
{
	Vector(float) shopping_cart = New(Vector(float));

	float carrot_cost = 1.00f;
	float potato_cost = 2.00f;
	float chicken_cost = 3.00f;

	Call(shopping_cart, add, carrot_cost);
	Call(shopping_cart, add, potato_cost);
	Call(shopping_cart, add, chicken_cost);

	//Oops, we don't want carrots
	Call(shopping_cart, remove, carrot_cost);

	//Find the potato cost index
	int found_potato_index = Call(shopping_cart, find, potato_cost);
	if(found_potato_index != NPOS)
	{
		//it's a sale!

		//Get the entry from the index
		float* found_potato_cost = Call(shopping_cart, get, found_potato_index);
		*found_potato_cost -= 0.5f;
	}

	//Tax
	ForEach(float* item_cost, Vector(float), shopping_cart,
	{
		*item_cost *= 1.1f;
	})

	float total = 0.0f;
	ForEach(float* item_cost, Vector(float), shopping_cart,
	{
		total += *item_cost;
	})

	//Expect 4.95f
	assert(fabs(total - 4.95f) < 0.01f);

	Delete(shopping_cart);

	return 0;
}