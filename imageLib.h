#include <X11/Xlib.h>
#include "window.h"

#ifndef IMAGELIB_H
#define IMAGELIB_H

typedef struct{
    Pixel*  pixels;
    int width;
    int height;
    int type;
} TImage;

TImage* createImage(int width, int height, int xp, int yp, int type);
void showImage(TImage* img, TWindow* w);

#endif
