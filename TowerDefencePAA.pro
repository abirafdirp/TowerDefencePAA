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
    Wall.cpp \
    BuildWallIcon.cpp \
    EnemyBlueSlime.cpp \
    Game.cpp \
    Tile.cpp \
    Tower.cpp \
    MyApplication.cpp \
    Enemy.cpp \
    Path.cpp

HEADERS  += \
    Wall.h \
    Tower.h \
    Tile.h \
    Game.h \
    EnemyBlueSlime.h \
    BuildWallIcon.h \
    MyApplication.h \
    Enemy.h \
    Path.h

FORMS    +=

RESOURCES += \
    resource.qrc

QMAKE_CXXFLAGS += -std=c++0x

CONFIG+=c++11
