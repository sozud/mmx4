// WeaponObj, weapon_object_update_funcs[9, 18]
// 80092648..800927EC
#include "common.h"
#include "main/weapons/weapon_00_lemon.h"
#include "main/weapons/weapon_09_charge_shot.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

// charge_shot_state_funcs
extern void (*charge_shot_state_funcs[])(struct WeaponObj*);

void charge_shot_main(struct WeaponObj*);

extern struct Unk_unk68 D_80108708[];

#include "weapon_resources.h"

void charge_shot_update(struct WeaponObj* arg0)
{
    charge_shot_state_funcs[arg0->state](arg0);
}

// charge_shot_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80092684(struct WeaponObj* arg0);
extern struct Unk_unk68 D_80108708[];
#endif

void func_80092684(struct WeaponObj* arg0)
{
    arg0->on_screen = 1;
#ifdef VERSION_DEMO
    if (arg0->id == 9)
        arg0->unk2 = 0;
    if (arg0->id == 0x12)
        arg0->unk2 = 1;
    if (arg0->id == 0x13)
        arg0->unk2 = 2;
    if (arg0->id == 0x14)
        arg0->unk2 = 3;
    arg0->unk50 = (const u8*)&D_80108708[arg0->unk2];
    if (arg0->id == 9)
        arg0->x_vel.val = FIXED(8);
    else
        arg0->x_vel.val = FIXED(10);
#else
    if (arg0->id == 9) {
        arg0->unk2 = 0;
        arg0->x_vel.val = FIXED(8);
    } else {
        arg0->unk2 = 1;
        arg0->x_vel.val = FIXED(10);
    }
    arg0->unk50 = (const u8*)&D_80108708[arg0->unk2];
#endif
    if (arg0->unk15 == 0) {
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    set_animation(arg0, arg0->unk2 + 0x1A);
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x14);
}

void charge_shot_main(struct WeaponObj* arg0)
{
#ifdef VERSION_DEMO
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x14) == 0) {
        animate_object(arg0);
        if (arg0->unk98 == 0) {
            move_object(MOVING_OBJECT(arg0));
            update_on_screen(BASE_OBJECT(arg0), 0x20, 0x14);
            return;
        }
        arg0->unk50 = 0;
    }
    arg0->on_screen = 0;
    arg0->state = 3;
#else
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x14) == 0 && arg0->unk98 == 0) {
        animate_object(arg0);
        move_object(MOVING_OBJECT(arg0));
        update_on_screen(BASE_OBJECT(arg0), 0x20, 0x14);
        return;
    }
    buster_shot_hide(arg0);
#endif
}

void player_shot_despawn(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.shot_count--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*charge_shot_state_funcs[])(struct WeaponObj*) = {
    func_80092684,
    charge_shot_main,
    player_shot_despawn,
    player_shot_despawn,
};

#ifdef VERSION_DEMO
struct Unk_unk68 D_80108708[] = {
    { -13, -7, 0x1D, 0xD },
    { -34, -19, 0x40, 0x24 },
    { -24, -17, 0x2C, 0x20 },
    { -34, -19, 0x40, 0x24 },
};
#endif
