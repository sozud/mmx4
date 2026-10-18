#ifndef MAIN_ITEMS_ITEM_01_STAGE_BLOCK_H
#define MAIN_ITEMS_ITEM_01_STAGE_BLOCK_H

struct Item01StageEntry {
    u16 x;
    u16 y;
    u16 left;
    u16 right;
    u16 trigger_x;
    u16 flags_and_palette;
    u16 velocity;
    u16 sound_id;
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

void func_800BF638(struct BaseObj* arg0, s8 arg1, s16 arg2, s16 arg3);

#endif
