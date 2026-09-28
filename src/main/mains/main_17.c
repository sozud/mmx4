// MainObj, main_object_update_funcs[17]
// 8004FF90..80050708
#include "common.h"
#include "func_tables.h"

void func_8004FF90(struct MainObj* arg0)
{
    D_800FBEB4[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

void func_8004FFE0(struct MainObj* arg0)
{
    arg0->unk5C = 6;
    arg0->unk60 = 2;
    arg0->unk61 = 0;
    arg0->collision_data = D_80106AF4;
    arg0->bg_offset = (u8)g_Player.bg_offset;
    arg0->unk16 = 6;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->animation_table = (const u8* const*)D_800FBE94;
    arg0->unk68 = &D_800FBE08;
    arg0->unk54 = &D_800FBE00;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk67 = 0;
    arg0->unk50 = &D_800FBE04;
    func_800506D8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 0);
    arg0->ext.main_17.unk80 = 4;
    arg0->ext.main_17.unk84 = 3;
    arg0->ext.main_17.unk88 = 0xC;
    arg0->ext.main_17.unk8C = 0;
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
    arg0->ext.main_17.saved_unk5 = arg0->y_pos.val;
}

void func_800500D4(struct MainObj* arg0)
{
    s32 collision;

    func_80050690(arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_800FBEC0[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    arg0->ext.main_17.unk90 = arg0->unk5;
    collision = func_8002DD04(arg0);
    if (func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi + arg0->unk68->unk0,
            arg0->unk68->unk3 + (arg0->y_pos.i.hi + arg0->unk68->unk1))
        == 0x3E) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_800FBEB0, arg0);
    } else if (collision < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_800FBEB0, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0);
    } else if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x20, 0x20);
        return;
    }
    arg0->state = 2;
}

void func_80050238(struct MainObj* arg0)
{
    arg0->ext.main_17.unk80 = 0;
    arg0->ext.main_17.unk84 = 0;
    arg0->ext.main_17.unk88 = 0;
    arg0->ext.main_17.unk8C = 0;
    arg0->ext.main_17.unk90 = 0;
    arg0->ext.main_17.saved_unk5 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8005026C(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.raw[4];
}

INCLUDE_ASM("main/nonmatchings/mains/main_17", func_80050278);

void func_80050418(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_800506D8(ANIMATED_OBJECT(arg0));
        arg0->unk5 = 2;
        arg0->ext.main_17.unk80 = 4;
        arg0->unk6 = 0;
        arg0->ext.main_17.unk84 = 3;
        func_80015D60(arg0, 0);
    }
}

void func_80050480(struct MainObj* arg0)
{
    if (arg0->unk20 != 0) {
        func_8002B694(ANIMATED_OBJECT(arg0));
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 2) {
        arg0->unk68 = &D_800FBE14;
        arg0->unk54 = &D_800FBE0C;
        arg0->unk50 = &D_800FBE10;
    }
    if (arg0->animation_step.fields.event == 1) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_800FBEB0, arg0);
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        func_80015D60(arg0, 0);
    }
}

void func_80050540(struct MainObj* self)
{
    s32 distance;
    s32 target_y;
    s32 current_y;

    if (self->unk70 & 8) {
        if (self->ext.main_17.unk8C != 0) {
            self->unk5 = 4;
            self->unk6 = 0;
            self->unk67 = 0;
        } else {
            func_80015D60(self, 0);
            target_y = self->ext.main_17.saved_unk5;
            current_y = self->y_pos.val;
            distance = target_y - current_y;
            self->unk5 = 2;
            self->unk6 = 0;
            self->unk24 = 0;
            self->unk2C = 0;
            self->unk20 = 0;
            self->unk28 = 0;
            self->unk67 = 0;
            if (distance >= 0 ? distance > 0x7FFFF : current_y - target_y > 0x7FFFF) {
                self->ext.main_17.unk80 = 4;
                self->ext.main_17.unk84 = 3;
                self->ext.main_17.unk88 = 0xC;
            }
        }
    } else {
        func_8002B694(ANIMATED_OBJECT(self));
        if (self->unk20 == 0) {
            self->unk28 = 0;
        }
    }
    func_80015DC8(ANIMATED_OBJECT(self));
}

void func_80050644(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->ext.main_17.unk80 = 4;
        func_80015D60(arg0, 0);
    }
}

void func_80050690(struct MainObj* arg0)
{
    if (arg0->unk67 == 0 && !(arg0->unk70 & 8)) {
        arg0->unk5 = 5;
        arg0->unk2C = 0x4200;
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk67 = 1;
    }
}

void func_800506D8(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

struct Unk_unk68 D_800FBE00 = { -8, -13, 15, 26 };

struct Unk_unk68 D_800FBE04 = { -7, -11, 12, 22 };

struct Unk_unk68 D_800FBE08 = { 0, 0, 5, 13 };

struct Unk_unk68 D_800FBE0C = { -12, -1, 25, 13 };

struct Unk_unk68 D_800FBE10 = { -10, 1, 21, 10 };

struct Unk_unk68 D_800FBE14 = { 0, 5, 13, 8 };

union AnimationStep D_800FBE18[] = {
    { 0x00010008 },
    { 0x03010003 },
    { 0x04010004 },
    { 0x05010006 },
    { 0x04010004 },
    { 0x03010002 },
    { 0x03000101 },
};

union AnimationStep D_800FBE34[] = {
    { 0x0001000C },
    { 0x01010006 },
    { 0x0201000C },
    { 0x01010006 },
    { 0x0001000C },
    { 0x01010006 },
    { 0x0201000C },
    { 0x01010006 },
    { 0x0001000B },
    { 0x0000010C },
};

union AnimationStep D_800FBE5C[] = {
    { 0x06010005 },
    { 0x07010004 },
    { 0x08010004 },
    { 0x07010204 },
    { 0x0901003C },
    { 0x0A010002 },
    { 0x09010002 },
    { 0x0A010002 },
    { 0x0901001D },
    { 0x09000101 },
};

union AnimationStep D_800FBE84[] = {
    { 0x0B000101 },
};

union AnimationStep D_800FBE88[] = {
    { 0x0C000101 },
};

union AnimationStep D_800FBE8C[] = {
    { 0x0D000101 },
};

union AnimationStep D_800FBE90[] = {
    { 0x0E000101 },
};

union AnimationStep* D_800FBE94[7] = {
    D_800FBE18,
    D_800FBE34,
    D_800FBE5C,
    D_800FBE84,
    D_800FBE88,
    D_800FBE8C,
    D_800FBE90,
};

u8 D_800FBEB0[4] = { 3, 4, 5, 6 };

void (*D_800FBEB4[3])() = {
    func_8004FFE0,
    func_800500D4,
    func_80050238,
};

void (*D_800FBEC0[7])(struct MainObj*) = {
    func_8009216C,
    func_8005026C,
    func_80050278,
    func_80050418,
    func_80050480,
    func_80050540,
    func_80050644,
};
