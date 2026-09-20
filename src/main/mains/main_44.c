// MainObj, main_object_update_funcs[44]
// 80065930..80065B8C
#include "common.h"

void func_80065930(struct MainObj* arg0)
{
    D_800FF87C[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_44", func_8006596C);

extern void (*D_800FF888[])(struct MainObj*);

void func_80065A54(struct MainObj* arg0)
{
    s8 temp_v0;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FF888[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    func_8002DD04(arg0);
    temp_v0 = arg0->unk5;
    if (temp_v0 != 0) {
        arg0->ext.main_44.saved_unk5 = temp_v0;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
        return;
    }
    arg0->state = (u8)arg0->state + 1;
}

void func_80065B04(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80065B24(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_44.saved_unk5;
}

void func_80065B30(struct MainObj* arg0)
{
    D_800FF894[arg0->unk6](arg0);
}

void func_80065B6C(struct MainObj* arg0)
{
    func_80015DC8(arg0);
}
