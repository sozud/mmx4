// ItemObj, item_object_update_funcs[9]
// 800C20AC..800C24E0
#include "common.h"

void moving_block_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    moving_block_state_funcs[arg0->state](arg0);
}

// moving_block_init
INCLUDE_ASM("main/nonmatchings/items/item_09_moving_block", func_800C20F4);

// moving_block_move
INCLUDE_ASM("main/nonmatchings/items/item_09_moving_block", func_800C229C);

void moving_block_despawn(struct ItemObj* arg0)
{
    arg0->on_screen = 0;
    despawn_object(OBJECT_HEADER(arg0));
}

u8 moving_block_terrain_box[4] = { 0, 0, 0x18, 0x10 };

struct MovingBlockMotion moving_block_motion[1] = { { 0x10000, 0, 0x90, 0 } };

void (*moving_block_state_funcs[])(struct ItemObj*) = {
    func_800C20F4,
    func_800C229C,
    moving_block_despawn,
};
