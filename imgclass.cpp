#include "imgclass.h"

#include <QFileInfo>
#include <QDir>
#include <stdlib.h>

imgClass::imgClass(QString path)
{
    this->ready = false;
    this->open(path);
}

imgClass::imgClass(QImage img)
{
    //this->img = img;

    QString imgPath;
    QFileInfo* inf = 0;
    do
    {
        imgPath = this->getImgDir() + QString::number(rand()) + ".tif";
        if (inf)
            delete inf;
        inf = new QFileInfo(imgPath);
    }
    while (inf->exists());
    img.save(imgPath);
    img = QImage();
    this->path = imgPath;


    this->ready = true;
}

QImage imgClass::getRealPage(int n=1)
{
    if (n == 1 || n == 0)
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

QString imgClass::getImgDir()
{
    QString dirPath = QDir::tempPath() +
            QDir::separator() +
            "KBookOCR.tmp.imgs" + QDir::separator();
    QDir dir(dirPath);
    if (!dir.exists())
        dir.mkdir(dirPath);
    return dirPath;
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
             suffix == "tif" ||
             suffix == "png"))
    {
        this->img.load(path);
        //long number;
        QString imgPath;
        QFileInfo* inf = 0;
        do
        {
            imgPath = this->getImgDir() + QString::number(rand()) + ".tif";
            if (inf)
                delete inf;
            inf = new QFileInfo(imgPath);
        }
        while (inf->exists());
        img.save(imgPath);
        img = QImage();
        this->path = imgPath;

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
    QImage img;
    img.load(this->path);
    if (n == 1 || n == 0)
            return img;

    /*if (n == 1 || n == 0)
        return this->img;*/
    return QImage();
}
