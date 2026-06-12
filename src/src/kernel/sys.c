#include <genesis.h>
#include "sys.h"
#include "key.h"

Sys sys;

void Sys_updateGfx(void) {
    SPR_update();
    SYS_doVBlankProcess();
}

void Sys_update(void) {
    sys.updateGfx();
    key.poll();
}

void Sys_init(){
    sys.update      = Sys_update;
    sys.updateGfx   = Sys_updateGfx;
}