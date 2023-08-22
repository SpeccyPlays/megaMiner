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

    Keys lv1Keys = {5, NULL, {{.x =240, .y = 48}, {.x = 72, .y=0 }, {.x = 128, .y = 8}, {.x = 192, .y = 32}, {.x = 232, .y = 0}}};

#endif