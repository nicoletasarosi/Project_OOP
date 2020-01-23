#include "Validation.h"

void Validation::validationProduct(const Product &prod)
{
	if (prod.get_price() < 0)
		throw ValidationException("The price must be positive! \n");
}