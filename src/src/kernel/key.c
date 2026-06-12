#include <genesis.h>
#include "key.h"

Key key;

bool Key_press( int key_flag ){
    key.poll();
    return ( key.status & key_flag );
}

void Key_wait( int key_flag ){
    key.poll();
    while(! (key.status & key_flag) ){
        key.poll();
    };
}

bool Key_noinput( void ){
    key.poll();
    return key.status==0;
}

void Key_poll(void){
    key.status = JOY_readJoypad( JOY_1 );
}

void Key_init(void){

    key.wait   = Key_wait;
    key.press  = Key_press;
    key.poll   = Key_poll;
    key.noinput= Key_noinput;

    key.status = 0;
}
