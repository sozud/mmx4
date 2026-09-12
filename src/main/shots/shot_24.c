// ShotObj, shot_object_update_funcs[24]
// 8009E0B8..8009EB6C
#include "common.h"

void func_8009E0B8(struct ShotObj* arg0)
{
    D_8010910C[arg0->state](arg0);
}

void func_8009E0F4(struct ShotObj* arg0)
{
    u16 flags;
    struct WeaponObj* owner;
    u8 owner_state;

    arg0->unk58.collision_data = D_80106070;
    arg0->unk54 = D_801090C4;
    arg0->unk50.data = D_801090C4;
    arg0->unk84.shot_24.timer = 0x20;
    flags = arg0->unk42;
    owner = arg0->unk7C;
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk16 = 0;
    arg0->unk68 = NULL;
    arg0->unk6 = 0;
    arg0->unk84.shot_24.owner_notified = 0;
    arg0->unk42 = flags & 0x7FFF;
    owner_state = owner->unk6;
    arg0->unk5C = 1;
    arg0->unk60 = 4;
    arg0->unk84.shot_24.owner_state = owner_state;
    func_80015D60(arg0, 4);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E188);

void func_8009E34C(struct ShotObj* arg0)
{
    if (arg0->unk84.shot_24.timer == 0) {
        if (arg0->unk84.shot_24.owner_notified == 0) {
            arg0->unk7C->x_pos.bytes[0] = 0xFF;
        }
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    arg0->unk84.shot_24.timer--;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E3A8);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E490);

void func_8009E5A4(struct ShotObj* arg0)
{
    arg0->unk5 = arg0->unk84.shot_24.owner_notified;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E5B0);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E608);

void func_8009E690(struct ShotObj* arg0)
{
    s8 timer;
    u8* owner_state;

    owner_state = (u8*)&arg0->unk7C->x_pos;
    if (*owner_state == 4) {
        *owner_state = 5;
    }
    func_8002B718(MOVING_OBJECT(arg0));
    timer = (u8)arg0->unk7 - 1;
    arg0->unk7 = timer;
    if (timer == 0) {
        func_8001540C(2, 0x64, arg0);
        arg0->x_vel.val = FIXED(6);
        arg0->unk7 = 0x2A;
        arg0->unk5 = 5;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E718);

void func_8009E7B4(struct ShotObj* arg0)
{
    s8 temp_v0;

    temp_v0 = (u8)arg0->unk7 - 1;
    arg0->unk7 = temp_v0;
    if (temp_v0 == 0) {
        arg0->unk7 = 0x37;
        arg0->x_vel.val = -FIXED(4);
        arg0->unk5 = 7;
    }
}

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E7EC);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E8E0);

INCLUDE_ASM("main/nonmatchings/shots/shot_24", func_8009E9EC);

void func_8009EAA4(struct ShotObj* arg0)
{
    u8 active;

    active = arg0->unk7C->active;
    if ((active & 7) == ((active & 0x70) >> 4)) {
        arg0->unk5 = 3;
    }
    if ((u8)arg0->unk7C->x_pos.val != 4) {
        arg0->unk5 = 3;
    }
}

void func_8009EAF0(struct ShotObj* arg0)
{
    u8 pad[8];
    arg0->state = 0;
    arg0->x_pos.i.hi = D_801090E8[arg0->unk2][0];
    arg0->y_pos.i.hi = D_801090E8[arg0->unk2][1];
    func_800C813C(6, D_80109104, arg0);
    func_800AF808(arg0);
    ZeroObjectState(OBJECT_HEADER(arg0));
}

u8 D_801090C4[4] = { 0xFD, 0xFD, 0x05, 0x05 };

u8 D_801090C8[4] = { 0x43, 0xF7, 0x28, 0x11 };

u8 D_801090CC[2][4] = {
    { 0x45, 0xFD, 0x25, 0x04 },
    { 0xFE, 0xF8, 0x03, 0x02 },
};

s16 D_801090D4[3][2] = {
    { -0x72, -0x3A },
    { -0x6E, -0x18 },
    { -0x6D, 9 },
};

s16 D_801090E0[4] = { -0x53, -0x4F, -0x4E, 0 };

u16 D_801090E8[3][2] = {
    { 0x1A8B, 0x0143 },
    { 0x1A8E, 0x0168 },
    { 0x1A8F, 0x018A },
};

u8 D_801090F4[4] = { 1, 2, 4, 0 };

u8 D_801090F8[4] = { 0x10, 0x20, 0x40, 0 };

u8 D_801090FC[4] = { 0xFE, 0xFD, 0xFB, 0 };

u8 D_80109100[4] = { 0xEF, 0xDF, 0xBF, 0 };

u8 D_80109104[8] = { 6, 7, 8, 6, 7, 8, 0, 0 };

void (*D_8010910C[])(struct ShotObj*) = {
    func_8009E0F4,
    func_8009E188,
    func_8009E34C,
    func_8009E3A8,
    func_8009E490,
    func_8009EAF0,
};
