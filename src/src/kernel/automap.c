#include <genesis.h>
#include "automap.h"
#include "sys.h"
#include "dialog.h"

Automap automap;

void Automap_render(void){
    int x = 33;
    int y = 1;
    int w = 5;
    int h = 5;
    VDP_setTileMapXY(BG_B, DIALOG_TILE_UL, x      , y    );
    VDP_setTileMapXY(BG_B, DIALOG_TILE_UR, x + w  , y    );
    VDP_setTileMapXY(BG_B, DIALOG_TILE_BL, x      , y + h);
    VDP_setTileMapXY(BG_B, DIALOG_TILE_BR, x + w  , y + h);
    
    for(int ix=1; ix<w; ix++){
        VDP_setTileMapXY(BG_B, DIALOG_TILE_U, x + ix, y    );
        VDP_setTileMapXY(BG_B, DIALOG_TILE_B, x + ix, y + h);
    }
    for(int iy=1; iy<h; iy++){
        VDP_setTileMapXY(BG_B, DIALOG_TILE_CL, x    , y + iy);
        VDP_setTileMapXY(BG_B, DIALOG_TILE_CR, x + w, y + iy);
    }
    for(int iy=1; iy<h; iy++){
        for(int ix=1; ix<w; ix++){
        VDP_setTileMapXY(BG_B, DIALOG_TILE_C, x + ix, y + iy);
        }
    }
    automap.redraw = false;

    VDP_setTileMapXY(BG_B, 0x41B2, x + 1, y + 1);
    VDP_setTileMapXY(BG_B, 0x41B3, x + 2, y + 1);
    VDP_setTileMapXY(BG_B, 0x41B3, x + 3, y + 1);
    VDP_setTileMapXY(BG_B, 0x49B2, x + 4, y + 1);

    VDP_setTileMapXY(BG_B, 0x41D2, x + 1, y + 2);
    VDP_setTileMapXY(BG_B, 0x61D0, x + 2, y + 2);
    VDP_setTileMapXY(BG_B, 0x61D0, x + 3, y + 2);
    VDP_setTileMapXY(BG_B, 0x49D2, x + 4, y + 2);
    

    VDP_setTileMapXY(BG_B, 0x41D2, x + 1, y + 3);
    VDP_setTileMapXY(BG_B, 0x61D0, x + 2, y + 3);
    VDP_setTileMapXY(BG_B, 0x61D0, x + 3, y + 3);
    VDP_setTileMapXY(BG_B, 0x49D2, x + 4, y + 3);

    VDP_setTileMapXY(BG_B, 0x51B3, x + 2, y + 4);
    VDP_setTileMapXY(BG_B, 0x51B2, x + 1, y + 4);
    VDP_setTileMapXY(BG_B, 0x51B3, x + 3, y + 4);
    VDP_setTileMapXY(BG_B, 0x59B2, x + 4, y + 4);

}

void Automap_update(void){
    if( automap.redraw ) automap.render();
}

void Automap_setPosition(int x, int y){
    if( ( x != automap.position.x)||( y != automap.position.y) ) automap.redraw = true;
    automap.position.x = x;
    automap.position.y = y;
}

void Automap_init(void){
    automap.update      = Automap_update;
    automap.render      = Automap_render;
    automap.setPosition = Automap_setPosition;

    unsigned char *p = automap.data;
    for(int y=0; y<AUTOMAP_DATA_HEIGHT; y++){
        for(int x=0; x<AUTOMAP_DATA_WIDTH; x++){
            *p = 0;
            p++;
        }
    }

    automap.setPosition( 0, 0 );
}
