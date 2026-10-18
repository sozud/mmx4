#ifndef MAIN_MAINS_MAIN_32_BOMB_BAT_H
#define MAIN_MAINS_MAIN_32_BOMB_BAT_H

void bomb_bat_update(struct MainObj* arg0);

void func_8005C860(struct MainObj*);
void bomb_bat_main(struct MainObj*);

void func_8005CB90(struct MainObj*);

// bomb_bat_dive_funcs
void func_8005CF9C(struct MainObj*);

extern struct Unk_unk68 bomb_bat_body_box;

void bomb_bat_drop_bomb(struct MainObj*);

extern union AnimationStep* bomb_bat_animations[8];
extern struct Unk_unk68 D_800FDC88[2];

#endif
