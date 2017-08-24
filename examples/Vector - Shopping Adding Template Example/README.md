This example provides a templated vector case. What if the vector template did not
include floats? Unforunately, the way templates are implemented, one would have to update the vector template manually.
To do this, one needs to update the ooc_vector_template.c and ooc_vector_template.h with the correct
macros, so the templated class is generated correctly.

```C
#include "ooc.h"

int main()
{
	//Shopping for carrots, onions and tomatoes
	float carrot_cost = 0.87f;
	float onion_cost = 1.32f;
	float tomato_cost = 1.64f;

	//Bought 5 carrots, 4 onions and 3 tomatoes
	Vector(float) shopping_cart = New(Vector(float));

	Call(Vector(float), push_back, shopping_cart, carrot_cost * 5);
	Call(Vector(float), push_back, shopping_cart, onion_cost * 4);
	Call(Vector(float), push_back, shopping_cart, tomato_cost * 3);

	//Calculate checkout price
	float total_cost = 0.0f;
	ForEach(float* cost, Vector(float), shopping_cart,
	{
		total_cost += *cost;
	})

	printf("Your total is %.2lf dollars\n", total_cost);
	
	Delete(Vector(float), shopping_cart);

	return 0;
}
```