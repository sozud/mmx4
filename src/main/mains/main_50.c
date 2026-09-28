// MainObj, main_object_update_funcs[50]
// 8006970C..80069A94
#include "common.h"
#include "func_tables.h"

void func_8006970C(struct MainObj* arg0)
{
    D_800FFC3C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_50", func_80069748);

INCLUDE_ASM("main/nonmatchings/mains/main_50", func_800698D8);

void func_80069A08(struct MainObj* arg0)
{
    if (++arg0->ext.main_50.timer != 0x30) {
        if (!(D_80141BD8.unk0 & 7)) {
            func_800AF878(BASE_OBJECT(arg0), 1, 0x18, 0x18);
        }
    } else {
        arg0->state = 3;
    }
}

void func_80069A6C(struct MainObj* arg0)
{
    func_8002B108(arg0);
}

void func_80069A8C(struct MainObj* arg0)
{
}

u8 D_800FFBD8[4] = { 0xE0, 0xE0, 0x40, 0x50 };

u8 D_800FFBDC[8] = { 0, 1, 2, 1, 0, 2, 0, 0 };

u8 D_800FFBE4[8] = { 7, 8, 9, 7, 9, 8, 0, 0 };

union AnimationStep D_800FFBEC[1] = { { 0x00000101 } };

union AnimationStep D_800FFBF0[1] = { { 0x01000001 } };

union AnimationStep D_800FFBF4[1] = { { 0x02000001 } };

union AnimationStep D_800FFBF8[1] = { { 0x03000001 } };

union AnimationStep D_800FFBFC[1] = { { 0x04000001 } };

union AnimationStep D_800FFC00[1] = { { 0x05000001 } };

union AnimationStep D_800FFC04[1] = { { 0x06000001 } };

union AnimationStep D_800FFC08[1] = { { 0x07000001 } };

union AnimationStep D_800FFC0C[1] = { { 0x08000001 } };

union AnimationStep D_800FFC10[1] = { { 0x09000001 } };

union AnimationStep* D_800FFC14[10] = {
    D_800FFBEC,
    D_800FFBF0,
    D_800FFBF4,
    D_800FFBF8,
    D_800FFBFC,
    D_800FFC00,
    D_800FFC04,
    D_800FFC08,
    D_800FFC0C,
    D_800FFC10,
};

void (*D_800FFC3C[])(struct MainObj*) = {
    func_80069748,
    func_800698D8,
    func_80069A08,
    func_80069A6C,
};

void (*D_800FFC4C[2])() = {
    func_8009216C,
    func_80069A8C,
};
