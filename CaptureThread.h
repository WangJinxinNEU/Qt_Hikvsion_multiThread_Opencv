#ifndef CAPTURETHREAD_H
#define CAPTURETHREAD_H

#include <QThread>
#include <QtGui>
// OpenCV header files
#include "opencv/highgui.h"
#include "ImageBuffer.h"
#include "HCNetSDK.h"
#include "LinuxPlayM4.h"
#include "PlayM4.h"
using namespace cv;

//class ImageBuffer;

class CaptureThread : public QThread
{
    Q_OBJECT

public:
    CaptureThread();
    void stopCaptureThread();
    int getInputSourceWidth();
    int getInputSourceHeight();
    void hik_init();

private:
    VideoCapture cap;
    Mat grabbedFrame;
protected:
    void run();
};





#endif // CAPTURETHREAD_H
