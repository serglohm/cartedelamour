#ifndef PTSENGINE_H
#define PTSENGINE_H

#include <QObject>
#include <QImage>
#include <QNetworkAccessManager>
#include <QDeclarativeImageProvider>
#include <QDeclarativeView>

class ImageUploader;
class ImageDownloader;
class SQLSaver;
class DownloadedImageCache;
class ResourceImageProvider;
class PTSEngine : public QObject
{
    Q_OBJECT
public:
    explicit PTSEngine(QDeclarativeView& aView, QObject *parent = 0);
    ~PTSEngine();
    QDeclarativeView& iView;
    QDeclarativeImageProvider* getImageProvider();
private:
    QNetworkAccessManager* iNetwMgr;
    SQLSaver* iSQLSaver;
    DownloadedImageCache* iImageCache;
    ResourceImageProvider* iImageProv;
    ImageUploader* iImageUploader;
    QString iSID;
signals:
    void imageLoaded(int iid);
    void imageUploaded(int iid);

public slots:
    void setSID(QString aSID);
    void loadImage(int iid);
    void downloadImage(int iid);
    void uploadImage(int iid);
    bool hasImage(int iid);
    bool tryImage(int iid);
    void onImageDownloaded(int aIdx);
    void onImageUploaded(int aIdx);
    void getCameraPreview(const QString& aUrl, const QString& aMessage, int aUID);
};

#endif // PTSENGINE_H
