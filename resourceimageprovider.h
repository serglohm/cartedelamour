#ifndef RESOURCEIMAGEPROVIDER_H
#define RESOURCEIMAGEPROVIDER_H

#include <QDeclarativeImageProvider>

class DownloadedImageCache;

class ResourceImageProvider : public QDeclarativeImageProvider
{
public:
    ResourceImageProvider(QDeclarativeImageProvider::ImageType type, DownloadedImageCache& aImageCache);
    ~ResourceImageProvider();
    QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize);
    QPixmap requestPixmap(const QString& id, QSize* size, const QSize& requestedSize);
private:
    DownloadedImageCache& iImageCache;
};

#endif // RESOURCEIMAGEPROVIDER_H

