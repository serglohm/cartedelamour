#include "imagecache.h"
#include "sqlsaver.h"
#include "imagedownloader.h"
#include <QDebug>


DownloadedImageCache::DownloadedImageCache(QNetworkAccessManager& aNetAccMngr, SQLSaver& aSQL, QObject *parent) :
    QObject(parent),
    iNetAccMngr(aNetAccMngr),
    iSQL(aSQL)
{

}

bool DownloadedImageCache::isLoaded(int aIid)
{
    return iImageLoadHash.contains(aIid);
}

void DownloadedImageCache::imageDownloaded(int aIdx, QImage* aImage)
{
    QImage tImg(*aImage);
    iImageHash.insert(aIdx, tImg);
    iImageLoadHash.remove(aIdx);
    iImageSaveHash.insert(aIdx, 1);

    qWarning() <<  QString("Downloader complete %1").arg(aIdx);
    emit onImageDownloaded(aIdx);
}

void DownloadedImageCache::imageDownloadError(int aIdx)
{
    qWarning() <<  QString("ERROR in Downloader %1").arg(aIdx);
}

bool DownloadedImageCache::saveUnsaved()
{
    for(int i = 0; i < iImageSaveHash.keys().count(); i++)
    {
        int iidx = iImageSaveHash.keys()[i];
        QImage img = iImageHash.value(iidx);
        iSQL.saveImage(iidx, img);
    }
    iImageSaveHash.clear();

}

bool DownloadedImageCache::clearHash(QList<int>& aNotDeletedList)
{
    saveUnsaved();
    for(int i = 0; i < iImageHash.keys().count(); i++)
    {
        int iid = iImageHash.keys()[i];
        int f = true;
        for(int j = 0; j < aNotDeletedList.count(); j++)
        {
            if(iid == aNotDeletedList[j])
            {
                f = false;
                break;
            }
        }
        if(f)
            iImageHash.remove(iid);

    }
}


bool DownloadedImageCache::clearHash()
{
    saveUnsaved();
    iImageHash.clear();
}

bool DownloadedImageCache::getImage(int aIID, QImage& aImage)
{
    if(iImageHash.contains(aIID))
    {
        aImage = iImageHash.value(aIID);
        return true;
    }
    else if(iSQL.loadImage(aIID, aImage))
    {
        iImageHash.insert(aIID, aImage);
        return true;
    }
    return false;
}

void DownloadedImageCache::downloadImage(int aIID, QString& aFnameValue, QString& aFoldernameValue)
{
    iImageLoadHash.insert(aIID, 1);

    QString imgPath;
    imgPath.append(aFoldernameValue);
    imgPath.append("/");
    imgPath.append(aFnameValue);

    for(int i = 0; i < iImageDownloaderList.count(); i++)
    {
        if(! iImageDownloaderList[i]->isLoading())
        {
            qWarning() <<  QString("Exist Downloader %1 %2").arg(i).arg(aIID);
            iImageDownloaderList[i]->downloadImage(aIID, imgPath);
            return;
        }
    }

    ImageDownloaderPointer newDwn = new ImageDownloader(iNetAccMngr);

    connect(newDwn, SIGNAL(imageDownloaded(int, QImage*)), this, SLOT(imageDownloaded(int, QImage*)));
    connect(newDwn, SIGNAL(imageDownloadError(int)), this, SLOT(imageDownloadError(int)));

    qWarning() <<  QString("New Downloader %1").arg(aIID);
    newDwn.data()->downloadImage(aIID, imgPath);
    iImageDownloaderList.append(newDwn);

}
