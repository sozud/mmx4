// ShotObj, shot_object_update_funcs[57]
// 800AE450..800AE6B4
#include "common.h"

u16 D_80109F50[6][2] = {
    { 0x4AE, 0x29C },
    { 0x49F, 0x279 },
    { 0x49D, 0x259 },
    { 0x49B, 0x231 },
    { 0x49D, 0x259 },
    { 0x49D, 0x259 },
};

s16 D_80109F68[30][2] = {
    { -7040, 16672 },
    { -5984, 14112 },
    { -4672, 11296 },
    { -3104, 8224 },
    { -768, 5408 },
    { -1504, 3104 },
    { -704, 1568 },
    { 7040, 14368 },
    { 6048, 11808 },
    { 5312, 8736 },
    { 4320, 6176 },
    { 3072, 3872 },
    { 1824, 3088 },
    { 1328, 1808 },
    { 576, 1056 },
    { 13440, 14368 },
    { 11936, 10528 },
    { 10432, 7712 },
    { 8160, 5152 },
    { 5888, 3360 },
    { 3616, 1056 },
    { 576, 1056 },
    { 16604, 4172 },
    { 12533, 4157 },
    { 8217, 4132 },
    { 4156, 4108 },
    { 592, 4104 },
    { 23442, 12512 },
    { 23392, 12477 },
    { -22144, -5832 },
};

u8 D_80109FE0[6][2] = {
    { 22, 4 },
    { 15, 6 },
    { 7, 7 },
    { 0, 6 },
    { 29, 1 },
    { 27, 2 },
};

s16* D_80109FEC[30] = {
    D_80109F68[0],
    D_80109F68[1],
    D_80109F68[2],
    D_80109F68[3],
    D_80109F68[4],
    D_80109F68[5],
    D_80109F68[6],
    D_80109F68[7],
    D_80109F68[8],
    D_80109F68[9],
    D_80109F68[10],
    D_80109F68[11],
    D_80109F68[12],
    D_80109F68[13],
    D_80109F68[14],
    D_80109F68[15],
    D_80109F68[16],
    D_80109F68[17],
    D_80109F68[18],
    D_80109F68[19],
    D_80109F68[20],
    D_80109F68[21],
    D_80109F68[22],
    D_80109F68[23],
    D_80109F68[24],
    D_80109F68[25],
    D_80109F68[26],
    D_80109F68[27],
    D_80109F68[28],
    D_80109F68[29],
};

INCLUDE_ASM("main/nonmatchings/shots/shot_57", func_800AE450);

void func_800AE4F0(struct ShotObj* arg0)
{
    u32 i;
    u32 start;

    if (arg0->unk7C->unk95 != 0) {
        start = arg0->unk8C.bytes[0];
        for (i = 0; i < arg0->unk8C.bytes[1] + 1; i++) {
            arg0->unk50.frames = D_80109FEC[start++];
            func_8002D9BC(arg0);
        }
        arg0->state = 2;
    }
}

void func_800AE594(struct ShotObj* arg0)
{
    u32 i;
    u32 start;

    if (arg0->unk7C->unk95 != 0) {
        start = arg0->unk8C.bytes[0];
        for (i = 0; i < arg0->unk8C.bytes[1] + 1; i++) {
            arg0->unk50.frames = D_80109FEC[start++];
            func_8002D9BC(arg0);
        }
        return;
    }
    arg0->state = 3;
}

void func_800AE63C(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800AE65C(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk94 != 0) {
        arg0->state = 3;
    }
    D_8010A064[arg0->state](arg0);
}

void (*D_8010A064[])(struct ShotObj*) = {
    func_800AE450,
    func_800AE4F0,
    func_800AE594,
    func_800AE63C,
};
