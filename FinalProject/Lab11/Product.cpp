#include "Product.h"

bool compareName(const Product &prod1, const Product &prod2)
{
	if (prod1.get_name() < prod2.get_name())
		return true;
	return false;
}

bool comparePrice(const Product &prod1, const Product &prod2)
{
	if (prod1.get_price() < prod2.get_price())
		return true;
	return false;
}

bool compareNameAndType(const Product &prod1, const Product &prod2)
{
	if (prod1.get_name() < prod2.get_name())
		return true;
	else if (prod1.get_name() == prod2.get_name())
	{
		if (prod1.get_type() < prod2.get_type())
			return true;
	}
	return false;
}

std::string Product::getString()
{
	std::string str;
	str = this->get_name() + " " + this->get_type() + " " + to_string(this->get_price()) + " " + this->get_producer();
	return str;
}
