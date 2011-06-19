#include "pdfdocument.h"

#include <QFileInfo>

pdfDocument::pdfDocument(QString path) :
    doc(0)
{
    this->open(path);
}

pdfDocument::~pdfDocument()
{
    if (this->doc)
        delete this->doc;
}

bool pdfDocument::open(QString path)
{
    QFileInfo inf(path);
    if (!path.isEmpty() &&
            inf.exists() &&
            inf.suffix().toLower() == "pdf")
    {
        this->setPath(path);
        doc = Poppler::Document::load(path);
        this->ready = true;
        return true;
    }
    return false;
}

QImage pdfDocument::getPreview(int n)
{
    if (this->isOpened() &&
            n > 0 &&
            n <= this->getPageCount())
    {
        //doc->page(n)->renderToImage()
        return doc->page(n)->renderToImage(70,110);
    }
    return QImage();
}

QImage pdfDocument::getPage(int n)
{
    if (this->isOpened() &&
            n > 0 &&
            n <= this->getPageCount())
    {
        //doc->page(n)->renderToImage()
        return doc->page(n)->renderToImage(100,100);
    }
    return QImage();
}

int pdfDocument::getPageCount()
{
    if (this->isOpened())
        return doc->numPages();
    return 0;
}

QString pdfDocument::getFormat()
{
    return "pdf";
}

bool pdfDocument::close()
{
    if (this->isOpened())
    {
        if (this->doc)
        {
            delete this->doc;
            this->doc = 0;
        }
        this->ready = false;
        return true;
    }
}
