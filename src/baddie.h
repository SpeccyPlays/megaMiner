#ifndef BADDIE_H   /* Include guard */
#define BADDIE_H
#include <genesis.h>
#include <resources.h>

typedef struct {
    Sprite *eSprite;
    //sprites usually only move on x axis apart from Eugene so including Y for him
    u16 xStart;
    u16 xEnd;
    u16 yStart;
    u16 yEnd;
    u16 xPos;
    u16 yPos;
    s8 moveIncrement; //will either be 1 or -1
    bool facingLeft; //all sprites face right, so need horizonal flip if facing left
} Enemy;
/*
lv2BdS, 97, 247, 104, 104
lv2BdS, 8, 159, 24, 24

lv3BdS, 8, 167 , 104, 104
lv3BdS, 8, 143, 24, 24
lv3BdS, 144, 247, 24, 24*/

#endif