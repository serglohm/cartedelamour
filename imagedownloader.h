#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>

#include <QImage>
#include <QNetworkRequest>
#include <QNetworkReply>


class ImageDownloader : public QObject
{
    Q_OBJECT
public:
    explicit ImageDownloader(QNetworkAccessManager& aNetAccMngr, QObject *parent = 0);
    void downloadImage(int aIdx, QString& filename);
    void setHostUrl(QString& aUrl);

    bool isLoading();

private:
    QString iHostUrl;
    QUrl iUrl;
    QNetworkReply *iReply;
    QNetworkAccessManager& iNetAccMngr;
    int iIdx;
    bool iLoading;
signals:
    void imageDownloaded(int aIdx, QImage* aImage);
    void imageDownloadError(int aIdx);

public slots:
    void requestReady();
};

#endif // IMAGEDOWNLOADER_H
