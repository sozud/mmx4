// MainObj, main_object_update_funcs[40]
// 80061DC0..800623C4
#include "common.h"
#include "func_tables.h"

void func_80061DC0(struct MainObj* arg0)
{
    D_800FEA78[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_40", func_80061DFC);

INCLUDE_ASM("main/nonmatchings/mains/main_40", func_80061F2C);

void func_800620C8(struct MainObj* self)
{
    s32 index;

    self->ext.main_40.timer--;
    if (self->ext.main_40.timer != 0) {
        if (!(D_80141BD8.unk0 & 7)) {
            if (self->ext.main_40.unk80 < 2U) {
                func_800AF878(BASE_OBJECT(self), 1, 0x10, 0x30);
            }
        }
        if (self->ext.main_40.unk80 >= 2U && self->ext.main_40.timer == self->ext.main_40.trigger_time) {
            index = (self->ext.main_40.unk80 - 2) * 2;
            ((void (*)(s32, s32, s32))func_800DABE4)(self->ext.main_40.unk81 + 6,
                self->x_pos.i.hi + D_800FEA5C[index],
                self->y_pos.i.hi + D_800FEA5C[index + 1]);
        }
    } else {
        self->state++;
    }
}

void func_800621C0(struct MainObj* arg0)
{
    u8 state = arg0->ext.main_40.unk80;
    s32 offset;

    if (state >= 2U) {
        offset = (state - 2) * 2;
        ((void (*)(s32, s32, s32))func_800DABE4)(arg0->ext.main_40.unk81 + 0xB,
            arg0->x_pos.i.hi + D_800FEA5C[offset],
            arg0->y_pos.i.hi + D_800FEA5C[offset + 1]);
        func_80062240(arg0);
    }
    func_8002B108(OBJECT_HEADER(arg0));
}

extern u8 D_800FEA68[];
extern u8 D_800FEA88[];

void func_80062240(struct MainObj* arg0)
{
    s32 temp_v0;
    u16 temp_s0;
    u16 temp_s1;
    u8 temp_s2;
    u8 temp_s3;
    u8 temp_s5;

    temp_s1 = (u16)arg0->x_pos.i.hi;
    temp_s0 = (u16)arg0->y_pos.i.hi;
    temp_v0 = arg0->ext.main_0.index * 3;
    temp_s5 = D_800FEA68[2 + temp_v0];
    temp_s2 = D_800FEA68[temp_v0];
    temp_s3 = D_800FEA68[1 + temp_v0];
    func_800C7DA4(temp_s5 * 2, D_800FEA88, arg0, 0);
    func_800B10E4(0x21,
        (s16)temp_s1 - (temp_s2 >> 1),
        (s16)temp_s0 - (temp_s3 >> 1) + 0x10,
        (s16)temp_s1 + (temp_s2 >> 1),
        (s16)temp_s0 + (temp_s3 >> 1) + 0x10,
        temp_s5);
    func_8001540C(0, (get_random() & 1) ^ 1, arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_40", func_80062338);

s8 D_800FE9C8[4] = { -32, -32, 64, 80 };

s8 D_800FE9CC[4] = { -16, -48, 32, 96 };

s8 D_800FE9D0[4] = { -16, -32, 32, 64 };

s8 D_800FE9D4[4] = { -40, -48, 80, 96 };

s8 D_800FE9D8[4] = { -104, -24, -48, 48 };

s8 D_800FE9DC[4] = { -40, -48, 80, 96 };

s8 D_800FE9E0[4] = { -32, -24, 64, 48 };

union AnimationStep D_800FE9E4[] = { { 0x00000001 } };

union AnimationStep D_800FE9E8[] = { { 0x01000001 } };

union AnimationStep D_800FE9EC[] = { { 0x02000001 } };

union AnimationStep D_800FE9F0[] = { { 0x03000001 } };

union AnimationStep D_800FE9F4[] = { { 0x04000001 } };

union AnimationStep D_800FE9F8[] = { { 0x05000001 } };

union AnimationStep* D_800FE9FC[6] = {
    D_800FE9E4,
    D_800FE9E8,
    D_800FE9EC,
    D_800FE9F0,
    D_800FE9F4,
    D_800FE9F8,
};

u8 D_800FEA14[8] = { 0, 1, 2, 1, 0, 2, 0, 0 };

u8 D_800FEA1C[8] = { 1, 2, 3, 4, 5, 2, 4, 0 };

s8* D_800FEA24[7] = {
    D_800FE9C8,
    D_800FE9CC,
    D_800FE9D0,
    D_800FE9D4,
    D_800FE9D8,
    D_800FE9DC,
    D_800FE9E0,
};

union AnimationStep** D_800FEA40[7] = {
    NULL,
    D_800FE9FC,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
};

s8 D_800FEA5C[12] = { -16, -32, -40, -48, -104, -24, -40, -48, -32, -24, 0, 0 };

u8 D_800FEA68[16] = { 32, 48, 3, 80, 80, 6, 208, 32, 8, 64, 32, 5, 64, 32, 5, 0 };

void (*D_800FEA78[])(struct MainObj*) = {
    func_80061DFC,
    func_80061F2C,
    func_800620C8,
    func_800621C0,
};

u8 D_800FEA88[24] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    0,
    0,
    0,
};

struct Unk_unk68 D_800FEAA0 = { 0, 0, 16, 48 };
