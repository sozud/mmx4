// EffectObj, effect_object_update_funcs[16]
// 800B8F5C..800B9100
#include "common.h"

void autoscroll_segment_update(struct EffectObj* self)
{
    autoscroll_segment_state_funcs[self->state](self);
}

void autoscroll_segment_start(struct EffectObj* self)
{
    self->ext.effect_16.saved_background_2A = background_objects[0].unk2A;
    self->ext.effect_16.saved_background_28 = background_objects[0].unk28;
    background_objects[0].unk26 = autoscroll_segment_bounds[self->unk2].primary;
    background_objects[0].unk24 = autoscroll_segment_bounds[self->unk2].primary;
    background_objects[0].unk47 = 6;
    background_objects[0].unk30 = 0;
    background_objects[0].unk32 = 0x140;
    background_objects[0].unk51 = 0;
    self->state++;
}

void autoscroll_segment_wait(struct EffectObj* self)
{
    if (background_objects[0].x_pos.i.hi >= *(s16*)&autoscroll_segment_bounds[self->unk2].primary) {
        self->state++;
    }
}

void autoscroll_segment_end(struct EffectObj* self)
{
    u16 unk6;

    background_objects[0].unk24 = autoscroll_segment_bounds[self->unk2].secondary;
    background_objects[0].unk2A = self->ext.effect_16.saved_background_2A;
    unk6 = self->ext.effect_16.saved_background_28;
    background_objects[0].unk28 = unk6;
    background_objects[0].unk51 = 1;
    background_objects[0].unk30 = 0xA0;
    background_objects[0].unk32 = 0xA0;
    background_objects[0].unk47 = 2;
    background_objects[0].unk48 = 8;
    despawn_object_permanently(OBJECT_HEADER(self));
}

void (*autoscroll_segment_state_funcs[])(struct EffectObj*) = {
    autoscroll_segment_start,
    autoscroll_segment_wait,
    autoscroll_segment_end,
};

struct Effect16Coordinate autoscroll_segment_bounds[2] = {
    { 0x7000, 0x7100 },
    { 0x4000, 0x4150 },
};
