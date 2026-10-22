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

void charge_shot_update(struct WeaponObj* arg0)
{
    charge_shot_state_funcs[arg0->state](arg0);
}

// charge_shot_init
#ifdef MMX4_PC
void func_80092684(struct WeaponObj* arg0);
extern struct Unk_unk68 D_80108708[];
#endif

#ifdef MMX4_PC
void func_80092684(struct WeaponObj* arg0)
{
    s32 velocity;

    arg0->on_screen = 1;
    if (arg0->id == 9) {
        velocity = FIXED(8);
        arg0->unk2 = 0;
    } else {
        velocity = FIXED(10);
        arg0->unk2 = 1;
    }
    arg0->x_vel.val = velocity;
    arg0->unk50 = (const u8*)&D_80108708[arg0->unk2];
    if (arg0->unk15 == 0) {
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    set_animation(arg0, arg0->unk2 + 0x1A);
    arg0->state = (u8)arg0->state + 1;
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x14);
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_09_charge_shot", func_80092684);
#endif

void charge_shot_main(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x14) == 0 && arg0->unk98 == 0) {
        animate_object(arg0);
        move_object(MOVING_OBJECT(arg0));
        update_on_screen(BASE_OBJECT(arg0), 0x20, 0x14);
        return;
    }
    buster_shot_hide(arg0);
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
