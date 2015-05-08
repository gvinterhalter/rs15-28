#-------------------------------------------------
#
# Project created by QtCreator 2012-04-16T14:33:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qnodeseditor
TEMPLATE = app


SOURCES += main.cpp\
        qnemainwindow.cpp \
    nodeAttr.cpp \
    nodeBlock.cpp \
    attrConnection.cpp \
    nodeEditor.cpp

HEADERS  += qnemainwindow.h \
    nodeBlock.h \
    nodeAttr.h \
    attrConnection.h \
    nodeEditor.h \
    attr.h

