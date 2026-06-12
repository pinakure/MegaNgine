#ifndef CREATURE_H
#define CREATURE_H

#include "stat.h"

typedef struct sCreature {
    bool            male;
    int             level;
    Stat            hp;
    Stat            exp;
    Stat            strength;
    Stat            defense;
    Stat            speed;
    Stat            luck;
    Stat            sp[4];
    unsigned int    attack[4];
}Creature;

#endif
