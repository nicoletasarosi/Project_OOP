#pragma once
#include "Observer.h"
#include "Service.h"
#include <qmainwindow.h>
#include <qboxlayout.h>
#include <qtablewidget.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qmessagebox.h>

class CosCRUDGUI : public QMainWindow, public Observer
{
private:
	QStringList *headerList = new QStringList{ "Name", "Type", "Price", "Producer", "Report" };
	QWidget *wid = new QWidget;
	QVBoxLayout *layout = new QVBoxLayout;
	QTableWidget *table = new QTableWidget;
	Service &serv;

	QPushButton *generateCartButton = new QPushButton{ "GENERATE CART" };
	QPushButton *clearCartButton = new QPushButton{ "CLEAR CART" };
	QLabel *generateCartText = new QLabel("Number of products:");
	QLineEdit *generateCartInput = new QLineEdit;
	

public:
	CosCRUDGUI(Service &s);
	void init();
	void connect();
	void update() override;
	void displayInfoMessage(string msg);
	void displayErrorMessage(string msg);
};

