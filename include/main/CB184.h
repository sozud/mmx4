#ifndef MAIN_CB184_H
#define MAIN_CB184_H

#ifdef MMX4_PC
extern void tile_effect_nop (void);
#endif

void refresh_visible_tile_effect(s32 arg0, s32 arg1, s32 arg2);

void apply_tile_effect(u8, arg_s16, arg_s16);

#endif
