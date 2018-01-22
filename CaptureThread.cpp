#include "CaptureThread.h"
#include "ImageBuffer.h"
#include "opencv2/opencv.hpp"
#include "global.h"
#include "unistd.h"

// Qt header files
#include <QDebug>
int nPort=0;
volatile int gbHandling=3 ;
unsigned int count=1;


void CALLBACK DecCBFun(int nPort, char * pBuf, int nSize, FRAME_INFO * pFrameInfo, void * nReserved1, int nReserved2)
{
    if (gbHandling)
    {
        gbHandling--;
        return;
    }

    long lFrameType = pFrameInfo->nType;
    if (lFrameType == T_YV12)
    {

        Mat pImg(pFrameInfo->nHeight, pFrameInfo->nWidth, CV_8UC3);
        Mat src(pFrameInfo->nHeight + pFrameInfo->nHeight / 2, pFrameInfo->nWidth, CV_8UC1, pBuf);
        cvtColor(src, pImg, CV_YUV2BGR_YV12);
    //  Sleep(-1);
        stoppedMutex.lock();//测试是否停止的过程要加锁
         if (stopped)
         {
             stopped=false;
             stoppedMutex.unlock();
         }
         stoppedMutex.unlock();
         // Capture and add frame to buffer

         //cv::resize(pImg, pImg, Size(600, 400), 0, 0, 3);
         if(count%5==0)
         {
             //pImg=pImg(cv::Rect(400,0,900,1000));//ab为左上角的定点 cd为其宽度和长度
             cv::resize(pImg, pImg, Size(480, 360), 0, 0, 3);

             imageBuffer->addFrame(pImg);//添加到缓冲区队列
         }
         count++;
         //resize(pImg, pImg, Size(960, 960), 0, 0, CV_INTER_LINEAR);
         //imshow("IPCamera", pImg);
         //imwrite( "/home/wjx/qt_project/Attendance_Monitoring_System_hik/data/Gray_Image.jpg", pImg );
         qDebug()<<"11";
         //waitKey(1);


    }

    gbHandling = 3;

}

///实时流回调
void CALLBACK fRealDataCallBack(LONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, void *pUser)
{

    switch (dwDataType)
    {

    case NET_DVR_SYSHEAD: //系统头

        if (!PlayM4_GetPort(&nPort))  //获取播放库未使用的通道号
        {
            break;
        }
        //m_iPort = lPort; //第一次回调的是系统头，将获取的播放库port号赋值给全局port，下次回调数据时即使用此port号播放

        if (dwBufSize > 0)
        {
            std::cout<<"dwBufSize      "<<dwBufSize<<std::endl;
            if (!PlayM4_SetStreamOpenMode(nPort, STREAME_REALTIME))  //设置实时流播放模式
            {
                break;
            }

            if (!PlayM4_OpenStream(nPort, pBuffer, dwBufSize, 10*1024 * 1024)) //打开流接口
            {
                break;
            }

            if (!PlayM4_Play(nPort, NULL)) //播放开始
            {
                break;
            }
            if (!PlayM4_SetDecCallBackEx(nPort, DecCBFun, NULL, NULL))
            {
                break;
            }

//            if (PlayM4_SetDecCallBack(nPort, DecCBFun))
//            {
//                std::cout<<"33"<<std::endl;

//               // break;
//            }
        }
        break;
    case NET_DVR_STREAMDATA:   //码流数据
        if (dwBufSize > 0 && nPort != -1)
        {
            if (!PlayM4_InputData(nPort, pBuffer, dwBufSize))
            {
                std::cout << "error" << PlayM4_GetLastError(nPort) << std::endl;
                break;
            }
        }
        break;
    default: //其他数据
        if (dwBufSize > 0 && nPort != -1)
        {
            if (!PlayM4_InputData(nPort, pBuffer, dwBufSize))
            {
                break;
            }
        }
        break;
    }
}

void CALLBACK g_ExceptionCallBack(DWORD dwType, LONG lUserID, LONG lHandle, void *pUser)
{
    char tempbuf[256] = { 0 };
    switch (dwType)
    {
    case EXCEPTION_RECONNECT:    //预览时重连
        printf("----------reconnect--------%d\n", time(NULL));
        break;
    default:
        break;
    }
}






//根据给定缓冲区建立捕获进程
CaptureThread::CaptureThread() : QThread()

{
    // Initialize variables
    stopped=false;//停止标志

} // CaptureThread constructor




//线程主功能函数
void CaptureThread::run()
{
    //---------------------------------------
    // 初始化
    NET_DVR_Init();
    //设置连接时间与重连时间
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);


    //---------------------------------------
    // 注册设备
    LONG lUserID;
    NET_DVR_DEVICEINFO_V30 struDeviceInfo;
    lUserID = NET_DVR_Login_V30("219.216.81.34", 8000, "admin", "1234qwer", &struDeviceInfo);
    if (lUserID < 0)
    {
        printf("Login error, %d\n", NET_DVR_GetLastError());
        NET_DVR_Cleanup();
        return;
    }

    //---------------------------------------
    //设置异常消息回调函数
    NET_DVR_SetExceptionCallBack_V30(0, NULL, g_ExceptionCallBack, NULL);

    //---------------------------------------
    //启动预览并设置回调数据流
    LONG lRealPlayHandle;




    NET_DVR_PREVIEWINFO struPlayInfo = { 0 };
    struPlayInfo.hPlayWnd = NULL;         //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
    struPlayInfo.lChannel = 1;           //预览通道号
    struPlayInfo.dwStreamType = 0;       //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
    struPlayInfo.dwLinkMode = 1;         //0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP

    lRealPlayHandle = NET_DVR_RealPlay_V40(lUserID, &struPlayInfo, fRealDataCallBack, NULL);

    if (lRealPlayHandle < 0)
    {
        printf("NET_DVR_RealPlay_V40 error\n");
        printf("%d\n", NET_DVR_GetLastError());
        NET_DVR_Logout(lUserID);
        NET_DVR_Cleanup();
        return;
    }
    waitKey();

    sleep(-1);
    //---------------------------------------
    //关闭预览
    NET_DVR_StopRealPlay(lRealPlayHandle);
    //注销用户
    NET_DVR_Logout(lUserID);
    //释放SDK资源
    NET_DVR_Cleanup();

    qDebug() << "Stopping capture thread...";
}

//打开摄像机

void CaptureThread::stopCaptureThread()
{
    stoppedMutex.lock();
    stopped=true;
    stoppedMutex.unlock();
} // stopCaptureThread()


int CaptureThread::getInputSourceWidth()
{
    return cap.get(CV_CAP_PROP_FRAME_WIDTH);//帧宽度
} // getInputSourceWidth()

int CaptureThread::getInputSourceHeight()
{
    return cap.get(CV_CAP_PROP_FRAME_HEIGHT);//帧高度
} // getInputSourceHeight()



