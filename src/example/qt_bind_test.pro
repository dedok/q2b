QT -= gui
TEMPLATE = app
TARGET = 
DEPENDPATH += .
INCLUDEPATH += ./q2b
LIBS += 

CXXFLAGS += -ggdb -Wall -pedantic -O2 -DDEBUG 

SOURCES += qt_bind_test.cpp
DESTDIR = ./bin
