#ifndef SQLSAVER_H
#define SQLSAVER_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QImage>
#include <QBuffer>
#include <QVariant>
#include <QPixmap>
#include <QFile>
#include <QHash>
#include <QList>


class SQLSaver
{
public:
    SQLSaver();

    bool loadImage(int aIid, QImage& aImg);
    bool saveImage(int aIdx, QImage& aImage);
    bool hasImage(int aIid);
    int getCountQueryResult(const QString& querySql);

    ~SQLSaver();

protected:


private:
    QSqlDatabase db;

};

#endif // SQLSAVER_H
