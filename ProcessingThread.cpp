#include "ImageBuffer.h"
#include "ProcessingThread.h"
#include "MatToQImage.h"

// Qt header files
#include <QDebug>
// OpenCV header files
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "global.h"
// Configuration header file
//构造函数，指定缓冲区，和图片宽度、高度
ProcessingThread::ProcessingThread(int inputSourceWidth, int inputSourceHeight) : QThread(),
                                   inputSourceWidth(inputSourceWidth),
                                   inputSourceHeight(inputSourceHeight)
{
    // Initialize variables
    stopped1=false;
} // ProcessingThread constructor

ProcessingThread::~ProcessingThread()
{
} // ProcessingThread destructor

//处理线程的主功能函数
void ProcessingThread::run()
{
    while(1)
    {
        /////////////////////////////////
        // Stop thread if stopped=TRUE //测试是否停止的过程要加锁
        /////////////////////////////////
        stoppedMutex1.lock();
        if (stopped1)
        {
            stopped1=false;
            stoppedMutex1.unlock();
            break;
        }
        stoppedMutex1.unlock();
        /////////////////////////////////

        // Get frame from queue, store in currentFrame, set ROI
        currentFrame=Mat(imageBuffer->getFrame());//从缓冲区中取出一帧
        //currentFrame=imread("Penguins.jpg");

        updateMembersMutex.lock();

        //以下的函数或者程序可以用来对每一帧图像进行处理
        frame=MatToQImage(currentFrame);
        updateMembersMutex.unlock();
        // Convert Mat to QImage: Show BGR frame


        // Update statistics
        currentSizeOfBuffer=imageBuffer->getSizeOfImageBuffer();
        // Inform GUI thread of new frame (QImage)
        //发出信号，通知GUI线程有新处理好的一帧
        emit newFrame(frame);
    }
    qDebug() << "Stopping processing thread...";
}

//停止处理线程
void ProcessingThread::stopProcessingThread()
{
    stoppedMutex.lock();
    stopped=true;
    stoppedMutex.unlock();
} // stopProcessingThread()


int ProcessingThread::getCurrentSizeOfBuffer()
{
    return currentSizeOfBuffer;
} // getCurrentSizeOfBuffer()


