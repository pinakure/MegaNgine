#ifndef AUTOMAP_H
#define AUTOMAP_H

#include "point.h"

#define AUTOMAP_DATA_WIDTH      4
#define AUTOMAP_DATA_HEIGHT     4

typedef struct sAutomap {
    unsigned char   data[ AUTOMAP_DATA_HEIGHT * AUTOMAP_DATA_WIDTH ];
    bool            redraw;
    Point           position;

    void    (*init          )(void);
    void    (*update        )(void);
    void    (*render        )(void);
    void    (*setPosition   )(int, int);
    
}Automap;

extern Automap automap;
extern void Automap_init(void);

#endif

