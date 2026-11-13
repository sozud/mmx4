#ifndef MAIN_ITEMS_ITEM_04_DESTRUCTIBLE_CORE_H
#define MAIN_ITEMS_ITEM_04_DESTRUCTIBLE_CORE_H

struct Item04Data {
    u16 x;
    u16 y;
    u16 unk4[5];
    u8 object_id;
    u8 pad;
};

void destructible_core_update(struct ItemObj*);

void func_800C0864(struct ItemObj*);

extern struct Item04Data destructible_core_data[4];

#endif
