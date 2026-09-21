// ItemObj, item_object_update_funcs[24]
// 800C6054..800C62DC
#include "common.h"

struct Item24AnimationStep {
    u8 duration;
    u8 mode;
    u8 frame;
    u8 command;
};

struct Item24AnimationStep D_8010D360[7] = {
    { 1, 0, 0, 0 },
    { 1, 0, 0, 1 },
    { 1, 0, 0, 2 },
    { 1, 0, 0, 3 },
    { 1, 0, 0, 4 },
    { 1, 0, 0, 5 },
    { 1, 0, 0, 6 },
};

struct Item24AnimationStep* D_8010D37C[7] = {
    &D_8010D360[0],
    &D_8010D360[1],
    &D_8010D360[2],
    &D_8010D360[3],
    &D_8010D360[4],
    &D_8010D360[5],
    &D_8010D360[6],
};

u8 D_8010D398[12] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 0, 0 };
u8 D_8010D3A4[4] = { 0, 0, 0x17, 0x26 };
u32 D_8010D3A8 = 0x4927DBEC;

void func_800C6054(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010D3AC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/items/item_24", func_800C609C);

void func_800C6198(struct ItemObj* arg0)
{
    s32 collision;
    u16 flags;

    collision = func_8002DD04(MAIN_OBJECT(arg0));
    if (collision < 0) {
        arg0->on_screen = 0;
        func_800C813C(0xA, D_8010D398, arg0);
        arg0->unk7C.timer = 0x1E;
        arg0->state++;
        return;
    }
    if (collision > 0) {
        flags = arg0->unk42 | 0x8000;
    } else {
        flags = arg0->unk42 & 0x7FFF;
    }
    arg0->unk42 = flags;
    func_8002E184(arg0);
    is_on_screen(BASE_OBJECT(arg0));
}

extern u32 D_8010D3B8[];

void func_800C6228(struct ItemObj* arg0)
{
    if (--arg0->unk7C.timer != 0) {
        if ((D_80141BD8.unk0 & 7) == 0) {
            func_800AF878(BASE_OBJECT(arg0), 1, 0xF, 0x3F);
        }
        if ((D_80141BD8.unk0 & 0xF) == 0) {
            func_8001540C(0, D_8010D3B8[get_random() & 3], arg0);
        }
    } else {
        func_8002B108(OBJECT_HEADER(arg0));
    }
}

void (*D_8010D3AC[])(struct ItemObj*) = {
    func_800C609C,
    func_800C6198,
    func_800C6228,
};

u32 D_8010D3B8[4] = { 0, 1, 2, 3 };
