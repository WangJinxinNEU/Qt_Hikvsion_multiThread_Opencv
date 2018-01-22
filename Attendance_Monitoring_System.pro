#-------------------------------------------------
#
# Project created by QtCreator 2017-10-31T21:30:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Attendance_Monitoring_System
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
        mainwindow.cpp\
    MatToQImage.cpp \
    CaptureThread.cpp \
    ImageBuffer.cpp \
    ProcessingThread.cpp \
    Controller.cpp \
    global.cpp

HEADERS  += mainwindow.h\
    MatToQImage.h \
    CaptureThread.h \
    ImageBuffer.h \
    ProcessingThread.h \
    Controller.h \
    global.h

FORMS    += mainwindow.ui


INCLUDEPATH += /home/wjx/opencv-2.4.13/include/opencv \
INCLUDEPATH += /home/wjx/opencv-2.4.13/include/opencv2 \
INCLUDEPATH += /home/wjx/HIKSDK64/incCn \
#INCLUDEPATH += /usr/include \
#INCLUDEPATH += /usr/local/include \
#INCLUDEPATH += /usr/local/cuda-8.0/include \


#LIBS += -L/usr/lib/
#LIBS += -L/usr/local/lib/
#LIBS += -L/usr/lib/x86_64-linux-gnu/
#LIBS += -L/usr/local/cuda-8.0/lib64/
#LIBS += -L/usr/local/cuda/lib/
#LIBS += -L/usr/lib/nvidia-375/

#LIBS += -lcurand -lcublas -lcublas_device -lcudnn -lcudart_static

LIBS += -L/home/wjx/opencv-2.4.13/build/lib\
-lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
-lopencv_ml \
-lopencv_video \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_objdetect \
-lopencv_contrib \
-lopencv_legacy \
-lopencv_flann \

#LIBS += -lGLU -lGL -lglut
#LIBS += -lcudnn -lglog -lgflags -lboost_system -lboost_filesystem -lm -lboost_thread
#LIBS += -pthread -fPIC -std=c++11 -fopenmp

#LIBS+=-L/home/wjx/qt_project/Attendance_Monitoring_System_hik \
#-lopenpose -lcaffe


LIBS += -L/home/wjx/HIKSDK64/lib \
-lHCCore \
-lHCDisplay \
-lPlayCtrl \
-lHCPlayBack \
-lAudioRender \
-lSuperRender \
-lHCAlarm \
-lHCCoreDevCfg \
-lHCGeneralCfgMgr \
-lhcnetsdk \
-lHCPlayBack \
-lanalyzedata \
-lHCIndustry \
-lHCPreview \
-lHCVoiceTalk \
-lhpr \
-liconv2 \
-lStreamTransClient \
-lSystemTransform \

