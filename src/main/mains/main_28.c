// MainObj, main_object_update_funcs[28]
// 80059C48..8005A4CC
#include "common.h"
#include "func_tables.h"

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
    struct MainObj* context = arg0->ext.main_28.context;

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
    struct MainObj* context;

    context = arg0->ext.main_28.context;
    if (context->active != 0 && context->ext.main_29.slots.children[arg0->ext.main_28.index] == arg0) {
        context->ext.main_29.unk94--;
        context->ext.main_29.slots.children[arg0->ext.main_28.index] = NULL;
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

union AnimationStep D_800FD3F4[] = {
    { 0x00000001 },
};

union AnimationStep D_800FD3F8[] = {
    { 0x01010003 },
    { 0x02010003 },
    { 0x00010003 },
    { 0x03010003 },
    { 0x00000003 },
};

union AnimationStep D_800FD40C[] = {
    { 0x04010003 },
    { 0x05010003 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08FC0003 },
};

union AnimationStep D_800FD420[] = {
    { 0x00010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x09010002 },
    { 0x00010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0A010002 },
    { 0x09000002 },
};

union AnimationStep D_800FD460[] = {
    { 0x1F000001 },
};

union AnimationStep D_800FD464[] = {
    { 0x20010003 },
    { 0x21010003 },
    { 0x1F010003 },
    { 0x22010003 },
    { 0x1F000003 },
};

union AnimationStep D_800FD478[] = {
    { 0x23010003 },
    { 0x24010003 },
    { 0x25010003 },
    { 0x26010003 },
    { 0x27FC0003 },
};

union AnimationStep D_800FD48C[] = {
    { 0x1F010002 },
    { 0x28010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x29010002 },
    { 0x28010002 },
    { 0x1F010002 },
    { 0x28010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x29010002 },
    { 0x28000002 },
};

union AnimationStep D_800FD4CC[] = {
    { 0x0C000001 },
};

union AnimationStep D_800FD4D0[] = {
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0C010003 },
    { 0x0F010003 },
    { 0x0C000003 },
};

union AnimationStep D_800FD4E4[] = {
    { 0x10010003 },
    { 0x11010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x14FC0003 },
};

union AnimationStep D_800FD4F8[] = {
    { 0x0C010002 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x16010002 },
    { 0x15010002 },
    { 0x0C010002 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x16010002 },
    { 0x15000002 },
};

union AnimationStep D_800FD538[] = {
    { 0x18010001 },
    { 0x19010001 },
    { 0x1A010001 },
    { 0x1BFD0001 },
};

union AnimationStep D_800FD548[] = {
    { 0x1C000001 },
};

union AnimationStep D_800FD54C[] = {
    { 0x1D000001 },
};

union AnimationStep D_800FD550[] = {
    { 0x1E000001 },
};

union AnimationStep* D_800FD554[] = {
    D_800FD3F4,
    D_800FD3F8,
    D_800FD40C,
    D_800FD420,
    D_800FD4CC,
    D_800FD4D0,
    D_800FD4E4,
    D_800FD4F8,
    D_800FD460,
    D_800FD464,
    D_800FD478,
    D_800FD48C,
    D_800FD538,
    D_800FD548,
    D_800FD54C,
    D_800FD550,
};

u8 D_800FD594[] = {
    0x0D,
    0x0E,
    0x0F,
    0x00,
};

struct Unk_unk68 D_800FD598[6] = {
    { -5, -5, 10, 11 },
    { -5, -5, 10, 11 },
    { -11, -11, 21, 21 },
    { -11, -11, 21, 21 },
    { 22, 0, 22, 18 },
    { 0, 21, 18, 21 },
};

struct Unk_unk68* D_800FD5B0[] = {
    D_800FD598 + 4,
    D_800FD598 + 5,
};

struct Unk_unk68* D_800FD5B8[] = {
    D_800FD598 + 2,
    D_800FD598 + 3,
};

struct Unk_unk68* D_800FD5C0[] = {
    D_800FD598,
    D_800FD598 + 1,
};

u8 D_800FD5C8[] = {
    0x0A,
    0x14,
    0x1E,
    0x28,
    0x32,
    0x0A,
    0x14,
    0x1E,
    0x28,
    0x32,
    0x0A,
    0x14,
    0x1E,
    0x28,
    0x32,
    0x0A,
    0x14,
    0x1E,
    0x28,
    0x32,
    0x0A,
    0x14,
    0x1E,
    0x28,
    0x32,
    0x0A,
    0x14,
    0x1E,
    0x28,
    0x32,
    0x0A,
    0x14,
};

void (*D_800FD5E8[])(struct MainObj*) = {
    func_80059C84,
    func_80059D6C,
    func_8005A3E4,
    func_8005A460,
    func_8005A4AC,
};

struct Main28InitData D_800FD5FC[4] = {
    { 5, 0x00 },
    { 5, 0x40 },
    { 1, 0x00 },
    { 9, 0x40 },
};

void (*D_800FD604[])(struct MainObj*) = {
    func_8009216C,
    func_80059E38,
    func_80059E40,
    func_80059F60,
    func_8005A3DC,
};

struct FixedPointPosition D_800FD618[4] = {
    { (s32)0xFFFD0000, 0 },
    { (s32)0x00030000, 0 },
    { 0, (s32)0xFFFD0000 },
    { 0, (s32)0x00030000 },
};

struct FixedPointPosition D_800FD638[4] = {
    { (s32)0xFFFF0000, 0 },
    { (s32)0x00010000, 0 },
    { 0, (s32)0xFFFF0000 },
    { 0, (s32)0x00010000 },
};
