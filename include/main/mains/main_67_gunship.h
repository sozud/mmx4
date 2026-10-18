#ifndef MAIN_MAINS_MAIN_67_GUNSHIP_H
#define MAIN_MAINS_MAIN_67_GUNSHIP_H

void gunship_update(struct MainObj *arg0);

void func_80082574(struct MainObj*);

void gunship_spawn_bullet(struct MainObj*);
void gunship_spawn_exhaust(struct MainObj*);
s32 gunship_is_within(struct MainObj*, s32, s32);

void func_800828B4(struct MainObj*);

void gunship_spawn_missiles(struct VisualObj* arg0);

extern void* gunship_animations[29];

extern struct Unk_unk68 gunship_hurt_box;
extern struct Unk_unk68 gunship_terrain_box;

#endif
