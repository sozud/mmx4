// ItemObj, item_object_update_funcs[0]
// 800BE9A0..800BEBB4
#include "common.h"

void breakable_wall_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    breakable_wall_state_funcs[arg0->state](arg0);
}

// breakable_wall_init
INCLUDE_ASM("main/nonmatchings/items/item_00", func_800BE9E8);

void breakable_wall_main(struct ItemObj* arg0)
{
    u8 var_a0;

    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        spawn_debris(7, breakable_wall_debris, arg0);
        var_a0 = 7;
        if (arg0->unk2 == 0) {
            var_a0 = 2;
        }
        apply_tile_effect(var_a0, (s16)(arg0->x_pos.u.hi - 0x20),
            (s16)(arg0->y_pos.u.hi - 0x18));
        arg0->state = 2;
    }
}

void breakable_wall_despawn(struct ItemObj* arg0)
{
    despawn_object_permanently(OBJECT_HEADER(arg0));
}

void (*breakable_wall_state_funcs[])(struct ItemObj*) = {
    func_800BE9E8,
    breakable_wall_main,
    breakable_wall_despawn,
};

u8 breakable_wall_hit_box[4] = { 0xE0, 0xE8, 0x40, 0x30 };
u8 breakable_wall_debris[8] = { 0, 1, 2, 3, 4, 5, 6, 0 };
