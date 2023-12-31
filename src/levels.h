#ifndef LEVELS_H   /* Include guard */
#define LEVELS_H
#include <genesis.h>
#include <resources.h>
#include "baddie.h"
#include "globalstruct.h"

typedef struct {
	/* data */
	CoOrds startPos;
	bool facingLeft;
} LvStart;

LvStart playerLvStart[] = {{{.x = 16, .y = 104}, FALSE},{{.x = 16, .y = 104}, FALSE},{{.x = 16, .y = 104}, FALSE},
							{{.x = 224, .y = 104}, TRUE},{{.x = 16, .y = 24}, FALSE}, {{.x = 128, .y = 24}, TRUE},
							{{.x = 16, .y = 104}, FALSE},{{.x = 16, .y = 104}, FALSE},{{.x = 8, .y = 104}, FALSE},
							{{.x = 8, .y = 32}, FALSE},{{.x = 24, .y = 8}, FALSE},{{.x = 16, .y = 104}, FALSE},
							{{.x = 232, .y = 104}, TRUE},{{.x = 232, .y = 104}, TRUE},{{.x = 16,.y = 104}, FALSE},
							{{.x = 16, .y = 104}, FALSE},{{.x = 16, .y = 24}, FALSE},{{.x = 232, .y = 104}, TRUE},
							{{.x = 104, .y = 48}, FALSE},{{.x = 224, .y = 104}, TRUE}};

CoOrds gatePos[] = {{.x = 232, .y = 104},{.x = 232, .y = 104},{.x = 232, .y = 88},{.x = 232, .y = 8},
					{.x = 120, .y = 104},{.x = 232, .y = 0}, {.x = 120, .y = 104},{.x = 120, .y = 104},
					{.x = 8, .y = 0},{.x = 96, .y = 104},{.x = 8, .y = 8},{.x = 120, .y = 104},{.x = 8, .y = 104},
					{.x = 120, .y = 0},{.x = 8, .y = 24},{.x = 96, .y = 40},{.x = 232, .y = 8},{.x = 232, .y = 0},
					{.x = 8, .y = 8},{.x = 152, .y = 40}};

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