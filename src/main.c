/**
 * Mega Miner
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include <resources.h>
#include "levels.h"
#include "game.h"
#include "mainplayer.h"
#include "baddie.h"
#include "collisionMaps.h"
#include "collectables.h"

//screen positioning
const u8 xOffset = 4; //offsets are in number of 8x8 tiles
const u8 yOffset = 3;
u16 xOffsetPixel = 0; //pixel off sets will be used for sprites
u16 yOffsetPixel = 0; //we update the value in main - tile offset * 8
u8 xLvTileWidth = 32;
u8 yLvTileHeight = 16;
u16 tilesPerLevel = 512;

//i = x + width*y; for traversing 1d array as 2d array space
u16 xLeftStop = 37;//19-07-23 don't think I'm using this now
u16 xRightStop = 267;//19-07-23 don't think I'm using this now
//used for keeping track of what tiles are loaded in VRAM
u16 ind = TILE_USERINDEX;
u16 baseInd = TILE_USERINDEX;
//sprite stuff
Player willy = {NULL, 48, 128, STAND, NOTHING, 0, 8, 0, 18, 0, 100};//change x and y so don't include offset ?
Sprite *boot = NULL;
Enemy lv1Baddie = {&lv1BdS, 64, 135, 56, 56, 64, 56, 1, FALSE};

//game stuff
enum state gameState = INTRO;
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
u8 convertPixelValueToTile(u16 value);
void pCollisions(u16 x, u16 y);
u8 collideDown(u16 x, u16 y);
u8 collideUp(u16 x, u16 y);
u8 collideLeft(u16 x, u16 y);
u8 collideRight(u16 x, u16 y);
u8 checkCollisionMap(u8 x, u8 y);

int main()
{
    xOffsetPixel = xOffset * 8;
    yOffsetPixel = yOffset * 8;
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
    VDP_drawText(levelNames[lvNumber], xOffset, 16 + yOffset);
    VDP_drawText("AIR", 0 + xOffset, 17 + yOffset);
    VDP_drawText("High Score", 0 + xOffset, 18 + yOffset);
    VDP_drawText("Score", 21 + xOffset, 18 + yOffset);
}
void loadLevel(){
    SPR_init(0, 0, 0);
    VDP_drawImageEx(BG_B, levelsBG[lvNumber], TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0+xOffset, 0+yOffset, FALSE, TRUE);
    XGM_setLoopNumber(-1);
    XGM_startPlay(&megaMinerMain);
    willy.pSprite = SPR_addSprite(&minerWillySprite, willy.x, willy.y, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    /*baddie.eSprite = SPR_addSprite(&lv1BdS, baddie.xStart, baddie.yStart, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    lv1Baddie.xPos += xOffsetPixel;
    lv1Baddie.yPos += yOffsetPixel;
    lv1Baddie.xStart += xOffsetPixel;
    lv1Baddie.yStart += yOffsetPixel;
    lv1Baddie.eSprite = SPR_addSprite(&lv1BdS, lv1Baddie.xStart, lv1Baddie.yStart, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    */
    
    for (u8 i = 0; i < lv1Keys.numOfKeys; i++){
        allLvKeys[lvNumber]->keySprite = SPR_addSprite(&key, allLvKeys[lvNumber]->xy[i].x + xOffsetPixel, allLvKeys[lvNumber]->xy[i].y + yOffsetPixel, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    }
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
            //23/8/23 removed below while testing key loading for each level
            //SPR_setPosition(lv1Baddie.eSprite, lv1Baddie.xPos, lv1Baddie.yPos);
            //SPR_setHFlip(lv1Baddie.eSprite, lv1Baddie.facingLeft);
            SPR_setPosition(willy.pSprite,willy.x,willy.y); 
            SPR_setHFlip(willy.pSprite, flip);
            SPR_setAnim(willy.pSprite, willy.currentSpriteNum);
            SPR_update();
            //below for debugging - showing willys x/y sprite values
            char ch[3] = "0";
            sprintf(ch, "%d", willy.x - xOffsetPixel);
            VDP_drawText(ch, xOffset + 2, yOffset);
            sprintf(ch, "%d", willy.y - yOffsetPixel);
            VDP_drawText(ch, xOffset + 6, yOffset);
        }
        //23/8/23 removed below while testing key loading for each level
        /*if (counter % 4 == 0){
            lv1Baddie.xPos += lv1Baddie.moveIncrement;
            if (lv1Baddie.xPos - 16 >= lv1Baddie.xEnd || lv1Baddie.xPos <= lv1Baddie.xStart){
                lv1Baddie.moveIncrement = lv1Baddie.moveIncrement * - 1;
                lv1Baddie.facingLeft = !lv1Baddie.facingLeft;
            }
            counter = 0;
        }*/
        counter ++;
        SYS_doVBlankProcess();
    }
    SPR_clear();
    VDP_clearSprites();
    //below for clearing collision debugging display
    VDP_drawText("                      ", xOffset + 2, yOffset); 
    VDP_drawText("                      ", xOffset + 2, yOffset + 2);
    VDP_drawText("                      ", xOffset + 4, yOffset + 2);
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
    //so only check the controls when player is doing neither
    //if you walk off a platform then player should fall and lock controls out
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
            lvNumber += 1;
            if (lvNumber > 19){
                lvNumber = 0;
            }
            drawHud();
            loadLevel();
            SYS_doVBlankProcess();
        }
    }
    else if (willy.pJumpOrFall == FALL){
        //this covers walking off the edge of a plaform
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
u8 convertPixelValueToTile(u16 value){
    return value / 8; //divide by by 8
};
void pCollisions(u16 x, u16 y){
    if (collideLeft(x, y) || collideRight(x, y)){
        willy.pMovements = STAND;
    }
}
u8 collideDown(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 3 - xOffsetPixel);
    u8 x2 = convertPixelValueToTile(x + 14 - xOffsetPixel);
    u8 y1 = convertPixelValueToTile((y + 16) - yOffsetPixel);
    u8 tileL = checkCollisionMap(x1, y1);
    u8 tileR = checkCollisionMap(x2, y1);

    /*char ch[3] = "000"; 
    sprintf(ch, "%d", x1);
    VDP_drawText(ch, xOffset + 2, yOffset + 3 );
    sprintf(ch, "%d", y1);
    VDP_drawText(ch, xOffset + 4, yOffset + 3 );
    sprintf(ch, "%d", tileL);
    VDP_drawText(ch, xOffset + 2, yOffset + 4 );
    sprintf(ch, "%d", tileR);
    VDP_drawText(ch, xOffset + 4, yOffset + 4 );*/
    
    if (tileL != NOTILE || tileR != NOTILE){
        return 1;
    }
    else{
        return 0;
    }
};
u8 collideUp(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 3 - xOffsetPixel);
    u8 x2 = convertPixelValueToTile(x + 14 - xOffsetPixel);
    u8 y1 = convertPixelValueToTile(y + 0 - yOffsetPixel);
    u8 tileL = checkCollisionMap(x1, y1);
    u8 tileR = checkCollisionMap(x2, y1);
    /*u8 tileL = levelMap[y1 - 1][x1];
    u8 tileR = levelMap[y1 - 1][x2];*/
    /*char ch[3] = "000"; 
    sprintf(ch, "%d", x1);
    VDP_drawText(ch, xOffset + 2, yOffset + 3 );
    sprintf(ch, "%d", y1);
    VDP_drawText(ch, xOffset + 4, yOffset + 3 );
    sprintf(ch, "%d", tileL);
    VDP_drawText(ch, xOffset + 2, yOffset + 4 );
    sprintf(ch, "%d", tileR);
    VDP_drawText(ch, xOffset + 4, yOffset + 4 );*/
    if (tileL == BRICK || tileR == BRICK){
        return 1;
    }
    else{
        return 0;
    }
};
u8 collideLeft(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 3 - xOffsetPixel);
    u8 y1 = convertPixelValueToTile(y + 8 - yOffsetPixel);
    u8 tileB = checkCollisionMap(x1, y1);
    if (tileB == BRICK){
        willy.x += 1;
        return 1;
    }
    else{
        //VDP_drawText("               ", xOffset + 1, yOffset + 2);
        return 0;
    }
};
u8 collideRight(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 14 - xOffsetPixel);
    u8 y1 = convertPixelValueToTile(y + 8 - yOffsetPixel);
    //u8 tileT = levelMap[y1][x1];
    u8 tileB = checkCollisionMap(x1, y1);
    if (tileB == BRICK){
        //VDP_drawText("Collision RIGHT", xOffset + 1, yOffset + 2);
        willy.x -=1;
        return 1;
    }
    else{
        //VDP_drawText("               ", xOffset + 1, yOffset + 2);
        return 0;
    }
}
u8 checkCollisionMap(u8 x, u8 y){
    u8 ret = allCms[(lvNumber * tilesPerLevel) + (x + xLvTileWidth*y)];
    return ret;
}
