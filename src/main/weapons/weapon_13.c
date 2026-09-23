// WeaponObj, weapon_object_update_funcs[13]
// 800954BC..800957B0
#include "common.h"

void func_800954BC(struct WeaponObj* arg0)
{
    s32 should_reset = g_Player.unkC3 != 0;

    if (g_Player.unkC4 != 0) {
        should_reset = 1;
    }
    if (g_Player.unk93 != 4) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    D_80108934[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_13", func_80095538);

void func_8009564C(struct WeaponObj* self)
{
    u8 timer;
    s8 event;
    u8* timer_ptr = &self->ext.weapon_13.timer;

    if (func_8002B1E8(BASE_OBJECT(self), 0x38, 0x38) == 0) {
        func_80015DC8(ANIMATED_OBJECT(self));
        if (self->unk5 == 0) {
            if (g_Player.unk17 == 0x67) {
                func_8002B718(MOVING_OBJECT(self));
                self->unk5++;
            } else {
                self->x_pos.val = g_Player.x_pos.val;
                self->y_pos.val = g_Player.y_pos.val;
            }
        } else {
            func_8002B718(MOVING_OBJECT(self));
        }

        event = self->animation_step.fields.event;
        if (event != 0) {
            self->unk50 = &D_80108910[event];
        } else {
            self->unk50 = NULL;
        }

        timer = *timer_ptr;
        if (timer == 0) {
            *timer_ptr = 4;
            self->unk64++;
        } else {
            *timer_ptr = timer - 1;
        }
        func_80095770(self);
    } else {
        self->on_screen = 0;
        self->state = 3;
    }
}

void func_80095770(struct WeaponObj* arg0)
{
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    func_8002B318(BASE_OBJECT(arg0), 0x38, 0x38);
}
