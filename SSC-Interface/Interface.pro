#-------------------------------------------------
#
# Project created by QtCreator 2014-07-16T01:29:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Interface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    progressdialog.cpp \
    csvwriter.cpp

HEADERS  += mainwindow.h \
    progressdialog.h \
    csvwriter.h

FORMS    += mainwindow.ui \
    progressdialog.ui

CONFIG += serialport

CONFIG += static

QT  += serialport
