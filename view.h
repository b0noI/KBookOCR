#ifndef VIEW_H
#define VIEW_H

#include <QString>
#include <QImage>
#include <QSize>
#include "document.h"

class View
{
public:
    //View(QString);
    View(Document*, int);
    View(QImage, Document*, int);
    QImage getView();
    QImage getPreview(QSize);
    bool setView(const QImage&);

protected:
    Document* doc;
    int page;
    int realPage;

private:
    QImage img;

    //QSize previewSize();


};

#endif // VIEW_H
