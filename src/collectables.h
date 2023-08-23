#ifndef COLLECTABLES_H   /* Include guard */
#define COLLECTABLES_H
#include <genesis.h>
#include <resources.h>

typedef struct {
    u16 x;
    u16 y;
} CoOrds;
typedef struct {
    u8 numOfKeys;
    Sprite *keySprite;
    CoOrds xy[];
} Keys;

Keys lv1Keys = {5, NULL, {{.x=240,.y=48}, {.x=72,.y=0}, {.x=128,.y=8}, {.x=192,.y=32}, {.x=232, .y=0}}};
Keys lv2Keys = {5, NULL, {{.x=24,.y=72}, {.x=152,.y=96}, {.x=56,.y=8}, {.x=192,.y=8}, {.x=208, .y=56}}};
Keys lv3Keys = {5, NULL, {{.x=168, .y=48}, {.x=240,.y=48}, {.x=48,.y=0}, {.x=120,.y=0}, {.x=184,.y=0}}};
Keys lv4Keys = {5, NULL, {{.x=8,.y=0}, {.x=96,.y=8}, {.x=128,.y=48}, {.x=200,.y=8}, {.x=240,.y=48}}};
Keys lv5Keys = {5, NULL, {{.x=56,.y=96}, {.x=72,.y=96}, {.x=72,.y=48}, {.x=232,.y=56}, {.x=240,.y=8}}};
Keys lv6Keys = {5, NULL, {{.x=8,.y=80}, {.x=104,.y=88}, {.x=120,.y=48}, {.x=136,.y=48}, {.x=240,.y=56}}};
Keys lv7Keys = {5, NULL, {{.x=152,.y=80}, {.x=160,.y=48}, {.x=216,.y=56}, {.x=240,.y=24}, {.x=240,.y=88}}};
Keys lv8Keys = {4, NULL, {{.x=16,.y=64}, {.x=112,.y=48}, {.x=104,.y=16}, {.x=232,.y=104}}};
Keys lv9Keys = {1, NULL, {{128,8}}};
Keys lv10Keys = {5, NULL, {{.x=112,.y=8}, {.x=96,.y=48}, {.x=144,.y=64}, {.x=168,.y=16}, {.x=240,.y=8}}};
Keys lv11Keys = {5, NULL, {{.x=8,.y=32}, {.x=152,.y=48}, {.x=192,.y=0}, {.x=240,.y=8}, {.x=240,.y=104}}};
Keys lv12Keys = {5, NULL, {{.x=16,.y=48}, {.x=120,.y=24}, {.x=128,.y=56}, {.x=208,.y=40}, {.x=232,.y=104}}};
Keys lv13Keys = {5, NULL, {{.x=80,.y=48}, {.x=88,.y=96}, {.x=152,.y=72}, {.x=208,.y=24}, {.x=208,.y=72}}};
Keys lv14Keys = {4, NULL, {{.x=24,.y=64}, {.x=128,.y=56}, {.x=216,.y=56}, {.x=184,.y=16}}};
Keys lv15Keys = {3, NULL, {{.x=208,.y=112}, {.x=200,.y=16}, {.x=104,.y=48}}};
Keys lv16Keys = {4, NULL, {{.x=104,.y=56}, {.x=156,.y=80}, {.x=8,.y=0}, {.x=240,.y=16}}};
Keys lv17Keys = {5, NULL, {{.x=8,.y=72}, {.x=120,.y=56}, {.x=152,.y=80}, {.x=192,.y=40}, {.x=208,.y=88}}};
Keys lv18Keys = {1, NULL, {{.x=128,.y=8}}};
Keys lv19Keys = {2, NULL, {{.x=8,.y=40}, {.x=240,.y=8}}};
Keys lv20Keys = {5, NULL, {{.x=80,.y=88}, {.x=112,.y=88}, {.x=152,.y=88}, {.x=184,.y=40}, {.x=240,.y=48}}};

Keys *allLvKeys[] = {&lv1Keys, &lv2Keys, &lv3Keys, &lv4Keys, &lv5Keys, &lv6Keys, &lv7Keys, &lv8Keys, &lv9Keys
                    &lv10Keys, &lv11Keys, &lv12Keys, &lv13Keys, &lv14Keys, &lv15Keys, &lv16Keys, &lv17Keys, 
                    &lv18Keys, &lv19Keys, &lv20Keys};


#endif