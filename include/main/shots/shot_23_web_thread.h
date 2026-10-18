#ifndef MAIN_SHOTS_SHOT_23_WEB_THREAD_H
#define MAIN_SHOTS_SHOT_23_WEB_THREAD_H

void web_thread_update(struct ShotObj*);

// web_thread_step_funcs
extern void (*web_thread_step_funcs[])(struct ShotObj*);

void web_thread_snap(struct ShotObj*);
void web_thread_pulse(struct ShotObj*);

#endif
