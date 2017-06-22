#-------------------------------------------------
#
# Project created by QtCreator 2017-06-04T19:21:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gomoku
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    judges/free_style_judge.cpp \
    judges/std_gomoku_judge.cpp \
    organizers/std_organizer.cpp \
    players/human_player.cpp \
    players/primary_ai.cpp \
    players/threat_finder.cpp \
    board.cpp \
    game.cpp \
    game_factory.cpp \
    game_organizer.cpp \
    player.cpp \
    te.cpp \
    judges/forbidden_judge.cpp \
    settings_dialog.cpp

HEADERS  += mainwindow.h \
    judges/free_style_judge.h \
    judges/std_gomoku_judge.h \
    organizers/std_organizer.h \
    players/human_player.h \
    players/primary_ai.h \
    players/threat_finder.h \
    board.h \
    game.h \
    game_factory.h \
    game_organizer.h \
    player.h \
    te.h \
    winning_judge.h \
    judges/forbidden_judge.h \
    settings_dialog.h

FORMS    +=

RESOURCES += \
    resources.qrc

RC_ICONS = ./res/icon.ico
