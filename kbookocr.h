#ifndef KBOOKOCR_H
#define KBOOKOCR_H

#include <QMainWindow>
#include <QProcess>
#include <QFileInfo>

#include <libksane/ksane.h>
#include <kiconloader.h>
#include <kmainwindow.h>
#include <kdialog.h>

#include "enum.h"
#include "convertingtoimgwite.h"
#include "viewwidget.h"
#include "viewadder.h"
#include "ocrthread.h"
#include "savethread.h"
#include "jpgdirdocument.h"
//#include "scanerdialog.h"

// #include <poppler/PDFDoc.h>
//#include <poppler/PDFDoc.h>
#include <poppler/qt4/poppler-qt4.h>

#include "document.h"

namespace Ui {
    class KBookocr;
}

using namespace KSaneIface;

//class KBookocr : public QMainWindow
class KBookocr : public KMainWindow
{
    Q_OBJECT

public:
    explicit KBookocr(QWidget *parent = 0);
    ~KBookocr();

    bool setPathToSave();
    bool setPathToSave(const QString&);
    bool clearPathToSave();
    QString getPathToSave();
    QString getVersion();
    //bool setOutFormat(OUT_FORMAT);
    //OUT_FORMAT getOutFormat();
    //static QString fromFormatToStr(OUT_FORMAT format);

    // new
    //bool openDoc(QString);
    // end new

    int getPageCount();
public slots:
    void addFinished();
    void doneProgress(int,int);
    void newViewAdd(ViewWidget*);
    void newImgAdd(QImage,int,Document*);
    void deleteViewId(int);
    void selectedViewId(int);
    void pageCounChanged(int);
    //void scanComplete(const QImage&,int);
    void OCRComplete(QString);
    void OCRProcess(int);
    void scanerReady(QByteArray&,int,int,int,int);
    void saveDone(QString);
    void loadFilesReady();
    void djvuReady();
    void showAboutKDE();
    void showDonate();
    //void scanerListReady(const QList< KSaneWidget::DeviceInfo > & );


private:

    // new
    //Okular::Document currentDoc;
    //KParts::Part::
    //Okular::KDocumenView
    // end new

    //KScanDialog* scanDialog;

    //bool toWriter;

    bool saveImages();
    bool saveAllImages();
    bool saveImages(int,int);
    bool saveImg(int);
    bool saveManualImages();
    QString getWorkDir();
    bool clearWorkDir();
    bool removeDir(const QString&);
    bool startOpening(QString);
    bool startOpenDJVU(QString);

    Ui::KBookocr *ui;

    KIconLoader* iconLoader;

    //convertingToImgWite* convToImg;

    //bool pdf;
    //bool open;
    bool saveToFile;

    //int currentFirstView;

    //OUT_FORMAT outFormat;

    int currentPage;
    //Poppler::Document *doc;
    QSize size;
    QSize baseSize;
    void setSize();
    //QProcess* bookOCRProcess;
    QProcess* openOfficeProcess;
    //QProcess* previewDJVUProcess;
    //QProcess* scanProcess;
    QProcess* libreOfficeProcess;
    //QProcess* getScanPreviewProcess;
    QProcess* convertDjvu2Pdf;
    QProcess* loader;

    //void setVisibleScanOrFile(bool); // true - file, false - scaner
    bool isFileMode();
    //void start();
    //void getScanPreview();
    //bool startConvertFromDjvu(QString,QString,QString);
    //void openFiles();
    //void scanAndOCR();
    //void OCRFromFile();
    //void load();
    //void save();
    //QString formImgFromPdf();
    //QString scanToFile();

    //void refreshViewPanel();
    //void setViewPanelVisible(bool);

    QString pathToSave;
    //QString djvuPath;

    //QList<bool> pageChecked;
    //QList<int> makeListOfMarkedPages();

    QList<ViewWidget*> viewWidgets;
    viewAdder* adder;
    OCRThread* OCR;
    SaveThread* saver;
    //ScanerDialog scanDialog;
    KSaneIface::KSaneWidget scanerWidget;
    Document* openPath(const QString&);
    bool isImg(QFileInfo);
    bool isPdf(QFileInfo);
    bool isDjvu(QFileInfo);
    //bool addView(Document*,int);
    int idCount;
    int getNewId();
    void makeToolbox();


private slots:

    void showAbout();
    void on_horizontalSlider_sliderReleased();
    void on_pushButton_4_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_spinBox_2_valueChanged(int );
    void on_spinBox_valueChanged(int );
    void openOfficeOpen(int);
    //void previewDJVUChanged(int);
    //void scanComplete(int);
    //void scanPreviewReady(int);
    //void djvu2pdfReady(int);

    void on_radioButton_7_clicked();
    void on_radioButton_6_clicked();
    void on_radioButton_5_clicked();
    void on_spinBox_3_valueChanged(int );
    //void on_pushButton_3_clicked();

    //void on_pushButton_clicked();
    void addFileToProject();
    void scanImg();
    void startOCRToFile();
    void startOCRToEditor();
    void on_spinBox_2_editingFinished();
    void on_verticalScrollBar_valueChanged(int value);
    void on_label_view1_linkActivated(QString link);
    void on_label_view1_clicked(bool checked);
    void on_label_view2_clicked(bool checked);
    void on_label_view3_clicked(bool checked);
    void on_label_view4_clicked(bool checked);
    void on_pushButton_clicked();
    void on_label_view1_clicked();
    void on_pushButton_3_clicked();


    void on_radioButton_8_clicked();
    void on_horizontalSlider_actionTriggered(int action);
    void on_pushButton_9_clicked();
    void saveProject();
    void on_pushButton_12_clicked();
    void openProject();
};

#endif // KBOOKOCR_H
