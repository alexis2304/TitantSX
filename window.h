#include <X11/Xlib.h>

#ifndef WINDOW_H
#define WINDOW_H

typedef struct{
    int x;
    int y;
    char* color;
}   Pixel;

typedef struct{
    Pixel *pixels;
    int z_position;
    ScreenObject* child;
}   ScreenObject;

typedef struct{
    int width;  // la largeur.
    int height; // la hauter.

    int x;  // la position x
    int y;  // la position y

    Display *display;       // Le display
	Window window;          // la fenetere
    int screen;          // l'ecran
	XEvent event;               // Les evenetments
    Colormap colormap;      // la colormap
    Pixel* pixels;
    int pixelscount;
} TWindow;

void TInitScreen(TWindow *w);
void UpdateView(TWindow *w);

#endif
