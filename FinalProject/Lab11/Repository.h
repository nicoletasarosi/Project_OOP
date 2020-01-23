#pragma once
#include "Product.h"
#include <vector>
#include <string>
#include "ListTemplate.h"
#include <utility>
#include <fstream>
#include <sstream>

using namespace std;

class Repository
{
	//	Vector de produse
	vector<Product> objects;
	

	/*
		Verifica daca un produs se gaseste in vectrul de produse
		input : prod - Product
		output : true - daca produs exista
				 false - daca produsul nu exista
	*/
	bool exist(const Product &prod);

public:
	//	Constructor default
	Repository() = default;

	//	Constructor care impiedica copierea obiectelor
	Repository(const Repository &repo) = delete;

	/*
		Adauga un produs nou in vector
		input : prod - Product
		output : -
		Daca produsul se gaseste deja in vector semnaleaza o eroare
		Altfel il adauga la sfarsitul vectorului
	*/
	virtual void add(const Product &prod) = 0;

	/*
		Modifica un produs din vector
		input : prod - Produs
		output : -
		Daca elementul exista in vector ii va modifica pretul
		Altfel va semnala o eroare
	*/
	virtual void update(const Product &prod) = 0;

	/*
		Cauta un pprodus in vector
		input : _name - string
				_type - string
				price - double
				_producer - string
		output : prod - Product - Daca produsul exista in vector
				 Semnaleaa eroare daca produsul nu exista
	*/
	virtual Product search(const string &_name, const string &_type, const string &_producer) = 0;

	/*

		Sterge un produs din vector
		input : prod - Product
		output : -
	*/
	virtual void remove(string _name, string _type, string _producer) = 0;

	/*
		Returneaza toate elementele din vectorul de produse
		input : -
		output : objects - vector<Products>
	*/
	virtual const vector<Product> &getAll() noexcept;
};

class RepositoryException
{
	//	Mesaj de eroare
	string message;

public:
	//	Constructor
	RepositoryException(string _message) :message{ _message } {}
	string get_message()
	{
		return message;
	}
};

class RepositoryFile : public Repository
{
private:
	string fileName;
	
public:
	RepositoryFile(string _fileName) : fileName{ _fileName } {};

	void storeToFile();
	void loadFromFile();

	void add(const Product &prod) override;
	void update(const Product &prod) override;
	Product search(const string &_name, const string &_type, const string &_prducer) override;
	void remove(string _name, string _type, string _producer) override;

	string getFileName();
};
