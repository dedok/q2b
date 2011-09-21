QT -= gui
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += ../include
LIBS += 

CXXFLAGS += -ggdb -Wall -pedantic -O2 -DDEBUG 

SOURCES += qt_bind_test.cpp
DESTDIR = ../../bin/examples
