// MiscObj, misc_object_update_funcs[0]
// 800C7A68..800C7BF4
#include "common.h"

extern void (*D_8010D9EC[])(struct MiscObj*);

void func_800C7A68(struct MiscObj* arg0)
{
    arg0->unk18 = arg0->x_pos.val;
    arg0->unk1C = arg0->y_pos.val;
    D_8010D9EC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/misc/misc_00", func_800C7AB0);

INCLUDE_ASM("main/nonmatchings/misc/misc_00", func_800C7B0C);

void func_800C7B60(struct MiscObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/misc/misc_00", func_800C7B80);
