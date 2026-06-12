#include <genesis.h>
#include "kernel/gpu.h"
#include "kernel/dialog.h"
#include "kernel/key.h"
#include "kernel/sys.h"
#include "kernel/pokebattle.h"
#include "kernel/automap.h"

void setup(){
    gpu         .init = Gpu_init; 
    dialog      .init = Dialog_init;
    key         .init = Key_init;
    sys         .init = Sys_init;
    pokebattle  .init = Pokebattle_init;
    automap     .init = Automap_init;
}

static void vblank();

void loop(){

    SYS_setVBlankCallback(vblank);

    while( 1 ){
        //CAMERA_centerOn(fix32ToInt(posX), fix32ToInt(posY));
        pokebattle.run();
        automap.redraw = true;
        automap.update();
        //while(1){}
        gpu.print       (10, 10, "aaa bbb ccc 12340 !-$%&'()*+,-./<=>?#~[\\]^_");
        gpu.bigText     ( 0, 0, "abcdefghijklmnopqrstuvwxyz", 3);
        gpu.bigText     ( 0,29, "0123456789?!", 2);
        gpu.bigText     (13,29, "0123456789?!", 1);
        gpu.bigText     (26,29, "0123456789?!", 0);
        dialog.print    ( 2, 2, 35, 23, "Preparing System >\n.\n..\n...\n....\n.....\n......\n.\n..\n...\n....\n.....\n......\nOk.\nSystem Ready.\n");
        dialog.print    ( 10, 0, 20, 5, "Hola Diego.\nSi puedes leer esto significa que logre hacer funcionar mi caja de mensajes en una Mega Drive.\n\n\nAhora lo que sigue es una buena story que contar, porque un metroidvania va a ser, tiene que\nseguir los pasos de SOTN, pero en un\nambiente distopico y diferenciarse de Life On Mars.");
        SPR_update();
        SYS_doVBlankProcess();
    }
}

void main(bool hard){
    setup();
    sys         .init();
    gpu         .init();
    dialog      .init();
    key         .init();
    pokebattle  .init();
    automap     .init();
    loop();
}


static void vblank(){
    // handle vblank stuff
    //LEVEL_onVBlank();
}