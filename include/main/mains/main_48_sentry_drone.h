#ifndef MAIN_MAINS_MAIN_48_SENTRY_DRONE_H
#define MAIN_MAINS_MAIN_48_SENTRY_DRONE_H

void sentry_drone_update(struct MainObj* arg0);

// sentry_drone_state_funcs
void func_8006738C(struct MainObj*);

// sentry_drone_step_funcs
void sentry_drone_resume_step(struct MainObj* arg0);

// sentry_drone_drift_funcs
void sentry_drone_drift_start(struct MainObj*);

// sentry_drone_dash_funcs
void sentry_drone_dash_start(struct MainObj*);

void sentry_drone_burst_fire(struct MainObj*);

void func_80067DAC(struct MainObj*);
void sentry_drone_spread_fire(struct MainObj*);

void func_800681C4(struct MainObj*);
void func_80068340(struct MainObj*);

#endif
