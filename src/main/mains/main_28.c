// MainObj, main_object_update_funcs[28]
// 80059C48..8005A4CC
#include "common.h"

void func_80059C48(struct MainObj* arg0)
{
    D_800FD5E8[arg0->state](arg0);
}

void func_80059C84(struct MainObj* arg0)
{
    volatile struct MainObj* self = arg0;
    s32 value8 = self->x_pos.val;
    s32 valueC = self->y_pos.val;
    u16 high8 = self->x_pos.i.hi;
    s32 tableIndex;
    u16 valueE;

    tableIndex = 1;
    self->state = tableIndex;
    self->on_screen = tableIndex;
    tableIndex = ((volatile u8*)self)[2];
    self->unk5 = 2;
    self->unk5C = 3;
    self->unk60 = 3;
    self->animation_table = (const u8* const*)D_800FD554;
    self->collision_data = D_80107074;
    self->unk16 = 5;
    valueE = self->y_pos.i.hi;
    self->unk6 = 0;
    self->unk7C = 0;
    self->unk61 = 0;
    self->ext.main_28.unk85 = 0;
    self->unk54 = 0;
    self->unk50 = 0;
    self->unk68 = 0;
    self->unk67 = 0;
    self->unk20 = 0;
    self->unk24 = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    tableIndex = (tableIndex << 1) & 0xFF;
    self->unk18.val = value8;
    self->unk1C.val = valueC;
    self->ext.main_28.unk86 = high8;
    self->ext.main_28.unk88 = valueE;
    self->ext.main_28.unk84 = ((u8*)D_800FD5FC)[tableIndex];
    self->unk15 = ((u8*)D_800FD5FC)[tableIndex + 1];
    func_80015D60(arg0, arg0->ext.main_28.unk84);
}

void func_80059D6C(struct MainObj* arg0)
{
    struct Main28Context* context = arg0->ext.main_28.context;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->x_pos.val = context->x_pos.val;
    arg0->y_pos.val = context->y_pos.val;

    D_800FD604[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (func_8002DD04(arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        func_800C813C(2, D_800FD594, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0xC);
        arg0->state = 2;
        return;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
}

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
