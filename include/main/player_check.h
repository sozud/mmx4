#ifndef MAIN_PLAYER_CHECK_H
#define MAIN_PLAYER_CHECK_H

enum PlayerInput {
    PLAYER_INPUT_RIGHT = 0x1,
    PLAYER_INPUT_LEFT = 0x2,
    PLAYER_INPUT_UP = 0x4,
    PLAYER_INPUT_DOWN = 0x8,
    PLAYER_INPUT_SHOOT = 0x10,
    PLAYER_INPUT_SPECIAL = 0x20,
    PLAYER_INPUT_GIGA = 0x40,
    PLAYER_INPUT_JUMP = 0x80,
    PLAYER_INPUT_DASH = 0x100,
    PLAYER_INPUT_NEXT_WEAPON = 0x200,
    PLAYER_INPUT_PREVIOUS_WEAPON = 0x400,
};

#ifdef MMX4_PC
extern s32 player_check_dash_jump (struct PlayerObj *arg0);
extern s32 player_check_walk_start (struct PlayerObj *arg0);
extern s32 player_dash_should_end (struct PlayerObj *arg0);
extern s32 player_check_ladder (struct PlayerObj *arg0);
extern s32 player_check_dash_jump_walk (struct PlayerObj *arg0);
extern s32 player_check_script (struct PlayerObj *arg0);
extern s32 player_leap_check_peak (struct PlayerObj *arg0);

extern void player_check_fall (struct PlayerObj *arg0);
extern void player_update_double_tap (struct PlayerObj *arg0);
extern void player_check_capsule (struct PlayerObj *arg0);
extern void player_check_ride (struct PlayerObj *arg0);
extern void player_check_damage (struct PlayerObj *arg0);
extern void player_reset_actions (struct PlayerObj *arg0);
extern void player_noop (void);
#endif

void player_script_walk_to_mark(struct PlayerObj*);

s32 player_check_dash_input(struct PlayerObj*);
s32 func_80033FF0(struct PlayerObj*);

s32 player_check_walk(struct PlayerObj* self);
s32 player_check_wall_jump(struct PlayerObj* self);
s32 player_is_pushing_wall(struct PlayerObj* self);

#endif
