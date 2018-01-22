#ifndef PROCESSINGTHREAD_H
#define PROCESSINGTHREAD_H


// Qt header files
#include <QThread>
#include <QtGui>
// OpenCV header files
#include <opencv/highgui.h>
#include "ImageBuffer.h"

using namespace cv;

class ProcessingThread : public QThread
{
    Q_OBJECT

public:
    ProcessingThread(int inputSourceWidth, int inputSourceHeight);
    ~ProcessingThread();
    void stopProcessingThread();
    int getCurrentSizeOfBuffer();
private:
 //   ImageBuffer *imageBuffer;
  //  volatile bool stopped;
    int inputSourceWidth;
    int inputSourceHeight;
    int currentSizeOfBuffer;
    Mat currentFrame;
    Mat currentFrameGrayscale;
    QImage frame;
 //   QMutex stoppedMutex;
    QMutex updateMembersMutex;
    Size frameSize;
    Point framePoint;
    QString name;
    // Image processing flags

protected:
    void run();
signals:
    void newFrame(const QImage &frame);
    void newName(const QString &name);
};

#endif // PROCESSTHREAD_H
