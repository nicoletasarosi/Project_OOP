#include "UI.h"
#include "Product.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <map>
#include <fstream>

using namespace std;

void UI::printMenu()
{
	cout << "	Menu\n";
	cout << "'0' -> Exit			\n";
	cout << "'1' -> Add product		\n";
	cout << "'2' -> Update product	\n";
	cout << "'3' -> Delete product  \n";
	cout << "'4' -> Print products	\n";
	cout << "'5' -> Find product	\n";
	cout << "'6' -> Filter			\n";
	cout << "'7' -> Sort			\n";
	cout << "'8' -> Add to cart		\n";
	cout << "'9' -> Empty cart		\n";
	cout << "'10' -> Add random products to cart \n";
	cout << "'11' -> Print products from cart \n";
	cout << "'12' -> Report( type- quantity) \n";
	cout << "'13' -> Undo \n";
}

/*
  Citeste date de la consola (int,float, double, string, etc)
  Reia citirea pana cand utilizatorul introduce corect
*/
template<typename T>
T myRead(const char*msg)
{
	T cmd{};
	while (true)
	{
		std::cout << msg;
		std::cin >> cmd;
		const bool fail = std::cin.fail();
		std::cin.clear();
		const auto& aux = std::cin.ignore(1000, '\n');
		if (!fail && aux.gcount() <= 1)
			break;
	}
	return cmd;
}

void UI::printProduct(const Product &prod)
{
	std::cout << std::left << std::setw(25) << prod.get_name() << std::setw(25) << prod.get_type() << std::setw(25) << prod.get_price() << std::setw(25) << prod.get_producer() << endl;
}

void UI::printProducts(const vector<Product>& products)
{
	if (products.size() == 0)
		cout << "There are no products! \n";
	else
	{
		std::cout << std::left << std::setw(25) << "Name" << std::setw(25) << "Type" << std::setw(25) << "Price" << std::setw(25) << "Producer" << endl;
		for (const Product &prod : products)
		{
			if (prod.get_name() == "")
				break;
			printProduct(prod);
		}
	}
}

void UI::searchProductUI()
{
	string _name, _type, _producer;
	cout << "Name :";
	cin >> _name;
	cout << "Type: ";
	cin >> _type;
	cout << "Producer: ";
	cin >> _producer;
	Product prod = serv.searchProduct(_name, _type, _producer);
	std::cout << std::left << std::setw(25) << "Name" << std::setw(25) << "Type" << std::setw(25) << "Price" << std::setw(25) << "Producer" << endl;
	printProduct(prod);
}

void UI::addUI()
{
	string _name, _type, _producer;
	double _price;
	cout << "Name :";
	cin >> _name;
	cout << "Type: ";
	cin >> _type;
	_price = myRead<double>("Price: ");
	cout << "Producer: ";
	cin >> _producer;
	try
	{
		try
		{
			serv.addProduct(_name, _type, _price, _producer);
			cout << "Successfully added! \n";
		}
		catch (ValidationException) { cout << "Datele sunt invalide! \n"; };
	}
	catch (RepositoryException repoEx) { cout << repoEx.get_message(); };
}

void UI::updateUI()
{
	string _name, _type, _producer;
	double _price;
	cout << "Name :";
	cin >> _name;
	cout << "Type: ";
	cin >> _type;
	cout << "Producer: ";
	cin >> _producer;
	_price = myRead<double>("New price: ");
	try
	{
		try
		{
			serv.updateProduct(_name, _type, _price, _producer);
			cout << "Successfully update! \n";
		}
		catch (ValidationException) { cout << "Datele sunt invalide! \n"; };
	}
	catch (RepositoryException repoEx) { cout << repoEx.get_message(); };
}

void UI::removeUI()
{
	string _name, _type, _producer;
	cout << "Name :";
	cin >> _name;
	cout << "Type: ";
	cin >> _type;
	cout << "Producer: ";
	cin >> _producer;
	try
	{
		serv.removeProduct(_name, _type, _producer);
		cout << "Successfully delete! \n";
	}
	catch (RepositoryException repoEx) { cout << repoEx.get_message(); };
}

void UI::filterAfterPrice()
{
	double price;
	price = myRead<double>("Price: ");
	if (price < 0)
		cout << "The price must be positive! \n";
	else
	{
		vector<Product> filtered = serv.filterAfterPrice(price);
		printProducts(filtered);
	}
}

void UI::filterAfterName()
{
	cout << "Enter name: ";
	string _name;
	cin >> _name;
	vector<Product> filtered = serv.filterAfterName(_name);
	printProducts(filtered);
}

void UI::filterdAfterProducer()
{
	cout << "Enter producer: ";
	string _producer;
	cin >> _producer;
	vector<Product> filtered = serv.filterAfterProducer(_producer);
	printProducts(filtered);
}

void UI::filter()
{
	system("cls");
	cout << "Choose one: price, name, producer \n : ";
	string _option;
	cin >> _option;
	if (_option == "price")
		filterAfterPrice();
	else if (_option == "name")
		filterAfterName();
	else if (_option == "producer")
		filterdAfterProducer();
	else
		cout << "Invalid option! \n";
}

void UI::sortAfterName()
{
	vector<Product> allProduct = serv.getAll();
	vector<Product> sorted = serv.sortAfterName(allProduct);
	printProducts(sorted);
}

void UI::sortAfterPrice()
{
	vector<Product> allProduct = serv.getAll();
	vector<Product> sorted = serv.sortAfterPrice(allProduct);
	printProducts(sorted);
}

void UI::sortAfterNameAndType()
{
	vector<Product> allProduct = serv.getAll();
	vector<Product> sorted = serv.sortAfterNameAndType(allProduct);
	printProducts(sorted);
}

void UI::sort()
{
	system("cls");
	cout << "Choose one: name, price, nt(name and type) \n";
	string _option;
	cin >> _option;
	if (_option == "name")
		sortAfterName();
	else if (_option == "price")
		sortAfterPrice();
	else if (_option == "nt")
		sortAfterNameAndType();
	else cout << "Invalid option! \n";
}

void UI::addToCartUI()
{
	string _name;
	cout << "Enter the product's name: ";
	cin >> _name;
	serv.addToCart(_name);
	cout << "The cart total price is: " << serv.totalPrice() << endl;
}

void UI::emptyCartUI()
{
	serv.emptyCart();
	cout << "The cart total price is: " << serv.totalPrice() << endl;
}

void UI::randomAddToCartUI()
{
	cout << "Enter a number: ";
	int nr;
	cin >> nr;
	serv.randomAddToCart(nr);
	cout << "The cart total price is: " << serv.totalPrice() << endl;
	saveIntoCSVFile();
}

void UI::reportUI()
{
	map<string, int> dictionary = serv.report();
	for (auto& element : dictionary)
		cout << element.first << " -> " << element.second << endl;
}

void UI::implicitlyAddUI()
{
	/*
	serv.addProduct("lion", "cereale", 11.9, "nestle");
	serv.addProduct("milka", "ciocolata", 5.3, "milka");
	serv.addProduct("coca-cola", "suc", 3.4, "coca-cola");
	serv.addProduct("iaurt grecesc", "iaurt", 10, "muler");
	serv.addProduct("santal de merisoare", "suc", 7.8, "santal");
	*/
	
}

void UI::saveIntoCSVFile()
{
	ofstream MyFile;
	MyFile.open("cart.csv");
	vector<Product> products = serv.allFromCart();
	MyFile << "Name" << "," << "Type" << "," << "Price" << "," << "Producer" << endl;
	for (const Product prod : products)
	{
		string name = prod.get_name();
		MyFile << name << "," << prod.get_type() << "," << prod.get_price() << "," << prod.get_producer() << endl;
	}
}

void UI::UndoUI()
{
	if (!serv.doUndo())
	{
		std::cout << "Can't undo!\n";
	}
	else
	{
		std::cout << "Operation undone!\n";
	}
}



int UI::start()
{
	implicitlyAddUI();
	while (true)
	{
		system("cls");
		vector<Product> products = serv.getAll();
		printMenu();
		int cmd;

		cout << "Enter your command: ";
		cin >> cmd;
		switch (cmd)
		{
		case 1: addUI(); break;
		case 2: updateUI(); break;
		case 3: removeUI(); break;
		case 4: printProducts(products); break;
		case 5: searchProductUI(); break;
		case 6: filter(); break;
		case 7: sort(); break;
		case 8: addToCartUI(); saveIntoCSVFile(); break;
		case 9: emptyCartUI(); saveIntoCSVFile();  break;
		case 10: randomAddToCartUI(); break;
		case 11: printProducts(serv.allFromCart()); break;
		case 12: reportUI(); break;
		case 13: UndoUI(); break;
		case 0: return 0;
		default:
			cout << "Invalid command ! \n";
		}
		system("pause");
	}
}