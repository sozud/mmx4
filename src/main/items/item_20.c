// ItemObj, item_object_update_funcs[20]
// 800C4CE4..800C52CC
#include "common.h"

struct Item20BackgroundConfig {
    u16 first;
    u16 second;
};

u8 D_8010D20C[4] = { 0, 0, 8, 8 };
u8 D_8010D210[4] = { 0xF8, 0xF8, 0x10, 0x10 };

struct Item20BackgroundConfig D_8010D214[8] = {
    { 0x0400, 0x0400 },
    { 0x0300, 0x0300 },
    { 0x0400, 0x0400 },
    { 0x0400, 0x0700 },
    { 0x0400, 0x0700 },
    { 0x0100, 0x0300 },
    { 0x0100, 0x0300 },
    { 0x0100, 0x0300 },
};

void func_800C4CE4(struct ItemObj* arg0)
{
    D_8010D234[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_20", func_800C4D20);

void func_800C4E78(struct ItemObj* arg0)
{
    D_8010D240[arg0->unk5](arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800C4EC8(struct ItemObj* arg0)
{
    if (func_8002BB80(arg0, &g_Player) != 0) {
        arg0->unk5 = 1;
    }
}

void func_800C4F04(struct ItemObj* arg0)
{
    func_8001540C(2, 0xEC, arg0);
    arg0->unk5 = 2;
}

INCLUDE_ASM("main/nonmatchings/items/item_20", func_800C4F40);

void func_800C5058(struct ItemObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/items/item_20", func_800C5078);

INCLUDE_ASM("main/nonmatchings/items/item_20", func_800C5210);

void (*D_8010D234[])(struct ItemObj*) = {
    func_800C4D20,
    func_800C4E78,
    func_800C5058,
};

void (*D_8010D240[3])(struct ItemObj*) = {
    func_800C4EC8,
    func_800C4F04,
    func_800C4F40,
};
