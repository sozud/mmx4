// ShotObj, shot_object_update_funcs[32]
// 800A0170..800A03B8
#include "common.h"

u8 flame_pillar_short_box[4] = { 0xF8, 0xCC, 0x0F, 0x23 };
u8 flame_pillar_tall_box[4] = { 0xF8, 0xCC, 0x0F, 0x65 };

// flame_pillar_init
INCLUDE_ASM("main/nonmatchings/shots/shot_32_flame_pillar", func_800A0170);

void flame_pillar_active(struct ShotObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    if (self->animation_step.fields.relative_step < 0) {
        self->state++;
    }
}

void flame_pillar_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void flame_pillar_update(struct ShotObj* self)
{
    flame_pillar_state_funcs[self->state](self);
}

void (*flame_pillar_state_funcs[])(struct ShotObj*) = {
    func_800A0170,
    flame_pillar_active,
    flame_pillar_despawn,
};
