#ifndef MAIN_ITEMS_ITEM_03_FALLING_PILLAR_H
#define MAIN_ITEMS_ITEM_03_FALLING_PILLAR_H

struct Item03StageEntry {
    u16 x;
    u16 y;
    u16 velocity;
    u16 right;
    u16 trigger_x;
    u16 object_id;
    s16 width;
    s16 height;
};

void falling_pillar_update(struct ItemObj*);

void func_800C044C(struct ItemObj*);
void falling_pillar_wait_player(struct ItemObj*);
void func_800C05FC(struct ItemObj*);
void falling_pillar_finish(struct ItemObj*);

extern struct Item03StageEntry falling_pillar_entries[22];

#endif
