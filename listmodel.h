#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QVariant>

class ListItem: public QObject {
	Q_OBJECT

public:
	ListItem(QObject* parent = 0) : QObject(parent) {}
	virtual ~ListItem() {}
	virtual QString id() const = 0;
	virtual QVariant data(int role) const = 0;
	virtual QHash<int, QByteArray> roleNames() const = 0;

signals:
	void dataChanged();
};

class ListModel : public QAbstractListModel
{
	Q_OBJECT

public:
	explicit ListModel(ListItem* prototype, QObject* parent = 0);
	~ListModel();
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	void appendRow(ListItem* item);
	void appendRows(const QList<ListItem*> &items);
	void insertRow(int row, ListItem* item);
	bool removeRow(int row, const QModelIndex &parent = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
	ListItem* takeRow(int row);
	ListItem* find(const QString &id) const;
	QModelIndex indexFromItem( const ListItem* item) const;
	void clear();

private slots:
	void handleItemChange();

private:
	ListItem* m_prototype;
	QList<ListItem*> m_list;
};

#endif // LISTMODEL_H
