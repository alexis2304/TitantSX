#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>

int main(int argc, char **argv){
	Display *d;
	Window w;
	XEvent e;
	
	int x;		// la position x
	int y;		// La position y
	int width;	// La largeur
	int height;	// La hauteur	

	
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
	
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, 100, 100, 0,
					BlackPixel(d, s), WhitePixel(d, s));
	XSelectInput(d, w,  ExposureMask | KeyPressMask);
	XMapWindow(d, w);
	
	screen_colormap = DefaultColormap(d, s);
	Status rc;
	XParseColor(d, screen_colormap, "#FFFFFF", &col);
	XAllocColor(d, screen_colormap, &col);
	while(1){
		XNextEvent(d, &e);
		if(e.type == Expose){
			XSetForeground(d, DefaultGC(d, s), col.pixel);
			XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
			XDrawString(d, w, DefaultGC(d, s), 10, 50, msg, strlen(msg));
		}
		if(e.type == KeyPress)
			break;
	}
	XCloseDisplay(d);
	return 0;
}
