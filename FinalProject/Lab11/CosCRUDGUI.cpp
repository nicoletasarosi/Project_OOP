#include "CosCRUDGUI.h"



CosCRUDGUI::CosCRUDGUI(Service &s) : serv{ s }
{
	init();
	update();
}

void CosCRUDGUI::init()
{
	table->setColumnCount(4);
	table->setHorizontalHeaderLabels(*headerList);
	layout->addWidget(table);
	layout->addWidget(clearCartButton);
	QHBoxLayout *generateCartLayout = new QHBoxLayout;
	generateCartLayout->addWidget(generateCartText);
	generateCartLayout->addWidget(generateCartInput);
	generateCartLayout->addWidget(generateCartButton);
	layout->addLayout(generateCartLayout);
	wid->setLayout(layout);
	setCentralWidget(wid);

	QObject::connect(clearCartButton, &QPushButton::clicked, [this]()
	{	
		serv.emptyCart();
	});

	QObject::connect(generateCartButton, &QPushButton::clicked, [this]()
	{	
		bool converted;
		int numberOfProducts = generateCartInput->text().toInt(&converted);
		if (converted)
		{
			serv.randomAddToCart(numberOfProducts);
			displayInfoMessage("You have added " + std::to_string(numberOfProducts) + " products! \n");
			update();
		}
		else
			displayErrorMessage("The number is invalid! \n");
	});
	QObject::connect(table, &QTableWidget::itemSelectionChanged, [this]()
	{
		if (table->selectedItems().size() > 0)
		{
			int column = table->selectedItems()[0]->column();
			table->sortItems(column);
			table->clearSelection();
		}
	});
}

void CosCRUDGUI::update()
{
	auto products = serv.allFromCart();
	int rowCounter = 0;
	table->clear();
	table->setRowCount(int(serv.allFromCart().size()));
	table->setHorizontalHeaderLabels(*headerList);
	for (const auto &prod : products)
	{
		table->setItem(rowCounter, 0, new QTableWidgetItem(QString::fromStdString(prod.get_name())));
		table->setItem(rowCounter, 1, new QTableWidgetItem(QString::fromStdString(prod.get_type())));
		table->setItem(rowCounter, 2, new QTableWidgetItem(QString::fromStdString(to_string(prod.get_price()))));
		table->setItem(rowCounter, 3, new QTableWidgetItem(QString::fromStdString(prod.get_producer())));
		rowCounter++;
	}
}

void CosCRUDGUI::displayInfoMessage(string msg) {
	QMessageBox::information(this, "Info", QString::fromStdString(msg), QMessageBox::Ok);
}

void CosCRUDGUI::displayErrorMessage(string msg) {
	QMessageBox::critical(this, "Error!", QString::fromStdString(msg), QMessageBox::Ok);
}

