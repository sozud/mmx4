// WeaponObj, weapon_object_update_funcs[57]
// 80098838..80098990
#include "common.h"

void func_80098838(struct WeaponObj* arg0)
{
    D_80108BA8[arg0->state](arg0);
}

void func_80098874(struct WeaponObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk50 = D_80108BA4;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk54 = 0;
    arg0->pad58[4] = 1;
    arg0->pad58[8] = 3;
    func_80015D60(arg0, 0xC);
}

void func_800988C4(struct WeaponObj* arg0)
{
    s8 temp_v1;
    struct PlayerObj* temp_a0;
    struct WeaponObj* self = arg0;
    temp_a0 = self->owner;
    if (temp_a0->state < 2) {
        temp_v1 = temp_a0->unk5;
        if ((temp_v1 == 5) || (temp_v1 == 0)) {
            self->on_screen = 0;
            if (temp_a0->animation_step.fields.frame_index == 3) {
                self->x_pos.val = temp_a0->x_pos.val;
                self->y_pos.val = temp_a0->y_pos.val;
                func_80015DC8(ANIMATED_OBJECT(self));
                func_8002B318(BASE_OBJECT(self), 0x10, 0x10);
            }
            return;
        }
    }

    self->state = 2;
    self->on_screen = 0;
}

void func_80098970(struct WeaponObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 D_80108B94[8] = { 2, 0x1E, 0, 4, 0, 0, 0, 0 };

u8 D_80108B9C[8] = { 0x0F, 0x0E, 0x0D, 0x10, 0x0D, 0, 0, 0 };

u8 D_80108BA4[4] = { 0xCF, 0xEE, 0x3C, 0x37 };

void (*D_80108BA8[])(struct WeaponObj*) = {
    func_80098874,
    func_800988C4,
    func_80098970,
};
