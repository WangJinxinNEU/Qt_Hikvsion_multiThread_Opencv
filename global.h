#ifndef GLOBAL_H
#define GLOBAL_H

#include "ImageBuffer.h"

extern ImageBuffer *imageBuffer;
extern QMutex stoppedMutex;
extern volatile bool stopped;
extern QMutex stoppedMutex1;
extern volatile bool stopped1;
#endif // GLOBAL_H
