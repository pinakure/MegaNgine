#include <genesis.h>
#include "gpu.h"
#include "sys.h"
#include "key.h"
#include "dialog.h"

Dialog dialog;

void Dialog_clear(void){
    for(int iy=0; iy<dialog.size.y; iy++){
        for(int ix=0; ix<dialog.size.x; ix++){
            VDP_setTileMapXY(BG_A, 0x6000, dialog.x + ix, dialog.y + iy);
        }
    }
}

void Dialog_wait(void){
    dialog.cursor.y = 0;
    int counter=0;
    while( !key.press( BUTTON_A ) ){
        if((counter & 0x1f) == 0x10)
            VDP_setTileMapXY(BG_A, 0x3000 | DIALOG_TILE_GRAVE, dialog.x + (dialog.w-1) , dialog.y + (dialog.h-1));
        else if((counter & 0x1f) == 0x00)
            VDP_setTileMapXY(BG_A, 0x3000, dialog.x + (dialog.w-1) , dialog.y + (dialog.h-1));
        counter++;
        sys.updateGfx();
    } while( !key.noinput() ){
        sys.updateGfx();
    }

    dialog.clear();
}

void Dialog_nextLine(void){
    dialog.cursor.x = dialog.x;
    dialog.cursor.y++;
    if( dialog.cursor.y > ( dialog.h-2 ) ){
        dialog.wait();
        dialog.cursor.x = dialog.x;
        dialog.cursor.y = dialog.y;
    }
}

void Dialog_print(int x, int y, int w, int h, const char *text){
    int     speed   = 0;
    Point   origin;
    origin.x = x;
    origin.y = y;
    dialog.w        = 2<<speed;
    dialog.h        = 2<<speed;
    dialog.size.x   = w;
    dialog.size.y   = h;
    dialog.x        = x;
    dialog.y        = y;
    w               = 0;
    h               = 0;
    // Draw box
    dialog.clear();
    
    while(( w < dialog.size.x ) || ( h < dialog.size.y) ){
        
        w           = dialog.w >> speed;
        h           = dialog.h >> speed;
        dialog.x    = origin.x + (( dialog.size.x >> 1 )-( w >> 1 ));
        dialog.y    = origin.y + (( dialog.size.y >> 1 )-( h >> 1 ));
        x           = dialog.x;
        y           = dialog.y;
        
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
        
        if( w < dialog.size.x ) dialog.w++;        
        if( h < dialog.size.y ) dialog.h++;
        sys.updateGfx();
    }
    dialog.w >>= speed;
    dialog.h >>= speed;
    dialog.cursor.x = dialog.x;
    dialog.cursor.y = dialog.y;
    // Print text
    for( int i=0, li=i+strlen(text); i<li; i++ ){
        int c = text[i];
        if( c == ' ') {
            c = 0;
            if(dialog.cursor.x == dialog.x)continue;
        }
        else {
            if(c == '\n' ){ 
                dialog.nextLine(); 
                continue;
            }
                 if( ( c == '#' )                 ) c = DIALOG_TILE_HASH;
            else if( ( c == '~' )                 ) c = DIALOG_TILE_TILDE;
            else if( ( c == '^' )                 ) c = DIALOG_TILE_GRAVE;
            else if( ( c == '_' )                 ) c = DIALOG_TILE_LODASH;
            else if( ( c >= '0' ) && ( c <= '9' ) ) c = ( DIALOG_TILE_DIGITS    + c ) - '0';
            else if( ( c >= 'A' ) && ( c <= 'Z' ) ) c = ( DIALOG_TILE_UPPER     + c ) - 'A';
            else if( ( c >= 'a' ) && ( c <= 'z' ) ) c = ( DIALOG_TILE_LOWER     + c ) - 'a';
            else if( ( c >= '[' ) && ( c <= ']' ) ) c = ( DIALOG_TILE_BRACKET   + c ) - '[';
            else                                    c = ( DIALOG_TILE_EXCLAM    + c ) - '!';
        }
        VDP_setTileMapXY(BG_A, 0x2000 | c, dialog.cursor.x+1, dialog.cursor.y+1);
        dialog.cursor.x++;
        if( dialog.cursor.x > dialog.x+( dialog.w - 2 ) ) dialog.nextLine();
        sys.updateGfx();
    }
    dialog.wait();
}

void Dialog_init(void){
    dialog.wait     = Dialog_wait;
    dialog.nextLine = Dialog_nextLine;
    dialog.print    = Dialog_print;
    dialog.clear    = Dialog_clear;

    dialog.x        = 0;
    dialog.y        = 0;
    dialog.w        = 2;
    dialog.h        = 2;
    dialog.size.x   = 20;
    dialog.size.y   = 5;
}
