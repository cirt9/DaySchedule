#-------------------------------------------------
#
# Project created by QtCreator 2017-04-29T13:12:03
#
#-------------------------------------------------
include(../defaults.pri)

QT       += core gui sql multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DaySchedule
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainmenu.cpp \
    dayboard.cpp \
    activity.cpp \
    layoutdeleter.cpp \
    activitystate.cpp \
    timerangesystem.cpp \
    monthboard.cpp \
    yearboard.cpp \
    listofyearsboard.cpp \
    boardtemplate.cpp \
    calendarcard.cpp \
    bar.cpp \
    databasemanager.cpp \
    timecounter.cpp \
    dateselectingwidget.cpp \
    taskmanager.cpp \
    optionwidget.cpp \
    notification.cpp \
    statswidget.cpp \
    statistics.cpp \
    saveswidget.cpp \
    filenamewidget.cpp \
    mainwindowtemplate.cpp

HEADERS  += mainwindow.h \
    mainmenu.h \
    dayboard.h \
    activity.h \
    layoutdeleter.h \
    activitystate.h \
    timerangesystem.h \
    monthboard.h \
    yearboard.h \
    listofyearsboard.h \
    boardtemplate.h \
    calendarcard.h \
    bar.h \
    databasemanager.h \
    timecounter.h \
    dateselectingwidget.h \
    taskmanager.h \
    optionwidget.h \
    notification.h \
    statswidget.h \
    statistics.h \
    saveswidget.h \
    filenamewidget.h \
    mainwindowtemplate.h

FORMS    += \
    mainwindow.ui

RESOURCES += \
    resources.qrc

DISTFILES += \
    style.css
