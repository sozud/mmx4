#ifndef MAIN_ITEMS_ITEM_04_DESTRUCTIBLE_CORE_H
#define MAIN_ITEMS_ITEM_04_DESTRUCTIBLE_CORE_H

struct Item04Data {
    u16 unk0;
    u16 unk2[6];
    u8 object_ids[50];
};

void destructible_core_update(struct ItemObj*);

void func_800C0864(struct ItemObj*);

extern struct Item04Data destructible_core_data;

#endif
