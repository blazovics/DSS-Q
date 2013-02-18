#-------------------------------------------------
#
# Project created by QtCreator 2013-02-12T09:11:45
#
#-------------------------------------------------

QT       += core gui

TARGET = DSS-Q
TEMPLATE = app


SOURCES += main.cpp \
    entity.cpp \
    field.cpp \
    place.cpp \
    logger.cpp \
    scene.cpp \
    QT_UI/screenwidget.cpp \
    renderobject.cpp \
    swarmentity.cpp \
    grgentity.cpp \
    QT_UI/toolbarwidget.cpp \
    targetentity.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

HEADERS += \
    entity.h \
    field.h \
    place.h \
    common.h \
    logger.h \
    scene.h \
    QT_UI/screenwidget.h \
    maths.h \
    renderobject.h \
    swarmentity.h \
    grgentity.h \
    QT_UI/toolbarwidget.h \
    targetentity.h
