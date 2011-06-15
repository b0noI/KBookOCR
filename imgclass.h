#ifndef IMGCLASS_H
#define IMGCLASS_H

#include "document.h"

#include <QString>

class imgClass : public Document
{
public:
    imgClass(QString);
    QImage getPage(int);
    int getPageCount();
    QString getFormat();
    bool open(QString);
    bool close();
private:
    QImage img;
};

#endif // IMGCLASS_H
