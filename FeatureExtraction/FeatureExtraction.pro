#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T14:07:00
#
#-------------------------------------------------

TARGET = FeatureExtraction
CONFIG   += console
CONFIG   -= app_bundle

SOURCES += main.cpp \
    image2Features.cpp \
    DataStorage.cpp

INCLUDEPATH += /usr/include/

QMAKE_LIBS += `pkg-config opencv --libs`
QMAKE_LIBDIR += /usr/lib/x86_64-linux-gnu/

QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE += -O3
QMAKE_LFLAGS_RELEASE -= -O1

HEADERS += \
    image2Features.h \
    DataStorage.h \
    drawing.h
