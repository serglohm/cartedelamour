#ifndef IMAGEUPLOADER_H
#define IMAGEUPLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>

#include <QImage>
#include <QNetworkRequest>
#include <QNetworkReply>


class ImageUploader : public QObject
{
    Q_OBJECT
public:
    explicit ImageUploader(QNetworkAccessManager& aNetAccMngr, QObject *parent = 0);
    ~ImageUploader();

    void uploadImage(int aIdx, const QImage& aImage, const QString& aMessage, const QString& aUrl);

    QNetworkReply *iReply;
    QNetworkAccessManager& iNetAccMngr;

    int iId;
signals:
    void imageUploaded(int aId);
public slots:
    void requestReady();
};

#endif // IMAGEUPLOADER_H
