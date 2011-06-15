#include "document.h"

Document::Document():
    previewSize(QSize(300,200))
{
  //  connect(this,SIGNAL(pageIsReady(QImage)),this,SLOT(readyPageForPreview(QImage)));
}

bool Document::isOpened()
{
    return this->ready;
}

QString Document::getPath()
{
    return path;
}

bool Document::setPath(const QString & path)
{
    if (!path.isEmpty() && path != this->getPath())
    {
        this->path = path;
        return true;
    }
    return false;
}

QSize Document::getPreviewSize()
{
    return this->previewSize;
}

bool Document::setPreviewSize(const QSize &size)
{
    if (size != this->previewSize &&
            size.width() > 10 &&
            size.height() > 10)
    {
        this->previewSize = size;
        return true;
    }
    return false;
}

QImage Document::getPreview(int n)
{
    if (n > 0 && n < this->getPageCount())
    {
        return this->getPage(n).scaled(this->getPreviewSize());
        //return true;
    }
    return QImage();
}

/*
void Document::readyPageForPreview(QImage img)
{
    emit this->previewIsReady(img.scaled(this->getPreviewSize()));
}
*/
