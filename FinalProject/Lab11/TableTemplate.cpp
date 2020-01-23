#include "TableTemplate.h"


//MyTableModel::MyTableModel(Service& s) : serv{ s } {
//}
int MyTableModel::rowCount(const QModelIndex & /*parent*/) const {
	return int(serv.getAll().size());
}
int MyTableModel::columnCount(const QModelIndex & /*parent*/) const {
	return 5;
}
QVariant MyTableModel::data(const QModelIndex &index, int role) const {
	auto elems = serv.getAll();
	if (role == Qt::DisplayRole) {
		QString str;
	
		if (index.column() == 0) {
			str = QString::fromStdString(elems.at(index.row()).get_name());
		}
		else if (index.column() == 2) {
			str = QString::fromStdString(elems.at(index.row()).get_type());
		}
		else if (index.column() == 3) {
			str = QString::number(elems.at(index.row()).get_price());
		}
		else if (index.column() == 4) {
			str = QString::fromStdString(elems.at(index.row()).get_producer());
		}
		return str;
	}
	return QVariant();
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole) {
		if (orientation == Qt::Horizontal) {
			if (section == 0) {
				return QString("Quantity");
			}
			else if (section == 1) {
				return QString("Name");
			}
			else if (section == 2) {
				return QString("Type");
			}
			else if (section == 3) {
				return QString("Price");
			}
			else if (section == 4) {
				return QString("Producer");
			}
		}
	}
	return QVariant();
}

bool MyTableModel::setData(const QModelIndex & index, const QVariant & value, int role) {
	if (role == Qt::EditRole) {
		int row = index.row();
		int column = index.column();

		QModelIndex topLeft = createIndex(row, column);
		emit dataChanged(topLeft, topLeft);
	}
	return true;
}
Qt::ItemFlags MyTableModel::flags(const QModelIndex & index) const {
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}



/*
void MyTableModel::timerTikTak() {
	QModelIndex topLeft = createIndex(0, 0);
	QModelIndex bottomRight = createIndex(rowCount(), columnCount());
	emit dataChanged(topLeft, bottomRight);
}*/