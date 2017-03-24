#-------------------------------------------------
#
# Project created by QtCreator 2017-01-15T13:39:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myUml
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    umlmainwidget.cpp \
    components/scenes/domainscene.cpp \
    components/primitives/domainitem.cpp \
    components/primitives/domainarrow.cpp \
    umlapi.cpp \
#    components/primitives/usecaseactor.cpp \
    components/primitives/abstractumlitem.cpp \
    components/primitives/umllineitem.cpp

HEADERS  += mainwindow.h \
    umlmainwidget.h \
    components/scenes/domainscene.h \
    components/primitives/domainitem.h \
    components/primitives/domainarrow.h \
    umlapi.h \
#    components/primitives/usecaseactor.h \
    components/primitives/abstractumlitem.h \
    components/primitives/umllineitem.h

FORMS += \
    umlmainform.ui
