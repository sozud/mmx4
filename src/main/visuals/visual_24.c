// VisualObj, visual_object_update_funcs[24]
// 800B35B8..800B3D3C
#include "common.h"

s32 D_8010A5FC[4] = { 0x1C000, 0x2C000, 0x3C000, 0x34000 };
s32 D_8010A60C[4] = { 0x18000, 0x28000, 0x8000, 0x30000 };
s32 D_8010A61C[4] = { 0x1C000, 0x2C000, 0x3C000, 0x34000 };
s32 D_8010A62C[4] = { -0x18000, -0x28000, -0x8000, -0x30000 };
s16 D_8010A63C[8] = { -9, 0x13, -0x26, -0x16, 0x2B, -0xA, 0x1C, 0x26 };

void func_800B35B8(struct VisualObj* arg0)
{
    D_8010A64C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B35F4);

void func_800B36F0(struct VisualObj* arg0)
{
    D_8010A654[arg0->unk5](arg0);
}

void func_800B372C(struct VisualObj* arg0)
{
    D_8010A66C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B3768);

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B37F8);

void func_800B3848(struct VisualObj* arg0)
{
    D_8010A674[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B3884);

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B392C);

void func_800B397C(struct VisualObj* arg0)
{
    D_8010A67C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B39B8);

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B3A60);

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B3AB0);

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B3B1C);

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B3B58);

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B3B94);

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B3C34);

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B3C90);

INCLUDE_ASM("main/nonmatchings/visuals/visual_24", func_800B3CCC);

void (*D_8010A64C[])(struct VisualObj*) = {
    func_800B35F4,
    func_800B36F0,
};

void (*D_8010A654[])(struct VisualObj*) = {
    func_800B372C,
    func_800B3848,
    func_800B3AB0,
    func_800B397C,
    func_800B3B1C,
    func_800B3C34,
};

void (*D_8010A66C[])(struct VisualObj*) = { func_800B3768, func_800B37F8 };
void (*D_8010A674[])(struct VisualObj*) = { func_800B3884, func_800B392C };
void (*D_8010A67C[])(struct VisualObj*) = { func_800B39B8, func_800B3A60 };
void (*D_8010A684[])(struct VisualObj*) = { func_800B3B58, func_800B3B94 };
void (*D_8010A68C[])(struct VisualObj*) = { func_800B3C90, func_800B3CCC };
