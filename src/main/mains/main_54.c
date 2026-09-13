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

void func_8006BFF8(struct MainObj* arg0)
{
    g_Player.unkBA = 0;
    func_80036AE4(0x14, g_Player.unk15);
    arg0->unk5 = 1;
    arg0->unk42 &= 0x7FFF;
    func_80015D60(arg0, 0x13);
    arg0->unk7C = 0x7F;
    arg0->unk7E = 0x19;
    arg0->unk61 = 0x19;
    func_8002B318(BASE_OBJECT(arg0), 0x60, 0x60);
}

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

void func_8006C598(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_8001540C(2, 0x82, arg0);
        func_80015D60(arg0, 0xA);
        arg0->unk54 = (const u8*)D_801001FC;
        arg0->unk50 = (const u8*)D_801001F8;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk6 = 3;
    }
}

void func_8006C61C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 0);
        func_8006EA78(arg0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

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

void func_8006CD80(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 0);
        func_8006EA78(arg0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CDD4);

void func_8006CE9C(struct MainObj* arg0)
{
    D_80100650[arg0->unk6](arg0);
}

void func_8006CED8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 0xD);
        arg0->unk6 = 1;
    }
}

void func_8006CF2C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk60 = 9;
        func_80015D60(arg0, 0xE);
        if (arg0->unk15 == 0) {
            arg0->unk20 = FIXED(-1);
        } else {
            arg0->unk20 = FIXED(1);
        }
        arg0->ext.main_54.unk86 = 1;
        arg0->ext.main_54.unk87 = 1;
        func_8001540C(2, 0x83, arg0);
        arg0->unk28 = FIXED(0.5);
        arg0->unk6 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006CFB8);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D280);

void func_8006D368(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk60 = 9;
        arg0->ext.main_54.unk86 = 1;
        arg0->unk20 = -arg0->unk20;
        func_80015D60(arg0, 0xE);
        func_8001540C(2, 0x83, arg0);
        arg0->unk6 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D3DC);

void func_8006D69C(struct MainObj* arg0)
{
    D_80100664[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D6D8);

void func_8006D830(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 7);
        arg0->unk6 = 2;
        arg0->ext.main_54.unk87 = 1;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006D888);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006DB04);

void func_8006DBE8(struct MainObj* arg0)
{
    D_80100674[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006DC24);

void func_8006DCF4(struct MainObj* arg0)
{
    if (arg0->ext.main_54.unk8C[0] == 0 && ((s16)background_objects[0].x_pos.u.hi == 0x24A0 || engine_obj.stage == 0xC)) {
        arg0->unk6 = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006DD44);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006DF68);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E034);

void func_8006E260(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        if (engine_obj.stage == 8) {
            arg0->unk15 = 0;
            func_80015D60(arg0, 0x18);
            func_8002217C(0x10, 0xFF, ENGINE_UNK2E);
            ENGINE_UNK2E = 1;
        }
        arg0->unk6 = 6;
    }
}

void func_8006E2E4(struct MainObj* arg0)
{
    if (abc_object.unkC == 0) {
        func_80015D60(arg0, 0x19);
        arg0->unk7E = 3;
        arg0->unk6 = 7;
        func_800921E8(7);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E334);

void func_8006E414(struct MainObj* arg0)
{
    D_80100694[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E450);

void func_8006E594(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        func_8001540C(2, 0x88, arg0);
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        func_80015D60(arg0, 0x12);
        arg0->unk6 = 2;
    }
}

void func_8006E604(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_8006EA78(arg0);
        func_80015D60(arg0, 0xC);
        arg0->unk7C = 0x14;
        arg0->unk7E = 1;
        arg0->unk5 = 6;
        arg0->unk6 = 0;
        arg0->ext.main_54.unk86 = 1;
    }
}

void func_8006E674(struct MainObj* arg0)
{
    D_801006A0[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E6B0);

void func_8006E750(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 == 0) {
        arg0->unk2C = FIXED(2);
        arg0->unk20 = 0;
        arg0->unk6 = 2;
        func_80015D60(arg0, 0x17);
        arg0->unk60 = 7;
        arg0->unk50 = (const u8*)&D_80100210;
        arg0->unk54 = (const u8*)&D_80100214;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E7CC);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E88C);

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006E920);

void func_8006EA78(struct MainObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_54", func_8006EAA8);

void (*D_801005E4[])(struct MainObj*) = {
    func_8006BB70,
    func_8006BD1C,
    func_8006BFBC,
};
