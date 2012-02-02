#include "imagedownloader.h"

#include <QByteArray>
#include <QPixmap>

ImageDownloader::ImageDownloader(QNetworkAccessManager& aNetAccMngr, QObject *parent) :
    QObject(parent),
    iNetAccMngr(aNetAccMngr)
{
    iHostUrl = QString("http://www.mobileadv.ru/");
}

void ImageDownloader::setHostUrl(QString& aUrl)
{
    iHostUrl = aUrl;
}

void ImageDownloader::downloadImage(int aIdx, QString& filename)
{
    iLoading = true;
    iIdx = aIdx;

    QString tempUrl(iHostUrl);
    tempUrl.append(filename);
    iUrl = tempUrl;

    iReply = iNetAccMngr.get(QNetworkRequest(iUrl));
    connect(iReply, SIGNAL(finished()), this, SLOT(requestReady()));
}

bool ImageDownloader::isLoading()
{
    return iLoading;
}

void ImageDownloader::requestReady()
{
    bool result = iReply->error() == QNetworkReply::NoError;

    if (result)
    {
        QByteArray qba = iReply->readAll();
        QPixmap dixy;
        dixy.loadFromData(qba);
        QImage* iImage = new QImage(dixy.toImage());
        emit imageDownloaded(iIdx, iImage);
        delete iImage;
    }
    else
    {
        emit imageDownloadError(iIdx);
    }

    iReply->deleteLater();
    iReply = NULL;

    iLoading = false;
}




