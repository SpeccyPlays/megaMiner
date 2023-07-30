/**
 * Mega Miner
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include <resources.h>
#include "levels.h"

//screen positioning
u8 xOffset =  4; //offsets are in number of 8x8 tiles
u8 yOffset =  3;
u16 xLeftStop = 37;//19-07-23 don't think I'm using this now
u16 xRightStop = 267;//19-07-23 don't think I'm using this now
//used for keeping track of what tiles are loaded in VRAM
u16 ind = TILE_USERINDEX;
u16 baseInd = TILE_USERINDEX;
//player stuff
enum movements {STAND = 0, WALKLEFT = 1 , WALKRIGHT = 2, DEAD = 3, BLOCKED = 4};
enum jumpOrFall {NOTHING = 0, JUMPING = 1, FALLING = 2, FALL = 3};
typedef struct {
    Sprite *pSprite;
    u16 x;
    u16 y;
    enum movements pMovements;
    enum jumpOrFall pJumpOrFall;
    u8 currentSpriteNum; //willy will stay on same animation frame so need to track it
    u8 numOfFrames; //used later on so we can loop from end frame to first
    u8 jumpCounter; //see how high willy has jumped
    u8 jumpMax; //max height he can jump
    u8 fallCounter; //Willy will die if he falls for too long
    u8 maxFall; //max fall height in pixels
} Player ;
Player willy = {NULL, 48, 128, STAND, NOTHING, 0, 8, 0, 18, 0, 100};//change x and y so don't include offset ?
Enemy baddie = {NULL, 72 + 32, 104 + 32, 0, 0, 72 + 32, 56 + 24, 1, FALSE};
Sprite *boot = NULL;
//game stuff
enum state {INTRO = 0, PLAY = 1, DEATH = 2};
enum state gameState = INTRO;
//8 = empty space; 0 = ledge; 1 = brick; 2 = bush; 3 = key; 4 = spike; 5 = floor that falls
//6 = gate; 7 = conveyor belt
//first [] is y, second x
u8 levelMap[17][32] = {
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 3, 8, 4, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 3, 8, 1},
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
    {1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 2, 3, 8, 8, 2, 8, 8, 8, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 0, 5, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 3, 1},
	{1, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1, 1, 1, 8, 2, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
	{1, 0, 0, 0, 0, 8, 8, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 1},
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 0, 0, 1},
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 2, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1, 1, 1, 5, 5, 5, 5, 5, 0, 0, 0, 1},
	{1, 8, 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 8, 8, 8, 6, 6, 1},
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 6, 6, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
};
const Image *levelsBG[20] = {&level1, &level2, &level3, &level4, &level5, &level6, &level7, &level8,
                            &level9, &level10, &level11, &level12, &level13, &level14, &level15, &level16,
                            &level17, &level18, &level19, &level20};
u8 lvNumber = 0;
//level sprites

//declarations
void playIntro();
void drawHud();
void updateHud();
void loadLevel();
void playGame();
void showDeathSequence();
void handleInput();
void handlePlayAnim();
void pMoveLeft();
void pMoveRight();
void pJumping();
void pFalling();
u16 convertPixelValueToTile(u16 value);
void pCollisions(u16 x, u16 y);
u8 collideDown(u16 x, u16 y);
u8 collideUp(u16 x, u16 y);
u8 collideLeft(u16 x, u16 y);
u8 collideRight(u16 x, u16 y);
u8 objectChecking(u8 objectToCheck);

int main()
{
    SPR_init(0, 0, 0); //start sprite engine
    while(1){
        switch (gameState){
            case INTRO:
                playIntro();
                break;
            case PLAY:
                playGame();
                break;
            case DEATH:
                showDeathSequence();
                break;
        }
    }
    return(0);
    
}
void playIntro(){
    ind = baseInd; //so we're overwriting previous level data instead of filling all memory with level data
    PAL_setPalette(PAL0, introScreen.palette->data, DMA);
    drawHud();
    VDP_drawImageEx(BG_B, &introScreen, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0+xOffset, 0+yOffset, FALSE, TRUE);
    //ind += introScreen.tileset->numTile;
    XGM_setLoopNumber(-1);
    XGM_startPlay(&intro);
    while (gameState == INTRO){
        u16 value = JOY_readJoypad(JOY_1);
	    if(value & BUTTON_START){
           gameState = PLAY;
           break;
        }
        SYS_doVBlankProcess();
    }
    XGM_stopPlay();
};
void drawHud(){
    ind = baseInd; //so we're overwriting previous level data instead of filling all memory with level data
    VDP_drawImageEx(BG_B, &HUD, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind), 0+xOffset, 16+yOffset, FALSE, TRUE);
    ind += HUD.tileset->numTile;
    VDP_clearTextArea(xOffset, yOffset, 32, 168);
};
void updateHud(){
    VDP_setPaletteColor(15, RGB8_8_8_TO_VDPCOLOR(255, 255, 255));
    VDP_drawText("Central Cavern", 10 + xOffset, 16 + yOffset);
    VDP_drawText("AIR", 0 + xOffset, 17 + yOffset);
    VDP_drawText("High Score", 0 + xOffset, 18 + yOffset);
    VDP_drawText("Score", 21 + xOffset, 18 + yOffset);
}
void loadLevel(){
    VDP_drawImageEx(BG_B, levelsBG[lvNumber], TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0+xOffset, 0+yOffset, FALSE, TRUE);
    XGM_setLoopNumber(-1);
    XGM_startPlay(&megaMinerMain);
    willy.pSprite = SPR_addSprite(&minerWillySprite, willy.x, willy.y, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    baddie.eSprite = SPR_addSprite(&lv1BdS, baddie.xStart, baddie.yStart, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    updateHud();
};
void playGame(){
    loadLevel();
    u8 counter = 0;
    u16 flip;
    while(gameState == PLAY)
    {
        //using a counter too slow the play down so it's more like the original
        if (counter % 2 == 0){
            if (willy.pMovements == WALKLEFT){
                flip = TRUE;
            }
            else if(willy.pMovements == WALKRIGHT){
                flip = FALSE;
            }
            handleInput();
            SPR_setPosition(baddie.eSprite, baddie.xPos, baddie.yPos);
            SPR_setHFlip(baddie.eSprite, baddie.facingLeft);
            SPR_setPosition(willy.pSprite,willy.x,willy.y); 
            SPR_setHFlip(willy.pSprite, flip);
            SPR_setAnim(willy.pSprite, willy.currentSpriteNum);
            SPR_update();//19-7-23 maybe move this to main loop
        }
        if (counter % 4 == 0){
            baddie.xPos += baddie.moveIncrement;
            if (baddie.xPos - 16 >= baddie.xEnd || baddie.xPos <= baddie.xStart){
                baddie.moveIncrement = baddie.moveIncrement * - 1;
                baddie.facingLeft = !baddie.facingLeft;
            }
            counter = 0;
        }

        counter ++;
        SYS_doVBlankProcess();
    }
    SPR_clear();
    VDP_clearSprites();
};
void showDeathSequence(){
    SPR_init(0, 0, 0);
    drawHud();
    VDP_drawImageEx(BG_B, &deathScreen, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0+xOffset, 0+yOffset, FALSE, TRUE);
    ind += deathScreen.tileset->numTile;
    boot = SPR_addSprite(&deathBoot, (16 + xOffset) * 8, (yOffset) * 8, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    for (u16 j = 0; j < 180; j++){
        SPR_update();
        SYS_doVBlankProcess();
    }
    SPR_clear();
    SYS_doVBlankProcess();
    gameState = INTRO;
    VDP_clearSprites();
};
void handleInput(){
    //In the original you can't change direction of the jump or when falling
    //so only check the controls when player is doing neithr
    if (willy.pJumpOrFall == NOTHING){
        u16 value = JOY_readJoypad(JOY_1);
        if (value & BUTTON_RIGHT){
            willy.pMovements = WALKRIGHT;
            pMoveRight();
        }
        else if(value & BUTTON_LEFT){
            willy.pMovements = WALKLEFT;
            pMoveLeft();
        }
        else {
            willy.pMovements = STAND;
        }
        if (!collideDown(willy.x, willy.y)) {
            //willy.pMovements = STAND;
            willy.pJumpOrFall = FALL;
        }
        if (value & BUTTON_B){
            willy.pJumpOrFall = JUMPING;
        }
        else if (value & BUTTON_C){
            gameState = DEATH;
        }
    }
    else if (willy.pJumpOrFall == FALL){
        pFalling();
    }
    else if (willy.pJumpOrFall == JUMPING || willy.pJumpOrFall == FALLING){
        if (willy.pMovements == WALKRIGHT){
            pMoveRight();
        }
        else if (willy.pMovements == WALKLEFT){
            pMoveLeft();
        }
        if (willy.pJumpOrFall == JUMPING){
            if (!collideUp(willy.x, willy.y)){
                pJumping();
            }
            else {
                willy.jumpCounter = 0;
                willy.pJumpOrFall = FALLING;
            }
        }
        else if (willy.pJumpOrFall == FALLING){
            pFalling();
        }
    }
    pCollisions(willy.x, willy.y);
};
void pMoveLeft(){
    willy.x -= 1;
    handlePlayAnim();
};
void pMoveRight(){
    willy.x += 1;
    handlePlayAnim();
};
void pJumping(){
    if (willy.jumpCounter <= willy.jumpMax){
        willy.jumpCounter ++;
        willy.y --;
    }
   else if (willy.jumpCounter > willy.jumpMax){
        willy.jumpCounter = 0;
        willy.pJumpOrFall = FALLING;
        willy.y ++;
    }
};
void pFalling(){
    willy.fallCounter ++;
    willy.y ++;
    if (collideDown(willy.x, willy.y)){  
        willy.fallCounter = 0;
        willy.pJumpOrFall = NOTHING;
    }
    if (willy.fallCounter > willy.maxFall){
            //willy.pMovements = DEAD;
    }
};
void handlePlayAnim(){
    willy.currentSpriteNum ++;
    if (willy.currentSpriteNum >= willy.numOfFrames){
        willy.currentSpriteNum = 0;
    }
};
u16 convertPixelValueToTile(u16 value){
    return value >> 3; //divide by by 8
};
void pCollisions(u16 x, u16 y){
    if (collideLeft(x, y) || collideRight(x, y)){
        willy.pMovements = STAND;
    }
}
u8 collideDown(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 3 - (xOffset * 8));
    u8 x2 = convertPixelValueToTile(x + 14 - (xOffset * 8));
    u8 y1 = convertPixelValueToTile(y + 16 - (yOffset * 8));
    u8 tileL = levelMap[y1 + 1][x1];
    u8 tileR = levelMap[y1 + 1][x2];
    if (tileL != 8 || tileR != 8){
        VDP_drawText("Collision down", xOffset + 1, yOffset + 2);
        return 1;
    }
    else{
        VDP_drawText("                 ", xOffset + 1, yOffset + 2);
        return 0;
    }
};
u8 collideUp(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 3 - xOffset * 8);
    u8 x2 = convertPixelValueToTile(x + 14 - xOffset * 8);
    u8 y1 = convertPixelValueToTile(y + 16 - yOffset * 8);
    u8 tileL = levelMap[y1 - 1][x1];
    u8 tileR = levelMap[y1 - 1][x2];
    if (tileL == 1 || tileR == 1){
        VDP_drawText("Collision up", xOffset + 1, yOffset + 2);
        return 1;
    }
    else{
        VDP_drawText("                ", xOffset + 1, yOffset + 2);
        return 0;
    }
};
u8 collideLeft(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 3 - xOffset * 8);
    u8 y1 = convertPixelValueToTile(y + 14 - yOffset * 8);
    //u8 tileT = levelMap[y1][x1];
    u8 tileB = levelMap[y1][x1];
    if (tileB == 1){
        //VDP_drawText("Collision LEFT", xOffset + 1, yOffset + 2);
        willy.x += 2;
        return 1;
    }
    else{
        //VDP_drawText("               ", xOffset + 1, yOffset + 2);
        return 0;
    }
};
u8 collideRight(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 14 - xOffset * 8);
    u8 y1 = convertPixelValueToTile(y + 16 - yOffset * 8);
    //u8 tileT = levelMap[y1][x1];
    u8 tileB = levelMap[y1][x1];
    if (tileB == 1){
        //VDP_drawText("Collision RIGHT", xOffset + 1, yOffset + 2);
        willy.x -=2;
        return 1;
    }
    else{
        //VDP_drawText("               ", xOffset + 1, yOffset + 2);
        return 0;
    }
}
u8 objectChecking(u8 objectToCheck){
    return 0;
}
