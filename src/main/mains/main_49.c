// MainObj, main_object_update_funcs[49]
// 800684F8..8006970C
#include "common.h"

void func_800684F8(struct MainObj* arg0)
{
    D_800FFB78[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068548);

void func_800688B8(struct MainObj* arg0)
{
    u8 temp_v1;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (func_8002DD04(arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(5, D_800FFB68, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0x12);
        goto block_12;
    }
    temp_v1 = SP_CUR_MAIN_OBJ->ext.main_49.unk85;
    if (temp_v1 != 2 && temp_v1 < 6U) {
        func_80068F88(arg0);
    }
    func_80068D6C(arg0);
    if (SP_CUR_MAIN_OBJ->ext.main_49.unk86 == 0) {
        func_80069000(arg0);
    }
    D_800FFB88[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (SP_CUR_MAIN_OBJ->ext.main_49.unk86 == 0) {
        if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
            is_on_screen(BASE_OBJECT(arg0));
        } else {
            arg0->state = 2;
        }
    } else if (func_8002B1E8(BASE_OBJECT(arg0), 0x70, 0) != 0) {
        arg0->state = 2;
    } else {
        is_on_screen(BASE_OBJECT(arg0));
    }
    return;
block_12:
    arg0->state = 2;
}

void func_80068A10(struct MainObj* arg0)
{
    if (SP_CUR_MAIN_OBJ->ext.main_49.unk86 == 0 || arg0->unk2 == 9) {
        func_8002B0C8(OBJECT_HEADER(arg0));
    } else {
        func_8002B108(OBJECT_HEADER(arg0));
    }
}

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

extern u32 D_801076F8[];
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

void func_80068D4C(struct MainObj* arg0)
{
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80068D6C);

void func_80068F88(struct MainObj* arg0)
{
    u8 timer;

    if (arg0->unk5 == 2) {
        timer = SP_CUR_MAIN_OBJ->ext.main_49.index + 1;
        SP_CUR_MAIN_OBJ->ext.main_49.index = timer;
        if ((timer & 0xFF) == 0x5A) {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            SP_CUR_MAIN_OBJ->ext.main_49.index = 0;
            arg0->unk24 = 0;
            arg0->unk2C = 0;
            arg0->unk20 = 0;
            func_80015D60(arg0, 7);
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_49", func_80069000);

void func_8006917C(struct MainObj* arg0)
{
    D_800FFBB8[arg0->unk6](arg0);
}

void func_800691B8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        if (SP_CUR_MAIN_OBJ->ext.main_49.unk80 == 4) {
            func_80015D60(arg0, 0x17);
        } else {
            func_80015D60(arg0, 0x18);
        }
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk6++;
    }
}

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
