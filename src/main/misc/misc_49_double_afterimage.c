// MiscObj, misc_object_update_funcs[49]
// 800D1990..800D1B44
#include "common.h"

// double_afterimage_init
INCLUDE_ASM("main/nonmatchings/misc/misc_49_double_afterimage", func_800D1990);

// double_afterimage_fade
void func_800D1A48(struct MiscObj* self)
{
    if (self->unk2 != 4) {
        if (--self->ext.misc_49.timer == 0) {
            self->on_screen = 0;
            self->state = 2;
            return;
        }
        animate_object(ANIMATED_OBJECT(self));
        move_with_gravity(ANIMATED_OBJECT(self));
    } else {
        if (--self->ext.misc_49.timer == 0) {
            self->on_screen = 0;
            self->state = 2;
            return;
        }
        animate_object(ANIMATED_OBJECT(self));
    }
    is_on_screen(BASE_OBJECT(self));
}

void double_afterimage_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void double_afterimage_update(struct MiscObj* self)
{
    double_afterimage_state_funcs[self->state](self);
}

u8 double_afterimage_angles[4] = { 4, 12, 16, 31 };

void (*double_afterimage_state_funcs[3])(struct MiscObj*) = {
    func_800D1990,
    func_800D1A48,
    double_afterimage_despawn,
};
