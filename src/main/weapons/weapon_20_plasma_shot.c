#include "common.h"

void plasma_shot_update(struct WeaponObj* arg0)
{
    plasma_shot_state_funcs[arg0->state](arg0);
}

// plasma_shot_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_20_plasma_shot", func_800929DC);

void plasma_shot_main(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x2A, 0x22) == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        if (arg0->id == 0x14) {
            func_80092B5C(arg0);
            return;
        }
        plasma_orb_linger(arg0);
        return;
    }
    buster_shot_hide(arg0);
}

// plasma_shot_move
INCLUDE_ASM("main/nonmatchings/weapons/weapon_20_plasma_shot", func_80092B5C);

void plasma_orb_linger(struct WeaponObj* arg0)
{
    u8 timer;
    u8 sub_timer;

    if (arg0->unk5 == 0) {
        struct Weapon20Ext* ext = &arg0->ext.weapon_20;

        timer = arg0->ext.weapon_20.lifetime;
        if (timer == 0) {
            set_animation(arg0, 0x1F);
            arg0->unk50 = 0;
            arg0->unk5 = 1;
        } else {
            ext->lifetime = timer - 1;
            sub_timer = ext->timer;
            if (sub_timer == 0) {
                ext->timer = 4;
                arg0->unk64 = (u8)arg0->unk64 + 1;
            } else {
                ext->timer = sub_timer - 1;
            }
        }
    } else if (arg0->animation_step.fields.relative_step == 0) {
        buster_shot_hide(arg0);
        return;
    }

    update_on_screen(BASE_OBJECT(arg0), 0x2A, 0x22);
}

void buster_shot_follow_muzzle(struct WeaponObj* arg0)
{
    struct PlayerObj* owner;

    if (arg0->unk84.word == 0) {
        owner = arg0->owner;
        if (owner->attacking == 0) {
            arg0->unk84.word = 1;
        }
        if (owner->unk15 != arg0->unk15) {
            arg0->unk84.word = 1;
        }
        if (arg0->unk84.word == 0) {
            buster_shot_place_at_muzzle(VISUAL_OBJECT(arg0), owner, arg0->id);
        }
    }
}

void (*plasma_shot_state_funcs[])(struct WeaponObj*) = {
    func_800929DC,
    plasma_shot_main,
    player_shot_despawn,
    player_shot_despawn,
};
