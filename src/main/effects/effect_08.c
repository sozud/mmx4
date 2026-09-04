// EffectObj, effect_object_update_funcs[8]
// 800B7078..800B75C8
#include "common.h"

void func_800B7078(struct EffectObj* arg0)
{
    D_8010B4D8[arg0->state](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B70B4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B70EC);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B7140);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B7180);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B71A8);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B72C4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B7304);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B7318);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B7328);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B7368);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B7394);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B73D4);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B7414);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B7440);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B7480);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B74C0);

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B74EC);

void func_800B7520(struct EffectObj* arg0)
{
}

INCLUDE_ASM("asm/us/main/nonmatchings/effects/effect_08", func_800B7528);

void (*D_8010B4D8[])(struct EffectObj*) = {
    func_800B70B4,
    func_800B70EC,
};
