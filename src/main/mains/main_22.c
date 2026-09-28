// MainObj, main_object_update_funcs[22]
// 80054FE8..80055E04
#include "common.h"
#include "func_tables.h"

void func_80054FE8(struct MainObj* arg0)
{
    D_800FCAEC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_80055024);

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_80055164);

void func_8005529C(struct MainObj* arg0)
{
    arg0->ext.main_22.saved_unk5 = 0;
    arg0->ext.main_22.unk84 = 0;
    arg0->ext.main_22.parts_mask = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_800552C4(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_22.saved_unk5;
}

void func_800552D0(struct MainObj* arg0)
{
    D_800FCB14[arg0->unk6](arg0);
}

void func_8005530C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 1);
    arg0->ext.main_22.unk84 = 8;
    arg0->ext.main_22.unk90 = 0;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_80055358);

void func_800555B0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_22.unk84 == 0) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80055604(struct MainObj* arg0)
{
    D_800FCB20[arg0->unk6](arg0);
}

void func_80055640(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->ext.main_22.unk84 = 0x28;
    arg0->unk6++;
}

void func_8005567C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_22.unk84 != 0) {
        arg0->ext.main_22.unk84 = 0x28;
        if (arg0->ext.main_22.unk8C != 0) {
            arg0->unk5 = 4;
            arg0->unk6 = 0;
        }
    }
}

void func_800556D4(struct MainObj* arg0)
{
    D_800FCB28[arg0->unk6](arg0);
}

void func_80055710(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 1);
    arg0->ext.main_22.unk84 = 0x31;
    arg0->unk6++;
}

void func_800559BC(struct MainObj*);

void func_80055758(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_22.unk84 == 0) {
        func_800559BC(arg0);
        arg0->ext.main_22.unk84 = 0x1E;
        arg0->unk6++;
    }
}

void func_800557B0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_22.unk84 == 0) {
        arg0->unk6 = 0;
        arg0->unk5++;
    }
}

void func_800557FC(struct MainObj* arg0)
{
    D_800FCB34[arg0->unk6](arg0);
}

void func_80055838(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 2);
    arg0->ext.main_22.unk84 = 0x12;
    arg0->unk6++;
}

void func_80055880(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_22.unk84 == 0) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_800558D4(struct MainObj* arg0)
{
    D_800FCB3C[arg0->unk6](arg0);
}

void func_80055910(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->ext.main_22.unk84 = 0x28;
    arg0->unk6++;
}

void func_8005594C(struct MainObj* arg0)
{
    if (--arg0->ext.main_22.unk84 != 0) {
        if ((D_80141BD8.unk0 & 3) == 0) {
            func_800AF878(BASE_OBJECT(arg0), 1, 0x18, 0x30);
        }
    } else {
        arg0->unk6++;
    }
}

void func_800559B4(void)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_22", func_800559BC);

void func_80055C54(struct MainObj* arg0)
{
    struct Unk_unk68* collision;
    s16 x_pos;
    s32 y_pos;
    u8 result;

    arg0->ext.main_23.unk81 = arg0->ext.main_23.unk80;
    x_pos = arg0->x_pos.i.hi;
    collision = arg0->unk68;
    y_pos = (s16)(collision->unk3
        + ((u16)arg0->y_pos.i.hi + (s8)(u8)collision->unk1) + 1);

    result = func_8002D724(PLAYER_OBJECT(arg0), x_pos, y_pos);
    if (result == 0) {
        result = ((s32(*)(struct PlayerObj*, s16, s32))func_8002D724)(
            PLAYER_OBJECT(arg0), x_pos, y_pos + 0x10);
        if (result == 0) {
            arg0->ext.main_23.unk80 = 3;
            return;
        }
    }

    if (result >= 0x11 && result <= 0x1E) {
        if (result >= 0x19) {
            arg0->ext.main_23.unk80 = 2;
            if (result >= 0x1B) {
                if (arg0->unk15 == 0)
                    arg0->ext.main_23.unk80 = 0x82;
            } else if (arg0->unk15 != 0) {
                arg0->ext.main_23.unk80 = 0x82;
            }
        } else {
            arg0->ext.main_23.unk80 = 1;
            if (result >= 0x15) {
                if (arg0->unk15 == 0)
                    arg0->ext.main_23.unk80 = 0x81;
            } else if (arg0->unk15 != 0) {
                arg0->ext.main_23.unk80 = 0x81;
            }
        }
    } else if (result == 0x3E) {
        if (arg0->on_screen != 0) {
            func_800AF808(BASE_OBJECT(arg0));
            func_800C813C(7, D_800FCE80, arg0);
            arg0->state = (u8)arg0->state + 1;
        }
    } else if (result != 0x10) {
        arg0->ext.main_23.unk80 = 0;
    }
}

struct Unk_unk68 D_800FCA20 = { -19, -48, 37, 92 };

union AnimationStep D_800FCA24[] = {
    { 0x00000001 },
};

union AnimationStep D_800FCA28[] = {
    { 0x01010003 },
    { 0x02010004 },
    { 0x03010005 },
    { 0x02010004 },
    { 0x01010003 },
    { 0x00010014 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A000001 },
};

union AnimationStep D_800FCA5C[] = {
    { 0x09010003 },
    { 0x08010003 },
    { 0x07010003 },
    { 0x06010003 },
    { 0x05010003 },
    { 0x04000003 },
};

union AnimationStep D_800FCA74[] = {
    { 0x0B000003 },
};

union AnimationStep D_800FCA78[] = {
    { 0x0C000003 },
};

union AnimationStep D_800FCA7C[] = {
    { 0x0D000003 },
};

union AnimationStep D_800FCA80[] = {
    { 0x0E000003 },
};

union AnimationStep D_800FCA84[] = {
    { 0x0F000003 },
};

union AnimationStep* D_800FCA88[8] = {
    D_800FCA24,
    D_800FCA28,
    D_800FCA5C,
    D_800FCA74,
    D_800FCA78,
    D_800FCA7C,
    D_800FCA80,
    D_800FCA84,
};

u8 D_800FCAA8[8] = { 4, 5, 6, 7, 4, 5, 6, 7 };

s16 D_800FCAB0 = (s16)0xFFD0;

s16 D_800FCAB2 = (s16)0x000A;

u8 D_800FCAB4[56] = { 0x03, 0x00, 0x30, 0x00, 0x0A, 0x00, 0x03, 0x00, 0xEA, 0xFF, 0x45, 0x00, 0x04, 0x00, 0x16, 0x00, 0x45, 0x00, 0x04, 0x00, 0xD8, 0xFF, 0xF0, 0xFF, 0x03, 0x00, 0x28, 0x00, 0xF0, 0xFF, 0x03, 0x00, 0xD8, 0xFF, 0x24, 0x00, 0x04, 0x00, 0x28, 0x00, 0x24, 0x00, 0x04, 0x00, 0xE6, 0xFF, 0xE4, 0xFF, 0x03, 0x00, 0x1A, 0x00, 0xE4, 0xFF, 0x03, 0x00 };

void (*D_800FCAEC[])(struct MainObj*) = {
    func_80055024,
    func_80055164,
    func_8005529C,
};

void (*D_800FCAF8[])() = {
    func_8009216C,
    func_800552C4,
    func_800552D0,
    func_80055604,
    func_800556D4,
    func_800557FC,
    func_800558D4,
};

void (*D_800FCB14[])() = {
    func_8005530C,
    func_80055358,
    func_800555B0,
};

void (*D_800FCB20[])() = {
    func_80055640,
    func_8005567C,
};

void (*D_800FCB28[])() = {
    func_80055710,
    func_80055758,
    func_800557B0,
};

void (*D_800FCB34[])() = {
    func_80055838,
    func_80055880,
};

void (*D_800FCB3C[])() = {
    func_80055910,
    func_8005594C,
    func_800559B4,
};
