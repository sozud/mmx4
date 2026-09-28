// MainObj, main_object_update_funcs[42]
// 80062D60..800631C8
#include "common.h"
#include "func_tables.h"

void func_80062D60(struct MainObj* arg0)
{
    D_800FEF74[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_42", func_80062D9C);

void func_80062E70(struct MainObj* arg0)
{
    func_80015D60(arg0, 0);
}

void func_80062E90(struct MainObj* arg0)
{
    s16 temp_v0;
    s32 temp_a2;
    s32 temp_v0_2;

    temp_v0 = (u16)arg0->unk7C - 1;
    arg0->unk7C = temp_v0;
    if (temp_v0 == 0) {
        arg0->unk7C = 0x5A;
        func_8002B93C(
            MOVING_OBJECT(arg0),
            func_8002B7DC(
                OBJECT_HEADER(arg0),
                OBJECT_HEADER(&g_Player))
                & 0xFF);

        temp_v0_2 = arg0->unk20;
        temp_a2 = arg0->unk24;
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = -((s32)(temp_v0_2 * 0x2D) >> 8);
        arg0->unk2C = -((s32)(temp_a2 * 0x2D) >> 8);
        func_80015D60(arg0, 1);
        arg0->unk5 = 3;
        arg0->ext.main_42.unk84 = 0;
        arg0->ext.main_42.background_relative += 1;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80062F60(struct MainObj* arg0)
{
    struct MiscObj* misc;

    if (--arg0->unk7C == 0x5A) {
        arg0->unk28 = -arg0->unk28;
        arg0->unk2C = -arg0->unk2C;
    }
    if (--arg0->unk7C == 0) {
        if (arg0->ext.main_42.background_relative < 5) {
            arg0->unk7C = 0xB4;
            arg0->unk28 = 0;
            arg0->unk2C = 0;
            arg0->unk20 = 0;
            arg0->unk24 = 0;
            func_80015D60(arg0, 0);
            arg0->unk5 = 2;
        } else {
            arg0->unk20 = 0;
            arg0->unk24 = FIXED(2);
            func_80015D60(arg0, 3);
            arg0->unk5 = 4;
            arg0->ext.main_42.unk84 = NULL;
        }
    }
    if (!(arg0->unk7C & 3)) {
        misc = func_8002AE90(arg0->ext.main_42.unk84, 0);
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0xE;
            misc->ext.pointer.unk50 = arg0;
            misc->x_pos.val = arg0->x_pos.val;
            misc->y_pos.val = arg0->y_pos.val;
            misc->unk2 = arg0->animation_step.fields.event;
            arg0->ext.main_42.unk84 = misc;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_800630AC(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718(arg0);
}

void func_800630DC(struct MainObj* self)
{
    extern u8 D_800FEF6C[];
    extern void (*D_800FEF80[])(struct MainObj*);

    if (func_8002DD04(self) < 0) {
        self->unk5 = 0;
        self->state += 1;
        self->unk42 &= 0x7FFF;
        func_800AF808(BASE_OBJECT(self));
        func_800C813C(6, D_800FEF6C, self);
        return;
    }

    D_800FEF80[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }

    func_8002B0C8(OBJECT_HEADER(self));
}

void func_800631A8(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

s8 D_800FEE64[4] = { -6, -6, 11, 11 };

s8 D_800FEE68[4] = { -10, -9, 17, 17 };

union AnimationStep D_800FEE6C[] = {
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010003 },
    { 0x03010003 },
    { 0x04010002 },
    { 0x04FB0001 },
};

union AnimationStep D_800FEE84[] = {
    { 0x00010003 },
    { 0x14010102 },
    { 0x15010202 },
    { 0x16010302 },
    { 0x17010402 },
    { 0x18010502 },
    { 0x19010602 },
    { 0x1A010702 },
    { 0x1B010802 },
    { 0x1C010902 },
    { 0x1D010A02 },
    { 0x1E010B02 },
    { 0x1F010C02 },
    { 0x20010D02 },
    { 0x04010E01 },
    { 0x04F10E01 },
};

union AnimationStep D_800FEEC4[] = {
    { 0x05010002 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x08010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0C010102 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010001 },
    { 0x13F10001 },
};

union AnimationStep D_800FEF04[] = {
    { 0x00010002 },
    { 0x01010102 },
    { 0x02010202 },
    { 0x03010302 },
    { 0x04010402 },
    { 0x00010502 },
    { 0x01010602 },
    { 0x02010702 },
    { 0x03010802 },
    { 0x04010902 },
    { 0x00010A02 },
    { 0x01010B02 },
    { 0x02010C02 },
    { 0x03010D02 },
    { 0x04010E01 },
    { 0x04F10E01 },
};

union AnimationStep D_800FEF44[] = { { 0x21000001 } };

union AnimationStep D_800FEF48[] = { { 0x22000001 } };

union AnimationStep D_800FEF4C[] = { { 0x23000001 } };

union AnimationStep* D_800FEF50[7] = {
    D_800FEE6C,
    D_800FEE84,
    D_800FEEC4,
    D_800FEF04,
    D_800FEF44,
    D_800FEF48,
    D_800FEF4C,
};

u8 D_800FEF6C[8] = { 4, 5, 6, 4, 5, 6, 0, 0 };

void (*D_800FEF74[])(struct MainObj*) = {
    func_80062D9C,
    func_800630DC,
    func_800631A8,
};

void (*D_800FEF80[5])() = {
    func_8009216C,
    func_80062E70,
    func_80062E90,
    func_80062F60,
    func_800630AC,
};
