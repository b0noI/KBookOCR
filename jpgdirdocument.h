#ifndef JPGDIRDOCUMENT_H
#define JPGDIRDOCUMENT_H

#include "document.h"
#include <QFileInfoList>

class JpgDirDocument : public Document
{
public:
    QImage getPage(int);
    QImage getRealPage(int);
    int getPageCount();
    QString getFormat();
    bool open(QString);
    QImage getPreview(int);
    bool close();
    JpgDirDocument(QString);
private:
    QFileInfoList files;
};

#endif // JPGDIRDOCUMENT_H
