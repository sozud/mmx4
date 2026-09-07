// MainObj, main_object_update_funcs[49]
// 800684F8..8006970C
#include "common.h"

void func_800684F8(struct MainObj* arg0)
{
    D_800FFB78[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068548);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_800688B8);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068A10);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068A68);

void func_80068B3C(struct MainObj* arg0)
{
}

void func_80068B44(struct MainObj* arg0)
{

    D_800FFBA8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068B80);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068C2C);

void func_80068CB0(struct MainObj* arg0)
{
    D_800FFBB0[arg0->unk6](arg0);
}

extern u8 D_801076F8[];
extern u8 D_800FFB60[];
extern u8 D_800FFB64[];

void func_80068CEC(struct MainObj* arg0)
{
    arg0->collision_data = (const u16*)D_801076F8;
    arg0->unk54 = D_800FFB60;
    arg0->unk50 = D_800FFB64;
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk24 = 0;
    arg0->unk2C = 0;
    arg0->unk6++;
    func_80015D60(arg0, 8);
}

void func_80068D4C(void)
{
    func_80015DC8();
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068D6C);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068F88);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80069000);

void func_8006917C(struct MainObj* arg0)
{
    D_800FFBB8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_800691B8);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80069248);

void func_800692AC(struct MainObj* arg0)
{
    D_800FFBC0[arg0->unk6](arg0);
}

void func_800692E8(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80069330);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_800693AC);

void func_80069414(struct MainObj* arg0)
{
    D_800FFBC8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80069450);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_8006951C);

void func_80069610(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 11);
        arg0->unk6++;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80069660);
