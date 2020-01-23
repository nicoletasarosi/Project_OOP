#include "Service.h"
#include <functional>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <random>
#include <algorithm>

using namespace std;

void Service::addProduct(const string &_name, const string &_type, const double _price, const string &_producer)
{
	Product p{ _name, _type, _price, _producer };

	auto ptr = make_unique<UndoAdd>(p, &repo);
	undoVector.push_back(move(ptr));

	valid.validationProduct(p);
	repo.add(p);
}

Product Service::searchProduct(const string &_name, const string &_type, const string &_producer)
{
	valid.validationProduct(Product{ _name, _type, 1, _producer });
	return repo.search(_name, _type, _producer);
}

void Service::updateProduct(const string &_name, const string &_type, const double _price, const string &_producer)
{
	Product p = repo.search(_name, _type, _producer);

	auto ptr = make_unique<UndoUpdate>(p, &repo);
	undoVector.push_back(move(ptr));

	valid.validationProduct(Product{ _name, _type, _price, _producer });
	repo.update(Product{ _name, _type, _price, _producer });

}

void Service::removeProduct(const string &_name, const string &_type, const string &_producer)
{
	Product p = repo.search(_name, _type, _producer);

	auto ptr = make_unique<UndoRemove>(p, &repo);
	undoVector.push_back(move(ptr));

	valid.validationProduct(p);
	repo.remove(_name, _type, _producer);
}

vector <Product> Service::filterAfter(function <bool(const Product&)> fct)
{
	vector <Product> allProducts = getAll();
	vector <Product> filtered(allProducts.size());
	auto it = copy_if(allProducts.begin(), allProducts.end(), filtered.begin(), fct);

	return filtered;
}

vector <Product> Service::filterAfterPrice(const double price)
{
	return filterAfter([price](Product prod) noexcept
	{
		return prod.get_price() == price;
	});
}

vector <Product> Service::filterAfterName(const string name)
{
	return filterAfter([name](Product prod) noexcept
	{
		return prod.get_name().find(name) != -1;
	});
}

vector <Product> Service::filterAfterProducer(const string producer)
{
	return filterAfter([producer](Product prod) noexcept
	{
		return prod.get_producer().find(producer) != -1;
	});
}

vector <Product> Service::sortAfter(vector <Product> sorted, sortFunction fct)
{
	sort(sorted.begin(), sorted.end(), fct);
	return sorted;
}

vector <Product> Service::sortAfterName(const vector<Product> &prod)
{
	return sortAfter(prod, compareName);
}

vector <Product> Service::sortAfterPrice(const vector<Product>& prod)
{
	return sortAfter(prod, comparePrice);
}

vector<Product> Service::sortAfterNameAndType(const vector<Product>& prod)
{
	return sortAfter(prod, compareNameAndType);
}

void Service::addToCart(const string &_name)
{
	for (const Product &prod : getAll())
	{
		if (prod.get_name() == _name)
		{
			cart.push_back(prod);
			break; }}
}

void Service::emptyCart()
{
	cart.clear();
	notify();
}

double Service::totalPrice()
{
	double totalPrice = 0;
	for (const Product &prod : cart)
		totalPrice += prod.get_price();
	return totalPrice;
}

void Service::randomAddToCart(int nrProducts)
{
	vector<Product> products = repo.getAll();
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> const dist(0, int(products.size()) - 1);
	while (nrProducts > 0) 
	{
		const int rndNr = dist(mt);// numar aleator intre [0,size-1]
		Product prod = products.at(rndNr);
		cart.push_back(prod);
		nrProducts--;
	}
	notify();
}		

vector<Product> Service::allFromCart()
{
	return cart;
	notify();
}

map<string, int> Service::report()
{
	map<string, int> dictionary;
	vector<Product> products = repo.getAll();
	for (size_t i = 0; i < products.size(); i++)
	{
		string type = products.at(i).get_type();
		dictionary[type] = 0;
	}
	for (size_t i = 0; i < products.size(); i++)
	{
		string type = products.at(i).get_type();
		dictionary[type]++;
	}
	return dictionary; 
}

bool Service::doUndo()
{
	if (undoVector.size() == 0)
		return false;
	undoVector[this->undoVector.size() - 1]->doUndo();
	undoVector.pop_back();
	return true;
}
