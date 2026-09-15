// MiscObj, misc_object_update_funcs[52]
// 800D2190..800D2A74
#include "common.h"

extern void (*D_8010F518[])(struct MiscObj*);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D2190);

void func_800D2420(struct MiscObj* arg0)
{
    if (arg0->unk6 == 0) {
        if (g_Player.x_pos.i.hi >= 0x911) {
            arg0->unk6++;
            background_objects[0].unk26 = 0x8C0;
            func_80036AE4(0x14, 0x40);
        }
    } else if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
        arg0->unk6 = 0;
        arg0->ext.unk.unk55 = 0x1E;
        arg0->unk5++;
    }
}

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D24B4);

void func_800D254C(struct MiscObj* arg0)
{
    if (abc_object.unkC == 0) {
        arg0->state = 2;
        arg0->unk6 = 0;
        arg0->ext.unk.unk55 = 0x1E;
        if (engine_obj.cur_character == 0) {
            arg0->unk5 = 0;
        } else {
            arg0->unk5 = 1;
        }
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800D25AC(struct MiscObj* arg0)
{
    D_8010F50C[arg0->unk5](arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D25FC);

INCLUDE_ASM("main/nonmatchings/misc/misc_52", func_800D26F4);

void func_800D2794(struct MiscObj* arg0)
{
    D_8010F518[arg0->unk2](arg0);
    if (D_80141BD8.unk0 % 10 == 0) {
        u8 unk56;
        arg0->y_pos.i.hi += arg0->ext.misc_52.unk57;
        unk56 = --arg0->ext.misc_52.unk56;
        if (unk56 == 0) {
            arg0->ext.misc_52.unk56 = 7;
            arg0->ext.misc_52.unk57 *= -1;
        }
    }
}

void func_800D2854(struct MiscObj* arg0)
{
    u8 timer;

    timer = arg0->ext.unk.unk55;
    if (timer == 0) {
        arg0->ext.unk.unk55 = 0x1E;
        arg0->unk6++;
    } else {
        arg0->ext.unk.unk55 = timer - 1;
    }
    arg0->on_screen = 0;
    if (D_80141BD8.unk0 & 1) {
        is_on_screen(BASE_OBJECT(arg0));
    }
}

void func_800D28BC(struct MiscObj* arg0)
{
    s8 timer = arg0->ext.unk.unk55;
    arg0->on_screen = 0;
    timer--;
    arg0->ext.unk.unk55 = timer;
    if (!(timer & 0xFF)) {
        engine_obj.unkF = 0x40;
    }
}

void func_800D28E8(struct MiscObj* arg0)
{
    D_8010F528[arg0->unk6](arg0);
}

void func_800D2924(struct MiscObj* arg0)
{
    u8 timer;

    is_on_screen(BASE_OBJECT(arg0));
    timer = arg0->ext.unk.unk55 - 1;
    arg0->ext.unk.unk55 = timer;
    if (timer == 0) {
        engine_obj.unkF = 0x40;
    }
}

void func_800D2970(struct MiscObj* arg0)
{
    u8 timer;

    arg0->on_screen = 0;
    timer = arg0->ext.unk.unk55 - 1;
    arg0->ext.unk.unk55 = timer;
    if (timer == 0) {
        func_80036B18();
        func_8002B108(OBJECT_HEADER(arg0));
    }
}

void func_800D29C0(struct MiscObj* arg0)
{
    D_8010F530[arg0->unk6](arg0);
}

void func_800D29FC(struct MiscObj* arg0)
{
    D_8010F538[arg0->unk5](arg0);
}

void func_800D2A38(struct MiscObj* arg0)
{
    D_8010F544[arg0->state](arg0);
}

union AnimationStep D_8010F4E4[5] = {
    { .packed = 0x0001003A },
    { .packed = 0x04010008 },
    { .packed = 0x05010021 },
    { .packed = 0x04010008 },
    { .packed = 0x00FC003A },
};

union AnimationStep D_8010F4F8[3] = {
    { .packed = 0x01010001 },
    { .packed = 0x02010001 },
    { .packed = 0x03FE0001 },
};

union AnimationStep* D_8010F504[2] = { D_8010F4E4, D_8010F4F8 };

void (*D_8010F50C[3])(struct MiscObj*) = {
    func_800D2420,
    func_800D24B4,
    func_800D254C,
};
void (*D_8010F518[4])(struct MiscObj*) = {
    func_800D25AC,
    func_800D25FC,
    func_800D26F4,
    func_800D26F4,
};
void (*D_8010F528[2])(struct MiscObj*) = { func_800D2854, func_800D28BC };
void (*D_8010F530[2])(struct MiscObj*) = { func_800D2854, func_800D2970 };
void (*D_8010F538[3])(struct MiscObj*) = {
    func_800D28E8,
    func_800D2924,
    func_800D29C0,
};
void (*D_8010F544[3])(struct MiscObj*) = {
    func_800D2190,
    func_800D2794,
    func_800D29FC,
};
