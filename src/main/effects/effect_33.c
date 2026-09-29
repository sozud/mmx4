// EffectObj, effect_object_update_funcs[33]
// 800BC748..800BCE48
#include "common.h"

void rock_dropper_update(struct EffectObj* self)
{
    rock_dropper_state_funcs[self->state](self);
}

// rock_dropper_init
INCLUDE_ASM("main/nonmatchings/effects/effect_33", func_800BC784);

// rock_dropper_drop
INCLUDE_ASM("main/nonmatchings/effects/effect_33", func_800BC92C);

void rock_dropper_despawn(struct EffectObj* self)
{
    switch (self->unk2 & 0xF0) {
    case 0:
        if (self->backref != NULL) {
            despawn_object_permanently(OBJECT_HEADER(self));
        } else {
            ZeroObjectState(OBJECT_HEADER(self));
        }
        break;
    case 0x10:
        if (self->backref != NULL) {
            despawn_object_permanently(OBJECT_HEADER(self));
        } else {
            ZeroObjectState(OBJECT_HEADER(self));
        }
        break;
    case 0x20:
        if (self->backref != NULL) {
            despawn_object(OBJECT_HEADER(self));
        } else {
            ZeroObjectState(OBJECT_HEADER(self));
        }
        break;
    }
}

void rock_dropper_idle(struct EffectObj* self)
{
}

void (*rock_dropper_state_funcs[])(struct EffectObj*) = {
    func_800BC784,
    func_800BC92C,
    rock_dropper_despawn,
    rock_dropper_idle,
};
