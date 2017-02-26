#include "window.h"

/*
** -----------------------------
** Permet d'innitialiser l'ecran
** -----------------------------
*/
void TInitScreen(TWindow *w){
    w->display = XOpenDisplay(NULL);
    if(w->display == NULL){
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}
    // On innitialise la taille de l'écran
    w->width = DisplayWidth(w->display, 0);
	w->height = DisplayHeight(w->display, 0);

    win->screen = DefaultScreen(w->display);
	win->window = XCreateSimpleWindow(w->display, RootWindow(w->display, w->screen), w->x, w->y, w->width, w->height, 0,
					BlackPixel(w->display, w->screen), WhitePixel(w->display, w->screen));
	XSelectInput(w->display, w->window,  ExposureMask | KeyPressMask);
	XMapWindow(w->display, w->window);
    XClearWindow(w->display, w->window);
    w->colormap = DefaultColormap(w->display, w->screen);
}
