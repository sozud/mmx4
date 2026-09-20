// MainObj, main_object_update_funcs[37]
// 8005FDBC..80060A88
#include "common.h"

void func_8005FDBC(struct MainObj* arg0)
{
    D_800FE6E4[arg0->state](arg0);
    if (arg0->unk5 != 4) {
        CollisionRelated(PLAYER_OBJECT(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_8005FE1C);

extern void (*D_800FE6F0[])(struct MainObj*);
extern char D_800FE6CC[];

void func_80060144(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    D_800FE6F0[self->unk5](self);
    func_8002D9BC(self);
    self->ext.main_37.saved_unk5 = self->unk5;
    if (func_8002DD04(self) < 0) {
        func_800AF808(BASE_OBJECT(self));
        func_800C813C(0xA, &D_800FE6CC, self);
        func_800BF60C(BASE_OBJECT(self), 0x13);
        self->state = 2;
    } else if (self->unk2 == 3 || func_8002B1E8(BASE_OBJECT(self), 0x60, 0x40) == 0) {
        func_8002B318(BASE_OBJECT(self), 0x20, 0x20);
    } else {
        self->state = 2;
    }
}

void func_80060228(struct MainObj* arg0)
{
    arg0->unk62 = 0;
    arg0->ext.main_37.unk80.word = 0;
    arg0->ext.main_37.unk84 = 0;
    arg0->ext.main_37.unk88 = 0;
    arg0->ext.main_37.unk8C = 0;
    arg0->ext.main_37.saved_unk5 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8006025C(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_37.saved_unk5;
}

void func_80060268(struct MainObj* arg0)
{
    D_800FE704[arg0->unk6](arg0);
}

void func_800602A4(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->ext.main_37.unk80.saved_direction = arg0->unk15;
        func_80060A58(ANIMATED_OBJECT(arg0));
        arg0->unk24 = 0;
        if (arg0->unk15 == 0) {
            arg0->unk20 = FIXED(-1.5);
        } else {
            arg0->unk20 = FIXED(1.5);
        }
        if (arg0->unk15 != arg0->ext.main_37.unk80.saved_direction) {
            func_80015D60(arg0, 2);
            arg0->unk5 = 3;
            arg0->unk6 = 2;
        } else {
            func_80015D60(arg0, 3);
            arg0->unk6 = 1;
        }
    }
}

void func_80060354(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_800603A0(struct MainObj* arg0)
{
    D_800FE70C[arg0->unk6](arg0);
}

void func_800603DC(struct MainObj* arg0)
{
    s32 direction_mask;

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk15 == 0) {
        direction_mask = arg0->unk70 & 2;
    } else {
        direction_mask = arg0->unk70 & 1;
    }
    if (direction_mask != 0) {
        arg0->unk6 = 2;
        arg0->unk15 ^= 0x40;
        arg0->unk20 = -arg0->unk20;
        func_80015D60(arg0, 2);
        return;
    }
    if ((arg0->unk70 & 8) == 0) {
        arg0->unk20 = 0;
        arg0->unk24 = FIXED(-1.5);
        func_80015D60(arg0, 3);
        arg0->unk6 = 1;
    }
}

void func_800604A0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 1);
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_800604EC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80060538(struct MainObj* arg0)
{
    D_800FE718[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_80060574);

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_800606D8);

void func_80060870(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk28 = FIXED(0.125);
        arg0->unk20 = 0;
        arg0->unk6 = 3;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_37", func_800608CC);

void func_8006097C(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk6 = 5;
    }
}

void func_800609C4(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk20 == 0) {
        arg0->unk7C = 0x28;
        arg0->unk6 = 6;
    }
}

void func_80060A10(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk6 = 3;
    }
}

void func_80060A58(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}
