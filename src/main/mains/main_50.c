// MainObj, main_object_update_funcs[50]
// 8006970C..80069A94
#include "common.h"

void func_8006970C(struct MainObj* arg0)
{
    D_800FFC3C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_50", func_80069748);

INCLUDE_ASM("main/nonmatchings/mains/main_50", func_800698D8);

void func_80069A08(struct MainObj* arg0)
{
    if (++arg0->ext.main_50.timer != 0x30) {
        if (!(D_80141BD8.unk0 & 7)) {
            func_800AF878(BASE_OBJECT(arg0), 1, 0x18, 0x18);
        }
    } else {
        arg0->state = 3;
    }
}

void func_80069A6C(struct MainObj* arg0)
{
    func_8002B108(arg0);
}

void func_80069A8C(struct MainObj* arg0)
{
}
