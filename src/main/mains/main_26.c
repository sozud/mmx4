// MainObj, main_object_update_funcs[26]
// 80058158..800586F0
#include "common.h"
#include "func_tables.h"

void func_80058158(struct MainObj* arg0)
{
    D_800FD1DC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_26", func_80058194);

void func_80058240(struct MainObj* arg0)
{
    arg0->unk5 = 2;
}

void func_8005824C(struct MainObj* arg0)
{
}

void func_80058254(struct MainObj* arg0)
{
    s32 hit = func_8002DD04(arg0);
    s8 stage;

    if (arg0->ext.main_26.last_health != arg0->unk5C) {
        stage = arg0->ext.main_26.stage--;
        if (stage != 1) {
            if (stage == 2) {
                func_800583B0(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi, 0);
            }
        } else {
            func_800583B0(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi, 5);
            arg0->unk5C = 1;
        }
        arg0->ext.main_26.last_health = arg0->unk5C;
    }
    if (func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi, arg0->y_pos.i.hi - 0x10) == 0 || hit < 0) {
        arg0->unk5 = 0;
        arg0->state++;
        arg0->unk42 &= 0x7FFF;
        func_8001540C(5, 1, NULL);
        return;
    }
    D_800FD1E8[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x50, 0x30) != 0) {
        func_8002B0C8(OBJECT_HEADER(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_26", func_800583B0);

void func_800585F4(struct BaseObj* arg0)
{
    func_800583B0(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi, 10);
    arg0->y_pos.u.hi += 0x18;
    func_800C813C(0xC, D_800FD1D0, arg0);
    arg0->unk5 += 2;
}

void func_80058658(struct BaseObj* arg0)
{
}

void func_80058660(struct BaseObj* arg0)
{
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_80058680(struct BaseObj* arg0)
{
    D_800FD1F4[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (func_8002B1E8(arg0, 0x50, 0x30) != 0) {
        func_8002B108(OBJECT_HEADER(arg0));
    }
}

struct Unk_unk68 D_800FD19C[] = {
    { -16, -16, 0x30, 0x30 },
};

union AnimationStep D_800FD1A0[] = {
    { 0x00000001 },
};

union AnimationStep D_800FD1A4[] = {
    { 0x01000001 },
};

union AnimationStep D_800FD1A8[] = {
    { 0x02000001 },
};

union AnimationStep D_800FD1AC[] = {
    { 0x03000001 },
};

union AnimationStep D_800FD1B0[] = {
    { 0x04000001 },
};

union AnimationStep D_800FD1B4[] = {
    { 0x05000001 },
};

union AnimationStep* D_800FD1B8[] = {
    D_800FD1A0,
    D_800FD1A4,
    D_800FD1A8,
    D_800FD1AC,
    D_800FD1B0,
    D_800FD1B4,
};

u8 D_800FD1D0[] = {
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
};

void (*D_800FD1DC[])(struct MainObj*) = {
    func_80058194,
    func_80058254,
    func_80058680,
};

void (*D_800FD1E8[])() = {
    func_8009216C,
    func_80058240,
    func_8005824C,
};

void (*D_800FD1F4[])(struct BaseObj*) = {
    func_800585F4,
    func_80058658,
    func_80058660,
};
