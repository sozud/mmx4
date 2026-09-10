// MiscObj, misc_object_update_funcs[46]
// 800D1284..800D1990
#include "common.h"

void func_800D1284(struct MiscObj* arg0)
{
    D_8010F1A4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D12C0);

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D1464);

void func_800D14D8(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D14F8);

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D154C);

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D15A8);

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D1614);

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D166C);

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D16E0);

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D1708);

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D177C);

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D17F0);

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D1864);

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D188C);

INCLUDE_ASM("main/nonmatchings/misc/misc_46", func_800D18C0);

union AnimationStep D_8010F194[1] = {
    { .packed = 0x00000101 },
};

union AnimationStep D_8010F198[1] = {
    { .packed = 0x01000101 },
};

union AnimationStep* D_8010F19C[2] = {
    D_8010F194,
    D_8010F198,
};

void (*D_8010F1A4[3])(struct MiscObj*) = {
    func_800D12C0,
    func_800D1464,
    func_800D14D8,
};

void (*D_8010F1B0[11])(struct MiscObj*) = {
    func_800D14F8,
    func_800D154C,
    func_800D15A8,
    func_800D1614,
    func_800D166C,
    func_800D16E0,
    func_800D1708,
    func_800D177C,
    func_800D17F0,
    func_800D1864,
    func_800D188C,
};
