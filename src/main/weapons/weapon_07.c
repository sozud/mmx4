// WeaponObj, weapon_object_update_funcs[7]
// 80096E10..80097384
#include "common.h"

void func_80096E10(struct WeaponObj* arg0)
{
    s32 disabled;

    disabled = g_Player.unkC3 != 0;
    if (g_Player.unkC4 != 0) {
        disabled = 1;
    }
    if (g_Player.unk93 != 7) {
        disabled = 1;
    }
    if (g_Player.unk96 == 0x10) {
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
            temp_v0 = arg0->ext.raw[5];
            if (temp_v0 == 0) {
                arg0->ext.raw[5] = 4;
                arg0->unk64++;
                return;
            }
            arg0->ext.raw[5] = temp_v0 - 1;
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
            if (arg0->ext.raw[4] != 0) {
                arg0->ext.raw[4]--;
                if (arg0->ext.raw[4] == 0) {
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
    g_Player.unk98--;
    g_Player.unk99--;
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
