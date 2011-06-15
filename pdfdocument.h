#ifndef PDFDOCUMENT_H
#define PDFDOCUMENT_H

#include "document.h"
#include <poppler/qt4/poppler-qt4.h>

class pdfDocument : public Document
{
public:
    pdfDocument(QString);
    bool open(QString);
    QImage getPage(int);
    int getPageCount();
    QString getFormat();
    QImage getPreview(int n);
    bool close();
    ~pdfDocument();
private:
    Poppler::Document *doc;
};

#endif // PDFDOCUMENT_H
