// MiscObj, misc_object_update_funcs[44]
// 800D07EC..800D0E48
#include "common.h"

#ifdef VERSION_JP
INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0820_jp);
#endif

void func_800D07EC(struct MiscObj* arg0)
{
    D_8010F084[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0828);

INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0988);

void func_800D09E4(struct MiscObj* arg0)
{
    func_8002B108(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0A04);

INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0AA4);

INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0B14);

INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0B68);

INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0B90);

INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0BE4);

void func_800D0C60(void)
{
}

INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0C68);

INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0D68);

union AnimationStep D_8010F040[6] = {
    { .packed = 0x00010048 },
    { .packed = 0x01010002 },
    { .packed = 0x02010003 },
    { .packed = 0x00010006 },
    { .packed = 0x01010002 },
    { .packed = 0x02FB0003 },
};

union AnimationStep D_8010F058[2] = {
    { .packed = 0x03010005 },
    { .packed = 0x03000101 },
};

union AnimationStep D_8010F060[6] = {
    { .packed = 0x04010048 },
    { .packed = 0x05010002 },
    { .packed = 0x06010003 },
    { .packed = 0x04010006 },
    { .packed = 0x05010002 },
    { .packed = 0x06FB0003 },
};

union AnimationStep* D_8010F078[3] = {
    D_8010F040,
    D_8010F058,
    D_8010F060,
};

void (*D_8010F084[3])(struct MiscObj*) = {
    func_800D0828,
    func_800D0988,
    func_800D09E4,
};

void (*D_8010F090[7])(struct MiscObj*) = {
    func_800D0A04,
    func_800D0AA4,
    func_800D0B14,
    func_800D0B68,
    func_800D0B90,
    func_800D0BE4,
    func_800D0C60,
};

u8 D_8010F0AC[24] = {
    0,
    2,
    4,
    5,
    6,
    7,
    9,
    10,
    12,
    1,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    3,
    8,
    11,
#ifdef VERSION_JP
    0,
#else
    21,
#endif
    0,
    0,
};
