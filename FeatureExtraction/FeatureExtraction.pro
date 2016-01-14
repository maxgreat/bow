#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T14:07:00
#
#-------------------------------------------------

TARGET = FeatureExtraction
CONFIG   += console
CONFIG   -= app_bundle

SOURCES += main.cpp \
    image2Features.cpp

INCLUDEPATH += /usr/include/

QMAKE_LIBS += `pkg-config opencv --libs`
QMAKE_LIBDIR += /usr/lib/x86_64-linux-gnu/

HEADERS += \
    image2Features.h \
    DataStorage.h \
    drawing.h
