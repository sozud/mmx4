#ifndef MAIN_MAINS_MAIN_65_MAGMA_DRAGOON_H
#define MAIN_MAINS_MAIN_65_MAGMA_DRAGOON_H

void magma_dragoon_update(struct MainObj* arg0);

void magma_dragoon_intro_warning(struct MainObj*);
void magma_dragoon_spawn_flames(struct AnimatedObj*, u32);

void func_8007E6F8(struct MainObj*);

void func_8007E95C(struct MainObj*);

void magma_dragoon_fire_volley_fire(struct MainObj*);

void magma_dragoon_breath_fire(struct MainObj*);

void func_8007F174(struct MainObj*);

void func_8007F404(struct MainObj*);

void func_8007F5B0(struct MainObj*);

void func_8007F780(struct MainObj*);

void func_8007FAA4(struct MainObj*);

void func_8007E4C8(struct MainObj* arg0);

void func_8007FF00(struct MainObj*);
void func_8007FFFC(struct MainObj*);

void func_8007DD98(struct MainObj*);
void func_8007FD24(struct MainObj*);

extern struct Unk_unk68 magma_dragoon_hurt_box;

extern struct Unk_unk68 magma_dragoon_attack_box;

void magma_dragoon_spawn_flames(struct AnimatedObj*, u32);

#endif
