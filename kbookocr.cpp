#include "kbookocr.h"
#include "ui_kbookocr.h"

//#include "enum.h"
//#include "wizard.h"

#include <QFileDialog>
#include <QImage>
#include <QSize>
#include <QFileInfo>
#include <QMessageBox>
#include <QSettings>
#include <QDialog>
#include <QSpacerItem>

#include "imgclass.h"
#include "pdfdocument.h"
#include "djvudocument.h"

#include <kurl.h>

#include <poppler/qt4/poppler-qt4.h>

KBookocr::KBookocr(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KBookocr),
    pdf (true),
    open(false),
    currentPage(1),
    saveToFile(false),
    outFormat(RTF),
    idCount(0),
    adder(0)
    //currentDoc(this)
{



    ui->setupUi(this);

    //ui->verticalLayout->addWidget(this->currentDoc.widget());

    //this->scanDialog = KScanDialog::getScanDialog( this );
    //if (this->scanDialog)
    //{
    //    connect (this->scanDialog,SIGNAL(finalImage(QImage,int)),this,SLOT(scanComplete(QImage,int)));
    //}

    ui->groupBox->setVisible(false);
    //ui->groupBox->
   // ui->label_11->setVisible(false);

    QSettings settings("KBookOCR", "snapShot");
    //if (settings.allKeys().contains("load"))
    //{
        //QDialog dialog();
        //if (settings.value("load").toBool()/* && dialog.exec()*/)
        //{
            //ui->pushButton_3->setVisible(true);
        //}
        //else
            //ui->pushButton_3->setVisible(false);
    //}else
        //ui->pushButton_3->setVisible(false);

    //ui->lineEdit_2->setVisible(false);

    this->bookOCRProcess = 0;
    this->scanProcess = 0;
    this->libreOfficeProcess = 0;
    this->getScanPreviewProcess = 0;
    this->convertDjvu2Pdf = 0;

    size.setWidth(0);

    ui->radioButton_7->setVisible(false);

    this->setVisibleScanOrFile(false);


    /*
    ui->label_view1->setMaximumSize(60,120);
    ui->label_view1->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    ui->label_view2->setMaximumSize(60,120);
    ui->label_view2->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    ui->label_view3->setMaximumSize(60,120);
    ui->label_view3->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    ui->label_view4->setMaximumSize(60,120);
    ui->label_view4->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    */

    //connect (this->viewWidgets,SIGNAL())
}

void KBookocr::selectedViewId(int id)
{
    for (int i=0;i<this->getPageCount();i++)
        if (this->viewWidgets.at(i)->get_Id() == id)
        {
            ui->spinBox_3->setValue(i+1);
            return;
        }
}

void KBookocr::scanComplete(const QImage &img, int n)
{
    this->newImgAdd(img,n);
}

void KBookocr::pageCounChanged(int n)
{
    ui->spinBox_3->setMaximum(n);
    ui->spinBox_3->setSuffix(" / "+QString::number(n));
    for (int i=0;i<this->viewWidgets.count();i++)
        this->viewWidgets[i]->setPageNumber(i+1);
}

int KBookocr::getNewId()
{
    return this->idCount++;
}

bool KBookocr::openDoc(QString path)
{
    //if (this->currentDoc)
    //    delete this->currentDoc;
    //this->currentDoc = new Okular::Document(this);
    //currentDoc->openDocument()

   // KUrl url(path);
    //KMimeType::Ptr mime;
    //this->currentDoc.openDocument(path, url);
}

KBookocr::~KBookocr()
{
    this->save();

    if (this->getScanPreviewProcess)
    {
        this->getScanPreviewProcess->kill();
        delete this->getScanPreviewProcess;
    }

    if (this->convertDjvu2Pdf)
    {
        this->convertDjvu2Pdf->kill();
        delete this->convertDjvu2Pdf;
    }

    if (this->bookOCRProcess)
    {
        this->bookOCRProcess->kill();
        delete this->bookOCRProcess;
    }

    if (this->libreOfficeProcess)
    {
        this->libreOfficeProcess->kill();
        delete this->libreOfficeProcess;
    }

    /*if (this->previewDJVUProcess)
    {
        this->previewDJVUProcess->kill();
        delete this->previewDJVUProcess;
    }*/
    //this->openOfficeProcess->

    if (this->scanProcess)
    {
        this->scanProcess->kill();
        delete this->scanProcess;
    }

    if (this->adder)
        delete this->adder;

    delete ui;
}

void KBookocr::load()
{
    QSettings settings("KBookOCR", "snapShot");
    if (settings.allKeys().contains("load"))
    {
        //QDialog dialog();
        if (settings.value("load").toBool()/* && dialog.exec()*/)
        {
            ui->radioButton->setChecked(
                        settings.value("allPages").toBool());
            //, ui->radioButton->isChecked());
            ui->radioButton_2->setChecked(
                        settings.value("pagesFromTo").toBool());
            //, ui->radioButton_2->isChecked());
            ui->radioButton_3->setChecked(
                        settings.value("manualPages").toBool());
            //, ui->radioButton_3->isChecked());

            //this->pageChecked = (QList<bool>)(settings.value("listOfPages"));//, this->pageChecked);

            this->currentPage =
                    settings.value("currentPage").toInt();//, this->currentPage);

            this->currentFirstView =
                    settings.value("currentFirstPage").toInt();//, this->currentFirstView);

            //ui->lineEdit_2->setText(
              //  settings.value("inPath").toString());//, ui->lineEdit_2->text());

            this->setPathToSave(
                settings.value("outPath").toString());//, this->getPathToSave());

            this->setVisibleScanOrFile(true);
            //ui->lineEdit_2->setText(QFileDialog::getOpenFileName());
            this->openFiles();

            //settings.setValue("load", true);
        }
    }
}

void KBookocr::save()
{
    QSettings settings("KBookOCR", "snapShot");
    /*if (this->isFileMode())
    {*/



        settings.setValue("allPages", ui->radioButton->isChecked());
        settings.setValue("pagesFromTo", ui->radioButton_2->isChecked());
        settings.setValue("manualPages", ui->radioButton_3->isChecked());

        //settings.setValue("listOfPages", this->pageChecked);

        settings.setValue("currentPage", this->currentPage);
        settings.setValue("currentFirstPage", this->currentFirstView);
        //settings.setValue("inPath", ui->lineEdit_2->text());
        settings.setValue("outPath", this->getPathToSave());
        settings.setValue("load", true);
        //settings.setValue("isSaveMode", 68);

 /*   }
    else
        settings.setValue("load", false);*/
}

QString KBookocr::fromFormatToStr(OUT_FORMAT format)
{
    switch (format)
    {
        case HTML:
            return "html";
        break;

    case RTF:
        return "rtf";
    break;

    case HOCR:
        return "hocr";
    break;


    };

    return "ERROR";
}

OUT_FORMAT KBookocr::getOutFormat()
{
    return this->outFormat;
}

bool KBookocr::setOutFormat(OUT_FORMAT format)
{
    if (this->outFormat == format)
        return false;
    this->outFormat = format;
    return true;
}

bool KBookocr::setPathToSave()
{
    QString tmp;
    tmp = QFileDialog::getSaveFileName();
    if (tmp.isEmpty())
        return false;
    this->pathToSave = tmp;
    return true;
}

QString KBookocr::getPathToSave()
{
    return this->pathToSave;
}

bool KBookocr::setPathToSave(const QString &path)
{
    if (!path.isEmpty())
    {
        this->pathToSave = path;
        return true;
    }
    return false;
}
/*
void KBookocr::scanComplete(int)
{
    QString path, pathTo, base;

    base = ui->checkBox->isChecked() ? KBookocr::fromFormatToStr(this->getOutFormat()) : "txt";

    //path =  ui->radioButton_9->isChecked() ? QDir::tempPath() + "/tmp.tiff" : ui->lineEdit_3->text();
    pathTo = !this->saveToFile ? QDir::tempPath() + "/tmp." + base : this->getPathToSave();

    QImage image;
    image.load(path);
    this->baseSize = image.size();
    this->setSize();
    image = image.scaled(size);
    ui->label_3->setMaximumSize(size);
    ui->label_3->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    QPixmap pm;
    ////pm.convertFromImage(image);

    pm = QPixmap::fromImage(image);

    pm = QPixmap::fromImage(image);

    ui->label_3->setPixmap(pm);

    if (!this->saveToFile)
    {
        this->setPathToSave(pathTo);
        this->openOfficeOpen(1);
    }
    /*
    QImage image = doc->page(newValue)->renderToImage(100,100);
    this->baseSize = image.size();
    if (size.width() > 0)
    {
        this->setSize();
        image.scaled(size);
        //ui->label_3->setSizePolicy();
        ui->label_3->setMaximumSize(size);
        ui->label_3->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

     */
//}

QString KBookocr::formImgFromPdf()
{
    QString dirPath;
    if (this->open && this->pdf)
    {
        this->convToImg = new convertingToImgWite();
        this->convToImg->show();


        dirPath = QDir::tempPath() + QDir::separator()+ "KBookOCR.OCR" + QDir::separator();
        QDir dir;
        if (dir.exists(dirPath))
        {
            dir.rmdir(dirPath);
        }
        dir.mkdir(dirPath);
        //dirPath =

        bool convert[this->doc->numPages()];

        int all = 0;

        if (ui->radioButton->isChecked())
        {
            for (int i=0;i<this->doc->numPages();i++)
                convert[i] = true;
            all = this->doc->numPages();
        }
        else
            if (ui->radioButton_2->isChecked())
            {
                for (int i=0;i<this->doc->numPages();i++)
                    if (i > ui->spinBox->value() && i < ui->spinBox_2->value())
                    {
                        convert[i] = true;
                        all++;
                    }
                    else
                        convert[i] = false;
            }
        else
                if (ui->radioButton_3->isChecked())
                {
                     for (int i=0;i<this->doc->numPages();i++)
                     {
                         //convert[i] = this->pageChecked.at(i);
                         if (convert[i])
                             all++;
                     }
                }
        int cur=0;
        for (int i=0;i<this->doc->numPages();i++)
            if (convert[i])
            {
                QImage img = doc->page(i+1)->renderToImage(100,100);
                img.save(dirPath+QString::number(i)+".png");
                this->convToImg->setProgress(cur,all);
                cur++;
            }

        return dirPath;

        this->convToImg->hide();
        delete this->convToImg;
    }
    return dirPath;
}

void KBookocr::scanAndOCR()
{
    QString program = "scan.sh";

    QStringList param;
    param.clear();

    QString base;
    base = ui->checkBox->isChecked() ? KBookocr::fromFormatToStr(this->getOutFormat()) : "txt";

    QString pathTo, pathFrom;
    pathTo = !this->saveToFile ? QDir::tempPath() + "/tmp." + base : this->getPathToSave();
    //pathFrom = ui->radioButton_9->isChecked() ? QDir::tempPath() + "/tmp.tiff" : ui->lineEdit_3->text();

    param << pathFrom << pathTo << ui->comboBox->currentText();

    this->scanProcess = new QProcess(this);
    connect (this->scanProcess,SIGNAL(finished(int)),this,SLOT(scanComplete(int)));
    this->scanProcess->start(program, param);
}

void KBookocr::OCRFromFile()
{
     QString dirIn;
     dirIn = this->formImgFromPdf();

     QString pathFrom, pathTo;

     //pathFrom = ui->lineEdit_2->text();
     pathFrom = dirIn;

     pathTo = this->getPathToSave();

     QString base;
     base = ui->checkBox->isChecked() ? KBookocr::fromFormatToStr(this->getOutFormat()) : "txt";

     QString program = "bookocr.sh";
     bookOCRProcess = new QProcess(this);


        connect (this->bookOCRProcess,SIGNAL(finished(int)),this,SLOT(openOfficeOpen(int)));


     if (!this->saveToFile)
         this->setPathToSave(pathTo);

     QStringList args;
     args.clear();
     args.append(pathFrom);
     args.append(pathTo);
     args.append(ui->comboBox->currentText());

     if (ui->checkBox->isChecked())
     {
         args.append(KBookocr::fromFormatToStr(this->getOutFormat()));
     }
     else
     {
         args.append("text");
     }

     bookOCRProcess->start(program,args);

     /*
     if (ui->radioButton->isChecked())
     {

         //QString base;
         //base = ui->checkBox->isChecked() ? KBookocr::fromFormatToStr(this->getOutFormat()) : "txt";

         if (!this->saveToFile)
             pathTo = QDir::tempPath()+"/tmp."+base;


         QString program = "bookocr.sh";
         bookOCRProcess = new QProcess(this);
         connect (this->bookOCRProcess,SIGNAL(finished(int)),this,SLOT(openOfficeOpen(int)));
         if (!this->saveToFile)
             this->setPathToSave(pathTo);

         QStringList args;
         args.clear();
         args.append(pathFrom);
         args.append(pathTo);
         args.append(ui->comboBox->currentText());

         if (ui->checkBox->isChecked())
         {
             args.append(KBookocr::fromFormatToStr(this->getOutFormat()));
         }
         else
         {
             args.append("text");
         }

         bookOCRProcess->start(program,args);
     }

     if (ui->radioButton_2->isChecked())
     {
         QString base;
         base.clear();
         base = ui->checkBox->isChecked() ? KBookocr::fromFormatToStr(this->getOutFormat()) : "txt";

         if (!this->saveToFile)
             pathTo = QDir::tempPath()+"/tmp."+base;
             //ui->lineEdit->setText(QDir::tempPath()+"/tmp.txt");

         QString first;
         QString last;

         last =QString::number(ui->spinBox_2->value());

         while (last.size() != 3)
             last = "0"+last;

         first = QString::number(ui->spinBox->value());

         while (first.size() != 3)
             first = "0"+first;

         QString program = "bookocr.sh";// + pathFrom+" "+pathTo+" "+ui->comboBox->currentText()+ " "+first+" "+last;
         bookOCRProcess = new QProcess(this);
         connect (this->bookOCRProcess,SIGNAL(finished(int)),this,SLOT(openOfficeOpen(int)));
         if (!this->saveToFile)
             this->setPathToSave(pathTo);

         QStringList args;
         args.clear();
         args.append(pathFrom);
         args.append(pathTo);
         args.append(ui->comboBox->currentText());
         args.append(first);
         args.append(last);

         if (ui->checkBox->isChecked())
         {
             args.append(KBookocr::fromFormatToStr(this->getOutFormat()));
         }else
         {
             args.append("text");
         }

         bookOCRProcess->start(program,args);

         //bookOCRProcess->start(program);
     }


     if (ui->radioButton_3->isChecked())
     {

         QString base;
         base = ui->checkBox->isChecked() ? KBookocr::fromFormatToStr(this->getOutFormat()) : "txt";

         if (!this->saveToFile)
             pathTo = QDir::tempPath()+"/tmp."+base;
             //ui->lineEdit->setText(QDir::tempPath()+"/tmp.txt");

       //  QMessageBox::information(this,"test",pathFrom);

         QString program = "bookocr.sh";// + pathFrom+" "+pathTo+" "+ui->comboBox->currentText();
         bookOCRProcess = new QProcess(this);
         connect (this->bookOCRProcess,SIGNAL(finished(int)),this,SLOT(openOfficeOpen(int)));
         if (!this->saveToFile)
             this->setPathToSave(pathTo);

         QStringList args;
         args.clear();
         args.append(pathFrom);
         args.append(pathTo);
         args.append(ui->comboBox->currentText());

         if (ui->checkBox->isChecked())
         {
             args.append(KBookocr::fromFormatToStr(this->getOutFormat()));
         }
         else
         {
             args.append("text");
         }

         QString pageList;

         for (int i=0;i<this->makeListOfMarkedPages().count();i++)
         {
             if (i > 0)
                 pageList += (" "+QString::number(this->makeListOfMarkedPages().at(i)));
             else
                 pageList = QString::number(this->makeListOfMarkedPages().at(i));
         }

         args.append(pageList);

         bookOCRProcess->start(program,args);
     }
     */
}

void KBookocr::start()
{


    if (!this->isFileMode())
    {

        this->scanAndOCR();

    }
    else
    {
        this->OCRFromFile();
    }
}

void KBookocr::openOfficeOpen(int)
{
//ooffice -writer
    if (!this->saveToFile)
    {
        // OO
        QString program = "ooffice";// -writer " + ui->lineEdit->text();

        QStringList args;
        args.clear();
        args.append("-writer");
        args.append(this->getPathToSave());

        openOfficeProcess  = new QProcess(this);
        openOfficeProcess->start(program,args);
        //OO

        // LO
        program = "lowriter";// -writer " + ui->lineEdit->text();

        //QStringList args;
        args.clear();
        //args.append("-writer");
        args.append(this->getPathToSave());

        this->libreOfficeProcess  = new QProcess(this);
        this->libreOfficeProcess->start(program,args);
        //LO
        this->clearPathToSave();
    }
}

bool KBookocr::clearPathToSave()
{
    this->pathToSave = QString();
    return true;
}

void KBookocr::on_spinBox_3_valueChanged(int newValue)
{
    if (newValue > 0 && newValue < this->getPageCount())
    {
        QImage image = //doc->page(newValue)->renderToImage(100,100);
                this->viewWidgets.at(newValue - 1)->getView();
        this->baseSize = image.size();
        if (size.width() > 0)
        {
            this->setSize();
            image = image.scaled(size);
            //image = image.convertToFormat(QImage::Format_Mono);
            //ui->label_3->setSizePolicy();
            ui->label_3->setMaximumSize(size);
            ui->label_3->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

        }
        else
        {
            ui->label_3->setMaximumSize(image.size());
        }

        QPixmap pm;
        //pm.convertFromImage(image);

        pm = QPixmap::fromImage(image);
        ui->label_3->setPixmap(pm);
    }

    /*if (open && pdf)
    {
    QImage image = doc->page(newValue)->renderToImage(100,100);
    this->baseSize = image.size();
    if (size.width() > 0)
    {
        this->setSize();
        image = image.scaled(size);
        image = image.convertToFormat(QImage::Format_Mono);
        //ui->label_3->setSizePolicy();
        ui->label_3->setMaximumSize(size);
        ui->label_3->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    }
    else
    {
        ui->label_3->setMaximumSize(image.size());
    }

    QPixmap pm;
    //pm.convertFromImage(image);

    pm = QPixmap::fromImage(image);
    ui->label_3->setPixmap(pm);
    }
    /*else
    if (open && !pdf)
    {
        QString program = "djvuPageConv.sh";// + ui->lineEdit_2->text()+" "+QDir::tempPath()+"/tmp.tiff "+QString::number(newValue);

        QStringList args;
        args.clear();
        args.append(ui->lineEdit_2->text());
        args.append(QDir::tempPath()+"/tmp.tiff");
        args.append(QString::number(newValue));

        //this->previewDJVUProcess = new QProcess(this);

        QFile tmpFile(QDir::tempPath()+"/tmp.tiff");
        if (tmpFile.exists())
            tmpFile.remove();

        //this->previewDJVUProcess->start(program,args);
        //connect (this->previewDJVUProcess,SIGNAL(finished(int)),this,SLOT(previewDJVUChanged(int)));

        //openOfficeProcess  = new QProcess(this);
        //openOfficeProcess->start(program);

    }
*//*
    if (open)
    {
        this->currentPage = newValue;
    }*/
}

void KBookocr::setSize()
{
    if (ui->radioButton_7->isChecked())
    {

        this->size.setHeight(this->baseSize.height() * 2);
        this->size.setWidth(this->baseSize.width() * 2 );
        //ui->label_3->setMaximumSize(size);

    }

    if (ui->radioButton_6->isChecked())
    {

        this->size.setHeight(this->baseSize.height()/2);
        this->size.setWidth(this->baseSize.width()/2);

    }

    if (ui->radioButton_8->isChecked())
    {
        this->size.setHeight(this->baseSize.height()- this->baseSize.height()/(ui->horizontalSlider->value()/2));
        this->size.setWidth(this->baseSize.width()- this->baseSize.width()/(ui->horizontalSlider->value()/2));
    }
}

void KBookocr::previewDJVUChanged(int)
{
    if(open)
    {
    QImage image;
    image.load(QDir::tempPath()+"/tmp.tiff");

    this->baseSize = image.size();

    if (size.width() > 0)
    {
        this->setSize();
        image = image.scaled(size);
        //ui->label_3->setSizePolicy();
        ui->label_3->setMaximumSize(size);
        ui->label_3->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
    }
    else
    {
        ui->label_3->setMaximumSize(image.size());
    }

    QPixmap pm;
    //pm.convertFromImage(image);

    pm = QPixmap::fromImage(image);
    ui->label_3->setPixmap(pm);

    if (ui->radioButton_8->isChecked())
    {
        //ui->radioButton_8->setEnabled(true);
        ui->horizontalSlider->setEnabled(true);
    }
    }
}

void KBookocr::on_radioButton_5_clicked() //set native size
{
    size.setWidth(0);
    ui->label_3->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    this->on_spinBox_3_valueChanged(this->currentPage);
}

void KBookocr::on_radioButton_6_clicked() //set small size
{
    //size.setWidth(240);
   // size.setHeight(320);

    this->setSize();
    this->on_spinBox_3_valueChanged(this->currentPage);
}

void KBookocr::on_radioButton_7_clicked()  //set big size
{
    size.setWidth(480);
    size.setHeight(640);

    this->on_spinBox_3_valueChanged(this->currentPage);
}

void KBookocr::on_spinBox_valueChanged(int newValue)
{
    if (!ui->radioButton_2->isChecked())
        ui->radioButton_2->setChecked(true);

    if (ui->spinBox_2->value() < newValue)
        ui->spinBox_2->setValue(newValue);
}

void KBookocr::on_spinBox_2_valueChanged(int newValue)
{

}

void KBookocr::on_horizontalSlider_valueChanged(int)
{
    if (!ui->radioButton_2->isChecked())
        ui->radioButton_2->setChecked(true);
}

void KBookocr::on_pushButton_4_clicked()
{
    //ui->lineEdit_3->setText(QFileDialog::getSaveFileName());
    //if (!ui->radioButton_10->isChecked())
    //{
      //  ui->radioButton_10->setChecked(true);
    //}
}

void KBookocr::on_horizontalSlider_sliderReleased()
{

    if (open)
    {

    if (!ui->radioButton_8->isChecked())
        ui->radioButton_8->setChecked(true);

    this->setSize();
    this->on_spinBox_3_valueChanged(this->currentPage);


    if (!pdf)
    {
        ui->horizontalSlider->setEnabled(false);
    }
    }


}
/*
QList<int> KBookocr::makeListOfMarkedPages()
{
    QList<int> pageList;
    for (int i=0;i<this->pageChecked.size();i++)
    {
        if (pageChecked.at(i))
            pageList << i+1;
    }
    return pageList;
}
*/
QString KBookocr::getVersion()
{
    return "2.0 beta";
}

void KBookocr::on_pushButton_5_clicked()
{
    //QString t = "dfhd";
    //t;

    QMessageBox::information(this,"KBookOCR","version "+this->getVersion()+" <p><a href=\"http://kbookocr.blogspot.com/ \">HomePage</a> <p>Based on <b>cuneiform</b> <p><p>Blog:  <a href=\"http://mr-protos.ya.ru/ \">mr-protos</a> <p>Blog:  <a href=\"http://b0noI.ya.ru\">b0noI</a>"+
                             "<p> Icons are used from \"Farm-Fresh Web Icons\" set <p>http://www.fatcow.com/free-icon");
}

void KBookocr::setVisibleScanOrFile(bool n) // true - file, false - scaner
{

    //ui->pushButton_3->setVisible(false);

    //this->setViewPanelVisible(false);

    if (n)
    {
        //ui->label_7->setVisible(true);
       // ui->lineEdit_2->setVisible(true);
        //ui->groupBox->setVisible(true);

        //ui->radioButton_9->setVisible(false);
        //ui->radioButton_10->setVisible(false);
        //ui->lineEdit_3->setVisible(false);
        //ui->pushButton_4->setVisible(false);
    }
    else
    {

        //ui->label_7->setVisible(false);
        //ui->lineEdit_2->setVisible(false);
        //ui->groupBox->setVisible(false);

        //ui->radioButton_9->setVisible(true);
        //ui->radioButton_10->setVisible(true);
        //ui->lineEdit_3->setVisible(true);
        //ui->pushButton_4->setVisible(true);
    }
}

bool KBookocr::startConvertFromDjvu(QString djvuPath, QString tiffPath, QString pdfPath)
{
    QFileInfo inf(djvuPath);
    if (inf.exists() && inf.suffix().toLower() == "djvu")
    {

        QString program = "djvu2pdf.sh";

        QStringList param;
        param.clear();

        param << djvuPath << tiffPath << pdfPath;

        this->convertDjvu2Pdf = new QProcess(this);
        connect (this->convertDjvu2Pdf,SIGNAL(finished(int)),this,SLOT(djvu2pdfReady(int)));
        this->convertDjvu2Pdf->start(program, param);
        return true;
    }
    return false;
}

void KBookocr::djvu2pdfReady(int)
{

    ui->pushButton_2->setEnabled(true);
    ui->pushButton_8->setEnabled(true);
    this->openFiles();
}

bool KBookocr::addView(Document *doc, int n)
{
    /*if (doc)
    {
        ViewWidget* view = new ViewWidget(this->getNewId(),this,doc,n);
        //ui->scrollAreaWidgetContents_2->children().append();
        ui->verticalLayout_10->addWidget(view);
        return true;
    }
    return false;*/
}

void KBookocr::openFiles()
{
    open = false;

    ui->label_3->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

    //QFileInfo fileIn(ui->lineEdit_2->text());
    //if (fileIn.exists())
    {
        //sif (fileIn.suffix().toLower() == "pdf" /*|| fileIn.suffix().toLower() == "djvu"*/)
        /*{
            //doc = Poppler::Document::load(ui->lineEdit_2->text());
            open = true;
            pdf = true;
        }
        else*/
        {
            //if (fileIn.suffix().toLower() == "djvu")
            {
                //this->djvuPath = ui->lineEdit_2->text();
                this->startConvertFromDjvu(this->djvuPath,QDir::tempPath()+QDir::separator()+"tmp.kbookocr.tiff",QDir::tempPath()+QDir::separator()+"tmp.kbookocr.pdf");
                //ui->lineEdit_2->setText(QDir::tempPath()+QDir::separator()+"tmp.kbookocr.pdf");

                open = false;
                pdf = false;

                ui->pushButton_2->setEnabled(false);
                ui->pushButton_8->setEnabled(false);

                return ;
                //QMessageBox::information(this,"KBookocr","There is no previe for *.djvu files");
            }
        }

    }

    if (open && pdf)
    {
        //this->setViewPanelVisible(true);
        //this->currentPage = 1;
        //ui->spinBox_3->setValue(1);
        //this->on_spinBox_3_valueChanged(1);
        ui->spinBox->setMaximum(doc->numPages());
        ui->spinBox_2->setMaximum(doc->numPages());

        ui->spinBox_3->setMaximum(doc->numPages());
        ui->spinBox_3->setSuffix(" / "+QString::number(doc->numPages()));

        //ui->verticalScrollBar->setMaximum(doc->numPages());

        /*QImage image = doc->page(1)->renderToImage(100,100);

        if (size.width() > 0)
            image.scaled(size);

        QPixmap pm;
        //pm.convertFromImage(image);

    pm = QPixmap::fromImage(image);
        ui->label_3->setPixmap(pm);*/

        //this->pageChecked.clear();
        //for (int i=0;i<this->doc->numPages();i++)
            //this->pageChecked << false;

    }
    if (open && !pdf)
    {

        ui->spinBox->setMaximum(1000);
        ui->spinBox_2->setMaximum(1000  );

        ui->spinBox_3->setMaximum(1000);
        ui->spinBox_3->setSuffix("");

    }

    if (open)
    {

        this->currentPage = 1;
        ui->spinBox_3->setValue(1);
        this->on_spinBox_3_valueChanged(1);
        this->currentFirstView = 1;
        //this->refreshViewPanel();

    }
}

Document* KBookocr::openPath(const QString &path)
{
    Document* doc = 0;
    QFileInfo inf(path);
    if (inf.exists())
    {
        if (this->isImg(inf))
        {
            doc = new imgClass(path);
        }
        else
        {
            if (this->isPdf(inf))
                doc = new pdfDocument(path);
            /*else
                if (this->isDjvu(inf))
                    doc = new djvuDocument(path);*/
        }

    }
    return doc;
}

bool KBookocr::isDjvu(QFileInfo inf)
{
    if (inf.exists() && inf.suffix().toLower() == "djvu")
        return true;
    return false;
}

bool KBookocr::isPdf(QFileInfo inf)
{
    if (inf.exists() && inf.suffix().toLower() == "pdf")
        return true;
    return false;
}

bool KBookocr::isImg(QFileInfo inf)
{
    QString suffix = inf.suffix().toLower();
    if (inf.exists() &&
            (suffix == "jpg" ||
             suffix == "jpeg" ||
             suffix == "bmp" ||
             suffix == "gif" ||
             suffix == "png"))
    {
        return true;
    }
    return false;
}

void KBookocr::on_pushButton_6_clicked()
{
    //this->setVisibleScanOrFile(true);

    //doc->setPreviewSize(QSize(70,110));
    /*if (doc)
    {
        for (int i=1;i<doc->getPageCount()+1;i++)
            this->addView(doc,i);
    }*/
    //if () TODO
    if (this->adder)
    {
        QMessageBox::warning(this,"KBookOCR","waite untill last book is adding");
        return ;
    }

    Document* doc = this->openPath(QFileDialog::getOpenFileName());
    if (doc)
    {
    this->adder = new viewAdder(this, ui->verticalLayout_10,doc, this->getNewId());
    connect(this->adder,SIGNAL(finished()),this,SLOT(addFinished()));
    connect(this->adder,SIGNAL(done(int,int)),this,SLOT(doneProgress(int,int)));
    connect(this->adder, SIGNAL(newViewReady(ViewWidget*)),this,SLOT(newViewAdd(ViewWidget*)));
    connect(this->adder,SIGNAL(newImgDone(QImage,int)),this,SLOT(newImgAdd(QImage,int)));

    ui->groupBox->setVisible(true);
   // ui->label_11->setVisible(true);

    this->idCount += doc->getPageCount();
    //this->adder->run();
    //this->adder->start
    this->adder->Execute();
    //this->adder->start();
    }
    //ui->lineEdit_2->setText(QFileDialog::getOpenFileName());
    //this->openFiles();
}

int KBookocr::getPageCount()
{
    return this->viewWidgets.count();
}

void KBookocr::doneProgress(int all, int done)
{
    done = (done*100)/all;
    ui->progressBar->setValue(done);
}

void KBookocr::addFinished()
{


    if (this->adder)
    {

        //for (int i=0;i<this->adder->getWidgetCount();i++)
          //  ui->verticalLayout_10->addWidget(this->adder->getWidgetAt(i));

        //this->update();

        delete this->adder;
        this->adder = 0;
        //this->idCount += doc->getPageCount();
    }


    ui->groupBox->setVisible(false);
    //ui->label_11->setVisible(false);
}

bool KBookocr::isFileMode()
{
    return ui->radioButton->isVisible();
}

void KBookocr::on_pushButton_7_clicked()
{
    //this->setVisibleScanOrFile(false);
    //this->getScanPreview();
    if (!this->scanDialog)
    {
        QMessageBox::warning(this,"KBookOCR","There is no scan support in system");
    }else
    {
        if (this->scanDialog->setup())
            this->scanDialog->show();
    }
}

void KBookocr::getScanPreview()
{
    QPixmap pm;
    QImage image(":/imgs/files/imgs/scanWait.jpeg");
    pm = QPixmap::fromImage(image);
    ui->label_3->setPixmap(pm);

    this->getScanPreviewProcess = new QProcess(this);
    connect (this->getScanPreviewProcess,SIGNAL(finished(int)),this,SLOT(scanPreviewReady(int)));

    QString program = "scanimage";
    QStringList param;
    param << "--format=tiff"
             << "--resolution"
                << "100"
                   << "--mode"
                      << "Lineart"
                         << "--quality-cal=no"
                            << "-l"
                               << "10"
                                  << "-t"
                                     << "0"
                                        << "-x"
                                           << "140"
                                              << "-y"
                                                 << "215"
                                                 << QDir::tempPath() + "/previeTmp.tiff";

    this->getScanPreviewProcess->start(program, param);
}

void KBookocr::scanPreviewReady(int)
{
    QPixmap pm;
    QImage image(QDir::tempPath() + "/previeTmp.tiff");
    pm = QPixmap::fromImage(image);
    ui->label_3->setPixmap(pm);
}

void KBookocr::on_pushButton_2_clicked()
{
    this->saveToFile = true;
    this->setPathToSave();
    this->start();
}

void KBookocr::on_pushButton_8_clicked()
{
    this->saveToFile = false;
    this->start();
}

void KBookocr::on_spinBox_2_editingFinished()
{


    if (ui->spinBox_2->value() < ui->spinBox->value())
        ui->spinBox_2->setValue(ui->spinBox->value());

}

void KBookocr::on_verticalScrollBar_valueChanged(int value)
{
    if (this->isFileMode() && this->open && this->pdf)
    {
        if (value != this->currentFirstView && value < this->doc->numPages())
        {
            this->currentFirstView = value;
            //this->refreshViewPanel();
        }
    }
}
/*
void KBookocr::refreshViewPanel()
{
    QSize size(70,110);
    if (this->currentFirstView + 4 < doc->numPages())
    {

        //ui->label_pages_1->setText(QString::number(this->currentFirstView));
        //ui->label_pages_2->setText(QString::number(this->currentFirstView+1));
        //ui->label_pages_3->setText(QString::number(this->currentFirstView+2));
        //ui->label_pages_4->setText(QString::number(this->currentFirstView+3));

        QImage image = doc->page(this->currentFirstView)->renderToImage(100,100);
        image = image.scaled(size);
        QPixmap pm;
        pm = QPixmap::fromImage(image);
        QIcon ico(pm);
        //ui->label_view1->setIcon(ico);
        //ui->label_view1->setIconSize(size);
        /*if (this->pageChecked.at(this->currentFirstView-1))
            ui->label_view1->setChecked(true);
        else
            ui->label_view1->setChecked(false);*/
/*
        image = doc->page(this->currentFirstView+1)->renderToImage(100,100);
        image = image.scaled(size);
        pm = QPixmap::fromImage(image);
        //ico.pixmap()
        QIcon ico2(pm);
        //ui->label_view2->setIcon(ico2);
        //ui->label_view2->setIconSize(size);
        /*if (this->pageChecked.at(this->currentFirstView))
            ui->label_view2->setChecked(true);
        else
            ui->label_view2->setChecked(false);*/
/*
        image = doc->page(this->currentFirstView+2)->renderToImage(100,100);
        image = image.scaled(size);
        pm = QPixmap::fromImage(image);
        QIcon ico3(pm);
        //ui->label_view3->setIcon(ico3);
        //ui->label_view3->setIconSize(size);
        /*if (this->pageChecked.at(this->currentFirstView+1))
            ui->label_view3->setChecked(true);
        else
            ui->label_view3->setChecked(false);*/
/*
        image = doc->page(this->currentFirstView+3)->renderToImage(100,100);
        image = image.scaled(size);
        pm = QPixmap::fromImage(image);
        QIcon ico4(pm);
        //ui->label_view4->setIcon(ico4);
        //ui->label_view4->setIconSize(size);
        /*if (this->pageChecked.at(this->currentFirstView+2))
            ui->label_view4->setChecked(true);
        else
            ui->label_view4->setChecked(false);*/
/*
    }
    else
    {
        QImage image = doc->page(this->doc->numPages()-4)->renderToImage(100,100);
        image = image.scaled(size);
        QPixmap pm;
        pm = QPixmap::fromImage(image);
        QIcon ico(pm);
        //ui->label_view1->setIcon(ico);
        //ui->label_view1->setIconSize(size);
        /*if (this->pageChecked.at(this->currentFirstView-1))
            ui->label_view1->setChecked(true);
        else
            ui->label_view1->setChecked(false);*/
/*
        image = doc->page(this->doc->numPages()-3)->renderToImage(100,100);
        image = image.scaled(size);
        pm = QPixmap::fromImage(image);
        QIcon ico2(pm);
        //ui->label_view2->setIcon(ico2);
        //ui->label_view2->setIconSize(size);
        /*if (this->pageChecked.at(this->currentFirstView))
            ui->label_view2->setChecked(true);
        else
            ui->label_view2->setChecked(false);*/
/*
        image = doc->page(this->doc->numPages()-2)->renderToImage(100,100);
        image = image.scaled(size);
        pm = QPixmap::fromImage(image);
        QIcon ico3(pm);
        //ui->label_view3->setIcon(ico3);
        //ui->label_view3->setIconSize(size);
        /*if (this->pageChecked.at(this->currentFirstView+1))
            ui->label_view3->setChecked(true);
        else
            ui->label_view3->setChecked(false);*/
/*
        image = doc->page(this->doc->numPages()-1)->renderToImage(100,100);
        image = image.scaled(size);
        pm = QPixmap::fromImage(image);
        QIcon ico4(pm);
        //ui->label_view4->setIcon(ico4);
        //ui->label_view4->setIconSize(size);
       /* if (this->pageChecked.at(this->currentFirstView+2))
            ui->label_view4->setChecked(true);
        else
            ui->label_view4->setChecked(false);*/

/*
    }
}
*/
void KBookocr::on_label_view1_linkActivated(QString link)
{
    int i=0;
    i++;
}

void KBookocr::on_label_view1_clicked(bool checked)
{
    //this->pageChecked[this->currentFirstView-1] = checked;
    ui->radioButton_3->setChecked(true);
    ui->spinBox_3->setValue(this->currentFirstView);
    //this->on_spinBox_3_valueChanged(this->currentFirstView);
}

void KBookocr::on_label_view2_clicked(bool checked)
{
    //this->pageChecked[this->currentFirstView] = checked;
    ui->radioButton_3->setChecked(true);
    ui->spinBox_3->setValue(this->currentFirstView+1);
    //this->on_spinBox_3_valueChanged(this->currentFirstView+1);
}

void KBookocr::on_label_view3_clicked(bool checked)
{
    //this->pageChecked[this->currentFirstView+1] = checked;
    ui->radioButton_3->setChecked(true);
    ui->spinBox_3->setValue(this->currentFirstView+2);
    //this->on_spinBox_3_valueChanged(this->currentFirstView+2);
}

void KBookocr::on_label_view4_clicked(bool checked)
{
    //this->pageChecked[this->currentFirstView+2] = checked;
    ui->radioButton_3->setChecked(true);
    ui->spinBox_3->setValue(this->currentFirstView+3);
    //this->on_spinBox_3_valueChanged(this->currentFirstView+3);
}
/*
void KBookocr::setViewPanelVisible(bool vis)
{
    //ui->verticalScrollBar->setVisible(vis);
    //ui->label_view1->setVisible(vis);
    //ui->label_view2->setVisible(vis);
    //ui->label_view3->setVisible(vis);
    //ui->label_view4->setVisible(vis);

    //ui->label_pages_1->setVisible(vis);
    //ui->label_pages_2->setVisible(vis);
    //ui->label_pages_3->setVisible(vis);
    //ui->label_pages_4->setVisible(vis);

    ui->radioButton_3->setVisible(vis);
    ui->label_6->setVisible(vis);
    ui->label_9->setVisible(vis);

    if (ui->radioButton_3->isChecked() && !vis)
        ui->radioButton->setChecked(true);

    ui->pushButton->setVisible(vis);
}
*/
void KBookocr::on_pushButton_clicked()
{
    //for (int i=0;i<ui->verticalLayout_10->`;i++)
         //ui->verticalLayout_10->children().at(i)->
      //  ui->verticalLayout_10->removeWidget(ui->verticalLayout_10->removeItem());
    //ui->verticalLayout_10->count()

    /*QLayoutItem *child;
    while ((child = ui->verticalLayout_10->takeAt(1)) != 0)
    {
    delete child->widget();
    delete child;

}*/
    for (int i=0;i<this->viewWidgets.count();i++)
        delete this->viewWidgets[i];
    this->viewWidgets.clear();
    this->pageCounChanged(this->getPageCount());
    //ui->verticalLayout_10->addWidget(new QSpacerItem());
    //ui->verticalLayout_10->addSpacing();

}

void KBookocr::deleteViewId(int id)
{
    for (int i=0;i<this->viewWidgets.count();i++)
        if (this->viewWidgets.at(i)->get_Id() == id)
        {
            delete this->viewWidgets[i];
            this->viewWidgets.removeAt(i);
            i--;
        }
    this->pageCounChanged(this->getPageCount());
}

void KBookocr::newImgAdd(QImage img, int n)
{

    ViewWidget* view = new ViewWidget(this->getNewId(),this,img,n);
    connect (view, SIGNAL(deleted(int)),this,SLOT(deleteViewId(int)));
    connect (view,SIGNAL(selected(int)),this,SLOT(selectedViewId(int)));
    ui->verticalLayout_10->addWidget(view);
    this->viewWidgets << view;
    this->pageCounChanged(this->getPageCount());
    if (ui->spinBox_3->value() == 0)
        ui->spinBox_3->setValue(1);
}

void KBookocr::newViewAdd(ViewWidget *view)
{
    //QLayout* la = ui->verticalLayout_10;
    ui->verticalLayout_10->addWidget(view);

    //ViewWidget* test = new ViewWidget(0,this,this->openPath("/home/b0noi/tmp/1.png"),1);
    //ui->verticalLayout_10->addWidget(test);
    //ui->verticalLayout_10->
    //view->show();
}

void KBookocr::on_label_view1_clicked()
{

}

void KBookocr::on_pushButton_3_clicked()
{
    //this->load();
    this->adder->terminate();
    delete this->adder;
    this->adder = 0;
    ui->groupBox->setVisible(false);
    this->pageCounChanged(this->getPageCount());
    //ui->pushButton_3->setVisible(false);
}
