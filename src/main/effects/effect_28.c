// EffectObj, effect_object_update_funcs[28]
// 800BBC14..800BC144
#include "common.h"

void func_800BBC14(struct EffectObj* arg0)
{
    D_8010BED4[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_28", func_800BBC50);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_28", func_800BBD24);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_28", func_800BBD88);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_28", func_800BBE84);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_28", func_800BBEA4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_28", func_800BBF34);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_28", func_800BBFCC);

void (*D_8010BED4[])(struct EffectObj*) = {
    func_800BBC50,
    func_800BBD24,
    func_800BBD88,
    func_800BBE84,
};
