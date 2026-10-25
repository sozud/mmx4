// WeaponObj, weapon_object_update_funcs[2]
// 80093CBC..80094A78
#include "common.h"
#include "main/objects.h"
#include "main/weapons/weapon_02_frost_tower.h"
#include "main/object_motion.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/sprite_animations.h"
#include "main/stage_objects.h"

extern struct Unk_unk68 frost_tower_charged_part_box[];

extern struct Unk_unk68 frost_tower_terrain_box[];

extern u8 frost_sparkle_animations[];

extern s32 frost_particle_x_vels[8];
extern s32 frost_particle_y_vels[8];
void frost_particle_launch(struct MiscObj* arg0);
void frost_sparkle_init(struct MiscObj* arg0);
void frost_shard_init(struct MiscObj* arg0);
void frost_particle_fall(struct MiscObj* arg0);

// frost_tower_state_funcs
extern void (*frost_tower_state_funcs[])(struct WeaponObj*);

void frost_tower_main(struct WeaponObj*);
void frost_tower_despawn(struct WeaponObj*);
void frost_tower_despawn(struct WeaponObj*);

// frost_tower_step_funcs
extern void (*frost_tower_step_funcs[])(struct WeaponObj*);
void frost_tower_form(struct WeaponObj*);
void frost_tower_check_ground(struct WeaponObj*);
void frost_tower_fall(struct WeaponObj*);

// frost_tower_charged_state_funcs
extern void (*frost_tower_charged_state_funcs[])(struct WeaponObj*);

void frost_tower_despawn(struct WeaponObj*);
void frost_tower_despawn(struct WeaponObj*);

// frost_tower_charged_part_state_funcs
extern void (*frost_tower_charged_part_state_funcs[])(struct WeaponObj*);

void frost_tower_charged_part_main(struct WeaponObj*);
void frost_tower_despawn(struct WeaponObj*);
void frost_tower_despawn(struct WeaponObj*);

extern struct Unk_unk68 frost_tower_hit_box[];
extern u16 frost_tower_charged_part_offsets[];
void frost_tower_charged_spawn_part(s8 arg0);

#include "weapon_resources.h"

void frost_tower_update(struct WeaponObj* arg0)
{
    s32 should_change_state;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;

    should_change_state = 0;
    if (g_Player.input_locked != 0) {
        should_change_state = 1;
    }
    if (g_Player.capsule_state != 0) {
        should_change_state = 1;
    }
    if (g_Player.weapon != 2) {
        should_change_state = 1;
    }
    if (g_Player.shot_type == 0xB) {
        should_change_state = 1;
    }
    if (should_change_state != 0) {
        arg0->state = 3;
    }

    frost_tower_state_funcs[arg0->state](arg0);
    CollisionRelated(PLAYER_OBJECT(arg0));
}

// frost_tower_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80093D78(struct WeaponObj* arg0);
void func_80094280(struct WeaponObj* arg0);
void func_800942E8(struct WeaponObj* arg0);
void func_800944B8(struct WeaponObj* arg0);
extern struct Unk_unk68 frost_tower_hit_box[];
extern u16 frost_tower_charged_part_offsets[];
void frost_tower_charged_spawn_part(s8 arg0);
void frost_tower_hide(struct WeaponObj* arg0);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/weapons/weapon_02_frost_tower", func_80093D78);
#else
void func_80093D78(struct WeaponObj* arg0)
{
    struct PlayerObj* player;
    struct Weapon2Ext* ext;

    arg0->on_screen = 1;
    arg0->unk64 = 1;
    arg0->unk50 = frost_tower_hit_box;
    arg0->unk38 = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[3];
    arg0->unk3C = (u8*)SP_SPRITE_FRAMES + SP_SPRITE_FRAMES[0xB];
    arg0->animation_table = D_8011C094;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = 3;
    arg0->unk15 = 0;
    player = &g_Player;
    ext = &arg0->ext.weapon_2;
    if (g_Player.unk15 == 0)
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi + 5;
    else
        arg0->x_pos.i.hi = g_Player.x_pos.i.hi - 5;
    arg0->y_pos.i.hi = player->y_pos.i.hi - 6;
    arg0->x_vel.val = 0;
    arg0->unk28.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk2C = 0;
    arg0->unk49 = 0;
    arg0->unk67 = 1;
    ext->lifetime = 0x96;
    ext->timer = 8;
    set_animation(arg0, 0);
    arg0->unk5 = 0;
    arg0->state++;
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
    update_on_screen(BASE_OBJECT(arg0), 0x28, 0x38);
}
#endif

void frost_tower_main(struct WeaponObj* arg0)
{
    u32 i;
    struct Weapon2Ext* ext = &arg0->ext.weapon_2;

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x28, 0x38) == 0) {
        if (ext->lifetime == 0) {
            func_8001540C(0, WEAPON_SOUND_FROST, arg0);
            for (i = 0; i < 8U; i++) {
                frost_tower_spawn_shard(arg0);
            }
        } else {
            ext->lifetime--;
            animate_object(ANIMATED_OBJECT(arg0));
            frost_tower_step_funcs[arg0->unk5](arg0);
            if (arg0->unk50 != NULL) {
                if (ext->timer == 0) {
                    ext->timer = 8;
                    arg0->unk64++;
                } else {
                    ext->timer--;
                }
            }
            update_on_screen(BASE_OBJECT(arg0), 0x28, 0x38);
            return;
        }
    }
    frost_tower_hide(arg0);
}

void frost_tower_form(struct WeaponObj* arg0)
{
    if (arg0->animation_step.fields.event & 0x40) {
        arg0->animation_step.fields.event = 0;
        func_8001540C(0, WEAPON_SOUND_FROST, arg0);
    }
    if (arg0->animation_step.fields.event & 0x80) {
        arg0->animation_step.fields.event = 0;
        arg0->unk68 = frost_tower_terrain_box;
        arg0->unk67 = 0;
        arg0->unk5 = 1;
    }
}

void frost_tower_check_ground(struct WeaponObj* arg0)
{
    if (!(arg0->unk70 & 8)) {
        arg0->unk67 = -1;
        arg0->x_vel.val = 0;
        arg0->unk28.val = 0;
        arg0->y_vel.val = 0;
        arg0->unk2C = 0x4200;
        arg0->unk5 = 2;
    }
}

void frost_tower_fall(struct WeaponObj* arg0)
{
    u32 i;

    if (arg0->unk70 & 8) {
        func_8001540C(0, WEAPON_SOUND_FROST, arg0);
        arg0->unk67 = 0;
        i = 0;
        do {
            frost_tower_spawn_shard(arg0);
            i++;
        } while (i < 4);
        start_screen_shake_x(8, 6, 1);
        arg0->unk5 = 1;
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
}

void frost_tower_despawn(struct WeaponObj* arg0)
{
    arg0->unk50 = 0;
    arg0->unk68 = 0;
    g_Player.shot_count--;
    g_Player.special_shot_count--;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void frost_tower_hide(struct WeaponObj* arg0)
{
    arg0->on_screen = 0;
    arg0->state = 3;
    arg0->unk50 = 0;
    arg0->unk68 = 0;
}

void frost_tower_spawn_shard(struct WeaponObj* arg0)
{
    struct MiscObj* temp_v0;

    temp_v0 = find_free_misc_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 1;
        temp_v0->id = 0x25;
        temp_v0->unk2 = 0;
        temp_v0->bg_offset = arg0->bg_offset;
        temp_v0->x_pos.val = arg0->x_pos.val;
        temp_v0->y_pos.val = arg0->y_pos.val;
    }
}

// WeaponObj, weapon_object_update_funcs[11]

void frost_tower_charged_update(struct WeaponObj* arg0)
{
    s32 disabled;

    disabled = 0;
    if (g_Player.input_locked != 0) {
        disabled = 1;
    }
    if (g_Player.capsule_state != 0) {
        disabled = 1;
    }
    if (g_Player.weapon != 2) {
        disabled = 1;
    }
    if (disabled != 0) {
        arg0->state = 3;
    }
    if (arg0->unk2 == 0) {
        frost_tower_charged_state_funcs[arg0->state](arg0);
    } else {
        frost_tower_charged_part_state_funcs[arg0->state](arg0);
    }
}

// frost_tower_charged_init
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/weapons/weapon_02_frost_tower", func_80094280);
#else
void func_80094280(struct WeaponObj* arg0)
{
    arg0->unk38 = (u8*)SP_PLAYER_GFX + SP_PLAYER_GFX[3];
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->previous_animation_index = 0xFF;
    arg0->animation_step.fields.frame_index = 9;
    arg0->ext.raw[2] = 0;
    arg0->ext.raw[3] = 0;
    arg0->state++;
    arg0->unk5 = 0;
    decompress_player_gfx(GRAPHICS_OBJECT(arg0), 0x140, 0x20);
}
#endif

// frost_tower_charged_main
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/weapons/weapon_02_frost_tower", func_800942E8);
#else
void func_800942E8(struct WeaponObj* arg0)
{
    u8* ext = arg0->ext.raw;
    s32 strength;

    if (ext[2] == 0) {
        ext[2] = 0x28;
        strength = 0x20;
        switch (ext[3]) {
        case 0:
            frost_tower_charged_spawn_part(1);
            break;
        case 1:
            frost_tower_charged_spawn_part(2);
            frost_tower_charged_spawn_part(-0x7E);
            break;
        case 2:
            frost_tower_charged_spawn_part(1);
            frost_tower_charged_spawn_part(3);
            frost_tower_charged_spawn_part(-0x7D);
            break;
        case 3:
            frost_tower_charged_spawn_part(4);
            frost_tower_charged_spawn_part(-0x7C);
            frost_tower_charged_spawn_part(5);
            frost_tower_charged_spawn_part(-0x7B);
            strength = 0x40;
            break;
        }
        func_8001540C(0, WEAPON_SOUND_FROST, 0);
        start_screen_shake_x(strength, 8, 1);
        if (++ext[3] == 4)
            frost_tower_hide(arg0);
    } else {
        ext[2]--;
    }
}
#endif

void frost_tower_charged_spawn_part(s8 arg0)
{
    struct WeaponObj* weapon_obj;

    weapon_obj = find_free_weapon_obj();
    if (weapon_obj != NULL) {
        weapon_obj->active = 1;
        weapon_obj->id = 0xB;
        weapon_obj->unk2 = arg0;
        weapon_obj->bg_offset = g_Player.bg_offset;
        g_Player.shot_count++;
        g_Player.special_shot_count++;
    }
}

// frost_tower_charged_part_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800944B8(struct WeaponObj* arg0)
{
    s32* player_gfx = SP_PLAYER_GFX;
    s32* sprite_frames = SP_SPRITE_FRAMES;
    struct BackgroundObj* background = &background_objects[g_Player.bg_offset];
    u16 base;

    arg0->on_screen = 1;
    arg0->unk38 = (u8*)player_gfx + player_gfx[3];
    arg0->animation_table = D_8011C094;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = 1;
    arg0->unk15 = 0;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[0xB];
    base = background->x_pos.i.hi + 0xA0;
    if (arg0->unk2 & 0x80)
        arg0->x_pos.i.hi = base - frost_tower_charged_part_offsets[arg0->unk2 & 0x7F];
    else
        arg0->x_pos.i.hi = base + frost_tower_charged_part_offsets[arg0->unk2 & 0x7F];
    arg0->x_vel.val = 0;
    arg0->unk28.val = 0;
    arg0->y_vel.val = -0x80000;
    arg0->unk2C = 0;
    arg0->y_pos.i.hi = background->y_pos.i.hi + 0x30;
    set_animation(arg0, 6);
    arg0->unk5 = 0;
    arg0->state++;
    update_on_screen(BASE_OBJECT(arg0), 0x28, 0x38);
}
#else
INCLUDE_ASM("main/nonmatchings/weapons/weapon_02_frost_tower", func_800944B8);
#endif

void frost_tower_charged_part_main(struct WeaponObj* arg0)
{
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x28, 0x38) == 0) {
        animate_object(ANIMATED_OBJECT(arg0));
        if (arg0->unk5 == 0) {
            if (arg0->animation_step.fields.event == 1) {
                arg0->animation_step.fields.event = 0;
                arg0->unk50 = frost_tower_charged_part_box;
                arg0->unk64 = 1;
            }
            if (arg0->animation_step.fields.event == 2) {
                arg0->animation_step.fields.event = 0;
                arg0->unk5 = (u8)arg0->unk5 + 1;
            }
        } else {
            move_object(MOVING_OBJECT(arg0));
        }
        update_on_screen(BASE_OBJECT(arg0), 0x28, 0x38);
        return;
    }
    frost_tower_hide(arg0);
}

void frost_shard_update(struct MiscObj* arg0)
{
    s32 var_a1;

    var_a1 = 0;
    if (g_Player.input_locked != 0) {
        var_a1 = 1;
    }
    if (g_Player.capsule_state != 0) {
        var_a1 = 1;
    }
    if (g_Player.weapon != 2) {
        var_a1 = 1;
    }
    if (g_Player.shot_type == 0xB) {
        var_a1 = 1;
    }
    if (var_a1 != 0) {
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (arg0->state == 0) {
        frost_shard_init(arg0);
        return;
    }
    frost_particle_fall(arg0);
}

void frost_shard_init(struct MiscObj* arg0)
{
    s32* player_gfx;
    s32* sprite_frames;

    frost_particle_launch(arg0);
    player_gfx = SP_PLAYER_GFX;
    arg0->unk38 = (u8*)player_gfx + (player_gfx[0xC / 4]);
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk3C = (u8*)sprite_frames + (sprite_frames[0x2C / 4]);
    arg0->animation_table = D_8011C094;
    arg0->unk40 = WEAPON_TEXTURE_SPECIAL_0;
    arg0->unk42 = WEAPON_PALETTE_1;
    arg0->unk16 = 0;
    set_animation(arg0, (get_random() & 3) + 2);
}

void frost_sparkle_update(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        frost_sparkle_init(arg0);
    } else {
        frost_particle_fall(arg0);
    }
}

void frost_sparkle_init(struct MiscObj* arg0)
{
    s32* sprite_frames;

    frost_particle_launch(arg0);
    sprite_frames = SP_SPRITE_FRAMES;
    arg0->unk3C = (u8*)sprite_frames + sprite_frames[6];
    arg0->animation_table = D_8011C018;
    arg0->unk40 = WEAPON_TEXTURE_BASE;
    arg0->unk42 = WEAPON_PALETTE_2;
    arg0->unk16 = 0;
    set_animation(arg0, frost_sparkle_animations[get_random() & 7]);
}

void frost_particle_launch(struct MiscObj* self)
{
    self->on_screen = 1;

    if (get_random() & 1) {
        self->x_pos.u.hi += get_random() & 0xF;
    } else {
        self->x_pos.u.hi -= get_random() & 0xF;
    }

    if (get_random() & 1) {
        self->y_pos.u.hi += get_random() & 0x17;
    } else {
        self->y_pos.u.hi -= get_random() & 0x17;
    }

    if (get_random() & 1) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }

    self->x_vel.val = frost_particle_x_vels[get_random() & 7];
    self->y_vel.val = frost_particle_y_vels[get_random() & 7];
    self->unk28 = 0;
    self->unk2C = FIXED(0.3125);
    self->state++;
    self->unk5 = 0;
    update_on_screen(BASE_OBJECT(self), 0x14, 0x18);
}

void frost_particle_fall(struct MiscObj* arg0)
{
    s8 on_screen;

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x14, 0x18) == 0) {
        move_with_gravity(ANIMATED_OBJECT(arg0));
        if (FLICKER_ENABLED) {
            arg0->on_screen ^= 1;
        }
        if (arg0->on_screen != 0) {
            update_on_screen(BASE_OBJECT(arg0), 0x14, 0x18);
        }
    } else {
        ZeroObjectState(OBJECT_HEADER(arg0));
    }
}

struct Unk_unk68 frost_tower_hit_box[] = {
    { -22, -44, 0x2C, 0x56 },
};

struct Unk_unk68 frost_tower_terrain_box[] = {
    { 0, 0, 6, 0x1B },
};

struct Unk_unk68 frost_tower_charged_part_box[] = {
    { -34, -46, 0x42, 0x60 },
};

void (*frost_tower_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80093D78,
    (void (*)(struct WeaponObj*))frost_tower_main,
    (void (*)(struct WeaponObj*))frost_tower_despawn,
    (void (*)(struct WeaponObj*))frost_tower_despawn,
};

void (*frost_tower_step_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))frost_tower_form,
    (void (*)(struct WeaponObj*))frost_tower_check_ground,
    (void (*)(struct WeaponObj*))frost_tower_fall,
};

void (*frost_tower_charged_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_80094280,
    (void (*)(struct WeaponObj*))func_800942E8,
    (void (*)(struct WeaponObj*))frost_tower_despawn,
    (void (*)(struct WeaponObj*))frost_tower_despawn,
};

void (*frost_tower_charged_part_state_funcs[])(struct WeaponObj*) = {
    (void (*)(struct WeaponObj*))func_800944B8,
    (void (*)(struct WeaponObj*))frost_tower_charged_part_main,
    (void (*)(struct WeaponObj*))frost_tower_despawn,
    (void (*)(struct WeaponObj*))frost_tower_despawn,
};

u16 frost_tower_charged_part_offsets[] = {
    0x0000,
    0x0000,
    0x0040,
    0x0060,
    0x0028,
    0x0070,
};

u8 frost_sparkle_animations[] = {
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x08,
    0x05,
};

s32 frost_particle_x_vels[] = {
    (s32)0xFFFD0000,
    (s32)0xFFFE0000,
    (s32)0x00018000,
    (s32)0x00028000,
    (s32)0xFFFC8000,
    (s32)0xFFFD8000,
    (s32)0x00020000,
    (s32)0x00030000,
};

s32 frost_particle_y_vels[] = {
    (s32)0x00038000,
    (s32)0x00048000,
    (s32)0x00060000,
    (s32)0x00030000,
    (s32)0x00040000,
    (s32)0x00050000,
    (s32)0x00058000,
    (s32)0x00028000,
};
