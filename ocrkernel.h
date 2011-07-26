#ifndef OCRKERNEL_H
#define OCRKERNEL_H

#include <QString>
#include <QStringList>
#include <QObject>
#include <QProcess>

class OCRKernel : public QObject
{
    Q_OBJECT

public:
    OCRKernel();
    ~OCRKernel();
    virtual bool startOCR(const QString& from,const QString& to,const QString& lang, bool layout) = 0;

signals:
    void ocrReady(QString);


private:
    bool startOCRProcess(const QString&,const QStringList&);
    bool deleteOCRProcess();
    QProcess* ocrProcess;
    QString toPath;
    QString getToPath() const;
private slots:
    void ocrReady(int);
};

#endif // OCRKERNEL_H
