#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T14:07:00
#
#-------------------------------------------------

QT += core gui
#QT += widgets

TARGET = FeatureExtraction
#TEMPLATE = app
CONFIG   += console
CONFIG   -= app_bundle

SOURCES += main.cpp \
    DataStorage.cpp \
    descriptor.cpp \
    #mainwindow.cpp \
    imagedescriptors.cpp \
    imagelibrary.cpp

INCLUDEPATH += /usr/include/

QMAKE_CC = gcc-5
QMAKE_CXX = g++-5

QMAKE_LIBS += `pkg-config opencv --libs`
QMAKE_LIBDIR += /usr/lib/x86_64-linux-gnu/
QMAKE_LIBDIR += -L/usr/local/lib

QMAKE_CXXFLAGS += -std=c++11 -Wall -Werror

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -Wunused-result -Wunused-parameter
QMAKE_LFLAGS_RELEASE += -Wunused-result -Wunused-parameter -mno-sse4a
QMAKE_LFLAGS_RELEASE -= -O1

DEFINES += USE_OPENCV

HEADERS += \
    DataStorage.h \
    drawing.h \
    descriptor.h \
    #mainwindow.h \
    imagedescriptors.h \
    imagelibrary.h
