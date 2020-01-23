#include "GUI.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <qmessagebox.h>



GUI::GUI(Service *serv)
{
	this->serv = serv;
	this->window();
	this->populateList(this->serv->getAll());
}


GUI::~GUI()
{
}

void GUI::window()
{
	QHBoxLayout *mainLayout = new QHBoxLayout{ this };
	QHBoxLayout *listLayout = new QHBoxLayout{};

	this->products = new QListWidget{};
	listLayout->addWidget(this->products);

	QVBoxLayout *leftLayout = new QVBoxLayout{};
	this->name = new QLineEdit{};
	this->type = new QLineEdit{};;
	this->price = new QLineEdit{};
	this->producer = new QLineEdit{};

	QFormLayout *dataLayout = new QFormLayout{};
	dataLayout->addRow("Name", this->name);
	dataLayout->addRow("Type", this->type);
	dataLayout->addRow("Price", this->price);
	dataLayout->addRow("Producer", this->producer);

	QVBoxLayout *buttonLayout = new QVBoxLayout{};
	QHBoxLayout *buttonLayout1 = new QHBoxLayout{};
	QHBoxLayout *buttonLayout2 = new QHBoxLayout{};
	QHBoxLayout *buttonLayout3 = new QHBoxLayout{};
	this->addButton = new QPushButton{ "ADD" };
	this->removeButton = new QPushButton{ "REMOVE" };
	this->updateButton = new QPushButton{ "UPDATE" };
	this->sortNameButton = new QPushButton{ "SORT AFTER NAME" };
	this->sortPriceButton = new QPushButton{ "SORT AFTER PRICE" };
	this->filterNameButton = new QPushButton{ "FILTER AFTER NAME" };
	this->filterProducerButton = new QPushButton{ "FILTER AFTER PRODUCER" };
	this->CosCRUDGUIButton = new QPushButton{ "CosCRUDGUI" };
	this->CosReadOnlyGUIButton = new QPushButton{ "CosReadOnlyGUI" };
	buttonLayout1->addWidget(addButton);
	buttonLayout1->addWidget(removeButton);
	buttonLayout1->addWidget(updateButton);
	buttonLayout2->addWidget(sortNameButton);
	buttonLayout2->addWidget(sortPriceButton);
	buttonLayout2->addWidget(filterNameButton);
	buttonLayout2->addWidget(filterProducerButton);
	buttonLayout3->addWidget(tableButton);
	buttonLayout3->addWidget(CosCRUDGUIButton);
	buttonLayout3->addWidget(CosReadOnlyGUIButton);
	buttonLayout->addLayout(buttonLayout1);
	buttonLayout->addLayout(buttonLayout2);
	buttonLayout->addLayout(buttonLayout3);

	leftLayout->addLayout(dataLayout);
	leftLayout->addLayout(buttonLayout);

	mainLayout->addLayout(listLayout);
	mainLayout->addLayout(leftLayout);

	QObject::connect(addButton, &QPushButton::clicked, [this]() {this->add(); });
	QObject::connect(removeButton, &QPushButton::clicked, [this]() {this->remove(); });
	QObject::connect(updateButton, &QPushButton::clicked, [this]() {this->update(); });
	QObject::connect(sortNameButton, &QPushButton::clicked, [this]() {this->sortAfterName(); });
	QObject::connect(sortPriceButton, &QPushButton::clicked, [this]() {this->sortAfterPrice(); });
	QObject::connect(filterNameButton, &QPushButton::clicked, [this]() {this->filterAfterName(); });
	QObject::connect(filterProducerButton, &QPushButton::clicked, [this]() {this->filterAfterProducer(); });
	QObject::connect(tableButton, &QPushButton::clicked, [this]() {this->createTable();  });
	QObject::connect(CosCRUDGUIButton, &QPushButton::clicked, [this]()
	{
		CosCRUDGUI *cart = new CosCRUDGUI{ *serv };
		serv->addObserver(cart);
		cart->show();
	});
	QObject::connect(CosReadOnlyGUIButton, &QPushButton::clicked, [this]()
	{
		CosReadOnlyGUI *cart = new CosReadOnlyGUI{ *serv };
		serv->addObserver(cart);
		cart->show();
	});
}

void GUI::populateList(vector<Product> prod)
{
	this->clear();
	for (auto p : prod)
		this->products->addItem(QString::fromStdString(p.getString()));

}

void GUI::clear()
{
	while (this->products->count())
		this->products->takeItem(0);
}


void GUI::add()
{
	std::string _name = this->name->text().toStdString();
	std::string _type = this->type->text().toStdString();
	std::string _price = this->price->text().toStdString();
	std::string _producer = this->producer->text().toStdString();
	const double price = std::stod(_price);

	try
	{
		this->serv->addProduct(_name, _type, price, _producer);
		this->populateList(this->serv->getAll());
		QMessageBox::information(this->addButton, tr("Succeded!"), tr("Product added"));
	}
	catch (RepositoryException)
	{
		QMessageBox::information(this->addButton, tr("Failed!"), tr("The product already exist!"));
	}
	catch (ValidationException)
	{
		QMessageBox::information(this->addButton, tr("Failed!"), tr("Invalid product!"));
	}
	catch (const std::invalid_argument)
	{
		QMessageBox::information(this->addButton, tr("Failed!"), tr("Invalid Product!"));
	}
}

void GUI::remove()
{
	std::string _name = this->name->text().toStdString();
	std::string _type = this->type->text().toStdString();
	std::string _price = this->price->text().toStdString();
	std::string _producer = this->producer->text().toStdString();

	double price = std::stod(_price);

	try
	{
		this->serv->removeProduct(_name, _type, _producer);
		this->populateList(this->serv->getAll());
		QMessageBox::information(this->removeButton, tr("Succeded!"), tr("Produc removed!"));
	}
	catch (RepositoryException)
	{
		QMessageBox::information(this->removeButton, tr("Failed!"), tr("The product doesn't exist!"));
	}
	catch (ValidationException)
	{
		QMessageBox::information(this->removeButton, tr("Failed!"), tr("Invalid product!"));
	}
	catch (const std::invalid_argument)
	{
		QMessageBox::information(this->removeButton, tr("Failed!"), tr("Invalid product!"));
	}
}

void GUI::update()
{
	std::string _name = this->name->text().toStdString();
	std::string _type = this->type->text().toStdString();
	std::string _price = this->price->text().toStdString();
	std::string _producer = this->producer->text().toStdString();

	double price = std::stod(_price);

	try
	{
		this->serv->updateProduct(_name, _type, price, _producer);
		this->populateList(this->serv->getAll());
		QMessageBox::information(this->removeButton, tr("Succeded!"), tr("Produc removed!"));
	}
	catch (RepositoryException)
	{
		QMessageBox::information(this->removeButton, tr("Failed!"), tr("The product doesn't exist!"));
	}
	catch (ValidationException)
	{
		QMessageBox::information(this->removeButton, tr("Failed!"), tr("Invalid product!"));
	}
	catch (const std::invalid_argument)
	{
		QMessageBox::information(this->removeButton, tr("Failed!"), tr("Invalid product!"));
	}
}

void GUI::sortAfterName()
{
	std::vector<Product> prods = this->serv->getAll();
	vector<Product> prod = this->serv->sortAfterName(prods);
	this->populateList(prod);
}

void GUI::sortAfterPrice()
{
	std::vector<Product> prods = this->serv->getAll();
	vector<Product> prod = this->serv->sortAfterPrice(prods);
	this->populateList(prod);
}

void GUI::filterAfterName()
{
	QHBoxLayout *filterLayout = new QHBoxLayout{ filterNameWidget };
	QListWidget *filterProducts = new QListWidget;
	filterProducts->clear();
	std::string _name = this->name->text().toStdString();
	vector<Product> prod = this->serv->filterAfterName(_name);
	for (auto p : prod)
	{
		if (p.get_price() == 0)
			break;
		filterProducts->addItem(QString::fromStdString(p.getString()));
	}
	filterLayout->addWidget(filterProducts);
	filterNameWidget->show();
}

void GUI::filterAfterProducer()
{
	QHBoxLayout *filterLayout = new QHBoxLayout{ filterProducerWidget };
	QListWidget *filterProducts = new QListWidget;
	filterProducts->clear();
	std::string _producer = this->producer->text().toStdString();
	vector<Product> prods = this->serv->filterAfterProducer(_producer);
	for (auto p : prods)
	{
		if (p.get_price() == 0)
			break;
		filterProducts->addItem(QString::fromStdString(p.getString()));
	}
	filterLayout->addWidget(filterProducts);
	filterProducerWidget->show();
}

void GUI::createTable()
{
	QHBoxLayout *tableLayout = new QHBoxLayout{ tableWidget };
	model = new MyTableModel(*serv);
	table->setModel(model);

	tableLayout->addWidget(table);
	tableWidget->show();
}
