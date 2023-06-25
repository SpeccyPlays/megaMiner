/**
 * Mega Miner
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include <resources.h>

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
player willy = {NULL, 48, 120, STAND, NOTHING, 0, 8, 0, 18, 0, 12};
//game stuff
enum state {INTRO = 0, PLAY = 1, DEATH = 2};
enum state gameState = INTRO;
//8 = empty space 0 = ledge 1 = brick 2 = bush 3 = key 4 = spike 5 = floor that falls
//6 = gate 7 = conveyor belt
//first [] is y, second x
u8 levelMap[16][32] = {
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 3, 8, 4, 8, 8, 8, 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 3, 8, 1},
	{1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 3, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1},
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
//screen positioning
u8 xOffset =  4; //offsets are in number of 8x8 tiles
u8 yOffset =  3;
u16 xLeftStop = 37;
u16 xRightStop = 267;
//declarations
void playIntro();
void playGame();
void showDeathSequence();
void handleInput();
void handlePlayAnim();
void pMoveLeft();
void pMoveRight();
u16 convertPixelValueToTile(u16 value);

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
}
void playGame(){
    VDP_drawImageEx(BG_B, &level1, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0+xOffset, 0+yOffset, FALSE, TRUE);
    ind += level1.tileset->numTile;
    VDP_drawImageEx(BG_A, &level1foreground, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0+xOffset, 0+yOffset, FALSE, TRUE);
    ind += level1foreground.tileset->numTile;
    VDP_setPaletteColor(15, RGB8_8_8_TO_VDPCOLOR(255, 255, 255));
    VDP_drawText("Central Cavern", 10 + xOffset, 15 + yOffset);
    VDP_drawText("AIR", 0 + xOffset, 16 + yOffset);
    VDP_drawText("High Score", 0 + xOffset, 17 + yOffset);
    VDP_drawText("Score", 21 + xOffset, 17 + yOffset);
    XGM_setLoopNumber(-1);
    XGM_startPlay(&megaMinerMain);
    SPR_init(0, 0, 0);
    willy.pSprite = SPR_addSprite(&minerWillySprite, willy.x, willy.y, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    u8 counter = 0;
    while(gameState == PLAY)
    {
        //using a counter too slow the play down so it's more like the original
        if (counter % 2 == 0){
            u16 flip;
            if (willy.pMovements == WALKLEFT){
                flip = TRUE;
            }
            else {
                flip = FALSE;
            }
            char x[8] = {0};
            sprintf(x, "%d", convertPixelValueToTile((willy.x + 3)  - xOffset * 8));
            char y[8] = {0};
            sprintf(y, "%d", convertPixelValueToTile(willy.y- yOffset * 8));
            VDP_drawText(x , xOffset + 1, yOffset);
            VDP_drawText(y, xOffset + 1, yOffset + 1);
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
}
void showDeathSequence(){
    gameState = INTRO;
};
void handleInput(){
    u16 value = JOY_readJoypad(JOY_1);
    if (willy.pJumpOrFall == JUMPING && willy.jumpCounter <= willy.jumpMax){
        willy.jumpCounter ++;
        willy.y --;
        if (willy.pMovements == WALKRIGHT && willy.x < xRightStop){
            pMoveRight();
        }
        else if(willy.pMovements == WALKLEFT && willy.x > xLeftStop){
            pMoveLeft();
        }
        if (willy.jumpCounter > willy.jumpMax){
            willy.jumpCounter = 0;
            willy.pJumpOrFall = FALLING;
        }
    }
    else if (willy.pJumpOrFall == FALLING){
        willy.fallCounter ++;
        willy.y ++;
        if (willy.fallCounter > willy.maxFall){
            willy.pMovements = STAND;
        }
        else if (willy.pMovements == WALKRIGHT && willy.x < xRightStop){
            pMoveRight();
        }
        else if(willy.pMovements == WALKLEFT && willy.x > xLeftStop){
            pMoveLeft();
        }
    }
	else if(value & BUTTON_RIGHT && willy.x < xRightStop){
        willy.pMovements = WALKRIGHT;
        pMoveRight();
    }
	else if(value & BUTTON_LEFT && willy.x > xLeftStop){
        willy.pMovements = WALKLEFT;
        pMoveLeft();
    }
    if (value & BUTTON_B && willy.pJumpOrFall == NOTHING){
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
    return value >> 3; //divide by by 8
}

