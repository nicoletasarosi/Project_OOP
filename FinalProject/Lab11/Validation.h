#pragma once
#include <string>
#include "Product.h"

class Validation
{
public:
	Validation() = default;
	Validation(const Validation &valid) = delete;

	void validationProduct(const Product &prod);
};


class ValidationException
{
	string message;

public:

	ValidationException(string _message) :message{ _message } {}
	string get_message()
	{
		return message;
	}
};
