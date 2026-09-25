// MainObj, main_object_update_funcs[12]
// 8004B8C0..8004C734
#include "common.h"

void func_8004B8C0(struct MainObj* arg0)
{
    D_800FB6A8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004B8FC);

void func_8004BAF8(struct MainObj* arg0)
{
    s32 result;
    s8 mode = arg0->unk5;

    if (mode != 5 || arg0->unk6 != 4) {
        CollisionRelated(PLAYER_OBJECT(arg0));
    }
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    func_8004C6C4(arg0);
    D_800FB6B4[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    result = func_8002DD04(arg0);
    if (result < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(5, D_800FB67C, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0xE);
    } else {
        if (result > 0) {
            SP_CUR_MAIN_OBJ->ext.main_12.saved_unk5 = arg0->unk5;
        }
        if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
            is_on_screen(BASE_OBJECT(arg0));
            return;
        }
    }
    arg0->state++;
}

void func_8004BC14(struct MainObj* arg0)
{
    arg0->unk5 = SP_CUR_MAIN_OBJ->ext.main_12.saved_unk5;
}

void func_8004BC2C(struct MainObj* arg0)
{
    struct MainObj* current;

    func_8002B694(ANIMATED_OBJECT(arg0));
    current = SP_CUR_MAIN_OBJ;
    if (current->ext.main_12.unk88 == 0) {
        if (arg0->unk24 >= 0) {
            arg0->unk24 = FIXED(0.5);
            arg0->unk2C = -arg0->unk2C;
            current->ext.main_12.unk88 = 1;
        }
    } else if (arg0->unk24 < 0) {
        arg0->unk24 = FIXED(-0.5);
        arg0->unk2C = -arg0->unk2C;
        current->ext.main_12.unk88 = 0;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8004BCC8(struct MainObj* arg0)
{
    arg0->unk5 = 4;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk7E = 8;
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004BCFC);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004BF5C);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004C210);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004C394);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004C56C);

void func_8004C654(struct MainObj* arg0)
{
    if (arg0->unk2 == 2) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8004C694(struct MainObj* arg0)
{
    if (arg0->x_pos.val < g_Player.x_pos.val) {
        arg0->unk15 = 0x40;
    } else {
        arg0->unk15 = 0;
    }
}

void func_8004C6C4(struct MainObj* arg0)
{
    s16 object_x;
    s16 distance;

    if ((arg0->unk7C != 0) && (arg0->unk5 == 2)) {
        object_x = arg0->x_pos.i.hi;
        if ((g_Player.x_pos.i.hi - object_x) >= 0) {
            distance = g_Player.x_pos.i.hi - object_x;
        } else {
            distance = object_x - g_Player.x_pos.i.hi;
        }
        if (distance < 0x90) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
        }
    }
}
