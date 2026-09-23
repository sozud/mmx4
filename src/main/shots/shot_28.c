// ShotObj, shot_object_update_funcs[28]
// 8009F46C..8009F638
#include "common.h"

u8 D_801091C0[4] = { 0xDB, 0xF2, 0x1E, 0x37 };

void func_8009F46C(struct ShotObj* arg0)
{
    struct BaseObj* unk7C = arg0->unk7C;
    arg0->x_pos.val = unk7C->x_pos.val;
    arg0->y_pos.val = unk7C->y_pos.val;
    D_801091C4[arg0->state](arg0);
}

void func_8009F4C0(struct ShotObj* self)
{
    struct WeaponObj* owner = self->unk7C;

    self->unk40 = owner->unk40;
    self->unk42 = owner->unk42 & 0x7FFF;
    self->animation_table = owner->animation_table;
    self->unk3C = owner->unk3C;
    self->unk15 = owner->unk15;
    self->bg_offset = owner->bg_offset;
    self->x_pos.val = owner->x_pos.val;
    self->y_pos.val = owner->y_pos.val;
    self->unk50.data = D_801091C0;
    self->unk5C = 1;
    self->unk16 = 4;
    self->unk54 = NULL;
    self->unk60 = 6;
    self->unk68 = NULL;
    self->unk58.data = NULL;
    func_80015D60(self, 0xB);
    self->unk5 = 2;
    self->state++;
}

void func_8009F594(struct ShotObj* arg0)
{
    struct WeaponObj* temp_v1;

    temp_v1 = arg0->unk7C;
    if (temp_v1->state >= 2) {
        arg0->state++;
        return;
    }
    if (temp_v1->animation_step.fields.frame_index == 3) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002D9BC(arg0);
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
    }
}

void func_8009F618(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_801091C4[])(struct ShotObj*) = {
    func_8009F4C0,
    func_8009F594,
    func_8009F618,
};
