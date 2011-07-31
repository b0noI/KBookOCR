#-------------------------------------------------
#
# Project created by QtCreator 2010-11-12T17:13:59
#
#-------------------------------------------------

QT       += core gui

TARGET = KBookocr
TEMPLATE = app


SOURCES += main.cpp\
        kbookocr.cpp \
    document.cpp \
    view.cpp \
    viewwidget.cpp \
    djvudocument.cpp \
    pdfdocument.cpp \
    imgclass.cpp \
    viewadder.cpp \
    ocrthread.cpp \
    savethread.cpp \
    jpgdirdocument.cpp \
    rangedialog.cpp \
    ocrkernel.cpp \
    cuniiformocr.cpp \
    kerneldialog.cpp \
    settings.cpp \
    tesseractocr.cpp

HEADERS  += kbookocr.h \
    enum.h \
    document.h \
    view.h \
    viewwidget.h \
    djvudocument.h \
    pdfdocument.h \
    imgclass.h \
    viewadder.h \
    ocrthread.h \
    savethread.h \
    jpgdirdocument.h \
    rangedialog.h \
    ocrkernel.h \
    cuniiformocr.h \
    kerneldialog.h \
    settings.h \
    tesseractocr.h

FORMS    += kbookocr.ui \
    viewwidget.ui \
    rangedialog.ui \
    kerneldialog.ui

INCLUDEPATH  += /usr/include/poppler/qt4
LIBS         += -lpoppler-qt4 \
		-lksane

RESOURCES += \
    ico.qrc

OTHER_FILES += \
    kbookocr.ui (Case Conflict 1) \
    RoadMap.txt \
    ../../../Progs/deb/kbookocr/DEBIAN/control \
    KBookOCR_UI.qml \
    README.txt
