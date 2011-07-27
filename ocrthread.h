#ifndef OCRTHREAD_H
#define OCRTHREAD_H

#include <QThread>
#include <QList>
#include <QString>
#include <QProcess>

#include "ocrkernel.h"


class OCRThread : public QThread
{
    Q_OBJECT
public:
    explicit OCRThread(QObject *parent, QString, QString lang, bool html, OCRKernel*);
    ~OCRThread();
    void run();

signals:

    void ready(QString);
    void process(int);

public slots:
    void txtReady(int);
    void nextTXTOCR(QString);
    void splitReady();

private:

    bool startOCR();
    bool addImges(QString);
    int getImgCount();
    QString getImgAt(int);
    bool isImg(QString);
    bool removeImg(QString);
    bool spliter();

    QString lang;
    QString imgDir;
    QString outPath;
    QString inPath;

    //QProcess* OCRProccess;
    QProcess* SpliterProcess;
    OCRKernel* kernel;
    QList<QString> imges;
    QList<QString> txts;

    bool isReady;
    bool html;
    int count;
};

#endif // OCRTHREAD_H
