#-------------------------------------------------
#
# Project created by QtCreator 2014-10-21T08:29:35
#
#-------------------------------------------------

QT       += core gui
QT       +=sql xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = manager
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp

HEADERS  += widget.h \
    connection.h

FORMS    += widget.ui
