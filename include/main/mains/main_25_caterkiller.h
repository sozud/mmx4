#ifndef MAIN_MAINS_MAIN_25_CATERKILLER_H
#define MAIN_MAINS_MAIN_25_CATERKILLER_H

void caterkiller_update(struct MainObj* arg0);

// caterkiller_state_funcs
void func_80057160(struct MainObj*);
void func_80057308(struct MainObj*);

// caterkiller_crawl_funcs
void caterkiller_crawl_start(struct MainObj*);
void func_8005754C(struct MainObj*);
void caterkiller_crawl_end(struct MainObj*);

// caterkiller_lunge_funcs
void caterkiller_lunge_start(struct MainObj*);
void func_80057874(struct MainObj*);
void caterkiller_lunge_end(struct MainObj*);

// caterkiller_fall_funcs
void caterkiller_fall_start(struct MainObj*);
void caterkiller_fall_drop(struct MainObj*);
void func_80057C00(struct MainObj*);

// caterkiller_climb_funcs
void caterkiller_climb_start(struct MainObj*);
void caterkiller_climb_hop(struct MainObj*);
void caterkiller_climb_rise(struct MainObj*);
void caterkiller_climb_cling(struct MainObj*);

void caterkiller_face_player(struct MainObj*);

#endif
