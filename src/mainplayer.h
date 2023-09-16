#ifndef MAINPLAYER_H   /* Include guard */
#define MAINPLAYER_H
#include <genesis.h>
#include <resources.h>
#include "globalstruct.h"

//player stuff
enum movements {STAND = 0, WALKLEFT = 1 , WALKRIGHT = 2, DEAD = 3, BLOCKED = 4};
enum jumpOrFall {NOTHING = 0, JUMPING = 1, FALLING = 2, FALL = 3};
typedef struct {
    Sprite *pSprite;
    const SpriteDefinition *pSpriteDef;
    u16 x;
    u16 y;
    bool facingLeft;
    enum movements pMovements;
    enum jumpOrFall pJumpOrFall;
    u8 currentSpriteNum; //willy will stay on same animation frame so need to track it
    u8 numOfFrames; //used later on so we can loop from end frame to first
    u8 jumpCounter; //see how high willy has jumped
    u8 jumpMax; //max height he can jump
    u8 fallCounter; //Willy will die if he falls for too long
    u8 maxFall; //max fall height in pixels
} Player ;

Player willy = {NULL, &minerWillySprite, FALSE, 48, 128, STAND, NOTHING, 0, 8, 0, 18, 0, 100};

#endif