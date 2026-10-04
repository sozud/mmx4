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
    { 0x1001001E },
    { 0x01010004 },
    { 0x02010004 },
    { 0x11010005 },
    { 0x12010008 },
    { 0x13010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x2B010003 },
    { 0x2C010003 },
    { 0x3201000C },
    { 0x2E010002 },
    { 0x2F01001D },
    { 0x2F000001 },
};

union AnimationStep cutscene_actor_anim_1[49] = {
    { 0x0001001E },
    { 0x01010002 },
    { 0x15010002 },
    { 0x1601000A },
    { 0x15010002 },
    { 0x00010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x17010008 },
    { 0x00010002 },
    { 0x01010002 },
    { 0x15010002 },
    { 0x1601000A },
    { 0x15010002 },
    { 0x00010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x17010008 },
    { 0x00010002 },
    { 0x01010002 },
    { 0x02010002 },
    { 0x03010012 },
    { 0x02010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x0001001D },
    { 0x00000001 },
};

union AnimationStep cutscene_actor_anim_2[19] = {
    { 0x0201001E },
    { 0x00010004 },
    { 0x4D010018 },
    { 0x4E010008 },
    { 0x4D010002 },
    { 0x82010002 },
    { 0x83010002 },
    { 0x84010003 },
    { 0x85010003 },
    { 0x86010003 },
    { 0x87010003 },
    { 0x88010004 },
    { 0x89010004 },
    { 0x8A010004 },
    { 0x8B010004 },
    { 0x50010002 },
    { 0x01010002 },
    { 0x0201001D },
    { 0x02000001 },
};

union AnimationStep cutscene_actor_anim_3[30] = {
    { 0x0001001E },
    { 0x01010003 },
    { 0x20010003 },
    { 0x2101000F },
    { 0x26010003 },
    { 0x27010002 },
    { 0x26010001 },
    { 0x2B010001 },
    { 0x28010001 },
    { 0x2C010001 },
    { 0x27010001 },
    { 0x2B010001 },
    { 0x29010001 },
    { 0x2C010001 },
    { 0x27010002 },
    { 0x26010001 },
    { 0x2B010001 },
    { 0x28010001 },
    { 0x2C010001 },
    { 0x27010001 },
    { 0x2B010001 },
    { 0x29010001 },
    { 0x2C010001 },
    { 0x27010014 },
    { 0x03010003 },
    { 0x01010003 },
    { 0x0001000F },
    { 0x01010003 },
    { 0x5B01001D },
    { 0x5B000001 },
};

union AnimationStep cutscene_actor_anim_4[11] = {
    { 0x0101001E },
    { 0x08010008 },
    { 0x09010003 },
    { 0x0A010002 },
    { 0x0B010008 },
    { 0x0C010004 },
    { 0x66010006 },
    { 0x55010002 },
    { 0x56010002 },
    { 0x5701001D },
    { 0x57000001 },
};

union AnimationStep cutscene_actor_anim_5[12] = {
    { 0x0001001E },
    { 0x35010007 },
    { 0x36010007 },
    { 0x3701000A },
    { 0x36010003 },
    { 0x35010003 },
    { 0x9301000E },
    { 0x2D010019 },
    { 0x05010014 },
    { 0x2E010003 },
    { 0x0001001D },
    { 0x00000001 },
};

union AnimationStep cutscene_actor_anim_6[13] = {
    { 0x0601001E },
    { 0x5A010002 },
    { 0x5B010002 },
    { 0x5A010018 },
    { 0x5C010008 },
    { 0x5D010008 },
    { 0x5E010008 },
    { 0x5F01000B },
    { 0x60010002 },
    { 0x61010002 },
    { 0x60010002 },
    { 0x6101001D },
    { 0x61000001 },
};

union AnimationStep cutscene_actor_anim_7[16] = {
    { 0x7D01001E },
    { 0x7E010002 },
    { 0x7F01000A },
    { 0x7E010002 },
    { 0x80010001 },
    { 0x81010001 },
    { 0x80010001 },
    { 0x81010001 },
    { 0x80010001 },
    { 0x8101001E },
    { 0x80010002 },
    { 0x82010002 },
    { 0x8301000A },
    { 0x82010002 },
    { 0x8401001D },
    { 0x84000001 },
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
