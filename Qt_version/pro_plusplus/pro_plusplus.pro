#-------------------------------------------------
#
# Project created by QtCreator 2021-04-06T09:23:09
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pro_plusplus
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


SOURCES += \
        main.cpp \
        main_window.cpp \
    sqlite_utils.cpp \
    pro.cpp \
    pro_dayset_dlg.cpp \
    pro_dayset_serv.cpp \
    pro_sel_dlg.cpp \
    pro_sel_serv.cpp \
    statistics_dlg.cpp \
    statistics_serv.cpp

HEADERS += \
        main_window.h \
    sqlite_utils.h \
    pro.h \
    pro_dayset_dlg.h \
    pro_dayset_serv.h \
    pro_sel_dlg.h \
    pro_sel_serv.h \
    statistics_dlg.h \
    statistics_serv.h

FORMS += \
        main_window.ui \
    pro_dayset_dlg.ui \
    pro_sel_dlg.ui \
    statistics_dlg.ui

RESOURCES += \
    pro++.qrc
