#ifndef MAIN_MAINS_MAIN_02_ITEM_CARRIER_H
#define MAIN_MAINS_MAIN_02_ITEM_CARRIER_H

void item_carrier_update(struct MainObj* arg0);

// item_carrier_state_funcs
void func_80042950(struct MainObj* arg0);
void func_80042A48(struct MainObj* arg0);
void func_80042AFC(struct MainObj* arg0);

void item_carrier_drop(struct MainObj* arg0);

void item_carrier_hover_turn(struct MainObj*);

// item_carrier_drop_funcs
void item_carrier_drop_start(struct MainObj* arg0);

void item_carrier_drop_fall(struct MainObj* arg0);

void item_carrier_leave_up(struct MainObj*);

extern union AnimationStep* item_carrier_animations[11];

#endif
