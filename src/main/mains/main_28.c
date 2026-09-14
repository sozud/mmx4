// MainObj, main_object_update_funcs[28]
// 80059C48..8005A4CC
#include "common.h"

void func_80059C48(struct MainObj* arg0)
{
    D_800FD5E8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_28", func_80059C84);

INCLUDE_ASM("main/nonmatchings/mains/main_28", func_80059D6C);

void func_80059E38(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_28", func_80059E40);

INCLUDE_ASM("main/nonmatchings/mains/main_28", func_80059F60);

void func_8005A3DC(struct MainObj* arg0)
{
}

void func_8005A3E4(struct MainObj* arg0)
{
    struct Main28Context* context;

    context = arg0->ext.main_28.context;
    if (context->unk0 != 0 && context->objects[arg0->ext.main_28.index] == arg0) {
        context->count--;
        context->objects[arg0->ext.main_28.index] = NULL;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8005A460(struct MainObj* arg0)
{
    func_800AF808(BASE_OBJECT(arg0));
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    func_800C813C(2, D_800FD594, arg0);
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8005A4AC(struct MainObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}
