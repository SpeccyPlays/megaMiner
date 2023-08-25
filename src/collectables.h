#ifndef COLLECTABLES_H   /* Include guard */
#define COLLECTABLES_H
#include <genesis.h>
#include <resources.h>

/*
Need to make sure keys are all individual objects so we can remove them when collected by player
*/

typedef struct {
    u16 x;
    u16 y;
} CoOrds;
typedef struct {
    Sprite *kSprite;
    const SpriteDefinition *kSpriteDef;
    CoOrds xy;
} Key;

typedef struct {
    u8 numOfKeys;
    Key tKeys[];
} Keys;

Keys lv1Keys = {5, {{NULL, &key, {.x=240,.y=48}}, {NULL, &key, {.x=72,.y=0}}, {NULL, &key, {.x=128,.y=8}}, 
                {NULL, &key, {.x=192,.y=32}}, {NULL, &key, {.x=232, .y=0}}}};
Keys lv2Keys = {5, {{NULL, &kbat,{.x=24,.y=72}}, {NULL, &kbat,{.x=152,.y=96}}, {NULL, &kbat,{.x=56,.y=8}}, 
                {NULL, &kbat,{.x=192,.y=8}}, {NULL, &kbat,{.x=208, .y=56}}}};
Keys lv3Keys = {5, {{NULL, &key,{.x=168, .y=48}}, {NULL, &key,{.x=240,.y=48}}, {NULL, &key,{.x=48,.y=0}}, 
                {NULL, &key,{.x=120,.y=0}}, {NULL, &key,{.x=184,.y=0}}}};
Keys lv4Keys = {5, {{NULL, &key,{.x=8,.y=0}}, {NULL, &key,{.x=96,.y=8}}, {NULL, &key,{.x=128,.y=48}}, 
                {NULL, &key,{.x=200,.y=8}}, {NULL, &key,{.x=240,.y=48}}}};
Keys lv5Keys = {5, {{NULL, &key,{.x=56,.y=96}}, {NULL, &key,{.x=72,.y=96}}, {NULL, &key,{.x=72,.y=48}}, 
                {NULL, &key,{.x=232,.y=56}}, {NULL, &key,{.x=240,.y=8}}}};
Keys lv6Keys = {5, {{NULL, &key,{.x=8,.y=80}}, {NULL, &key,{.x=104,.y=88}}, {NULL, &key,{.x=120,.y=48}}, 
                {NULL, &key,{.x=136,.y=48}}, {NULL, &key,{.x=240,.y=56}}}};
Keys lv7Keys = {5, {{NULL, &key,{.x=152,.y=80}}, {NULL, &key,{.x=160,.y=48}}, {NULL, &key,{.x=216,.y=56}}, 
                {NULL, &key,{.x=240,.y=24}}, {NULL, &key,{.x=240,.y=88}}}};
Keys lv8Keys = {4, {{NULL, &kbanana,{.x=16,.y=64}}, {NULL, &kbanana,{.x=112,.y=48}}, {NULL, &kbanana,{.x=104,.y=16}}, 
                {NULL, &kbanana,{.x=232,.y=104}}}};
Keys lv9Keys = {1, {{NULL, &key,{128,8}}}};
Keys lv10Keys = {5, {{NULL, &kbauble,{.x=112,.y=8}}, {NULL, &kbauble,{.x=96,.y=48}}, {NULL, &kbauble,{.x=144,.y=64}}, 
                {NULL, &kbauble,{.x=168,.y=16}}, {NULL, &kbauble,{.x=240,.y=8}}}};
Keys lv11Keys = {5, {{NULL, &kp10,{.x=8,.y=32}}, {NULL, &kp10,{.x=152,.y=48}}, {NULL, &kp10,{.x=192,.y=0}}, 
                {NULL, &kp10,{.x=240,.y=8}}, {NULL, &kp10,{.x=240,.y=104}}}};
Keys lv12Keys = {5, {{NULL, &kbanana,{.x=16,.y=48}}, {NULL, &kbanana,{.x=120,.y=24}}, {NULL, &kbanana,{.x=128,.y=56}}, 
                {NULL, &kbanana,{.x=208,.y=40}}, {NULL, &kbanana,{.x=232,.y=104}}}};
Keys lv13Keys = {5, {{NULL, &knoidea,{.x=80,.y=48}}, {NULL, &knoidea,{.x=88,.y=96}}, {NULL, &knoidea,{.x=152,.y=72}}, 
                {NULL, &knoidea,{.x=208,.y=24}}, {NULL, &knoidea,{.x=208,.y=72}}}};
Keys lv14Keys = {4, {{NULL, &kchips,{.x=24,.y=64}}, {NULL, &kchips,{.x=128,.y=56}}, {NULL, &kchips,{.x=216,.y=56}}, 
                {NULL, &kchips,{.x=184,.y=16}}}};
Keys lv15Keys = {3, {{NULL, &kmoney,{.x=208,.y=112}}, {NULL, &kmoney,{.x=200,.y=16}}, {NULL, &kmoney,{.x=104,.y=48}}}};
Keys lv16Keys = {4, {{NULL, &ksquares,{.x=104,.y=56}}, {NULL, &ksquares,{.x=156,.y=80}}, {NULL, &ksquares,{.x=8,.y=0}}, 
                {NULL, &ksquares,{.x=240,.y=16}}}};
Keys lv17Keys = {5, {{NULL, &key,{.x=8,.y=72}}, {NULL, &key,{.x=120,.y=56}}, {NULL, &key,{.x=152,.y=80}}, 
                    {NULL, &key,{.x=192,.y=40}}, {NULL, &key,{.x=208,.y=88}}}};
Keys lv18Keys = {1, {{NULL, &key,{.x=128,.y=8}}}};
Keys lv19Keys = {2, {{NULL, &key,{.x=8,.y=40}}, {NULL, &key,{.x=240,.y=8}}}};
Keys lv20Keys = {5, {{NULL, &key,{.x=80,.y=88}}, {NULL, &key,{.x=112,.y=88}}, {NULL, &key,{.x=152,.y=88}}, 
                    {NULL, &key,{.x=184,.y=40}}, {NULL, &key,{.x=240,.y=48}}}};

Keys *allLvKeys[] = {&lv1Keys, &lv2Keys, &lv3Keys, &lv4Keys, &lv5Keys, &lv6Keys, &lv7Keys, &lv8Keys, &lv9Keys,
                    &lv10Keys, &lv11Keys, &lv12Keys, &lv13Keys, &lv14Keys, &lv15Keys, &lv16Keys, &lv17Keys, 
                    &lv18Keys, &lv19Keys, &lv20Keys};
#endif