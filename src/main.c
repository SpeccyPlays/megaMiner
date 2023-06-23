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
enum movements {STAND = 0, WALKLEFT = 1 , WALKRIGHT = 2, JUMPING = 3};
typedef struct {
    Sprite *pSprite;
    u16 x;
    u16 y;
    enum movements pMovements;
    u16 currentSpriteNum; //willy will stay on same animation frame so need to track it
    u16 numOfFrames; //used later on so we can loop from end frame to first
} player ;
player willy = {NULL, 48, 120, STAND, 0, 8};
//game stuff
enum state {INTRO = 0, PLAY = 1, DEATH = 2};
enum state gameState = INTRO;
//screen positioning
u8 xOffset =  4;
u8 yOffset =  3;
//declarations
void playIntro();
void playGame();
void showDeathSequence();
void handleInput();
void handlePlayAnim();

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
    while(1)
    {
        if (counter % 2 == 0){
            u16 flip;
            if (willy.pMovements == WALKLEFT){
                flip = TRUE;
            }
            else {
                flip = FALSE;
            }
            handleInput();
            SPR_setPosition(willy.pSprite,willy.x,willy.y);
            SPR_setHFlip(willy.pSprite, flip);
            SPR_setAnim(willy.pSprite, willy.currentSpriteNum);
            SPR_update();
            counter = 0;
        }
            //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
        counter ++;
    }
}
void showDeathSequence(){

};
void handleInput(){
    u16 value = JOY_readJoypad(JOY_1);
	if(value & BUTTON_RIGHT && willy.x < 267){
        willy.pMovements = WALKRIGHT;
        willy.x += 1;
        handlePlayAnim();
    }
	else if(value & BUTTON_LEFT && willy.x > 37){
        willy.pMovements = WALKLEFT;
        willy.x -= 1;
        handlePlayAnim();
    }
};
void handlePlayAnim(){
    willy.currentSpriteNum ++;
    if (willy.currentSpriteNum >= willy.numOfFrames){
        willy.currentSpriteNum = 0;
    }
}

