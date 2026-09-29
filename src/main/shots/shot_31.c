// ShotObj, shot_object_update_funcs[31]
// 8009FF10..800A0170
#include "common.h"

u8 slash_beast_crescent_boxes[2][4] = {
    { 0xF8, 0xEE, 0x0F, 0x23 },
    { 0xF7, 0xF1, 0x14, 0x1B },
};
s8 slash_beast_crescent_offsets[4] = { -72, -6, -60, -51 };

void slash_beast_crescent_update(struct ShotObj* self)
{
    slash_beast_crescent_state_funcs[self->state](self);
}

// slash_beast_crescent_init
INCLUDE_ASM("main/nonmatchings/shots/shot_31", func_8009FF4C);

void slash_beast_crescent_fly(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 2;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }
    self->state = 2;
}

void slash_beast_crescent_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*slash_beast_crescent_state_funcs[])(struct ShotObj*) = {
    func_8009FF4C,
    slash_beast_crescent_fly,
    slash_beast_crescent_despawn,
};
