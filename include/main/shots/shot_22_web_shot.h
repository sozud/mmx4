#ifndef MAIN_SHOTS_SHOT_22_WEB_SHOT_H
#define MAIN_SHOTS_SHOT_22_WEB_SHOT_H

void web_shot_update(struct ShotObj*);

void func_8009D788(struct ShotObj*);
void web_shot_main(struct ShotObj*);

// web_shot_step_funcs
extern void (*web_shot_step_funcs[])(struct ShotObj*);

#endif
