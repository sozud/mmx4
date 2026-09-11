// MainObj, main_object_update_funcs[53]
// 8006AF70..8006BB00
#include "common.h"

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006AF70);

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B114);

void func_8006B180(struct BarObj* arg0)
{
    D_801001C8[arg0->unk5](arg0);
}

void func_8006B1BC(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B1C4);

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B2A4);

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B398);

void func_8006B514(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_8006B2A4();
    } else {
        func_8006B398(arg0);
    }
    func_8002B694(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B568);

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B5F8);

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B6B0);

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B79C);

void func_8006B848(struct MainObj* arg0)
{
    func_80015D60(arg0, 2);
    if (arg0->unk2 == 4) {
        arg0->unk20 = FIXED(-1);
    } else {
        arg0->unk20 = FIXED(11);
    }
    arg0->unk24 = FIXED(8);
    arg0->unk2C = FIXED(0.3125);
    arg0->unk67 = 1;
    arg0->unk5 = 6;
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x20);
}

void func_8006B8BC(struct MainObj* arg0)
{
    func_8006B514(arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x30, 0x20);
}

INCLUDE_ASM("main/nonmatchings/mains/main_53", func_8006B8F4);

void func_8006BAA4(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8006BAC4(struct MainObj* arg0)
{
    D_801001EC[arg0->state](arg0);
}
