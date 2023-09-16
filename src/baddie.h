#ifndef BADDIE_H   /* Include guard */
#define BADDIE_H
#include <genesis.h>
#include <resources.h>
#include "globalstruct.h"

typedef struct {
    Sprite *eSprite;
    const SpriteDefinition *bdSpriteDef; //from resources.h
    u16 xStart;
    u16 xEnd;
    u16 yStart;
    u16 yEnd;
    u16 xPos;
    u16 yPos;
    s8 moveIncrement; //determines both which direction to go and speed of movement
    bool facingLeft; //all sprites face right, so need horizonal flip if facing left
    bool yMove; //false if baddie moves on x axis, true if not
    u16 xLvStart;
    u16 yLvStart;
} Enemy;

typedef struct {
    u8 numOfBaddies;
    Enemy Baddies[];
} LvBaddies;

//leave x and y positions as 0 as the start and end values all need to 
//be updated with the offset values so might as well set positions then
LvBaddies lv1Baddies = {1, {{NULL, &lv1BdS, 64, 120, 56, 56, 0, 0, -1, TRUE, FALSE, 96, 56}}};

LvBaddies lv2Baddies = {2, {{NULL, &lv2BdS, 97, 232, 104, 104, 0, 0, -1, TRUE, FALSE, 176, 104}, 
                            {NULL, &lv2BdS, 8, 144, 24, 24, 0, 0, -1, TRUE, FALSE, 88, 24}}};

LvBaddies lv3Baddies = {3, {{NULL, &lv3BdS, 8, 152, 104, 104, 0, 0, -1, TRUE, FALSE, 144, 104}, 
                            {NULL, &lv3BdS, 8, 128, 24, 24, 0, 0, -1, TRUE, FALSE, 120, 24},
                            {NULL, &lv3BdS, 144, 232, 24, 24, 0, 0, 1, FALSE, FALSE, 152, 24}}};

LvBaddies lv4Baddies = {2, {{NULL, &lv4BdS, 8, 80, 104, 104, 0, 0, -1, TRUE, FALSE, 72, 104},
                            {NULL, &lv4BdS, 48, 128, 104, 104, 0, 0, -1, TRUE, FALSE, 96, 104}}};

LvBaddies lv5Baddies = {3, {{NULL, &lv5BdS, 8, 96, 24, 24, 0, 0, 1, FALSE, FALSE, 40, 24},
                            {NULL, &lv5BdS, 32, 96, 56, 56, 0, 0, -1, TRUE, FALSE, 72, 56},
                            {NULL, &lv5BdS2, 120, 120, 0, 88, 0, 0, 1, FALSE, TRUE, 120, 44}}};

LvBaddies lv6Baddies = {4, {{NULL, &lv6BdS, 48, 112, 64, 64, 0, 0, -1, TRUE, FALSE, 88, 64},
                            {NULL, &lv6BdS, 112, 168, 64, 64, 0, 0, -1, TRUE, FALSE, 128, 64},
                            {NULL, &lv6BdS, 56, 160, 104, 104, 0, 0, -1, TRUE, FALSE, 152, 104},
                            {NULL, &lv6BdS, 192, 232, 104, 104, 0, 0, 1, FALSE, FALSE, 200, 104}}};

LvBaddies lv7Baddies = {3, {{NULL, &lv7BdS, 16, 80, 64, 64, 0, 0, 1, FALSE, FALSE, 56, 64},
                            {NULL, &lv7BdS, 120, 232, 8, 8, 0, 0, 1, FALSE, FALSE, 200, 8},
                            {NULL, &lv7BdS, 136, 232, 104, 104, 0, 0, 1, FALSE, FALSE, 224, 104}}};
//faster baddies
LvBaddies lv8Baddies = {4, {{NULL, &lv8BdS, 8, 72, 104, 104, 0, 0, 2, FALSE, FALSE, 64, 104},
                            {NULL, &lv8BdS, 88, 120, 88, 88, 0, 0, -1, TRUE, FALSE, 104, 88},
                            {NULL, &lv8BdS, 144, 168, 56, 56, 0, 0, -2, TRUE, FALSE, 160, 56},
                            {NULL, &lv8BdS2, 120, 120, 0, 0, 0, 0, 1, FALSE, TRUE, 120, 0}}};
//faster baddies
LvBaddies lv9Baddies = {6, {{NULL, &lv9BdS, 96, 144, 80, 80, 0, 0, 1, FALSE, FALSE, 136, 80},
                            {NULL, &lv9BdS, 96, 144, 24, 24, 0, 0, -1, TRUE, FALSE, 136, 24},
                            {NULL, &lv9BdS2, 40, 40, 0, 104, 0, 0, 1, FALSE, TRUE, 40, 40},
                            {NULL, &lv9BdS2, 80, 80, 0, 104, 0, 0, 2, FALSE, TRUE, 80, 72},
                            {NULL, &lv9BdS2, 160, 160, 0, 104, 0, 0, 1, FALSE, TRUE, 160, 40},
                            {NULL, &lv9BdS2, 200, 200, 0, 104, 0, 0, 2, FALSE, TRUE, 200, 72}}};
//faster baddies
LvBaddies lv10Baddies = {4, {{NULL, &lv10BdS, 32, 208, 104, 104, 0, 0, 2, FALSE, FALSE, 104, 104},
                            {NULL, &lv10BdS, 64, 112, 80, 80, 0, 0, -1, TRUE, FALSE, 104, 80},
                            {NULL, &lv10BdS, 72, 112, 56, 56, 0, 0, -2, TRUE, FALSE, 88, 56},
                            {NULL, &lv10BdS, 136, 168, 40, 40, 0, 0, 2, FALSE, FALSE, 152, 40}}};
//faster baddies
LvBaddies lv11Baddies = {7, {{NULL, &lv11BdS, 24, 24, 32, 104, 0, 0, -1, FALSE, TRUE, 24, 88},
                            {NULL, &lv11BdS, 96, 96, 0, 56, 0, 0, 2, FALSE, TRUE, 96, 8},
                            {NULL, &lv11BdS, 168, 168, 48, 104, 0, 0, -1, FALSE, TRUE, 168, 88},
                            {NULL, &lv11BdS, 208, 208, 0, 104, 0, 0, 2, FALSE, TRUE, 208, 96},
                            {NULL, &lv11BdS2, 40, 152, 104, 104, 0, 0, -1, TRUE, FALSE, 48, 104 },
                            {NULL, &lv11BdS2, 112, 144, 56, 56, 0, 0, -1, TRUE, FALSE, 136, 56},
                            {NULL, &lv11BdS2, 120, 192, 24, 24, 0, 0, -1, TRUE, FALSE, 136, 24}}};//check range
//faster baddies
LvBaddies lv12Baddies = {4, {{NULL, &lv12BdS, 8, 72, 104, 104, 0, 0, 2, FALSE, FALSE, 48, 104},
                            {NULL, &lv12BdS, 88, 122, 88, 88, 0, 0, -1, TRUE, FALSE, 114, 88},
                            {NULL, &lv12BdS, 200, 224, 48, 48, 0, 0, -2, TRUE, FALSE, 222, 48},
                            {NULL, &lv12BdS2, 120, 120, 0, 0, 0, 0, 1, FALSE, TRUE, 120, 0}}};
//faster baddies
LvBaddies lv13Baddies = {5, {{NULL, &lv13BdS, 56, 232, 8, 8, 0, 0, -2, TRUE, FALSE, 168, 8},
                            {NULL, &lv13BdS, 56, 232, 32, 32, 0, 0, -1, TRUE, FALSE, 184, 32},
                            {NULL, &lv13BdS, 56, 232, 56, 56, 0, 0, 2, FALSE, FALSE, 88, 56},
                            {NULL, &lv13BdS, 56, 232, 80, 80, 0, 0, -1, TRUE, FALSE, 200, 80},
                            {NULL, &lv13BdS2, 40, 40, 8, 104, 0, 0, -1, FALSE, TRUE, 40, 88}}};
//level 14 baddies have a falling pattern so need to work it out
LvBaddies lv14Baddies = {0, {{NULL, &lv13BdS, 0, 0, 0, 0, 0, 0, -1, FALSE, FALSE, 0, 0}}};
//faster baddies
LvBaddies lv15Baddies = {3, {{NULL, &lv15BdS, 80, 80, 32, 104, 0, 0, -2, FALSE, TRUE, 80, 56},
                            {NULL, &lv15BdS, 128, 128, 32, 104, 0, 0, 1, FALSE, TRUE, 128, 88},
                            {NULL, &lv15BdS,168, 168, 32, 104,0 ,0, 2, FALSE, TRUE, 168, 72}}};
//i think i made the sprites facing left for lv16
//faster baddies
LvBaddies lv16Baddies = {4, {{NULL, &lv16BdS, 8, 168, 104, 104, 0, 0, -2, FALSE, FALSE, 152, 104},
                            {NULL, &lv16BdS, 8, 64, 80, 80, 0, 0, -2, FALSE, FALSE, 16, 80},
                            {NULL, &lv16BdS, 144, 184, 56, 56, 0, 0, 2, TRUE, FALSE, 152, 56},
                            {NULL, &lv16BdS, 200, 232, 40, 40, 0, 0, -2, FALSE, FALSE, 216, 40}}};
//faster baddies
LvBaddies lv17Baddies = {6, {{NULL, &lv17BdS, 40, 64, 104, 104, 0, 0, 1, FALSE, FALSE, 48, 104},
                            {NULL, &lv17BdS, 96, 200, 104, 104, 0, 0, 2, FALSE, FALSE, 184, 104},
                            {NULL, &lv17BdS2, 24, 24, 64, 104, 0, 0, -1, FALSE, TRUE, 24, 88},
                            {NULL, &lv17BdS2, 80, 80, 0, 104, 0, 0, 2, FALSE, TRUE, 80, 88},
                            {NULL, &lv17BdS2, 152, 152, 0, 64, 0, 0, -1, FALSE, TRUE, 152, 40},
                            {NULL, &lv17BdS2, 216, 216, 0, 96, 0, 0, 2, FALSE, TRUE, 216, 8}}};
//faster baddies
LvBaddies lv18Baddies = {8, {{NULL, &lv18BdS, 94, 144, 24, 24, 0, 0, -1, TRUE, FALSE, 144, 24},
                            {NULL, &lv18BdS, 94, 144, 48, 48, 0, 0, -2, TRUE, FALSE, 128, 48},
                            {NULL, &lv18BdS, 94, 144, 80, 80, 0, 0, 1, FALSE, FALSE, 102, 80},
                            {NULL, &lv18BdS, 94, 144, 104, 104, 0, 0, 2, FALSE, FALSE, 128, 104},
                            {NULL, &lv18BdS2, 40, 40, 0, 104, 0, 0, 2, FALSE, TRUE, 40, 40},
                            {NULL, &lv18BdS2, 80, 80, 0, 104, 0, 0, -2, FALSE, TRUE, 80, 80},
                            {NULL, &lv18BdS2, 160, 160, 0, 104, 0, 0, 4, FALSE, TRUE, 160, 32},
                            {NULL, &lv18BdS2, 200, 200, 0, 104, 0, 0, -1, FALSE, TRUE, 200, 48}}};
//faster baddies
LvBaddies lv19Baddies = {7, {{NULL, &lv19BdS, 184, 232, 24, 24, 0, 0, -2, TRUE, FALSE, 192, 24},
                            {NULL, &lv19BdS, 176, 232, 48, 48, 0, 0, -2, TRUE, FALSE, 200, 48},
                            {NULL, &lv19BdS, 184, 232, 72, 72, 0, 0, -1, TRUE, FALSE, 192, 72},
                            {NULL, &lv19BdS, 96, 232, 104, 104, 0, 0, -2, TRUE, FALSE, 114, 104},
                            {NULL, &lv19BdS2, 40, 40, 0, 104, 0, 0, 2, FALSE, TRUE, 40, 8},
                            {NULL, &lv19BdS2, 88, 88, 48, 104, 0, 0, -1, FALSE, TRUE, 88, 64},
                            {NULL, &lv19BdS2, 128, 128, 0, 80, 0, 0, 1, FALSE, TRUE, 128, 32}}};
//faster baddies
LvBaddies lv20Baddies = {2, {{NULL, &lv20BdS, 56, 174, 104, 104, 0, 0, 2, FALSE, FALSE, 142, 104},
                            {NULL, &lv20BdS2, 192, 192, 40, 104, 0, 0, -1, FALSE, TRUE, 192, 88}}};
//faster baddies
LvBaddies *allLvBaddies[] = {&lv1Baddies, &lv2Baddies, &lv3Baddies, &lv4Baddies, &lv5Baddies, &lv6Baddies, &lv7Baddies,
                            &lv8Baddies, &lv9Baddies, &lv10Baddies, &lv11Baddies, &lv12Baddies, &lv13Baddies, &lv14Baddies,
                            &lv15Baddies, &lv16Baddies, &lv17Baddies, &lv18Baddies, &lv19Baddies, &lv20Baddies};


#endif