// MainObj, main_object_update_funcs[72]
// 8008ADFC..8008BA38
#include "common.h"
#include "func_tables.h"

void func_8008ADFC(struct MainObj* arg0)
{
    s32 x_pos;
    s32 y_pos;

    x_pos = arg0->x_pos.val;
    y_pos = arg0->y_pos.val;
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk5C = 0x18;
    arg0->unk60 = 6;
    arg0->animation_table = (const u8* const*)D_80104E7C;
    arg0->unk54 = (const u8*)&D_80104F00;
    arg0->unk50 = (const u8*)&D_80104F00;
    arg0->unk68 = &D_80104F04;
    arg0->collision_data = (const u16*)D_80108184;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->unk7C = 0;
    arg0->on_screen = 0;
    arg0->unk61 = 0;
    arg0->unk67 = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk16 = 5;
    arg0->unk18.val = x_pos;
    arg0->unk1C.val = y_pos;
}

void func_8008AE94(struct MainObj* arg0)
{
    if ((arg0->x_pos.val - g_Player.x_pos.val) < 0) {
        arg0->unk15 = 0x40;
        return;
    }

    arg0->unk15 = 0;
}

void func_8008AEC4(struct BaseObj* arg0, s8 arg1)
{
    arg0->unk5 = arg1;
    arg0->unk6 = 0;
}

void func_8008AED0(struct MainObj* arg0)
{
    arg0->x_pos.val += arg0->unk20;
}

void func_8008AEE8(struct MainObj* arg0)
{
    if (arg0->unk15 != 0) {
        arg0->unk20 = FIXED(1.375);
    } else {
        arg0->unk20 = FIXED(-1.375);
    }
}

void func_8008AF10(struct MainObj* arg0)
{
    s32 value;

    value = arg0->ext.main_72.unk84 << 8;
    if (arg0->unk15 == 0) {
        value = -value;
    }
    arg0->unk20 = value;
}

void func_8008AF30(struct MainObj* arg0, s32 arg1)
{
    s32 v;
    struct ShotObj* obj = find_free_shot_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x2F;
        obj->unk2 = arg1;
        obj->x_pos.i.hi = arg0->x_pos.i.hi;
        obj->y_pos.i.hi = arg0->y_pos.i.hi;
        obj->animation_table = arg0->animation_table;
        obj->unk40 = arg0->unk40;
        obj->unk3C = arg0->sprite_frames;
        v = (u8)func_8002938C(0x48);
        obj->unk42 = SOME_COORDINATE_CONVERSION(v);
        obj->unk16 = arg0->unk16;
        obj->unk7C = arg0;
        obj->unk15 = arg0->unk15;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B020);

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B188);

void func_8008B270(struct MainObj* arg0)
{
    s8 state;
    u8 timer1;
    u8 timer2;

    state = arg0->unk6;
    if (state == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 8);
        arg0->ext.main_72.lifetime = 0x40;
        arg0->ext.main_72.spawn_timer = 0x10;
        func_8008AE94(arg0);
        func_8001540C(2, 0x4C, arg0);
    }

    timer1 = arg0->ext.main_72.lifetime - 1;
    arg0->ext.main_72.lifetime = timer1;
    if (timer1 != 0) {
        timer2 = arg0->ext.main_72.spawn_timer - 1;
        arg0->ext.main_72.spawn_timer = timer2;
        if (timer2 == 0) {
            func_8008AF30(arg0, 0);
            arg0->ext.main_72.spawn_timer = 0x10;
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
    } else {
        func_8008AEC4(BASE_OBJECT(arg0), 2);
    }
}

void func_8008B33C(struct MainObj* self)
{
    s8 state;

    state = self->unk6;
    if (state == 0) {
        self->unk6 = state + 1;
        func_8008AE94(self);
        self->unk24 = FIXED(5.5);
        self->unk2C = FIXED(0.2578125);
        self->unk20 = 0;
        self->unk28 = 0;
        self->unk67 = 1;
        func_80015D60(self, 2);
        self->unk70 &= 0xF7;
        func_8001540C(2, 0x48, self);
    }
    self->unk20 = 0;
    func_8008AF10(self);
    if (!(self->unk70 & 4) && self->unk24 >= 0 && self->y_pos.i.hi - g_Player.y_pos.i.hi >= 0) {
        func_8002B694(ANIMATED_OBJECT(self));
        return;
    }
    func_8008AEC4(BASE_OBJECT(self), 2);
}

void func_8008B42C(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6++;
        arg0->unk67 = 0;
        func_80015D60(arg0, 4);
        arg0->unk70 |= 8;
        func_8001540C(2, 0x45, arg0);
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        func_8008AEC4(BASE_OBJECT(arg0), 7);
        return;
    }
    func_80015DC8(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B4B8);

void func_8008B5C0(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6 = 1;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk67 = 1;
        func_80015D60(arg0, 3);
    }
    if (arg0->unk70 & 8) {
        func_8008AEC4(BASE_OBJECT(arg0), 5);
        return;
    }
    if ((arg0->y_pos.i.hi - g_Player.y_pos.i.hi) >= -0x30) {
        func_8008AEC4(BASE_OBJECT(arg0), 2);
        return;
    }
    arg0->unk20 = 0;
    func_8008AF10(arg0);
    if (arg0->unk24 < FIXED(-5.875)) {
        arg0->unk24 = FIXED(-5.875);
    }
    func_8002B694(ANIMATED_OBJECT(arg0));
}

INCLUDE_ASM("main/nonmatchings/mains/main_72", func_8008B69C);

void func_8008B7D4(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        arg0->unk6++;
        func_80015D60(arg0, 9);
        arg0->ext.main_72.lifetime = 0x80;
        arg0->ext.main_72.spawn_timer = 0x30;
        func_8008AE94(arg0);
        func_8001540C(2, 0x4C, arg0);
    }

    if (--arg0->ext.main_72.lifetime != 0) {
        if ((--arg0->ext.main_72.spawn_timer & 0xF) != 0) {
            func_8008AF30(arg0, 1);
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
    } else {
        func_8008AEC4(BASE_OBJECT(arg0), 2);
    }
}

void func_8008B898(struct MainObj* arg0)
{
    func_8008AEC4(BASE_OBJECT(arg0), 2);
}

void func_8008B8B8(struct MainObj* self)
{
    s32 result;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    D_80104F10[self->unk5](self);
    CollisionRelated(PLAYER_OBJECT(self));
    func_8002D9BC(self);
    result = func_8002DD04(self);
    if (result < 0) {
        func_800C813C(7, D_80104F08, self);
        self->state = 2;
        self->unk5 = 0;
    } else if (result != 0) {
        func_80089B58(VISUAL_OBJECT(self), 8);
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state = 2;
    self->unk5 = 0;
}

void func_8008B984(struct MainObj* arg0)
{
    arg0->unk42 &= 0x7FFF;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8008B9B0(void)
{
}

void func_8008B9B8(void)
{
}

void func_8008B9C0(struct MainObj* arg0)
{
    D_80104F3C[arg0->unk5](arg0);
}

void func_8008B9FC(struct MainObj* arg0)
{
    D_80104F48[arg0->state](arg0);
}

struct Unk_unk68 D_80104D40[5] = {
    { 100, 0, 1, 0 },
    { 7, 0, 1, 11 },
    { 1, 1, 1, 12 },
    { 49, 0, 1, 12 },
    { 8, 0, -4, 11 },
};

struct Unk_unk68 D_80104D54[9] = {
    { 6, 0, 1, 0 },
    { 6, 0, 1, 1 },
    { 6, 1, 1, 2 },
    { 6, 0, 1, 3 },
    { 6, 0, 1, 4 },
    { 6, 0, 1, 5 },
    { 6, 0, 1, 6 },
    { 6, 0, 1, 7 },
    { 6, 0, -8, 8 },
};

union AnimationStep D_80104D78[] = {
    { 0x09000006 },
};

union AnimationStep D_80104D7C[] = {
    { 0x0A000006 },
};

union AnimationStep D_80104D80[] = {
    { 0x0B010002 },
    { 0x0C010008 },
    { 0x0B010007 },
    { 0x00000008 },
};

union AnimationStep D_80104D90[] = {
    { 0x0D010004 },
    { 0x0E000008 },
};

union AnimationStep D_80104D98[] = {
    { 0x0D000004 },
};

union AnimationStep D_80104D9C[] = {
    { 0x10010002 },
    { 0x20010003 },
    { 0x11010001 },
    { 0x1D010001 },
    { 0x12010001 },
    { 0x1E010001 },
    { 0x1F010001 },
    { 0x20000013 },
};

struct Unk_unk68 D_80104DBC[4] = {
    { 1, 0, 1, 21 },
    { 1, 0, 1, 22 },
    { 1, 0, 1, 23 },
    { 1, 0, -3, 24 },
};

struct Unk_unk68 D_80104DCC[4] = {
    { 1, 0, 1, 25 },
    { 1, 0, 1, 26 },
    { 1, 0, 1, 27 },
    { 1, 0, -3, 28 },
};

union AnimationStep D_80104DDC[] = {
    { 0x0F000001 },
};

union AnimationStep D_80104DE0[] = {
    { 0x25010005 },
    { 0x26010008 },
    { 0x25000006 },
};

union AnimationStep D_80104DEC[] = {
    { 0x27010005 },
    { 0x28010005 },
    { 0x29010005 },
    { 0x2A010005 },
    { 0x2B010005 },
    { 0x2C010005 },
    { 0x2D010005 },
    { 0x2E010005 },
    { 0x2F000005 },
};

struct Unk_unk68 D_80104E10[12] = {
    { 2, 0, 1, 48 },
    { 2, 0, 1, 49 },
    { 2, 0, 1, 50 },
    { 2, 0, 1, 51 },
    { 2, 0, 1, 52 },
    { 2, 0, 1, 53 },
    { 1, 0, 1, 48 },
    { 1, 0, 1, 49 },
    { 1, 0, 1, 50 },
    { 1, 0, 1, 51 },
    { 1, 0, 1, 52 },
    { 1, 0, -11, 53 },
};

union AnimationStep D_80104E40[] = {
    { 0x36000002 },
};

union AnimationStep D_80104E44[] = {
    { 0x37000002 },
};

union AnimationStep D_80104E48[] = {
    { 0x38000002 },
};

union AnimationStep D_80104E4C[] = {
    { 0x39000002 },
};

union AnimationStep D_80104E50[] = {
    { 0x3A000002 },
};

union AnimationStep D_80104E54[] = {
    { 0x3B000002 },
};

union AnimationStep D_80104E58[] = {
    { 0x3C000002 },
};

struct Unk_unk68 D_80104E5C[4] = {
    { 2, 0, 1, 61 },
    { 2, 0, 1, 62 },
    { 2, 0, 1, 63 },
    { 2, 0, -3, 64 },
};

struct Unk_unk68 D_80104E6C[4] = {
    { 2, 0, 1, 65 },
    { 2, 0, 1, 66 },
    { 2, 0, 1, 67 },
    { 2, 0, -3, 68 },
};

void* D_80104E7C[33] = {
    D_80104D40,
    D_80104D54,
    D_80104D78,
    D_80104D7C,
    D_80104D80,
    D_80104D90,
    D_80104D98,
    D_80104D9C,
    D_80104DBC,
    D_80104DCC,
    D_80104DDC,
    D_80104DE0,
    D_80104E5C,
    D_80104E6C,
    D_80104E10,
    D_80104DEC,
    D_80104E10,
    D_80104DEC,
    D_80104E10,
    D_80104DEC,
    D_80104DEC,
    D_80104E10,
    D_80104E10,
    D_80104E10,
    D_80104E40,
    D_80104E44,
    D_80104E48,
    D_80104E4C,
    D_80104E50,
    D_80104E54,
    D_80104E58,
    D_80104E5C,
    D_80104E6C,
};

struct Unk_unk68 D_80104F00 = { -14, -18, 28, 52 };

struct Unk_unk68 D_80104F04 = { 0, -1, 15, 33 };

struct Unk_unk68 D_80104F08[2] = {
    { 24, 25, 26, 27 },
    { 28, 29, 30, 0 },
};

void (*D_80104F10[11])(struct MainObj*) = {
    func_8009216C,
    func_8008B898,
    func_8008B020,
    func_8008B188,
    func_8008B5C0,
    func_8008B42C,
    func_8008B4B8,
    func_8008B33C,
    func_8008B270,
    func_8008B69C,
    func_8008B7D4,
};

void (*D_80104F3C[3])() = {
    func_8008B984,
    func_8008B9B0,
    func_8008B9B8,
};

void (*D_80104F48[3])() = {
    func_8008ADFC,
    func_8008B8B8,
    func_8008B9C0,
};
