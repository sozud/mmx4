// WeaponObj, weapon_object_update_funcs[19]
// 800927EC..800929A0
#include "common.h"

void func_800927EC(struct WeaponObj* arg0)
{
    D_80108748[arg0->state](arg0);
}

void func_80092828(struct WeaponObj* arg0)
{
    struct PlayerObj* owner;

    arg0->active = 0x21;
    arg0->on_screen = 1;
    arg0->unk50 = (const u8*)D_80108718;
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 1);
    arg0->animation_table = D_8011BF40;
    arg0->unk42 = 0x7802;
    arg0->unk40 = 0;
    arg0->unk16 = 1;
    owner = arg0->owner;
    arg0->unk15 = owner->unk15;
    arg0->unk84.word = 0;
    func_80092CEC(WEAPON_OBJECT(arg0));
    arg0->x_pos.i.lo = 0;
    arg0->y_pos.i.lo = 0;
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(10);
    } else {
        arg0->x_vel.val = FIXED(-10);
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    func_80015D60(arg0, 0x18);
    func_8001540C(1, 9, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    func_8002B318(BASE_OBJECT(arg0), 0x1A, 0x12);
}

void func_80092918(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x1A, 0x12) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->unk98 == 0) {
            func_80092490(ANIMATED_OBJECT(arg0));
            func_8002B318(BASE_OBJECT(arg0), 0x1A, 0x12);
            return;
        }
        func_80092600(arg0);
        return;
    }
    arg0->on_screen = 0;
    arg0->state = 3;
}

void (*D_80108748[])(struct WeaponObj*) = {
    func_80092828,
    func_80092918,
    func_80092614,
    func_80092614,
};
