#ifndef MAIN_ITEMS_ITEM_02_PICKUP_H
#define MAIN_ITEMS_ITEM_02_PICKUP_H

void func_800BF638(struct BaseObj* arg0, s8 arg1, s16 arg2, s16 arg3);

void pickup_update(struct ItemObj*);

void func_800BF76C(struct ItemObj*);

void func_800C00BC(struct ItemObj*);
void func_800BFCC0(struct ItemObj*, u8);
void pickup_collect_health(struct ItemObj*, s8, s8);
void set_objects_frozen(s8);

#endif
