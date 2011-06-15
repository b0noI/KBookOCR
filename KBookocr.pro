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
    convertingtoimgwite.cpp \
    document.cpp \
    view.cpp \
    viewwidget.cpp \
    djvudocument.cpp \
    pdfdocument.cpp \
    imgclass.cpp \
    viewadder.cpp

HEADERS  += kbookocr.h \
    enum.h \
    convertingtoimgwite.h \
    document.h \
    view.h \
    viewwidget.h \
    djvudocument.h \
    pdfdocument.h \
    imgclass.h \
    viewadder.h

FORMS    += kbookocr.ui \
    convertingtoimgwite.ui \
    viewwidget.ui

INCLUDEPATH  += /usr/include/poppler/qt4
LIBS         += -L/usr/lib -lpoppler-qt4

RESOURCES += \
    ico.qrc

OTHER_FILES += \
    kbookocr.ui (Case Conflict 1) \
    RoadMap.txt \
    ../../../Progs/deb/kbookocr/DEBIAN/control
