# -------------------------------------------------
# Project created by QtCreator 2010-11-22T13:39:36
# -------------------------------------------------
QT += network \
    svg
TARGET = client
TEMPLATE = app
SOURCES += main.cc \
    mainwindow.cc \
    world.cc \
    interpreter.cc \
    drawer.cc \
    formatter.cc \
    inputhandler.cc \
    connectdialog.cc
HEADERS += mainwindow.h \
    world.h \
    interpreter.h \
    drawer.h \
    formatter.h \
    inputhandler.h \
    connectdialog.h

RESOURCES += \
    std.qrc
