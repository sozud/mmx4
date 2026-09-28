// WeaponObj, weapon_object_update_funcs[4]
// 800951C0..800957B0
#include "common.h"

void func_800951C0(struct WeaponObj* arg0)
{
    s32 disabled;

    disabled = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        disabled = 1;
    }
    if (g_Player.weapon != 4) {
        disabled = 1;
    }
    if (g_Player.shot_type == 0xD) {
        disabled = 1;
    }
    if (disabled != 0) {
        arg0->state = 3;
    }
    D_80108920[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_04", func_80095254);

void func_800953D0(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x28) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B718(MOVING_OBJECT(arg0));
        func_8009547C(arg0);
        return;
    }

    arg0->on_screen = 0;
    arg0->state = 3;
}

void func_80095430(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.shot_count--;
    g_Player.special_shot_count--;
    ZeroObjectState((struct ObjectHeader*)arg0);
}

void func_8009547C(struct WeaponObj* arg0)
{
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x28);
}

// WeaponObj, weapon_object_update_funcs[13]

void func_800954BC(struct WeaponObj* arg0)
{
    s32 should_reset = g_Player.input_locked != 0;

    if (g_Player.capsule_state != 0) {
        should_reset = 1;
    }
    if (g_Player.weapon != 4) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    D_80108934[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_04", func_80095538);

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

struct Unk_unk68 D_8010890C[] = {
    { -22, -32, 0x2A, 0x36 },
};

struct Unk_unk68 D_80108910[] = {
    { 0, 0, 0, 0 },
    { -16, -10, 0x1C, 0x14 },
    { -34, -36, 0x3C, 0x34 },
    { -40, -50, 0x40, 0x56 },
};

void (*D_80108920[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80095254,
    (void (*)(struct WeaponObj*))func_800953D0,
    (void (*)(struct WeaponObj*))func_80095430,
    (void (*)(struct WeaponObj*))func_80095430,
};

u8 D_80108930[4] = {
    0xF5,
    0xF6,
    0x06,
    0xF4,
};

void (*D_80108934[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80095538,
    (void (*)(struct WeaponObj*))func_8009564C,
    (void (*)(struct WeaponObj*))func_80095430,
    (void (*)(struct WeaponObj*))func_80095430,
};
