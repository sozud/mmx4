// ShotObj, shot_object_update_funcs[53]
// 800AAC98..800ABE08
#include "common.h"

s8 D_80109C38[3][4] = {
    { -34, -40, 67, 79 },
    { -54, -19, 20, 25 },
    { 0, 4, 26, 35 },
};

s16 D_80109C44[8][3][2] = {
    { { 0x3E0, 0x278 }, { 0x610, 0x258 }, { 0x610, 0x2A8 } },
    { { 0x3E0, 0x2B8 }, { 0x4D8, 0x1D0 }, { 0x610, 0x2B8 } },
    { { 0x3E0, 0x2B8 }, { 0x3E0, 0x258 }, { 0x610, 0x288 } },
    { { 0x610, 0x2B8 }, { 0x3E0, 0x258 }, { 0x3E0, 0x2A8 } },
    { { 0x610, 0x2B8 }, { 0x3E0, 0x258 }, { 0x3E0, 0x2A8 } },
    { { 0x610, 0x2B8 }, { 0x3E0, 0x258 }, { 0x3E0, 0x2B8 } },
    { { 0x568, 0x1D0 }, { 0x528, 0x1D0 }, { 0x448, 0x1D0 } },
    { { 0x598, 0x308 }, { 0x448, 0x1D0 }, { 0x4E8, 0x308 } },
};

s16 D_80109CA4[8][3][2] = {
    { { 0x448, 0x278 }, { 0x598, 0x258 }, { 0x598, 0x2A8 } },
    { { 0x448, 0x2B8 }, { 0x4D8, 0x248 }, { 0x598, 0x2B8 } },
    { { 0x448, 0x2B8 }, { 0x448, 0x258 }, { 0x598, 0x288 } },
    { { 0x578, 0x2B8 }, { 0x498, 0x258 }, { 0x498, 0x2A8 } },
    { { 0x598, 0x2B8 }, { 0x498, 0x258 }, { 0x498, 0x2A8 } },
    { { 0x578, 0x2B8 }, { 0x408, 0x258 }, { 0x448, 0x2B8 } },
    { { 0x568, 0x248 }, { 0x528, 0x258 }, { 0x448, 0x248 } },
    { { 0x598, 0x2B8 }, { 0x448, 0x248 }, { 0x4E8, 0x2B8 } },
};

u8 D_80109D04[8][3] = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 1, 0, 0 },
    { 1, 0, 2 },
    { 1, 0, 0 },
    { 0, 0, 0 },
    { 1, 0, 1 },
};

void (*D_80109D1C[])(struct ShotObj*) = {
    func_800AAD6C,
    func_800AAE94,
};

void (*D_80109D24[])(struct ShotObj*) = {
    func_800AB128,
    func_800AB170,
    func_800AB224,
};

void (*D_80109D30[])(struct ShotObj*) = {
    func_800AB384,
    func_800AB3A4,
};

void (*D_80109D38[])(struct ShotObj*) = {
    func_800AB518,
    func_800AB564,
    func_800AB5A4,
};

void (*D_80109D44[])(struct ShotObj*) = {
    func_800AB6C4,
    func_800AB710,
};

void (*D_80109D4C[])(struct ShotObj*) = {
    func_800AB7C0,
    func_800AB814,
};

void (*D_80109D54[])(struct ShotObj*) = {
    func_800AB8C0,
    func_800AB8EC,
};

void (*D_80109D5C[])(struct ShotObj*) = {
    func_800AAD44,
    func_800AAD64,
    func_800AAFF8,
    func_800AB050,
    func_800AB32C,
    func_800AB4C0,
    func_800AB66C,
    func_800AB98C,
    func_800AB868,
    func_800AB768,
};

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AAC98);

void func_800AAD44(struct ShotObj* arg0)
{
    func_8009216C(arg0);
}

void func_800AAD64(struct ShotObj* arg0)
{
}

void func_800AAD6C(struct ShotObj* arg0)
{
    s8 direction;

    arg0->unk8C.bytes[2] = arg0->unk7C->ext.raw[1];
    arg0->unk15 = 0;
    arg0->unk5C = 0x30;
    arg0->x_pos.i.hi = D_80109C44[arg0->unk8C.bytes[2]][arg0->unk2][0];
    arg0->y_pos.i.hi = D_80109C44[arg0->unk8C.bytes[2]][arg0->unk2][1];
    direction = func_8002B7B0(OBJECT_HEADER(arg0),
        D_80109CA4[arg0->unk8C.bytes[2]][arg0->unk2][0] << 16,
        D_80109CA4[arg0->unk8C.bytes[2]][arg0->unk2][1] << 16);
    arg0->unk8C.bytes[1] = direction;
    func_8002B93C(MOVING_OBJECT(arg0), direction & 0xFF);
    func_80015D60(arg0, 7);
    arg0->unk8C.byte = 1;
    arg0->unk68 = (struct Unk_unk68*)D_80109C38[2];
    arg0->x_vel.val *= 3;
    arg0->y_vel.val *= 3;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AAE94);

void func_800AAFF8(struct ShotObj* arg0)
{
    D_80109D1C[arg0->unk6](arg0);
    func_8002B318((struct BaseObj*)arg0, 0x80, 0x80);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB050);

void func_800AB128(struct ShotObj* arg0)
{
    func_80015D60(arg0, 8);
    arg0->timer = 0x3C;
    arg0->unk8A = 4;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB170);

void func_800AB224(struct ShotObj* arg0)
{
    struct WeaponObj* owner;
    struct ShotObj* shot;
    u32 i;

    owner = arg0->unk7C;
    arg0->timer--;
    if (arg0->timer == 0) {
        i = 0;
        do {
            func_8001540C(2, 3, arg0);
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x36;
                shot->unk2 = 0;
                shot->unk7 = i;
                shot->x_pos.val = arg0->x_pos.val;
                shot->y_pos.val = arg0->y_pos.val;
                shot->unk7C = owner;
            }
            i++;
        } while (i < 4);
        arg0->timer = 0x28;
        arg0->unk8A--;
        if (arg0->unk8A == 0) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            owner->ext.raw[2] = 1;
            return;
        }
        arg0->unk6--;
    }
}

void func_800AB32C(struct ShotObj* arg0)
{
    D_80109D24[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800AB384(struct ShotObj* arg0)
{
    arg0->timer = 1;
    arg0->unk8A = 6;
    arg0->unk6++;
}

void func_800AB3A4(struct ShotObj* arg0)
{
    s16 timer;
    s16 count;
    struct ShotObj* shot;
    struct MiscObj* misc;
    struct WeaponObj* owner;

    owner = arg0->unk7C;
    timer = (u16)arg0->timer - 1;
    arg0->timer = timer;
    if (timer == 0) {
        func_8001540C(2, 8, arg0);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x36;
            shot->unk2 = 1;
            shot->x_pos.val = arg0->x_pos.val;
            shot->y_pos.val = arg0->y_pos.val - FIXED(24);
            shot->unk7C = owner;
        }
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0x37;
            misc->unk2 = 3;
            misc->x_pos.val = arg0->x_pos.val;
            misc->y_pos.val = arg0->y_pos.val - FIXED(24);
            misc->ext.misc_55.owner = MAIN_OBJECT(shot);
        }
        arg0->timer = 0x1E;
        count = (u16)arg0->unk8A - 1;
        arg0->unk8A = count;
        if (count == 0) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            owner->ext.raw[2] = 1;
        }
    }
}

void func_800AB4C0(struct ShotObj* arg0)
{
    D_80109D30[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800AB518(struct ShotObj* arg0)
{
    func_80015D60(arg0, 9);
    arg0->timer = 1;
    arg0->x_vel.val = FIXED(-1);
    arg0->y_vel.val = 0;
    arg0->unk6++;
}

void func_800AB564(struct ShotObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6++;
    }
    func_80015DC8(arg0);
}

void func_800AB5A4(struct ShotObj* self)
{
    s16 timer;
    struct ShotObj* shot;
    struct WeaponObj* owner;

    owner = self->unk7C;
    timer = self->timer - 1;
    self->timer = timer;
    if (timer == 0) {
        func_8001540C(2, 7, self);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x36;
            shot->unk2 = 2;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            shot->unk7C = owner;
        }
        self->timer = 6;
    }
    func_8002B718(MOVING_OBJECT(self));
    if (self->x_pos.i.hi < 0x4D8) {
        self->unk5 = 3;
        self->unk6 = 0;
        owner->ext.raw[2] = 1;
    }
}

void func_800AB66C(struct ShotObj* arg0)
{
    D_80109D38[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800AB6C4(struct ShotObj* arg0)
{
    func_80015D60(arg0, 0xB);
    func_8001540C(2, 4, arg0);
    arg0->unk6++;
}

void func_800AB710(struct ShotObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }

    if (arg0->animation_step.fields.event == 1) {
        arg0->animation_step.fields.event = 0;
        arg0->unk50.data = (const u8*)D_80109C38[1];
    }

    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_800AB768(struct ShotObj* arg0)
{
    D_80109D44[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800AB7C0(struct ShotObj* arg0)
{
    func_80015D60(arg0, 9);
    arg0->x_vel.val = FIXED(2);
    arg0->y_vel.val = 0;
    arg0->unk28 = arg0->x_pos.val + FIXED(112);
    arg0->unk6++;
}

void func_800AB814(struct ShotObj* arg0)
{
    s32 limit;

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(arg0);
    limit = arg0->unk28;
    if (limit < arg0->x_pos.val) {
        arg0->x_pos.val = limit;
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_800AB868(struct ShotObj* arg0)
{
    D_80109D4C[arg0->unk6](arg0);
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
}

void func_800AB8C0(struct ShotObj* arg0)
{
    arg0->timer = 0x32;
    arg0->unk8A = 2;
    arg0->unk50.data = NULL;
    arg0->unk8C.byte = 1;
    arg0->unk6++;
}

void func_800AB8EC(struct ShotObj* self)
{
    s16 timer;
    s16 blink_timer;

    timer = self->timer - 1;
    self->timer = timer;
    if (timer == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
        self->unk68 = NULL;
        self->unk76 = 0;
        self->unk77 = 0;
        self->x_pos.i.hi = 0;
        self->y_pos.i.hi = 0;
        self->unk8C.byte = 0;
        self->unk15 = 0;
        return;
    }

    blink_timer = self->unk8A - 1;
    self->unk8A = blink_timer;
    if (blink_timer == 0) {
        self->unk8A = 2;
        self->unk8C.byte ^= 1;
    }
    if ((u8)self->unk8C.byte != 0) {
        func_8002B318(BASE_OBJECT(self), 0x50, 0x50);
    }
}

void func_800AB98C(struct ShotObj* arg0)
{
    D_80109D54[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/shots/shot_53", func_800AB9C8);

void func_800ABB50(struct ShotObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800ABB70(struct ShotObj* arg0)
{
    struct WeaponObj* temp_s1 = arg0->unk7C;
    if (temp_s1->unk94 == 2) {
        arg0->state = 2;
        arg0->unk5 = 0;
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi + 20, 0);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi + 20, 1);
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi - 20, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi - 20, -1);
    }
    if (temp_s1->unk94 == 1) {
        arg0->unk8C.byte = 0;
        arg0->state = 1;
        arg0->unk5 = 3;
        arg0->unk6 = 0;
        arg0->unk7 = 1;
        arg0->unk50.data = NULL;
        temp_s1->ext.weapon_6.direction = 0;
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi + 20, 0);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi + 20, 1);
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi + 0, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi + 15, arg0->y_pos.i.hi - 20, -1);
        func_800AFAB4(0, arg0->x_pos.i.hi - 15, arg0->y_pos.i.hi - 20, -1);
        arg0->x_pos.i.hi = 0;
        arg0->y_pos.i.hi = 0;
        arg0->unk5C = 0x30;
        return;
    }
    arg0->on_screen = 0;
    D_80109D84[arg0->state](arg0);
}

void (*D_80109D84[])(struct ShotObj*) = {
    func_800AAC98,
    func_800AB9C8,
    func_800ABB50,
};
