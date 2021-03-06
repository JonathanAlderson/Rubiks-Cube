######################################################################
# Automatically generated by qmake (3.0) Tue Aug 8 14:19:53 2017
######################################################################

TEMPLATE = app
TARGET = RubiksCube
INCLUDEPATH += . /opt/local/include

QT += widgets opengl gui

LIBS += -lglut -lGLU

CONFIG += c++11

# Input
HEADERS += Image.h RubiksWidget.h RubiksWindow.h cubie.h cube.h confetti.h materials.h
SOURCES += RubiksMain.cpp \
           RubiksWidget.cpp \
           RubiksWindow.cpp \
           cube.cpp \
           cubie.cpp \
           Image.cpp \
           confetti.cpp
