#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setWindowTitle(QString::fromUtf8("qt多线程读取海康摄像机数据"));
    imageBufferSize=2;//定义缓冲区的大小
    controller = new Controller;//创建控制器
    connect(ui->startButton,SIGNAL(clicked()),this,SLOT(startProgram()));
    connect(ui->stopButton,SIGNAL(clicked()),this,SLOT(stopProgram()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startProgram(){

        if((isCameraConnected=controller->connectToCamera(imageBufferSize,false,7,7)))     //参数的意义见Imagebuffer的定义
        {
            //将处理线程的“产生新的一帧”信号和GUI线程的“更新帧”槽连接
            connect(controller->processingThread,SIGNAL(newFrame(QImage)),this,SLOT(updateFrame(QImage)));
            // Create connections (3) between GUI thread (emitter) and processing thread (receiver/listener)
            // Get input stream properties
            sourceWidth=controller->captureThread->getInputSourceWidth();
            sourceHeight=controller->captureThread->getInputSourceHeight();
            //std::cout<<"111"<<std::endl;

            // Set text in labels in main window
        }
        // Display error dialog if camera connection is unsuccessful
        else
        {
            QMessageBox::warning(this,"ERROR:","Could not connect to camera.");
            // Delete dialogs
        }

} // startProgram()

void MainWindow::stopProgram()
{

    disconnect(controller->processingThread,SIGNAL(newFrame(QImage)),0,0);
    delete controller;
    this->close();



} // stopProgram()


void MainWindow::updateFrame(const QImage &frame)
{
    ui->frameLabel->setPixmap(QPixmap::fromImage(frame));
} // updateFrame()

