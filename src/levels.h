#ifndef LEVELS_H   /* Include guard */
#define LEVELS_H
#include <genesis.h>
#include <resources.h>
#include "baddie.h"

typedef struct {
	/* data */
	u16 x;
	u16 y;
	bool facingLeft
} LvStart;

LvStart playerLvStart[] = {{16, 104, FALSE},{16, 104, FALSE},{16, 104, FALSE},{224, 104, TRUE},{16, 24, FALSE},
							{128, 24, TRUE},{16, 104, FALSE},{16, 104, FALSE},{8, 104, FALSE},{8, 32, FALSE},
							{24, 8, FALSE},{16, 104, FALSE},{232, 104, TRUE},{232, 104, TRUE},{16, 104, FALSE},
							{16, 104, FALSE},{16, 24, FALSE},{232, 104, TRUE},{104, 48, FALSE},{224, 104, TRUE}};



const Image *levelsBG[20] = {&level1, &level2, &level3, &level4, &level5, &level6, &level7, &level8,
                            &level9, &level10, &level11, &level12, &level13, &level14, &level15, &level16,
                            &level17, &level18, &level19, &level20};
char *levelNames[] ={
	//I've done the lazy method of centering these here rather than trying to do
	//clever code formatting
	//
	"          Central Cavern        ",
	"          The Cold Room         ",
	"          The Menagerie         ",
	"   Abandoned Uranium Workings   ",
	"          Eugene's Lair         ",
	"         Processing Plant       ", 
	"             The Vat            ",
	"Miner Willy Meets The Kong Beast",
	"         Wacky Amoebatrons      ",
	"        The Endorian Forest     ",
	"Attack of the Mutant Telephones ",
	" Return of the Alien Kong Beast ",
	"           Ore Refinery         ",
	"        Skylab Landing Bay      ",
	"            The Bank            ",
	"       The Sixteenth Cavern     ",
	"          The Warehouse         ",
	"       Amoebatrons' Revenge     ",
	"       Solar Power Generator    ",
	"        The Final Barrier       "
};



#endif