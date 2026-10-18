#ifndef MAIN_PLAYER_COMMON_H
#define MAIN_PLAYER_COMMON_H

void player_update_init(struct PlayerObj*);

void player_update_death(struct PlayerObj*);
void player_update_inactive(struct PlayerObj*);

void player_entry_beam_in(struct PlayerObj* arg0);
void player_entry_placed(struct PlayerObj* arg0);
void player_entry_ride(struct PlayerObj* arg0);

void player_death_start(struct PlayerObj*);
void player_death_wait(struct PlayerObj*);
void func_80035C20(struct PlayerObj*);
void player_death_end(struct PlayerObj*);
#ifdef MMX4_PC
void player_spawn_death_orb(s8);
void player_spawn_death_orbs(s8);
#endif

#ifdef MMX4_PC
extern u16 player_map_buttons (s32 arg0);

extern void player_update_frame_hitbox (struct PlayerObj *arg0);

extern void player_clear_flash (struct PlayerObj *arg0);
extern void player_update_flash (struct PlayerObj *arg0);
extern void player_copy_palette (struct PlayerObj *arg0, s32 arg1, s32 arg2);

extern void player_spawn_dash_dust (struct PlayerObj *arg0);
extern void player_spawn_wall_kick_spark (struct PlayerObj *arg0);
extern void player_start_script_action (s8 arg0, s8 arg1);

extern struct VisualObj *player_spawn_visual (s8 arg0, s8 arg1, s8 arg2, void *arg3);
#endif

extern struct Unk_unk68 player_x_collision_bounds;
extern struct Unk_unk68 player_zero_collision_bounds;

void player_damage(s8);

s32 player_set_animation(struct PlayerObj*, s32);

void player_set_collision_bounds(struct PlayerObj*);

extern u16 player_stage_3_entry_y[2][4];
extern u16 player_stage_6_entry_y[6];
extern u16 player_stage_12_entry_y[20];

void player_set_idle_animation(struct PlayerObj*);

void player_set_animation_frame(struct PlayerObj*, s32, s32);

void player_clear_dash_and_attack(struct PlayerObj*);
void player_play_voice(struct PlayerObj*, u8);
struct WeaponObj* player_spawn_weapon(s8, s8, s8, struct PlayerObj*);

void player_spawn_wall_slide_dust(struct PlayerObj*);
void player_spawn_dash_spark(struct PlayerObj*);
void player_spawn_dash_splash(struct PlayerObj*);

void player_clear_dash(struct PlayerObj*);

void player_air_steer(struct PlayerObj* self);
void player_check_splash(struct PlayerObj* self);
void player_clear_attack(struct PlayerObj* self);
void player_end_script_action(void);

void player_read_input(void);

void player_reset_palette(struct PlayerObj* self);

void player_set_palette(struct PlayerObj* self, s32 palette);
void player_spawn(void);

#endif
