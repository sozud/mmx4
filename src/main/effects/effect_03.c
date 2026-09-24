// EffectObj, effect_object_update_funcs[3]
// 800B5CC4..800B5EB0
#include "common.h"

void func_800B5CC4(struct EffectObj* arg0)
{
    if (arg0->state == 0) {
        func_800B5D04(arg0);
        return;
    }
    func_800B5E2C(arg0);
}

INCLUDE_ASM("main/nonmatchings/effects/effect_03", func_800B5D04);

void func_800B5E2C(struct EffectObj* arg0)
{
    if (arg0->ext.palette_animation.timer-- == 0) {
        arg0->ext.palette_animation.cursor += 2;
        if (arg0->ext.palette_animation.cursor[1] < 0) {
            arg0->ext.palette_animation.cursor += arg0->ext.palette_animation.cursor[1] * 2;
        }
        arg0->ext.palette_animation.timer = arg0->ext.palette_animation.cursor[1];
        arg0->ext.palette_animation.source = SP_ARC_30 + ((u8)arg0->ext.palette_animation.cursor[0] << 3);
        func_800B5C60(arg0);
    }
}

extern s8* D_800F49DC[10];
extern s8* D_800F4A3C[3];
extern s8* D_800F4F6C[6];
extern s8* D_800F4FE8[5];
extern s8* D_800F54E8[3];
extern s8* D_800F55A8[9];
extern s8* D_800F60F8[2];
extern s8* D_800F6100[4];
extern s8* D_800F664C[6];
extern s8* D_800F6670[7];
extern s8* D_800F6A40[4];
extern s8* D_800F6AA4[5];
extern s8* D_800F7158[2];
extern s8* D_800F71EC[4];
extern s8* D_800F768C[3];
extern s8* D_800F7AA0[2];
extern s8* D_800F8174[1];
extern s8* D_800F81CC[3];
extern s8* D_800F8430[4];
extern s8* D_800F8458[4];
extern s8* D_800F8760[3];
extern s8* D_800F87B4[3];
extern s8* D_800F8978[1];
extern u16 D_800F4A04[10];
extern u16 D_800F4A48[4];
extern u16 D_800F4F84[6];
extern u16 D_800F4FFC[6];
extern u16 D_800F54F4[4];
extern u16 D_800F55CC[10];
extern u16 D_800F6110[2];
extern u16 D_800F6114[4];
extern u16 D_800F6664[6];
extern u16 D_800F668C[8];
extern u16 D_800F6A50[4];
extern u16 D_800F6AB8[6];
extern u16 D_800F7160[2];
extern u16 D_800F71FC[4];
extern u16 D_800F7698[4];
extern u16 D_800F7AA8[2];
extern u16 D_800F8178[2];
extern u16 D_800F81D8[4];
extern u16 D_800F8440[4];
extern u16 D_800F8468[4];
extern u16 D_800F876C[4];
extern u16 D_800F87C0[4];
extern u16 D_800F897C[2];

u16* D_8010B354[27] = {
    D_800F4A04,
    D_800F4A48,
    D_800F4F84,
    D_800F4FFC,
    D_800F54F4,
    D_800F55CC,
    D_800F6110,
    D_800F6114,
    D_800F6664,
    D_800F668C,
    D_800F6A50,
    D_800F6AB8,
    D_800F7160,
    D_800F71FC,
    NULL,
    D_800F7698,
    NULL,
    D_800F7AA8,
    D_800F8178,
    NULL,
    D_800F81D8,
    NULL,
    D_800F8440,
    D_800F8468,
    D_800F876C,
    D_800F87C0,
    D_800F897C,
};

s8** D_8010B3C0[27] = {
    D_800F49DC,
    D_800F4A3C,
    D_800F4F6C,
    D_800F4FE8,
    D_800F54E8,
    D_800F55A8,
    D_800F60F8,
    D_800F6100,
    D_800F664C,
    D_800F6670,
    D_800F6A40,
    D_800F6AA4,
    D_800F7158,
    D_800F71EC,
    NULL,
    D_800F768C,
    NULL,
    D_800F7AA0,
    D_800F8174,
    NULL,
    D_800F81CC,
    NULL,
    D_800F8430,
    D_800F8458,
    D_800F8760,
    D_800F87B4,
    D_800F8978,
};

void (*D_8010B42C[])(struct EffectObj*) = {
    func_800B5D04,
    func_800B5E2C,
};
