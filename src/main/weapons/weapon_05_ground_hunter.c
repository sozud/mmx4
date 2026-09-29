// WeaponObj, weapon_object_update_funcs[5]
// 800957B0..800961B0
#include "common.h"

void ground_hunter_update(struct WeaponObj* arg0)
{
    s32 shouldSetState;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    shouldSetState = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        shouldSetState = 1;
    }
    if (g_Player.weapon != 5) {
        shouldSetState = 1;
    }
    if (shouldSetState != 0) {
        arg0->state = 3;
    }

    ground_hunter_state_funcs[arg0->state](arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
}

// ground_hunter_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_05_ground_hunter", func_80095854);

void ground_hunter_main(struct WeaponObj* arg0)
{
    if ((func_8002B1E8(BASE_OBJECT(arg0), 0x2C, 0x20) == 0) && (arg0->unk98 == 0)) {
        animate_object(ANIMATED_OBJECT(arg0));
        ground_hunter_step_funcs[arg0->unk5](arg0);
        if (arg0->unk50 != 0) {
            if (arg0->unk17 == 2) {
                arg0->unk50 = ground_hunter_rise_box;
                return;
            }
            arg0->unk50 = ground_hunter_crawl_box;
        }
    } else {
        ground_hunter_hide(arg0);
    }
}

void ground_hunter_fly(struct WeaponObj* arg0)
{
    if (ground_hunter_check_wall(arg0) == 0) {
        if (g_Player.input.buttons.held & 8) {
            ground_hunter_start_rise(arg0);
        }
        if (arg0->unk70 & 8) {
            ground_hunter_start_crawl(arg0);
        }
        move_object(MOVING_OBJECT(arg0));
        update_on_screen(BASE_OBJECT(arg0), 0x2C, 0x20);
    }
}

void ground_hunter_rise(struct WeaponObj* arg0)
{
    if (ground_hunter_check_wall(arg0) == 0) {
        if ((arg0->unk70 & 8) == 0) {
            ground_hunter_start_rise(arg0);
        }
        move_object(MOVING_OBJECT(arg0));
        update_on_screen(BASE_OBJECT(arg0), 0x2C, 0x20);
    }
}

void ground_hunter_crawl(struct WeaponObj* arg0)
{
    s32 mask;
    u32 flags;

    mask = 2;
    if (arg0->unk15 != 0) {
        mask = 1;
    }
    flags = arg0->unk70;
    if (flags & 8) {
        if (mask & flags) {
            ground_hunter_start_burst(arg0);
        } else {
            ground_hunter_start_crawl(arg0);
        }
    }
    move_object(MOVING_OBJECT(arg0));
    update_on_screen(BASE_OBJECT(arg0), 0x2C, 0x20);
}

void ground_hunter_burst(struct WeaponObj* arg0)
{
    animate_object(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        ground_hunter_hide(arg0);
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x2C, 0x20);
}

void ground_hunter_despawn(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    arg0->unk68 = 0;
    g_Player.shot_count--;
    g_Player.special_shot_count--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

s32 ground_hunter_check_wall(struct WeaponObj* arg0)
{
    s32 mask;
    u32 flags;

    mask = 2;
    if (arg0->unk15 != 0) {
        mask = 1;
    }
    flags = arg0->unk70;
    if (mask & flags) {
        if (flags & 8) {
            ground_hunter_start_burst(arg0);
        } else {
            ground_hunter_start_rise(arg0);
        }
        update_on_screen(BASE_OBJECT(arg0), 0x2C, 0x20);
        return 1;
    }
    return 0;
}

void ground_hunter_start_crawl(struct WeaponObj* arg0)
{
    set_animation(arg0, 1);
    arg0->unk67 = 0;
    if (arg0->unk15 != 0) {
        arg0->x_vel.val = FIXED(6);
    } else {
        arg0->x_vel.val = FIXED(-6);
    }
    arg0->y_vel.val = 0;
    arg0->unk5 = 1;
}

void ground_hunter_start_rise(struct WeaponObj* arg0)
{
    set_animation(arg0, 2);
    arg0->unk67 = 1;
    arg0->y_vel.val = -FIXED(6);
    arg0->x_vel.val = 0;
    arg0->unk5 = 2;
}

void ground_hunter_start_burst(struct WeaponObj* arg0)
{
    set_animation(arg0, 6);
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk50 = 0;
    arg0->unk68 = 0;
    arg0->state = 2;
    arg0->unk5 = 0;
}

void ground_hunter_hide(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
    arg0->unk68 = 0;
}

// WeaponObj, weapon_object_update_funcs[14]

void ground_hunter_charged_update(struct WeaponObj* arg0)
{
    s32 should_reset = g_Player.input_locked != 0;

    if (g_Player.capsule_state != 0) {
        should_reset = 1;
    }
    if (g_Player.weapon != 5) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    ground_hunter_charged_state_funcs[arg0->state](arg0);
}

// ground_hunter_charged_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_05_ground_hunter", func_80095E3C);

void ground_hunter_charged_main(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x2C, 0x18) == 0) {
        animate_object(arg0);
        move_object(MOVING_OBJECT(arg0));
        ground_hunter_charged_step_funcs[arg0->unk5](arg0);
        return;
    }

    ground_hunter_hide(arg0);
}

void ground_hunter_charged_wait_fire(struct WeaponObj* arg0)
{
    if (g_Player.input.buttons.held & 0xC) {
        arg0->ext.weapon_14.unk8D = 5;
        arg0->ext.weapon_14.unk8C = 0;
        arg0->unk5 = 1;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x2C, 0x18);
}

// ground_hunter_charged_fire
INCLUDE_ASM("main/nonmatchings/weapons/weapon_05_ground_hunter", func_80096060);

void ground_hunter_charged_shot_fly(struct WeaponObj* arg0)
{
    if (arg0->unk98 != 0) {
        ground_hunter_hide(arg0);
        return;
    }

    update_on_screen(BASE_OBJECT(arg0), 0x2C, 0x18);
}

struct Unk_unk68 ground_hunter_crawl_box[] = {
    { -16, -8, 0x22, 0xE },
};

struct Unk_unk68 ground_hunter_rise_box[] = {
    { -10, -16, 0x12, 0x1C },
};

struct Unk_unk68 ground_hunter_terrain_box[] = {
    { 0, 0, 8, 6 },
};

struct Unk_unk68 ground_hunter_charged_hit_box[] = {
    { -24, -12, 0x3E, 0x18 },
};

struct Unk_unk68 ground_hunter_charged_shot_box[] = {
    { -10, -16, 0x12, 0x22 },
};

void (*ground_hunter_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80095854,
    (void (*)(struct WeaponObj*))ground_hunter_main,
    (void (*)(struct WeaponObj*))ground_hunter_burst,
    (void (*)(struct WeaponObj*))ground_hunter_despawn,
};

void (*ground_hunter_step_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))ground_hunter_fly,
    (void (*)(struct WeaponObj*))ground_hunter_rise,
    (void (*)(struct WeaponObj*))ground_hunter_crawl,
};

void (*ground_hunter_charged_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80095E3C,
    (void (*)(struct WeaponObj*))ground_hunter_charged_main,
    (void (*)(struct WeaponObj*))ground_hunter_burst,
    (void (*)(struct WeaponObj*))ground_hunter_despawn,
};

void (*ground_hunter_charged_step_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))ground_hunter_charged_wait_fire,
    (void (*)(struct WeaponObj*))func_80096060,
    (void (*)(struct WeaponObj*))ground_hunter_charged_shot_fly,
};
