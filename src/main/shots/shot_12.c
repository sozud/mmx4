// ShotObj, shot_object_update_funcs[12]
// 8009B7F8..8009BD28
#include "common.h"

void func_8009B7F8(struct ShotObj* arg0)
{
    D_80108E9C[arg0->state](arg0);
    if (arg0->state >= 3) {
        CollisionRelated(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_12", func_8009B85C);

void func_8009B9B0(struct ShotObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_8002D9BC(arg0);
    if (*(s16*)&arg0->unk7C->active == 2) {
        arg0->state = 2;
    }
    if (func_8002BB80(arg0, &g_Player) != 0) {
        arg0->state = 2;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x10, 0x10);
        return;
    }
    arg0->state = 2;
}

void func_8009BA4C(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

INCLUDE_ASM("main/nonmatchings/shots/shot_12", func_8009BA6C);

void func_8009BAE8(struct ShotObj* self)
{
    u16* flags;
    u16 value;

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002DD04(MAIN_OBJECT(self)) < 0 || func_8002BB80(MAIN_OBJECT(self), MAIN_OBJECT(&g_Player)) != 0) {
        flags = (u16*)self->unk7C;
        *flags ^= D_80108E74.masks[self->unk2];
        func_8001540C(5, 2, NULL);
        func_800C813C(4, D_80108E98, self);
        self->state = 6;
        return;
    }

    value = *(u16*)self->unk7C;
    if (value == 0) {
        func_800C813C(4, D_80108E98, self);
        self->state = 6;
    } else if (!(value & D_80108E74.masks[self->unk2])) {
        func_80015D60(self, 0x1E);
        self->unk2C = FIXED(0.15625);
        self->y_vel.val = 0;
        self->state = 5;
    }
    func_8002B318(BASE_OBJECT(self), 0x80, 0x80);
}

void func_8009BC14(struct ShotObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_8002D9BC(arg0);

    if (arg0->unk70 & 8) {
        func_8001540C(5, 2, NULL);
        func_800C813C(4, D_80108E98, arg0);
        arg0->state = 6;
    }
    if (func_8002DD04(MAIN_OBJECT(arg0)) < 0) {
        func_8001540C(5, 2, NULL);
        func_800C813C(4, D_80108E98, arg0);
        arg0->state = 6;
    }
    if (func_8002BB80(arg0, &g_Player) != 0) {
        func_8001540C(5, 2, NULL);
        func_800C813C(4, D_80108E98, arg0);
        arg0->state = 6;
    }
    func_8002B318(BASE_OBJECT(arg0), 0x80, 0x80);
}

void func_8009BD08(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 D_80108E68[4] = { 0xFA, 0xF8, 0x0C, 0x0D };

u8 D_80108E6C[4] = { 0xF7, 0xF0, 0x10, 0x25 };

u8 D_80108E70[4] = { 0xFF, 0x04, 0x09, 0x14 };

struct Shot12CollisionData D_80108E74 = {
    { 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x100, 0x200 },
    0x16,
    { 0xFF, 0x0E, 0xEF, 0xFE, 0xE7, 0xF1, 0xF1, 0xEB, 0x01, 0xF2, 0x0F, 0xFF, 0x17, 0x0D, 0x11 },
};

u8 D_80108E98[4] = { 0x1F, 0x20, 0x1F, 0x20 };

void (*D_80108E9C[])(struct ShotObj*) = {
    func_8009B85C,
    func_8009B9B0,
    func_8009BA4C,
    func_8009BA6C,
    func_8009BAE8,
    func_8009BC14,
    func_8009BD08,
};
