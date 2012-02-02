#ifndef IMAGECACHE_H
#define IMAGECACHE_H

#include <QObject>

#include <QHash>
#include <QList>
#include <QPointer>
#include <QPainter>
#include <QNetworkAccessManager>

#include "imagedownloader.h"

#define ImageDownloaderPointer QPointer<ImageDownloader>

class SQLSaver;

class DownloadedImageCache : public QObject
{
    Q_OBJECT
public:
    explicit DownloadedImageCache(QNetworkAccessManager& aNetAccMngr, SQLSaver& aSQL, QObject *parent = 0);
    bool isLoaded(int aIid);
    bool getImage(int aIID, QImage& aImage);
    void downloadImage(int aIID, QString& aFnameValue, QString& aFoldernameValue);
    bool saveUnsaved();

    bool clearHash();
    bool clearHash(QList<int>& aNotDeletedList);

protected:
    SQLSaver& iSQL;

private:
    QList<ImageDownloaderPointer> iImageDownloaderList;
    QHash<int, QImage> iImageHash;
    QHash<int, int> iImageSaveHash;
    QHash<int, int> iImageLoadHash;

    QNetworkAccessManager& iNetAccMngr;

signals:
    void onImageDownloaded(int aIdx);

public slots:
    void imageDownloaded(int aIdx, QImage* aImage);
    void imageDownloadError(int aIdx);

};

#endif // IMAGECACHE_H
