#include <stdlib.h>
#include <stdio.h>

#include "../Headers/COSCore.h"

/*  +-----------------------------+
    |Permet d'innitialiser l'ecran|
    +-----------------------------+
*/
void COSInitScreen(COSScreen *c){
    c->display = XOpenDisplay(NULL);
    if(c->display == NULL){
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}
    // On innitialise la taille de l'écran
    c->width = DisplayWidth(c->display, 0);
	c->height = DisplayHeight(c->display, 0);

    c->screen = DefaultScreen(c->display);
	c->window = XCreateSimpleWindow(c->display, RootWindow(c->display, c->screen), c->x, c->y, c->width, c->height, 0,
					BlackPixel(c->display, c->screen), WhitePixel(c->display, c->screen));
	XSelectInput(c->display, c->window,  ExposureMask | KeyPressMask);
	XMapWindow(c->display, c->window);
    XClearWindow(c->display, c->window);
    c->colormap = DefaultColormap(c->display, c->screen);
    c->pixelscount = 0;
    c->wobject = NULL;  // Innitialisations des objets a null
    c->wobjectLenght = 0;
}

/*  +------------------------------------------+
    |Permet de metre à jour la vue du conteneur|
    +------------------------------------------+
*/
void COSUpdateView(COSScreen *c){
    int count = c->pixelscount;
    int i = 0;
    XColor col;

    XNextEvent(c->display, &c->event);
    while(i < count){
		if(c->event.type == Expose){
            XParseColor(c->display, c->colormap, c->pixels[i].color, &col);
        	XAllocColor(c->display, c->colormap, &col);
			XSetForeground(c->display, DefaultGC(c->display, c->screen), col.pixel);
			XDrawPoint(c->display, c->window, DefaultGC(c->display, c->screen), c->pixels[i].x, c->pixels[i].y);
		}
        XFlush(c->display);
        i++;
    }
}


/*  -----------------------------------------
    Innitialise un nouvelle element COSWobjet
    -----------------------------------------
*/
void COSInitWobject(int isActive, COSWobject * w, COSScreen * c){
    COSWobject ** temp;

    temp = realloc(c->wobject, sizeof(COSWobject *) * (c->wobjectLenght + 1));
    if(temp == NULL){
        fprintf(stderr,"Reallocation impossible");
        free(c->wobject);
        exit(EXIT_FAILURE);
    }
    c->wobject = temp;
    c->wobjectLenght = c->wobjectLenght + 1;
    
    w->id = c->wobjectLenght - 1;
    char buffer[20];
    char *_name = {'_', 'O', 'B', 'J', itoa(w->id, buffer, 10)};
    w->name = _name;
    w->types = NULL;

    c->wobject[w->id] = w;
}