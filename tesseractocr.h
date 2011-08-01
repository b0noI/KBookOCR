#ifndef TESSERACTOCR_H
#define TESSERACTOCR_H

#include "ocrkernel.h"

class TesseractOCR : public OCRKernel
{
public:
    TesseractOCR();
    QString getFormat() const;
    QString getProgName() const;
    QStringList getLanguageList () const;
protected:
    QStringList generateArgs(const QString& from,const QString& to,const QString& lang, bool layout) const;
};

#endif // TESSERACTOCR_H
