// WeaponObj, weapon_object_update_funcs[8]
// 80097860..80097EEC
#include "common.h"

void func_80097860(struct WeaponObj* arg0)
{
    s32 should_reset = g_Player.input_locked != 0;

    if (g_Player.capsule_state != 0) {
        should_reset = 1;
    }
    if (g_Player.weapon != 8) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    D_80108A24[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_08", func_800978DC);

void func_80097A24(struct WeaponObj* arg0)
{
    if ((func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) && (arg0->unk98 == 0)) {
        if (arg0->ext.weapon_8.timer != 0) {
            arg0->ext.weapon_8.timer--;
            func_80015DC8(ANIMATED_OBJECT(arg0));
            func_8002B718(MOVING_OBJECT(arg0));
            arg0->unk50 = (const u8*)&D_801089FC[arg0->animation_step.fields.event];
            func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
            return;
        }
    }

    func_80097B14(arg0);
}

void func_80097AC8(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.shot_count--;
    g_Player.special_shot_count--;
    ZeroObjectState((struct ObjectHeader*)arg0);
}

void func_80097B14(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
}

// WeaponObj, weapon_object_update_funcs[17]

void func_80097B28(struct WeaponObj* arg0)
{
    s32 should_reset = g_Player.input_locked != 0;

    if (g_Player.capsule_state != 0) {
        should_reset = 1;
    }
    if (g_Player.weapon != 8) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    D_80108A34[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_08", func_80097BA4);

void func_80097CF4(struct WeaponObj* arg0)
{
    struct MiscObj* misc_obj;
    u8 timer;

    if (func_8002B1E8((struct BaseObj*)arg0, 0x20, 0x20) == 0) {
        timer = arg0->ext.weapon_17.timer;
        if (timer == 0) {
            arg0->ext.weapon_17.timer = 3;
            misc_obj = find_free_misc_obj();
            if (misc_obj != 0) {
                misc_obj->active = 1;
                misc_obj->id = 0x29;
                misc_obj->unk2 = ((s8)arg0->unk2) >> 1;
                misc_obj->bg_offset = arg0->bg_offset;
                misc_obj->x_pos.val = arg0->x_pos.val;
                misc_obj->y_pos.val = arg0->y_pos.val;
                misc_obj->unk15 = arg0->unk15;
            }
        } else {
            arg0->ext.weapon_17.timer = timer - 1;
        }
        func_80015DC8((struct AnimatedObj*)arg0);
        func_8002B718((struct MovingObj*)arg0);
        func_8002B318((struct BaseObj*)arg0, 0x20, 0x20);
        return;
    }
    func_80097B14(arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_08", func_80097DD8);

struct Unk_unk68 D_801089FC[] = {
    { -8, -12, 0x14, 0x18 },
    { -12, -16, 0x1C, 0x22 },
    { -14, -20, 0x26, 0x2C },
    { -8, -14, 0x14, 0x18 },
    { -12, -20, 0x1C, 0x22 },
    { -14, -26, 0x26, 0x2C },
};

struct Unk_unk68 D_80108A14[] = {
    { -16, -16, 0x26, 0x26 },
    { -16, -18, 0x26, 0x26 },
    { -16, -20, 0x26, 0x26 },
    { -16, -22, 0x26, 0x26 },
};

void (*D_80108A24[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_800978DC,
    (void (*)(struct WeaponObj*))func_80097A24,
    (void (*)(struct WeaponObj*))func_80097AC8,
    (void (*)(struct WeaponObj*))func_80097AC8,
};

void (*D_80108A34[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80097BA4,
    (void (*)(struct WeaponObj*))func_80097CF4,
    (void (*)(struct WeaponObj*))func_80097AC8,
    (void (*)(struct WeaponObj*))func_80097AC8,
};

u8 D_80108A44[] = {
    0x04,
    0x03,
    0x02,
    0x01,
    0x1F,
    0x1E,
    0x1D,
    0x1C,
};
