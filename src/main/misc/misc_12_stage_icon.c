// MiscObj, misc_object_update_funcs[12]
// 800CA228..800CA52C
#include "common.h"

// stage_icon_init
INCLUDE_ASM("main/nonmatchings/misc/misc_12_stage_icon", func_800CA228);

void stage_icon_highlight(struct MiscObj* self)
{
    self->on_screen = 0;
    if (engine_obj.unk3 == self->unk2) {
        self->unk42 = 0x780A;
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->unk42 = 0x7809;
    }
}

// stage_icon_follow_init
INCLUDE_ASM("main/nonmatchings/misc/misc_12_stage_icon", func_800CA40C);

void stage_icon_follow(struct MiscObj* self)
{
    if (self->ext.misc_24.main->active == 0) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    is_on_screen(BASE_OBJECT(self));
}

void stage_icon_show_selected(struct MiscObj* self)
{
    self->on_screen = 0;
    if (engine_obj.unk3 == self->unk2) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void stage_icon_update(struct MiscObj* self)
{
    stage_icon_state_funcs[self->state](self);
}

union AnimationStep stage_icon_anim_0[9] = {
    { .packed = 0x0001001E },
    { .packed = 0x0101001E },
    { .packed = 0x0201001E },
    { .packed = 0x0301001E },
    { .packed = 0x0401001E },
    { .packed = 0x0501001E },
    { .packed = 0x0601001E },
    { .packed = 0x0701001E },
    { .packed = 0x1000001E },
};

union AnimationStep stage_icon_anim_1[8] = {
    { .packed = 0x0801001E },
    { .packed = 0x0901001E },
    { .packed = 0x0A01001E },
    { .packed = 0x0B01001E },
    { .packed = 0x0C01001E },
    { .packed = 0x0D01001E },
    { .packed = 0x0E01001E },
    { .packed = 0x0FF9001E },
};

union AnimationStep* stage_icon_animations[2] = { stage_icon_anim_0, stage_icon_anim_1 };

struct Misc12Position {
    s16 x;
    s16 y;
};

struct Misc12Position stage_icon_positions[8] = {
    { 8, 0x120 },
    { 0x55, 0x120 },
    { 0xA2, 0x120 },
    { 0xEF, 0x120 },
    { 0x21, 0x1B0 },
    { 0x61, 0x1B0 },
    { 0xA2, 0x1B0 },
    { 0xE2, 0x1B0 },
};

void (*stage_icon_state_funcs[5])(struct MiscObj*) = {
    func_800CA228,
    stage_icon_highlight,
    func_800CA40C,
    stage_icon_follow,
    stage_icon_show_selected,
};
