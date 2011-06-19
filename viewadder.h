#ifndef VIEWADDER_H
#define VIEWADDER_H

#include <QThread>
#include <QLayout>
#include "document.h"
#include "viewwidget.h"

class viewAdder : public QThread
{
    Q_OBJECT
public:
    explicit viewAdder(QWidget*,QLayout*, Document*,int);
    void run();
    void Execute();
    int getNewId();
    int getWidgetCount();
    ViewWidget* getWidgetAt(int);


signals:
    void done(int,int);
    void newViewReady(ViewWidget*);
    void newImgDone(QImage,int);

public slots:

private:
    QWidget* parr;
    bool addView(Document* , int);
    QLayout* la;
    Document* doc;
    int START;
    QList<ViewWidget*> widgetVector;

};

#endif // VIEWADDER_H
