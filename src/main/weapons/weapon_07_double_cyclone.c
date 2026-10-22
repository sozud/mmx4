// WeaponObj, weapon_object_update_funcs[7]
// 80096E10..80097860
#include "common.h"
#include "main/weapons/weapon_07_double_cyclone.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

void double_cyclone_charged_fly(struct WeaponObj*);

// double_cyclone_state_funcs
extern void (*double_cyclone_state_funcs[])(struct WeaponObj*);

void double_cyclone_main(struct WeaponObj*);
void double_cyclone_despawn(struct WeaponObj*);
void double_cyclone_despawn(struct WeaponObj*);

// double_cyclone_step_funcs
extern void (*double_cyclone_step_funcs[])(struct WeaponObj*);
void double_cyclone_form(struct WeaponObj*);
void double_cyclone_fly(struct WeaponObj*);
void double_cyclone_spin(struct WeaponObj*);
void double_cyclone_dissipate(struct WeaponObj*);
void double_cyclone_hide(struct WeaponObj* arg0);

// double_cyclone_charged_state_funcs
extern void (*double_cyclone_charged_state_funcs[])(struct WeaponObj*);

void double_cyclone_charged_main(struct WeaponObj*);
void double_cyclone_charged_offscreen(struct WeaponObj*);

void double_cyclone_charged_despawn(struct WeaponObj*);

extern u8 double_cyclone_spawn_offsets[4];
extern struct Unk_unk68 double_cyclone_hit_box[];
extern union AnimationStep* D_8011C0F0[5];
extern u8 double_cyclone_charged_spawn_offsets[4];
extern struct Unk_unk68 double_cyclone_charged_hit_box[];

#include "weapon_resources.h"

s32 double_cyclone_charged_check_expired(struct WeaponObj* arg0);
s32 double_cyclone_check_expired(struct WeaponObj* arg0);

void double_cyclone_update(struct WeaponObj* arg0)
{
    s32 disabled;

    disabled = 0;
    if (g_Player.input_locked != 0) {
        disabled = 1;
    }
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

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80096EA4(struct WeaponObj* arg0);
void func_80097430(struct WeaponObj* arg0);
void func_80097670(struct WeaponObj* arg0);
extern struct Unk_unk68 double_cyclone_hit_box[];
extern u8 double_cyclone_spawn_offsets[4];
extern u8 double_cyclone_charged_spawn_offsets[4];
extern struct Unk_unk68 double_cyclone_charged_hit_box[];
void double_cyclone_charged_draw(struct WeaponObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80096EA4(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    s8 dx = double_cyclone_spawn_offsets[arg0->unk2 * 2];
    s8 dy = double_cyclone_spawn_offsets[arg0->unk2 * 2 + 1];

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = double_cyclone_hit_box;
    arg0->unk38 = (u8*)player_gfx + player_gfx[8];
    arg0->unk16 = 1;
    arg0->animation_table = D_8011C0F0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x10];
    if (arg0->unk2 == 0) {
        arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
        arg0->x_vel.val = -0x26000;
        arg0->unk15 = 0;
    } else {
        arg0->x_vel.val = 0x26000;
        arg0->unk40 = WEAPON_TEXTURE_SPECIAL_1;
        arg0->unk15 = PLAYER_FACING_RIGHT;
    }
    if (g_Player.unk15 == 0) {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + dx;
    } else {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - dx;
        arg0->unk15 ^= PLAYER_FACING_RIGHT;
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi + dy;
    arg0->unk49 = arg0->unk2;
    arg0->ext.weapon_7.timer = 0x23;
    arg0->ext.weapon_7.unk90 = 8;
    arg0->ext.weapon_7.unk91 = 4;
    set_animation(arg0, 0);
    func_8001540C(0, WEAPON_SOUND_CYCLONE, arg0);
    arg0->state++;
    double_cyclone_draw(arg0);
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_07_double_cyclone", func_80096EA4);
#endif

void double_cyclone_main(struct WeaponObj* arg0)
{
    u8 temp_v0;
    struct Weapon7Ext* ext;

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 0) {
        ext = &arg0->ext.weapon_7;
        double_cyclone_step_funcs[arg0->unk5](arg0);
        if (arg0->unk50 != 0) {
            temp_v0 = ext->unk91;
            if (temp_v0 == 0) {
                ext->unk91 = 4;
                arg0->unk64++;
                return;
            }
            ext->unk91 = temp_v0 - 1;
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
            struct Weapon7Ext* weapon_7 = &arg0->ext.weapon_7;
            if (weapon_7->unk90 != 0) {
                weapon_7->unk90--;
                if (weapon_7->unk90 == 0) {
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

    var_a1 = 0;
    if (g_Player.input_locked != 0) {
        var_a1 = 1;
    }
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
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80097430(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    s32 side;
    s8 dx;
    s8 dy;

    arg0->unk38 = (u8*)player_gfx + player_gfx[8];
    arg0->animation_table = D_8011C0F0;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_1;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x10];
    if (arg0->unk2 < 0) {
        side = 1;
        arg0->x_vel.val = 0x60000;
        arg0->unk15 = PLAYER_FACING_RIGHT;
    } else {
        side = 0;
        arg0->x_vel.val = -0x60000;
        arg0->unk15 = 0;
    }
    dx = double_cyclone_charged_spawn_offsets[side * 2];
    dy = double_cyclone_charged_spawn_offsets[side * 2 + 1];
    if (g_Player.unk15 == 0) {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + dx;
    } else {
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - dx;
        arg0->unk15 ^= PLAYER_FACING_RIGHT;
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->y_pos.i.hi = g_Player.y_pos.i.hi + dy;
    arg0->ext.weapon_16.timer = 0x32;
    arg0->ext.weapon_16.unk91 = 4;
    arg0->ext.weapon_16.delay = (arg0->unk2 & 0x7F) << 2;
    arg0->unk49 = 1;
    set_animation(arg0, 4);
    func_8001540C(0, WEAPON_SOUND_CYCLONE, arg0);
    func_8001540C(1, 0xA, arg0);
    arg0->unk5 = 0;
    arg0->state++;
    double_cyclone_charged_draw(arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x18, 0x30);
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_07_double_cyclone", func_80097430);
#endif

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
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80097670(struct WeaponObj* arg0)
{
    if (arg0->ext.weapon_16.delay != 0) {
        arg0->ext.weapon_16.delay--;
        return;
    }
    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = double_cyclone_charged_hit_box;
    arg0->unk5++;
    update_on_screen(BASE_OBJECT(arg0), 0x18, 0x30);
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_07_double_cyclone", func_80097670);
#endif

void double_cyclone_charged_fly(struct WeaponObj* arg0)
{
    struct Weapon16Ext* ext = &arg0->ext.weapon_16;
    move_object(MOVING_OBJECT(arg0));
    if (ext->unk91 == 0) {
        ext->unk91 = 4;
        arg0->unk64++;
    } else {
        ext->unk91--;
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
