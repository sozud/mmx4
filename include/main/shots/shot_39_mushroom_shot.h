#ifndef MAIN_SHOTS_SHOT_39_MUSHROOM_SHOT_H
#define MAIN_SHOTS_SHOT_39_MUSHROOM_SHOT_H

void mushroom_shot_update(struct ShotObj*);

// mushroom_shot_sprout_step_funcs
extern void (*mushroom_shot_sprout_step_funcs[])(struct ShotObj*);

extern u8 mushroom_shot_sprout_palettes[4];
extern u8 mushroom_shot_sprout_alt_palettes[4];

void func_800A5194(struct ShotObj*);

#endif
