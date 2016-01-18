#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T14:07:00
#
#-------------------------------------------------

QT += core gui
QT += widgets

TARGET = FeatureExtraction
TEMPLATE = app
#CONFIG   += console
#CONFIG   -= app_bundle

SOURCES += main.cpp \
    image2Features.cpp \
    DataStorage.cpp \
    descriptor.cpp \
    mainwindow.cpp \
    imagedescriptors.cpp

INCLUDEPATH += /usr/include/

QMAKE_LIBS += `pkg-config opencv --libs`
QMAKE_LIBDIR += /usr/lib/x86_64-linux-gnu/

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3 -Wunused-result
QMAKE_LFLAGS_RELEASE -= -O1

DEFINES += USE_OPENCV

HEADERS += \
    DataStorage.h \
    drawing.h \
    descriptor.h \
    image2Features.h \
    mainwindow.h \
    imagedescriptors.h
