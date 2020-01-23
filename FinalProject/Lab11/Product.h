#pragma once
#include <string>
#include <iostream>

using namespace std;

class Product
{
	//Campuri
	std::string name;
	std::string type;
	double price;
	std::string producer;

public:
	//Constructorul clasei Product
	Product() = default;
	Product(const string _name, const string _type, double _price, const string _producer) :name{ _name }, type{ _type }, price{ _price }, producer{ _producer }{}
	//Copie constructor
	Product(const Product &prod) : name{ prod.name }, type{ prod.type }, price{ prod.price }, producer{ prod.producer }{ };
	//returnneaza numele produsilui
	string get_name() const { return name; }
	//returneaza tipul produsului
	string get_type() const { return type; }
	//returneaza pretul produsului
	double get_price() const	{ return price; }
	//returneaza producatorul produsului
	string get_producer() const { return producer; }
	//modifica numele unui produs
	void set_name(const string _name) { name = _name; }
	//modifica tipul unui produs
	void set_type(const string _type) { type = _type; }
	//modifica pretul unui produs
	void set_price(const double _price) { price = _price; }
	//modifica producatorul unui produs
	void set_producer(const string _producer) { producer = _producer; }

	//
	std::string getString();
};

/*
	Compara numele a doua produse
	input : prod1 - Product
			prod2 - Product
	output : true - daca prod1 este, alfabetic, in fata lui prod2
			 false - daca prod1 este, alfabetic, dupa prod2
*/
bool compareName(const Product &, const Product &);

/*
	Compara pretul a doua produse
	input : prod1 - Product
			prod2 - Product
	output : true - pretul lui prod1 < pretul lui prod2
			 false - pretul lui prod1 > pretul lui prod2
*/
bool comparePrice(const Product &, const Product &);

/*
	Compara numele si tipul  a doua produse
	input : prod1 - Product
			prod2 - Product
	output : true - daca prod1 este, alfabetic, in fata lui prod2
			 false - daca prod1 este, alfabetic, dupa prod2
*/
bool compareNameAndType(const Product &, const Product &);