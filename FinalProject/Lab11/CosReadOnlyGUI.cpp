#include "CosReadOnlyGUI.h"



CosReadOnlyGUI::CosReadOnlyGUI(Service &serv) : serv{ serv }
{
	setMaximumWidth(1000);
	setMaximumHeight(2500);
}

void CosReadOnlyGUI::paintEvent(QPaintEvent *ev)
{
	QPainter p{ this };
	int numOfProducts = int(serv.allFromCart().size());
	while (numOfProducts > 0)
	{
		int x = rand() % (width() - 20);
		int y = rand() % (height() - 20);
		p.drawImage(x, y, QImage("images.png"));
		numOfProducts--;
	}
}

void CosReadOnlyGUI::update()
{
	repaint();
}