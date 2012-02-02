#include "ptsengine.h"
#include "imagedownloader.h"
#include "sqlsaver.h"
#include "imagecache.h"
#include "resourceimageprovider.h"
#include "imageuploader.h"

#include <QDebug>
#include <QDeclarativeEngine>

PTSEngine::PTSEngine(QDeclarativeView& aView, QObject *parent):
    QObject(parent), iView(aView)
{
    iNetwMgr = new QNetworkAccessManager(this);
    iSQLSaver = new SQLSaver();

    iImageCache = new DownloadedImageCache(*iNetwMgr, *iSQLSaver);
    connect(iImageCache, SIGNAL(onImageDownloaded(int)), this, SLOT(onImageDownloaded(int)));

    iImageProv = new ResourceImageProvider(QDeclarativeImageProvider::Pixmap, *iImageCache);
    iImageUploader = new ImageUploader(*iNetwMgr);
    connect(iImageUploader, SIGNAL(imageUploaded(int)), this, SLOT(onImageUploaded(int)));
}

PTSEngine::~PTSEngine(){
    delete iImageProv;
    delete iImageCache;
    delete iImageUploader;
    delete iSQLSaver;
    delete iNetwMgr;
}

QDeclarativeImageProvider* PTSEngine::getImageProvider(){
    return iImageProv;
}


bool PTSEngine::tryImage(int iid){
   bool result = iSQLSaver->hasImage(iid);
   if(! result){
       downloadImage(iid);
   }
   return result;
}

bool PTSEngine::hasImage(int iid){
   bool result = iSQLSaver->hasImage(iid);
   return result;
}

void PTSEngine::loadImage(int iid){

    QImage tempImg;
    if(! iImageCache->getImage(iid, tempImg))
    {
        downloadImage(iid);
    }
}

void PTSEngine::uploadImage(int iid){

}

void PTSEngine::downloadImage(int iid){
    if(! iImageCache->isLoaded(iid))
    {
        QString cgi("cgi-bin");
        QString url = QString("widget.cgi?cmd=get_img&sid=%1&param1=%2").arg(iSID).arg(iid);
        qWarning() << "loadImage " << iid << "url " << url;
        iImageCache->downloadImage(iid, url, cgi);
    } else{
        qWarning() << "loadImage isLoaded " << iid;
    }
}

void PTSEngine::onImageUploaded(int aIdx){
    qWarning() << "QT onImageUploaded: " << aIdx;
    emit imageUploaded(aIdx);
}

void PTSEngine::getCameraPreview(const QString& aUrl, const QString& aMessage, int aUID){
    QUrl url(aUrl);
    QString providerName = url.host();
    QString imgId = url.path().mid(1);

    QDeclarativeEngine* eng = iView.engine();
    QDeclarativeImageProvider* prov = eng->imageProvider(providerName);
    QSize imgsize(320, 240);

    QImage result = prov->requestImage(imgId, &imgsize, imgsize);

    QString urlStr = QString("http://mobileadv.ru/cgi-bin/pts_upload.cgi?sid=%1&param1=%2").arg(iSID).arg(aUID);
    iImageUploader->uploadImage(aUID, result, aMessage, urlStr);

}

void PTSEngine::onImageDownloaded(int aIdx)
{
    QImage tempImg;
    if(iImageCache->getImage(aIdx, tempImg)){
        qWarning() << "imageDownloaded " << aIdx << " image = " << tempImg.size();
        tempImg.save(QString("C:\Data\%1.jpg").arg(aIdx));
    }
    iImageCache->saveUnsaved();
    emit imageLoaded(aIdx);

}

void PTSEngine::setSID(QString aSID){
    iSID = aSID;
    qWarning() << "set SID = " << iSID;
}
