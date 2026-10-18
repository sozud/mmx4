#ifndef MAIN_MAINS_MAIN_19_SURFACE_HOPPER_H
#define MAIN_MAINS_MAIN_19_SURFACE_HOPPER_H

void surface_hopper_update(struct MainObj* arg0);

// surface_hopper_state_funcs
void func_800528BC(struct MainObj*);

// surface_hopper_launched_state_funcs
void func_80053D24(struct MainObj*);
void func_80053EB8(struct MainObj*);

void func_80052CB8(struct MainObj*);
void func_80052E94(struct MainObj*);
void surface_hopper_crawl_turn(struct MainObj*);

void func_80053338(struct MainObj*);

void func_8005368C(struct MainObj*);

// surface_hopper_launched_step_funcs
void surface_hopper_launch(struct MainObj* arg0);
void surface_hopper_set_launch(struct MainObj* arg0);
void func_8005402C(struct MainObj* arg0);
void func_8005402C(struct MainObj* arg0);
void func_8005402C(struct MainObj* arg0);

extern struct Unk_unk68* surface_hopper_launch_hurt_boxes[4];
extern struct Unk_unk68* surface_hopper_launch_attack_boxes[4];
extern struct Unk_unk68* surface_hopper_launch_terrain_boxes[4];
extern s16 surface_hopper_launch_x_speeds[8];
extern s16 surface_hopper_launch_y_speeds[8];
extern u8 surface_hopper_launch_facings[8];
extern u8 surface_hopper_launch_animations[8];

extern struct Unk_unk68* surface_hopper_attach_terrain_boxes[2];

#endif
