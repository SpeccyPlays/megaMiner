#ifndef LEVELS_H   /* Include guard */
#define LEVELS_H
#include <genesis.h>
#include <resources.h>
#include "baddie.h"
typedef struct {
    Image *lvBG_B; //main ground which has no animation
    u16 numOfEnemy;
    Enemy *lvEnemy;
    u8 levelMap[17][32]; //20 levels each 17 x 32 tiles (8x8 tile size)
    Sprite *lvSprites[8]; //animated tiles
} levelData;
const Image *levelsBG[20] = {&level1, &level2, &level3, &level4, &level5, &level6, &level7, &level8,
                            &level9, &level10, &level11, &level12, &level13, &level14, &level15, &level16,
                            &level17, &level18, &level19, &level20};
char *levelNames[] ={
	"Central Cavern",
	"The Cold Room",
	"The Menagerie",
	"Abandoned Uranium Workings",
	"Eugene's Lair",
	"Processing Plant", 
	"The Vat",
	"Miner Willy Meets The Kong Beast",
	"Wacky Amoebatrons",
	"The Endorian Forest",
	"Attack of the Mutant Telephones",
	"Return of the Alien Kong Beast",
	"Ore Refinery",
	"Skylab Landing Bay",
	"The Bank",
	"The Sixteenth Cavern",
	"The Warehouse",
	"Amoebatrons' Revenge",
	"Solar Power Generator",
	"The Final Barrier"
};

#endif