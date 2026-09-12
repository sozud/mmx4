// ItemObj, item_object_update_funcs[10]
// 800C24E0..800C2BE0
#include "common.h"

struct Item10AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item10Offset {
    s16 x;
    s16 y;
};

struct Item10AnimationStep D_8010CCA0[4] = {
    { 3, 0, 1, 0 },
    { 3, 0, 1, 1 },
    { 3, 0, 1, 2 },
    { 3, 0, 253, 1 },
};

struct Item10AnimationStep D_8010CCB0[4] = {
    { 3, 0, 1, 3 },
    { 3, 0, 1, 4 },
    { 3, 0, 1, 5 },
    { 3, 0, 253, 4 },
};

struct Item10AnimationStep D_8010CCC0[4] = {
    { 3, 0, 1, 6 },
    { 3, 0, 1, 7 },
    { 3, 0, 1, 8 },
    { 3, 0, 253, 7 },
};

struct Item10AnimationStep D_8010CCD0[4] = {
    { 3, 0, 1, 9 },
    { 3, 0, 1, 10 },
    { 3, 0, 1, 11 },
    { 3, 0, 253, 10 },
};

struct Item10AnimationStep D_8010CCE0[4] = {
    { 3, 0, 1, 12 },
    { 3, 0, 1, 13 },
    { 3, 0, 1, 14 },
    { 3, 0, 253, 13 },
};

struct Item10AnimationStep D_8010CCF0[4] = {
    { 3, 0, 1, 15 },
    { 3, 0, 1, 16 },
    { 3, 0, 1, 17 },
    { 3, 0, 253, 16 },
};

struct Item10AnimationStep D_8010CD00[4] = {
    { 3, 0, 1, 18 },
    { 3, 0, 1, 19 },
    { 3, 0, 1, 20 },
    { 3, 0, 253, 19 },
};

struct Item10AnimationStep D_8010CD10[19] = {
    { 3, 0, 1, 21 },
    { 3, 0, 1, 22 },
    { 3, 0, 1, 23 },
    { 3, 0, 1, 24 },
    { 3, 0, 1, 25 },
    { 3, 0, 1, 26 },
    { 3, 0, 1, 27 },
    { 3, 0, 1, 28 },
    { 3, 0, 1, 29 },
    { 3, 0, 1, 30 },
    { 3, 0, 1, 31 },
    { 3, 0, 1, 32 },
    { 3, 0, 1, 33 },
    { 3, 0, 1, 34 },
    { 3, 0, 1, 35 },
    { 3, 0, 1, 36 },
    { 3, 0, 1, 37 },
    { 3, 0, 1, 38 },
    { 3, 0, 249, 39 },
};

struct Item10AnimationStep D_8010CD5C[12] = {
    { 2, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, 1, 40 },
    { 6, 0, 1, 42 },
    { 6, 0, 1, 43 },
    { 6, 1, 0, 44 },
};

struct Item10AnimationStep D_8010CD8C[11] = {
    { 3, 0, 1, 45 },
    { 3, 0, 1, 46 },
    { 3, 0, 1, 47 },
    { 3, 0, 1, 48 },
    { 3, 0, 1, 49 },
    { 3, 0, 1, 50 },
    { 3, 0, 1, 51 },
    { 3, 0, 1, 52 },
    { 3, 0, 1, 53 },
    { 3, 0, 1, 54 },
    { 3, 1, 0, 62 },
};

struct Item10AnimationStep D_8010CDB8[7] = {
    { 3, 0, 1, 55 },
    { 3, 0, 1, 56 },
    { 3, 0, 1, 57 },
    { 3, 0, 1, 58 },
    { 3, 0, 1, 59 },
    { 3, 0, 1, 60 },
    { 3, 0, 250, 61 },
};

struct Item10AnimationStep D_8010CDD4[7] = {
    { 3, 0, 1, 45 },
    { 3, 0, 1, 46 },
    { 3, 0, 1, 47 },
    { 3, 0, 1, 48 },
    { 3, 0, 1, 49 },
    { 3, 0, 1, 50 },
    { 3, 0, 250, 51 },
};

struct Item10AnimationStep D_8010CDF0[2] = {
    { 3, 0, 1, 63 },
    { 3, 0, 255, 64 },
};

struct Item10AnimationStep D_8010CDF8[1] = {
    { 3, 0, 0, 65 },
};

struct Item10AnimationStep* D_8010CDFC[14] = {
    D_8010CCA0,
    D_8010CCB0,
    D_8010CCC0,
    D_8010CCD0,
    D_8010CCE0,
    D_8010CCF0,
    D_8010CD00,
    D_8010CD10,
    D_8010CD5C,
    D_8010CD8C,
    D_8010CDB8,
    D_8010CDD4,
    D_8010CDF0,
    D_8010CDF8,
};

void func_800C24E0(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010CE34[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_10", func_800C2528);

INCLUDE_ASM("main/nonmatchings/items/item_10", func_800C2638);

INCLUDE_ASM("main/nonmatchings/items/item_10", func_800C27D8);

INCLUDE_ASM("main/nonmatchings/items/item_10", func_800C2850);

void func_800C28E8(struct ItemObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    is_on_screen(BASE_OBJECT(arg0));
}

extern struct Item10Offset D_8010CE5C[5];

void func_800C2918(struct ItemObj* arg0)
{
    if (arg0->tail_ext.item_10.timer == 0) {
        struct MiscObj* obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x24;
            obj->unk15 = get_random() & 0x40;
            obj->state = 0;
            obj->unk5 = 0;
            obj->unk6 = 0;
            obj->x_pos.u.hi = arg0->x_pos.u.hi + D_8010CE5C[get_random() & 3].x;
            obj->y_pos.u.hi = arg0->y_pos.u.hi + D_8010CE5C[get_random() & 3].y;
            obj->unk2 = 0;
            obj->ext.pointer.unk50 = arg0;
        }
        arg0->tail_ext.item_10.timer = (get_random() & 3) * 10;
        return;
    }
    arg0->tail_ext.item_10.timer--;
}

void func_800C2A04(struct ItemObj* arg0)
{
    if (arg0->tail_ext.item_10.previous_value == 0) {
        struct MiscObj* obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x24;
            obj->unk15 = get_random() & 0x40;
            obj->state = 0;
            obj->unk5 = 0;
            obj->unk6 = 0;
            obj->x_pos.u.hi = arg0->x_pos.u.hi + D_8010CE5C[(get_random() & 3)].x;
            obj->y_pos.u.hi = arg0->y_pos.u.hi + D_8010CE5C[(get_random() & 3)].y;
            obj->unk2 = 1;
            obj->ext.pointer.unk50 = arg0;
        }
        arg0->tail_ext.item_10.previous_value = (get_random() & 3) * 15;
        return;
    }
    arg0->tail_ext.item_10.previous_value--;
}

void func_800C2AF0(struct ItemObj* arg0)
{
    if (arg0->tail_ext.item_10.value == 0) {
        struct MiscObj* obj = find_free_misc_obj();
        if (obj != NULL) {
            obj->active = 0x41;
            obj->id = 0x24;
            obj->unk15 = get_random() & 0x40;
            obj->state = 0;
            obj->unk5 = 0;
            obj->unk6 = 0;
            obj->x_pos.u.hi = arg0->x_pos.u.hi + D_8010CE5C[get_random() & 3].x;
            obj->y_pos.u.hi = arg0->y_pos.u.hi + D_8010CE5C[get_random() & 3].y;
            obj->unk2 = 2;
            obj->ext.pointer.unk50 = arg0;
        }
        arg0->tail_ext.item_10.value = (get_random() & 3) * 12;
        return;
    }
    arg0->tail_ext.item_10.value--;
}

void (*D_8010CE34[])(struct ItemObj*) = {
    func_800C2528,
    func_800C2638,
    func_800C27D8,
    func_800C2850,
    func_800C28E8,
    func_800C2918,
};

u8 D_8010CE4C[4] = { 0, 0xF8, 0x20, 0x18 };
u8 D_8010CE50[4] = { 0xE0, 0xE8, 0x40, 0x30 };
u8 D_8010CE54[8] = { 1, 2, 3, 4, 5, 0, 0, 0 };

struct Item10Offset D_8010CE5C[5] = {
    { 0, 12 },
    { -16, -8 },
    { 16, -10 },
    { -19, 16 },
    { -16, -6 },
};
