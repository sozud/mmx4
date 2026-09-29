// WeaponObj, weapon_object_update_funcs[7]
// 80096E10..80097860
#include "common.h"

void double_cyclone_update(struct WeaponObj* arg0)
{
    s32 disabled;

    disabled = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        disabled = 1;
    }
    if (g_Player.weapon != 7) {
        disabled = 1;
    }
    if (g_Player.shot_type == 0x10) {
        disabled = 1;
    }
    if (disabled != 0) {
        arg0->state = 3;
    }
    double_cyclone_state_funcs[arg0->state](arg0);
}

// double_cyclone_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80096EA4);

void double_cyclone_main(struct WeaponObj* arg0)
{
    u8 temp_v0;

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        double_cyclone_step_funcs[arg0->unk5](arg0);
        if (arg0->unk50 != 0) {
            temp_v0 = arg0->ext.weapon_7.unk91;
            if (temp_v0 == 0) {
                arg0->ext.weapon_7.unk91 = 4;
                arg0->unk64++;
                return;
            }
            arg0->ext.weapon_7.unk91 = temp_v0 - 1;
        }
    } else {
        double_cyclone_hide(arg0);
    }
}

void double_cyclone_form(struct WeaponObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.relative_step == 0) {
        set_animation(arg0, 1);
        arg0->unk5++;
    }
    double_cyclone_draw(arg0);
}

void double_cyclone_fly(struct WeaponObj* arg0)
{
    if (double_cyclone_check_expired(arg0) == 0) {
        if (arg0->unk98 != 0) {
            arg0->unk98 = 0;
            arg0->unk5++;
        } else {
            if (arg0->ext.weapon_7.unk90 != 0) {
                arg0->ext.weapon_7.unk90--;
                if (arg0->ext.weapon_7.unk90 == 0) {
                    arg0->unk2C = FIXED(-0.21484375);
                }
            }
            animate_object(ANIMATED_OBJECT(arg0));
            move_with_gravity(ANIMATED_OBJECT(arg0));
        }
        double_cyclone_draw(arg0);
    }
}

void double_cyclone_spin(struct WeaponObj* arg0)
{
    if (double_cyclone_check_expired(arg0) == 0) {
        animate_object(arg0);
        double_cyclone_draw(arg0);
    }
}

s32 double_cyclone_check_expired(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_7.timer == 0) {
        set_animation(arg0, 2);
        arg0->unk50 = 0;
        arg0->unk5 = 3;
        double_cyclone_draw(arg0);
        return 1;
    }

    arg0->ext.weapon_7.timer--;
    return 0;
}

void double_cyclone_dissipate(struct WeaponObj* arg0)
{
    animate_object(arg0);
    if (arg0->animation_step.fields.relative_step == 0) {
        double_cyclone_hide(arg0);
    } else {
        double_cyclone_draw(arg0);
    }
}

void double_cyclone_hide(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
}

void double_cyclone_despawn(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    g_Player.shot_count--;
    g_Player.special_shot_count--;
    ZeroObjectState((struct ObjectHeader*)arg0);
}

void double_cyclone_draw(struct WeaponObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    } else {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x30);
    }
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}

// WeaponObj, weapon_object_update_funcs[16]

void double_cyclone_charged_update(struct WeaponObj* arg0)
{
    s32 var_a1;

    var_a1 = g_Player.input_locked != 0;
    if (g_Player.capsule_state != 0) {
        var_a1 = 1;
    }
    if (g_Player.weapon != 7) {
        var_a1 = 1;
    }
    if (g_Player.actions_reset != 0) {
        var_a1 = 1;
    }
    if (g_Player.hp == 0) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        arg0->state = 3;
    }
    double_cyclone_charged_state_funcs[arg0->state](arg0);
}

// double_cyclone_charged_init
INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80097430);

void double_cyclone_charged_main(struct WeaponObj* arg0)
{
    if (double_cyclone_charged_check_expired(arg0) == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        if (func_8002B1E8(BASE_OBJECT(arg0), 0x18, 0x30) == 0) {
            if (arg0->unk5 == 0) {
                func_80097670(arg0);
            } else {
                double_cyclone_charged_fly(arg0);
            }
        } else {
            arg0->on_screen = 0;
            arg0->state = 2;
            arg0->unk50 = 0;
        }
        double_cyclone_charged_draw(arg0);
    }
}

// double_cyclone_charged_gather
INCLUDE_ASM("main/nonmatchings/weapons/weapon_07", func_80097670);

void double_cyclone_charged_fly(struct WeaponObj* arg0)
{
    move_object(MOVING_OBJECT(arg0));
    if (arg0->ext.weapon_16.unk91 == 0) {
        arg0->ext.weapon_16.unk91 = 4;
        arg0->unk64++;
    } else {
        arg0->ext.weapon_16.unk91--;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x18, 0x30);
}

void double_cyclone_charged_offscreen(struct WeaponObj* arg0)
{
    if (double_cyclone_charged_check_expired(arg0) == 0) {
        animate_object(arg0);
        double_cyclone_charged_draw(arg0);
    }
}

s32 double_cyclone_charged_check_expired(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_16.timer == 0) {
        double_cyclone_hide(arg0);
        double_cyclone_charged_draw(arg0);
        return 1;
    }
    arg0->ext.weapon_16.timer--;
    return 0;
}

void double_cyclone_charged_draw(struct WeaponObj* arg0)
{
    if (arg0->unk2 == 0) {
        decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x30);
    }
}

void double_cyclone_charged_despawn(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    if (arg0->unk2 == 0) {
        g_Player.shot_count--;
        g_Player.special_shot_count--;
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}

struct Unk_unk68 double_cyclone_hit_box[] = {
    { -16, -16, 0x20, 0x20 },
};

struct Unk_unk68 double_cyclone_charged_hit_box[] = {
    { -12, -28, 0x18, 0x36 },
};

void (*double_cyclone_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80096EA4,
    (void (*)(struct WeaponObj*))double_cyclone_main,
    (void (*)(struct WeaponObj*))double_cyclone_despawn,
    (void (*)(struct WeaponObj*))double_cyclone_despawn,
};

u8 double_cyclone_spawn_offsets[4] = {
    0xEF,
    0xF9,
    0x1A,
    0xF9,
};

void (*double_cyclone_step_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))double_cyclone_form,
    (void (*)(struct WeaponObj*))double_cyclone_fly,
    (void (*)(struct WeaponObj*))double_cyclone_spin,
    (void (*)(struct WeaponObj*))double_cyclone_dissipate,
};

void (*double_cyclone_charged_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80097430,
    (void (*)(struct WeaponObj*))double_cyclone_charged_main,
    (void (*)(struct WeaponObj*))double_cyclone_charged_offscreen,
    (void (*)(struct WeaponObj*))double_cyclone_charged_despawn,
};

u8 double_cyclone_charged_spawn_offsets[4] = {
    0xF0,
    0xF9,
    0x1F,
    0xF9,
};
