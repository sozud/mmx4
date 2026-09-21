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

void func_800C5078(void)
{
    u32 i;
    struct MainObj* p1;
    struct MiscObj* p2;
    struct WeaponObj* p3;
    struct ShotObj* p4;
    struct VisualObj* p5;

    p1 = main_objects;
    for (i = 0; i < COUNT(main_objects); p1++, i++) {
        if (p1->active != 0) {
            p1->y_pos.val = 0x8000000 - p1->y_pos.val;
            p1->unk1C.val = 0x8000000 - p1->unk1C.val;
        }
    }
    p2 = misc_objects;
    for (i = 0; i < COUNT(misc_objects); p2++, i++) {
        if (p2->active != 0) {
            p2->y_pos.val = 0x8000000 - p2->y_pos.val;
            p2->unk1C.val = 0x8000000 - p2->unk1C.val;
        }
    }
    p3 = weapon_objects;
    for (i = 0; i < COUNT(weapon_objects); p3++, i++) {
        if (p3->active != 0) {
            p3->y_pos.val = 0x8000000 - p3->y_pos.val;
            p3->unk1C.val = 0x8000000 - p3->unk1C.val;
        }
    }
    p4 = shot_objects;
    for (i = 0; i < COUNT(shot_objects); p4++, i++) {
        if (p4->active != 0) {
            p4->y_pos.val = 0x8000000 - p4->y_pos.val;
            p4->unk1C.val = 0x8000000 - p4->unk1C.val;
        }
    }
    p5 = visual_objects;
    for (i = 0; i < COUNT(visual_objects); p5++, i++) {
        if (p5->active != 0) {
            p5->y_pos.val = 0x8000000 - p5->y_pos.val;
            p5->unk1C.val = 0x8000000 - p5->unk1C.val;
        }
    }
}

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
