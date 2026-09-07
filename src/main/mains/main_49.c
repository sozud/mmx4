// MainObj, main_object_update_funcs[49]
// 800684F8..8006970C
#include "common.h"

extern void (*D_800FFB78[])(struct MainObj*);

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
    extern void (*D_800FFBA8[])(struct MainObj*);

    D_800FFBA8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068B80);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068C2C);

extern void (*D_800FFBB0[])(struct MainObj*);

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

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_8006917C);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_800691B8);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80069248);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_800692AC);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_800692E8);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80069330);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_800693AC);

extern void (*D_800FFBC8[])(struct MainObj*);

void func_80069414(struct MainObj* arg0)
{
    D_800FFBC8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80069450);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_8006951C);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80069610);

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80069660);
