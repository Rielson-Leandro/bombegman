# -------------------------------------------------
# Project created by QtCreator 2010-11-22T13:38:26
# -------------------------------------------------
QT += network
QT -= gui
TARGET = server
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cc \
    world.cc \
    map.cc \
    mapobject.cc \
    player.cc \
    bomb.cc \
    bomber.cc
HEADERS += world.h \
    map.h \
    mapobject.h \
    player.h \
    bomb.h \
    bomber.h

OTHER_FILES += \
    server.ini
