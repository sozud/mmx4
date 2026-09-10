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

#ifdef VERSION_JP
#define EFFECT_STAGE_DATA(address) ((address) + 0x13C)
#else
#define EFFECT_STAGE_DATA(address) (address)
#endif

u16* D_8010B354[27] = {
    (u16*)EFFECT_STAGE_DATA(0x800F4A04),
    (u16*)EFFECT_STAGE_DATA(0x800F4A48),
    (u16*)EFFECT_STAGE_DATA(0x800F4F84),
    (u16*)EFFECT_STAGE_DATA(0x800F4FFC),
    (u16*)EFFECT_STAGE_DATA(0x800F54F4),
    (u16*)EFFECT_STAGE_DATA(0x800F55CC),
    (u16*)EFFECT_STAGE_DATA(0x800F6110),
    (u16*)EFFECT_STAGE_DATA(0x800F6114),
    (u16*)EFFECT_STAGE_DATA(0x800F6664),
    (u16*)EFFECT_STAGE_DATA(0x800F668C),
    (u16*)EFFECT_STAGE_DATA(0x800F6A50),
    (u16*)EFFECT_STAGE_DATA(0x800F6AB8),
    (u16*)EFFECT_STAGE_DATA(0x800F7160),
    (u16*)EFFECT_STAGE_DATA(0x800F71FC),
    NULL,
    (u16*)EFFECT_STAGE_DATA(0x800F7698),
    NULL,
    (u16*)EFFECT_STAGE_DATA(0x800F7AA8),
    (u16*)EFFECT_STAGE_DATA(0x800F8178),
    NULL,
    (u16*)EFFECT_STAGE_DATA(0x800F81D8),
    NULL,
    (u16*)EFFECT_STAGE_DATA(0x800F8440),
    (u16*)EFFECT_STAGE_DATA(0x800F8468),
    (u16*)EFFECT_STAGE_DATA(0x800F876C),
    (u16*)EFFECT_STAGE_DATA(0x800F87C0),
    (u16*)EFFECT_STAGE_DATA(0x800F897C),
};

s8** D_8010B3C0[27] = {
    (s8**)EFFECT_STAGE_DATA(0x800F49DC),
    (s8**)EFFECT_STAGE_DATA(0x800F4A3C),
    (s8**)EFFECT_STAGE_DATA(0x800F4F6C),
    (s8**)EFFECT_STAGE_DATA(0x800F4FE8),
    (s8**)EFFECT_STAGE_DATA(0x800F54E8),
    (s8**)EFFECT_STAGE_DATA(0x800F55A8),
    (s8**)EFFECT_STAGE_DATA(0x800F60F8),
    (s8**)EFFECT_STAGE_DATA(0x800F6100),
    (s8**)EFFECT_STAGE_DATA(0x800F664C),
    (s8**)EFFECT_STAGE_DATA(0x800F6670),
    (s8**)EFFECT_STAGE_DATA(0x800F6A40),
    (s8**)EFFECT_STAGE_DATA(0x800F6AA4),
    (s8**)EFFECT_STAGE_DATA(0x800F7158),
    (s8**)EFFECT_STAGE_DATA(0x800F71EC),
    NULL,
    (s8**)EFFECT_STAGE_DATA(0x800F768C),
    NULL,
    (s8**)EFFECT_STAGE_DATA(0x800F7AA0),
    (s8**)EFFECT_STAGE_DATA(0x800F8174),
    NULL,
    (s8**)EFFECT_STAGE_DATA(0x800F81CC),
    NULL,
    (s8**)EFFECT_STAGE_DATA(0x800F8430),
    (s8**)EFFECT_STAGE_DATA(0x800F8458),
    (s8**)EFFECT_STAGE_DATA(0x800F8760),
    (s8**)EFFECT_STAGE_DATA(0x800F87B4),
    (s8**)EFFECT_STAGE_DATA(0x800F8978),
};

#undef EFFECT_STAGE_DATA

void (*D_8010B42C[])(struct EffectObj*) = {
    func_800B5D04,
    func_800B5E2C,
};
