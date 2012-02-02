#include "imageuploader.h"
#include <QByteArray>
#include <QBuffer>
#include <QDebug>

ImageUploader::ImageUploader(QNetworkAccessManager& aNetAccMngr, QObject *parent) :
    QObject(parent), iNetAccMngr(aNetAccMngr)
{
    iId = 0;
}

ImageUploader::~ImageUploader(){
}

void ImageUploader::uploadImage(int aIdx, const QImage& aImage, const QString& aMessage, const QString& aUrl)
{
    iId = aIdx;
    QByteArray ba;
    QImage im(aImage);
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);
    im.save(&buffer, "JPEG");

    QNetworkRequest request;

    request.setUrl(QUrl(aUrl));

    qWarning() << "upload Message " << aUrl;

    request.setRawHeader("Host", "mobileadv.ru");
    request.setRawHeader("Content-type", "multipart/form-data, boundary=4507614711");
    request.setRawHeader("Cache-Control", "no-cache");
    request.setRawHeader("Accept","*/*");

    QByteArray bytes;
    bytes.append("------------4507614711\r\n");
    bytes.append("Content-Disposition: form-data; name=\"message\"\r\n");
    bytes.append("\r\n");
    bytes.append(aMessage);
    bytes.append("\r\n");


    bytes.append("------------4507614711\r\n");
    bytes.append("Content-Disposition: form-data; name=\"attach\"; filename=\"1.jpg\"\r\n");
    bytes.append("Content-type: image/jpeg\r\n");
    bytes.append("\r\n");
    bytes.append(ba);
    bytes.append("\r\n");

    bytes.append("------------4507614711--");
    bytes.append("\r\n");

    qWarning() << "updaload image ";

    iReply = iNetAccMngr.post(request, bytes);
    connect(iReply, SIGNAL(finished()), this, SLOT(requestReady()));
}


void ImageUploader::requestReady()
{
    bool result = iReply->error() == QNetworkReply::NoError;
    if (result)
    {
        qWarning() << "requestReady OK ";
        QByteArray qba = iReply->readAll();
        QString str("");
        str += qba;
        qWarning() << str;
        emit imageUploaded(iId);
    }
    else
    {
        qWarning() << "requestReady ERROR ";
    }
    iReply->deleteLater();
    iReply = NULL;

}

