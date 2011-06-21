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
            n >= 0 &&
            n < this->getPageCount())
    {
        //doc->page(n)->renderToImage()
        return doc->page(n)->renderToImage(70,110);
    }
    return QImage();
}

QImage pdfDocument::getRealPage(int n)
{
    if (this->isOpened() &&
            n >= 0 &&
            n < this->getPageCount())
    {
        //doc->page(n)->renderToImage()

        //doc->page(n)->
        //this->doc->
       //return  this->doc->page(n)->renderToImage(
         //           doc->page(n)->pageSize().width()
           //         ,doc->page(n)->pageSize().height());

        //return this->doc->page(n)->renderToImage(248,353);
        //return this->doc->page(n)->renderToImage(124,179);
        double xy = this->doc->page(n)->pageSize().height()/
                this->doc->page(n)->pageSize().width();
        double x = 248;
        double y = x*xy;
        return this->doc->page(n)->renderToImage(x,y);

        //return true;
    }
    return QImage();
}

/*bool pdfDocument::saveImg(QString path, int n)
{
    if (!path.isEmpty())
    {
        if (this->isOpened() &&
                n >= 0 &&
                n < this->getPageCount())
        {
            //doc->page(n)->renderToImage()

            //doc->page(n)->
            //this->doc->
            this->doc->page(n)->renderToImage(
                        doc->page(n)->pageSize().width()
                        ,doc->page(n)->pageSize().height())
                    .save(path);
            return true;
        }

    }
    return false;
}*/

QImage pdfDocument::getPage(int n)
{
    if (this->isOpened() &&
            n >= 0 &&
            n < this->getPageCount())
    {
        //doc->page(n)->renderToImage()

        //doc->page(n)->
        double xy = this->doc->page(n)->pageSize().height()/
                this->doc->page(n)->pageSize().width();
        double x = 150;
        double y = x*xy;
        return doc->page(n)->renderToImage(x,y);
        //return this->getRealPage(n);
                    //doc->page(n)->pageSize().width()
                    //,doc->page(n)->pageSize().height());
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
