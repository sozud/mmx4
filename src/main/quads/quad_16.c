// QuadObj, quad_object_update_funcs[16]
// 800D802C..800D8648
#include "common.h"

INCLUDE_ASM("main/nonmatchings/quads/quad_16", func_800D802C);

void func_800D8150(struct QuadObj* arg0)
{
    if (--arg0->ext.unk38 == 0) {
        arg0->ext.unk38 = 8;
        arg0->unk5++;
    }
}

INCLUDE_ASM("main/nonmatchings/quads/quad_16", func_800D8180);

void func_800D8290(struct QuadObj* arg0)
{
    struct PlayerObj* obj = arg0->unk5C;
    arg0->ext.unk38--;
    if (arg0->ext.unk38 == 0) {
        arg0->unk34 = 0x12;
        arg0->ext.unk38 = 0x10;
        arg0->unk5 = (u8)arg0->unk5 + 1;
        obj->shot_types[1] = 0;
    } else {
        arg0->unk34 = D_8010FED4[arg0->ext.unk38 & 3];
    }
}

INCLUDE_ASM("main/nonmatchings/quads/quad_16", func_800D82E8);

void func_800D83DC(struct QuadObj* arg0)
{
    D_8010FED8[arg0->unk5](arg0);
    quad_is_on_screen(arg0);
}

void func_800D842C(struct QuadObj* arg0)
{
    if (--arg0->ext.unk38 == 0) {
        arg0->ext.unk38 = 0x10;
        arg0->unk5++;
    }
}

INCLUDE_ASM("main/nonmatchings/quads/quad_16", func_800D845C);

void func_800D8578(struct QuadObj* arg0)
{
    D_8010FEE8[arg0->unk5](arg0);
    quad_is_on_screen(arg0);
}

void func_800D85C8(struct QuadObj* arg0)
{
    ZeroObjectState(arg0);
}

void func_800D85E8(struct QuadObj* arg0)
{
    struct PlayerObj* temp_v1;

    temp_v1 = arg0->unk5C;
    if ((u8)temp_v1->shot_types[0] != 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        temp_v1->shot_types[1] = 0;
    }
    D_8010FEF0[arg0->state](arg0);
}

s16 D_8010FE54[2][2] = {
    { 0x50E, 0x29C },
    { 0x50D, 0x29B },
};

s16 D_8010FE5C[14][2] = {
    { 0x492, 0x2F0 },
    { 0x493, 0x2F0 },
    { 0x4FF, 0x279 },
    { 0x4FE, 0x278 },
    { 0x410, 0x2D0 },
    { 0x410, 0x2D1 },
    { 0x4FD, 0x259 },
    { 0x4FC, 0x258 },
    { 0x410, 0x28B },
    { 0x410, 0x28C },
    { 0x4FB, 0x231 },
    { 0x4FA, 0x230 },
    { 0x410, 0x230 },
    { 0x410, 0x231 },
};

s16 D_8010FE94[8][2] = {
    { 0x4FF, 0x279 },
    { 0x4FD, 0x278 },
    { 0x410, 0x2D0 },
    { 0x410, 0x2D4 },
    { 0x4FD, 0x259 },
    { 0x4FC, 0x258 },
    { 0x2C0, 0x2F0 },
    { 0x2C4, 0x2F0 },
};

s16 D_8010FEB4[8][2] = {
    { 0x453, 0x2F0 },
    { 0x4D5, 0x2F0 },
    { 0x410, 0x2AF },
    { 0x410, 0x300 },
    { 0x410, 0x273 },
    { 0x410, 0x2C3 },
    { 0x410, 0x20B },
    { 0x410, 0x263 },
};

u8 D_8010FED4[4] = { 0x12, 0x13, 0x14, 0x13 };

void (*D_8010FED8[])(struct QuadObj*) = {
    func_800D8150,
    func_800D8180,
    func_800D8290,
    func_800D82E8,
};

void (*D_8010FEE8[])(struct QuadObj*) = {
    func_800D842C,
    func_800D845C,
};

void (*D_8010FEF0[])(struct QuadObj*) = {
    func_800D802C,
    func_800D83DC,
    func_800D85C8,
    func_800D8578,
};
