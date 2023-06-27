#ifndef LEVELS_H   /* Include guard */
#define LEVELS_H
#include <genesis.h>
#include <resources.h>

typedef struct {
    Sprite *eSprite;
    //sprites usually only move on x axis apart from Eugene so including Y for him
    u16 xStart;
    u16 xEnd;
    u16 yStart;
    u16 yEnd;
} Enemy;
u8 currentLevel;
typedef struct {
    Image *lvBG_B; //main ground which has no animation
    u16 numOfEnemy;
    Enemy *lvEnemy;
    u8 levelMap[17][32]; //20 levels each 16 x 32 tiles (8x8 tiles)
    Sprite *lvSprites[8]; //animated tiles
} levelData;

#endif