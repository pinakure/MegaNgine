#ifndef DIALOG_H
#define DIALOG_H

#include "point.h"

#define DIALOG_TILE_UL      0x61AF
#define DIALOG_TILE_U       0x61B0
#define DIALOG_TILE_UR      0x61B1
#define DIALOG_TILE_CL      0x61CF
#define DIALOG_TILE_C       0x61D0
#define DIALOG_TILE_CR      0x61D1
#define DIALOG_TILE_BL      0x61EF
#define DIALOG_TILE_B       0x61F0
#define DIALOG_TILE_BR      0x61F1
#define DIALOG_TILE_LOWER   0x0030
#define DIALOG_TILE_UPPER   0x0050
#define DIALOG_TILE_HASH    0x004A
#define DIALOG_TILE_TILDE   0x004D
#define DIALOG_TILE_GRAVE   0x006D
#define DIALOG_TILE_BRACKET 0x006A
#define DIALOG_TILE_EXCLAM  0x0011
#define DIALOG_TILE_DIGITS  0x0020
#define DIALOG_TILE_LODASH  0x006E

typedef struct sDialog{

    int     x;
    int     y;
    int     w;
    int     h;
    Point   size;
    Point   cursor;
    void    (*init      )(void);
    void    (*wait      )(void);
    void    (*clear     )(void);
    void    (*nextLine  )(void);
    void    (*print     )(int, int, int , int,  const char*);
}Dialog;

extern Dialog dialog;
extern void Dialog_init();

#endif
