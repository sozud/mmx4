#ifndef MAIN_MAINS_MAIN_60_STORM_OWL_H
#define MAIN_MAINS_MAIN_60_STORM_OWL_H

// storm_owl_patrol_funcs
typedef struct {
    s16 x;
    s16 y;
    s32 vx;
    s32 vy;
} Main60Waypoint;

void storm_owl_update(struct MainObj *arg0);

void func_80075320(struct MainObj*);

void storm_owl_start_warning(struct MainObj*);

void storm_owl_spawn_roar(struct AnimatedObj* arg0);
void storm_owl_spawn_feather(struct MainObj* arg0);
void storm_owl_spawn_intro_wind(struct MainObj* self);
void storm_owl_spawn_volley_feather(struct MainObj* self, s8 count);
void func_80078314(struct MainObj* arg0);
void storm_owl_choose_corner(struct MainObj* arg0);
void storm_owl_choose_pattern(struct MainObj*);

void storm_owl_death_explode(struct MainObj*);

void func_80075C6C(struct MainObj*);

extern Main60Waypoint storm_owl_waypoints[];

void func_80075E78(struct MainObj*);

void func_800760C4(struct MainObj*);

void func_80076364(struct MainObj*);
void func_8007651C(struct MainObj*);

void storm_owl_reenter_warp(struct MainObj*);

void storm_owl_storm_rain_again(struct MainObj*);

void storm_owl_spawn_cyclones(struct MainObj*);
void storm_owl_clear_shots(void);

extern void* storm_owl_animations[30];

extern struct Unk_unk68 storm_owl_attack_box;
extern struct Unk_unk68 storm_owl_slam_terrain_box;

void storm_owl_spawn_storm_charge(struct AnimatedObj*);

extern struct Unk_unk68 storm_owl_hurt_box;

#endif
