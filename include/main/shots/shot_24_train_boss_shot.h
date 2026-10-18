#ifndef MAIN_SHOTS_SHOT_24_TRAIN_BOSS_SHOT_H
#define MAIN_SHOTS_SHOT_24_TRAIN_BOSS_SHOT_H

void enemy_hit_reaction_shot(struct ShotObj*);

void train_boss_shot_update(struct ShotObj*);

void func_8009E188(struct ShotObj*);

// train_boss_arm_step_funcs
extern void (*train_boss_arm_step_funcs[])(struct ShotObj*);

void func_8009E8E0(struct ShotObj* arg0);

void train_boss_arm_wait_sync(struct ShotObj* arg0);

extern u8 train_boss_bullet_hit_box[4];

extern u16 train_boss_arm_debris_positions[3][2];
extern u8 train_boss_arm_debris[8];

extern s16 train_boss_arm_offsets[3][2];

#endif
