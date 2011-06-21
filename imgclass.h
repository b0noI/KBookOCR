#ifndef IMGCLASS_H
#define IMGCLASS_H

#include "document.h"

#include <QString>

class imgClass : public Document
{
public:
    imgClass(QString);
    imgClass(QImage);
    QImage getPage(int);
    int getPageCount();
    QString getFormat();
    bool open(QString);
    bool close();
    bool saveImg(QString, int);
    QImage getRealPage(int);

private:
    QString getImgDir();
    QImage img;
    QString path;
};

#endif // IMGCLASS_H
