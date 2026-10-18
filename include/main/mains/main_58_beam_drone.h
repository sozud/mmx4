#ifndef MAIN_MAINS_MAIN_58_BEAM_DRONE_H
#define MAIN_MAINS_MAIN_58_BEAM_DRONE_H

void beam_drone_update(struct MainObj* arg0);

void func_80074438(struct MainObj*);
void func_800745E8(struct MainObj*);

void beam_drone_spawn_beam(struct VisualObj* arg0);
void beam_drone_spawn_charge(struct AnimatedObj*);

extern void* beam_drone_animations[12];

#endif
