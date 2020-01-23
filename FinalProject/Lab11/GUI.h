#pragma once
#include "Service.h"
#include <qwidget>
#include "C:\Qt\5.12.3\msvc2017_64\include\QtWidgets\qwidget.h"
#include "qlistwidget.h"
#include "qlineedit.h"
#include "qpushbutton.h"
#include "qtablewidget.h"
#include "CosCRUDGUI.h"
#include "CosReadOnlyGUI.h"
#include "TableTemplate.h"

class GUI : public QWidget
{
private:
	Service *serv;
	QListWidget *products;
	QLineEdit *name, *type, *price, *producer;
	QPushButton *addButton, *removeButton, *updateButton, *sortNameButton, *sortPriceButton, *filterNameButton, *filterProducerButton;
	QPushButton *CosCRUDGUIButton, *CosReadOnlyGUIButton;
	QWidget *tableWidget = new QWidget;
	QTableView *table = new QTableView();
	//QTableWidget *table = new QTableWidget;
	QPushButton *tableButton = new QPushButton{ "SHOW TABLE" };
	QWidget *filterNameWidget = new QWidget;
	QWidget *filterProducerWidget = new QWidget;
	MyTableModel *model;

	/*
		Adauga un produs nou in lista 
		input: -
		output:-
		Adauga produsul daca se poate, altfel arunca exceptii
	*/
	void add();

	/*
		Sterge un produs din lista
		input:-
		output:-
		Sterge produsul din lista daca acesta este existent, altfel arunca o exceptie
	*/
	void remove();

	/*
		Modifica un produs din lista
		input:-
		output:-
		Modifica produsul daca acesta este existent, altfel arunca o exceptie
	*/
	void update();

	/*
		Sorteaza produsele crescator dupa nume
		input:-
		output:-
	*/
	void sortAfterName();

	/*
		Sorteaza produsele crescator dupa pret
		input:-
		output:-
	*/
	void sortAfterPrice();
	void filterAfterName();
	void filterAfterProducer();
	/*
		Creeaza si afiseaza un tabel formata din lista de produse
		input:-
		output:-
	*/
	void createTable();

public:
	GUI(Service *serv);
	~GUI();

	void window();

	void populateList(vector<Product> prod);
	void clear();
};

