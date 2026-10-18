#ifndef MAIN_MAINS_MAIN_22_BEE_HIVE_H
#define MAIN_MAINS_MAIN_22_BEE_HIVE_H

void bee_hive_update(struct MainObj* arg0);

// bee_hive_state_funcs
void func_80055024(struct MainObj*);

void bee_hive_despawn(struct MainObj* arg0);

// bee_hive_step_funcs
void bee_hive_resume_step(struct MainObj* arg0);
void bee_hive_open(struct MainObj* arg0);
void bee_hive_wait(struct MainObj* arg0);
void bee_hive_release(struct MainObj* arg0);
void bee_hive_shake(struct MainObj* arg0);
void bee_hive_explode(struct MainObj* arg0);

// bee_hive_open_funcs
void bee_hive_open_start(struct MainObj*);
void func_80055358(struct MainObj*);
void bee_hive_open_end(struct MainObj*);

// bee_hive_wait_funcs
void bee_hive_wait_start(struct MainObj* arg0);
void bee_hive_wait_watch(struct MainObj*);

// bee_hive_release_funcs
void bee_hive_release_start(struct MainObj*);
void bee_hive_release_wait(struct MainObj*);
void bee_hive_release_pause(struct MainObj*);

// bee_hive_shake_funcs
void bee_hive_shake_start(struct MainObj*);
void bee_hive_shake_end(struct MainObj*);

// bee_hive_explode_funcs
void bee_hive_explode_start(struct MainObj* arg0);
void bee_hive_explode_smoke(struct MainObj*);
void bee_hive_explode_done(void);

extern void (*bee_hive_step_funcs[])(struct MainObj*);

extern u8 bee_hive_debris[8];

#endif
