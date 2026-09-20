// MainObj, main_object_update_funcs[40]
// 80061DC0..800623C4
#include "common.h"

void func_80061DC0(struct MainObj* arg0)
{
    D_800FEA78[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_40", func_80061DFC);

INCLUDE_ASM("main/nonmatchings/mains/main_40", func_80061F2C);

INCLUDE_ASM("main/nonmatchings/mains/main_40", func_800620C8);

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
