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
    QImage getView();
    QImage getPreview(QSize);
    //bool setView(const QImage&);

private:
    QImage img;
    Document* doc;
    int page;
    //QSize previewSize();


};

#endif // VIEW_H
