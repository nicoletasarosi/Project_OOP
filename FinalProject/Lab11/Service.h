#pragma once

#include "Product.h"
#include "Repository.h"
#include <string>
#include <vector>
#include <functional>
#include "Validation.h"
#include "ListTemplate.h"
#include <map>
#include "Undo.h"
#include "Observer.h"

//functie de comparat 2 produse pentru sortare
typedef bool(*sortFunction)(const Product &, const Product&);

using namespace std;

class Service : public Observable
{
	//	campuri
	RepositoryFile &repo;
	Validation &valid;
	vector<Product> cart;
	vector<unique_ptr<UndoAction>> undoVector;

public:
	Service(RepositoryFile &repo, Validation &valid)noexcept :repo{ repo }, valid{ valid } {};
	Service(const Service &serv) = delete;

	/*
		Returneaza toate elementele din vector
		input : -
		output : vector<Product>
	*/
	const vector<Product> &getAll() noexcept
	{
		return repo.getAll();
	}

	/*
		Creeaza un produs pe care in adauga un produs in vector
		input : _name - string
				_type - string
				_price - double
				_producer - string
		Produsul va fi adaugat in vector
	*/
	void addProduct(const string &_name, const string &_type, const double _price, const string &_producer);

	/*
		Cauta un produs in vector, returnandu-l ulterior
		input : _name - string
				_type - string
				_producer - string
		output : Product
	*/
	Product searchProduct(const string &_name, const string &_type, const string &_producer);

	/*
		Modifica un produs din interiorul vectorului
		input : _name - string
				_type - string
				_price - double
				_producer - string
		PRodusul va fi modificat
	*/
	void updateProduct(const string &_name, const string &_type, const double _price, const string &_producer);

	/*
		Sterge un produs din vector
		input : _name - string
				_type - string
				_price - double
				_producer - string
		Produsul va fi sters c=din vector
	*/
	void removeProduct(const string &_name, const string &_type, const string &_producer);

	/*
		Creeaza si returneaza un vector de produse, filtrate dupa o functie
		input : fct - function <bool(const Product&)>
		output: filtered - vector <Product>
	*/
	vector <Product> filterAfter(function <bool(const Product&)> fct);

	/*
		Returneaza produsele filtrate dupa un pret dorit
		input : price - double
		output : apeleaza funcia filterAfter
	*/
	vector <Product> filterAfterPrice(const double price);

	/*
		Returneaza produsele filtrate dupa un nume dorit
		input : name - string
		output : apeleaza functia filterAfter
	*/
	vector <Product> filterAfterName(const string name);

	/*
		Returneaza produsele filtrate dupa un producator dorit
		input : producer - string
		output : apeleaza functia filterAfter
	*/
	vector <Product> filterAfterProducer(const string producer);

	/*
		Creeaza si returneaza un vector cu produsele sortate
		input : sorted - vector<Products>
				fct - sortFunction
		output : sorted - vector<Products>
	*/
	vector <Product> sortAfter(vector <Product> sorted, sortFunction fct);

	/*
		Returneaza produsele sortate depa nume
		input : prod - vector<Product>
		output : apeleaza functia SortAfter
	*/
	vector <Product> sortAfterName(const vector<Product>& prod);

	/*
		Returneaza produsele sortate depa pret
		input: prod - vector<Product>
		output: apeleaza functia SortAfter
	*/
	vector <Product> sortAfterPrice(const vector<Product>& prod);

	/*
		Returneaza produsele sortate depa nume si dupa tip
		input: prod - vector<Product>
		output: apeleaza functia SortAfter
	*/
	vector <Product> sortAfterNameAndType(const vector<Product>& prod);

	/*
		Adauga un produs in cosul de cumparaturi
		input: name - string
		output: -
		Produsul va fi adaugat
	*/
	void addToCart(const string &_name);

	/*
		Goleste cosul de cumparaturi
		input: -
		output: -
		Toate produsele din cos vor fi sterse
	*/
	void emptyCart();

	/*
		Calculeaza si returneaza pretul total al produselor din cos
		input: -
		output: totalPrice - double
		Returneaza pretul total al produselor din cos
	*/
	double totalPrice();

	/*
		Adauga produse random in cosul de cumparaturi
		input: nrProducts - int
		output: -
		Vor fi adaugate nrProducts produse random in cos
	*/
	void randomAddToCart(int nrProducts);

	/*
		Returneaza cosul de cumparaturi
		input: -
		output: cart - vector
	*/
	vector<Product> allFromCart();

	/*
		
	*/
	map<string, int> report();

	/*
	
	*/
	bool doUndo();
};

