#ifndef MAIN_SHOTS_SHOT_34_RAY_TRAP_H
#define MAIN_SHOTS_SHOT_34_RAY_TRAP_H

void ray_trap_update(struct ShotObj*);

void func_800A19A8(struct ShotObj*);
void func_800A1B1C(struct ShotObj*);
void func_800A1BEC(struct ShotObj*);

// ray_trap_step_funcs
extern void (*ray_trap_step_funcs[])(struct ShotObj*);
void ray_trap_fall(struct ShotObj*);
void ray_trap_chase(struct ShotObj*);
void func_800A1CCC(struct ShotObj*);
void func_800A1E3C(struct ShotObj*);

void func_800A16FC(struct ShotObj*);
void func_800A2098(struct ShotObj*);

#endif
