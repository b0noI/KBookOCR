#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QImage>
#include <QString>
#include <QSize>
#include <QObject>

class Document : public QObject
{
    Q_OBJECT

public:
    Document();
    virtual QImage getPage(int) = 0;
    virtual int getPageCount() = 0;
    virtual QString getFormat() = 0;
    virtual bool open(QString) = 0;
    virtual bool close() = 0;
    QString getPath();
    bool setPath(const QString&);
    virtual QImage getPreview(int);
    bool setPreviewSize(const QSize&);
    QSize getPreviewSize();
    bool isOpened();

signals:
    void opened();

protected:
     bool ready;

private:
    QString path;
    QSize previewSize;
};

#endif // DOCUMENT_H
