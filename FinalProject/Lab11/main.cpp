#include "Lab11.h"
#include <QtWidgets/QApplication>
#include <string>
#include <iostream>
#include "Ui.h"
#include "Service.h"
#include "Repository.h"
#include "Product.h"
#include "Test.h"
#include "Validation.h"
#include <stdlib.h>
#include "GUI.h"
#include "Validation.h"

int main(int argc, char *argv[])
{
	RepositoryFile *repo = new RepositoryFile{ "products.txt" };
	repo->loadFromFile();
	string command;
	int cmd;
	while (true)
	{
		std::cout << "	Your options   \n";
		std::cout << "0 -> Exit	       \n";
		std::cout << "1 -> QT Designer \n";
		std::cout << "2 -> Console	   \n";
		std::cout << "Your command: ";
		std::cin >> cmd;
		if (cmd == 1)
		{
			QApplication a(argc, argv);
			Validation *valid = new Validation{};
			Service *serv = new Service{ *repo , *valid };
			GUI gui{ serv };
			gui.show();
			return a.exec();
		}
		else if (cmd == 2)
		{
			Validation *valid = new Validation{};
			Service *serv = new Service{ *repo , *valid };
			UI ui(*serv);
			testAll();
			ui.start();
		}
		else if (cmd == 0)
			return 0;
		else
			cout << "Invalid command! \n";
	}
}
