#-------------------------------------------------
#
# Project created by QtCreator 2015-10-08T20:57:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Inform_Lab2
TEMPLATE = app


SOURCES += main.cpp\
        mw.cpp \
    fnc.cpp \
    des.cpp

HEADERS  += mw.h \
    fnc.h \
    des.h

FORMS    += mw.ui

QMAKE_CXXFLAGS += -std=gnu++0x
