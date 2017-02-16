#-------------------------------------------------
#
# Project created by QtCreator 2017-02-14T12:31:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BaoGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    player.cpp \
    user.cpp \
    board.cpp

HEADERS  += mainwindow.h \
    game.h \
    player.h \
    user.h \
    board.h

FORMS    += mainwindow.ui
