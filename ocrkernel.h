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
    OCRKernel(const QString&);
    ~OCRKernel();

    virtual QString getProgName() const = 0;

    bool startOCR(const QString& from,const QString& to,const QString& lang, bool layout);
    bool setProg(const QString&);
    QString getProg() const;


signals:
    void ocrReady(QString);

protected:
    virtual QStringList generateArgs(const QString& from,const QString& to,const QString& lang, bool layout) const = 0;

private:
    bool startOCRProcess(const QStringList&);
    bool deleteOCRProcess();
    QProcess* ocrProcess;
    QString toPath;
    QString getToPath() const;

    QString prog;
    bool isReady() const;

private slots:
    void ocrReady(int);
};

#endif // OCRKERNEL_H
