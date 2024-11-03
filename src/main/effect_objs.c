#include "common.h"

void func_800B56F4(struct EffectObj* arg0)
{
    D_8010A798[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B5730);

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B5798);

void func_800B58A0(struct EffectObj* arg0)
{
    D_8010AFAC[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B58DC);

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B58F4);

// scaling X animation in logo graphics
void TitleScalingXUpdate(struct EffectObj* arg0)
{
    g_TitleScalingXUpdateFuncs[arg0->state]();
}

// g_TitleScalingXUpdateFuncs state 0
void func_800B599C(struct EffectObj* arg0)
{
    u16 color;
    struct Unk14* temp_v0;
    struct EffectObj* current;
    u8 i;

    if (arg0->unk2 != -1) {
        temp_v0 = D_8010B1F8[arg0->unk2];
        arg0->unk14 = temp_v0;
        arg0->unk18.one.a = temp_v0->unk2;
        for (i = 0; i < 4; i++) {
            D_8013E188[i] = D_8010B23C[arg0->unk2][i];
        }
        D_80175E9C = arg0->unk14->unk3 & 1;
        D_80141BE4 = arg0->unk14->unk3 & 2;
        D_8013E1BC = arg0->unk14->unk3 & 4;
        color = arg0->unk14->unk0;
        D_80175EA0 = color & 0x1F;
        D_80141BE6 = color & 0x3E0;
        D_8013E1BE = color & 0x7C00;
        arg0->state++;
        return;
    }
    D_8013E1BE = 0;
    D_80141BE6 = 0;
    D_80175EA0 = 0;
    D_8013E1BC = 0;
    D_80141BE4 = 0;
    D_80175E9C = 0;

    for (current = &effect_objects[0]; current < &effect_objects[0x20]; current++) {
        if (current->unk2 == 2 && current != arg0) {
            func_8002B0C8(current);
        }
    }
    func_8002B0C8(arg0);
}

// g_TitleScalingXUpdateFuncs state 1
void func_800B5B54(struct EffectObj* arg0)
{
    u16 color;
    if (arg0->unk18.one.a-- == 0) {
        arg0->unk14++;
        if (arg0->unk14->unk0 == 0x8000) {
            if (arg0->unk14->unk3 == 1) {
                func_8002B0C8(arg0);
                return;
            }
            arg0->unk14 = &arg0->unk14[arg0->unk14->unk2];
        }
        color = arg0->unk14->unk0;
        arg0->unk18.one.a = arg0->unk14->unk2;
        D_80175EA0 = color & 0x1F;
        D_80141BE6 = color & 0x3E0;
        D_8013E1BE = color & 0x7C00;
        D_80175E9C = arg0->unk14->unk3 & 1;
        D_80141BE4 = arg0->unk14->unk3 & 2;
        D_8013E1BC = arg0->unk14->unk3 & 4;
        need_palette_load |= 5;
    }
}

void func_800B5C60(struct EffectObj* arg0)
{
    s32* var_a1;
    s32* var_a2;
    u32 var_v1;

    var_a2 = arg0->unk14;
    var_a1 = arg0->unk18.ptr;

    for (var_v1 = 0; var_v1 < arg0->unk20 * 8; var_v1++) {
        *var_a1++ = *var_a2++;
    }

    need_palette_load |= 1;
}

void func_800B5CC4(struct EffectObj* arg0)
{
    if (arg0->state == 0) {
        func_800B5D04(arg0);
        return;
    }
    func_800B5E2C(arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B5D04);

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B5E2C);

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B5EB0);

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B5EEC);

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B6060);

void func_800B6080(struct EffectObj* arg0)
{
    D_8010B444[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B60BC);

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B649C);

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B64BC);

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B6660);

void func_800B6A0C(struct EffectObj* arg0)
{
    D_8010B45C[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B6A48);

INCLUDE_ASM("asm/us/main/nonmatchings/effect_objs", func_800B6A90);