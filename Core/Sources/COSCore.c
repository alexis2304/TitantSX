#include <stdlib.h>
#include <stdio.h>

#include "../Headers/COSCore.h"

/*  +-----------------------------+
    |Permet d'innitialiser l'ecran|
    +-----------------------------+
*/
void COSInitScreen(TWindow *w){
    w->display = XOpenDisplay(NULL);
    if(w->display == NULL){
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}
    // On innitialise la taille de l'écran
    w->width = DisplayWidth(w->display, 0);
	w->height = DisplayHeight(w->display, 0);

    w->screen = DefaultScreen(w->display);
	w->window = XCreateSimpleWindow(w->display, RootWindow(w->display, w->screen), w->x, w->y, w->width, w->height, 0,
					BlackPixel(w->display, w->screen), WhitePixel(w->display, w->screen));
	XSelectInput(w->display, w->window,  ExposureMask | KeyPressMask);
	XMapWindow(w->display, w->window);
    XClearWindow(w->display, w->window);
    w->colormap = DefaultColormap(w->display, w->screen);
    w->pixelscount = 0;
}

/*  +------------------------------------------+
    |Permet de metre à jour la vue du conteneur|
    +------------------------------------------+
*/
void UpdateView(TWindow *w){
    int count = w->pixelscount;
    int i = 0;
    XColor col;

    XNextEvent(w->display, &w->event);
    while(i < count){
		if(w->event.type == Expose){
            XParseColor(w->display, w->colormap, w->pixels[i].color, &col);
        	XAllocColor(w->display, w->colormap, &col);
			XSetForeground(w->display, DefaultGC(w->display, w->screen), col.pixel);
			XDrawPoint(w->display, w->window, DefaultGC(w->display, w->screen), w->pixels[i].x, w->pixels[i].y);
		}
        XFlush(w->display);
        i++;
    }
}
