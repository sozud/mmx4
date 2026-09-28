// MainObj, main_object_update_funcs[15]
// 8004D930..8004E890
#include "common.h"
#include "func_tables.h"

void func_8004D930(struct MainObj* arg0)
{
    if (!(func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi,
              arg0->y_pos.i.hi)
            & 0xFF)) {
        arg0->state = 1;
        arg0->unk5 = 1;
        arg0->unk2 = 0;
        arg0->unk54 = &D_800FBA50;
        arg0->unk50 = &D_800FBA50;
    }

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) == 0) {
        if (arg0->unk2 == 2) {
            func_8002B318(BASE_OBJECT(arg0), 0x25, 0x25);
        }
    } else {
        arg0->state = 2;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004D9CC);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004DB10);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004DCB0);

void func_8004DEA0(struct MainObj* arg0)
{
    s8 state;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    state = arg0->unk6;
    if (state == 0) {
        if (arg0->animation_step.fields.event != 0) {
            arg0->unk6 = state + 1;
        }
    } else {
        func_8002B694(ANIMATED_OBJECT(arg0));
        if (arg0->unk24 < 0) {
            arg0->unk6++;
            func_80015D60(arg0, 3);
            arg0->unk5 = 2;
            arg0->unk2C = FIXED(0.2578125);
            arg0->unk6 = 0;
            arg0->unk24 = 0;
            arg0->unk28 = 0;
            arg0->unk67 = -1;
        }
    }
}

void func_8004DF40(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk6 == 0) {
        arg0->collision_data = (const u16*)D_801069F4;
        func_8002B694(ANIMATED_OBJECT(arg0));
        if (arg0->unk70 & 8) {
            func_80015D60(arg0, 4);
            arg0->unk24 = 0;
            arg0->unk2C = 0;
            arg0->unk20 = 0;
            arg0->unk28 = 0;
            arg0->unk6++;
        }
    } else if (arg0->animation_step.fields.relative_step == 0) {
        func_80015D60(arg0, 1);
        arg0->unk5 = 1;
        arg0->unk6 = 0;
        arg0->unk67 = 0;
    }
}

void func_8004DFEC(struct MainObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        arg0->unk6++;
        func_80015D60(arg0, 5);
        arg0->unk7C = 0x3C;
    case 1:
        if (arg0->animation_step.fields.event != 0) {
            arg0->collision_data = D_801060F0;
            arg0->unk54 = &D_800FBA54;
            arg0->unk50 = &D_800FBA54;
        }
        if (--arg0->unk7C == 0) {
            arg0->unk6++;
            func_80015D60(arg0, 6);
        }
        break;
    case 2:
        if (arg0->animation_step.fields.relative_step == 0) {
            func_80015D60(arg0, 1);
            arg0->unk5 = 1;
            arg0->collision_data = D_801069F4;
            arg0->unk54 = &D_800FBA50;
            arg0->unk50 = &D_800FBA50;
            arg0->unk6 = 0;
            arg0->ext.main_0.flags[0] = 0x78;
            arg0->ext.main_0.background_relative &= 0xFE;
        }
        break;
    }
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8004E128(struct MainObj* arg0)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->animation_step.fields.event = 0;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 8;
            shot->x_pos.val = arg0->x_pos.val;
            shot->y_pos.val = arg0->y_pos.val;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->unk40 = arg0->unk40;
            shot->unk42 = arg0->unk42;
            shot->bg_offset = (u8)arg0->bg_offset;
            shot->animation_table = (u32**)arg0->animation_table;
            shot->unk15 = arg0->unk15;
        }
    }
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk5 = 1;
        arg0->unk6 = 0;
        func_80015D60(arg0, 1);
        arg0->ext.main_0.flags[1] = 0x78;
        arg0->ext.main_0.background_relative &= 0xFD;
    }
}

void func_8004E218(struct MainObj* self)
{
    s32 x_velocity;

    if (self->unk6 == 0) {
        self->collision_data = D_801069F4;
        self->unk54 = &D_800FBA50;
        self->unk50 = &D_800FBA50;
        self->unk6++;
        func_80015D60(self, 1);
        x_velocity = FIXED(-0.375);
        if (self->unk15 != 0) {
            x_velocity = FIXED(0.375);
        }
        self->unk20 = x_velocity;
        self->unk28 = 0;
        self->unk24 = 0;
        self->unk2C = 0;
    }

    func_80015DC8(ANIMATED_OBJECT(self));
    func_8002B718(MOVING_OBJECT(self));
    if (self->unk15 != 0) {
        if (self->unk70 & 1) {
            self->unk15 = 0;
            self->unk20 = -self->unk20;
        }
    } else if (self->unk70 & 2) {
        self->unk15 = 0x40;
        self->unk20 = -self->unk20;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004E300);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004E490);

INCLUDE_ASM("main/nonmatchings/mains/main_15", func_8004E55C);

void func_8004E6A4(struct MainObj* arg0)
{
    u16 x;

    if (ENGINE_STAGE_ID == 0x102 && engine_obj.character_state.bytes[0] != 0) {
        x = arg0->x_pos.i.hi;
        if ((u16)(x - 0xC0F) < 0x1E2 || (u16)(x - 0x100F) < 0x1E2
            || (u16)(x - 0x1315) < 0x1DC || (u16)(x - 0x1613) < 0x1BF) {
            arg0->state = 3;
            arg0->unk6 = 0;
            return;
        }
    }
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (func_8002DD04(arg0) < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(4, D_800FBB84, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0x12);
        arg0->state++;
        return;
    }
    func_8004DB10(arg0);
    func_8004D9CC(arg0);
    func_8004DCB0(arg0);
    D_800FBB88[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x25, 0x25);
    } else {
        arg0->state++;
    }
}

void func_8004E810(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8004E830(struct MainObj* arg0)
{
    D_800FBBA0[arg0->state](arg0);
    if (arg0->state != 5) {
        CollisionRelated(PLAYER_OBJECT(arg0));
    }
}

struct Unk_unk68 D_800FBA4C = { 0, 1, 11, 12 };

struct Unk_unk68 D_800FBA50 = { -11, -16, 21, 29 };

struct Unk_unk68 D_800FBA54 = { -12, -4, 21, 18 };

union AnimationStep D_800FBA58[] = {
    { 0x00000001 },
};

union AnimationStep D_800FBA5C[] = {
    { 0x01010008 },
    { 0x02010008 },
    { 0x03010008 },
    { 0x04010003 },
    { 0x05010005 },
    { 0x06010008 },
    { 0x07010008 },
    { 0x08010008 },
    { 0x09010003 },
    { 0x0AF70005 },
};

union AnimationStep D_800FBA84[] = {
    { 0x00010006 },
    { 0x0B01000A },
    { 0x0C010102 },
    { 0x0D010002 },
    { 0x0E010003 },
    { 0x0E000001 },
};

union AnimationStep D_800FBA9C[] = {
    { 0x0F010002 },
    { 0x10FF0002 },
};

union AnimationStep D_800FBAA4[] = {
    { 0x11010003 },
    { 0x0B01000A },
    { 0x12010002 },
    { 0x00010003 },
    { 0x12010002 },
    { 0x12000001 },
};

union AnimationStep D_800FBABC[] = {
    { 0x00010006 },
    { 0x12010001 },
    { 0x13010002 },
    { 0x14010102 },
    { 0x15010001 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x18000001 },
};

union AnimationStep D_800FBAE4[] = {
    { 0x18010006 },
    { 0x17010001 },
    { 0x16010002 },
    { 0x15010002 },
    { 0x14010001 },
    { 0x13010002 },
    { 0x12010002 },
    { 0x00010002 },
    { 0x12010002 },
    { 0x00000001 },
};

union AnimationStep D_800FBB0C[] = {
    { 0x00010006 },
    { 0x19010006 },
    { 0x1A010008 },
    { 0x1B010102 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x0001000A },
    { 0x00000001 },
};

union AnimationStep D_800FBB2C[] = {
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20FE0002 },
};

union AnimationStep D_800FBB38[] = {
    { 0x21000001 },
};

union AnimationStep D_800FBB3C[] = {
    { 0x22000001 },
};

union AnimationStep D_800FBB40[] = {
    { 0x23000001 },
};

union AnimationStep D_800FBB44[] = {
    { 0x24000001 },
};

union AnimationStep D_800FBB48[] = {
    { 0x25000001 },
};

union AnimationStep* D_800FBB4C[14] = {
    D_800FBA58,
    D_800FBA5C,
    D_800FBA84,
    D_800FBA9C,
    D_800FBAA4,
    D_800FBABC,
    D_800FBAE4,
    D_800FBB0C,
    D_800FBB2C,
    D_800FBB38,
    D_800FBB3C,
    D_800FBB40,
    D_800FBB44,
    D_800FBB48,
};

u8 D_800FBB84[4] = { 9, 10, 11, 12 };

void (*D_800FBB88[6])() = {
    func_8009216C,
    func_8004E218,
    func_8004DF40,
    func_8004DFEC,
    func_8004E128,
    func_8004DEA0,
};

void (*D_800FBBA0[6])(struct MainObj*) = {
    func_8004E55C,
    func_8004E6A4,
    func_8004E810,
    func_8004E300,
    func_8004E490,
    func_8004D930,
};
