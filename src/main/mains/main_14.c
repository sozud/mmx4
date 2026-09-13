// MainObj, main_object_update_funcs[14]
// 8004CF24..8004D930
#include "common.h"

void func_8004CF24(struct MainObj* arg0)
{
    D_800FB9FC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004CF60);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D044);

void func_8004D160(struct MainObj* arg0)
{
    arg0->ext.main_14.unk80 = 0;
    arg0->ext.main_14.unk84 = 0;
    engine_obj.character_state.bytes[0] = 0;
    func_80015930(2, 0x40);
    if (arg0->ext.main_14.unk94 != 0) {
        func_8002B0C8(OBJECT_HEADER(arg0));
        return;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8004D1C8(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_14.saved_unk5;
}

void func_8004D1D4(struct MainObj* arg0)
{
    D_800FBA20[arg0->unk6](arg0);
}

void func_8004D210(struct MainObj* arg0)
{
    s32* velocity;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8004D784(arg0, 3);
    func_8001540C(2, 0x40, arg0);

    velocity = D_800FB89C;
    arg0->ext.main_14.unk80 = 0x20;
    arg0->ext.main_14.unk84 = 1;
    if (arg0->unk15 & 0x40) {
        velocity++;
    }
    arg0->unk20 = *velocity;
    arg0->unk6++;
}

void func_8004D290(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (--arg0->ext.main_14.unk80 == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_8004D2E0(struct MainObj* arg0)
{
    D_800FBA28[arg0->unk6](arg0);
}

void func_8004D31C(struct MainObj* arg0)
{
    func_80015D60(arg0, 1);
    arg0->ext.main_14.unk80 = 0x2E;
    arg0->unk20 = 0;
    arg0->unk54 = (const u8*)D_800FB890;
    arg0->unk50 = (const u8*)D_800FB890;
    arg0->unk6++;
}

void func_8004D370(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_14.unk80 == 0) {
        func_80015D60(arg0, 2);
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D3C8);

void func_8004D408(struct MainObj* arg0)
{
    D_800FBA34[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D444);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D480);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D4D0);

void func_8004D580(struct MainObj* arg0)
{
    arg0->ext.main_14.unk8C = 1;
    func_8001540C(5, 4, arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 0);
    arg0->unk6 = 0;
    arg0->unk5++;
}

void func_8004D5E0(struct MainObj* arg0)
{
    D_800FBA44[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D61C);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D69C);

void func_8004D6CC(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D6FC);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D784);

INCLUDE_ASM("main/nonmatchings/mains/main_14", func_8004D84C);
