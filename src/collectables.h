#ifndef COLLECTABLES_H   /* Include guard */
#define COLLECTABLES_H
#include <genesis.h>
#include <resources.h>

typedef struct {
    u16 x;
    u16 y
} CoOrds;
typedef struct {
    Sprite *keySprite;
    CoOrds xy;
} key;



#endif