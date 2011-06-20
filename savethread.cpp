#include "savethread.h"
#include <QDir>

SaveThread::SaveThread(QObject* parent, QList<ViewWidget*> _views, QString path) :
    QThread(parent),
    savePath(path),
    views(_views),
    saveProcess(0)
{

}

SaveThread::~SaveThread()
{
    if (this->saveProcess)
    {
        this->saveProcess->kill();
        delete this->saveProcess;
    }
}

void SaveThread::run()
{
    this->removeTempDir();
    if (this->saveViews())
    {

        this->startSave();

        this->exec();
    }

}

bool SaveThread::startSave()
{
    if (!this->savePath.isEmpty())
    {
        if (this->saveProcess)
        {
            delete this->saveProcess;

        }

        this->saveProcess = new QProcess(this);

        connect (this->saveProcess,SIGNAL(finished(int)),this,SLOT(saveReady()));

        QString prog = "save.sh";
        QStringList args;
        args << this->getTempDir() + "*.jpg";
        args << this->savePath;

        /*QString prog = "gzip";
        QStringList args;
        args << this->getTempDir() + "*.jpg";*/
        this->saveProcess->start(prog,args);

        //QString outPut = this->saveProcess->readAll();

        return true;
    }
    return false;
}

void SaveThread::saveReady()
{
    emit this->done(this->savePath);
}

bool SaveThread::saveViews()
{
    if (this->views.count() > 0)
    {
        ViewWidget* view;
        double done = 0;
        foreach (view, this->views)
        {
            double all = this->views.count();
            done++;
            QString fileSavePath = this->getTempDir()+"KbookOCR."+
                    QString::number(view->get_Id())+
                    ".jpg";
            view->saveImg(fileSavePath);
            emit this->process((int)((done*100)/all));
        }

        return true;
    }
    return false;
}

QString SaveThread::getTempDir()
{
    QString dirPath = QDir::tempPath() + QDir::separator() + "temp.KBookOCR.save" + QDir::separator();
    QDir dir(dirPath);
    if (!dir.exists())
    {
        dir.mkdir(dirPath);
    }
    return dirPath;
}

bool SaveThread::removeTempDir()
{
    return this->removeDir(this->getTempDir());
}

bool SaveThread::removeDir(const QString &dirName)
{
    bool result = true;
    QDir dir(dirName);

    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }

            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }

    return result;
}

