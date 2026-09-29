// MiscObj, misc_object_update_funcs[31]
// 800CDE44..800CE114
#include "common.h"

// option_toggle_init
INCLUDE_ASM("main/nonmatchings/misc/misc_31", func_800CDE44);

// option_toggle_appear
INCLUDE_ASM("main/nonmatchings/misc/misc_31", func_800CDF4C);

void option_toggle_refresh(struct MiscObj* self)
{
    if (D_80171EA9 != self->ext.misc_31.animation) {
        self->animation_step.fields.frame_index = D_80171EA9 == 0 ? 0x57 : 0x56;
        self->ext.misc_31.animation = D_80171EA9;
    }
    is_on_screen(BASE_OBJECT(self));
}

void option_toggle_update(struct MiscObj* self)
{
    self->on_screen = 0;
    option_toggle_state_funcs[self->state](self);
}

void (*option_toggle_state_funcs[3])(struct MiscObj*) = {
    func_800CDE44,
    func_800CDF4C,
    option_toggle_refresh,
};

union AnimationStep option_toggle_anim_0[36] = {
    { .packed = 0x3101000F },
    { .packed = 0x3201000D },
    { .packed = 0x3301000A },
    { .packed = 0x31010008 },
    { .packed = 0x32010007 },
    { .packed = 0x33010006 },
    { .packed = 0x31010006 },
    { .packed = 0x32010005 },
    { .packed = 0x33010005 },
    { .packed = 0x31010004 },
    { .packed = 0x32010005 },
    { .packed = 0x33010005 },
    { .packed = 0x31010006 },
    { .packed = 0x32010006 },
    { .packed = 0x33010007 },
    { .packed = 0x31010008 },
    { .packed = 0x3201000A },
    { .packed = 0x3301000D },
    { .packed = 0x3101000F },
    { .packed = 0x3301000D },
    { .packed = 0x3201000A },
    { .packed = 0x31010008 },
    { .packed = 0x33010007 },
    { .packed = 0x32010006 },
    { .packed = 0x31010006 },
    { .packed = 0x33010005 },
    { .packed = 0x32010005 },
    { .packed = 0x31010004 },
    { .packed = 0x33010005 },
    { .packed = 0x32010005 },
    { .packed = 0x31010006 },
    { .packed = 0x33010006 },
    { .packed = 0x32010007 },
    { .packed = 0x31010008 },
    { .packed = 0x3301000A },
    { .packed = 0x32DD000D },
};

u32* option_toggle_animations[1] = { (u32*)option_toggle_anim_0 };
