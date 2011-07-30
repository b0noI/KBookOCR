#include "ocrkernel.h"
#include <QFileInfo>

OCRKernel::OCRKernel(const QString& prog)
{
    this->ocrProcess = 0;
    this->setProg(prog);
}

OCRKernel::~OCRKernel()
{
    this->deleteOCRProcess();
}

bool OCRKernel::setProg(const QString &prog)
{
    if (prog.isEmpty())
        return false;

    this->prog = prog;
    return true;
}

QString OCRKernel::getProg() const
{
    return this->prog;
}

bool OCRKernel::isReady() const
{
    if (this->getProg().isEmpty())
        return false;

    return true;
}

bool OCRKernel::startOCRProcess(const QStringList &args)
{
    if (args.isEmpty() || args.size() < 2 || !this->isReady())
        return false;

    this->deleteOCRProcess();

    this->ocrProcess = new QProcess(this);
    connect (this->ocrProcess, SIGNAL(finished(int)),this,SLOT(ocrReady(int)));
    this->ocrProcess->start(this->getProg(), args);
}

QString OCRKernel::getToPath() const
{
    return this->toPath;
}

void OCRKernel::ocrReady(int)
{
    emit this->ocrReady(this->getToPath());
    this->deleteOCRProcess();
}

bool OCRKernel::startOCR(const QString &from, const QString &to, const QString &lang, bool layout)
{
    QFileInfo fromInf(from);
    if (!fromInf.exists())
        return false;
    QStringList args = this->generateArgs(from, to, lang, layout);

    if (args.count() < 2)
        return false;

    this->startOCRProcess(args);
    return true;
}

bool OCRKernel::deleteOCRProcess()
{
    if (this->ocrProcess != 0)
    {
        delete this->ocrProcess;
        this->ocrProcess = 0;
        return true;
    }
    return false;
}
