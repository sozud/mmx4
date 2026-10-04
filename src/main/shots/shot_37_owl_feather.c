// ShotObj, shot_object_update_funcs[37]
// 800A3C78..800A428C
#include "common.h"

s8 owl_feather_hit_box[4] = { -11, -11, 22, 22 };

u16 owl_feather_velocities[11][2] = {
    { 0x43, 0x28 },
    { 0x80, 0x28 },
    { 0xBC, 0x28 },
    { 0xF8, 0x28 },
    { 0x52, 0x70 },
    { 0x9E, 0x70 },
    { 0xEA, 0x70 },
    { 0x43, 0xB0 },
    { 0x80, 0xB0 },
    { 0xBC, 0xB0 },
    { 0xF8, 0xB0 },
};

void owl_feather_update(struct ShotObj* self)
{
    owl_feather_state_funcs[self->state](self);
}

// owl_feather_init
INCLUDE_ASM("main/nonmatchings/shots/shot_37_owl_feather", func_800A3CB4);

// owl_feather_fly
INCLUDE_ASM("main/nonmatchings/shots/shot_37_owl_feather", func_800A3FEC);

void owl_feather_despawn(struct ShotObj* self)
{
    struct MainObj* owner;

    if (self->unk2 > 0 && self->unk2 < 5) {
        owner = MAIN_OBJECT(self->unk7C);
        owner->ext.main_60.feather_mask -= 1 << self->unk84.value;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void owl_feather_idle(struct ShotObj* self)
{
}

void (*owl_feather_state_funcs[])(struct ShotObj*) = {
    func_800A3CB4,
    func_800A3FEC,
    owl_feather_despawn,
    owl_feather_idle,
};
