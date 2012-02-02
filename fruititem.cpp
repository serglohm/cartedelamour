#include "fruititem.h"

FruitItem::FruitItem(const QString &name, const QString &size, QObject *parent) :
	ListItem(parent), m_name(name), m_size(size), m_price(-1)
{
}

void FruitItem::setPrice(qreal price)
{
	if(m_price != price) {
		m_price = price;
		emit dataChanged();
	}
}

QHash<int, QByteArray> FruitItem::roleNames() const
{
	QHash<int, QByteArray> names;
	names[NameRole] = "name";
	names[SizeRole] = "size";
	names[PriceRole] = "price";
	return names;
}

QVariant FruitItem::data(int role) const
{
	switch(role) {
		case NameRole:
			return name();
		case SizeRole:
			return size();
		case PriceRole:
			return price();
		default:
			return QVariant();
	}
}