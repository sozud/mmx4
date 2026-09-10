// VisualObj, visual_object_update_funcs[32]
// 800B4E34..800B5570
#include "common.h"

u8 D_8010A714[4] = { 0xF, 6, 0x16, 0xF0 };
u8 D_8010A718[4] = { 0xF8, 0x16, 2, 0xFF };
u8 D_8010A71C[4] = { 0xD, 0xC, 0xD, 0xB };
s32 D_8010A720[8] = {
    -0x50000,
    -0x42000,
    0x45000,
    0x28000,
    -0x48000,
    -0x43000,
    0x50000,
    0x22000,
};
s32 D_8010A740[8] = {
    -0x10000,
    0x8000,
    0xC000,
    0x12000,
    0x10000,
    -0x8000,
    -0xC000,
    -0x12000,
};

INCLUDE_ASM("main/nonmatchings/visuals/visual_32", func_800B4E34);

void func_800B518C(struct VisualObj* arg0)
{
    if (arg0->unk50->state >= 3) {
        arg0->state = 2;
    }
    func_80015DC8(arg0);
    is_on_screen(arg0);
}

void func_800B51E0(struct VisualObj* arg0)
{
    if (--arg0->unk54 == 0) {
        arg0->unk54 = 30;
        arg0->unk5++;
    }
    is_on_screen(arg0);
}

void func_800B522C(struct VisualObj* arg0)
{
    arg0->on_screen = 0;
    if (--arg0->unk54 == 0) {
        arg0->state = 2;
    }
    if (arg0->unk54 & 1) {
        is_on_screen(arg0);
    }
}

void func_800B5280(struct VisualObj* arg0)
{
    D_8010A760[arg0->unk5](arg0);
    func_80015DC8(arg0);
    func_8002B718((struct MovingObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_32", func_800B52D8);

INCLUDE_ASM("main/nonmatchings/visuals/visual_32", func_800B5348);

void func_800B5448(struct VisualObj* arg0)
{
    struct PlayerObj* temp_s0 = arg0->unk50;
    func_80015DC8(arg0);
    arg0->x_pos.val = temp_s0->x_pos.val;
    arg0->y_pos.val = temp_s0->y_pos.val;
    is_on_screen(arg0);
    if (temp_s0->unk91 == 0) {
        arg0->state = 2;
    }
}

void func_800B54B0(struct VisualObj* arg0)
{
    D_8010A768[arg0->unk2](arg0);
}

void func_800B54EC(struct VisualObj* arg0)
{
    if (arg0->unk2 == 1) {
        arg0->unk50->unk8C--;
    }
    ZeroObjectState(arg0);
}

void func_800B5534(struct VisualObj* arg0)
{
    D_8010A784[arg0->state](arg0);
}

void (*D_8010A760[])(struct VisualObj*) = {
    func_800B51E0,
    func_800B522C,
};

void (*D_8010A768[])(struct VisualObj*) = {
    func_800B518C,
    func_800B5280,
    func_800B52D8,
    func_800B5348,
    func_800B5348,
    func_800B52D8,
    func_800B5448,
};

void (*D_8010A784[])(struct VisualObj*) = {
    func_800B4E34,
    func_800B54B0,
    func_800B54EC,
};
