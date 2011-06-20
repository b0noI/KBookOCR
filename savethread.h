#ifndef SAVETHREAD_H
#define SAVETHREAD_H

#include <QThread>
#include <QProcess>
#include "viewwidget.h"

class SaveThread : public QThread
{
    Q_OBJECT
public:
    explicit SaveThread(QObject*,QList<ViewWidget*>, QString);
    ~SaveThread();
    void run();


signals:
    void process(int);
    void done(QString);
public slots:
    void saveReady();

private:
    QProcess* saveProcess;
    QString getTempDir();
    bool removeTempDir();
    bool removeDir(const QString&);
    QString savePath;
    QList<ViewWidget*> views;
    bool saveViews();
    bool startSave();
};

#endif // SAVETHREAD_H
