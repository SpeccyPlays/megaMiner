#ifndef LEVELS_H   /* Include guard */
#define LEVELS_H
#include <genesis.h>
#include <resources.h>
#include "baddie.h"

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