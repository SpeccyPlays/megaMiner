#ifndef COLLECTABLES_H   /* Include guard */
#define COLLECTABLES_H
#include <genesis.h>
#include <resources.h>

typedef struct {
    u16 x;
    u16 y;
} CoOrds;
typedef struct {
    u8 numOfKeys;
    Sprite *keySprite;
    CoOrds xy[];
} Keys;

Keys lv1Keys = {5, NULL, {{.x=240,.y=48}, {.x=72,.y=0}, {.x=128,.y=8}, {.x=192,.y=32}, {.x=232, .y=0}}};
Keys lv2Keys = {5, NULL, {{.x=24,.y=72}, {.x=152,.y=96}, {.x=56,.y=8}, {.x=192,.y=8}, {.x=208, .y=56}}};
Keys lv3Keys = {5, NULL, {{.x=168, .y=48}, {.x=240,.y=48}, {.x=48,.y=0}, {.x=120,.y=0}, {.x=184,.y=0}}};
Keys lv4Keys = {5, NULL, {{.x=8,.y=0}, {.x=96,.y=8}, {.x=128,.y=48}, {.x=200,.y=8}, {.x=240,.y=48}}};
Keys lv5Keys = {5, NULL, {{.x=56,.y=96}, {.x=72,.y=96}, {.x=72,.y=48}, {.x=232,.y=56}, {.x=240,.y=8}}};
Keys lv6Keys = {5, NULL, {{.x=8,.y=80}, {.x=104,.y=88}, {.x=120,.y=48}, {.x=136,.y=48}, {.x=240,.y=56}}};

Keys *allLvKeys[] = {&lv1Keys, &lv2Keys, &lv3Keys, &lv4Keys, &lv5Keys, lv6Keys};


#endif