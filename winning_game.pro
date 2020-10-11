QT -= gui

DESTDIR = bin
CONFIG += c++11 console
CONFIG -= app_bundle
QMAKE_LFLAGS += -no-pie

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QT += opengl
LIBS += -lSOIL -lGLEW -lglfw

SOURCES += main.cpp \
    statemachine.cpp \
    rotationmanager.cpp \
    countingmanager.cpp \
    reel.cpp \
    drawingmanager.cpp \
    globject.cpp \
    image.cpp \
    textureinfo.cpp \
    sceneinfo.cpp \
    resourceloader.cpp \
    buttons/doubleimagebutton.cpp \
    buttons/doublestatebutton.cpp \
    buttons/imagebutton.cpp \
    buttons/timebuttonscontainer.cpp \
    tweens/tweenbase.cpp \
    tweens/tweencoord.cpp \
    tweens/tweencurves.cpp \
    tweens/tweenmanager.cpp \
    tweens/tweenqueue.cpp \
    tweens/tweenscale.cpp \
    timermanager.cpp \
    timer.cpp \
    doubleimage.cpp \
    tweens/actiontween.cpp

HEADERS += \
    statemachine.h \
    rotationmanager.h \
    countingmanager.h \
    reel.h \
    shader.h \
    drawingmanager.h \
    image.h \
    globject.h \
    textureinfo.h \
    sceneinfo.h \
    resourceloader.h \
    buttons/doubleimagebutton.h \
    buttons/doublestatebutton.h \
    buttons/imagebutton.h \
    buttons/timebuttonscontainer.h \
    tweens/tweenbase.h \
    tweens/tweencoord.h \
    tweens/tweencurves.h \
    tweens/tweenmanager.h \
    tweens/tweenqueue.h \
    tweens/tweenscale.h \
    timermanager.h \
    timer.h \
    doubleimage.h \
    tweens/actiontween.h
