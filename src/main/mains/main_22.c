// MainObj, main_object_update_funcs[22]
// 80054FE8..80055E04
#include "common.h"

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
