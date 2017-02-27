#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>

//#include "window.h"
//#include "imageLib.h"
#include "Core/Headers/COSCore.h"

int main(int argc, char **argv){
	COSScreen screen;
	COSInit(&screen);
	
	while(1){
		COSUpdateView(&screen);
		if(screen.event.type == KeyPress){
			screen.x++;
			XMoveWindow(screen.display, screen.window, screen.x, screen.y);
			printf("Key %d pressed !\n", screen.event.xkey.keycode);
			if(screen.event.xkey.keycode == 9)
				break;
		}
	}
	XCloseDisplay(screen.display);
	return 0;
}
