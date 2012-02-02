#include "sqlsaver.h"
#include "constants.h"
#include <QDebug>

SQLSaver::SQLSaver()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(PushTheScreen::DB_NAME);
    db.open();

    QSqlQuery create_img_sql(PushTheScreen::CREATE_IMG_TABLE_SQL, db);    
    create_img_sql.exec();

}

SQLSaver::~SQLSaver()
{
    db.close();
}

bool SQLSaver::loadImage(int aIid, QImage& aImg)
{
    QSqlQuery pix_sql;
    pix_sql.prepare(QString("select img_data from images where iid=:iid"));
    pix_sql.bindValue(":iid", aIid);
    pix_sql.exec();

    bool result = false;

    if (pix_sql.next())
    {
        QByteArray qba = pix_sql.value(0).toByteArray();
        QPixmap dixy;
        dixy.loadFromData(qba);
        aImg = dixy.toImage();        
        result = true;
    }
    pix_sql.finish();
    return result;
}

bool SQLSaver::hasImage(int aIid)
{
    QSqlQuery pix_sql;
    pix_sql.prepare(QString("select iid from images where iid=:iid"));
    pix_sql.bindValue(":iid", aIid);
    pix_sql.exec();

    bool result = false;
    if (pix_sql.next())
    {
        result = true;
    }
    pix_sql.finish();
    return result;
}


bool SQLSaver::saveImage(int aIdx, QImage& aImage)
{
    QSqlQuery query;
    query.prepare("INSERT INTO images (iid, img_data) VALUES (?, ?)");
    query.addBindValue(aIdx);
    QByteArray ba;
    QImage im(aImage);
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    im.save(&buffer, "JPEG");

    query.addBindValue(ba);
    return query.exec();
}

int SQLSaver::getCountQueryResult(const QString& querySql)
{
    QSqlQuery query(querySql, db);
    int result = -1;
    query.exec();
    if (query.next())
        result = query.value(0).toInt();

    return result;
}
