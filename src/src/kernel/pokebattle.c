#include <genesis.h>
#include "pokebattle.h"
#include "gpu.h"
#include "sys.h"
#include "key.h"

PokeBattle pokebattle;


// #define UI_CORNER_HI        0x151
// #define UI_HORIZONTAL       0x152
// #define UI_TEE              0x153
// #define UI_CORNER_LO        0x154
// #define UI_VERTICAL         0x155
// #define UI_TEE_ROTATE       0x156
// #define UI_CROSS            0x157
// #define UI_S                0x158
// #define UI_H                0x159
// #define UI_P                0x15A
// #define UI_VOL              0x15B
// #define UI_CORNER_BOLD_A    0x15C
// #define UI_CORNER_BOLD_B    0x15D
// #define UI_CORNER_ALT       0x15E
// #define UI_VERTICAL_SOLID   0x15F
// #define UI_APPEND           0x160
// #define UI_BAR_PLACEHOLDER  0x161
// #define UI_MALE             0x162
// #define UI_FEMALE           0x163
// #define UI_LEVEL            0x164
// #define UI_SLASH            0x165
// #define UI_CURSOR           0x166
// #define UI_BAR              0x167

#define X       10
#define W       20
#define Y        4
#define H       20

void Pokebattle_number(int x, int y, int number){
    if( number / 100) {
        VDP_setTileMapXY(BG_B, 0x6000 | (0x1B9 + ((number/100)%10)), X+x, Y+y);
        x++;
    }
    if( number / 10) {
        VDP_setTileMapXY(BG_B, 0x6000 | (0x1B9 + ((number/10)%10)), X+x, Y+y);
        x++;
    }
    VDP_setTileMapXY(BG_B, 0x6000 | (0x1B9 + (number%10)), X+x, Y+y);
}


void Pokebattle_print(int x, int y, const char *text){
    for( int i=0, li=i+strlen(text); i<li; i++ ){
        int c = text[i];
        if( c == ' ') c = 0xC;
        else {
            if(c == '\n' ) continue;
                 if( ( c == '#' )                 ) c = 0x27F;
            else if( ( c == '?' )                 ) c = 0x220;
            else if( ( c == '!' )                 ) c = 0x21F;
            else if( ( c == '&' )                 ) c = 0x281;
            else if( ( c == '^' )                 ) c = 0x1282;
            else if( ( c == ',' )                 ) c = 0x280;
            else if( ( c == ';' )                 ) c = 0x221;
            else if( ( c == '.' )                 ) c = 0x222;
            else if( ( c >= '0' ) && ( c <= '9' ) ) c = ( 0x1B9     + c ) - '0';
            else if( ( c >= 'A' ) && ( c <= 'J' ) ) c = ( 0x1D9     + c ) - 'A';
            else if( ( c >= 'K' ) && ( c <= 'T' ) ) c = ( 0x1F9     + c ) - 'K';
            else if( ( c >= 'U' ) && ( c <= 'Z' ) ) c = ( 0x219     + c ) - 'U';
            else if( ( c >= 'a' ) && ( c <= 'j' ) ) c = ( 0x239     + c ) - 'a';
            else if( ( c >= 'k' ) && ( c <= 't' ) ) c = ( 0x259     + c ) - 'k';
            else if( ( c >= 'u' ) && ( c <= 'z' ) ) c = ( 0x279     + c ) - 'u';
            else                                    c = 0x220;
        }
        VDP_setTileMapXY(BG_B, 0x6000 | c, X+x, Y+y);
        x++;
    }
}

static inline void drawMessagePanel(int x, int y, int w, int h){
    // Main Dialog pane
    VDP_setTileMapXY( BG_B, UI_CORNER_HI            , x     , y     );
    VDP_setTileMapXY( BG_B, 0x0800 | UI_CORNER_HI   , x+w-1 , y     );
    VDP_setTileMapXY( BG_B, UI_CORNER_LO            , x     , y+h-1 );
    VDP_setTileMapXY( BG_B, 0x0800 | UI_CORNER_LO   , x+w-1 , y+h-1 );
    for( int iy=1; iy < h-1; iy++ ){
        VDP_setTileMapXY( BG_B, UI_VERTICAL         , x     , y+iy  );
        VDP_setTileMapXY( BG_B, 0x0800 | UI_VERTICAL, x+w-1 , y+iy  );
    }
    for( int ix=1; ix < w-1; ix++ ){
        VDP_setTileMapXY( BG_B, UI_HORIZONTAL       , x+ix  , y     );
        VDP_setTileMapXY( BG_B, UI_HORIZONTAL       , x+ix  , y+h-1 );
    }

    for( int iy = 1; iy<h-2; iy++ ){
        for( int ix = 1; ix<w-2; ix++ ){
            // clear
        }
    }
}
static inline void drawExpGauge( int x, int y, Stat *stat){
    // int count = (int)((((double)stat->value) / ((double)stat->max))*((double)72));
    int count = (stat->value*72) / stat->max;
    for(int i=0; i<8 ; i++){
        if (i<(count>>3 /*   /8  */ )){
            if(i<(count>>3 /*   /8  */ )-1)
                VDP_setTileMapXY( BG_A, 0x6000|(UI_BAR+0x20+7) , x+8-i, y );
            else 
                VDP_setTileMapXY( BG_A, 0x6000|(UI_BAR+0x20+(count&7)) , x+8-i, y );
        } else VDP_setTileMapXY( BG_A, 0x6000, x+8-i, y );
    }
}

static inline void drawGauge( int x, int y, Stat *stat){
    // for(int i=0; i<6; i++){
    //     VDP_setTileMapXY( BG_A, 0x6000|(UI_BAR+7)      , x + i, y );
    // }

     // int count = (int)((((double)stat->value) / ((double)stat->max))*((double)72));
    int count = (stat->value*56) / stat->max;
    int dac   = ((count>>3) < 2) ? 0x0000 : ((count>>3) <= 4) ? 0x6000 : 0x2000;
    for(int i=0; i<6 ; i++){
        if (i<(count>>3 /*   /8  */ )){
            if(i<(count>>3 /*   /8  */ )-1)
                VDP_setTileMapXY( BG_A, dac | ( UI_BAR + 7 ) , x+i, y );
            else 
                VDP_setTileMapXY( BG_A, dac | ( UI_BAR + (count & 7) ) , x+i, y );
        } else 
                VDP_setTileMapXY( BG_A, 0, x+i, y );
    }
}

static inline void drawFoePanel( int x, int y, Creature *foe){
    // Print level and gender

    
    VDP_setTileMapXY( BG_B, UI_LEVEL , x + 5  , y + 1 );
    pokebattle.print (   1   ,  0    , "Foe Name"    );
    pokebattle.number(   7   ,  1    , foe->level    );
    VDP_setTileMapXY( BG_B, foe->male ? UI_MALE : UI_FEMALE , x + 8, y+1 );

    VDP_setTileMapXY( BG_B, UI_VERTICAL_SOLID   , X + 1, Y+2 );
    VDP_setTileMapXY( BG_B, UI_H                , X + 2, Y+2 );
    VDP_setTileMapXY( BG_B, UI_P                , X + 3, Y+2 );
    VDP_setTileMapXY( BG_B, UI_CORNER_ALT       , X + 1, Y+3 );
    VDP_setTileMapXY( BG_B, UI_BAR_PLACEHOLDER  , X + 2, Y+3 );
    VDP_setTileMapXY( BG_B, UI_BAR_PLACEHOLDER  , X + 3, Y+3 );
    for(int i=0; i<6; i++){
        VDP_setTileMapXY( BG_B, UI_BAR_PLACEHOLDER  , i + X +  4 , Y +  2 );
        VDP_setTileMapXY( BG_B, UI_BAR_PLACEHOLDER  , i + X +  4 , Y +  3 );
    }
    VDP_setTileMapXY( BG_B, UI_APPEND           , X + 10, Y+2 );
    VDP_setTileMapXY( BG_B, 0x0800 | UI_VOL     , X + 10, Y+3 );
    
}

inline void drawHeroPanel(int x, int y, Creature *hero ){
    for(int i=0; i<6; i++){
        VDP_setTileMapXY( BG_B, UI_BAR_PLACEHOLDER  , i + X + 12 , Y + 10 );
        VDP_setTileMapXY( BG_B, UI_BAR_PLACEHOLDER  , i + X + 12 , Y + 12 );
    }
    
    // Draw ally pane 
    pokebattle.print    (   10   ,  8       , "Hero Name"    );
    VDP_setTileMapXY    ( BG_B, UI_LEVEL    , X + 14  , Y+9  );
    pokebattle.number   (   15   ,  9       , hero->level    );
    pokebattle.number   (   11   ,  11      , hero->hp.value);
    pokebattle.print    (   14   ,  11      , "/"           );
    pokebattle.number   (   15   ,  11      , hero->hp.max  );
    VDP_setTileMapXY( BG_B, pokebattle.hero.male ? UI_MALE : UI_FEMALE  , X + 17, Y +  9 );
    VDP_setTileMapXY( BG_B, UI_H                                        , X + 10, Y + 10 );
    VDP_setTileMapXY( BG_B, UI_P                                        , X + 11, Y + 10 );
    VDP_setTileMapXY( BG_B, UI_CORNER_BOLD_A                            , X + 18, Y + 10 );
    VDP_setTileMapXY( BG_B, 0x0800 | UI_VERTICAL_SOLID                  , X + 18, Y + 11 );
    VDP_setTileMapXY( BG_B, 0x1000 | UI_CORNER_BOLD_A                   , X + 18, Y + 12 );
    VDP_setTileMapXY( BG_B, UI_VOL                                      , X +  9, Y + 12 );
    VDP_setTileMapXY( BG_B, UI_BAR_PLACEHOLDER                          , X + 10, Y + 12 );
    VDP_setTileMapXY( BG_B, UI_BAR_PLACEHOLDER                          , X + 11, Y + 12 );
}

void Pokebattle_run(void){
    gpu.fill( 0, 0x600C);
    gpu.fill( 1, 0);
    gpu.palette     = 0;
    Creature *hero  = &pokebattle.hero;
    Creature *foe   = &pokebattle.foe;
    drawMessagePanel    ( X     , Y+H-7 , W                     , 6 );
    drawFoePanel        ( X+1   , Y     , foe                       );
    drawHeroPanel       ( X+1   , Y     , hero                      );
        
    // Draw 'creature' glitched gfx's
    for(int y=0; y<8;y++){
        for(int x=0; x<8;x++){
            VDP_setTileMapXY( BG_B, (( (x+y)+(x*y) + (x*(x+y)) + y*(y-x) ) & 0x1f)+0x200, X + 11 + x, Y + y     );
            VDP_setTileMapXY( BG_B, (( (x+y)+(x*y) + (x*(x+y)) + y*(y-x) ) & 0x1f)+0x200, X +  1 + x, Y + y + 5 );
        }
    }

    
    // Draw bars
    
    while(!key.press( BUTTON_A )){
        drawGauge   ( X +  4, Y +  2, &foe->hp   );
        drawGauge   ( X + 12, Y + 10, &hero->hp  );
        drawExpGauge( X +  9, Y + 12, &hero->exp );
        hero->exp.value++;
        hero->exp.value &=0x7F;
        hero->hp.value++;
        hero->hp.value &=0xFF;
        foe->hp.value++;
        foe->hp.value &=0x7F;
        sys.update();
    }
    while(!key.noinput()){ sys.updateGfx(); }

}

void Pokebattle_init(void){
    pokebattle.run      = Pokebattle_run;
    pokebattle.print    = Pokebattle_print;
    pokebattle.number   = Pokebattle_number;

    Creature *hero  = &pokebattle.hero;
    Creature *foe   = &pokebattle.foe;
    foe ->level     = 10;
    hero->level     = 10;
    foe->hp.value   = 0;
    foe->hp.max     = 0x80;
    hero->hp.value  = 0;
    hero->hp.max    = 0x100;
    hero->exp.value = 0;
    hero->exp.max   = 0x80;
}