// MainObj, main_object_update_funcs[19]
// 8005284C..8005458C
#include "common.h"

void func_8005284C(struct MainObj* arg0)
{
    if (arg0->unk2 < 3) {
        D_800FC784[arg0->state](arg0);
    } else {
        D_800FC790[arg0->state](arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_800528BC);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80052A68);

void func_80052B94(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        func_80015D60(
            arg0, D_800FC7B4[SP_CUR_MAIN_OBJ->ext.main_19.animation_index]);
        return;
    }

    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        SP_CUR_MAIN_OBJ->ext.main_19.unk80 = get_random() & 1;
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80052C2C(struct MainObj* arg0)
{
    arg0->unk7C++;
    D_800FC7B8[arg0->unk6](arg0);
}

void func_80052C70(struct MainObj* arg0)
{
    func_8002B718((struct MovingObj*)arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    if (arg0->unk70 != 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80052CB8);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80052E94);

void func_800531B4(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk6 = 3;
        if (SP_CUR_MAIN_OBJ->ext.main_19.animation_index < 2) {
            func_80015D60(arg0, 0xB);
        } else {
            func_80015D60(arg0, 0xA);
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80053224(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk6 = 0;
        SP_CUR_MAIN_OBJ->ext.main_19.unk80 ^= 1;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80053274(struct MainObj* arg0)
{
    s32 animation;
    struct MainObj* current;

    if (arg0->animation_step.fields.relative_step < 0) {
        current = SP_CUR_MAIN_OBJ;
        if (current->ext.main_19.animation_index < 2) {
            animation = 9;
            if (current->ext.main_19.unk80 == 0) {
                animation = 8;
            }
            arg0->unk2C = 0;
            arg0->unk20 = 0;
            arg0->unk28 = 0;
        } else {
            animation = 7;
            arg0->unk24 = 0;
            arg0->unk2C = 0;
        }
        arg0->unk68 = D_800FC73C[arg0->unk2 >> 1];
        func_80015D60(arg0, animation);
        arg0->unk6 = 5;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053338);

void func_800535CC(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk6 = 0;
    } else {
        func_80015DC8(arg0);
    }
}

void func_80053604(struct MainObj* arg0)
{
    D_800FC7DC[arg0->unk6](arg0);
}

void func_80053640(struct MainObj* arg0)
{
    arg0->unk6 = 1;
    arg0->unk7C = 0;
    func_80015D60(arg0,
        D_800FC7E4[SP_CUR_MAIN_OBJ->ext.main_19.animation_index >> 1]);
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_8005368C);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_800537E0);

u8 func_8005398C(struct MainObj* self)
{
    u16 player_x;
    u16 player_y;
    s16 dy;
    s16 dx;
    s32 flags;

    player_x = g_Player.x_pos.u.hi;
    player_y = g_Player.y_pos.u.hi;
    dy = player_y - self->y_pos.u.hi;
    dx = player_x - self->x_pos.u.hi;
    flags = 0;

    if ((dx < 0 ? -dx : dx) < 0x40 || (dy < 0 ? -dy : dy) >= 0x60) {
        flags = 1;
    }
    if ((dx < 0 ? -dx : dx) >= 0x80) {
        flags |= 2;
    }

    func_8002B93C(MOVING_OBJECT(self),
        func_8002B7DC(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF);
    return flags;
}

u8 func_80053A88(struct PlayerObj* arg0, s16 arg1, s16 arg2)
{
    s32 saved_x_pos;
    s32 saved_y_pos;
    s32 saved_unk18;
    s32 saved_unk1C;
    u8 result;

    saved_x_pos = arg0->x_pos.val;
    saved_y_pos = arg0->y_pos.val;
    saved_unk18 = arg0->unk18.val;
    saved_unk1C = arg0->unk1C.val;
    arg0->unk18.val = saved_x_pos;
    arg0->unk1C.val = saved_y_pos;
    arg0->x_pos.u.hi = arg0->x_pos.u.hi + arg1;
    arg0->y_pos.u.hi = arg0->y_pos.u.hi + arg2;
    CollisionRelated(arg0);
    result = arg0->unk70;
    arg0->x_pos.val = saved_x_pos;
    arg0->y_pos.val = saved_y_pos;
    arg0->unk18.val = saved_unk18;
    arg0->unk1C.val = saved_unk1C;
    arg0->unk70 = 0;
    return result;
}

u8 func_80053B18(struct PlayerObj* arg0, s16 arg1, s16 arg2)
{
    arg1 = arg0->x_pos.i.hi + arg1;
    arg2 = arg0->y_pos.i.hi + arg2;
    return func_8002D724(arg0, arg1, arg2);
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053B54);

void func_80053D04(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053D24);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_80053EB8);

INCLUDE_ASM("main/nonmatchings/mains/main_19", func_8005402C);

void func_8005440C(struct MainObj* self)
{
    s32 index;

    index = (SP_CUR_MAIN_OBJ->ext.main_19.animation_index << 2) + SP_CUR_MAIN_OBJ->ext.main_19.unk80;
    self->unk20 = D_800FC814[index] << 16;
    self->unk24 = D_800FC824[index] << 16;
    self->unk15 = D_800FC834[index];
    func_80015D60(self, D_800FC83C[index]);
    self->unk54 = D_800FC754[SP_CUR_MAIN_OBJ->ext.main_19.unk80];
    self->unk50 = D_800FC764[SP_CUR_MAIN_OBJ->ext.main_19.unk80];
    self->unk68 = D_800FC774[SP_CUR_MAIN_OBJ->ext.main_19.unk80];
}

void func_80054518(struct MainObj* arg0)
{
    s16 timer;

    if (arg0->unk6 == 0) {
        func_8005440C(arg0);
        arg0->unk6 = 1;
        arg0->unk7C = 0x1E;
        return;
    }
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}
