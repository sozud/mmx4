// MainObj, main_object_update_funcs[51]
// 80069A94..8006A50C
#include "common.h"

void func_8006A450(struct MainObj* arg0);

void func_80069A94(struct MainObj* arg0)
{
    D_800FFD84[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_80069AD0);

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_80069BE4);

void func_80069CE4(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_800BF60C(BASE_OBJECT(arg0), 8);
        arg0->state++;
    } else if (--arg0->unk7E == 0) {
        func_800AF878(BASE_OBJECT(arg0), 1, 0x20, 0x20);
        arg0->unk7E = 5;
    }
}

void func_80069D74(struct MainObj* arg0)
{
    func_8002B0C8(OBJECT_HEADER(arg0));
}

void func_80069D94(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_51.saved_unk5;
}

void func_80069DA0(struct MainObj* arg0)
{
    D_800FFDB0[arg0->unk6](arg0);
}

void func_80069DDC(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}

void func_80069E28(struct MainObj* arg0)
{
    D_800FFDB4[arg0->unk6](arg0);
}

void func_80069E64(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (engine_obj.cur_character != (arg0->ext.main_51.unk84 & 1)) {
        func_80015D60(arg0, 2);
    } else {
        func_80015D60(arg0, 1);
    }
    func_8001540C(2, 0xA1, arg0);
    if (arg0->unk2 == 0 && arg0->ext.main_51.unk84 == 2 && engine_obj.cur_character == 0) {
        func_8006A388(arg0);
    } else {
        func_8006A2BC(arg0);
    }
    arg0->unk7C = 0x4B;
    arg0->unk6++;
}

INCLUDE_ASM("main/nonmatchings/mains/main_51", func_80069F28);

void func_80069FDC(struct MainObj* arg0)
{
    D_800FFDBC[arg0->unk6](arg0);
}

void func_8006A018(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 5);
        arg0->unk7C = 0x29;
        arg0->unk6++;
    }
}

void func_8006A078(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_8001540C(2, 0xA2, arg0);
        func_8006A450(arg0);
        arg0->unk7C = 0x3C;
        arg0->unk6++;
    }
}

void func_8006A0E4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}

void func_8006A130(struct MainObj* arg0)
{
    D_800FFDC8[arg0->unk6](arg0);
}

void func_8006A16C(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 6);
    arg0->unk7C = 0x1A;
    arg0->unk6++;
}

void func_8006A1B4(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk7C = 0x28U;
    }
}

void func_8006A208(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->unk70 & 8) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk2C = 0;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 0;
    } else {
        func_8002B694(ANIMATED_OBJECT(arg0));
    }
}

void func_8006A26C(struct MainObj* arg0)
{
    if (arg0->unk67 == 0 && !(arg0->unk70 & 8)) {
        arg0->unk5 = 6;
        arg0->unk2C = FIXED(0.2578125);
        arg0->unk6 = 0;
        arg0->unk24 = 0;
        arg0->unk20 = 0;
        arg0->unk28 = 0;
        arg0->unk67 = 1;
    }
}

void func_8006A2BC(struct MainObj* arg0)
{
    struct MainObj* source;
    s8 side;
    struct ShotObj* shot;

    source = arg0;
    shot = find_free_shot_obj();
    if (shot != 0) {
        shot->active = 0x41;
        shot->id = 0x1E;
        side = engine_obj.cur_character ^ (source->ext.main_51.unk84 & 1);
        shot->unk2 = side;
        if ((source->ext.main_51.unk84 == 3) && (engine_obj.cur_character == 0)) {
            shot->unk2 = side + 1;
        }
        shot->unk7C = (struct WeaponObj*)source;
        shot->unk42 = source->unk42;
        shot->animation_table = (u32**)D_800FFD44;
        shot->unk3C = source->sprite_frames;
        shot->unk40 = source->unk40;
        shot->unk15 = source->unk15;
        shot->bg_offset = (s8)(u8)source->bg_offset;
        shot->unk16 = 4;
    }
}

void func_8006A388(struct MainObj* arg0)
{
    u8 i;
    struct MainObj* obj;
    struct ShotObj* shot;

    obj = arg0;
    i = 0;
    do {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x1E;
            if (i == 0) {
                shot->unk2 = 0;
            } else {
                shot->unk2 = 2;
            }
            shot->unk7C = (struct WeaponObj*)obj;
            shot->unk42 = obj->unk42;
            shot->animation_table = (u32**)D_800FFD44;
            shot->unk3C = obj->sprite_frames;
            shot->unk40 = obj->unk40;
            shot->unk15 = obj->unk15;
            shot->bg_offset = (s8)(u8)obj->bg_offset;
            shot->unk16 = 4;
        }
        i++;
    } while (i < 2);
}

void func_8006A450(struct MainObj* arg0)
{
    u8 i;
    struct ShotObj* shot;

    i = 0;
    do {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x1D;
            shot->unk2 = i;
            shot->unk7C = WEAPON_OBJECT(arg0);
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)D_800FFD44;
            shot->unk3C = (u8*)arg0->sprite_frames;
            shot->unk40 = arg0->unk40;
            shot->unk15 = arg0->unk15;
            shot->bg_offset = arg0->bg_offset;
            shot->unk16 = 4;
        }
        i++;
    } while (i < 2);
}
