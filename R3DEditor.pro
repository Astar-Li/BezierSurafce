#-------------------------------------------------
#
# Project created by QtCreator 2019-05-05T17:36:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = R3DEditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    r3deditor.cpp \
    imagewidget.cpp \
    r3deditor_viewport.cpp \
    r3deditor_wireframe_painter.cpp \
    r3deditor_bezier_surface.cpp \
    r3deditor_camera.cpp \
    r3deditor_axis_painter.cpp \
    r3deditor_object_editor_painter.cpp \
    r3deditor_object.cpp

HEADERS += \
        mainwindow.h \
    r3deditor.h \
    observer.h \
    imagewidget.h \
    r3deditor_viewport.h \
    r3deditor_3d_types.h \
    r3deditor_bezier_surface.h \
    r3deditor_wireframe_painter.h \
    r3deditor_camera.h \
    r3deditor_axis_painter.h \
    r3deditor_object_editor_painter.h \
    r3deditor_object.h \
    r3deditor_scene.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
