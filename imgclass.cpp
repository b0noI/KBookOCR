#include "imgclass.h"

#include <QFileInfo>

imgClass::imgClass(QString path)
{
    this->ready = false;
    this->open(path);
}

imgClass::imgClass(QImage img)
{
    this->img = img;
    this->ready = true;
}

QImage imgClass::getRealPage(int n=1)
{
    if (n == 1)
        return this->getPage(n);
    return QImage();
}

bool imgClass::saveImg(QString path, int n=1)
{
    if (!path.isEmpty())
    {
        this->getPage(n).save(path);
        return true;
    }
    return false;
}

/*
virtual QImage getPage(int) = 0;
virtual int getPageCount() = 0;
virtual QString getFormat() = 0;
virtual bool open(QString) = 0;
virtual bool close() = 0;
*/

bool imgClass::close()
{
    this->ready = false;
}

bool imgClass::open(QString path)
{
    QFileInfo inf(path);
    QString suffix = inf.suffix().toLower();
    if (inf.exists() &&
            (suffix == "jpg" ||
             suffix == "jpeg" ||
             suffix == "bmp" ||
             suffix == "gif" ||
             suffix == "tiff" ||
             suffix == "png"))
    {
        this->img.load(path);
        this->ready = true;
        return true;
    }
    this->ready = false;
    return false;
}

QString imgClass::getFormat()
{
    return "img";
}

int imgClass::getPageCount()
{
    return 1;
}

QImage imgClass::getPage(int n)
{
    if (n == 1)
        return this->img;
    return QImage();
}
