// MiscObj, misc_object_update_funcs[53]
// 800D2A74..800D3084
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2A74);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2B9C);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2C04);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2CA4);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2D7C);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2DCC);

void func_800D2E1C(struct MiscObj* arg0)
{
    struct EffectObj* effect;

    arg0->ext.misc_53.timer = 0x12C;
    arg0->unk5++;
    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 0x41;
        effect->id = 0x1C;
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2E64);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2EDC);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2F34);

INCLUDE_ASM("main/nonmatchings/misc/misc_53", func_800D2FC4);

void func_800D301C(struct MiscObj* arg0)
{
    engine_obj.unkF = 1;
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_800D3048(struct MiscObj* arg0)
{
    D_8010F580[arg0->state](arg0);
}

union AnimationStep D_8010F550[3] = {
    { .packed = 0x00010001 },
    { .packed = 0x01010001 },
    { .packed = 0x02FE0001 },
};
union AnimationStep* D_8010F55C[1] = { D_8010F550 };

void (*D_8010F560[8])(struct MiscObj*) = {
    func_800D2B9C,
    func_800D2C04,
    func_800D2CA4,
    func_800D2D7C,
    func_800D2DCC,
    func_800D2E1C,
    func_800D2E64,
    func_800D2EDC,
};
void (*D_8010F580[3])(struct MiscObj*) = {
    func_800D2A74,
    func_800D2FC4,
    func_800D301C,
};
