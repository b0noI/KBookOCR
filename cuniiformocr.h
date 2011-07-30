#ifndef CUNIIFORMOCR_H
#define CUNIIFORMOCR_H
#include "ocrkernel.h"

class CuniIFormOCR : public OCRKernel
{
public:
    CuniIFormOCR();
    QString getProgName() const;



private:
    QStringList generateArgs(const QString& from,const QString& to,const QString& lang, bool layout) const;
};

#endif // CUNIIFORMOCR_H
