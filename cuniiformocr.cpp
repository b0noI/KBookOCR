//#include <QFileInfo>

#include "cuniiformocr.h"

#include <QApplication>

CuniIFormOCR::CuniIFormOCR() :
    OCRKernel("cuneiform")
{
}

QString CuniIFormOCR::getProgName() const
{
    return "CuneIForm";
}

QString CuniIFormOCR::getFormat() const
{
    return "jpg";
}

QStringList CuniIFormOCR::getLanguageList () const
{
    return QStringList()
            << QApplication::translate("KBookocr", "ruseng", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "rus", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "ukr", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "eng", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "ger", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "fra", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "swe", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "spa", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "ita", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "srp", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "hrv", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "pol", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "dan", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "por", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "dut", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "cze", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "rum", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "hun", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "bul", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "slo", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "lav", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "lit", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "est", 0, QApplication::UnicodeUTF8)
            << QApplication::translate("KBookocr", "tur", 0, QApplication::UnicodeUTF8);
}

QStringList CuniIFormOCR::generateArgs(const QString &from, const QString &to, const QString &lang, bool layout) const
{
    QString pathFrom = from;
    //QFileInfo inf(from);
    //QString pathTo = inf.filePath() +( layout ? ".html" : ".txt");

    QStringList args;
    args.clear();
    args << "-l";
    args << lang;
    if (layout)
        args << "-f" << "html";
    args << "-o";
    args << to;
    args << pathFrom;
    return args;
}
