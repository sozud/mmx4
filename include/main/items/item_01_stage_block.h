#ifndef MAIN_ITEMS_ITEM_01_STAGE_BLOCK_H
#define MAIN_ITEMS_ITEM_01_STAGE_BLOCK_H

struct Item01StageEntry {
    u16 x;
    u16 y;
    u16 left;
    u16 right;
    u16 trigger_x;
    u8 flags;
    u8 unkB;
    u16 velocity;
    u8 sound_id;
    u8 unkF;
};

struct Item01SpriteBounds {
    u8 x_offset;
    u8 y_offset;
    u8 width;
    u8 height;
};

void stage_block_update(struct ItemObj*);

void func_800BEBFC(struct ItemObj*);

void func_800BEFCC(struct ItemObj* arg0);
void func_800BF1FC(struct ItemObj* arg0);

extern struct Item01StageEntry stage_block_entries[15];

extern struct Item01SpriteBounds stage_block_bounds[15];

#endif
