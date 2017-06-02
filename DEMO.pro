#-------------------------------------------------
#
# Project created by QtCreator 2017-05-08T08:37:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DEMO
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH += $$PWD
CONFIG += C++11
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += -L$$PWD/ -lAPI_RS422_485_232
LIBS += -L$$PWD/ -lH1040_API_RS422
LIBS += -L$$PWD/ -lvisa32
LIBS += -L$$PWD/ -livi

SOURCES += main.cpp\
        MainWindow.cpp \
    QtResource.cpp \
    ASL422.cpp

HEADERS  += MainWindow.h \
    QtResource.h \
    ASL422.h \
    H1040_API_RS422.h

FORMS    += MainWindow.ui \
    ASL232.ui
