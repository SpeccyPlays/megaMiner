/**
 * HMega Miner
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include <resources.h>

u16 ind = TILE_USERINDEX;
u8 xOffset =  4;
u8 yOffset =  3;
u16 willyX = 48;
u16 willyY = 120;
Sprite *minerWilly;
enum state {INTRO = 0, PLAY = 1, DEAD = 2};
enum state gameState = INTRO;
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
            case DEAD:
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
    SPR_init(0, 0, 0);
    minerWilly = SPR_addSprite(&minerWillySprite, willyX, willyY, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    while(1)
    {
        u16 value = readInput();
	    if(value & BUTTON_RIGHT && willyX < 272){
            willyX += 1;
        }
	    else if(value & BUTTON_LEFT && willyX > 40){
            willyX-= 1;
        }
        SPR_setPosition(minerWilly,willyX,willyY);
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
