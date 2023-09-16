#ifndef COLLECTABLES_H   /* Include guard */
#define COLLECTABLES_H
#include <genesis.h>
#include <resources.h>
#include "globalstruct.h"

/*
Need to make sure keys are all individual objects so we can remove them when collected by player
*/


typedef struct {
    Sprite *kSprite;
    const SpriteDefinition *kSpriteDef;
    CoOrds xy;
    bool kShow;
} Key;

typedef struct {
    u8 numOfKeys;
    Key tKeys[];
} Keys;

Keys lv1Keys = {5, {{NULL, &key, {.x=240,.y=48}, TRUE}, {NULL, &key, {.x=72,.y=0}, TRUE}, {NULL, &key, {.x=128,.y=8}, TRUE}, 
                {NULL, &key, {.x=192,.y=32}, TRUE}, {NULL, &key, {.x=232, .y=0}, TRUE}}};
Keys lv2Keys = {5, {{NULL, &kbat,{.x=24,.y=72}, TRUE}, {NULL, &kbat,{.x=152,.y=96}, TRUE}, {NULL, &kbat,{.x=56,.y=8}, TRUE}, 
                {NULL, &kbat,{.x=192,.y=8}, TRUE}, {NULL, &kbat,{.x=208, .y=56}, TRUE}}};
Keys lv3Keys = {5, {{NULL, &key,{.x=168, .y=48}, TRUE}, {NULL, &key,{.x=240,.y=48}, TRUE}, {NULL, &key,{.x=48,.y=0}, TRUE}, 
                {NULL, &key,{.x=120,.y=0}, TRUE}, {NULL, &key,{.x=184,.y=0}, TRUE}}};
Keys lv4Keys = {5, {{NULL, &key,{.x=8,.y=0}, TRUE}, {NULL, &key,{.x=96,.y=8}, TRUE}, {NULL, &key,{.x=128,.y=48}, TRUE}, 
                {NULL, &key,{.x=200,.y=8}, TRUE}, {NULL, &key,{.x=240,.y=48}, TRUE}}};
Keys lv5Keys = {5, {{NULL, &key,{.x=56,.y=96}, TRUE}, {NULL, &key,{.x=72,.y=96}, TRUE}, {NULL, &key,{.x=72,.y=48}, TRUE}, 
                {NULL, &key,{.x=232,.y=56}, TRUE}, {NULL, &key,{.x=240,.y=8}, TRUE}}};
Keys lv6Keys = {5, {{NULL, &key,{.x=8,.y=80}, TRUE}, {NULL, &key,{.x=104,.y=88}, TRUE}, {NULL, &key,{.x=120,.y=48}, TRUE}, 
                {NULL, &key,{.x=136,.y=48}, TRUE}, {NULL, &key,{.x=240,.y=56}, TRUE}}};
Keys lv7Keys = {5, {{NULL, &key,{.x=152,.y=80}, TRUE}, {NULL, &key,{.x=160,.y=48}, TRUE}, {NULL, &key,{.x=216,.y=56}, TRUE}, 
                {NULL, &key,{.x=240,.y=24}, TRUE}, {NULL, &key,{.x=240,.y=88}, TRUE}}};
Keys lv8Keys = {4, {{NULL, &kbanana,{.x=16,.y=64}, TRUE}, {NULL, &kbanana,{.x=112,.y=48}, TRUE}, {NULL, &kbanana,{.x=104,.y=16}, TRUE}, 
                {NULL, &kbanana,{.x=232,.y=104}, TRUE}}};
Keys lv9Keys = {1, {{NULL, &key,{128,8}, TRUE}}};
Keys lv10Keys = {5, {{NULL, &kbauble,{.x=112,.y=8}, TRUE}, {NULL, &kbauble,{.x=96,.y=48}, TRUE}, {NULL, &kbauble,{.x=144,.y=64}, TRUE}, 
                {NULL, &kbauble,{.x=168,.y=16}, TRUE}, {NULL, &kbauble,{.x=240,.y=8}, TRUE}}};
Keys lv11Keys = {5, {{NULL, &kp10,{.x=8,.y=32}, TRUE}, {NULL, &kp10,{.x=152,.y=48}, TRUE}, {NULL, &kp10,{.x=192,.y=0}, TRUE}, 
                {NULL, &kp10,{.x=240,.y=8}, TRUE}, {NULL, &kp10,{.x=240,.y=104}, TRUE}}};
Keys lv12Keys = {5, {{NULL, &kbanana,{.x=16,.y=48}, TRUE}, {NULL, &kbanana,{.x=120,.y=24}, TRUE}, {NULL, &kbanana,{.x=128,.y=56}, TRUE}, 
                {NULL, &kbanana,{.x=208,.y=40}, TRUE}, {NULL, &kbanana,{.x=232,.y=104}, TRUE}}};
Keys lv13Keys = {5, {{NULL, &knoidea,{.x=80,.y=48}, TRUE}, {NULL, &knoidea,{.x=88,.y=96}, TRUE}, {NULL, &knoidea,{.x=152,.y=72}, TRUE}, 
                {NULL, &knoidea,{.x=208,.y=24}, TRUE}, {NULL, &knoidea,{.x=208,.y=72}, TRUE}}};
Keys lv14Keys = {4, {{NULL, &kchips,{.x=24,.y=64}, TRUE}, {NULL, &kchips,{.x=128,.y=56}, TRUE}, {NULL, &kchips,{.x=216,.y=56}, TRUE}, 
                {NULL, &kchips,{.x=184,.y=16}, TRUE}}};
Keys lv15Keys = {3, {{NULL, &kmoney,{.x=208,.y=112}, TRUE}, {NULL, &kmoney,{.x=200,.y=16}, TRUE}, {NULL, &kmoney,{.x=104,.y=48}, TRUE}}};
Keys lv16Keys = {4, {{NULL, &ksquares,{.x=104,.y=56}, TRUE}, {NULL, &ksquares,{.x=156,.y=80}, TRUE}, {NULL, &ksquares,{.x=8,.y=0}, TRUE}, 
                {NULL, &ksquares,{.x=240,.y=16}, TRUE}}};
Keys lv17Keys = {5, {{NULL, &key,{.x=8,.y=72}, TRUE}, {NULL, &key,{.x=120,.y=56}, TRUE}, {NULL, &key,{.x=152,.y=80}, TRUE}, 
                    {NULL, &key,{.x=192,.y=40}, TRUE}, {NULL, &key,{.x=208,.y=88}, TRUE}}};
Keys lv18Keys = {1, {{NULL, &key,{.x=128,.y=8}, TRUE}}};
Keys lv19Keys = {2, {{NULL, &key,{.x=8,.y=40}, TRUE}, {NULL, &key,{.x=240,.y=8}, TRUE}}};
Keys lv20Keys = {5, {{NULL, &key,{.x=80,.y=88}, TRUE}, {NULL, &key,{.x=112,.y=88}, TRUE}, {NULL, &key,{.x=152,.y=88}, TRUE}, 
                    {NULL, &key,{.x=184,.y=40}, TRUE}, {NULL, &key,{.x=240,.y=48}, TRUE}}};

Keys *allLvKeys[] = {&lv1Keys, &lv2Keys, &lv3Keys, &lv4Keys, &lv5Keys, &lv6Keys, &lv7Keys, &lv8Keys, &lv9Keys,
                    &lv10Keys, &lv11Keys, &lv12Keys, &lv13Keys, &lv14Keys, &lv15Keys, &lv16Keys, &lv17Keys, 
                    &lv18Keys, &lv19Keys, &lv20Keys};
#endif