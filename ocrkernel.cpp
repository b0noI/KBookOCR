#include "ocrkernel.h"

OCRKernel::OCRKernel()
{
    this->ocrProcess = 0;
}

OCRKernel::~OCRKernel()
{
    this->deleteOCRProcess();
}

bool OCRKernel::startOCRProcess(const QString &prog, const QStringList &args)
{
    if (args.isEmpty() || args.size() < 2)
        return false;

    this->deleteOCRProcess();

    this->ocrProcess = new QProcess(this);
    connect (this->ocrProcess, SIGNAL(finished(int)),this,SLOT(ocrReady(int)));
    this->ocrProcess->start(prog, args);
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

bool OCRKernel::deleteOCRProcess()
{
    if (this->ocrProcess)
    {
        delete this->ocrProcess;
        this->ocrProcess = 0;
        return true;
    }
    return false;
}
