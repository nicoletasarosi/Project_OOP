#pragma once
#include "Product.h"
#include "Service.h"

class UI
{
	Service &serv;

	/*
		Citeste datele necesare pentru constructia unUI produs, pe care il adauga ulterior in vector
		Daca produsul se poate adauga, se adauga si se afiseaza un mesaj de succes
		Altfel se afiseaz un mesaj de eroare
	*/
	void addUI();

	/*
		Printeaza meniul aplicatiei
	*/
	void printMenu();

	/*
		Afiseaza un produs
	*/
	void printProduct(const Product &prod);

	/*
		Afiseaza vectorul de produse
	*/
	void printProducts(const vector<Product> &products);

	/*
		Citeste datele necesare pentru un produs, care trebUIe cautat in vectoe
		Daca produs s-a gasit se va afisa pe ecren, impreuna cu un mesaj de succes
		Altfel se va afisa un mesaj de eroare
	*/
	void searchProductUI();

	/*
		Citeste datele necesare pentru un produs, pe care il sterge ulterior dein vectoe
		Daca produs existe in vector, aceste se sterge si se afiseaza un mesaj de succes
		Altfel se afiseaza un mesaj de eroare
	*/
	void removeUI();

	/*
		Citeste datele necesare pentru un produs, pe care il modifica ulterior in vector
		Daca produsul exista in vector, pretul acestUIa se modifica, urmand sa fie afisat un mesaj de succes
		Altfel se afiseaza un mesaj de eroare
	*/
	void updateUI();

	/*
		Citeste una dintre optiunile posibile, si in functie de asta apeleaza functia corespunzatoare
	*/
	void filter();

	/*
		Filtreaza produsele existente in functie de pretul introdus de a tastatura.
	*/
	void filterAfterPrice();

	/*
		Filtreaza produsele existente in functie de numele introdus de la tastatura.
	*/
	void filterAfterName();

	/*
		Filtreaza produsele existente in functie de producatorul introdus de la tastatura.
	*/
	void filterdAfterProducer();

	/*
		Sorteaza produsele existente in functie de numele citit de la tastatura
	*/
	void sortAfterName();

	/*
		Sorteaza produsele existente in functie de pretul citit de la tastatura
	*/
	void sortAfterPrice();

	/*
		Sorteaza produsele existente in functie de numele si tipul citit de la tastatura
	*/
	void sortAfterNameAndType();

	/*
		Citeste una dintre optiunile posibile, si in functie de asta apeleaza functia corespunzatoare
	*/
	void sort();

	/*
		Adauga produse in cosul de cumparaturi
	*/
	void addToCartUI();

	/*
		Sterge toate produsele din cosul de cumparaturi
	*/
	void emptyCartUI();

	/*
		Adauga produse random in cosul de cumparaturi
	*/
	void randomAddToCartUI();

	/*
		Adauga produse implicite
	*/
	void implicitlyAddUI();

	/*
		Face raportul gen - cantitate
	*/
	void reportUI();

	/*
		Salveaza cosul de cumparaturi intru-un fisier csv
	*/
	void saveIntoCSVFile();

	/*
	
	*/
	void UndoUI();

public:
	//	Constructor
	UI(Service &serv) noexcept :serv{ serv } {}
	//	Constructor care impiedica copierea
	UI(const UI &ot) = delete;
	//	Fnctie care se ocupa de rularea programulUI
	int start();
};

