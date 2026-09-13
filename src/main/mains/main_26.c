// MainObj, main_object_update_funcs[26]
// 80058158..800586F0
#include "common.h"

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

INCLUDE_ASM("main/nonmatchings/mains/main_26", func_80058254);

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
