#include "view.h"
#include "imgclass.h"
#include <QFileInfo>
/*
View::View(QString path)
{
    QFileInfo inf(path);

    if (inf.exists())
    {
        QString suffix;
        suffix = inf.suffix().toLower();
        if (suffix == "jpeg" ||
                suffix == "jpg" ||
                suffix == "bmp" ||
                suffix == "png" ||
                suffix == "gif")
            this->img.load(path);
        //emit this->ready;
    }
}
*/
bool View::setView(const QImage &img)
{
    if (img != this->getView() &&
            img.width() > 100 &&
            img.height() > 100)
    {

        this->img = img;
        return true;
    }
    return false;
}

View::View(QImage img, Document* doc, int page)
{
    this->setView(img);
    //this->doc = new imgClass(img);
    this->doc = doc;
    this->realPage = page;
}

View::View(Document *doc, int n) :
    doc(0),
    page(n),
    realPage(n)
{
    if (doc->isOpened() && doc->getPageCount()+1 > n && n > 0)
    {
        this->doc = doc;
        this->setView(doc->getPage(n));

        //doc->getRealPage(n).save("/tmp/1.jpg");
        //this->doc->page(n)->renderToImage(
          //                  doc->page(n)->pageSize().width()
            //                ,doc->page(n)->pageSize().height());

        //connect(doc,SIGNAL(pageIsReady(QImage)),this,SLOT(imgForViewReady(QImage)));
    }
}
/*
void View::imgForViewReady(QImage img)
{
    if (this->img.isNull())
    {
        this->setView(img);
        //emit this->ready();
    }
    //disconnect(doc,SIGNAL(pageIsReady(QImage)),this,SLOT(imgForViewReady(QImage)));
}
*/
QImage View::getView()
{
    //doc->getPreview()
    //return this->doc->getPage(this->page);
    return this->img;

}

QImage View::getPreview(QSize size)
{
    return this->getView().scaled(size);
    //return this->doc->getPreview(this->page);
}
