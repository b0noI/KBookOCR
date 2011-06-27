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
    int rotate; // 0 - up, 1 - right, 2 - down, 3 - left
    int getRotateAngel();

private:
    QString getImgDir();
    //QImage img;
    QString path;





};

#endif // VIEW_H
