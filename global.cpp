#include "global.h"

QMutex stoppedMutex;
QMutex stoppedMutex1;
ImageBuffer *imageBuffer = new ImageBuffer(5,true);
volatile bool stopped = true;
volatile bool stopped1 = true;
