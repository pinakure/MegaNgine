#ifndef GPU_H
#define GPU_H

#include <genesis.h>

#define ALPHA_4x8_UPPER     0xB0 // ABCDEF...
#define ALPHA_4x8_LOWER     0x90 // abcdef...
#define ALPHA_4x8_BRACKET   0xCA // [\]
#define ALPHA_4x8_HASH      0xAA // #
#define ALPHA_4x8_TILDE     0xAD // ~
#define ALPHA_4x8_GRAVE     0xCD // ^
#define ALPHA_4x8_LODASH    0xCE // _
#define ALPHA_4x8_EXCLAM    0x70 // !-$%&/()*+,-./<=>?
#define ALPHA_4x8_DIGITS    0x7F // 0123456789
#define ALPHA_4x8_OFFSET    0x60

#define BIGFONT_OFFSET      0x12F
#define BIGFONT_A           0x0000100A
#define BIGFONT_B           0x00011003
#define BIGFONT_C           0x00021002
#define BIGFONT_D           0x00031003
#define BIGFONT_E           0x00040011
#define BIGFONT_F           0x00041009
#define BIGFONT_G           0x00020012
#define BIGFONT_H           0x000A1005
#define BIGFONT_I           0x00061006
#define BIGFONT_J           0x00070013
#define BIGFONT_K           0x00081008
#define BIGFONT_L           0x00090011
#define BIGFONT_M           0x000A100D
#define BIGFONT_N           0x000B180B
#define BIGFONT_O           0x00001000
#define BIGFONT_P           0x00030014
#define BIGFONT_Q           0x00000015
#define BIGFONT_R           0x00030016
#define BIGFONT_S           0x00020017
#define BIGFONT_T           0x000C1006
#define BIGFONT_U           0x00051000
#define BIGFONT_V           0x00050019
#define BIGFONT_W           0x000D100A
#define BIGFONT_X           0x000E100E
#define BIGFONT_Y           0x000E1006
#define BIGFONT_Z           0x000F180F
#define BIGFONT_0           0x00181818
#define BIGFONT_1           0x001B1006
#define BIGFONT_2           0x0010180F
#define BIGFONT_3           0x00101010
#define BIGFONT_4           0x00050814
#define BIGFONT_5           0x001C0017
#define BIGFONT_6           0x001D001E
#define BIGFONT_7           0x000F1006
#define BIGFONT_8           0x001F1000
#define BIGFONT_9           0x181E181D
#define BIGFONT_QUESTION    0x0010001A
#define BIGFONT_EXCLAM      0x1006001A
#define BIGFONT_DOT         0xFFFF0020
#define BIGFONT_COMMA       0xFFFF0021
#define BIGFONT_COLON       0x00200020
#define BIGFONT_SEMICOLON   0x00200021

typedef struct sGpu {
    int palette; 
    void(*init      )(void);
    void(*print     )(int, int, const char*); // Use only on WINDOW, it uses both BG planes to render 4x8 characters    
    void(*bigText   )(int, int, const char*, int); 
    void(*fill      )(int, int); 
}Gpu;

extern Gpu gpu;
extern void Gpu_init(void);
#endif
