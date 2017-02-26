#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "imageLib.h"

/*
**
** Permet de crée une image blanche
**
*/
TImage* createImage(int width, int height, int xp, int yp, int type){
    TImage *image = malloc(sizeof(TImage) * 1);
    image->width = width;
    image->height = height;
    image->type = type;
    int pixelSize = width * height;
    Pixel *pixels = malloc(sizeof(Pixel) * pixelSize);
    image->pixels = pixels;
    int x = 0;
    int y = 0;

    // innitialise l'image avec la couleur noir
    while(y < height){
        x = 0;
        while(x < width){
            image->pixels[y * x].color = "#000000";
            image->pixels[y * x].x = x + xp;
            image->pixels[y * x].y = y + yp;
            x++;
        }
        y++;
    }
}

void showImage(TImage* img, TWindow* w){
    w->pixelscount = (img->width) * (img->height);
    w->pixels = img->pixels;
}
