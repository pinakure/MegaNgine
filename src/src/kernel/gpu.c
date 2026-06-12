#include "gpu.h"
#include "gfx.h"
#include "sprite.h"
#include "dma.h"

const unsigned int big_font[] = {
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_A        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_B        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_C        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_D        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_E        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_F        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_G        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_H        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_I        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_J        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_K        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_L        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_M        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_N        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_O        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_P        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_Q        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_R        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_S        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_T        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_U        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_V        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_W        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_X        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_Y        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_Z        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_0        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_1        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_2        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_3        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_4        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_5        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_6        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_7        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_8        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_9        ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_QUESTION ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_EXCLAM   ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_DOT      ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_COMMA    ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_COLON    ,
    ((BIGFONT_OFFSET<<16)|BIGFONT_OFFSET)+BIGFONT_SEMICOLON,  
};

void Gpu_print(int x, int y, const char *text){
    for( int i=0, li=i+strlen(text); i<li; i++ ){
        int c = text[i];
        if( c == ' ') c = 0;
        else {
                 if( ( c >= '0' ) && ( c <= '9' ) ) c = (ALPHA_4x8_DIGITS   + c ) - '0' ;
            else if( ( c == '#' )                 ) c = ALPHA_4x8_HASH                  ;
            else if( ( c == '~' )                 ) c = ALPHA_4x8_TILDE                 ;
            else if( ( c == '^' )                 ) c = ALPHA_4x8_GRAVE                 ;
            else if( ( c == '_' )                 ) c = ALPHA_4x8_LODASH                ;
            else if( ( c >= 'A' ) && ( c <= 'Z' ) ) c = ( ALPHA_4x8_UPPER   + c ) - 'A' ;
            else if( ( c >= 'a' ) && ( c <= 'z' ) ) c = ( ALPHA_4x8_LOWER   + c ) - 'a' ;
            else if( ( c >= '[' ) && ( c <= ']' ) ) c = ( ALPHA_4x8_BRACKET + c ) - '[' ;
            else                                    c = ( ALPHA_4x8_EXCLAM  + c ) - '!' ;
            // Alternate back and forth between left and right scrolled versions of the character
            if(( x & 1 ) == 1 ) c += ALPHA_4x8_OFFSET;
        }
        VDP_setTileMapXY(((x&1)==0)?BG_A:BG_B, gpu.palette | c, x>>1, y);
        x++;
    }
}

void Gpu_bigText( int x, int y, const char *text, int palette){
    y<<=1;
    palette = palette<<13;
    for( int i=0, li=i+strlen(text); i<li; i++ ){
        int c = text[i];
        if( c == ' ' ){
            VDP_setTileMapXY(BG_A, 0x0000, x, y+0);
            VDP_setTileMapXY(BG_A, 0x0000, x, y+1);
        } else {
                 if( ( c >= '0' )&&( c <= '9' ) ) c = (c-'0') + 26   ;// sum 26 to skip alphabetic chars
            else if( ( c >= 'a' )&&( c <= 'z' ) ) c = (c-'a')        ;
            else if(   c == '?'                 ) c = BIGFONT_QUESTION;
            else if(   c == '!'                 ) c = BIGFONT_EXCLAM;
            else if(   c == '.'                 ) c = BIGFONT_DOT;
            else if(   c == ','                 ) c = BIGFONT_COMMA;
            else if(   c == ':'                 ) c = BIGFONT_COLON;
            else if(   c == ';'                 ) c = BIGFONT_SEMICOLON;
            else                                  c = BIGFONT_QUESTION;
            unsigned int val = big_font[c];
            VDP_setTileMapXY(BG_A, palette | ( val >> 16    ), x, y     );
            VDP_setTileMapXY(BG_A, palette | ( val & 0xFFFF ), x, y + 1 );
        }
        x++;
    }
}

void Gpu_fill(int plane, int value){
    for(int y=0; y<30; y++){
        for(int x=0; x<40; x++){
            VDP_setTileMapXY(plane ? BG_A : BG_B, value, x, y);
        }
    }
}

void Gpu_init(){

    gpu.palette = 0x6000;

    gpu.fill    = Gpu_fill;
    gpu.print   = Gpu_print;
    gpu.bigText = Gpu_bigText;

    VDP_setScreenWidth320();
    //SYS_showFrameLoad(TRUE);
    VDP_loadTileSet(&bga_tileset, TILE_USERINDEX, DMA);
    
    //! This:
    VDP_setPaletteColors(0, palette_all.data, 64);
    //! is equivalent to this:
    // VDP_setPalette(0, palette_all.data);
    // VDP_setPalette(1, palette_all.data+16);
    // VDP_setPalette(2, palette_all.data+32);
    // VDP_setPalette(3, palette_all.data+48);
}

Gpu gpu;