// ShotObj, shot_object_update_funcs[57]
// 800AE450..800AEAC0
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_57", func_800AE450);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_57", func_800AE4F0);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_57", func_800AE594);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_57", func_800AE63C);

void func_800AE65C(struct ShotObj* arg0)
{
    if (arg0->unk7C->unk94 != 0) {
        arg0->base.state = 3;
    }
    D_8010A064[arg0->base.state](arg0);
}

void func_800AE6B4(struct BazObj* arg0)
{
    struct PlayerObj* ptr = &g_Player;
    arg0->base.x_pos.val = g_Player.base.x_pos.val;
    arg0->base.y_pos.val = g_Player.base.y_pos.val;

    if (arg0->base.state == 0) {
        func_800AE714(arg0, ptr);

    } else {
        func_800AE790(arg0, ptr);
    }
}

void func_800AE714(struct BazObj* arg0, struct PlayerObj* arg1)
{
    s32 var_v1 = arg0->base.unk2 == 0 ? 2 : 1;

    if (arg1->unk9B[0] == var_v1 || arg1->unk9B[1] == var_v1) {
        arg0->base.on_screen = 1;
        func_80015D60(arg0, arg0->base.unk2 + 8);
        arg0->base.state++;
    }
}

void func_800AE790(struct BazObj* arg0, struct PlayerObj* arg1)
{
    if ((arg1->unk9B[0] == 0) && (arg1->unk9B[1] == 0)) {
        arg0->base.on_screen = 0;
        arg0->base.state = 0;
    } else {
        func_80015DC8(arg0);
    }
}

void func_800AE7DC(struct UnkObj* arg0)
{
    struct PlayerObj* player = &g_Player;

    arg0->unk47 = player->cur_anim;
    arg0->base.unk15 = player->base.unk15;
    arg0->unk18 = arg0->base.x_pos.val;
    arg0->unk1C = arg0->base.y_pos.val;

    if (arg0->base.state == 0) {
        func_800AE848(arg0, player);
    } else {
        func_800AE88C(arg0, player);
    }
}

void func_800AE848(struct UnkObj* arg0, struct PlayerObj* player)
{
    if (player->unk8C != 0) {
        if (player->unk8C > 0) {
            arg0->base.on_screen = 1;
            func_800AEA58();
            return;
        }
        player->unk8C = 0;
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_57", func_800AE88C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_57", func_800AE8E4);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_57", func_800AE95C);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_57", func_800AE9D8);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_57", func_800AEA58);

INCLUDE_ASM("asm/us/main/nonmatchings/shots/shot_57", func_800AEAA0);

void (*D_8010A064[])(struct ShotObj*) = {
    func_800AE450,
    func_800AE4F0,
    func_800AE594,
    func_800AE63C,
};
