#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>

#include "window.h"


int main(int argc, char **argv){
	TWindow win;
	TInitScreen(&win);

	XColor col;
	Status rc;
	XParseColor(win.display, win.colormap, "#000000", &col);
	XAllocColor(win.display, win.colormap, &col);
	while(1){
		XNextEvent(win.display, &win.event);
		if(win.event.type == Expose){
			XSetForeground(win.display, DefaultGC(win.display, win.screen), col.pixel);
			//XFillRectangle(win.display, win.window, DefaultGC(win.display, win.screen), 20, 20, 10, 10);
			XDrawPoint(win.display, col.pixel, DefaultGC(win.display, win.screen), 10, 10);
		}
		if(win.event.type == KeyPress){
			win.x++;
			XMoveWindow(win.display, win.window, win.x, win.y);
			printf("Key %d pressed !\n", win.event.xkey.keycode);
			if(win.event.xkey.keycode == 9)
				break;
		}
		XFlush(win.display);
	}
	XCloseDisplay(win.display);
	return 0;
}
