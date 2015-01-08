#-------------------------------------------------
#
# Project created by QtCreator 2015-01-05T15:50:53
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = XVADataVisualizer
TEMPLATE = app


SOURCES += main.cpp\
        mainview.cpp \
    qcustomplot.cpp \
    dataplot.cpp

HEADERS  += mainview.h \
    qcustomplot.h \
    dataplot.h

FORMS    += mainview.ui \
    dataplot.ui
