// WeaponObj, weapon_object_update_funcs[0, 12, 23, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55]
// 800922D8..80092648
#include "common.h"

void func_800922D8(struct WeaponObj* arg0)
{
    D_80108728[arg0->state](arg0);
}

void func_80092314(struct WeaponObj* arg0)
{
    struct PlayerObj* owner;

    arg0->active = 0x21;
    arg0->on_screen = 1;
    arg0->unk50 = (const u8*)D_80108704;
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 1);
    arg0->animation_table = D_8011BF40;
    arg0->unk42 = 0x7802;
    arg0->unk40 = 0;
    arg0->unk16 = 0;
    owner = arg0->owner;
    arg0->unk15 = owner->unk15;
    arg0->unk84.word = 0;
    func_80092CEC(WEAPON_OBJECT(arg0));
    arg0->x_pos.i.lo = 0;
    arg0->y_pos.i.lo = 0;
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(6.75);
    } else {
        arg0->x_vel.val = FIXED(-6.75);
    }
    arg0->unk28 = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    func_80015D60(arg0, 0x15);
    func_8001540C(1, 8, arg0);
    arg0->state++;
    func_8002B318(BASE_OBJECT(arg0), 0xC, 8);
}

void func_80092408(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0xC, 8) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        if (arg0->unk98 == 0) {
            func_80092490(ANIMATED_OBJECT(arg0));
            func_8002B318(BASE_OBJECT(arg0), 0xC, 8);
            return;
        }
        func_800924F8(arg0);
        return;
    }
    func_80092600(arg0);
}

void func_80092490(struct AnimatedObj* arg0)
{
    if (arg0->unk5 == 0) {
        func_80092CEC(WEAPON_OBJECT(arg0));
        if (arg0->animation_step.fields.event != 0) {
            arg0->animation_step.fields.event = 0;
            arg0->unk5++;
        }
    } else {
        func_8002B718(MOVING_OBJECT(arg0));
    }
}
void func_800924F8(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    if (arg0->unk98 > 0) {
        func_80092600(arg0);
        return;
    }
    arg0->x_vel.val = -arg0->x_vel.val;
    if (get_random() & 1) {
        arg0->y_vel.val = FIXED(4.05) - 1;
    } else {
        arg0->y_vel.val = -(FIXED(4.05) - 1);
    }

    arg0->state = 2;
    arg0->unk5 = 0;
    arg0->unk15 ^= 0x40;
    func_8002B318(BASE_OBJECT(arg0), 0xC, 8);
}

void func_80092598(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0xC, 8) == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        func_8002B718(MOVING_OBJECT(arg0));
        func_8002B318(BASE_OBJECT(arg0), 0xC, 8);
        return;
    }
    func_80092600(arg0);
}

void func_80092600(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
}

void func_80092614(struct WeaponObj* arg0)
{
    struct PlayerObj* owner;

    owner = arg0->owner;
    arg0->unk50 = 0;
    owner->unk98--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_80108728[])(struct WeaponObj*) = {
    func_80092314,
    func_80092408,
    func_80092598,
    func_80092614,
};
