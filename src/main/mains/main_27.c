// MainObj, main_object_update_funcs[27]
// 800586F0..80059C48
#include "common.h"
#include "func_tables.h"

void func_800586F0(struct MainObj* arg0)
{
    D_800FD38C[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80058740);

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80058AC8);

void func_80058D50(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->state = 3;
    } else if (--arg0->unk7E == 0) {
        arg0->unk7E = 6;
        func_800AF878(arg0, 1, 16, 16);
    }
}

void func_80058DBC(struct MainObj* arg0)
{
    arg0->unk7A = 0;
    arg0->ext.raw[0] = 0;
    arg0->ext.raw[1] = 0;
    arg0->ext.raw[2] = 0;
    arg0->ext.raw[3] = 0;
    arg0->ext.raw[5] = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80058DF0(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_27.saved_unk5;
}

void func_80058DFC(struct MainObj* arg0)
{
    D_800FD3BC[arg0->unk6](arg0);
}

void func_80058E38(struct MainObj* arg0)
{
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->ext.main_27.unk8C == 0) {
        func_80015D60(arg0, 3);
        arg0->unk20 = 0;
        func_80015930(2, 0x51);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        return;
    }
    if (arg0->ext.main_27.unk90 != 0 && --arg0->ext.main_27.unk91 == 0) {
        if (arg0->ext.main_27.unk90 == 2) {
            arg0->ext.main_27.unk91 = 0x30;
            if (--arg0->ext.main_27.unk92 == 0) {
                arg0->ext.main_27.unk92 = 2;
                func_80015D60(arg0, 3);
                arg0->unk20 = 0;
                func_80015930(2, 0x51);
                arg0->unk5 = 5;
                arg0->unk6 = 0;
                return;
            }
        } else {
            arg0->ext.main_27.unk91 = 0x60;
        }
        arg0->unk7C = 0x14;
        arg0->unk24 = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
    }
    if (arg0->unk15 == 0 ? (arg0->unk70 & 2) : (arg0->unk70 & 1)) {
        arg0->unk7C = 0x14;
        arg0->unk24 = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
    }
}

void func_80058F94(struct MainObj* arg0)
{
    s8 next_state;

    if ((g_Player.x_pos.i.hi - arg0->x_pos.i.hi) >= 0xBD) {
        func_8001540C(2, 0x51, arg0);
        arg0->unk7A = 0;
        if (arg0->ext.main_27.unk80 == 0) {
            next_state = 2;
        } else {
            arg0->unk7C = 1;
            next_state = 7;
        }
        arg0->unk5 = next_state;
        arg0->unk6 = 0;
    }
}

void func_80059010(struct MainObj* arg0)
{
    D_800FD3C0[arg0->unk6](arg0);
}

void func_8005904C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk20 == 0) {
        arg0->unk28 = 0;
    }
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 2);
        arg0->unk6 = 1;
    }
}

void func_800590BC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->unk15 ^= 0x40;
        func_80015D60(arg0, 1);
        arg0->unk7C = 0x14;
        if (arg0->ext.main_27.unk8A == 0) {
            arg0->unk6 = 2;
        } else {
            if (arg0->unk15 == 0) {
                arg0->unk20 = FIXED(-4);
            } else {
                arg0->unk20 = FIXED(4);
            }
            func_80015D60(arg0, 7);
            arg0->unk5 = 7;
            arg0->unk6 = 1;
        }
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80059154);

void func_800591F0(struct MainObj* arg0)
{
    D_800FD3CC[arg0->unk6](arg0);
}

void func_8005922C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->ext.main_27.unk8B = 1;
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk7C = 4;
        arg0->unk7E = 0x1E;
        arg0->unk6 = 1;
    }
}

void func_80059290(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7E == 0) {
        if (arg0->unk15 == 0) {
            arg0->x_pos.u.hi -= 6;
        } else {
            arg0->x_pos.u.hi += 6;
        }
        arg0->ext.main_27.collision_direction = func_8002B7DC(OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));
        if (arg0->unk15 == 0) {
            arg0->x_pos.u.hi += 6;
        } else {
            arg0->x_pos.u.hi -= 6;
        }
        arg0->unk6 = 2;
    }
}

void func_80059344(struct MainObj* arg0)
{
    struct ShotObj* shot;
    u8 direction;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    direction = arg0->ext.main_27.collision_direction;
    if ((u32)(direction - 9) < 0xF) {
        if (arg0->unk15 != 0) {
            arg0->unk7C = 0xA;
            arg0->unk6 = 3;
        }
    } else if ((u32)(direction - 8) >= 0x11 && arg0->unk15 == 0) {
        arg0->unk7C = 0xA;
        arg0->unk6 = 3;
    }
    if (arg0->unk6 == 3) {
        return;
    }
    func_80015D60(arg0, 4);
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0xE;
        shot->unk2 = arg0->unk2;
        shot->unk40 = arg0->unk40;
        shot->unk42 = arg0->unk42;
        shot->animation_table = (u32**)arg0->animation_table;
        shot->unk3C = (void*)arg0->sprite_frames;
        shot->unk15 = arg0->unk15;
        shot->bg_offset = arg0->bg_offset;
        shot->x_pos.val = arg0->x_pos.val;
        shot->y_pos.val = arg0->y_pos.val;
        func_8002B93C(MOVING_OBJECT(shot), arg0->ext.main_27.collision_direction);
        shot->state = 0;
        shot->x_vel.val *= 3;
        shot->y_vel.val *= 3;
    }
    if (--arg0->unk7C == 0) {
        arg0->unk7C = 0xA;
        arg0->unk6 = 3;
    } else {
        arg0->unk7E = 0x14;
        arg0->unk6 = 1;
    }
}

void func_800594D8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 6);
        arg0->unk6 = 4;
    }
}

void func_8005952C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->ext.main_27.unk8B = 0;
    }
    if (arg0->animation_step.fields.event == 1) {
        func_80015D60(arg0, 1);
        arg0->unk7C = 10;
        arg0->unk6 = 5;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80059590);

INCLUDE_ASM("main/nonmatchings/mains/main_27", func_80059640);

void func_80059978(struct MainObj* arg0)
{
    D_800FD3E4[arg0->unk6](arg0);
}

void func_800599B4(struct MainObj* self)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(self));
    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;
    if (timer != 0) {
        return;
    }

    self->ext.main_27.unk8A = 1;
    if (self->unk15 == 0) {
        if (g_Player.x_pos.i.hi > self->x_pos.i.hi) {
            goto action;
        }
        goto common;
    }
    if (g_Player.x_pos.i.hi < self->x_pos.i.hi) {
        goto action;
    }
    goto common;

action:
    func_80015D60(self, 2);
    self->unk5 = 4;
    self->unk6 = 1;
    self->unk7C = 1;
    return;

common:
    self->unk7C = 0x14;
    self->unk6 = 1;
    if (self->unk15 == 0) {
        self->unk20 = FIXED(-4);
    } else {
        self->unk20 = FIXED(4);
    }
}

void func_80059A94(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    if (arg0->ext.main_27.unk8C != 1) {
        arg0->ext.main_27.unk8C--;
    }
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 1);
        arg0->unk28 = FIXED(-0.125);
        arg0->unk6 = 2;
    }
}

void func_80059B0C(struct MainObj* arg0)
{
    if (arg0->ext.main_27.unk8C != 1) {
        arg0->ext.main_27.unk8C--;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (arg0->unk20 == 0) {
        arg0->unk7C = 10;
        arg0->unk28 = 0;
        arg0->unk20 = 0;
        arg0->ext.main_27.unk88 = 0;
        arg0->unk6 = 3;
    }
}

void func_80059B7C(struct MainObj* arg0)
{
    s16 timer;

    if (arg0->ext.main_27.unk8C != 1) {
        arg0->ext.main_27.unk8C--;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->ext.main_27.unk89 = 0;
        arg0->ext.main_27.unk8A = 0;
        if (arg0->unk15 == 0) {
            if (g_Player.x_pos.i.hi > arg0->x_pos.i.hi) {
                timer = 0x14;
                arg0->unk7C = timer;
                timer = 4;
                arg0->unk28 = 0;
                arg0->unk24 = 0;
            } else {
                timer = 6;
            }
        } else if (g_Player.x_pos.i.hi < arg0->x_pos.i.hi) {
            timer = 0x14;
            arg0->unk7C = timer;
            timer = 4;
            arg0->unk28 = 0;
            arg0->unk24 = 0;
        } else {
            timer = 6;
        }
        arg0->unk5 = timer;
        arg0->unk6 = 0;
    }
}

struct Unk_unk68 D_800FD200[10] = {
    { -17, -16, 10, 34 },
    { -21, -26, 42, 16 },
    { -8, -2, 33, 6 },
    { -8, -7, 34, 16 },
    { 0, 7, 25, 23 },
    { -24, -27, 17, 54 },
    { -42, -33, 80, 17 },
    { -15, -2, 39, 6 },
    { -15, -7, 40, 16 },
    { 0, 7, 32, 39 },
};

union AnimationStep D_800FD228[] = {
    { 0x00010003 },
    { 0x01010003 },
    { 0x02010003 },
    { 0x03FD0003 },
};

union AnimationStep D_800FD238[] = {
    { 0x04010003 },
    { 0x05010003 },
    { 0x06010003 },
    { 0x07010003 },
    { 0x08010003 },
    { 0x09010003 },
    { 0x0A010003 },
    { 0x0BF90103 },
};

union AnimationStep D_800FD258[] = {
    { 0x0C010002 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010001 },
    { 0x11000101 },
};

union AnimationStep D_800FD274[] = {
    { 0x12010002 },
    { 0x13010006 },
    { 0x14010003 },
    { 0x15010003 },
    { 0x16010004 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010202 },
    { 0x1A010002 },
    { 0x19010002 },
    { 0x1A010009 },
    { 0x1A000101 },
};

union AnimationStep D_800FD2A4[] = {
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1A000101 },
};

union AnimationStep D_800FD2B8[] = {
    { 0x1F010003 },
    { 0x20010003 },
    { 0x21010003 },
    { 0x22010003 },
    { 0x23010003 },
    { 0x24FB0003 },
};

union AnimationStep D_800FD2D0[] = {
    { 0x1A010006 },
    { 0x17010002 },
    { 0x16010202 },
    { 0x25010002 },
    { 0x16010004 },
    { 0x15010003 },
    { 0x14010003 },
    { 0x13010006 },
    { 0x12010002 },
    { 0x26010002 },
    { 0x27010001 },
    { 0x27000101 },
};

union AnimationStep D_800FD300[] = {
    { 0x26010002 },
    { 0x27010002 },
    { 0x28010002 },
    { 0x29010001 },
    { 0x2A010001 },
    { 0x2B010002 },
    { 0x2C010002 },
    { 0x2D010001 },
    { 0x2E010001 },
    { 0x2F010002 },
    { 0x30010002 },
    { 0x31010001 },
    { 0x32010001 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010001 },
    { 0x36010002 },
    { 0x37F10002 },
};

union AnimationStep D_800FD348[] = {
    { 0x38000101 },
};

union AnimationStep D_800FD34C[] = {
    { 0x39000101 },
};

union AnimationStep D_800FD350[] = {
    { 0x3A000101 },
};

union AnimationStep D_800FD354[] = {
    { 0x3B000101 },
};

union AnimationStep* D_800FD358[] = {
    D_800FD228,
    D_800FD238,
    D_800FD258,
    D_800FD274,
    D_800FD2A4,
    D_800FD2B8,
    D_800FD2D0,
    D_800FD300,
    D_800FD348,
    D_800FD34C,
    D_800FD350,
    D_800FD354,
};

u8 D_800FD388[] = {
    0x08,
    0x09,
    0x0A,
    0x0B,
};

void (*D_800FD38C[])() = {
    func_80058740,
    func_80058AC8,
    func_80058D50,
    func_80058DBC,
};

void (*D_800FD39C[])() = {
    func_8009216C,
    func_80058DF0,
    func_80058DFC,
    func_80058F94,
    func_80059010,
    func_800591F0,
    func_80059640,
    func_80059978,
};

void (*D_800FD3BC[])() = {
    func_80058E38,
};

void (*D_800FD3C0[])(struct MainObj*) = {
    func_8005904C,
    func_800590BC,
    func_80059154,
};

void (*D_800FD3CC[])(struct MainObj*) = {
    func_8005922C,
    func_80059290,
    func_80059344,
    func_800594D8,
    func_8005952C,
    func_80059590,
};

void (*D_800FD3E4[])() = {
    func_800599B4,
    func_80059A94,
    func_80059B0C,
    func_80059B7C,
};
