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
    u8 spriteNum;
} player ;
player willy = {NULL, 48, 120, STAND, 0};
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
u16 readInput();

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
        u16 value = readInput();
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
    while(1)
    {
        u16 value = readInput();
	    if(value & BUTTON_RIGHT && willy.x < 272){
            willy.x += 1;
        }
	    else if(value & BUTTON_LEFT && willy.x > 40){
            willy.x -= 1;
        }
        SPR_setPosition(willy.pSprite,willy.x,willy.y);
        SPR_update();
        //For versions prior to SGDK 1.60 use VDP_waitVSync instead.
        SYS_doVBlankProcess();
    }
}
void showDeathSequence(){

};
u16 readInput(){
    return JOY_readJoypad(JOY_1);
}
