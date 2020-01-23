#pragma once
#include <qabstractitemmodel.h>
#include <vector>
#include "Product.h"
#include "Service.h"

using std::pair;
using std::vector;

class MyTableModel : public QAbstractTableModel {
public:
	MyTableModel(Service& s) : serv{ s } {}

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	bool MyTableModel::setData(const QModelIndex & index, const QVariant & value, int role);

	Qt::ItemFlags MyTableModel::flags(const QModelIndex & index) const;


	//void timerTikTak();

private:
	Service& serv;
};
