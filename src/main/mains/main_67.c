// MainObj, main_object_update_funcs[67]
// 80082434..80083218
#include "common.h"

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

void func_80082710(struct MainObj* arg0)
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

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082784);

void func_8008284C(struct MainObj* arg0)
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

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_80082FEC);

INCLUDE_ASM("main/nonmatchings/mains/main_67", func_800830D0);

s32 func_8008318C(struct MainObj* arg0, s32 arg1, s32 arg2)
{
    POS_BOUNDS_CHECK_FAIL_RET0(arg0->x_pos.val, arg1)
    POS_BOUNDS_CHECK_FAIL_RET0(arg0->y_pos.val, arg2)
    return 1;
}
