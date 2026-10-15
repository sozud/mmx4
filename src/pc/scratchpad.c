#include "common.h"

_Alignas(16) u8 mmx4_scratchpad[0x400];
void* mmx4_sp_primitive_cursor;
void* mmx4_sp_draw_mode_cursor;
u8* mmx4_sp_background_cursor;
void* mmx4_sp_background_primitive_cursor;
void* mmx4_sp_ordering_cursor;
void* mmx4_sp_auxiliary_cursor;
struct MainObj* mmx4_sp_current_main;
struct WeaponObj* mmx4_sp_current_weapon;
struct ShotObj* mmx4_sp_current_shot;
struct VisualObj* mmx4_sp_current_visual;
struct EffectObj* mmx4_sp_current_effect;
struct ItemObj* mmx4_sp_current_item;
struct MiscObj* mmx4_sp_current_misc;
struct UnkObj* mmx4_sp_current_unk;
struct QuadObj* mmx4_sp_current_quad;
struct LayerObj* mmx4_sp_current_layer;
