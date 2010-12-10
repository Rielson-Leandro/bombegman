QT += network
QT -= gui
TARGET = server
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += main.cc \
    world.cc \
    map.cc \
    mapentity.cc \
    player.cc \
    bomb.cc \
    bomber.cc \
    rand.cc
HEADERS += world.h \
    map.h \
    mapentity.h \
    player.h \
    bomb.h \
    bomber.h \
    rand.h \
    protocol.h

OTHER_FILES +=
