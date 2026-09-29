// MiscObj, misc_object_update_funcs[50]
// 800D1B44..800D1DC4
#include "common.h"

// cutscene_actor_init
INCLUDE_ASM("main/nonmatchings/misc/misc_50_cutscene_actor", func_800D1B44);

void cutscene_actor_wait(struct MiscObj* self)
{
    if (engine_obj.unk2 == 7) {
        self->state = 3;
        self->unk42 = 0x7848;
    }
    is_on_screen(BASE_OBJECT(self));
}

void cutscene_actor_hold(struct MiscObj* self)
{
    is_on_screen(BASE_OBJECT(self));
}

void cutscene_actor_animate(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void cutscene_actor_update(struct MiscObj* self)
{
    self->on_screen = 0;
    cutscene_actor_state_funcs[self->state](self);
}

union AnimationStep cutscene_actor_anim_0[18] = {
    { .packed = 0x1001001E },
    { .packed = 0x01010004 },
    { .packed = 0x02010004 },
    { .packed = 0x11010005 },
    { .packed = 0x12010008 },
    { .packed = 0x13010003 },
    { .packed = 0x12010003 },
    { .packed = 0x13010003 },
    { .packed = 0x12010003 },
    { .packed = 0x13010003 },
    { .packed = 0x12010003 },
    { .packed = 0x13010003 },
    { .packed = 0x2B010003 },
    { .packed = 0x2C010003 },
    { .packed = 0x3201000C },
    { .packed = 0x2E010002 },
    { .packed = 0x2F01001D },
    { .packed = 0x2F000001 },
};

union AnimationStep cutscene_actor_anim_1[49] = {
    { .packed = 0x0001001E },
    { .packed = 0x01010002 },
    { .packed = 0x15010002 },
    { .packed = 0x1601000A },
    { .packed = 0x15010002 },
    { .packed = 0x00010002 },
    { .packed = 0x17010002 },
    { .packed = 0x18010002 },
    { .packed = 0x17010002 },
    { .packed = 0x18010002 },
    { .packed = 0x17010008 },
    { .packed = 0x00010002 },
    { .packed = 0x01010002 },
    { .packed = 0x15010002 },
    { .packed = 0x1601000A },
    { .packed = 0x15010002 },
    { .packed = 0x00010002 },
    { .packed = 0x17010002 },
    { .packed = 0x18010002 },
    { .packed = 0x17010002 },
    { .packed = 0x18010002 },
    { .packed = 0x17010008 },
    { .packed = 0x00010002 },
    { .packed = 0x01010002 },
    { .packed = 0x02010002 },
    { .packed = 0x03010012 },
    { .packed = 0x02010002 },
    { .packed = 0x19010002 },
    { .packed = 0x1A010002 },
    { .packed = 0x19010002 },
    { .packed = 0x1A010002 },
    { .packed = 0x19010002 },
    { .packed = 0x1A010002 },
    { .packed = 0x19010002 },
    { .packed = 0x1A010002 },
    { .packed = 0x19010002 },
    { .packed = 0x1A010002 },
    { .packed = 0x19010002 },
    { .packed = 0x1A010002 },
    { .packed = 0x19010002 },
    { .packed = 0x1A010002 },
    { .packed = 0x19010002 },
    { .packed = 0x1A010002 },
    { .packed = 0x19010002 },
    { .packed = 0x1A010002 },
    { .packed = 0x19010002 },
    { .packed = 0x1A010002 },
    { .packed = 0x0001001D },
    { .packed = 0x00000001 },
};

union AnimationStep cutscene_actor_anim_2[19] = {
    { .packed = 0x0201001E },
    { .packed = 0x00010004 },
    { .packed = 0x4D010018 },
    { .packed = 0x4E010008 },
    { .packed = 0x4D010002 },
    { .packed = 0x82010002 },
    { .packed = 0x83010002 },
    { .packed = 0x84010003 },
    { .packed = 0x85010003 },
    { .packed = 0x86010003 },
    { .packed = 0x87010003 },
    { .packed = 0x88010004 },
    { .packed = 0x89010004 },
    { .packed = 0x8A010004 },
    { .packed = 0x8B010004 },
    { .packed = 0x50010002 },
    { .packed = 0x01010002 },
    { .packed = 0x0201001D },
    { .packed = 0x02000001 },
};

union AnimationStep cutscene_actor_anim_3[30] = {
    { .packed = 0x0001001E },
    { .packed = 0x01010003 },
    { .packed = 0x20010003 },
    { .packed = 0x2101000F },
    { .packed = 0x26010003 },
    { .packed = 0x27010002 },
    { .packed = 0x26010001 },
    { .packed = 0x2B010001 },
    { .packed = 0x28010001 },
    { .packed = 0x2C010001 },
    { .packed = 0x27010001 },
    { .packed = 0x2B010001 },
    { .packed = 0x29010001 },
    { .packed = 0x2C010001 },
    { .packed = 0x27010002 },
    { .packed = 0x26010001 },
    { .packed = 0x2B010001 },
    { .packed = 0x28010001 },
    { .packed = 0x2C010001 },
    { .packed = 0x27010001 },
    { .packed = 0x2B010001 },
    { .packed = 0x29010001 },
    { .packed = 0x2C010001 },
    { .packed = 0x27010014 },
    { .packed = 0x03010003 },
    { .packed = 0x01010003 },
    { .packed = 0x0001000F },
    { .packed = 0x01010003 },
    { .packed = 0x5B01001D },
    { .packed = 0x5B000001 },
};

union AnimationStep cutscene_actor_anim_4[11] = {
    { .packed = 0x0101001E },
    { .packed = 0x08010008 },
    { .packed = 0x09010003 },
    { .packed = 0x0A010002 },
    { .packed = 0x0B010008 },
    { .packed = 0x0C010004 },
    { .packed = 0x66010006 },
    { .packed = 0x55010002 },
    { .packed = 0x56010002 },
    { .packed = 0x5701001D },
    { .packed = 0x57000001 },
};

union AnimationStep cutscene_actor_anim_5[12] = {
    { .packed = 0x0001001E },
    { .packed = 0x35010007 },
    { .packed = 0x36010007 },
    { .packed = 0x3701000A },
    { .packed = 0x36010003 },
    { .packed = 0x35010003 },
    { .packed = 0x9301000E },
    { .packed = 0x2D010019 },
    { .packed = 0x05010014 },
    { .packed = 0x2E010003 },
    { .packed = 0x0001001D },
    { .packed = 0x00000001 },
};

union AnimationStep cutscene_actor_anim_6[13] = {
    { .packed = 0x0601001E },
    { .packed = 0x5A010002 },
    { .packed = 0x5B010002 },
    { .packed = 0x5A010018 },
    { .packed = 0x5C010008 },
    { .packed = 0x5D010008 },
    { .packed = 0x5E010008 },
    { .packed = 0x5F01000B },
    { .packed = 0x60010002 },
    { .packed = 0x61010002 },
    { .packed = 0x60010002 },
    { .packed = 0x6101001D },
    { .packed = 0x61000001 },
};

union AnimationStep cutscene_actor_anim_7[16] = {
    { .packed = 0x7D01001E },
    { .packed = 0x7E010002 },
    { .packed = 0x7F01000A },
    { .packed = 0x7E010002 },
    { .packed = 0x80010001 },
    { .packed = 0x81010001 },
    { .packed = 0x80010001 },
    { .packed = 0x81010001 },
    { .packed = 0x80010001 },
    { .packed = 0x8101001E },
    { .packed = 0x80010002 },
    { .packed = 0x82010002 },
    { .packed = 0x8301000A },
    { .packed = 0x82010002 },
    { .packed = 0x8401001D },
    { .packed = 0x84000001 },
};

union AnimationStep* cutscene_actor_animations[8] = {
    cutscene_actor_anim_0,
    cutscene_actor_anim_1,
    cutscene_actor_anim_2,
    cutscene_actor_anim_3,
    cutscene_actor_anim_4,
    cutscene_actor_anim_5,
    cutscene_actor_anim_6,
    cutscene_actor_anim_7,
};

void (*cutscene_actor_state_funcs[4])(struct MiscObj*) = {
    func_800D1B44,
    cutscene_actor_wait,
    cutscene_actor_hold,
    cutscene_actor_animate,
};
