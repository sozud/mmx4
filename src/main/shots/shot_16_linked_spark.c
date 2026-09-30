// ShotObj, shot_object_update_funcs[16]
// 8009C364..8009C5F0
#include "common.h"

void linked_spark_update(struct ShotObj* self)
{
    linked_spark_state_funcs[self->state](self);
}

void linked_spark_init(struct ShotObj* rawArg0)
{
    struct ShotObj* arg0 = rawArg0;
    s32 value;

    value = 1;
    arg0->state = value;
    arg0->on_screen = value;
    arg0->unk5C = value;
    value = arg0->unk2;
    arg0->unk16 = 6;
    arg0->unk68 = 0;
    arg0->unk54 = 0;
    arg0->unk50.data = 0;
    arg0->unk60 = 4;

    switch (value) {
    case 0:
        arg0->unk84.value = 6;
        arg0->unk15 = 0;
        break;
    case 1:
        arg0->unk84.value = 6;
        arg0->unk15 = 0x40;
        break;
    case 2:
        arg0->unk84.value = 9;
        break;
    case 3:
        arg0->unk84.value = 0xC;
        break;
    }

    set_animation(arg0, arg0->unk84.value);
}

// linked_spark_main
INCLUDE_ASM("main/nonmatchings/shots/shot_16_linked_spark", func_8009C45C);

void linked_spark_despawn(struct ShotObj* self)
{
    struct WeaponObj* weapon;

    weapon = self->unk7C;
    if ((weapon->active != 0) && (weapon->id == 0x1D) && (weapon->unk2 >= 0)) {
        weapon->ext.weapon_29.unk90 = 0;
        weapon->unk80.bytes[1] &= 0xFE;
    }
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*linked_spark_state_funcs[])(struct ShotObj*) = {
    linked_spark_init,
    func_8009C45C,
    linked_spark_despawn,
};
