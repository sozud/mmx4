// MainObj, main_object_update_funcs[20]
// 8005458C..80054C50
#include "common.h"

void func_8005458C(struct MainObj* arg0)
{
    D_800FC990[arg0->state](arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    CollisionRelated(PLAYER_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_20", func_800545EC);

void func_80054710(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    func_80015D60(arg0, 0);
}

void func_80054738(struct MainObj* arg0)
{
    func_80015DC8(arg0);
}

void func_80054758(struct MainObj* arg0)
{
    s32 collision = func_8002DD04(arg0);
    s8 countdown;

    if (arg0->unk2 == 0 && arg0->ext.main_20.unk80 != arg0->unk5C) {
        countdown = arg0->ext.main_20.unk81--;
        if (countdown != 1) {
            if (countdown == 2) {
                func_800583B0(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi - 0x10, 0);
            }
        } else {
            func_800583B0(arg0, arg0->x_pos.i.hi, arg0->y_pos.i.hi - 0x10, 5);
            arg0->unk5C = 1;
        }
        arg0->ext.main_20.unk80 = arg0->unk5C;
    }
    if (collision < 0) {
        arg0->unk5 = 0;
        arg0->state++;
        arg0->unk42 &= 0x7FFF;
        return;
    }
    D_800FC99C[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x80, 0x80) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
    } else {
        func_8002B0C8(OBJECT_HEADER(arg0));
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_20", func_800548B8);

void func_80054B38(struct MainObj* arg0)
{
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk50 = (const u8*)&D_800FC860;
    }
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5++;
        return;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80054B98(struct MainObj* arg0)
{
    arg0->unk7C = 1;
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_80054BBC(struct MainObj* self)
{
    D_800FC9A8[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) == 0) {
        if (self->unk7C == 0) {
            func_8002B318(BASE_OBJECT(self), 0x50, 0x80);
        }
    } else {
        func_8002B108(OBJECT_HEADER(self));
    }
}
