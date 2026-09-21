// ShotObj, shot_object_update_funcs[50]
// 800AA2FC..800AA5E0
#include "common.h"

void (*D_80109BEC[])(struct ShotObj*) = {
    func_800AA20C,
    func_800AA2FC,
    func_800AA3A0,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_50", func_800AA2FC);

void func_800AA3A0(struct ShotObj* self)
{
    s32 velocity;

    velocity = self->x_vel.val;
    if (velocity < 0) {
        if (self->unk70 & 2) {
            self->x_vel.val = -velocity;
            if ((self->unk70 & 0xD) == 0xD) {
                self->unk84.value = 1;
            }
        }
    } else if (self->unk70 & 1) {
        self->x_vel.val = -velocity;
        if ((self->unk70 & 0xE) == 0xE) {
            self->unk84.value = 1;
        }
    }

    velocity = self->y_vel.val;
    if (velocity < 0) {
        if (self->unk70 & 8) {
            self->y_vel.val = -velocity;
            if ((self->unk70 & 0xC) == 0xC) {
                self->unk84.value = 1;
            }
        }
    } else if (self->unk70 & 4) {
        self->y_vel.val = -velocity;
        if ((self->unk70 & 0xC) == 0xC) {
            self->unk84.value = 1;
        }
    }

    func_8002B694(ANIMATED_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
}

void func_800AA488(struct ShotObj* arg0)
{
    extern u8 D_80109BB0[];

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_80109BEC[arg0->unk5](arg0);
    CollisionRelated(arg0);
    if (arg0->unk7C->state == 2 || arg0->unk84.value != 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_80109BB0, arg0);
        arg0->state = 2;
        arg0->on_screen = 0;
        return;
    }
    func_8002D9BC(arg0);
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_80109BB0, arg0);
        arg0->state = 2;
        arg0->on_screen = 0;
        return;
    }
    if (func_8002B160(BASE_OBJECT(arg0)) == 0) {
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    arg0->state = 2;
    arg0->unk5 = 0;
    arg0->unk6 = 0;
    arg0->on_screen = 0;
}

void func_800AA5A4(struct ShotObj* arg0)
{
    D_80109BF8[arg0->state](arg0);
}

void (*D_80109BF8[])(struct ShotObj*) = {
    func_800AA148,
    func_800AA488,
    func_800A9D98,
};
