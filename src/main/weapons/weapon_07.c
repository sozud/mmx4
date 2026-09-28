// WeaponObj, weapon_object_update_funcs[7]
// 80096E10..80097860
#include "common.h"

void func_80096E10(struct WeaponObj* arg0)
{
    s32 disabled;

    disabled = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        disabled = 1;
    }
    if (g_Player.weapon != 7) {
        disabled = 1;
    }
    if (g_Player.shot_type == 0x10) {
        disabled = 1;
    }
    if (disabled != 0) {
        arg0->state = 3;
    }
    D_801089C4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80096EA4);

void func_80097048(struct WeaponObj* arg0)
{
    u8 temp_v0;

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        D_801089D8[arg0->unk5](arg0);
        if (arg0->unk50 != 0) {
            temp_v0 = arg0->ext.weapon_7.unk91;
            if (temp_v0 == 0) {
                arg0->ext.weapon_7.unk91 = 4;
                arg0->unk64++;
                return;
            }
            arg0->ext.weapon_7.unk91 = temp_v0 - 1;
        }
    } else {
        func_800972C8(arg0);
    }
}

void func_800970EC(struct WeaponObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 1);
        arg0->unk5++;
    }
    func_80097328(arg0);
}

void func_80097144(struct WeaponObj* arg0)
{
    if (func_80097214(arg0) == 0) {
        if (arg0->unk98 != 0) {
            arg0->unk98 = 0;
            arg0->unk5++;
        } else {
            if (arg0->ext.weapon_7.unk90 != 0) {
                arg0->ext.weapon_7.unk90--;
                if (arg0->ext.weapon_7.unk90 == 0) {
                    arg0->unk2C = FIXED(-0.21484375);
                }
            }
            func_80015DC8(ANIMATED_OBJECT(arg0));
            func_8002B694(ANIMATED_OBJECT(arg0));
        }
        func_80097328(arg0);
    }
}

void func_800971D4(struct WeaponObj* arg0)
{
    if (func_80097214(arg0) == 0) {
        func_80015DC8(arg0);
        func_80097328(arg0);
    }
}

s32 func_80097214(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_7.timer == 0) {
        func_80015D60(arg0, 2);
        arg0->unk50 = 0;
        arg0->unk5 = 3;
        func_80097328(arg0);
        return 1;
    }

    arg0->ext.weapon_7.timer--;
    return 0;
}

void func_80097278(struct WeaponObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        func_800972C8(arg0);
    } else {
        func_80097328(arg0);
    }
}

void func_800972C8(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
}

void func_800972DC(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.shot_count--;
    g_Player.special_shot_count--;
    ZeroObjectState((struct ObjectHeader*)arg0);
}

void func_80097328(struct WeaponObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    } else {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x30);
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

// WeaponObj, weapon_object_update_funcs[16]

void func_80097384(struct WeaponObj* arg0)
{
    s32 var_a1;

    var_a1 = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        var_a1 = 1;
    }
    if (g_Player.weapon != 7) {
        var_a1 = 1;
    }
    if (g_Player.actions_reset != 0) {
        var_a1 = 1;
    }
    if (g_Player.hp == 0) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        arg0->state = 3;
    }
    D_801089E8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80097430);

void func_800975DC(struct WeaponObj* arg0)
{
    if (func_80097780(arg0) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (func_8002B1E8(BASE_OBJECT(arg0), 0x18, 0x30) == 0) {
            if (arg0->unk5 == 0) {
                func_80097670(arg0);
            } else {
                func_800976DC(arg0);
            }
        } else {
            arg0->on_screen = 0;
            arg0->state = 2;
            arg0->unk50 = 0;
        }
        func_800977D4(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80097670);

void func_800976DC(struct WeaponObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->ext.weapon_16.unk91 == 0) {
        arg0->ext.weapon_16.unk91 = 4;
        arg0->unk64++;
    } else {
        arg0->ext.weapon_16.unk91--;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x18, 0x30);
}

void func_80097740(struct WeaponObj* arg0)
{
    if (func_80097780(arg0) == 0) {
        func_80015DC8(arg0);
        func_800977D4(arg0);
    }
}

s32 func_80097780(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_16.timer == 0) {
        func_800972C8(arg0);
        func_800977D4(arg0);
        return 1;
    }
    arg0->ext.weapon_16.timer--;
    return 0;
}

void func_800977D4(struct WeaponObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x30);
    }
}

void func_80097804(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    if (arg0->unk2 == 0) {
        g_Player.shot_count--;
        g_Player.special_shot_count--;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

struct Unk_unk68 D_801089BC[] = {
    { -16, -16, 0x20, 0x20 },
};

struct Unk_unk68 D_801089C0[] = {
    { -12, -28, 0x18, 0x36 },
};

void (*D_801089C4[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80096EA4,
    (void (*)(struct WeaponObj*))func_80097048,
    (void (*)(struct WeaponObj*))func_800972DC,
    (void (*)(struct WeaponObj*))func_800972DC,
};

u8 D_801089D4[4] = {
    0xEF,
    0xF9,
    0x1A,
    0xF9,
};

void (*D_801089D8[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_800970EC,
    (void (*)(struct WeaponObj*))func_80097144,
    (void (*)(struct WeaponObj*))func_800971D4,
    (void (*)(struct WeaponObj*))func_80097278,
};

void (*D_801089E8[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80097430,
    (void (*)(struct WeaponObj*))func_800975DC,
    (void (*)(struct WeaponObj*))func_80097740,
    (void (*)(struct WeaponObj*))func_80097804,
};

u8 D_801089F8[4] = {
    0xF0,
    0xF9,
    0x1F,
    0xF9,
};
