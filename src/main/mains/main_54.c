// MainObj, main_object_update_funcs[54]
// 8006BB00..8006EB40
#include "common.h"

void func_8006BB00(struct MainObj* arg0)
{
    D_801005E4[arg0->base.state](arg0);
    CollisionRelated(arg0);
    if (!(g_Player.unk5C & 0x7F)) {
        func_8006E920(arg0, 0x38);
    }
}

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006BB70);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006BD1C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006BFBC);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006BFF8);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006C07C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006C170);

void func_8006C278(struct MainObj* arg0)
{
    arg0->base.unk5 = 3;
    arg0->base.unk6 = 0;
}

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006C288);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006C2C4);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006C378);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006C598);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006C61C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006C670);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006C6AC);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006CA80);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006CB14);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006CB50);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006CC3C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006CD80);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006CDD4);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006CE9C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006CED8);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006CF2C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006CFB8);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006D280);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006D368);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006D3DC);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006D69C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006D6D8);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006D830);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006D888);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006DB04);

void func_8006DBE8(struct MainObj* arg0)
{
    D_80100674[arg0->base.unk6](arg0);
}

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006DC24);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006DCF4);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006DD44);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006DF68);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E034);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E260);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E2E4);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E334);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E414);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E450);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E594);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E604);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E674);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E6B0);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E750);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E7CC);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E88C);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006E920);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006EA78);

INCLUDE_ASM("asm/us/main/nonmatchings/mains/main_54", func_8006EAA8);

void (*D_801005E4[])(struct MainObj*) = {
    func_8006BB70,
    func_8006BD1C,
    func_8006BFBC,
};
