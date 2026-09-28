// MainObj, main_object_update_funcs[67]
// 80082434..80083218
#include "common.h"
#include "func_tables.h"

void func_80082F20(struct VisualObj* arg0);

void func_80082434(struct MainObj* arg0)
{
    D_80103E84[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082470);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082574);

void func_800826C8(struct MainObj* arg0)
{
    s32 y;

    arg0->unk18.val = arg0->x_pos.val;
    y = arg0->y_pos.val;
    arg0->unk1C.val = y;
    D_80103EAC[arg0->unk5](arg0, y);
}

void func_80082710(struct MainObj* arg0, s32 y)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 0x13);
    arg0->unk24 = FIXED(-0.5);
    arg0->unk20 = 0;
    arg0->unk28 = 0;
    arg0->unk2C = FIXED(0.0078125);
    arg0->unk68 = NULL;
    arg0->unk5++;
    func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
    func_8002E184(PLAYER_OBJECT(arg0));
}

void func_80082784(struct MainObj* arg0, s32 y)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B694(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_800BF60C(BASE_OBJECT(arg0), 8);
        func_800C813C(6, D_80103E7C, arg0);
        arg0->on_screen = 0;
        arg0->unk5++;
    } else {
        if (--arg0->unk7E == 0) {
            func_800AF878(BASE_OBJECT(arg0), 1, 0x40, 0x20);
            arg0->unk7E = 5;
        }
        func_8002B318(BASE_OBJECT(arg0), 0x50, 0x50);
        func_8002E184(PLAYER_OBJECT(arg0));
    }
}

void func_8008284C(struct MainObj* arg0, s32 y)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_8008286C(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_67.saved_unk5;
}

void func_80082878(struct MainObj* arg0)
{
    D_80103EB8[arg0->unk6](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_800828B4);

void func_800829EC(struct MainObj* arg0)
{
    D_80103EBC[arg0->unk6](arg0);
}

void func_80082A28(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->ext.main_67.unk89 = 1;
    func_8001540C(2, 0xA1, arg0);
    func_80082E88(arg0);
    arg0->ext.main_67.unk8A++;
    timer = 0xA;
    if (engine_obj.cur_character == 0) {
        timer = 0x14;
    }
    arg0->unk7C = timer;
    arg0->unk6++;
}

void func_80082AA8(struct MainObj* arg0)
{
    s16 timer;
    s16 reset_timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk6 = 0;
        if (arg0->ext.main_67.unk8A >= 3) {
            arg0->unk5 = 2;
            arg0->ext.main_67.unk89 = 0;
            arg0->ext.main_67.unk8A = 0;
            reset_timer = 0x28;
            if (engine_obj.cur_character == 0) {
                reset_timer = 0x1E;
            }
            arg0->unk7C = reset_timer;
        }
    }
}

void func_80082B2C(struct MainObj* arg0)
{
    D_80103EC4[arg0->unk6](arg0);
}

void func_80082B68(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    arg0->unk7C = 0x23;
    arg0->unk6++;
}

void func_80082BA4(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        func_80015D60(arg0, 1);
        arg0->unk7C = 4;
        arg0->unk6++;
    }
}

void func_80082C04(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_8001540C(2, 0xA2, arg0);
        func_80082F20(VISUAL_OBJECT(arg0));
        arg0->unk7C = 0x3C;
        arg0->unk6++;
    }
}

void func_80082C70(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7C = 0x78;
    }
}

void func_80082CC4(struct MainObj* arg0)
{
    D_80103ED4[arg0->unk6](arg0);
}

void func_80082D00(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    func_80015D60(arg0, 0x14);
    arg0->unk7C = 0x1A;
    arg0->unk6++;
}

void func_80082D48(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7C = 0x28;
    }
}

void func_80082D9C(struct MainObj* arg0)
{
    D_80103EDC[arg0->unk6](arg0);
}

void func_80082DD8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 0);
    func_800830D0(arg0);
    arg0->ext.main_67.unk89 = 1;
    arg0->unk7C = 0x78;
    arg0->unk6++;
}

void func_80082E30(struct MainObj* arg0)
{
    s16 timer;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    timer = arg0->unk7C - 1;
    arg0->unk7C = timer;
    if (timer == 0) {
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        arg0->ext.main_67.unk89 = 0;
        arg0->unk7C = 0xA;
    }
}

void func_80082E88(struct MainObj* arg0)
{
    struct ShotObj* shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x2B;
        shot->unk2 = (u8)engine_obj.cur_character;
        shot->unk7C = WEAPON_OBJECT(arg0);
        shot->unk42 = arg0->unk42;
        shot->animation_table = (u32**)D_80103E08;
        shot->unk3C = (void*)arg0->sprite_frames;
        shot->unk40 = arg0->unk40;
        shot->unk15 = arg0->unk15;
        shot->bg_offset = arg0->bg_offset;
        shot->unk16 = 4;
    }
}

void func_80082F20(struct VisualObj* arg0)
{
    struct ShotObj* shot;
    u8 i;
    for (i = 0; i < 4; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x2B;
            shot->unk2 = i + 2;
            shot->unk7C = WEAPON_OBJECT(arg0);
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)D_80103E08;
            shot->unk3C = arg0->unk3C;
            shot->unk40 = arg0->unk40;
            shot->unk15 = arg0->unk15;
            shot->bg_offset = arg0->bg_offset;
            shot->unk16 = (i < 2) ? 4 : 7;
        }
    }
}

void func_80082FEC(struct MainObj* self)
{
    if (self->ext.main_67.direction == 0) {
        if (self->ext.main_67.vertical_speed < FIXED(0.375) + 1) {
            if (self->ext.main_67.vertical_speed > 0 && self->ext.main_67.delay != 0) {
                self->ext.main_67.delay--;
            } else {
                self->ext.main_67.vertical_speed += FIXED(0.015625);
                self->y_pos.val -= self->ext.main_67.vertical_speed / 2;
                self->y_pos.val -= self->ext.main_67.vertical_speed;
            }
        } else {
            self->ext.main_67.delay = 0xF;
            self->ext.main_67.direction = 1;
        }
    } else {
        if (self->ext.main_67.vertical_speed >= FIXED(-0.375)) {
            if (self->ext.main_67.vertical_speed < 0 && self->ext.main_67.delay != 0) {
                self->ext.main_67.delay--;
            } else {
                self->ext.main_67.vertical_speed -= FIXED(0.015625);
                self->y_pos.val -= self->ext.main_67.vertical_speed / 2;
                self->y_pos.val -= self->ext.main_67.vertical_speed;
            }
        } else {
            self->ext.main_67.delay = 0xF;
            self->ext.main_67.direction = 0;
        }
    }
}

void func_800830D0(struct MainObj* arg0)
{
    s32 var_s1;
    struct VisualObj* temp_v0;

    var_s1 = 0;
    do {
        temp_v0 = find_free_visual_obj();
        if (temp_v0 != 0) {
            temp_v0->active = 0x41;
            temp_v0->id = 0x1F;
            temp_v0->unk2 = var_s1;
            temp_v0->unk50 = PLAYER_OBJECT(arg0);
            temp_v0->unk42 = arg0->unk42;
            temp_v0->animation_table = (u32**)D_80103E08;
            temp_v0->unk3C = arg0->sprite_frames;
            temp_v0->unk40 = arg0->unk40;
            temp_v0->bg_offset = arg0->bg_offset;
            temp_v0->unk16 = 5;
            temp_v0->unk15 = arg0->unk15;
        }
        var_s1 += 1;
    } while ((var_s1 & 0xFF) < 4U);
}

s32 func_8008318C(struct MainObj* arg0, s32 arg1, s32 arg2)
{
    POS_BOUNDS_CHECK_FAIL_RET0(arg0->x_pos.val, arg1)
    POS_BOUNDS_CHECK_FAIL_RET0(arg0->y_pos.val, arg2)
    return 1;
}

struct Unk_unk68 D_80103C84 = { -77, -41, -105, 68 };

struct Unk_unk68 D_80103C88 = { -1, -3, 78, 29 };

union AnimationStep D_80103C8C[] = {
    { 0x00000001 },
};

union AnimationStep D_80103C90[] = {
    { 0x00010002 },
    { 0x01010002 },
    { 0x02000002 },
};

struct Unk_unk68 D_80103C9C[5] = {
    { 5, 0, 1, 3 },
    { 5, 0, 1, 4 },
    { 5, 0, 1, 5 },
    { 5, 0, 1, 6 },
    { 5, 0, -4, 7 },
};

struct Unk_unk68 D_80103CB0[3] = {
    { 1, 0, 1, 8 },
    { 1, 0, 1, 9 },
    { 1, 0, -2, 10 },
};

struct Unk_unk68 D_80103CBC[3] = {
    { 1, 0, 1, 11 },
    { 1, 0, 1, 12 },
    { 1, 0, -2, 13 },
};

struct Unk_unk68 D_80103CC8[3] = {
    { 1, 0, 1, 14 },
    { 1, 0, 1, 15 },
    { 1, 0, -2, 16 },
};

struct Unk_unk68 D_80103CD4[3] = {
    { 1, 0, 1, 17 },
    { 1, 0, 1, 18 },
    { 1, 0, -2, 19 },
};

struct Unk_unk68 D_80103CE0[3] = {
    { 1, 0, 1, 20 },
    { 1, 0, 1, 21 },
    { 1, 0, -2, 22 },
};

struct Unk_unk68 D_80103CEC[3] = {
    { 1, 0, 1, 23 },
    { 1, 0, 1, 24 },
    { 1, 0, -2, 25 },
};

struct Unk_unk68 D_80103CF8[3] = {
    { 1, 0, 1, 26 },
    { 1, 0, 1, 27 },
    { 1, 0, -2, 28 },
};

struct Unk_unk68 D_80103D04[3] = {
    { 1, 0, 1, 29 },
    { 1, 0, 1, 30 },
    { 1, 0, -2, 31 },
};

struct Unk_unk68 D_80103D10[3] = {
    { 1, 0, 1, 32 },
    { 1, 0, 1, 33 },
    { 1, 0, -2, 34 },
};

struct Unk_unk68 D_80103D1C[3] = {
    { 1, 0, 1, 35 },
    { 1, 0, 1, 36 },
    { 1, 0, -2, 37 },
};

struct Unk_unk68 D_80103D28[3] = {
    { 1, 0, 1, 38 },
    { 1, 0, 1, 39 },
    { 1, 0, -2, 40 },
};

struct Unk_unk68 D_80103D34[3] = {
    { 1, 0, 1, 41 },
    { 1, 0, 1, 42 },
    { 1, 0, -2, 43 },
};

struct Unk_unk68 D_80103D40[3] = {
    { 1, 0, 1, 44 },
    { 1, 0, 1, 45 },
    { 1, 0, -2, 46 },
};

struct Unk_unk68 D_80103D4C[3] = {
    { 1, 0, 1, 47 },
    { 1, 0, 1, 48 },
    { 1, 0, -2, 49 },
};

struct Unk_unk68 D_80103D58[3] = {
    { 1, 0, 1, 50 },
    { 1, 0, 1, 51 },
    { 1, 0, -2, 52 },
};

struct Unk_unk68 D_80103D64[3] = {
    { 1, 0, 1, 53 },
    { 1, 0, 1, 54 },
    { 1, 0, -2, 55 },
};

union AnimationStep D_80103D70[] = {
    { 0x00010019 },
    { 0x38010019 },
    { 0x39010019 },
    { 0x3A000019 },
};

union AnimationStep D_80103D80[] = {
    { 0x02010001 },
    { 0x51010001 },
    { 0x3B010001 },
    { 0x51010001 },
    { 0x00000001 },
};

struct Unk_unk68 D_80103D94[12] = {
    { 4, 0, 1, 79 },
    { 4, 0, 1, 80 },
    { 4, 0, 1, 60 },
    { 4, 0, 1, 61 },
    { 4, 0, 1, 62 },
    { 14, 0, 1, 63 },
    { 4, 0, 1, 64 },
    { 4, 0, 1, 65 },
    { 4, 0, 1, 66 },
    { 4, 0, 1, 67 },
    { 4, 0, 1, 68 },
    { 14, 0, -11, 63 },
};

struct Unk_unk68 D_80103DC4[11] = {
    { 1, 0, 1, 69 },
    { 2, 0, 1, 70 },
    { 4, 0, 1, 71 },
    { 4, 0, 1, 72 },
    { 4, 0, 1, 73 },
    { 4, 0, 1, 74 },
    { 4, 0, 1, 75 },
    { 4, 0, 1, 76 },
    { 4, 0, 1, 77 },
    { 4, 0, 1, 78 },
    { 24, 0, -10, 63 },
};

union AnimationStep D_80103DF0[] = {
    { 0x52000001 },
};

union AnimationStep D_80103DF4[] = {
    { 0x53000001 },
};

union AnimationStep D_80103DF8[] = {
    { 0x54000001 },
};

union AnimationStep D_80103DFC[] = {
    { 0x55000001 },
};

union AnimationStep D_80103E00[] = {
    { 0x56000001 },
};

union AnimationStep D_80103E04[] = {
    { 0x57000001 },
};

void* D_80103E08[29] = {
    D_80103C8C,
    D_80103C90,
    D_80103C9C,
    D_80103CB0,
    D_80103CBC,
    D_80103CC8,
    D_80103CD4,
    D_80103CE0,
    D_80103CEC,
    D_80103CF8,
    D_80103D04,
    D_80103D10,
    D_80103D1C,
    D_80103D28,
    D_80103D34,
    D_80103D40,
    D_80103D4C,
    D_80103D58,
    D_80103D64,
    D_80103D70,
    D_80103D80,
    D_80103D94,
    D_80103DC4,
    D_80103DF0,
    D_80103DF4,
    D_80103DF8,
    D_80103DFC,
    D_80103E00,
    D_80103E04,
};

struct Unk_unk68 D_80103E7C[2] = {
    { 23, 24, 25, 26 },
    { 27, 28, 0, 0 },
};

void (*D_80103E84[3])() = {
    func_80082470,
    func_80082574,
    func_800826C8,
};

void (*D_80103E90[7])() = {
    func_8009216C,
    func_8008286C,
    func_80082878,
    func_800829EC,
    func_80082B2C,
    func_80082CC4,
    func_80082D9C,
};

void (*D_80103EAC[3])(struct MainObj*, s32) = {
    func_80082710,
    func_80082784,
    func_8008284C,
};

void (*D_80103EB8[1])() = {
    func_800828B4,
};

void (*D_80103EBC[2])() = {
    func_80082A28,
    func_80082AA8,
};

void (*D_80103EC4[4])() = {
    func_80082B68,
    func_80082BA4,
    func_80082C04,
    func_80082C70,
};

void (*D_80103ED4[2])() = {
    func_80082D00,
    func_80082D48,
};

void (*D_80103EDC[2])() = {
    func_80082DD8,
    func_80082E30,
};
