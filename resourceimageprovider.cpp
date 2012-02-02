#include "resourceimageprovider.h"
#include "imagecache.h"
#include <QImage>
#include <QPixmap>

#include <QDebug>

ResourceImageProvider::ResourceImageProvider(QDeclarativeImageProvider::ImageType type, DownloadedImageCache& aImageCache) :
    QDeclarativeImageProvider(type), iImageCache(aImageCache)
{
    qWarning() << QString("ResourceImageProvider");
}

ResourceImageProvider::~ResourceImageProvider()
{
    qWarning() << QString("~ResourceImageProvider");
}

QImage ResourceImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
{
    qWarning() << "requestImage " << id;
    QImage image;
    if(! iImageCache.getImage(id.toInt(), image)){
        QString rsrcid = "c:/data/QMLSis64.png";
        image.load(rsrcid);
    }
    QImage result;

    if (requestedSize.isValid()) {
        result = image.scaled(requestedSize, Qt::KeepAspectRatio);
    } else {
        result = image;
    }
    *size = result.size();
    return result;

}
QPixmap ResourceImageProvider::requestPixmap(const QString& id, QSize* size, const QSize& requestedSize)
{
    qWarning() << "requestPixmap" << id;
    QImage image;
    if(! iImageCache.getImage(id.toInt(), image)){
        QString rsrcid = "c:/data/QMLSis64.png";
        image.load(rsrcid);
    }
    QPixmap result;

    if (requestedSize.isValid()) {
        result = QPixmap::fromImage(image.scaled(requestedSize, Qt::KeepAspectRatio));
    } else {
        result = QPixmap::fromImage(image);
    }
    *size = result.size();
    return result;
}
