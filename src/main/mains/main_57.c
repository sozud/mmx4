// MainObj, main_object_update_funcs[57]
// 80072194..800743FC
#include "common.h"

extern void* D_80100EB0[];
extern u8 D_80100EBC[];

void func_800742AC(struct MainObj* arg0);

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

void func_80072A14(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, arg0);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 0x4);
        arg0->unk7C = 0x50;
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072A84);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80072BCC);

void func_80072C20(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (func_8009227C() != 0) {
        return;
    }
    if (--arg0->unk7E == 0) {
        func_8001540C(0, 0xE, NULL);
        arg0->unk7E = 3;
    }
    if (++arg0->unk5C == 0x30) {
        func_800742AC(arg0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->unk7E = 0;
        func_80036B18();
    }
}

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

void func_80073228(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, arg0);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 2);
        arg0->unk6++;
    }
}

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

void func_80073878(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 3) {
        func_8001540C(2, 0x92, arg0);
    }
    if (arg0->animation_step.fields.event == 2) {
        func_80015D60(arg0, 0x1A);
        arg0->unk7C = 0x40;
        arg0->unk6++;
    }
}

void func_800738EC(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

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

void func_80073E10(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80073E3C(struct MainObj* arg0)
{
}

void func_80073E44(struct MainObj* arg0)
{
    D_801014FC[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073E80);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80073F90);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80074068);

void func_800740CC(struct MainObj* arg0)
{
    if (--arg0->unk7C != 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        return;
    }
    if (arg0->unk5C >= 0x18) {
        arg0->ext.main_57.unk88 = &D_80100E78;
    } else {
        arg0->ext.main_57.unk88 = &D_80100E7C;
    }
    arg0->unk5 = 3;
    arg0->unk6 = 0;
    arg0->ext.main_57.unk93 = 0;
    arg0->ext.main_57.unk94 = 1;
}

void func_80074158(struct MainObj* arg0)
{
    D_8010150C[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80074194);

INCLUDE_ASM("main/nonmatchings/mains/main_57", func_80074220);

void func_8007427C(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

#ifndef MMX4_PC
void func_800742AC(struct MainObj* arg0)
{
    register u32 idx asm("s0");
    u8** table;
    u8* weights;
    u8 i;
    u32 rnd;
    u32 gr;

    idx = arg0->unk5C - 1;
    if ((s32)idx < 0)
        idx = arg0->unk5C + 0xE;
    idx = (idx >> 2);
    idx &= 0x3FC;
    table = *(u8***)((u8*)D_80100EB0 + idx);
    gr = get_random();
    i = 0;
    weights = &D_80100EBC[idx];
    rnd = gr & 0xF;
    while (i < 4) {
        if (rnd < weights[i]) {
            arg0->ext.main_57.unk88 = (struct Unk_unk68*)table[i];
            return;
        }
        i++;
    }
}
#endif

void func_80074368(s32 arg0)
{
    u16* list;
    u32* attrs;

    list = D_801013C8;
    if (engine_obj.stage == 0xC) {
        list = D_801013EC;
    }
    while (*list != 0) {
        attrs = SP_BG_TILE_ATTRS;
        attrs[*list] &= ~0xFF;
        attrs[*list] |= arg0;
        list++;
    }
}
