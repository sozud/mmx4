// MainObj, main_object_update_funcs[54]
// 8006BB00..8006EB40
#include "common.h"

void func_8006BB00(struct MainObj* arg0)
{
    D_801005E4[arg0->state](arg0);
    CollisionRelated(arg0);
    if (!(g_Player.unk5C & 0x7F)) {
        func_8006E920(arg0, 0x38);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006BB70);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006BD1C);

void func_8006BFBC(struct MainObj* arg0)
{
    D_80100620[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006BFF8);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006C07C);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006C170);

void func_8006C278(struct MainObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_8006C288(struct MainObj* arg0)
{
    D_8010062C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006C2C4);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006C378);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006C598);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006C61C);

void func_8006C670(struct MainObj* arg0)
{
    D_8010063C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006C6AC);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CA80);

void func_8006CB14(struct MainObj* arg0)
{
    D_80100644[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CB50);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CC3C);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CD80);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CDD4);

void func_8006CE9C(struct MainObj* arg0)
{
    D_80100650[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CED8);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CF2C);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CFB8);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D280);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D368);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D3DC);

void func_8006D69C(struct MainObj* arg0)
{
    D_80100664[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D6D8);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D830);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D888);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006DB04);

void func_8006DBE8(struct MainObj* arg0)
{
    D_80100674[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006DC24);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006DCF4);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006DD44);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006DF68);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E034);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E260);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E2E4);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E334);

void func_8006E414(struct MainObj* arg0)
{
    D_80100694[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E450);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E594);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E604);

void func_8006E674(struct MainObj* arg0)
{
    D_801006A0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E6B0);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E750);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E7CC);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E88C);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E920);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006EA78);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006EAA8);

void (*D_801005E4[])(struct MainObj*) = {
    func_8006BB70,
    func_8006BD1C,
    func_8006BFBC,
};
