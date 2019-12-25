#-------------------------------------------------
#
# Project created by QtCreator 2014-11-25T17:02:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Taquin
TEMPLATE = app
QMAKE_CXXFLAGS +=-std=c++11

SOURCES += main.cpp\
        MainWindow.cpp \
    Tableau.cpp \
    Taquin.cpp

HEADERS  += MainWindow.h \
    Taquin.h \
    Tableau.h

FORMS    += MainWindow.ui
