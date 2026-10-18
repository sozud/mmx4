#ifndef MAIN_MAINS_MAIN_10_DRAGONFLY_H
#define MAIN_MAINS_MAIN_10_DRAGONFLY_H

void dragonfly_update(struct MainObj* arg0);

void dragonfly_init(struct MainObj*);

void func_80049E68(struct MainObj* arg0);

void dragonfly_hunt_close(struct MainObj* arg0);

void func_8004A178(struct MainObj* arg0);

void dragonfly_carry_rise(struct MainObj* arg0);

u8 dragonfly_tile_above(struct MainObj*);
void dragonfly_carry_squeeze(struct MainObj* arg0);

extern u8 dragonfly_body_boxes[8];
extern u8 dragonfly_grab_box[4];

extern struct Unk_unk68 dragonfly_terrain_box;

extern const u8* dragonfly_animations[12];

#endif
