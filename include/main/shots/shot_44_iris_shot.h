#ifndef MAIN_SHOTS_SHOT_44_IRIS_SHOT_H
#define MAIN_SHOTS_SHOT_44_IRIS_SHOT_H

void iris_shot_update(struct ShotObj*);

void func_800A7008(struct ShotObj*);

void func_800A73C4(struct ShotObj*);

void iris_drone_brake(struct ShotObj*);

void func_800A766C(struct ShotObj*);
void iris_drone_burst(struct ShotObj*);
void iris_drone_explode(struct ShotObj*);

extern u8 iris_drone_explode_box[4];

#endif
