// WeaponObj, weapon_object_update_funcs[8]
// 80097860..80097EEC
#include "common.h"

void twin_slasher_update(struct WeaponObj* arg0)
{
    s32 should_reset = 0;

    if (g_Player.input_locked != 0) {
        should_reset = 1;
    }
    if (g_Player.capsule_state != 0) {
        should_reset = 1;
    }
    if (g_Player.weapon != 8) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    twin_slasher_state_funcs[arg0->state](arg0);
}

// twin_slasher_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_08_twin_slasher", func_800978DC);

void twin_slasher_main(struct WeaponObj* arg0)
{
    if ((func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) && (arg0->unk98 == 0)) {
        if (arg0->ext.weapon_8.timer != 0) {
            arg0->ext.weapon_8.timer--;
            animate_object(ANIMATED_OBJECT(arg0));
            move_object(MOVING_OBJECT(arg0));
            arg0->unk50 = (const u8*)&twin_slasher_hit_boxes[arg0->animation_step.fields.event];
            update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
            return;
        }
    }

    twin_slasher_hide(arg0);
}

void twin_slasher_despawn(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.shot_count--;
    g_Player.special_shot_count--;
    ZeroObjectState((struct ObjectHeader*)arg0);
}

void twin_slasher_hide(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
}

// WeaponObj, weapon_object_update_funcs[17]

void twin_slasher_charged_update(struct WeaponObj* arg0)
{
    s32 should_reset = 0;

    if (g_Player.input_locked != 0) {
        should_reset = 1;
    }
    if (g_Player.capsule_state != 0) {
        should_reset = 1;
    }
    if (g_Player.weapon != 8) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    twin_slasher_charged_state_funcs[arg0->state](arg0);
}

// twin_slasher_charged_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_08_twin_slasher", func_80097BA4);

void twin_slasher_charged_main(struct WeaponObj* arg0)
{
    struct MiscObj* misc_obj;
    u8 timer;
    struct Weapon17Ext* weapon_17 = &arg0->ext.weapon_17;

    if (func_8002B1E8((struct BaseObj*)arg0, 0x20, 0x20) == 0) {
        timer = weapon_17->timer;
        if (timer == 0) {
            weapon_17->timer = 3;
            misc_obj = find_free_misc_obj();
            if (misc_obj != 0) {
                misc_obj->active = 1;
                misc_obj->id = 0x29;
                misc_obj->unk2 = ((s8)arg0->unk2) >> 1;
                misc_obj->bg_offset = arg0->bg_offset;
                misc_obj->x_pos.val = arg0->x_pos.val;
                misc_obj->y_pos.val = arg0->y_pos.val;
                misc_obj->unk15 = arg0->unk15;
            }
        } else {
            weapon_17->timer = timer - 1;
        }
        animate_object((struct AnimatedObj*)arg0);
        move_object((struct MovingObj*)arg0);
        update_on_screen((struct BaseObj*)arg0, 0x20, 0x20);
        return;
    }
    twin_slasher_hide(arg0);
}

// twin_slasher_trail_update
INCLUDE_ASM("main/nonmatchings/weapons/weapon_08_twin_slasher", func_80097DD8);

struct Unk_unk68 twin_slasher_hit_boxes[] = {
    { -8, -12, 0x14, 0x18 },
    { -12, -16, 0x1C, 0x22 },
    { -14, -20, 0x26, 0x2C },
    { -8, -14, 0x14, 0x18 },
    { -12, -20, 0x1C, 0x22 },
    { -14, -26, 0x26, 0x2C },
};

struct Unk_unk68 twin_slasher_charged_hit_boxes[] = {
    { -16, -16, 0x26, 0x26 },
    { -16, -18, 0x26, 0x26 },
    { -16, -20, 0x26, 0x26 },
    { -16, -22, 0x26, 0x26 },
};

void (*twin_slasher_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_800978DC,
    (void (*)(struct WeaponObj*))twin_slasher_main,
    (void (*)(struct WeaponObj*))twin_slasher_despawn,
    (void (*)(struct WeaponObj*))twin_slasher_despawn,
};

void (*twin_slasher_charged_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80097BA4,
    (void (*)(struct WeaponObj*))twin_slasher_charged_main,
    (void (*)(struct WeaponObj*))twin_slasher_despawn,
    (void (*)(struct WeaponObj*))twin_slasher_despawn,
};

u8 twin_slasher_charged_angles[] = {
    0x04,
    0x03,
    0x02,
    0x01,
    0x1F,
    0x1E,
    0x1D,
    0x1C,
};
