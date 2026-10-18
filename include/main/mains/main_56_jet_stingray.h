#ifndef MAIN_MAINS_MAIN_56_JET_STINGRAY_H
#define MAIN_MAINS_MAIN_56_JET_STINGRAY_H

void jet_stingray_flyby_update(struct MainObj* arg0);
void jet_stingray_update(struct MainObj* arg0);

void jet_stingray_flyby_despawn(struct MainObj* arg0);
struct MainObj* func_8006FB20(struct MainObj*, s32, s32);

void jet_stingray_intro_warning(struct MainObj*);

void func_80070514(struct MainObj*);

void jet_stingray_vortex_spawn(struct MainObj*);
void func_80070A38(struct MainObj*);

// jet_stingray_ambush_funcs
extern struct Unk_unk68 jet_stingray_ambush_attack_box;

void jet_stingray_ambush_drop(struct MainObj*);
void jet_stingray_ambush_rise(struct MainObj*);
void jet_stingray_ambush_return(struct MainObj*);

void func_80071740(struct MainObj*);

void func_800710D4(struct MainObj* arg0);

void jet_stingray_death_explode(struct MainObj*);

void func_80071D30(struct MainObj*);

extern void* jet_stingray_animations[45];

extern struct Unk_unk68 jet_stingray_land_attack_box;
extern struct Unk_unk68 jet_stingray_land_hurt_box;
extern struct Unk_unk68 jet_stingray_terrain_box;

struct VisualObj* jet_stingray_spawn_splash(struct MainObj*);
u8 jet_stingray_check_surface(struct PlayerObj*, s32, s32);

#endif
