#Configuracion para Libreria
TEMPLATE = lib
QT += core sql xml
CONFIG += dll
TARGETDIR = lib

#Comprueba si se compila como aplicacion
TEST=YES
!isEmpty($$TEST)
{
	#Configuracion para Aplicacion de Test
	TEMPLATE = app
	CONFIG += console
	CONFIG -= app_bundle
	HEADERS += test/utils/utilsdefinitions.h \
	    test/datatest.h \
	    test/dbtest.h
	SOURCES += test/main.cpp \
	    test/datatest.cpp \
	    test/dbtest.cpp
	TARGETDIR = bin
}

#Define la Plataforma de compilacion
win32 { platform = win32 }
unix { platform = unix }

#Core Data Base
TARGET = coredb
INCLUDEPATH += cfg include src

#Indica la compilacion con Librerias especificas
#debug:DEFINES +=

release:DESTDIR = $$TARGETDIR
release:OBJECTS_DIR = build/release/$${platform}-obj
release:MOC_DIR = build/release/$${platform}-moc
release:RCC_DIR = build/release/$${platform}-rcc
release:UI_DIR = build/release/$${platform}-ui

debug:DESTDIR = $$TARGETDIR
debug:OBJECTS_DIR = build/debug/$${platform}-obj
debug:MOC_DIR = build/debug/$${platform}-moc
debug:RCC_DIR = build/debug/$${platform}-rcc
debug:UI_DIR = build/debug/$${platform}-ui

#Seccion de Includes
include(src/db/db.pri)
include(src/utils/utils.pri)
include(src/xml/xml.pri)

#Seccion de Includes de la aplicacion
#HEADERS += \
#    include/coredb.h

#Seccion de Ficheros de Configuracion
#OTHER_FILES += cfg/db.cnf

