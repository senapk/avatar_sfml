TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += game.c \
    aluno.c \
    csf.c

HEADERS += \
    aluno.h \
    csf.h \
    aluno.h

LIBS += -lcsfml-graphics -lcsfml-audio
