// MainObj, main_object_update_funcs[24]
// 80056788..80057100
#include "common.h"
#include "func_tables.h"

extern u8 D_800FCFA0[];

void func_80056788(struct MainObj* arg0)
{
    D_800FCFA8[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_24", func_800567C4);

void func_80056AC4(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    D_800FCFB4[self->unk5](self);

    if (self->unk5 != 3) {
        func_8002D9BC(self);
        self->ext.main_24.saved_unk5 = self->unk5;

        if (func_8002DD04(self) < 0) {
            func_800AF808(self);
            func_800C813C(5, D_800FCFA0, self);
            func_800BF60C(BASE_OBJECT(self), 0xC);
        } else if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
            func_8002B318(BASE_OBJECT(self), 0x20, 0x20);
            return;
        }

        self->state = 2;
    }
}

void func_80056BA8(struct MainObj* arg0)
{
    arg0->unk7A = 0;
    arg0->ext.main_24.unk80 = 0;
    arg0->ext.main_24.saved_unk5 = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80056BD0(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_24.saved_unk5;
}

void func_80056BDC(struct MainObj* arg0)
{
    D_800FCFC4[arg0->unk6](arg0);
}

void func_80056C18(struct MainObj* arg0)
{
    struct MiscObj* trail;
    u8 facing;

    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (!(++arg0->ext.main_24.unk80 & 3)) {
        trail = find_free_misc_obj();
        if (trail != NULL) {
            trail->active = 0x41;
            trail->id = 7;
            trail->unk2 = 0;
            trail->unk40 = arg0->unk40;
            trail->unk42 = arg0->unk42 & 0x7FFF;
            trail->animation_table = (u32**)arg0->animation_table;
            trail->unk3C = (void*)arg0->sprite_frames;
            trail->bg_offset = arg0->bg_offset;
            trail->x_pos.val = arg0->x_pos.val;
            trail->y_pos.val = arg0->y_pos.val;
            facing = arg0->unk15;
            trail->ext.misc_7.position = &arg0->x_pos;
            trail->state = 0;
            trail->unk15 = facing;
        }
    }
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 1);
        arg0->unk6 = 1;
    }
}

void func_80056D20(struct MainObj* arg0)
{
    s32 direction;

    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 == 0) {
        direction = arg0->unk2 & 3;
        arg0->unk2C = (direction < 2) ? FIXED(0.1875) : FIXED(-0.1875);
    }
    if (arg0->unk20 == 0) {
        arg0->unk7C = 0xA;
        arg0->unk28 >>= 2;
        func_80015D60(arg0, 2);
        arg0->unk6 = 2;
    }
}

void func_80056DB4(struct MainObj* arg0)
{
    struct MiscObj* trail;
    u8 facing;

    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (!(++arg0->ext.main_24.unk80 & 3)) {
        trail = find_free_misc_obj();
        if (trail != NULL) {
            trail->active = 0x41;
            trail->id = 7;
            trail->unk2 = 1;
            trail->unk40 = arg0->unk40;
            trail->unk42 = arg0->unk42 & 0x7FFF;
            trail->animation_table = (u32**)arg0->animation_table;
            trail->unk3C = (void*)arg0->sprite_frames;
            trail->bg_offset = arg0->bg_offset;
            trail->x_pos.val = arg0->x_pos.val;
            trail->y_pos.val = arg0->y_pos.val;
            facing = arg0->unk15;
            trail->ext.misc_7.position = &arg0->x_pos;
            trail->state = 0;
            trail->unk15 = facing ^ 0x40;
        }
    }
    if (--arg0->unk7C == 0) {
        arg0->unk2C = 0;
        if ((arg0->unk2 & 3) < 2) {
            arg0->unk24 = FIXED(-2);
        } else {
            arg0->unk24 = FIXED(2);
        }
        arg0->unk7C = 1;
        arg0->unk7E = 8;
        arg0->unk6 = 3;
    }
}

void func_80056EF4(struct MainObj* arg0)
{
    struct MiscObj* trail;
    struct ShotObj* shot;
    u8 facing;

    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (!(++arg0->ext.main_24.unk80 & 3)) {
        trail = find_free_misc_obj();
        if (trail != NULL) {
            trail->active = 0x41;
            trail->id = 7;
            trail->unk2 = 1;
            trail->unk40 = arg0->unk40;
            trail->unk42 = arg0->unk42 & 0x7FFF;
            trail->animation_table = (u32**)arg0->animation_table;
            trail->unk3C = (void*)arg0->sprite_frames;
            trail->bg_offset = arg0->bg_offset;
            trail->x_pos.val = arg0->x_pos.val;
            trail->y_pos.val = arg0->y_pos.val;
            facing = arg0->unk15;
            trail->ext.misc_7.position = &arg0->x_pos;
            trail->state = 0;
            trail->unk15 = facing ^ 0x40;
        }
    }
    if (--arg0->unk7E == 0) {
        func_80015D60(arg0, 9);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0xD;
            shot->unk2 = 0;
            shot->unk40 = arg0->unk40;
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)arg0->animation_table;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->bg_offset = arg0->bg_offset;
            shot->x_pos.val = arg0->x_pos.val;
            shot->y_pos.val = arg0->y_pos.val;
            shot->unk15 = arg0->unk15;
            shot->state = 0;
        }
        if (--arg0->unk7C == 0) {
            arg0->unk7E = 0x7FFF;
        } else {
            arg0->unk7E = 8;
        }
    }
}

void func_800570A4(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi >= 0xA1) {
        func_8001540C(2, 0x50, arg0);
        arg0->unk7A = 0;
        arg0->unk5 = 2;
    }
}

struct Unk_unk68 D_800FCED4[] = {
    { -11, -12, 22, 22 },
};

struct Unk_unk68 D_800FCED8[] = {
    { -8, -11, 16, 20 },
};

union AnimationStep D_800FCEDC[] = {
    { 0x00010006 },
    { 0x07010005 },
    { 0x06010004 },
    { 0x05010005 },
    { 0x04010006 },
    { 0x03010005 },
    { 0x02010004 },
    { 0x01010005 },
    { 0x00F90106 },
};

union AnimationStep D_800FCF00[] = {
    { 0x0C010003 },
    { 0x0D010005 },
    { 0x08010003 },
    { 0x09010004 },
    { 0x0A010005 },
    { 0x0B000101 },
};

union AnimationStep D_800FCF18[] = {
    { 0x0B000101 },
};

union AnimationStep D_800FCF1C[] = {
    { 0x11010002 },
    { 0x15010002 },
    { 0x13010002 },
    { 0x15010002 },
    { 0x14010002 },
    { 0x12010002 },
    { 0x16010002 },
    { 0x15F90002 },
};

union AnimationStep D_800FCF3C[] = {
    { 0x17000101 },
};

union AnimationStep D_800FCF40[] = {
    { 0x18000101 },
};

union AnimationStep D_800FCF44[] = {
    { 0x19000101 },
};

union AnimationStep D_800FCF48[] = {
    { 0x1A000101 },
};

union AnimationStep D_800FCF4C[] = {
    { 0x1B000101 },
};

union AnimationStep D_800FCF50[] = {
    { 0x0E010004 },
    { 0x0F010005 },
    { 0x0E010004 },
    { 0x0B000101 },
};

union AnimationStep D_800FCF60[] = {
    { 0x10010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1E000101 },
};

union AnimationStep* D_800FCF74[] = {
    D_800FCEDC,
    D_800FCF00,
    D_800FCF18,
    D_800FCF1C,
    D_800FCF3C,
    D_800FCF40,
    D_800FCF44,
    D_800FCF48,
    D_800FCF4C,
    D_800FCF50,
    D_800FCF60,
};

u8 D_800FCFA0[] = {
    0x04,
    0x05,
    0x06,
    0x07,
    0x08,
    0x00,
    0x00,
    0x00,
};

void (*D_800FCFA8[])(struct MainObj*) = {
    func_800567C4,
    func_80056AC4,
    func_80056BA8,
};

void (*D_800FCFB4[])(struct MainObj*) = {
    (void (*)(struct MainObj*))func_8009216C,
    func_80056BD0,
    func_80056BDC,
    func_800570A4,
};

void (*D_800FCFC4[])() = {
    func_80056C18,
    func_80056D20,
    func_80056DB4,
    func_80056EF4,
};
