//#include <QtGui/QApplication>
//#include <kapplication.h>
#include <QObject>
#include "kbookocr.h"

#include <KDE/KAboutData>
#include <KDE/KCmdLineArgs>
#include <KDE/KApplication>
#include <KDE/KConfigGroup>
#include <KDE/KConfigBase>
//#include "KBookOCR.h"

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);


    KAboutData aboutData("KBookOCR", "kbookocr", ki18n("KBookOCR"), "2.1",
                         ki18n("OCR system with multi-language support and simple GUI."),
                         KAboutData::License_GPL,
                         ki18n("(C) 2011 b0noI, Mr.Protos"));

    aboutData.addAuthor(ki18n("b0noI"),
                        ki18n("developer"),
                        "my2you@ya.ru", "http://b0noI.ya.ru");

    //aboutData.addAuthor()

    aboutData.addAuthor(ki18n("Mr.Protos"),
                        ki18n("developer"),
                        "mr.protos@ya.ru", 0);

    /*aboutData.addAuthor(ki18n("Arseniy Lartsev"),
                        ki18n("contributor"),
                        0, 0);

    aboutData.addCredit(ki18n("Gilles Caulier"),
                        ki18n("Importing libksane to extragear"),
                              0, 0);

    aboutData.addCredit(ki18n("Anne-Marie Mahfouf"),
                        ki18n("Writing the user manual"),
                              0, 0);

    aboutData.addCredit(ki18n("Laurent Montel"),
                        ki18n("Importing libksane to extragear"),
                              0, 0);

    aboutData.addCredit(ki18n("Chusslove Illich"),
                        ki18n("Help with translations"),
                              0, 0);

    aboutData.addCredit(ki18n("Albert Astals Cid"),
                        ki18n("Help with translations"),
                              0, 0);*/

    aboutData.setProgramIconName("kbookocr");

    KCmdLineArgs::init(argc, argv, &aboutData);


    KApplication a;
    //a.enableSessionManagement();
    KBookocr *kbook;
    kbook = new KBookocr;

    //KConfigBase conf;
    kbook->setAutoSaveSettings("KBookOCR");

    kbook->show();
    QObject::connect (&a,SIGNAL(lastWindowClosed()),&a,SLOT(quit()));
    /*KBookocr kbook;
    kbook.show();*/

    return a.exec();
}
