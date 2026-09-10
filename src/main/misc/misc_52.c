// MiscObj, misc_object_update_funcs[52]
// 800D2190..800D2A74
#include "common.h"

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2190);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2420);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D24B4);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D254C);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D25AC);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D25FC);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D26F4);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2794);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2854);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D28BC);

void func_800D28E8(struct MiscObj* arg0)
{
    D_8010F528[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2924);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2970);

void func_800D29C0(struct PlayerObj* arg0)
{
    D_8010F530[arg0->unk6](arg0);
}

void func_800D29FC(struct BarObj* arg0)
{
    D_8010F538[arg0->unk5](arg0);
}

void func_800D2A38(struct MiscObj* arg0)
{
    D_8010F544[arg0->state](arg0);
}

union AnimationStep D_8010F4E4[5] = {
    { .packed = 0x0001003A },
    { .packed = 0x04010008 },
    { .packed = 0x05010021 },
    { .packed = 0x04010008 },
    { .packed = 0x00FC003A },
};

union AnimationStep D_8010F4F8[3] = {
    { .packed = 0x01010001 },
    { .packed = 0x02010001 },
    { .packed = 0x03FE0001 },
};

union AnimationStep* D_8010F504[2] = { D_8010F4E4, D_8010F4F8 };

void (*D_8010F50C[3])(struct MiscObj*) = {
    func_800D2420,
    func_800D24B4,
    func_800D254C,
};
void (*D_8010F518[4])(struct MiscObj*) = {
    func_800D25AC,
    func_800D25FC,
    func_800D26F4,
    func_800D26F4,
};
void (*D_8010F528[2])(struct MiscObj*) = { func_800D2854, func_800D28BC };
void (*D_8010F530[2])(struct PlayerObj*) = { func_800D2854, func_800D2970 };
void (*D_8010F538[3])(struct BarObj*) = {
    func_800D28E8,
    func_800D2924,
    func_800D29C0,
};
void (*D_8010F544[3])(struct MiscObj*) = {
    func_800D2190,
    func_800D2794,
    func_800D29FC,
};
