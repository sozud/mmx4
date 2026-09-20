// MainObj, main_object_update_funcs[38]
// 80060A88..80061590
#include "common.h"

void func_80060A88(struct MainObj* arg0)
{
    D_800FE8EC[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060AC4);

INCLUDE_ASM("main/nonmatchings/mains/main_38", func_80060BC4);

void func_80060D3C(struct MainObj* arg0)
{
    if (--arg0->unk7C == 0) {
        func_800BF60C(BASE_OBJECT(arg0), 8);
        arg0->state++;
    }
    if (--arg0->unk7E == 0) {
        func_800AF878(BASE_OBJECT(arg0), 0, 0x18, 0x10);
        arg0->unk7E = 5;
    }
}

void func_80060DC8(struct MainObj* arg0)
{
    arg0->ext.main_38.unk88 = 2;
    if (arg0->ext.main_38.unk8C != 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
    } else {
        func_8002B0C8(OBJECT_HEADER(arg0));
    }
}

void func_80060E08(struct MainObj* arg0)
{
    arg0->unk5 = arg0->ext.main_38.saved_unk5;
}

void func_80060E14(struct MainObj* arg0)
{
    D_800FE918[arg0->unk6](arg0);
}

void func_80060E50(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(ANIMATED_OBJECT(arg0), 0);
    arg0->unk6++;
}

void func_80060E94(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7E == 0) {
        switch (arg0->ext.main_38.unk84) {
        case 0:
            arg0->unk5 = 3;
            arg0->unk7E = 0x14;
            break;
        case 1:
            arg0->unk5 = 5;
            arg0->unk7E = 0x14;
            break;
        case 2:
            arg0->unk5 = 5;
            arg0->unk7E = 0xA;
            break;
        }
        arg0->unk6 = 0;
        if (arg0->ext.main_38.unk84 != 2) {
            arg0->ext.main_38.unk84++;
        } else {
            arg0->ext.main_38.unk84 = 0;
        }
    }
}

void func_80060F5C(struct MainObj* arg0)
{
    D_800FE920[arg0->unk6](arg0);
}

void func_80060F98(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_80015D60(arg0, 1);
    func_8001540C(2, 0x60, arg0);
    func_800614E8(VISUAL_OBJECT(arg0));
    arg0->unk7C = 0x50;
    arg0->unk6++;
}

void func_80060FF8(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 4;
        arg0->ext.main_38.unk88 = 1;
        arg0->unk6 = 0;
    }
}

void func_8006104C(struct MainObj* arg0)
{
    D_800FE928[arg0->unk6](arg0);
}

void func_80061088(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 0x61, arg0);
    func_80015D60(arg0, 2);
    arg0->ext.main_38.unk88 = 2;
    func_8006135C(arg0);
    arg0->unk7C = 0x6E;
    arg0->unk6++;
}

void func_800610F0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80015D60(arg0, 0);
        arg0->ext.main_38.unk88 = 0;
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_8006114C(struct MainObj* arg0)
{
    D_800FE930[arg0->unk6](arg0);
}

void func_80061188(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8001540C(2, 0x62, arg0);
    func_80015D60(arg0, 5);
    arg0->unk7C = 0xA;
    arg0->unk6++;
}

void func_800611E0(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C == 0) {
        func_80061424(arg0);
        arg0->unk7C = 0x14;
        arg0->unk6++;
    }
}

void func_80061240(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 6;
        arg0->unk6 = 0;
    }
}

void func_8006128C(struct MainObj* arg0)
{
    D_800FE93C[arg0->unk6](arg0);
}

void func_800612C8(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    func_80015D60(arg0, 6);
    arg0->unk7C = 0x28;
    arg0->unk6++;
}

void func_80061310(struct MainObj* arg0)
{
    func_80015DC8((struct AnimatedObj*)arg0);
    if (--arg0->unk7C == 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
    }
}

void func_8006135C(struct PlayerObj* arg0)
{
    s32 is_zero;
    struct ShotObj* shot;
    u8 i;
    for (i = 0; i < 2; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x14;
            shot->unk2 = i;
            shot->unk7C = WEAPON_OBJECT(arg0);
            shot->unk42 = arg0->unk42;
            shot->animation_table = D_800FE890;
            shot->unk3C = arg0->unk3C;
            shot->unk40 = arg0->unk40;
            shot->unk15 = arg0->unk15;
            shot->bg_offset = arg0->bg_offset;
            is_zero = (arg0->unk2 == 0);
            shot->unk16 = is_zero ? 2 : 1;
        }
    }
}

void func_80061424(struct MainObj* arg0)
{
    s32 is_zero;
    struct ShotObj* shot;
    u8 i;
    for (i = 0; i < 2; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x15;
            shot->unk2 = i;
            shot->unk7C = WEAPON_OBJECT(arg0);
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)D_800FE890;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->unk40 = arg0->unk40;
            shot->unk15 = arg0->unk15;
            shot->bg_offset = arg0->bg_offset;
            is_zero = (i == 0);
            shot->unk16 = is_zero ? 4 : 6;
        }
    }
}

void func_800614E8(struct VisualObj* arg0)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x10;
        obj->unk2 = 0;
        obj->unk50 = (struct PlayerObj*)arg0;
        obj->unk42 = arg0->unk42;
        obj->animation_table = D_800FE890;
        obj->unk3C = arg0->unk3C;
        obj->unk40 = arg0->unk40;
        obj->bg_offset = arg0->bg_offset;
        obj->unk16 = 4;
        obj->unk15 = arg0->unk15;
        obj->x_pos.val = arg0->x_pos.val;
        obj->y_pos.val = arg0->y_pos.val;
    }
}
