// ShotObj, shot_object_update_funcs[12]
// 8009B7F8..8009BD28
#include "common.h"

void func_8009B7F8(struct ShotObj* arg0)
{
    D_80108E9C[arg0->state](arg0);
    if (arg0->state >= 3) {
        CollisionRelated(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_12", func_8009B85C);

INCLUDE_ASM("main/nonmatchings/shots/shot_12", func_8009B9B0);

void func_8009BA4C(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_12", func_8009BA6C);

INCLUDE_ASM("main/nonmatchings/shots/shot_12", func_8009BAE8);

INCLUDE_ASM("main/nonmatchings/shots/shot_12", func_8009BC14);

void func_8009BD08(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 D_80108E68[4] = { 0xFA, 0xF8, 0x0C, 0x0D };

u8 D_80108E6C[4] = { 0xF7, 0xF0, 0x10, 0x25 };

u8 D_80108E70[4] = { 0xFF, 0x04, 0x09, 0x14 };

struct Shot12CollisionData {
    u16 masks[10];
    u8 effect_id;
    u8 animation[15];
};

struct Shot12CollisionData D_80108E74 = {
    { 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200 },
    0x16,
    { 0xFF, 0x0E, 0xEF, 0xFE, 0xE7, 0xF1, 0xF1, 0xEB, 0x01, 0xF2, 0x0F, 0xFF, 0x17, 0x0D, 0x11 },
};

u8 D_80108E98[4] = { 0x1F, 0x20, 0x1F, 0x20 };

void (*D_80108E9C[])(struct ShotObj*) = {
    func_8009B85C,
    func_8009B9B0,
    func_8009BA4C,
    func_8009BA6C,
    func_8009BAE8,
    func_8009BC14,
    func_8009BD08,
};
