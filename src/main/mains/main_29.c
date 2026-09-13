// MainObj, main_object_update_funcs[29]
// 8005A4CC..8005B3FC
#include "common.h"

void func_8005A4CC(struct MainObj* arg0)
{
    if (arg0->unk2 >= 0) {
        D_800FD838[arg0->state](arg0);
    } else {
        D_800FD848[arg0->state](arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005A538);

void func_8005A6C0(struct MainObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FD858[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x68, 0x68) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x68, 0x68);
    } else {
        arg0->state = 2;
    }
}

void func_8005A750(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005A758);

void func_8005AA0C(struct MainObj* arg0)
{
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005AA14);

u8 func_8005AB34(struct MainObj* arg0)
{
    s32 state;

    state = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
    if ((u8)(state - 4) >= 24) {
        state = 1;
    }
    if ((u8)(state - 4) < 8) {
        state = 2;
    }
    if ((u8)(state - 12) < 8) {
        state = 0;
    }
    if ((u8)(state - 20) < 8) {
        state = 3;
    }
    return state;
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005ABC0);

void func_8005ACA0(struct MainObj* arg0)
{
    struct Main29Ext* context;
    struct Main29Record* record;
    struct Main29Record* target;

    context = &SP_CUR_MAIN_OBJ->ext.main_29;
    record = context->record;
    target = context->target;
    if (record != NULL && record->unk0 != 0 && record->unk1 == 0x10) {
        record->unk4 = 2;
    }
    target->unk4 = 2;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005AD00);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005AEB4);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005AF5C);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005B24C);

INCLUDE_ASM("main/nonmatchings/mains/main_29", func_8005B2C8);
