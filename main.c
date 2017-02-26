#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>

#include "window.h"
#include "imageLib.h"


int main(int argc, char **argv){
	TWindow win;
	TInitScreen(&win);
	TImage *myimg = createImage(100, 100, 400, 300, 0);
	showImage(myimg, win);
	while(1){
		UpdateView(&win);
		if(win.event.type == KeyPress){
			win.x++;
			XMoveWindow(win.display, win.window, win.x, win.y);
			printf("Key %d pressed !\n", win.event.xkey.keycode);
			if(win.event.xkey.keycode == 9)
				break;
		}
	}
	XCloseDisplay(win.display);
	return 0;
}
