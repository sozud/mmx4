#ifndef MAIN_ITEMS_ITEM_09_MOVING_BLOCK_H
#define MAIN_ITEMS_ITEM_09_MOVING_BLOCK_H

struct MovingBlockMotion {
    s32 x_velocity;
    s32 y_velocity;
    u16 range;
    u8 vertical;
};

void moving_block_update(struct ItemObj*);

void func_800C20F4(struct ItemObj*);
void func_800C229C(struct ItemObj*);

extern struct MovingBlockMotion moving_block_motion[1];

#endif
