// MiscObj, misc_object_update_funcs[3]
// 800C85D0..800C8774
#include "common.h"

void func_800C8610(struct MiscObj* arg0);
void debris_fall(struct MiscObj* arg0);

void debris_update(struct MiscObj* self)
{
    if (self->state == 0) {
        func_800C8610(self);
    } else {
        debris_fall(self);
    }
}

// debris_init
INCLUDE_ASM("main/nonmatchings/misc/misc_03_debris", func_800C8610);

void debris_fall(struct MiscObj* self)
{
    u8 temp_v0;

    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        move_with_gravity((struct AnimatedObj*)self);
        animate_object(self);
        temp_v0 = self->on_screen ^ 1;
        self->on_screen = temp_v0;
        if (temp_v0 != 0) {
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

s32 debris_x_speeds[8] = { -0x30000, -0x20000, 0x18000, 0x28000, -0x38000, -0x28000, 0x20000, 0x30000 };
s32 debris_y_speeds[8] = { 0x38000, 0x48000, 0x60000, 0x30000, 0x40000, 0x50000, 0x58000, 0x28000 };
