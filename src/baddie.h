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
    s8 moveIncrement; //determines both which direction to go and speed of movement
    bool facingLeft; //all sprites face right, so need horizonal flip if facing left
} Enemy;

typedef struct {
    u8 numOfBaddies;
    Enemy Baddies[];
} LvBaddies;

//leave x and y positions as 0 as the start and end values all need to 
//be updated with the offset values so might as well set positions then
LvBaddies lv1Baddies = {1, {NULL, &lv1BdS, 64, 120, 56, 56, 0, 0, -1, FALSE}};
LvBaddies lv2Baddies = {2, {{NULL, &lv2BdS, 97, 232, 104, 104, 0, 0, -1, FALSE}, 
                            {NULL, &lv2BdS, 8, 144, 24, 24, 0, 0, -1, FALSE}}};
LvBaddies lv3Baddies = {3, {{NULL, &lv3BdS, 8, 152, 104, 104, 0, 0, -1, FALSE}, 
                            {NULL, &lv3BdS, 8, 128, 24, 24, 0, 0, -1, FALSE},
                            {NULL, &lv3BdS, 144, 232, 24, 24, 0, 0, -1, FALSE}}};
LvBaddies lv4Baddies = {2, {{NULL, &lv4BdS, 8, 80, 104, 104, 0, 0, -1, FALSE},
                            {NULL, &lv4BdS, 48, 128 , 104, 104, 0, -1, FALSE}}};
LvBaddies lv5Baddies = {3, {{NULL, &lv5BdS, 8, 96, 24, 24, 0, 0, -1, FALSE},
                            {NULL, &lv5BdS, 32, 96, 56, 56, 0, 0, -1, FALSE},
                            {NULL, &lv5BdS2, 120, 120, 0, 88, 0, 0, -1, FALSE}}};
LvBaddies lv6Baddies = {4, {{NULL, &lv6BdS, 48, 112, 64, 64, 0, 0, -1, FALSE},
                            {NULL, &lv6BdS, 112, 168, 64, 64, 0, 0, -1, FALSE},
                            {NULL, &lv6BdS, 56, 160, 104, 104, 0, 0, -1, FALSE},
                            {NULL, &lv6BdS, 192, 232, 104, 104, 0, 0, -1, FALSE}}};
LvBaddies lv7Baddies = {3, {{NULL, &lv7BdS, 16, 80, 64, 64, 0, 0, -1, FALSE},
                            {NULL, &lv7BdS, 120, 232, 8, 8, 0, 0, -1, FALSE},
                            {NULL, &lv7BdS, 136, 232, 104, 104, 0, 0, -1, FALSE}}};
LvBaddies lv8Baddies = {4, {{NULL, &lv8BdS, 8, 72, 104, 104, 0, 0, -1, FALSE},
                            {NULL, &lv8BdS, 88, 120, 88, 88, 0, 0, -1, FALSE},
                            {NULL, &lv8BdS, 144, 168, 56, 56, 0, 0, -1, FALSE},
                            {NULL, &lv8BdS2, 120, 120, 0, 0, 0, 0, -1, FALSE}}};
LvBaddies lv9Baddies = {6, {{NULL, &lv9BdS, 96, 144, 80, 80, 0, 0, -1, FALSE},
                            {NULL, &lv9BdS, 96, 144, 24, 24, 0, 0, -1, FALSE},
                            {NULL, &lv9BdS2, 40, 40, 0, 104, 0, 0, -1, FALSE},
                            {NULL, &lv9BdS2, 80, 80, 0, 104, 0, 0, -1, FALSE},
                            {NULL, &lv9BdS2, 160, 160, 0, 104, 0, 0, -1, FALSE},
                            {NULL, &lv9BdS2, 200, 200, 0, 104, 0, 0, -1, FALSE}}};
LvBaddies lv10Baddies = {4, {{NULL, &lv10BdS, 32, 208, 104, 104, 0, 0, -1, FALSE},
                            {NULL, &lv10BdS, 64, 112, 80, 80, 0, 0, -1, FALSE},
                            {NULL, &lv10BdS, 72, 112, 56, 56, 0, 0, -1, FALSE},
                            {NULL, &lv10BdS, 136, 168, 40, 40, 0, 0, -1, FALSE}}};
LvBaddies lv11Baddies = {7, {{NULL, &lv11BdS, 24, 24, 32, 104, 0, 0, -1, FALSE},
                            {NULL, &lv11BdS, 96, 96, 0, 48, 0, 0, -1, FALSE},
                            {NULL, &lv11BdS, 168, 168, 48, 104, 0, 0, -1, FALSE},
                            {NULL, &lv11BdS, 208, 208, 0, 104, 0, 0, -1, FALSE},
                            {NULL, &lv11BdS2, 40, 152, 104, 104, 0, 0, -1, FALSE},
                            {NULL, &lv11BdS2, 112, 144, 48, 48, 0, 0, -1, FALSE},
                            {NULL, &lv11BdS2, 120, 107, 24, 24, 0, 0, -1, FALSE}}};
LvBaddies lv12Baddies = {4, {{NULL, &lv12BdS, 8, 72, 104, 104, 0, 0, -1, FALSE},
                            {NULL, &lv12BdS, 88, 122, 88, 88, 0, 0, -1, FALSE},
                            {NULL, &lv12BdS, 200, 224, 48, 48, 0, 0, -1, FALSE},
                            {NULL, &lv12BdS2, 120, 120, 0, 0, 0, 0, -1, FALSE}}};
LvBaddies lv13Baddies = {5, {{NULL, &lv13BdS, 8, 232, 8, 8, 0, 0, -1, FALSE},
                            {NULL, &lv13BdS, 8, 232, 32, 32, 0, 0, -1, FALSE},
                            {NULL, &lv13BdS, 8, 232, 56, 56, 0, 0, -1, FALSE},
                            {NULL, &lv13BdS, 8, 232, 80, 80, 0, 0, -1, FALSE},
                            {NULL, &lv13BdS2, 40, 40, 8, 104, 0, 0, -1, FALSE}}};
//level 14 baddies have a falling pattern so need to work it out
LvBaddies lv14Baddies = {0, {NULL, &lv13BdS, 0, 0, 0, 0, 0, 0, -1, FALSE}};
LvBaddies lv15Baddies = {3, {{NULL, &lv15BdS, 80, 80, 32, 104, 0, 0, -1, FALSE},
                            {NULL, &lv15BdS, 128, 128, 32, 104, 0, 0, -1, FALSE},
                            {NULL, &lv15BdS,168, 168, 32, 104,0 ,0, -1, FALSE}}};
LvBaddies lv16Baddies = {4, {{NULL, &lv16BdS, 8, 168, 104, 104, 0, 0, -1, FALSE},
                            {NULL, &lv16BdS, 8, 64, 80, 80, 0, 0, -1, FALSE},
                            {NULL, &lv16BdS, 144, 184, 56, 56, 0, 0, -1, FALSE},
                            {NULL, &lv16BdS, 200, 232, 40, 40, 0, 0, -1, FALSE}}};
LvBaddies lv17Baddies = {6, {{NULL, &lv17BdS, 40, 64, 104, 104, 0, 0, -1, FALSE},
                            {NULL, &lv17BdS, 96, 200, 104, 104, 0, 0, -1, FALSE},
                            {NULL, &lv17BdS2, 24, 24, 64, 104, 0, 0, -1, FALSE},
                            {NULL, &lv17BdS2, 80, 80, 0, 104, 0, 0, -1, FALSE},
                            {NULL, &lv17BdS2, 152, 152, 0, 64, 0, 0, -1, FALSE},
                            {NULL, &lv17BdS2, 216, 216, 0, 96, 0, 0, -1, FALSE}}};
LvBaddies lv18Baddies = {8, {{NULL, &lv18BdS, 94, 144, 24, 24, 0, 0, -1, FALSE},
                            {NULL, &lv18BdS, 94, 136, 48, 48, 0, 0, -1, FALSE},
                            {NULL, &lv18BdS, 94, 136, 80, 80, 0, 0, -1, FALSE},
                            {NULL, &lv18BdS, 94, 159, 104, 104, 0, 0, -1, FALSE},
                            {NULL, &lv18BdS2, 40, 40, 0, 104, 0, 0, -1, FALSE},
                            {NULL, &lv18BdS2, 80, 80, 0, 104, 0, 0, -1, FALSE},
                            {NULL, &lv18BdS2, 160, 160, 0, 104, 0, 0, -1, FALSE},
                            {NULL, &lv18BdS2, 200, 200, 0, 104, 0, 0, -1, FALSE}}};
LvBaddies lv19Baddies = {7, {{NULL, &lv19BdS, 184, 232, 24, 24, 0, 0, -1, FALSE},
                            {NULL, &lv19BdS, 175, 232, 48, 48, 0, 0, -1, FALSE},
                            {NULL, &lv19BdS, 184, 232, 72, 72, 0, 0, -1, FALSE},
                            {NULL, &lv19BdS, 96, 232, 104, 104, 0, 0, -1, FALSE},
                            {NULL, &lv19BdS2, 40, 40, 0, 104, 0, 0, -1, FALSE},
                            {NULL, &lv19BdS2, 88, 88, 48, 104, 0, 0, -1, FALSE},
                            {NULL, &lv19BdS2, 128, 128, 0, 80, 0, 0, -1, FALSE}}};
LvBaddies lv20Baddies = {2, {{NULL, &lv20BdS, 56, 174, 104, 104, 0, 0, -1, FALSE},
                            {NULL, &lv20BdS2, 192, 192, 40, 104, 0, 0, -1, FALSE}}};
LvBaddies *allLvBaddies[] = {&lv1Baddies, &lv2Baddies, &lv3Baddies, &lv4Baddies, &lv5Baddies, &lv6Baddies, &lv7Baddies,
                            &lv8Baddies, &lv9Baddies, &lv10Baddies, &lv11Baddies, &lv12Baddies, &lv13Baddies, &lv14Baddies,
                            &lv15Baddies, &lv16Baddies, &lv17Baddies, &lv18Baddies, &lv19Baddies, &lv20Baddies};


#endif