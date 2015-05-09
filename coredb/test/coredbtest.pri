TEMPLATE = app
QT += core sql xml

CONFIG += console
CONFIG -= app_bundle
DEFINES += CORETMCS_LIB

#Define la Plataforma de compilacion
win32 { platform = win32 }
unix { platform = unix }

TARGET = coretmcstest

release:DESTDIR = release/$${platform}-bin
release:OBJECTS_DIR = release/$${platform}-obj
release:MOC_DIR = release/$${platform}-moc
release:RCC_DIR = release/$${platform}-rcc
release:UI_DIR = release/$${platform}-ui

debug:DESTDIR = debug/$${platform}-bin
debug:OBJECTS_DIR = debug/$${platform}-obj
debug:MOC_DIR = debug/$${platform}-moc
debug:RCC_DIR = debug/$${platform}-rcc
debug:UI_DIR = debug/$${platform}-ui

#Seccion de Includes
#include(src/folder/file.pri)

#Seccion de Fuentes de la aplicacion
HEADERS += \
    datatest.h
SOURCES += main.cpp \
    datatest.cpp

#Seccion de Recursos de la aplicacion
#RESOURCES += resources/folder/file.qrc

#Usos de Librerias en desarrollo
INCLUDEPATH += ../include
INCLUDEPATH += ../src

LIBS += -L../debug/unix-bin -lTMCS_CODB_lib_unix_coredb
