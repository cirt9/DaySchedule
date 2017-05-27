#-------------------------------------------------
#
# Project created by QtCreator 2017-04-29T13:12:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DaySchedule
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainmenu.cpp \
    dayboard.cpp \
    activity.cpp \
    layoutdeleter.cpp \
    activitystate.cpp

HEADERS  += mainwindow.h \
    mainmenu.h \
    dayboard.h \
    activity.h \
    layoutdeleter.h \
    activitystate.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    style.css
