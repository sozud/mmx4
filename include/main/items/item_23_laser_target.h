#ifndef MAIN_ITEMS_ITEM_23_LASER_TARGET_H
#define MAIN_ITEMS_ITEM_23_LASER_TARGET_H

void laser_target_update(struct ItemObj*);

// laser_target_step_funcs
extern void (*laser_target_step_funcs[])(struct ItemObj*);

void laser_target_fire(struct ItemObj*);
void laser_target_hold(struct ItemObj*);

#endif
