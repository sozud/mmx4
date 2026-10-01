// ShotObj, shot_object_update_funcs[20]
// 8009CF38..8009D200
#include "common.h"

u8 cannon_blast_box_0[4] = { 0x80, 0xF1, 0xBE, 0x26 };
u8 cannon_blast_box_1[4] = { 0x80, 0xF1, 0xFF, 0x26 };
u8 cannon_blast_short_box[4] = { 0x80, 0xFA, 0xBD, 0x14 };
u8 cannon_blast_long_box[4] = { 0x80, 0xFA, 0xFF, 0x14 };

void cannon_blast_update(struct ShotObj* self)
{
    cannon_blast_state_funcs[self->state](self);
}

void cannon_blast_init(struct ShotObj* raw_arg0)
{
    struct ShotObj* arg0;
    s16 var_v0;
    struct WeaponObj* temp_s1;

    arg0 = raw_arg0;
    arg0->state = (u8)arg0->state + 1;
    arg0->on_screen = 1;
    temp_s1 = arg0->unk7C;
    arg0->unk68 = 0;
    arg0->unk54 = 0;
    arg0->unk58.data = (u8*)D_80105FF0;
    arg0->unk5C = 0;
    arg0->unk60 = 6;
    arg0->unk84.value = 0x6E;
    arg0->unk42 &= 0x7FFF;
    if (arg0->unk2 != 0) {
        set_animation(arg0, 4);
        arg0->unk50.data = cannon_blast_long_box;
        var_v0 = (u16)temp_s1->x_pos.i.hi - 0x177;
        arg0->x_pos.i.hi = var_v0;
    } else {
        set_animation(arg0, 3);
        arg0->unk50.data = cannon_blast_short_box;
        var_v0 = (u16)temp_s1->x_pos.i.hi - 0x77;
        arg0->x_pos.i.hi = var_v0;
    }
    arg0->y_pos.i.hi = (s16)(u16)temp_s1->y_pos.i.hi;
}

// cannon_blast_active
INCLUDE_ASM("main/nonmatchings/shots/shot_20_cannon_blast", func_8009D048);

void cannon_blast_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void cannon_blast_idle(struct ShotObj* self)
{
}

void (*cannon_blast_state_funcs[])(struct ShotObj*) = {
    cannon_blast_init,
    func_8009D048,
    cannon_blast_despawn,
    cannon_blast_idle,
};
