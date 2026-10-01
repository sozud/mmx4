// ItemObj, item_object_update_funcs[18]
// 800C4544..800C470C
#include "common.h"

void drop_pillar_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    drop_pillar_state_funcs[arg0->state](arg0);
}

void drop_pillar_init(struct ItemObj* arg0)
{
    arg0->unk16 = 6;
    arg0->animation_table = NULL;
    arg0->unk5C = 0;
    arg0->unk61 = 0;
    arg0->unk68 = NULL;
    arg0->unk50 = 0;
    arg0->unk54 = 0;
    arg0->unk58 = 0;
    arg0->x_pos.i.hi = 0x24B0;
    arg0->y_pos.i.hi = 0xC0;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = FIXED(0.125);
    update_on_screen(BASE_OBJECT(arg0), 0x40, 0x60);
    arg0->state = 1;
}

void drop_pillar_fall(struct ItemObj* arg0)
{
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->y_pos.i.hi > (0x188 - (arg0->unk2 << 6))) {
        func_8001540C(2, 0x88, arg0);
        arg0->state = 2;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x40, 0x60);
}

void drop_pillar_land(struct ItemObj* arg0)
{
    if (arg0->unk2 != 2) {
        apply_tile_effect(
            0xC,
            (s16)(arg0->x_pos.u.hi - 0x10),
            (s16)(arg0->y_pos.u.hi - 0x30));
    } else {
        apply_tile_effect(
            0xD,
            (s16)(arg0->x_pos.u.hi - 0x10),
            (s16)(arg0->y_pos.u.hi - 0x70));
    }

    start_screen_shake_y(0x10, 4, 2);
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*drop_pillar_state_funcs[])(struct ItemObj*) = {
    drop_pillar_init,
    drop_pillar_fall,
    drop_pillar_land,
};
