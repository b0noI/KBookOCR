#ifndef VIEWADDER_H
#define VIEWADDER_H

#include <QThread>
#include <QLayout>
#include "document.h"

class viewAdder : public QThread
{
    Q_OBJECT
public:
    explicit viewAdder(QObject*,QLayout*, Document*,int);
    void run();
    int getNewId();

signals:

public slots:

private:
    bool addView(Document* , int);
    QLayout* la;
    Document* doc;
    int start;

};

#endif // VIEWADDER_H
