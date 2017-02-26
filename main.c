#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>

#include "window.h"


int main(int argc, char **argv){
	TWindow win;
	TInitScreen(&win);
	/*
	Display *d;
	Window w;
	XEvent e;
	int x;		// la position x
	int y;		// La position y
	int width;	// La largeur
	int height;	// La hauteur

	x = 0;
	y = 0;
	width = 300;
	height = 300;

	// La colormap pour alouer les couleurs
	Colormap screen_colormap;

	// Crée les valeur de couleurs
	XColor col;

	char* msg = "Hello World!";
	int s;

	d = XOpenDisplay(NULL);
	if(d == NULL){
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}
	width = DisplayWidth(d, 0);
	height = DisplayHeight(d, 0);
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), x, y, width, height, 0,
					BlackPixel(d, s), WhitePixel(d, s));
	XSelectInput(d, w,  ExposureMask | KeyPressMask);
	XMapWindow(d, w);
    XClearWindow(d, w);

	printf("Screen Width : %d\n", DisplayWidth(d, 0));
	printf("Screen Height : %d\n", DisplayHeight(d, 0));

	screen_colormap = DefaultColormap(d, s);
	*/
	XColor col;
	Status rc;
	XParseColor(win.display, win.colormap, "#000000", &col);
	XAllocColor(win.display, win.colormap, &col);
	while(1){
		XNextEvent(win.display, &win.event);
		if(win.event.type == Expose){
			XSetForeground(win.display, DefaultGC(win.display, win.screen), col.pixel);
			XFillRectangle(win.display, win.window, DefaultGC(win.display, win.screen), 20, 20, 10, 10);
		}
		if(win.event.type == KeyPress){
			x++;
			XMoveWindow(win.display, win.window, x, y);
			printf("Key %d pressed !\n", win.event.xkey.keycode);
			if(win.event.xkey.keycode == 9)
				break;
		}
		XFlush(win.display);
	}
	XCloseDisplay(win.display);
	return 0;
}
