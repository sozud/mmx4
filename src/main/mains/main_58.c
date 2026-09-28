// MainObj, main_object_update_funcs[58]
// 800743FC..80074E84
#include "common.h"
#include "func_tables.h"

void func_800743FC(struct MainObj* arg0)
{
    D_80101658[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_80074438);

INCLUDE_ASM("main/nonmatchings/mains/main_58", func_800745E8);

void func_800747EC(struct MainObj* arg0)
{
    arg0->ext.main_58.unk88 = 2;
    if (arg0->unk2 == 0) {
        func_8002B0C8(OBJECT_HEADER(arg0));
        return;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8007482C(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_58.saved_unk5;
}

void func_80074838(struct MainObj* arg0)
{
    D_8010167C[arg0->unk6](arg0);
}

void func_80074874(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(ANIMATED_OBJECT(arg0), 0);
    arg0->unk6++;
}

void func_800748B8(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7E - 1;
    arg0->unk7E = timer;
    if (timer == 0) {
        arg0->unk5 = 3;
        arg0->unk20 = 0;
        arg0->unk24 = 0;
        arg0->unk7E = 0x14;
        arg0->unk6 = 0;
    }
}

void func_8007491C(struct MainObj* arg0)
{
    D_80101684[arg0->unk6](arg0);
}

void func_80074958(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 7);
    func_80074DDC(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 0x2D, arg0);
    arg0->unk7C = 0x50;
    arg0->unk6++;
}

void func_800749B8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 4;
        arg0->ext.main_58.unk88 = 1;
        arg0->unk6 = 0;
    }
}

void func_80074A0C(struct MainObj* arg0)
{
    D_8010168C[arg0->unk6](arg0);
}

void func_80074A48(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 1);
    func_80074D10(arg0);
    func_8001540C(2, 0x2C, arg0);
    arg0->unk7C = 0x12;
    arg0->unk6++;
}

void func_80074AA8(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        func_80015D60(arg0, 2);
        arg0->ext.main_58.unk88 = 2;
        arg0->unk7C = 0x3C;
        arg0->unk6++;
    }
}

void func_80074B10(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->ext.main_58.unk88 = 0;
        arg0->unk7C = 0x2A;
        arg0->unk6++;
    }
}

void func_80074B68(struct MainObj* arg0)
{
    s32 state;
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 0);
        state = arg0->unk2;
        if (state != 0) {
            state = 5;
        } else {
            state = 2;
        }
        arg0->unk5 = state;
        arg0->unk6 = 0;
        arg0->unk7E = 0x28;
    }
}

void func_80074BD8(struct MainObj* arg0)
{
    D_8010169C[arg0->unk6](arg0);
}

void func_80074C14(struct MainObj* arg0)
{
    s32 velocity;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 0);
    arg0->unk7C = 0x3C;
    if (arg0->unk2 == 1) {
        velocity = 0x18000;
        if (arg0->y_pos.i.hi >= 0x369) {
            velocity = -0x18000;
        }
        arg0->unk24 = velocity;
    } else {
        velocity = -0x18000;
        if (arg0->x_pos.i.hi >= 0x951) {
            velocity = 0x18000;
        }
        arg0->unk20 = velocity;
    }
    arg0->unk6++;
}

void func_80074CB8(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B718(MOVING_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->ext.main_58.unk88 = 2;
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

void func_80074D10(struct VisualObj* arg0)
{
    struct ShotObj* shot;
    u8 i;

    for (i = 0; i < 2; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x24;
            shot->unk2 = i;
            shot->unk7C = (struct WeaponObj*)arg0;
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)D_80101624;
            shot->unk3C = arg0->unk3C;
            shot->unk40 = arg0->unk40;
            shot->unk15 = arg0->unk15;
            shot->bg_offset = arg0->bg_offset;
            if (arg0->unk15 == 0) {
                shot->unk16 = 0;
            } else {
                shot->unk16 = 1;
            }
        }
    }
}

void func_80074DDC(struct AnimatedObj* arg0)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x10;
        obj->unk2 = 0;
        obj->unk50 = PLAYER_OBJECT(arg0);
        obj->unk42 = arg0->unk42;
        obj->animation_table = D_80101624;
        obj->unk3C = arg0->unk3C;
        obj->unk40 = arg0->unk40;
        obj->bg_offset = arg0->bg_offset;
        obj->unk16 = 4;
        obj->unk15 = arg0->unk15;
        obj->x_pos.val = arg0->x_pos.val;
        obj->y_pos.val = arg0->y_pos.val;
    }
}

struct Unk_unk68 D_80101514 = { -10, -10, 20, 20 };

struct Unk_unk68 D_80101518[4] = {
    { 2, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, -3, 3 },
};

union AnimationStep D_80101528[] = {
    { 0x0A010002 },
    { 0x0B010002 },
    { 0x0A010004 },
    { 0x0C010004 },
    { 0x0D010002 },
    { 0x0E010002 },
    { 0x0F000002 },
};

struct Unk_unk68 D_80101544[4] = {
    { 2, 0, 1, 16 },
    { 2, 0, 1, 17 },
    { 2, 0, 1, 18 },
    { 2, 0, -3, 19 },
};

struct Unk_unk68 D_80101554[7] = {
    { 2, 0, 1, 28 },
    { 2, 0, 1, 29 },
    { 2, 0, 1, 30 },
    { 1, 0, 1, 31 },
    { 1, 0, 1, 32 },
    { 1, 0, 1, 33 },
    { 1, 0, -2, 34 },
};

struct Unk_unk68 D_80101570[7] = {
    { 2, 0, 1, 35 },
    { 2, 0, 1, 36 },
    { 2, 0, 1, 37 },
    { 1, 0, 1, 38 },
    { 1, 0, 1, 39 },
    { 1, 0, 1, 40 },
    { 1, 0, -2, 41 },
};

union AnimationStep D_8010158C[] = {
    { 0x22010001 },
    { 0x21010001 },
    { 0x20010001 },
    { 0x1F010001 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x1C000002 },
};

union AnimationStep D_801015A8[] = {
    { 0x29010001 },
    { 0x28010001 },
    { 0x27010001 },
    { 0x26010001 },
    { 0x25010002 },
    { 0x24010002 },
    { 0x23000002 },
};

struct Unk_unk68 D_801015C4[8] = {
    { 2, 0, 1, 4 },
    { 3, 0, 1, 5 },
    { 2, 0, 1, 4 },
    { 3, 0, 1, 1 },
    { 2, 0, 1, 6 },
    { 2, 0, 1, 7 },
    { 2, 0, 1, 8 },
    { 3, 0, -7, 9 },
};

struct Unk_unk68 D_801015E4[13] = {
    { 4, 0, 1, 20 },
    { 4, 0, 1, 21 },
    { 3, 0, 1, 22 },
    { 3, 0, 1, 23 },
    { 2, 0, 1, 20 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 22 },
    { 2, 0, 1, 23 },
    { 2, 0, 1, 24 },
    { 2, 0, 1, 25 },
    { 2, 0, 1, 26 },
    { 2, 0, 1, 25 },
    { 2, 0, -4, 27 },
};

union AnimationStep D_80101618[] = {
    { 0x2A000001 },
};

union AnimationStep D_8010161C[] = {
    { 0x2B000001 },
};

union AnimationStep D_80101620[] = {
    { 0x2C000001 },
};

void* D_80101624[12] = {
    D_80101518,
    D_80101528,
    D_80101544,
    D_80101554,
    D_80101570,
    D_8010158C,
    D_801015A8,
    D_801015C4,
    D_801015E4,
    D_80101618,
    D_8010161C,
    D_80101620,
};

struct Unk_unk68 D_80101654 = { 9, 10, 11, 0 };

void (*D_80101658[3])() = {
    func_80074438,
    func_800745E8,
    func_800747EC,
};

void (*D_80101664[6])() = {
    func_8009216C,
    func_8007482C,
    func_80074838,
    func_8007491C,
    func_80074A0C,
    func_80074BD8,
};

void (*D_8010167C[2])() = {
    func_80074874,
    func_800748B8,
};

void (*D_80101684[2])() = {
    func_80074958,
    func_800749B8,
};

void (*D_8010168C[4])() = {
    func_80074A48,
    func_80074AA8,
    func_80074B10,
    func_80074B68,
};

void (*D_8010169C[2])() = {
    func_80074C14,
    func_80074CB8,
};
