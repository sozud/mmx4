#ifndef MAIN_OBJECTS_H
#define MAIN_OBJECTS_H

// D_800F43A8
struct MainObj* find_free_main_obj(void);
struct WeaponObj* find_free_weapon_obj(void);
struct ShotObj* find_free_shot_obj(void);
struct VisualObj* find_free_visual_obj(void);
struct EffectObj* find_free_effect_obj(void);
struct ItemObj* find_free_item_obj(void);
struct MiscObj* find_free_misc_obj(void);
struct QuadObj* find_free_quad_obj(void);
struct LayerObj* find_free_layer_obj(void);

#ifdef MMX4_PC
extern void func_8002B450 (void);

extern void reset_entity (struct PlayerObj *arg0);
extern void reset_main_and_shots (void);
#endif

void update_on_screen(struct BaseObj*, s32, s32);

void reset_game_engine(void);

void reset_objects();

void ZeroObjectState(struct ObjectHeader* arg0);

void func_8002AB20();

s32 func_8002B160(struct BaseObj*);
s32 func_8002B1E8(struct BaseObj*, s32, s32);

void is_on_screen(struct BaseObj*);

void despawn_object(struct ObjectHeader* arg0);
void despawn_object_permanently(struct ObjectHeader* arg0);
void func_8002B560(s8, s8);

struct MiscObj* func_8002AE90(struct MiscObj* arg0, s32 arg1);
struct UnkObj* find_free_unk_obj();
struct VisualObj* func_8002AF4C(struct VisualObj* arg0, s32 arg1);

void func_8002B3C0(struct BaseObj* arg0);
void func_8002B458(struct QuadObj* arg0);
void func_8002B460(void);

void reset_main_and_shots();

#endif
