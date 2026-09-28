// MainObj, main_object_update_funcs[16]
// 8004E890..8004FF90
#include "common.h"
#include "func_tables.h"

void func_8004E890(struct MainObj* arg0)
{
    D_800FBD8C[arg0->state](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004E8E0);

void func_8004EA88(struct MainObj* arg0)
{
    s32 collision;

    func_8004FBF4(arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (arg0->unk7 == 0) {
        func_8004FD38(arg0, 2);
        arg0->unk7 = 1;
    }

    D_800FBD9C[arg0->unk5](arg0);
    if (arg0->unk5 == 0xA) {
        return;
    }

    if (engine_obj.character_state.bytes[0] != 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(0xB, D_800FBD80, arg0);
        arg0->unk7C = 0x20;
        arg0->unk7E = 6;
        arg0->ext.main_16.shot_09_active = 0;
        arg0->on_screen = 0;
        arg0->state = 2;
        return;
    }

    func_8002D9BC(arg0);
    collision = func_8002DD04(arg0);
    if (collision < 0) {
        func_800AF808(BASE_OBJECT(arg0));
        func_800C813C(0xB, D_800FBD80, arg0);
        func_800BF60C(BASE_OBJECT(arg0), 0x13);
        arg0->unk7C = 0x20;
        arg0->unk7E = 6;
        arg0->ext.main_16.shot_09_active = 0;
        arg0->on_screen = 0;
        arg0->state = 2;
        return;
    }

    if ((collision == 0x1B || collision == 0x1C) && arg0->ext.main_16.unk8C != 1) {
        arg0->unk54 = &D_800FBBB8;
        func_80015D60(arg0, 0xE);
        arg0->ext.main_16.unk90 = 0;
        arg0->unk5 = 1;
        arg0->unk6 = 0;
    }

    if (arg0->state == 2) {
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x68, 0xA8) == 0) {
        func_8002B318(BASE_OBJECT(arg0), 0x48, 0x48);
        return;
    }
    arg0->ext.main_16.shot_09_active = 0;
    arg0->state = 3;
}

void func_8004EC44(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        arg0->state = 3;
    } else if (--arg0->unk7E == 0) {
        arg0->unk7E = 6;
        func_800AF878(arg0, 1, 24, 32);
    }
}

void func_8004ECB0(struct MainObj* arg0)
{
    arg0->ext.main_16.unk80 = 0;
    arg0->ext.main_16.unk84 = 0;
    arg0->ext.main_16.unk88 = 0;
    arg0->ext.main_16.unk8C = 0;
    arg0->ext.main_16.unk90 = 0;
    arg0->ext.main_16.shot_09_active = 0;
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_8004ECE4(struct MainObj* arg0)
{
    D_800FBDC8[arg0->unk6](arg0);
}

void func_8004ED20(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->unk7C = 0x1E;
    arg0->unk6 = 1;
    arg0->ext.main_16.unk8C = 2;
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004ED60);

void func_8004EF14(struct MainObj* arg0)
{
    if (arg0->unk70 & 8) {
        func_80015D60(arg0, 3);
        arg0->unk54 = (const u8*)&D_800FBBBC;
        arg0->unk67 = 0;
        func_8004FD38(arg0, 5);
        func_8004FD38(arg0, 2);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        return;
    }

    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
}

void func_8004EFA4(struct MainObj* arg0)
{
    D_800FBDD0[arg0->unk6](arg0);
}

void func_8004EFE0(struct MainObj* arg0)
{
    struct MiscObj* misc;
    u8 temp_v1;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        misc = find_free_misc_obj();
        if (misc != 0) {
            misc->active = 0x41;
            misc->id = 5;
            misc->unk40 = arg0->unk40;
            misc->unk42 = arg0->unk42 & 0x7FFF;
            misc->animation_table = (u32**)arg0->animation_table;
            misc->unk3C = (void*)arg0->sprite_frames;
            misc->bg_offset = arg0->bg_offset;
            misc->x_pos.val = arg0->x_pos.val;
            misc->y_pos.val = arg0->y_pos.val;
            temp_v1 = arg0->unk15;
            misc->ext.misc_7.position = &arg0->ext.main_16.unk90;
            misc->state = 0;
            misc->unk15 = temp_v1;
        }
        func_8004FD38(arg0, 5);
        func_80015D60(arg0, 2);
        arg0->unk6 = 1;
    }
}

void func_8004F0C4(struct MainObj* arg0)
{
    arg0->unk24 = FIXED(8.25);
    arg0->unk2C = FIXED(0.375);
    arg0->unk67 = 1;
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 2;
}

void func_8004F118(struct MainObj* arg0)
{
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk24 == 0) {
        arg0->ext.main_16.unk90 = 0;
        if (arg0->ext.main_16.unk80 == 0) {
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            arg0->unk67 = 0;
            return;
        }
        func_8004FC50(ANIMATED_OBJECT(arg0));
        func_80015D60(arg0, 6);
        arg0->ext.main_16.unk80 = 0;
        arg0->unk5 = 7;
        arg0->unk6 = 0;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004F1A0);

void func_8004F228(struct MainObj* arg0)
{
    D_800FBDDC[arg0->unk6](arg0);
}

void func_8004F264(struct MainObj* arg0)
{
    func_80015D60(arg0, 4);
    arg0->unk7C = 0x1E;
    arg0->unk6 = 1;
}

void func_8004F2A0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk7C % 10 == 0) {
        func_8001540C(2, 0x27, arg0);
    }
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 0xD);
        arg0->unk61 = 0;
        arg0->unk6 = 2;
        arg0->ext.main_16.unk88 = 0;
    }
}

void func_8004F34C(struct MainObj* arg0)
{
    s16 value;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    value = (u16)arg0->unk7C ^ arg0->ext.main_16.unk88;
    arg0->unk7C = value;
    if (value == 0) {
        arg0->unk60 = 3;
        arg0->unk50 = &D_800FBBC0;
    } else {
        arg0->unk60 = 6;
        arg0->unk50 = &D_800FBBC4;
    }
    if (arg0->animation_step.fields.event == 2) {
        arg0->ext.main_16.unk88 = 1;
        func_8001540C(2, 0x28, arg0);
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk60 = 3;
        arg0->unk50 = &D_800FBBC0;
        func_8004FC50(ANIMATED_OBJECT(arg0));
        func_80015D60(arg0, 0);
        arg0->ext.main_16.unk8C = 0;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_8004F424(struct MainObj* arg0)
{
    D_800FBDE8[arg0->unk6](arg0);
}

void func_8004F460(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 7);
        arg0->unk6 = 1;
        arg0->unk7C = 8;
        arg0->ext.main_16.unk80 = 0x18;
        arg0->ext.main_16.unk88 = 0;
        if (arg0->unk15 == 0) {
            arg0->ext.main_16.unk84 = -4;
        } else {
            arg0->ext.main_16.unk84 = 4;
        }
    }
}

void func_8004F4D4(struct MainObj* arg0)
{
    struct ShotObj* shot;
    u8 facing;
    u32 angle;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk7C == 8) {
        func_8001540C(2, 0x27, arg0);
    }
    if (--arg0->unk7C == 0) {
        func_8001540C(2, 0x29, arg0);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 9;
            shot->unk2 = arg0->ext.main_16.unk88;
            shot->unk40 = arg0->unk40;
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)arg0->animation_table;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->bg_offset = arg0->bg_offset;
            shot->x_pos.val = arg0->x_pos.val;
            shot->y_pos.val = arg0->y_pos.val;
            facing = arg0->unk15;
            shot->state = 3;
            shot->unk15 = facing;
        }

        angle = arg0->ext.main_16.unk80 & 0x1F;
        arg0->ext.main_16.unk80 = angle;
        func_8002B93C(MOVING_OBJECT(shot), angle);
        arg0->ext.main_16.unk80 += arg0->ext.main_16.unk84;
        if ((s32)arg0->ext.main_16.unk80 < 0x10) {
            func_80015D60(arg0, 7);
            arg0->unk6 = 2;
        } else {
            arg0->unk7C = 8;
            arg0->ext.main_16.unk88++;
        }
    }
}

void func_8004F62C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        func_80015D60(arg0, 2);
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk67 = 0;
    }
}

void func_8004F67C(struct MainObj* arg0)
{
    D_800FBDF4[arg0->unk6](arg0);
}

void func_8004F6B8(struct MainObj* arg0)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0) {
        return;
    }

    func_80015D60(arg0, 0x12);
    func_8001540C(2, 0x29, arg0);
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 9;
        shot->unk2 = 3;
        shot->unk40 = arg0->unk40;
        shot->unk42 = arg0->unk42;
        shot->animation_table = (u32**)arg0->animation_table;
        shot->unk3C = (void*)arg0->sprite_frames;
        shot->unk15 = arg0->unk15;
        shot->bg_offset = arg0->bg_offset;
        shot->x_pos.val = arg0->x_pos.val;
        shot->y_pos.val = arg0->y_pos.val;
        shot->unk15 = arg0->unk15;
        if (arg0->unk15 == 0) {
            shot->x_vel.val = FIXED(-1);
        } else {
            shot->x_vel.val = FIXED(1);
        }
        shot->y_vel.val = 0;
        shot->state = 3;
    }
    arg0->unk7C = 0x14;
    arg0->unk6 = 1;
}

void func_8004F7D0(struct MainObj* arg0)
{
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0) {
        return;
    }

    func_80015D60(arg0, 0x13);
    func_8001540C(2, 0x29, arg0);
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 9;
        shot->unk2 = 4;
        shot->unk40 = arg0->unk40;
        shot->unk42 = arg0->unk42;
        shot->animation_table = (u32**)arg0->animation_table;
        shot->unk3C = (void*)arg0->sprite_frames;
        shot->unk15 = arg0->unk15;
        shot->bg_offset = arg0->bg_offset;
        shot->x_pos.val = arg0->x_pos.val;
        shot->y_pos.val = arg0->y_pos.val;
        shot->unk15 = arg0->unk15;
        if (arg0->unk15 != 0) {
            shot->x_vel.val = FIXED(1);
        } else {
            shot->x_vel.val = FIXED(-1);
        }
        shot->y_vel.val = 0;
        shot->state = 3;
    }
    if (arg0->unk2 < 4) {
        arg0->unk7C = 0x14;
    } else {
        func_8004FC50(ANIMATED_OBJECT(arg0));
        arg0->unk7C = 0x3C;
    }
    arg0->unk6 = 2;
}

void func_8004F910(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0) {
        return;
    }
    if (arg0->unk2 >= 4) {
        if (--arg0->unk7E != 0) {
            arg0->unk6 = 0;
            return;
        }
        func_80015D60(arg0, 0x10);
        arg0->ext.main_16.unk80 = 1;
        arg0->ext.main_16.unk90 = 1;
        arg0->unk5 = 4;
    } else {
        func_80015D60(arg0, 0);
        arg0->unk5 = 2;
    }
    arg0->unk6 = 0;
}

void func_8004F9B4(struct MainObj* self)
{
    s16 timer;
    u8 facing;
    struct MiscObj* misc;

    timer = (u16)self->unk7C - 1;
    self->unk7C = timer;
    if (timer == 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 5;
            misc->unk2 = 0;
            misc->unk40 = self->unk40;
            misc->unk42 = self->unk42 & 0x7FFF;
            misc->animation_table = self->animation_table;
            misc->unk3C = self->sprite_frames;
            misc->unk15 = self->unk15;
            misc->bg_offset = (s8)(u8)self->bg_offset;
            misc->x_pos.val = self->x_pos.val;
            misc->y_pos.val = self->y_pos.val;
            facing = self->unk15;
            misc->ext.misc_5.animation = 0x14;
            misc->state = 3;
            misc->unk15 = facing;
        }
        self->ext.main_16.unk90 = 1;
        self->ext.main_16.unk80 = 0;
        self->unk5 = 4;
        self->unk6 = 0;
    }
}

void func_8004FAAC(struct MainObj* arg0)
{
    if (g_Player.x_pos.i.hi - arg0->x_pos.i.hi >= 0x11) {
        arg0->unk5 = 2;
        arg0->y_pos.u.hi -= 0x28;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004FAE4);

void func_8004FBF4(struct MainObj* arg0)
{
    if ((arg0->unk67 == 0) && (arg0->unk5 != 0xA) && !(arg0->unk70 & 8)) {
        arg0->unk5 = 3;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 1;
    }
}

void func_8004FC50(struct AnimatedObj* arg0)
{
    if (arg0->x_pos.val > g_Player.x_pos.val) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
}

void func_8004FC80(struct MainObj* obj)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot != 0) {
        u8 final_unk15;

        shot->active = 0x41;
        shot->id = 9;
        shot->unk2 = 0;
        shot->unk40 = obj->unk40;
        shot->unk42 = obj->unk42;
        shot->animation_table = ANIMATED_OBJECT(obj)->animation_table;
        shot->unk3C = ANIMATED_OBJECT(obj)->unk3C;
        shot->unk15 = obj->unk15;
        shot->bg_offset = obj->bg_offset;
        shot->x_pos.val = obj->x_pos.val;
        shot->y_pos.val = obj->y_pos.val;
        final_unk15 = obj->unk15;
        shot->unk7C = (struct WeaponObj*)&obj->ext.main_16.shot_09_active;
        shot->state = 0;
        shot->unk15 = final_unk15;
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_16", func_8004FD38);

struct Unk_unk68 D_800FBBB8 = { -14, -28, 30, 59 };

struct Unk_unk68 D_800FBBBC = { -16, -8, 34, 37 };

struct Unk_unk68 D_800FBBC0 = { -11, -17, 19, 47 };

struct Unk_unk68 D_800FBBC4 = { -89, -1, 69, 13 };

struct Unk_unk68 D_800FBBC8 = { 2, 2, 18, 26 };

union AnimationStep D_800FBBCC[] = {
    { 0x00010007 },
    { 0x00000101 },
};

union AnimationStep D_800FBBD4[] = {
    { 0x01010007 },
    { 0x01000101 },
};

union AnimationStep D_800FBBDC[] = {
    { 0x0A010003 },
    { 0x0BFF0103 },
};

union AnimationStep D_800FBBE4[] = {
    { 0x0C010001 },
    { 0x0D010002 },
    { 0x0C000101 },
};

union AnimationStep D_800FBBF0[] = {
    { 0x0C010008 },
    { 0x0D010008 },
    { 0x0C01001B },
    { 0x0C000101 },
};

union AnimationStep D_800FBC00[] = {
    { 0x02010003 },
    { 0x03000101 },
};

union AnimationStep D_800FBC08[] = {
    { 0x04010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x07010001 },
    { 0x05010001 },
    { 0x06FB0101 },
};

union AnimationStep D_800FBC20[] = {
    { 0x11010002 },
    { 0x11000101 },
};

union AnimationStep D_800FBC28[] = {
    { 0x0E010001 },
    { 0x10010001 },
    { 0x0FFE0101 },
};

union AnimationStep D_800FBC34[] = {
    { 0x12010001 },
    { 0x13FF0101 },
};

union AnimationStep D_800FBC3C[] = {
    { 0x14010001 },
    { 0x15FF0101 },
};

union AnimationStep D_800FBC44[] = {
    { 0x16010001 },
    { 0x17FF0101 },
};

union AnimationStep D_800FBC4C[] = {
    { 0x18010014 },
    { 0x1A010002 },
    { 0x19010201 },
    { 0x19010001 },
    { 0x1B010001 },
    { 0x1C010013 },
    { 0x1C000101 },
};

union AnimationStep D_800FBC68[] = {
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x1E010001 },
    { 0x1E000101 },
};

union AnimationStep D_800FBC84[] = {
    { 0x1F010002 },
    { 0x20010002 },
    { 0x21FE0002 },
};

union AnimationStep D_800FBC90[] = {
    { 0x00010008 },
    { 0x23010002 },
    { 0x22010022 },
    { 0x22000101 },
};

union AnimationStep D_800FBCA0[] = {
    { 0x24010002 },
    { 0x2501000E },
    { 0x25000101 },
};

union AnimationStep D_800FBCAC[] = {
    { 0x26010002 },
    { 0x2701000E },
    { 0x27000101 },
};

union AnimationStep D_800FBCB8[] = {
    { 0x28010002 },
    { 0x29FF0102 },
};

union AnimationStep D_800FBCC0[] = {
    { 0x2A010002 },
    { 0x2BFF0002 },
};

union AnimationStep D_800FBCC8[] = {
    { 0x2C010003 },
    { 0x2D010003 },
    { 0x2E010003 },
    { 0x2F010003 },
    { 0x30010003 },
    { 0x31010003 },
    { 0x32010003 },
    { 0x33010002 },
    { 0x33000101 },
};

union AnimationStep D_800FBCEC[] = {
    { 0x34000101 },
};

union AnimationStep D_800FBCF0[] = {
    { 0x35000101 },
};

union AnimationStep D_800FBCF4[] = {
    { 0x36000101 },
};

union AnimationStep D_800FBCF8[] = {
    { 0x37000101 },
};

union AnimationStep D_800FBCFC[] = {
    { 0x38000101 },
};

union AnimationStep D_800FBD00[] = {
    { 0x39000101 },
};

union AnimationStep D_800FBD04[] = {
    { 0x3A000101 },
};

union AnimationStep D_800FBD08[] = {
    { 0x3B000101 },
};

union AnimationStep* D_800FBD0C[29] = {
    D_800FBBCC,
    D_800FBBD4,
    D_800FBBDC,
    D_800FBBF0,
    D_800FBC00,
    D_800FBC08,
    D_800FBC20,
    D_800FBC28,
    D_800FBC44,
    D_800FBC3C,
    D_800FBC34,
    D_800FBCB8,
    D_800FBCC0,
    D_800FBC4C,
    D_800FBC68,
    D_800FBC84,
    D_800FBBE4,
    D_800FBC90,
    D_800FBCA0,
    D_800FBCAC,
    D_800FBCC8,
    D_800FBCEC,
    D_800FBCF0,
    D_800FBCF4,
    D_800FBCF8,
    D_800FBCFC,
    D_800FBD00,
    D_800FBD04,
    D_800FBD08,
};

u8 D_800FBD80[12] = { 21, 22, 23, 24, 25, 25, 25, 25, 26, 27, 28, 0 };

void (*D_800FBD8C[4])() = {
    func_8004E8E0,
    func_8004EA88,
    func_8004EC44,
    func_8004ECB0,
};

void (*D_800FBD9C[11])() = {
    func_8009216C,
    func_8004FAE4,
    func_8004ECE4,
    func_8004EF14,
    func_8004EFA4,
    func_8004F1A0,
    func_8004F228,
    func_8004F424,
    func_8004F67C,
    func_8004F9B4,
    func_8004FAAC,
};

void (*D_800FBDC8[2])() = {
    func_8004ED20,
    func_8004ED60,
};

void (*D_800FBDD0[3])(struct MainObj*) = {
    func_8004EFE0,
    func_8004F0C4,
    func_8004F118,
};

void (*D_800FBDDC[3])(struct MainObj*) = {
    func_8004F264,
    func_8004F2A0,
    func_8004F34C,
};

void (*D_800FBDE8[3])(struct MainObj*) = {
    func_8004F460,
    func_8004F4D4,
    func_8004F62C,
};

void (*D_800FBDF4[3])(struct MainObj*) = {
    func_8004F6B8,
    func_8004F7D0,
    func_8004F910,
};
