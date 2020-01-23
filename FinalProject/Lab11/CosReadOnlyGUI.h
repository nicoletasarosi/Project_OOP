#pragma once
#include "Observer.h"
#include "Service.h"
#include <qmainwindow.h>
#include <qpainter.h>
#include <stdlib.h>
#include <time.h>
#include <qimage.h>

class CosReadOnlyGUI : public QMainWindow, public Observer
{
private:
	Service &serv;

public:
	CosReadOnlyGUI(Service &serv);
	void paintEvent(QPaintEvent *ev) override;
	void update() override;
};

