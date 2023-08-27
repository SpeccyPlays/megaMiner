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

//used for keeping track of what tiles are loaded in VRAM
u16 ind = TILE_USERINDEX;
u16 baseInd = TILE_USERINDEX;
//sprite stuff
Sprite *boot = NULL;
//game stuff
enum state gameState = INTRO;
u8 lvNumber = 0;
u8 numOfLvs = 20;
u8 keyCounter = 0;
//level sprites
//declarations
void applyOffsets();
void playIntro();
void drawHud();
void updateHud();
void loadLevel();
void loadPlayer();
void loadBaddies();
void loadKeys();
void playGame();
void moveBaddies();
void baddieCollisionDetect();
void keyCollisionDetect();
void ckAmountOfKeysCollected();
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
    applyOffsets();
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
void applyOffsets(){
    /*
    Due to the fact the zx spectrum had a smaller screen than the Megadrive
    We need to have offsets to center the screen
    All sprites need this offset applied so better to do once here
    then we don't need to worry about it again
    */
    xOffsetPixel = xOffset * 8;
    yOffsetPixel = yOffset * 8;
    for (u8 lv =0; lv < numOfLvs; lv ++){
        for (u8 i = 0; i < allLvBaddies[lv]->numOfBaddies; i++){
            allLvBaddies[lv]->Baddies[i].xStart += xOffsetPixel;
            allLvBaddies[lv]->Baddies[i].xEnd += xOffsetPixel;
            allLvBaddies[lv]->Baddies[i].yStart += yOffsetPixel;
            allLvBaddies[lv]->Baddies[i].yEnd += yOffsetPixel;
            allLvBaddies[lv]->Baddies[i].xLvStart += xOffsetPixel;
            allLvBaddies[lv]->Baddies[i].yLvStart += yOffsetPixel;
        }
        for (u8 i = 0; i < allLvKeys[lv]->numOfKeys; i++){
            allLvKeys[lv]->tKeys[i].xy.x += xOffsetPixel;
            allLvKeys[lv]->tKeys[i].xy.y += yOffsetPixel;
        }
        playerLvStart[lv].x += xOffsetPixel;
        playerLvStart[lv].y += yOffsetPixel;
    }
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
    /*
    Draw the score area at the bottom of the screen
    */
    ind = baseInd; //so we're overwriting previous level data instead of filling all memory with level data
    VDP_drawImageEx(BG_B, &HUD, TILE_ATTR_FULL(PAL0, TRUE, FALSE, FALSE, ind), 0+xOffset, 16+yOffset, FALSE, TRUE);
    ind += HUD.tileset->numTile;
    VDP_clearTextArea(xOffset, yOffset, 32, 168);
};
void updateHud(){
    /*
    Add the data to the score area
    */
    VDP_setPaletteColor(15, RGB8_8_8_TO_VDPCOLOR(255, 255, 255));
    VDP_drawText(levelNames[lvNumber], xOffset, 16 + yOffset);
    VDP_drawText("AIR", 0 + xOffset, 17 + yOffset);
    VDP_drawText("High Score", 0 + xOffset, 18 + yOffset);
    VDP_drawText("Score", 21 + xOffset, 18 + yOffset);
}
void loadLevel(){
    /*
    Doesn't need much of an explanation - initilise the sprite engine, draw the level, start the music
    Load ALL the sprites
    */
    SPR_init(0, 0, 0);
    VDP_drawImageEx(BG_B, levelsBG[lvNumber], TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0+xOffset, 0+yOffset, FALSE, TRUE);
    XGM_setLoopNumber(-1);
    XGM_startPlay(&megaMinerMain);
    loadPlayer();
    loadBaddies();
    loadKeys();
    updateHud();
    keyCounter = 0;
};
void loadPlayer(){
    /*
    Does what it says on the tin. Loads player
    */
   willy.x = playerLvStart[lvNumber].x;
   willy.y = playerLvStart[lvNumber].y;
   willy.facingLeft = playerLvStart[lvNumber].facingLeft;
   willy.pSprite = SPR_addSprite(willy.pSpriteDef, willy.x, willy.y, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
}
void loadBaddies(){
    /*
    Does what it says on the tin. Loads baddies for the level we're on
    */
    for (u8 i = 0; i < allLvBaddies[lvNumber]->numOfBaddies; i++){
        allLvBaddies[lvNumber]->Baddies[i].xPos = allLvBaddies[lvNumber]->Baddies[i].xLvStart;
        allLvBaddies[lvNumber]->Baddies[i].yPos = allLvBaddies[lvNumber]->Baddies[i].yLvStart;
        allLvBaddies[lvNumber]->Baddies[i].eSprite = SPR_addSprite(allLvBaddies[lvNumber]->Baddies[i].bdSpriteDef, allLvBaddies[lvNumber]->Baddies[i].xPos, allLvBaddies[lvNumber]->Baddies[i].yPos, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    }
};
void loadKeys(){
    /*
    Does what it says on the tin. Loads keys for the level we're on
    Make sure the option to show them is true
    */
    for (u8 i = 0; i < allLvKeys[lvNumber]->numOfKeys; i++){
        allLvKeys[lvNumber]->tKeys[i].kSprite = SPR_addSprite(allLvKeys[lvNumber]->tKeys[i].kSpriteDef, allLvKeys[lvNumber]->tKeys[i].xy.x, allLvKeys[lvNumber]->tKeys[i].xy.y, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
        allLvKeys[lvNumber]->tKeys[i].kShow = TRUE;
    }
};
void playGame(){
    loadLevel();
    u8 counter = 0;
    while(gameState == PLAY)
    {
        //using a counter too slow the play down so it's more like the original
        if (counter % 2 == 0){
            handleInput();
            if (willy.pMovements == WALKLEFT){
                willy.facingLeft = TRUE;
            }
            else if(willy.pMovements == WALKRIGHT){
                willy.facingLeft = FALSE;
            }
            SPR_setPosition(willy.pSprite,willy.x,willy.y); 
            SPR_setHFlip(willy.pSprite, willy.facingLeft);
            SPR_setAnim(willy.pSprite, willy.currentSpriteNum);
            //below for debugging - showing willys x/y sprite values
            char ch[3] = "0";
            sprintf(ch, "%d", willy.x - xOffsetPixel);
            VDP_drawText(ch, xOffset + 2, yOffset);
            sprintf(ch, "%d", willy.y - yOffsetPixel);
            VDP_drawText(ch, xOffset + 6, yOffset);
            ch[3] = "0";
            sprintf(ch, "%d", keyCounter);
            VDP_drawText(ch, xOffset + 2, yOffset+ 1);
        }
        keyCollisionDetect();
        baddieCollisionDetect();
        ckAmountOfKeysCollected();
        if (counter % 4 == 0){
            VDP_drawText("                      ", xOffset + 2, yOffset + 2);
            moveBaddies();
            counter = 0;
        }
        SPR_update();
        counter ++;
        SYS_doVBlankProcess();
    }
    SPR_clear();
    VDP_clearSprites();
    //below for clearing collision debugging display
    VDP_drawText("                      ", xOffset + 2, yOffset); 
    VDP_drawText("                      ", xOffset + 2, yOffset + 1);
    VDP_drawText("                      ", xOffset + 2, yOffset + 2);
};
void moveBaddies(){
    /*
    Check all baddies for this level to see if they're at either end of their patrol
    If so, change direction and the way the sprite is facing
    */
    for (u8 i = 0; i < allLvBaddies[lvNumber]->numOfBaddies; i++){
        if (!allLvBaddies[lvNumber]->Baddies[i].yMove){
            allLvBaddies[lvNumber]->Baddies[i].xPos += allLvBaddies[lvNumber]->Baddies[i].moveIncrement;
            if (allLvBaddies[lvNumber]->Baddies[i].xPos >= allLvBaddies[lvNumber]->Baddies[i].xEnd || allLvBaddies[lvNumber]->Baddies[i].xPos <= allLvBaddies[lvNumber]->Baddies[i].xStart){
                allLvBaddies[lvNumber]->Baddies[i].moveIncrement = allLvBaddies[lvNumber]->Baddies[i].moveIncrement * - 1;
                allLvBaddies[lvNumber]->Baddies[i].facingLeft = !allLvBaddies[lvNumber]->Baddies[i].facingLeft;
            }
        }
        else {
            allLvBaddies[lvNumber]->Baddies[i].yPos += allLvBaddies[lvNumber]->Baddies[i].moveIncrement;
            if (allLvBaddies[lvNumber]->Baddies[i].yPos >= allLvBaddies[lvNumber]->Baddies[i].yEnd || allLvBaddies[lvNumber]->Baddies[i].yPos <= allLvBaddies[lvNumber]->Baddies[i].yStart){
                allLvBaddies[lvNumber]->Baddies[i].moveIncrement = allLvBaddies[lvNumber]->Baddies[i].moveIncrement * - 1;
            }
        }
        SPR_setPosition(allLvBaddies[lvNumber]->Baddies[i].eSprite,allLvBaddies[lvNumber]->Baddies[i].xPos, allLvBaddies[lvNumber]->Baddies[i].yPos);
        SPR_setHFlip(allLvBaddies[lvNumber]->Baddies[i].eSprite, allLvBaddies[lvNumber]->Baddies[i].facingLeft);
    }
}
void baddieCollisionDetect(){
    /*
    Check through baddie positions for current level to see if they hit willy
    */
    for (u8 i = 0; i < allLvBaddies[lvNumber]->numOfBaddies; i++){
        if((willy.x > allLvBaddies[lvNumber]->Baddies[i].xPos + 4) & (willy.x < allLvBaddies[lvNumber]->Baddies[i].xPos + 12) & 
            (willy.y + 2 > allLvBaddies[lvNumber]->Baddies[i].yPos) & (willy.y < allLvBaddies[lvNumber]->Baddies[i].yPos + 14)){
            VDP_drawText("        XHIT          ", xOffset + 2, yOffset + 2);  
        }
        else if ((willy.x + 12 > allLvBaddies[lvNumber]->Baddies[i].xPos + 4) & (willy.x + 12 < allLvBaddies[lvNumber]->Baddies[i].xPos + 12) & 
            (willy.y + 2 > allLvBaddies[lvNumber]->Baddies[i].yPos) & (willy.y < allLvBaddies[lvNumber]->Baddies[i].yPos + 14)){
            VDP_drawText("        XHIT          ", xOffset + 2, yOffset + 2); 
        }
        else if((willy.x > allLvBaddies[lvNumber]->Baddies[i].xPos + 4) & (willy.x < allLvBaddies[lvNumber]->Baddies[i].xPos + 12) & 
            (willy.y + 14 > allLvBaddies[lvNumber]->Baddies[i].yPos) & (willy.y + 14 < allLvBaddies[lvNumber]->Baddies[i].yPos + 14)){
            VDP_drawText("        XHIT          ", xOffset + 2, yOffset + 2);  
        }
        else if ((willy.x + 12 > allLvBaddies[lvNumber]->Baddies[i].xPos + 4) & (willy.x + 12 < allLvBaddies[lvNumber]->Baddies[i].xPos + 12) & 
            (willy.y + 14 > allLvBaddies[lvNumber]->Baddies[i].yPos) & (willy.y + 14 < allLvBaddies[lvNumber]->Baddies[i].yPos + 14)){
            VDP_drawText("        XHIT          ", xOffset + 2, yOffset + 2); 
        }
    }
};
void keyCollisionDetect(){
    /*
    Loop through a levels keys to see if willy has hit any that are still displayed
    If so, remove sprite from memory and set it to not show anytmore
    */

    for (u8 i = 0; i < allLvKeys[lvNumber]->numOfKeys; i++){
        if((willy.x + 3 > allLvKeys[lvNumber]->tKeys[i].xy.x) & (willy.x + 3 < allLvKeys[lvNumber]->tKeys[i].xy.x + 8) & 
            (willy.y + 1 > allLvKeys[lvNumber]->tKeys[i].xy.y) & (willy.y < allLvKeys[lvNumber]->tKeys[i].xy.y + 8) &
            (allLvKeys[lvNumber]->tKeys[i].kShow == TRUE)){
            allLvKeys[lvNumber]->tKeys[i].kShow = FALSE;
            keyCounter ++;
            SPR_releaseSprite(allLvKeys[lvNumber]->tKeys[i].kSprite);
        }
        else if ((willy.x + 12 > allLvKeys[lvNumber]->tKeys[i].xy.x) & (willy.x + 12 < allLvKeys[lvNumber]->tKeys[i].xy.x + 8) & 
            (willy.y + 1> allLvKeys[lvNumber]->tKeys[i].xy.y) & (willy.y < allLvKeys[lvNumber]->tKeys[i].xy.y + 8) &
            (allLvKeys[lvNumber]->tKeys[i].kShow == TRUE)){
            allLvKeys[lvNumber]->tKeys[i].kShow = FALSE;
            keyCounter ++;
            SPR_releaseSprite(allLvKeys[lvNumber]->tKeys[i].kSprite);
        }
        else if((willy.x + 3 > allLvKeys[lvNumber]->tKeys[i].xy.x) & (willy.x + 3 < allLvKeys[lvNumber]->tKeys[i].xy.x + 8) & 
            (willy.y + 14 > allLvKeys[lvNumber]->tKeys[i].xy.y) & (willy.y + 14 < allLvKeys[lvNumber]->tKeys[i].xy.y + 8) &
            (allLvKeys[lvNumber]->tKeys[i].kShow == TRUE)){
            allLvKeys[lvNumber]->tKeys[i].kShow = FALSE;
            keyCounter ++;
            SPR_releaseSprite(allLvKeys[lvNumber]->tKeys[i].kSprite);
        }
        else if ((willy.x + 12 > allLvKeys[lvNumber]->tKeys[i].xy.x) & (willy.x + 12 < allLvKeys[lvNumber]->tKeys[i].xy.x + 8) & 
            (willy.y + 14 > allLvKeys[lvNumber]->tKeys[i].xy.y) & (willy.y + 14 < allLvKeys[lvNumber]->tKeys[i].xy.y + 8) &
            (allLvKeys[lvNumber]->tKeys[i].kShow == TRUE)){
            allLvKeys[lvNumber]->tKeys[i].kShow = FALSE;
            keyCounter ++;
            SPR_releaseSprite(allLvKeys[lvNumber]->tKeys[i].kSprite); 
        }
    }
};
void ckAmountOfKeysCollected(){
    if (keyCounter >= allLvKeys[lvNumber]->numOfKeys){
        lvNumber ++;
        loadLevel();
    }
}
void showDeathSequence(){
    /*
    The squashing boot when willy is out of lives
    */
    SPR_init(0, 0, 0);
    drawHud();
    VDP_drawImageEx(BG_B, &deathScreen, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0+xOffset, 0+yOffset, FALSE, TRUE);
    ind += deathScreen.tileset->numTile;
    boot = SPR_addSprite(&deathBoot, (16 + xOffset) * 8, (yOffset) * 8, TILE_ATTR(PAL0, TRUE, FALSE, FALSE));
    for (u16 j = 0; j < 90; j++){
        SPR_update();
        SYS_doVBlankProcess();
    }
    SPR_clear();
    gameState = INTRO;
    VDP_clearSprites();
};
void handleInput(){
    /*
    In the original you can't change direction of the jump or when falling
    so only check the controls when player is doing neither
    if you walk off a platform then player should fall and lock controls out
    */
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
            SPR_clear();
            VDP_clearSprites();
            drawHud();
            loadLevel();
            SYS_doVBlankProcess();
        }
        else if (value & BUTTON_A){
            lvNumber = 0;
            showDeathSequence();
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
    return value / 8; 
};
void pCollisions(u16 x, u16 y){
    if (collideLeft(x, y) || collideRight(x, y)){
        willy.pMovements = STAND;
    }
};
u8 collideDown(u16 x, u16 y){
    u8 x1 = convertPixelValueToTile(x + 3 - xOffsetPixel);
    u8 x2 = convertPixelValueToTile(x + 14 - xOffsetPixel);
    u8 y1 = convertPixelValueToTile((y + 16) - yOffsetPixel);
    u8 tileL = checkCollisionMap(x1, y1);
    u8 tileR = checkCollisionMap(x2, y1);
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
};
u8 checkCollisionMap(u8 x, u8 y){
    u8 ret = allCms[(lvNumber * tilesPerLevel) + (x + xLvTileWidth*y)];
    return ret;
};
