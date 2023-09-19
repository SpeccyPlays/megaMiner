#ifndef GAME_H   /* Include guard */
#define GAME_H
#include <genesis.h>
#include <resources.h>

enum state {INTRO = 0, PLAY = 1, DEATH = 2};
Sprite *lives[3];

#endif