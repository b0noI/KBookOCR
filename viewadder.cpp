#include "viewadder.h"
#include "viewwidget.h"
#include <QThread>

viewAdder::viewAdder(QObject *parent,QLayout* _la, Document *_doc, int _start) :
    QThread(parent),
    la(_la),
    doc(_doc),
    START(_start)
{
}

void viewAdder::run()
{
    if (doc)
    {
        for (int i=1;i<=doc->getPageCount();i++)
            this->addView(doc,i);
    }
    //this->exec();
}

void viewAdder::Execute()
{
    start();
}

bool viewAdder::addView(Document *doc, int n)
{
    if (doc)
    {
        //int t = n;
        ViewWidget* view = new ViewWidget(this->getNewId(),0,doc,n);
        //ui->scrollAreaWidgetContents_2->children().append();
        la->addWidget(view);
        return true;
    }
    return false;
}

int viewAdder::getNewId()
{
    return this->START++;
}
