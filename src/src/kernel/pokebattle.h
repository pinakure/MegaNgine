#ifndef POKEBATTLE_H
#define POKEBATTLE_H

#include "creature.h"

#define UI_CORNER_HI        0x6151
#define UI_HORIZONTAL       0x6152
#define UI_TEE              0x6153
#define UI_CORNER_LO        0x6154
#define UI_VERTICAL         0x6155
#define UI_TEE_ROTATE       0x6156
#define UI_CROSS            0x6157
#define UI_S                0x6158
#define UI_H                0x6159
#define UI_P                0x615A
#define UI_VOL              0x615B
#define UI_CORNER_BOLD_A    0x615C
#define UI_CORNER_BOLD_B    0x615D
#define UI_CORNER_ALT       0x615E
#define UI_VERTICAL_SOLID   0x615F
#define UI_APPEND           0x6160
#define UI_BAR_PLACEHOLDER  0x6161
#define UI_MALE             0x6162
#define UI_FEMALE           0x6163
#define UI_LEVEL            0x6164
#define UI_SLASH            0x6165
#define UI_CURSOR           0x6166
#define UI_BAR              0x167

typedef struct sPokebattle {
    
    Creature    foe;
    Creature    hero;
   
    void    (*init      )(void);
    void    (*print     )(int, int, const char*);
    void    (*number    )(int, int, int);
    void    (*run       )(void);


}PokeBattle;

extern PokeBattle pokebattle;
extern void Pokebattle_init(void);
#endif
