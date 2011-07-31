#include "tesseractocr.h"

#include <QApplication>

TesseractOCR::TesseractOCR() :
    OCRKernel("tesseract")
{
}

QString TesseractOCR::getFormat() const
{
    return "tif";
}

QString TesseractOCR::getProgName() const
{
    return "Tesseract-OCR";
}

QStringList TesseractOCR::getLanguageList () const
{
    return QStringList()
            << QApplication::translate("KBookocr", "eng", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "deu", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "fra", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "ita", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "nld", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "por", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "spa", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "vie", 0, QApplication::UnicodeUTF8);
}

QStringList TesseractOCR::generateArgs(const QString &from, const QString &to, const QString &lang, bool layout) const
{
    QStringList args;
    args.clear();
    args << from;
    args << to;

    return args;
}
