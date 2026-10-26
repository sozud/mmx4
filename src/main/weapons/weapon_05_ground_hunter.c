// WeaponObj, weapon_object_update_funcs[5]
// 800957B0..800961B0
#include "common.h"
#include "main/weapons/weapon_05_ground_hunter.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/sprite_animations.h"
#include "main/weapons/weapon_22_nova_strike_hitbox.h"
#include "main/player_common.h"

extern struct Unk_unk68 ground_hunter_crawl_box[];
extern struct Unk_unk68 ground_hunter_rise_box[];

// ground_hunter_state_funcs
extern void (*ground_hunter_state_funcs[])(struct WeaponObj*);
void func_80095854(struct WeaponObj*);
void ground_hunter_main(struct WeaponObj*);
void ground_hunter_burst(struct WeaponObj*);
void ground_hunter_despawn(struct WeaponObj*);
void ground_hunter_hide(struct WeaponObj* arg0);

// ground_hunter_step_funcs
extern void (*ground_hunter_step_funcs[])(struct WeaponObj*);
void ground_hunter_fly(struct WeaponObj*);
void ground_hunter_start_crawl(struct WeaponObj*);

void ground_hunter_rise(struct WeaponObj*);
void ground_hunter_crawl(struct WeaponObj*);

// ground_hunter_charged_state_funcs
extern void (*ground_hunter_charged_state_funcs[])(struct WeaponObj*);

void ground_hunter_charged_main(struct WeaponObj*);
void ground_hunter_burst(struct WeaponObj*);
void ground_hunter_despawn(struct WeaponObj*);

// ground_hunter_charged_step_funcs
extern void (*ground_hunter_charged_step_funcs[])(struct WeaponObj*);
void ground_hunter_charged_wait_fire(struct WeaponObj*);

extern struct Unk_unk68 ground_hunter_charged_hit_box[];
extern struct Unk_unk68 ground_hunter_charged_shot_box[];

#include "weapon_resources.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/player_common.h"
#endif

s32 ground_hunter_check_wall(struct WeaponObj* arg0);
void ground_hunter_start_rise(struct WeaponObj* arg0);

void ground_hunter_update(struct WeaponObj* arg0)
{
    s32 shouldSetState;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    shouldSetState = 0;
    if (g_Player.input_locked != 0) {
        shouldSetState = 1;
    }
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
void func_80095854(struct WeaponObj* self)
{
    struct PlayerObj* player = &g_Player;

    self->on_screen = 1;
    self->unk50 = ground_hunter_crawl_box;
    self->unk64 = 1;
    self->unk68 = ground_hunter_terrain_box;
    self->unk38 = (u8*)SP_ARCHIVE_ENTRY(SP_PLAYER_GFX, 6);
    self->unk3C = (u8*)SP_ARCHIVE_ENTRY(SP_SPRITE_FRAMES, 14);
    self->animation_table = D_8011C0C8;
    self->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    self->unk42 = WEAPON_PALETTE_1;
    self->unk16 = 0;
    self->unk15 = player->unk15;

    buster_shot_place_at_muzzle(VISUAL_OBJECT(self), player, self->id);

    if (self->unk15) {
        self->x_vel.val = FIXED(6);
    } else {
        self->x_vel.val = FIXED(-6);
    }
    self->y_vel.val = FIXED(-2);
    self->unk28.val = 0;
    self->unk2C = 0;
    self->unk67 = 1;

    set_animation(self, 0);
    func_8001540C(1, 8, self);
    self->unk5 = 0;
    self->state++;
    update_on_screen(BASE_OBJECT(self), 0x2C, 0x20);
}

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
    u8 mask;
    u8 flags;

    mask = arg0->unk15 != 0 ? 1 : 2;
    flags = arg0->unk70;
    if (flags & 8) {
        if (flags & mask) {
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

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/weapons/weapon_05_ground_hunter", ground_hunter_check_wall);
#else
s32 ground_hunter_check_wall(struct WeaponObj* arg0)
{
    u16 mask;
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
#endif

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
    arg0->x_vel.val = 0;
    arg0->y_vel.val = -FIXED(6);
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
    s32 should_reset = 0;

    if (g_Player.input_locked != 0) {
        should_reset = 1;
    }

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

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80095E3C(struct WeaponObj* self);
void func_80096060(struct WeaponObj* self);
// src/main/weapons/weapon_05_ground_hunter.c

extern struct Unk_unk68 ground_hunter_charged_hit_box[];
extern struct Unk_unk68 ground_hunter_charged_shot_box[];
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/weapons/weapon_05_ground_hunter", func_80095E3C);
#else
void func_80095E3C(struct WeaponObj* self)
{
    struct PlayerObj* player;

    self->on_screen = 1;
    self->unk38 = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[6];
    self->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[14];
    self->animation_table = D_8011C0C8;
    self->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    self->unk42 = WEAPON_PALETTE_1;
    player = &g_Player;
    self->unk15 = g_Player.unk15;
    self->x_vel.val = 0;
    self->unk28.val = 0;
    self->y_vel.val = 0;
    self->unk2C = 0;
    set_animation(self, self->unk2 + 3);
    self->state++;
    if (self->unk2 == 0) {
        self->unk16 = 0;
        self->unk50 = ground_hunter_charged_hit_box;
        self->unk64 = 1;
        buster_shot_place_at_muzzle((struct VisualObj*)self, player, self->id);
        if (self->unk15)
            self->x_vel.val = FIXED(6);
        else
            self->x_vel.val = FIXED(-6);
        func_8001540C(1, 9, self);
        self->unk5 = 0;
    } else {
        self->unk50 = ground_hunter_charged_shot_box;
        self->unk16 = 1;
        self->unk64 = 0;
        if (self->unk2 == 1)
            self->y_vel.val = FIXED(8);
        else
            self->y_vel.val = FIXED(-8);
        self->unk5 = 2;
    }
    update_on_screen(BASE_OBJECT(self), 0x2C, 0x18);
}
#endif

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
    struct Weapon14Ext* ext = &arg0->ext.weapon_14;
    if (g_Player.input.buttons.held & 0xC) {
        ext->unk8C = 0;
        ext->unk8D = 5;
        arg0->unk5 = 1;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x2C, 0x18);
}

// ground_hunter_charged_fire
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/weapons/weapon_05_ground_hunter", func_80096060);
#else
void func_80096060(struct WeaponObj* self)
{
    struct Weapon14Ext* ext = &self->ext.weapon_14;
    struct PlayerObj* player = &g_Player;

    if (ext->unk8C == 0) {
        struct WeaponObj* shot;
        ext->unk8C = 4;
        shot = player_spawn_weapon(1, 0xE, 1, NULL);
        if (shot != NULL) {
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
        }
        shot = player_spawn_weapon(1, 0xE, 2, NULL);
        if (shot != NULL) {
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
        }
        g_Player.shot_count += 2;
        player->special_shot_count += 2;
        if (--*(u8*)&ext->unk8D == 0)
            ground_hunter_start_burst(self);
    } else {
        ext->unk8C--;
    }
    update_on_screen(BASE_OBJECT(self), 0x2C, 0x18);
}
#endif

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
