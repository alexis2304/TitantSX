#include <X11/Xlib.h>

#ifndef COSCORE_H
#define COSCORE_H

/*
    La structure d'un pixel (sa position , sa couleur)
*/
typedef struct{
    int x;                  // Position sur l'axe des x.
    int y;                  // Position sur l'axe des y.'
    char* color;            // La couleur du pixel. Doit etre sous forme Hexadecimal (#000000) plus facile pour le programmeur.
}   COSPixel;



/*  +---------------------------------------------------------------------------+
    |La structure d'un WOBJECT, ici c'est un objet qui contiendra d'autre objet |
    |et a partir de celui ci on pourra afficher tout son contenue.              |
    +---------------------------------------------------------------------------+
*/
typedef struct{
    COSPixel *pixels;       // Les le rendu total en pixel.
    int z_position;         // La position z et la profondeur. (permet de superposer deux ou plusieurs COSWobject).
    char *name;             // Le nom du COSWobject, permet de le retrouver.
    int *types;             // Les types des sous objets
    int id;                 // L'id pour permetre de le retrouver plus facilement.
    void **childs;          // Les sous objets.
}   COSWobject;



/*  +-------------------------------------------------------------------------------------+
    |La strucutre de l'ecran. C'est elle qui contiendra les information pour gérer l'ecran|
    |ainsi que tout ce qui concerne l'affichage.                                          |
    +-------------------------------------------------------------------------------------+
*/
typedef struct{
    int width;              // la largeur.
    int height;             // la hauter.

    int x;                  // la position x.
    int y;                  // la position y.

    Display *display;       // Le display.
	Window window;          // la fenetere.
    int screen;             // l'ecran.
	XEvent event;           // Les evenetments.
    Colormap colormap;      // la colormap.

    COSWobject** wobject;    // Les objets qui s'affcherons.
    COSPixel *pixels;
    int wobjectLenght;

} COSScreen;



/*
    Les fonctions
*/
void COSInit(COSScreen *c);         // Cette fonction permet d'innitialiser l'os.
void COSUpdateView(COSScreen *c);   // Cette fonction permet de metre a jour l'affichage a l'écran.
void COSInitWobject(int isActive, COSWobject * w, COSScreen * c);   // Permet d'innitialiser un COSWobject.
#endif
