// EffectObj, effect_object_update_funcs[2]
// 800B5960..800B5CC4
#include "common.h"

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
        arg0->ext.scaling_x.unk14 = temp_v0;
        arg0->ext.scaling_x.unk18 = temp_v0->unk2;
        for (i = 0; i < 4; i++) {
            D_8013E188[i] = D_8010B23C[arg0->unk2][i];
        }
        g_FilterModeR = arg0->ext.scaling_x.unk14->unk3 & 1;
        g_FilterModeG = arg0->ext.scaling_x.unk14->unk3 & 2;
        g_FilterModeB = arg0->ext.scaling_x.unk14->unk3 & 4;
        color = arg0->ext.scaling_x.unk14->unk0;
        g_FilterAmountR = color & 0x1F;
        g_FilterAmountG = color & 0x3E0;
        g_FilterAmountB = color & 0x7C00;
        arg0->state++;
        return;
    }
    g_FilterAmountR = g_FilterAmountG = g_FilterAmountB = 0;
    g_FilterModeR = g_FilterModeG = g_FilterModeB = 0;

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
    if (arg0->ext.scaling_x.unk18-- == 0) {
        arg0->ext.scaling_x.unk14++;
        if (arg0->ext.scaling_x.unk14->unk0 == 0x8000) {
            if (arg0->ext.scaling_x.unk14->unk3 == 1) {
                func_8002B0C8(arg0);
                return;
            }
            arg0->ext.scaling_x.unk14 = &arg0->ext.scaling_x.unk14[arg0->ext.scaling_x.unk14->unk2];
        }
        color = arg0->ext.scaling_x.unk14->unk0;
        arg0->ext.scaling_x.unk18 = arg0->ext.scaling_x.unk14->unk2;
        g_FilterAmountR = color & 0x1F;
        g_FilterAmountG = color & 0x3E0;
        g_FilterAmountB = color & 0x7C00;
        g_FilterModeR = arg0->ext.scaling_x.unk14->unk3 & 1;
        g_FilterModeG = arg0->ext.scaling_x.unk14->unk3 & 2;
        g_FilterModeB = arg0->ext.scaling_x.unk14->unk3 & 4;
        need_palette_load |= 5;
    }
}

void func_800B5C60(struct EffectObj* arg0)
{
    s32* var_a1;
    s32* var_a2;
    u32 var_v1;

    var_a2 = arg0->ext.unk_effect2.unk14;
    var_a1 = arg0->ext.unk_effect2.unk18.ptr;

    for (var_v1 = 0; var_v1 < arg0->ext.unk_effect2.unk20 * 8; var_v1++) {
        *var_a1++ = *var_a2++;
    }

    need_palette_load |= 1;
}

void (*g_TitleScalingXUpdateFuncs[])(struct EffectObj*) = {
    func_800B599C,
    func_800B5B54,
};
