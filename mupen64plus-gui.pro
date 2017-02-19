#-------------------------------------------------
#
# Project created by QtCreator 2017-02-16T19:17:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mupen64plus-gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    osal/osal_dynamiclib_unix.c \
    osal/osal_files_unix.c \
    vidext.cpp \
    settingsdialog.cpp \
    interface/common.cpp \
    interface/core_interface.cpp \
    interface/plugin.cpp

HEADERS  += mainwindow.h \
    vidext.h \
    interface/common.h \
    interface/core_interface.h \
    interface/plugin.h \
    settingsdialog.h \
    osal/osal_dynamiclib.h

FORMS    += mainwindow.ui

QMAKE_INCDIR += api osal interface

QMAKE_LFLAGS += -ldl
