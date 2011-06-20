#include "jpgdirdocument.h"

#include <QDir>
#include <QFileInfoList>

JpgDirDocument::JpgDirDocument(QString path)
{
    this->open(path);
}

bool JpgDirDocument::close()
{
    this->files.clear();
    this->ready = false;
}

QImage JpgDirDocument::getPage(int n)
{
    QImage img;
    if (n >=0 && n < this->getPageCount())
    {
        img.load(this->files.at(n).filePath());
    }
    return img;
}

QImage JpgDirDocument::getRealPage(int n)
{
    QImage img;
    if (n >=0 && n < this->getPageCount())
    {
        img.load(this->files.at(n).filePath());
    }
    return img;
}

int JpgDirDocument::getPageCount()
{
    return this->files.count();
}

QString JpgDirDocument::getFormat()
{
    return "jpg";
}

bool JpgDirDocument::open(QString path)
{
    QDir dir (path);
    if (dir.exists())
    {
        QFileInfoList files = dir.entryInfoList();
        QFileInfo file;
        foreach (file, files)
        {
            if (file.suffix().toLower() == "jpg")
                this->files << file;
        }
        this->ready = true;
    }
    else
        this->ready = false;
}

QImage JpgDirDocument::getPreview(int n)
{
    QImage img;
    if (n >=0 && n < this->getPageCount())
    {
        img.load(this->files.at(n).filePath());
    }
    return img;
}
