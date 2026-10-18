#ifndef MAIN_STAGE_OBJECTS_H
#define MAIN_STAGE_OBJECTS_H

struct Checkpoint {
    s16 x, y;
    s16 bg0_x, bg0_y, bg1_x, bg1_y, bg2_x, bg2_y;
    s16 bg0_right, bg0_bottom, bg0_left, bg0_top;
    s16 facing;
    s16 bg1_off_x, bg1_off_y, bg2_off_x, bg2_off_y;
    s16 player_unkBE;
#ifdef MMX4_WIN32
    s16 pc_unk24[2];
#endif
};

void start_screen_shake_x(s8, s8, s8);

void start_screen_shake_y(s8, s8, s8);

void func_80028BF0(void);

#endif
