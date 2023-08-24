#ifndef BADDIE_H   /* Include guard */
#define BADDIE_H
#include <genesis.h>
#include <resources.h>

typedef struct {
    Sprite *eSprite;
    const SpriteDefinition *bdSpriteDef; //from resources.h
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

typedef struct {
    u8 numOfBaddies;
    Enemy Baddies[];
} LvBaddies;

//leave x and y positions as 0 as the start and end values all need to 
//be updated with the offset values so might as well set positions then
LvBaddies lv1Baddies = {1, {NULL, &lv1BdS, 64, 135, 56, 56, 0, 0, 1, FALSE}};
LvBaddies lv2Baddies = {2, {{NULL, &lv2BdS, 97, 247, 104, 104, 0, 0, 1, FALSE}, 
                            {NULL, &lv2BdS, 8, 159, 24, 24, 0, 0, 1, FALSE}}};
LvBaddies lv3Baddies = {3, {{NULL, &lv3BdS, 8, 167, 104, 104, 0, 0, 1, FALSE}, 
                            {NULL, &lv3BdS, 8, 143, 24, 24, 0, 0, 1, FALSE},
                            {NULL, &lv3BdS, 144, 247, 24, 24, 0, 0, 1, FALSE}}};
LvBaddies *allLvBaddies[] = {&lv1Baddies, &lv2Baddies, &lv3Baddies};
/*
lv2BdS, 97, 247, 104, 104
lv2BdS, 8, 159, 24, 24

lv3BdS, 8, 167 , 104, 104
lv3BdS, 8, 143, 24, 24
lv3BdS, 144, 247, 24, 24*/

#endif