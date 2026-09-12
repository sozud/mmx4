// MiscObj, misc_object_update_funcs[44]
// 800D07EC..800D0E48
#include "common.h"

void func_800D07EC(struct MiscObj* arg0)
{
    D_8010F084[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0828);

void func_800D0988(struct MiscObj* arg0)
{
    func_800D0C68(arg0);
    D_8010F090[arg0->unk5](UNK_OBJECT(arg0));
    func_8002B318(BASE_OBJECT(arg0), 0x48, 0x48);
}

void func_800D09E4(struct MiscObj* arg0)
{
    func_8002B108(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_44", func_800D0A04);

void func_800D0AA4(struct UnkObj* arg0)
{
    if (background_objects[g_Player.bg_offset].x_pos.i.hi == 0xFD0) {
        func_80036AE4(0x15, 0);
        arg0->ext.timer = 0x3C;
        arg0->unk5 = 2;
    }
}

void func_800D0B14(struct UnkObj* arg0)
{
    s8 timer;

    timer = arg0->ext.timer - 1;
    arg0->ext.timer = timer;
    if (timer == 0) {
        func_8002217C(0x29, 1, 0);
        arg0->unk5 = 3;
    }
}

void func_800D0B68(struct UnkObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->ext.timer = 0x3C;
        arg0->unk5 = 4;
    }
}

void func_800D0B90(struct UnkObj* arg0)
{
    s8 timer;

    timer = arg0->ext.timer - 1;
    arg0->ext.timer = timer;
    if (timer == 0) {
        func_8002217C(0x2A, 2, 0);
        arg0->unk5 = 5;
    }
}

void func_800D0BE4(struct UnkObj* arg0)
{
    if (abc_object.unkC == 0) {
        background_objects[g_Player.bg_offset].unk24 = 0x11B0;
        func_80036B18();
        ENGINE_UNK2E = 1;
        arg0->unk5 = 6;
    }
}

void func_800D0C60(struct UnkObj* arg0)
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

void (*D_8010F090[7])(struct UnkObj*) = {
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
