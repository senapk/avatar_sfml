TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += rock/game.c \
    rock/tk.c \
    rock/aluno.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    rock/tk.h \
    rocke/aluno.h

LIBS += -lncurses
