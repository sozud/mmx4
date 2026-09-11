// MainObj, main_object_update_funcs[12]
// 8004B8C0..8004C734
#include "common.h"

void func_8004B8C0(struct MainObj* arg0)
{
    D_800FB6A8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004B8FC);

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004BAF8);

void func_8004BC14(struct MainObj* arg0)
{
    arg0->unk5 = SP_CUR_MAIN_OBJ->ext.main_12.saved_unk5;
}

INCLUDE_ASM("main/nonmatchings/mains/main_12", func_8004BC2C);

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
