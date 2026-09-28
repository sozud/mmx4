// MainObj, main_object_update_funcs[39]
// 80061590..80061DC0
#include "common.h"
#include "func_tables.h"

void func_80061590(struct MainObj* arg0)
{
    D_800FE9A4[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_39", func_800615CC);

void func_8006185C(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FE9B0[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    func_8002DD04(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x1000, 0x40) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
        return;
    }
    arg0->state = 2;
}

void func_800618F4(struct MainObj* arg0)
{
    arg0->ext.main_39.unk80.w = 0;
    arg0->ext.main_39.unk84.w = 0;
    func_8002B108(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_39", func_80061918);

void func_80061AA8(struct MainObj* arg0)
{
    D_800FE9BC[arg0->unk6](arg0);
}

void func_80061AE4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->y_pos.i.hi >= 0x119) {
        arg0->unk24 = 0;
        arg0->unk2C = 0;
    }
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk7C = 0x3C;
        func_80015D60(arg0, 2);
        arg0->unk6 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_39", func_80061B58);

void func_80061D18(struct MainObj* arg0)
{
    u8 object_id;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    object_id = arg0->unk2;
    if (!(object_id & 1)) {
        func_800DABE4((s8)object_id / 2, arg0->ext.main_39.unk80.h.unk82, 0x120);
    }
    arg0->ext.main_39.unk88 = 1;
    arg0->unk2C = FIXED(0.125);
    arg0->unk5 = 0;
    arg0->unk6 = 0;
}

void func_80061D90(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
}

s8 D_800FE944[4] = { -16, -7, 29, 29 };

s8 D_800FE948[4] = { -12, -5, 22, 26 };

s8 D_800FE94C[4] = { 0, 0, 16, 26 };

union AnimationStep D_800FE950[] = {
    { 0x00010001 },
    { 0x01010001 },
    { 0x02FE0001 },
};

union AnimationStep D_800FE95C[] = {
    { 0x03010001 },
    { 0x04010001 },
    { 0x05010001 },
    { 0x03010001 },
    { 0x04010001 },
    { 0x05000101 },
};

union AnimationStep D_800FE974[] = {
    { 0x07010003 },
    { 0x08010003 },
    { 0x09010003 },
    { 0x0A010003 },
    { 0x0B010003 },
    { 0x0C010003 },
    { 0x0D010003 },
    { 0x06F90003 },
};

union AnimationStep* D_800FE994[4] = {
    D_800FE950,
    D_800FE95C,
    D_800FE974,
    NULL,
};

void (*D_800FE9A4[])(struct MainObj*) = {
    func_800615CC,
    func_8006185C,
    func_800618F4,
};

void (*D_800FE9B0[3])(struct MainObj*) = {
    func_80061918,
    func_80061AA8,
    func_80061D90,
};

void (*D_800FE9BC[3])(struct MainObj*) = { func_80061AE4, func_80061B58, func_80061D18 };
