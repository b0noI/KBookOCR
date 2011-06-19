#include "viewadder.h"
#include <QThread>

viewAdder::viewAdder(QWidget *parent,QLayout* _la, Document *_doc, int _start) :
    QThread(parent),
    parr(parent),
    la(_la),
    doc(_doc),
    START(_start)
{
}

void viewAdder::run()
{
    if (doc)
    {
        for (int i=0;i<doc->getPageCount();i++)
        {
            emit this->done(doc->getPageCount(),i);
            //this->addView(doc,i);
            emit this->newImgDone(doc->getPage(i),i,doc);
        }
    }
    //exec();
    //this->exec();
}

void viewAdder::Execute()
{
    start();
}

bool viewAdder::addView(Document *doc, int n)
{
    //emit this->newImgDone(doc->getPage(n));
    return true;
    //````
    if (doc)
    {
        //int t = n;
        ViewWidget* view = new ViewWidget(this->getNewId(),/*this->parr*/0,doc,n);
        //ui->scrollAreaWidgetContents_2->children().append();
        //la->addWidget(view);
        emit this->newViewReady(view);
        //this->widgetVector << view;
        return true;
    }
    return false;
}

int viewAdder::getWidgetCount()
{
    return this->widgetVector.count();
}

ViewWidget* viewAdder::getWidgetAt(int n)
{
    if (n >= 0 && n < this->getWidgetCount())
    {
        return this->widgetVector.at(n);
    }
}

int viewAdder::getNewId()
{
    return this->START++;
}
