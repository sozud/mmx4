// WeaponObj, weapon_object_update_funcs[8]
// 80097860..80097EEC
#include "common.h"
#include "main/objects.h"
#include "main/weapons/weapon_08_twin_slasher.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/weapons/weapon_22_nova_strike_hitbox.h"
#include "main/sprite_animations.h"

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
    struct PlayerObj* player = &g_Player;
    u32 should_reset = 0;

    if (player->input_locked != 0) {
        should_reset = 1;
    }
#ifndef VERSION_DEMO
    if (player->capsule_state != 0) {
        should_reset = 1;
    }
#endif
    if (player->weapon != 8) {
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

void func_800978DC(struct WeaponObj* arg0)
{
    struct PlayerObj* player;
    struct Weapon8Ext* ext = &arg0->ext.weapon_8;

    arg0->on_screen = 1;
    arg0->unk50 = twin_slasher_hit_boxes;
    arg0->unk38 = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[9];
    arg0->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0x11];
    arg0->animation_table = D_8011C104;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = DEMO_ALT(0, 1);
    player = &g_Player;
    arg0->unk15 = g_Player.unk15;
#ifdef VERSION_DEMO
    if (arg0->unk15 != 0)
        arg0->x_pos.i.hi = player->x_pos.i.hi - D_8011B230.components[player->animation_step.fields.frame_index * 2];
    else
        arg0->x_pos.i.hi = player->x_pos.i.hi + D_8011B230.components[player->animation_step.fields.frame_index * 2];
    arg0->y_pos.i.hi = player->y_pos.i.hi + D_8011B230.components[player->animation_step.fields.frame_index * 2 + 1];
#else
    buster_shot_place_at_muzzle((struct VisualObj*)arg0, player, arg0->id);
#endif
    if (arg0->unk2 == 0)
        set_velocity_from_angle(MOVING_OBJECT(arg0), 2);
    else
        set_velocity_from_angle(MOVING_OBJECT(arg0), 0x1E);
    arg0->x_vel.val *= 8;
    arg0->y_vel.val *= 8;
    if (arg0->unk15 == 0)
        arg0->x_vel.val = -arg0->x_vel.val;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    ext->timer = 0x18;
    set_animation(arg0, arg0->unk2);
#ifndef VERSION_DEMO
    move_object(MOVING_OBJECT(arg0));
#endif
    arg0->state++;
    arg0->unk5 = 0;
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}

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
    struct PlayerObj* player = &g_Player;
    u32 should_reset = 0;

    if (player->input_locked != 0) {
        should_reset = 1;
    }
#ifndef VERSION_DEMO
    if (player->capsule_state != 0) {
        should_reset = 1;
    }
#endif
    if (player->weapon != 8) {
        should_reset = 1;
    }
    if (should_reset != 0) {
        arg0->state = 3;
    }
    twin_slasher_charged_state_funcs[arg0->state](arg0);
}

#ifdef VERSION_DEMO
extern struct Unk_unk68 D_800D8868_demo[];
extern u8 D_800D8860_demo[];

void func_80088668_demo(struct WeaponObj* arg0)
{
    struct PlayerObj* player;
    struct Weapon17Ext* ext = &arg0->ext.weapon_17;
    s32 level = arg0->unk2 >> 1;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = &D_800D8868_demo[level];
    arg0->unk38 = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[9];
    arg0->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0x11];
    arg0->animation_table = D_8011C104;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = 1;
    player = &g_Player;
    arg0->unk15 = g_Player.unk15;
    set_velocity_from_angle(MOVING_OBJECT(arg0), D_800D8860_demo[arg0->unk2]);
    arg0->x_vel.val *= 9;
    arg0->y_vel.val *= 9;
    arg0->unk28.val = 0;
    arg0->unk2C = 0;
    if (arg0->unk15 != 0) {
        arg0->x_pos.i.hi = player->x_pos.i.hi - D_8011B230.components[player->animation_step.fields.frame_index * 2];
    } else {
        arg0->x_pos.i.hi = player->x_pos.i.hi + D_8011B230.components[player->animation_step.fields.frame_index * 2];
        arg0->x_vel.val = -arg0->x_vel.val;
    }
    arg0->y_pos.i.hi = player->y_pos.i.hi + D_8011B230.components[player->animation_step.fields.frame_index * 2 + 1];
    move_object(MOVING_OBJECT(arg0));
    set_animation(arg0, level + 2);
    ext->timer = 3;
    arg0->unk5 = 0;
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}
#endif

// twin_slasher_charged_init
#ifndef VERSION_DEMO
void func_80097BA4(struct WeaponObj* arg0)
{
    struct PlayerObj* player;
    struct Weapon17Ext* ext = &arg0->ext.weapon_17;
    s32 level = arg0->unk2 >> 1;

    arg0->on_screen = 1;
    arg0->unk50 = &twin_slasher_charged_hit_boxes[level];
    arg0->unk64 = 1;
    arg0->unk38 = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[9];
    arg0->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0x11];
    arg0->animation_table = D_8011C104;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = 0;
    player = &g_Player;
    arg0->unk15 = g_Player.unk15;
    buster_shot_place_at_muzzle((struct VisualObj*)arg0, player, arg0->id);
    set_velocity_from_angle(MOVING_OBJECT(arg0), twin_slasher_charged_angles[arg0->unk2]);
    arg0->x_vel.val *= 9;
    arg0->unk28.val = 0;
    arg0->y_vel.val *= 9;
    arg0->unk2C = 0;
    if (arg0->unk15 == 0)
        arg0->x_vel.val = -arg0->x_vel.val;
    set_animation(arg0, level + 2);
    move_object(MOVING_OBJECT(arg0));
    ext->timer = 3;
    arg0->state++;
    arg0->unk5 = 0;
    update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
}
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
    s32* sprite_frames;
    s32* player_gfx;
    s32 should_reset = g_Player.input_locked != 0;

#ifndef VERSION_DEMO
    if (g_Player.capsule_state != 0) {
        should_reset = 1;
    }
#endif
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
        self->unk38 = (u8*)player_gfx + player_gfx[9];
        sprite_frames = SP_SPRITE_FRAMES;
        self->unk3C = (u8*)sprite_frames + sprite_frames[0x11];
        self->animation_table = D_8011C104;
        self->unk40 = WEAPON_TEXTURE_SPECIAL_0;
        self->unk42 = WEAPON_PALETTE_1;
        self->unk16 = DEMO_ALT(1, 3);
        set_animation(self, self->unk2 + 6);
        self->state++;
    }
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
}

#ifdef VERSION_DEMO
void func_80088BA8_demo(struct WeaponObj* weapon, struct PlayerObj* player);
void zero_saber_follow(struct WeaponObj*, struct PlayerObj*);

void func_80088A3C_demo(struct WeaponObj* self)
{
    struct PlayerObj* player = &g_Player;
    u8 duration;

    if (self->state == 0) {
        func_80088BA8_demo(self, player);
    } else {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.relative_step == 0) {
            g_Player.shot_count = 0;
        }
        if (g_Player.attacking == 0) {
            g_Player.shot_count = 0;
        }
        switch (self->id) {
        case 0x18:
        case 0x19:
        case 0x1A:
            if (g_Player.unk17 == 0x5F) {
                g_Player.shot_count = 0;
            }
            break;
        }
        if (player->shot_count == 0) {
            ZeroObjectState(OBJECT_HEADER(self));
            return;
        }
        if (self->unk2 != player->combo) {
            self->id = player->combo + 0x18;
            self->unk2 = player->combo;
            set_animation(self, self->unk2 + 0x60);
        }
        if (self->id == 0x1B && player->unk17 == 0x54) {
            self->id = 0x1C;
            duration = self->animation_step.fields.duration;
            set_animation_frame(ANIMATED_OBJECT(self), 0x64, player->animation_step.fields.event & 0x1F);
            self->animation_step.fields.duration = duration;
        }
    }
    zero_saber_follow(self, player);
}
#endif

#ifdef VERSION_DEMO
void func_80088BA8_demo(struct WeaponObj* weapon, struct PlayerObj* player)
{
    s8 type;
    s32 animation;

    weapon->on_screen = 1;
    weapon->unk38 = player->unk38;
    weapon->unk3C = player->unk3C;
    weapon->animation_table = player->animation_table;
    weapon->unk40 = player->unk40;
    weapon->unk42 = player->unk42;
    weapon->unk16 = 2;
    player->shot_count = 1;
    type = weapon->id - 0x18;
    switch (type) {
    case 0:
        animation = 0x60;
        break;
    case 3:
        animation = 0x63;
        break;
    case 4:
        animation = 0x64;
        break;
    case 5:
        animation = 0x65;
        break;
    case 6:
        animation = 0x66;
        break;
    case 7:
        animation = 0x67;
        break;
    case 8:
        if (weapon->unk2 == 0) {
            animation = 0x68;
        } else {
            animation = 0x6F;
        }
        break;
    }
    set_animation(weapon, animation);
    weapon->state++;
}
#endif

#ifdef VERSION_DEMO
extern struct Unk_unk68 twin_slasher_hit_boxes[];
extern struct Unk_unk68 twin_slasher_charged_hit_boxes[];
extern void (*twin_slasher_state_funcs[])(struct WeaponObj*);
extern void (*twin_slasher_charged_state_funcs[])(struct WeaponObj*);
extern u8 twin_slasher_charged_angles[];
#else
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
#endif

#ifdef VERSION_DEMO
struct Unk_unk68 twin_slasher_hit_boxes[6] = { { -8, -12, 20, 24 }, { -12, -16, 28, 34 }, { -14, -20, 38, 44 }, { -8, -14, 20, 24 }, { -12, -20, 28, 34 }, { -14, -26, 38, 44 } };

void (*twin_slasher_state_funcs[4])(struct WeaponObj*) = {
    func_800978DC,
    twin_slasher_main,
    twin_slasher_despawn,
    twin_slasher_despawn,
};

void (*twin_slasher_charged_state_funcs[4])(struct WeaponObj*) = {
    func_80088668_demo,
    twin_slasher_charged_main,
    twin_slasher_despawn,
    twin_slasher_despawn,
};

u8 D_800D8860_demo[8] = { 4, 3, 2, 1, 0x1F, 0x1E, 0x1D, 0x1C };

struct Unk_unk68 D_800D8868_demo[4] = { { -16, -16, 38, 38 }, { -16, -18, 38, 38 }, { -16, -20, 38, 38 }, { -16, -22, 38, 38 } };
#endif
