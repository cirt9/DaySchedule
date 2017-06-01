#-------------------------------------------------
#
# Project created by QtCreator 2017-05-30T21:10:59
#
#-------------------------------------------------
include(../defaults.pri)

QT       += testlib

QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += testtimerangesystem.cpp \
    main.cpp \
    ../DaySchedule/timerangesystem.cpp

HEADERS += \
    testtimerangesystem.h \
    ../DaySchedule/timerangesystem.h
