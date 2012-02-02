#include "listmodel.h"

class FruitItem : public ListItem
{
    Q_OBJECT

public:
    enum Roles {
        NameRole = Qt::UserRole+1,
        SizeRole,
        PriceRole
    };

public:
    FruitItem(QObject *parent = 0): ListItem(parent) {}
    explicit FruitItem(const QString &name, const QString &size, QObject *parent = 0);
    QVariant data(int role) const;
    QHash<int, QByteArray> roleNames() const;
    void setPrice(qreal price);
    inline QString id() const { return m_name; }
    inline QString name() const { return m_name; }
    inline QString size() const { return m_size; }
    inline qreal price() const { return m_price; }

private:
    QString m_name;
    QString m_size;
    qreal m_price;
};
