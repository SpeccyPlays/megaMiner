/**
 * Mega Miner
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include <resources.h>
#include "levels.h"

//used for keeping track of what tiles are loaded in VRAM
u16 ind = TILE_USERINDEX;
//player stuff
enum movements {STAND = 0, WALKLEFT = 1 , WALKRIGHT = 2, DEAD = 3};
enum jumpOrFall {NOTHING = 0, JUMPING = 1, FALLING = 2};
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
} player ;
player willy = {NULL, 48, 128, STAND, NOTHING, 0, 8, 0, 18, 0, 12};
//game stuff
enum state {INTRO = 0, PLAY = 1, DEATH = 2};
enum state gameState = INTRO;
//8 = empty space 0 = ledge 1 = brick 2 = bush 3 = key 4 = spike 5 = floor that falls
//6 = gate 7 = conveyor belt
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
const Image *levelsBG[5] = {&level1, &level2, &level3, &level4, &level5};
u8 lvNumber = 0;
//level sprites
Sprite *keySprite = NULL;
//screen positioning
u8 xOffset =  4; //offsets are in number of 8x8 tiles
u8 yOffset =  3;
u16 xLeftStop = 37;
u16 xRightStop = 267;
//declarations
void playIntro();
void loadLevel();
void playGame();
void showDeathSequence();
void handleInput();
void handlePlayAnim();
void pMoveLeft();
void pMoveRight();
u16 convertPixelValueToTile(u16 value);
u8 collideDown(u16 x, u16 y);
u8 collideUp(u16 x, u16 y);
u8 collideLeft(u16 x, u16 y);
u8 collideRight(u16 x, u16 y);

int main()
{
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
    PAL_setPalette(PAL0, introScreen.palette->data, DMA);
    VDP_drawImageEx(BG_B, &introScreen, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0+xOffset, 0+yOffset, FALSE, TRUE);
    ind += introScreen.tileset->numTile;
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
void loadLevel(){
    VDP_drawImageEx(BG_B, levelsBG[lvNumber], TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0+xOffset, 0+yOffset, FALSE, TRUE);
    ind += level1.tileset->numTile;
    //VDP_drawImageEx(BG_A, &level1foreground, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0+xOffset, 0+yOffset, FALSE, TRUE);
    //ind += level1foreground.tileset->numTile;
    VDP_setPaletteColor(15, RGB8_8_8_TO_VDPCOLOR(255, 255, 255));
    VDP_drawText("Central Cavern", 10 + xOffset, 16 + yOffset);
    VDP_drawText("AIR", 0 + xOffset, 17 + yOffset);
    VDP_drawText("High Score", 0 + xOffset, 18 + yOffset);
    VDP_drawText("Score", 21 + xOffset, 18 + yOffset);
    XGM_setLoopNumber(-1);
    XGM_startPlay(&megaMinerMain);
    SPR_init(0, 0, 0);
    willy.pSprite = SPR_addSprite(&minerWillySprite, willy.x, willy.y, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    keySprite = SPR_addSprite(&key, willy.x + 8, willy.y, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
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
            SPR_setPosition(willy.pSprite,willy.x,willy.y);
            SPR_setHFlip(willy.pSprite, flip);
            SPR_setAnim(willy.pSprite, willy.currentSpriteNum);
            SPR_update();
            counter = 0;
        }
    counter ++;
    SYS_doVBlankProcess();
    }
};
void showDeathSequence(){
    gameState = INTRO;
};
void handleInput(){
    u16 value = JOY_readJoypad(JOY_1);
    if (willy.pJumpOrFall == JUMPING && willy.jumpCounter <= willy.jumpMax && !collideUp(willy.x, willy.y) ){
        willy.jumpCounter ++;
        willy.y --;
        if (willy.pMovements == WALKRIGHT && !collideRight(willy.x, willy.y)){
            pMoveRight();
        }
        else if(willy.pMovements == WALKLEFT && !collideLeft(willy.x, willy.y)){
            pMoveLeft();
        }
        if (willy.jumpCounter > willy.jumpMax || collideUp(willy.x, willy.y)){
            willy.jumpCounter = 0;
            willy.pJumpOrFall = FALLING;
            willy.y ++;
        }
    }
    else if (willy.pJumpOrFall == FALLING){
        willy.fallCounter ++;
        willy.y ++;
        if (collideDown(willy.x , willy.y)){
            willy.pJumpOrFall = NOTHING;
            willy.fallCounter = 0;
        }
        else if (willy.fallCounter > willy.maxFall){
            //Willy will just helplessly fall
        }
        else if (willy.pMovements == WALKRIGHT && !collideRight(willy.x, willy.y)){
            pMoveRight();
        }
        else if(willy.pMovements == WALKLEFT && !collideLeft(willy.x, willy.y)){
            pMoveLeft();
        }
    }
	else if(value & BUTTON_RIGHT && !collideRight(willy.x, willy.y)){
        willy.pMovements = WALKRIGHT;
        pMoveRight();
        if (!collideDown(willy.x , willy.y)){
            willy.pJumpOrFall = FALLING;
            willy.pMovements = STAND;
        }
    }
	else if(value & BUTTON_LEFT && !collideLeft(willy.x, willy.y)){
        willy.pMovements = WALKLEFT;
        pMoveLeft();
        if (!collideDown(willy.x , willy.y)){
            willy.pJumpOrFall = FALLING;
            willy.pMovements = STAND;
        }
    }
    else {
        willy.pMovements = STAND;
    }
    if (value & BUTTON_B && willy.pJumpOrFall == NOTHING && !collideUp(willy.x, willy.y)){
        willy.pJumpOrFall = JUMPING;
        willy.y --;
    }
};
void pMoveLeft(){
    willy.x -= 1;
    handlePlayAnim();
};
void pMoveRight(){
    willy.x += 1;
    handlePlayAnim();
};
void handlePlayAnim(){
    willy.currentSpriteNum ++;
    if (willy.currentSpriteNum >= willy.numOfFrames){
        willy.currentSpriteNum = 0;
    }
};
u16 convertPixelValueToTile(u16 value){
    return value / 8; //divide by by 8
};
u8 collideDown(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 3 - xOffset * 8);
    u8 x2 = convertPixelValueToTile(x + 13 - xOffset * 8);
    u8 y1 = convertPixelValueToTile(y + 16 - yOffset * 8);
    u8 tileL = levelMap[y1 + 1][x1];
    u8 tileR = levelMap[y1 + 1][x2];
    if (tileL == 0 || tileR == 0){
        VDP_drawText("Collision", xOffset + 1, yOffset + 2);
        return 1;
    }
    else{
        VDP_drawText("                s", xOffset + 1, yOffset + 2);
        return 0;
    }
};
u8 collideUp(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 3 - xOffset * 8);
    u8 x2 = convertPixelValueToTile(x + 13 - xOffset * 8);
    u8 y1 = convertPixelValueToTile(y + 16 - yOffset * 8);
    u8 tileL = levelMap[y1 - 1][x1];
    u8 tileR = levelMap[y1 - 1][x2];
    if (tileL == 1 || tileR == 1){
        VDP_drawText("Collision", xOffset + 1, yOffset + 2);
        return 1;
    }
    else{
        VDP_drawText("                ", xOffset + 1, yOffset + 2);
        return 0;
    }
};
u8 collideLeft(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 3 - xOffset * 8);
    u8 y1 = convertPixelValueToTile(y + 16 - yOffset * 8);
    u8 tileT = levelMap[y1][x1];
    u8 tileB = levelMap[y1][x1];
    if (tileT == 1 || tileB == 1){
        VDP_drawText("Collision LEFT", xOffset + 1, yOffset + 2);
        return 1;
    }
    else{
        VDP_drawText("               ", xOffset + 1, yOffset + 2);
        return 0;
    }
};
u8 collideRight(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 13 - xOffset * 8);
    u8 y1 = convertPixelValueToTile(y + 16 - yOffset * 8);
    u8 tileT = levelMap[y1][x1];
    u8 tileB = levelMap[y1][x1];
    if (tileT == 1 || tileB == 1){
        VDP_drawText("Collision RIGHT", xOffset + 1, yOffset + 2);
        return 1;
    }
    else{
        VDP_drawText("               ", xOffset + 1, yOffset + 2);
        return 0;
    }
}
