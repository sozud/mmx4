#ifndef MAIN_MAINS_MAIN_28_SPAWNER_POD_H
#define MAIN_MAINS_MAIN_28_SPAWNER_POD_H

void spawner_pod_update(struct MainObj* arg0);

// spawner_pod_state_funcs
void spawner_pod_init(struct MainObj*);

void spawner_pod_detach(struct MainObj*);

void spawner_pod_remove(struct MainObj* arg0);

void spawner_pod_idle(struct MainObj* arg0);
void func_80059E40(struct MainObj* arg0);
void func_80059F60(struct MainObj* arg0);
void spawner_pod_step_4(struct MainObj* arg0);

extern union AnimationStep* spawner_pod_animations[];

#endif
