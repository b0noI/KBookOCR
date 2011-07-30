//#include <QFileInfo>

#include "cuniiformocr.h"

CuniIFormOCR::CuniIFormOCR() :
    OCRKernel("cuneiform")
{
}

QString CuniIFormOCR::getProgName() const
{
    return "CuneIForm";
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
