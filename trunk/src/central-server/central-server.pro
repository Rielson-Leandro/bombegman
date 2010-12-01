#-------------------------------------------------
#
# Project created by QtCreator 2010-11-29T14:01:19
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = central-server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cc \
    server.cc \
    clientconnection.cc

HEADERS += \
    server.h \
    clientconnection.h
