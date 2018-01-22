#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include "Controller.h"
#include <iostream>

#include <QTextCodec>
#include <fstream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    Controller *controller;
    int sourceWidth;
    int sourceHeight;
    int imageBufferSize;
    bool isCameraConnected;


public slots:
    void startProgram();
    void stopProgram();

private slots:
    void updateFrame(const QImage &frame);
};

#endif // MAINWINDOW_H
