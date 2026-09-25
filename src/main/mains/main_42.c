// MainObj, main_object_update_funcs[42]
// 80062D60..800631C8
#include "common.h"

void func_80062D60(struct MainObj* arg0)
{
    D_800FEF74[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_42", func_80062D9C);

void func_80062E70(struct MainObj* arg0)
{
    func_80015D60(arg0, 0);
}

void func_80062E90(struct MainObj* arg0)
{
    s16 temp_v0;
    s32 temp_a2;
    s32 temp_v0_2;

    temp_v0 = (u16)arg0->unk7C - 1;
    arg0->unk7C = temp_v0;
    if (temp_v0 == 0) {
        arg0->unk7C = 0x5A;
        func_8002B93C(
            MOVING_OBJECT(arg0),
            func_8002B7DC(
                OBJECT_HEADER(arg0),
                OBJECT_HEADER(&g_Player))
                & 0xFF);

        temp_v0_2 = arg0->unk20;
        temp_a2 = arg0->unk24;
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = -((s32)(temp_v0_2 * 0x2D) >> 8);
        arg0->unk2C = -((s32)(temp_a2 * 0x2D) >> 8);
        func_80015D60(arg0, 1);
        arg0->unk5 = 3;
        arg0->ext.main_42.unk84 = 0;
        arg0->ext.main_42.background_relative += 1;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_80062F60(struct MainObj* arg0)
{
    struct MiscObj* misc;

    if (--arg0->unk7C == 0x5A) {
        arg0->unk28 = -arg0->unk28;
        arg0->unk2C = -arg0->unk2C;
    }
    if (--arg0->unk7C == 0) {
        if (arg0->ext.main_42.background_relative < 5) {
            arg0->unk7C = 0xB4;
            arg0->unk28 = 0;
            arg0->unk2C = 0;
            arg0->unk20 = 0;
            arg0->unk24 = 0;
            func_80015D60(arg0, 0);
            arg0->unk5 = 2;
        } else {
            arg0->unk20 = 0;
            arg0->unk24 = FIXED(2);
            func_80015D60(arg0, 3);
            arg0->unk5 = 4;
            arg0->ext.main_42.unk84 = NULL;
        }
    }
    if (!(arg0->unk7C & 3)) {
        misc = func_8002AE90(arg0->ext.main_42.unk84, 0);
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0xE;
            misc->ext.pointer.unk50 = arg0;
            misc->x_pos.val = arg0->x_pos.val;
            misc->y_pos.val = arg0->y_pos.val;
            misc->unk2 = arg0->animation_step.fields.event;
            arg0->ext.main_42.unk84 = misc;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
}

void func_800630AC(struct MainObj* arg0)
{
    func_80015DC8(arg0);
    func_8002B718(arg0);
}

void func_800630DC(struct MainObj* self)
{
    extern char D_800FEF6C;
    extern void (*D_800FEF80[])(struct MainObj*);

    if (func_8002DD04(self) < 0) {
        self->unk5 = 0;
        self->state += 1;
        self->unk42 &= 0x7FFF;
        func_800AF808(BASE_OBJECT(self));
        func_800C813C(6, &D_800FEF6C, self);
        return;
    }

    D_800FEF80[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }

    func_8002B0C8(OBJECT_HEADER(self));
}

void func_800631A8(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}
