#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <X11/Xlib.h>
#include <Imlib2.h>


int main(int argc, char **argv){
	Display *d;
	Window w;
	Visual *vis;
	XEvent e;
	Imlib_Image image;
    Pixmap pix, mask;
	int depth;
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
	depth = DefaultDepth(d, DefaultScreen(d));
	vis   = DefaultVisual(d, DefaultScreen(d));
	s = DefaultScreen(d);
	w = XCreateSimpleWindow(d, RootWindow(d, s), x, y, width, height, 0,
					BlackPixel(d, s), WhitePixel(d, s));
	XSelectInput(d, w,  ExposureMask | KeyPressMask);
	XMapWindow(d, w);
	//XSync(d, false);

	imlib_context_set_dither(1);
    imlib_context_set_display(d);
    imlib_context_set_visual(vis);

    image = imlib_load_image("./01_Home.jpg");
    imlib_context_set_image(image);

    pix = XCreatePixmap(d, w, 1920, 1080, depth);
    imlib_context_set_drawable(pix);
    imlib_render_image_on_drawable_at_size(0, 0, 300, 300);

    XSetWindowBackgroundPixmap(d, w, pix);
    XClearWindow(d, w);

	screen_colormap = DefaultColormap(d, s);
	Status rc;
	XParseColor(d, screen_colormap, "#000000", &col);
	XAllocColor(d, screen_colormap, &col);
	while(1){
		XNextEvent(d, &e);
		if(e.type == Expose){
			XSetForeground(d, DefaultGC(d, s), col.pixel);
			XFillRectangle(d, w, DefaultGC(d, s), 20, 20, 10, 10);
		}
		if(e.type == KeyPress){
			x++;
			XMoveWindow(d, w, x, y);
		}
		XFlush(d);
	}
	XCloseDisplay(d);
	return 0;
}
