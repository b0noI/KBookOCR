#include <QtGui/QApplication>
#include "kbookocr.h"
//#include "KBookOCR.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    KBookocr kbook;
    //KBookOCR kbook;


    kbook.show();

    return a.exec();
}
