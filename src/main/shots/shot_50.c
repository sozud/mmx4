// ShotObj, shot_object_update_funcs[50]
// 800AA2FC..800AA5E0
#include "common.h"

void (*D_80109BEC[])(struct ShotObj*) = {
    func_800AA20C,
    func_800AA2FC,
    func_800AA3A0,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_50", func_800AA2FC);

INCLUDE_ASM("main/nonmatchings/shots/shot_50", func_800AA3A0);

void func_800AA488(struct ShotObj* arg0)
{
    extern u8 D_80109BB0[];

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80109BEC[arg0->unk5](arg0);
    CollisionRelated(arg0);
    if (arg0->unk7C->state == 2 || arg0->unk84.value != 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_80109BB0, arg0);
        arg0->state = 2;
        arg0->on_screen = 0;
        return;
    }
    func_8002D9BC(arg0);
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_80109BB0, arg0);
        arg0->state = 2;
        arg0->on_screen = 0;
        return;
    }
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->state = 2;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->on_screen = 0;
}

void func_800AA5A4(struct ShotObj* arg0)
{
    D_80109BF8[arg0->state](arg0);
}

void (*D_80109BF8[])(struct ShotObj*) = {
    func_800AA148,
    func_800AA488,
    func_800A9D98,
};
