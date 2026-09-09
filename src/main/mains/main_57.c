// MainObj, main_object_update_funcs[57]
// 80072194..800743FC
#include "common.h"

void func_80072194(struct MainObj* arg0)
{
    D_80101414[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    if (!(g_Player.unk5C & 0x7F)) {
        func_80074368(0x38);
    }
}

void func_80072204(struct MainObj* arg0)
{
    D_80101420[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072240);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800722A0);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072418);

void func_800725DC(struct MainObj* arg0)
{
    arg0->unk5 = 3;
    arg0->unk6 = 0;
}

void func_800725EC(struct BarObj* arg0)
{
    D_80101458[arg0->unk5](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072628);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800726CC);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800727C0);

void func_800728C8(struct MainObj* arg0)
{
    D_80101464[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072904);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072960);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072A14);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072A84);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072BCC);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072C20);

void func_80072CC4(struct MainObj* arg0)
{
    D_8010147C[arg0->unk6](arg0);
    func_8007427C(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072D14);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072DB0);

void func_80072DF8(struct MainObj* arg0)
{
    D_80101484[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072E34);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072EF8);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072F68);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072FF0);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073084);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073100);

void func_80073164(struct MainObj* arg0)
{
    D_8010149C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800731A0);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073228);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073294);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_8007330C);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_8007342C);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800734A8);

void func_80073500(struct MainObj* arg0)
{
    D_801014B4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_8007353C);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800735BC);

void func_80073650(struct MainObj* arg0)
{
    D_801014BC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_8007368C);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800736DC);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073748);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800737FC);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073878);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800738EC);

void func_80073938(struct MainObj* arg0)
{
    D_801014D4[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073974);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800739D4);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073B00);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073B58);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073BDC);

void func_80073C08(struct MainObj* arg0)
{
    D_801014E8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073C44);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073CA4);

void func_80073DDC(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0x60;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073E10);

void func_80073E3C(void)
{
}

void func_80073E44(struct MainObj* arg0)
{
    D_801014FC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073E80);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073F90);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80074068);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800740CC);

void func_80074158(struct MainObj* arg0)
{
    D_8010150C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80074194);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80074220);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_8007427C);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_800742AC);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80074368);
