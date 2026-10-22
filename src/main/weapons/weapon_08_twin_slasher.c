// WeaponObj, weapon_object_update_funcs[8]
// 80097860..80097EEC
#include "common.h"
#include "main/objects.h"
#include "main/weapons/weapon_08_twin_slasher.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/weapons/weapon_22_nova_strike_hitbox.h"

void twin_slasher_hide(struct WeaponObj*);

// twin_slasher_state_funcs
extern void (*twin_slasher_state_funcs[])(struct WeaponObj*);

void twin_slasher_main(struct WeaponObj*);
void twin_slasher_despawn(struct WeaponObj*);
void twin_slasher_despawn(struct WeaponObj*);

// twin_slasher_charged_state_funcs
extern void (*twin_slasher_charged_state_funcs[])(struct WeaponObj*);

void twin_slasher_charged_main(struct WeaponObj*);
void twin_slasher_despawn(struct WeaponObj*);
void twin_slasher_despawn(struct WeaponObj*);

extern struct Unk_unk68 twin_slasher_charged_hit_boxes[];
extern u8 twin_slasher_charged_angles[];

#include "weapon_resources.h"

extern union AnimationStep* D_8011C104[10];

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

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800978DC(struct WeaponObj* arg0);
void func_80097BA4(struct WeaponObj* arg0);
extern struct Unk_unk68 twin_slasher_charged_hit_boxes[];
extern u8 twin_slasher_charged_angles[];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800978DC(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;

    arg0->on_screen = 1;
    arg0->unk50 = twin_slasher_hit_boxes;
    arg0->unk38 = (u8*)player_gfx + player_gfx[9];
    arg0->animation_table = D_8011C104;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x11];
    arg0->unk15 = g_Player.unk15;
    buster_shot_place_at_muzzle((struct VisualObj*)arg0, &g_Player, arg0->id);
    set_velocity_from_angle(MOVING_OBJECT(arg0), arg0->unk2 == 0 ? 2 : 0x1E);
    arg0->x_vel.val *= 8;
    arg0->y_vel.val *= 8;
    if (arg0->unk15 == 0)
        arg0->x_vel.val = -arg0->x_vel.val;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->ext.weapon_8.timer = 0x18;
    set_animation(arg0, arg0->unk2);
    move_object(MOVING_OBJECT(arg0));
    arg0->unk5 = 0;
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_08_twin_slasher", func_800978DC);
#endif

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
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80097BA4(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    s32 level = arg0->unk2 >> 1;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = &twin_slasher_charged_hit_boxes[level];
    arg0->unk38 = (u8*)player_gfx + player_gfx[9];
    arg0->animation_table = D_8011C104;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0x11];
    arg0->unk15 = g_Player.unk15;
    buster_shot_place_at_muzzle((struct VisualObj*)arg0, &g_Player, arg0->id);
    set_velocity_from_angle(MOVING_OBJECT(arg0), twin_slasher_charged_angles[arg0->unk2]);
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    arg0->x_vel.val *= 9;
    arg0->y_vel.val *= 9;
    if (arg0->unk15 == 0)
        arg0->x_vel.val = -arg0->x_vel.val;
    set_animation(arg0, level + 2);
    move_object(MOVING_OBJECT(arg0));
    arg0->ext.weapon_17.timer = 3;
    arg0->unk5 = 0;
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_08_twin_slasher", func_80097BA4);
#endif

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
void func_80097DD8(struct MiscObj* self)
{
    s32* player_gfx;
    s32* sprite_frames;
    s32 should_reset = g_Player.input_locked != 0;

    if (g_Player.capsule_state != 0) {
        should_reset = 1;
    }
    if (g_Player.weapon != 8) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
    if (self->state != 0) {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.relative_step == 0) {
            ZeroObjectState(OBJECT_HEADER(self));
            return;
        }
    } else {
        self->on_screen = 1;
        player_gfx = SP_PLAYER_GFX;
        sprite_frames = SP_SPRITE_FRAMES;
        self->unk38 = (u8*)player_gfx + player_gfx[9];
        self->unk3C = (u8*)sprite_frames + sprite_frames[0x11];
        self->animation_table = D_8011C104;
        self->unk40 = WEAPON_TEXTURE_SPECIAL_0;
        self->unk42 = WEAPON_PALETTE_1;
        self->unk16 = 1;
        set_animation(self, self->unk2 + 6);
        self->state++;
    }
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
}

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
