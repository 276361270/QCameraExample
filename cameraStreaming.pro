#-------------------------------------------------
#
# Project created by QtCreator 2014-08-23T02:49:43
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cameraStreaming
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    CameraStream.cpp \
    CameraImageProcessor.cpp \
    ImgConverting.cpp \
    MyVideoWidget.cpp

HEADERS  += MainWindow.hpp \
    CameraStream.hpp \
    VideoEncoderInterface.hpp \
    CameraImageProcessor.hpp \
    ImgConverting.hpp \
    MyVideoWidget.hpp

FORMS    += MainWindow.ui

OTHER_FILES += \
    README.txt
