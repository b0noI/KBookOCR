#ifndef KBOOKOCR_H
#define KBOOKOCR_H

#include <QMainWindow>
#include <QProcess>
#include <QFileInfo>
#include <QCheckBox>
#include <QDropEvent>
#include <QDragEnterEvent>
#include <QMutex>

#include <libksane/ksane.h>
#include <KDE/KIconLoader>
#include <KDE/KMainWindow>
#include <KDE/KComboBox>
#include <KDE/KAction>
//#include <kdialog.h>

#include "enum.h"
#include "convertingtoimgwite.h"
#include "viewwidget.h"
#include "viewadder.h"
#include "ocrthread.h"
#include "savethread.h"
#include "jpgdirdocument.h"
#include "rangedialog.h"
#include "ocrkernel.h"
#include "kerneldialog.h"
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
    static const QStringList mimeTypes;

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
    void rangeReady(int, int);
    //void scanerListReady(const QList< KSaneWidget::DeviceInfo > & );


private:

    // new
    //Okular::Document currentDoc;
    //KParts::Part::
    //Okular::KDocumenView
    // end new

    //KScanDialog* scanDialog;

    //bool toWriter;
    void dropEvent(QDropEvent *);
    void dragEnterEvent(QDragEnterEvent*);

    bool saveImages();
    //bool saveAllImages();
    //bool saveImages(int,int);
    bool saveImg(int);
    bool saveManualImages();
    QString getWorkDir();
    bool clearWorkDir();
    bool removeDir(const QString&);
    bool startOpening(QString);
    bool startOpenDJVU(QString);
    bool showRDialog();

    OCRKernel* getCurrentOCRKernel();

    Ui::KBookocr *ui;
    KComboBox *langComboBox;
    //QCheckBox *layoutCheckBox;
    RangeDialog rDialog;
    KernelDialog kernelDialog;

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
    void iconsSet();
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
    void load();
    void save();
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

    // ACTIONS
    KAction* addDoc;
    KAction* scanDoc ;
    KAction* toFile;
    KAction* toEditor;
    KAction* showSettings;

    KToolBar *kToolBar;
    KToolBar *kOCRToolBar ;
    KToolBar *settingsToolBar;

    void makeActions();
    void makeToolbox();
    void makeFirstToolbox();
    void makeSecondToolbox();
    void makeSettingsToolbox();
    void makeMenu();
    // END ACTIONS

    QMutex mutex;


private slots:

    void showAbout();
    void showKernelDialog();
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
    bool addFileToProject(const QString&);
    void scanImg();
    void startOCRToFile();
    void startOCRToEditor();
    bool startOCR();
    void newKernelOCR();
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
    void on_pushButton_2_clicked();
    void on_comboBox_currentIndexChanged(const QString &arg1);
    void on_pageComboBox_currentIndexChanged(int index);
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_toggled(bool checked);
    void on_radioButton_2_toggled(bool checked);
    void on_radioButton_3_toggled(bool checked);
    void on_pageComboBox_currentIndexChanged(const QString &arg1);
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
};

#endif // KBOOKOCR_H
