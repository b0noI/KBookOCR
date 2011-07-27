#include "ocrthread.h"
#include <QFileInfo>
#include <QFileInfoList>
#include <QDir>
#include <QTextStream>


OCRThread::OCRThread(QObject *parent, QString inPath, QString lang, bool html, OCRKernel* ker) :
    QThread(parent),
    OCRProccess(0),
    SpliterProcess(0),
    isReady(false),
    kernel(ker)
{

    this->lang = lang;
    this->inPath = inPath;

    this->html = html;

    connect (this,SIGNAL(OCRReady()),this,SLOT(split()));


}

void OCRThread::run()
{
    QFileInfo inf(inPath);
    if (inf.exists() && inf.isDir())
    {
        QDir dir(inPath);
        QFileInfoList files = dir.entryInfoList();
        QFileInfo tempInf;
        foreach (tempInf, files)
        {
            if (tempInf.fileName() != "." &&
                    tempInf.fileName() != "..")
                this->addImges(tempInf.filePath());

        }
        this->count = this->getImgCount();
        this->startOCR();
        //while(!this->isReady)
        //{
        //    wait(30000);
        //}
        //this->wait();
        //this->sleep();
        exec();
    }
}

void OCRThread::txtReady(int)
{
    if (this->getImgCount() > 0)
        this->nextTXTOCR(this->getImgAt(0));
    else
        this->spliter();
}

void OCRThread::splitReady()
{


    this->isReady = true;
    emit this->ready(this->outPath);
}

bool OCRThread::spliter()
{
    QDir dir(this->imgDir);
    if (dir.exists())
    {

        QString path = this->imgDir + QDir::separator()+"all"+(this->html ? ".html" : ".txt");
        this->outPath = path;

        QFile outFile(this->outPath);
        outFile.open(QIODevice::WriteOnly);
        QTextStream outStream(&outFile);
        //outStream << this->SpliterProcess->readAll();


        QFileInfoList files = dir.entryInfoList();
        QFileInfo inf;
        QString suf = this->html ? "html" : "txt";
        foreach (inf, files)
        {
            if (inf.suffix().toLower() == suf && inf.fileName() != "all")
            {
                QFile inFile(inf.filePath());
                inFile.open(QIODevice::ReadOnly);
                QTextStream inStream(&inFile);
                QString text = inStream.readAll();
                outStream << text;
                inFile.close();
            }
        }

        outFile.close();



        this->splitReady();
/*
        if (this->SpliterProcess)
            delete this->SpliterProcess;

        this->SpliterProcess = new QProcess(this);
        connect (this->SpliterProcess,SIGNAL(finished(int)),this,SLOT(splitReady()));

        //if (!this->saveToFile)
        //    this->setPathToSave(pathTo);

        QString path = this->imgDir + QDir::separator()+"all.txt";
        //QFileInfo inf(path);
        //QString pathTo = inf.filePath() + ".txt";

        QStringList args;
        args.clear();
        args << this->imgDir+QDir::separator()+"*.txt";// > "+path;
        //args << ">";
        //args << path;
    //    args << pathTo;
       // args << pathFrom;
        //args.append(ui->comboBox->currentText());

        //if (ui->checkBox->isChecked())
        //{
        //    args.append(KBookocr::fromFormatToStr(this->getOutFormat()));
        //}
        //else
        //{
        //    args.append("text");
        //}


        //this->SpliterProcess->readAll()
        this->SpliterProcess->start("cat",args);
*/
        return true;
    }
    return false;
}

OCRThread::~OCRThread()
{
    if (this->OCRProccess)
    {
        this->OCRProccess->kill();
        delete this->OCRProccess;
    }

    if (this->SpliterProcess)
    {
        this->SpliterProcess->kill();
        delete this->SpliterProcess;
    }
}

bool OCRThread::startOCR()
{
    if (this->getImgCount() > 0)
    {
        QFileInfo inf(this->getImgAt(0));
        this->imgDir = inf.path();
        this->nextTXTOCR(this->getImgAt(0));
    }
}

bool OCRThread::removeImg(QString path)
{
    if (this->imges.contains(path))
    {
        this->imges.removeAt(this->imges.indexOf(path));
        return true;
    }
    return false;
}

void OCRThread::nextTXTOCR(QString path)
{
    if (this->removeImg(path))
    {
     // OCR
        emit this->process(((double)this->count - (double)this->getImgCount())/((double)this->count/(double)100));
        //if (this->OCRProccess)
        //    delete this->OCRProccess;
        //if (this->kernel)
        //    delete this->kernel;

        // = new QProcess(this);
        //connect (this->OCRProccess,SIGNAL(finished(int)),this,SLOT(txtReady(int)));
        connect (this->kernel,SIGNAL(ocrReady(QString)),this,SLOT(txtReady(int)));

        /*QString pathFrom = path;
        QFileInfo inf(path);
        QString pathTo = inf.filePath() +( this->html ? ".html" : ".txt");

        QStringList args;
        args.clear();
        args << "-l";
        args << this->lang;
        if (this->html)
            args << "-f" << "html";
        args << "-o";
        args << pathTo;
        args << pathFrom;

        OCRProccess->start("cuneiform",args);*/
        this->kernel->startOCR(pathFrom, pathTo, this->lang, this->html);
    }

}

int OCRThread::getImgCount()
{
    return this->imges.count();
}

QString OCRThread::getImgAt(int n)
{
    if (n >= 0 && n < this->getImgCount())
    {
        return this->imges.at(n);
    }
}

bool OCRThread::addImges(QString path)
{
    QFileInfo inf(path);
    if (inf.exists())
    {
        if (this->isImg(path))
        {
            this->imges << path;
            return true;
        }
    }
    return true;
}

bool OCRThread::isImg(QString path)
{
    QFileInfo inf(path);
    if (inf.exists())
    {
        QString suffix = inf.suffix().toLower();
        if (suffix == "png"
                || suffix == "jpg"
                || suffix == "jpeg"
                || suffix == "bmp"
                || suffix == "png")
            return true;
    }
    return false;
}
