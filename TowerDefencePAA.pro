#-------------------------------------------------
#
# Project created by QtCreator 2015-10-01T06:22:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowerDefencePAA
TEMPLATE = app


SOURCES += main.cpp \
    tower.cpp \
    game.cpp \
    wall.cpp \
    buildwallicon.cpp \
    enemyblueslime.cpp

HEADERS  += \
    tower.h \
    game.h \
    wall.h \
    buildwallicon.h \
    enemyblueslime.h

FORMS    +=

RESOURCES += \
    resource.qrc

QMAKE_CXXFLAGS += -std=c++0x
