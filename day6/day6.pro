QT += core
QT -= gui

TARGET = day6
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

DISTFILES += \
    input.txt

win32-msvc* {
  QMAKE_LFLAGS += -STACK:10000000
}
