// MainObj, main_object_update_funcs[65]
// 8007DC54..800806A0
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_64_cyber_peacock.h"
#include "main/mains/main_65_magma_dragoon.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/player_common.h"
#include "main/128C4.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/visuals/visual_03_small_effect.h"
#include "main/collision_bounds.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#include "main/collision_bounds.h"
#endif

extern struct Unk_unk68 magma_dragoon_terrain_box;

extern struct Unk_unk68 magma_dragoon_crouch_hurt_box;

extern struct Unk_unk68 magma_dragoon_leap_attack_box;
extern struct Unk_unk68 magma_dragoon_punch_attack_box;

extern struct Unk_unk68 magma_dragoon_fire_volley_debris;

// magma_dragoon_intro_funcs
extern void (*magma_dragoon_intro_funcs[])(struct MainObj*);

void magma_dragoon_intro_leap(struct MainObj*);
void magma_dragoon_intro_descend(struct MainObj*);
void magma_dragoon_intro_land(struct MainObj*);
void magma_dragoon_intro_pose(struct MainObj*);
void magma_dragoon_intro_start_health_bar(struct MainObj*);
void magma_dragoon_intro_ready(struct MainObj*);
void magma_dragoon_intro_fill_health(struct MainObj*);

// magma_dragoon_dive_kick_funcs
extern void (*magma_dragoon_dive_kick_funcs[])(struct MainObj*);
void magma_dragoon_dive_kick_jump(struct MainObj*);
void magma_dragoon_dive_kick_rise(struct MainObj*);

void func_8007E848(struct MainObj*);

// magma_dragoon_flame_burst_funcs
extern void (*magma_dragoon_flame_burst_funcs[])(struct MainObj*);
void magma_dragoon_flame_burst_start(struct MainObj*);

// magma_dragoon_fire_volley_funcs
extern void (*magma_dragoon_fire_volley_funcs[])(struct MainObj*);
void magma_dragoon_fire_volley_start(struct MainObj*);

void magma_dragoon_fire_volley_wait(struct MainObj*);

// magma_dragoon_breath_funcs
extern void (*magma_dragoon_breath_funcs[])(struct MainObj*);
void magma_dragoon_breath_start(struct MainObj*);

// magma_dragoon_leap_center_funcs
extern void (*magma_dragoon_leap_center_funcs[])(struct MainObj*);
void magma_dragoon_leap_center_start(struct MainObj*);
void magma_dragoon_leap_center_glide(struct MainObj*);
void magma_dragoon_leap_center_land(struct MainObj*);
void magma_dragoon_leap_center_recover(struct MainObj*);

// magma_dragoon_leap_wall_funcs
extern void (*magma_dragoon_leap_wall_funcs[])(struct MainObj*);
void magma_dragoon_leap_wall_start(struct MainObj*);

void magma_dragoon_leap_wall_finish(struct MainObj*);

// magma_dragoon_fireball_funcs
extern void (*magma_dragoon_fireball_funcs[])(struct MainObj*);
void magma_dragoon_fireball_start(struct MainObj*);

// magma_dragoon_fireball_low_funcs
extern void (*magma_dragoon_fireball_low_funcs[])(struct MainObj*);
void magma_dragoon_fireball_low_start(struct MainObj*);

// magma_dragoon_rising_punch_funcs
extern void (*magma_dragoon_rising_punch_funcs[])(struct MainObj*);
void magma_dragoon_rising_punch_start(struct MainObj*);

void magma_dragoon_rising_punch_rise(struct MainObj*);
void magma_dragoon_rising_punch_land(struct MainObj*);
void magma_dragoon_rising_punch_recover(struct MainObj*);

// magma_dragoon_stagger_funcs
extern void (*magma_dragoon_stagger_funcs[])(struct MainObj*);

void magma_dragoon_stagger_rise(struct MainObj*);
void magma_dragoon_stagger_burn(struct MainObj*);
void magma_dragoon_stagger_fall(struct MainObj*);
void magma_dragoon_stagger_recover(struct MainObj*);

// magma_dragoon_step_funcs
void magma_dragoon_hold(struct MainObj* arg0);
void magma_dragoon_intro(struct MainObj* arg0);

void magma_dragoon_dive_kick(struct MainObj* arg0);
void magma_dragoon_flame_burst(struct MainObj* arg0);
void magma_dragoon_fire_volley(struct MainObj* arg0);
void magma_dragoon_breath(struct MainObj* arg0);
void magma_dragoon_leap_center(struct MainObj* arg0);
void magma_dragoon_leap_wall(struct MainObj* arg0);
void magma_dragoon_fireball(struct MainObj* arg0);
void magma_dragoon_fireball_low(struct MainObj* arg0);
void magma_dragoon_rising_punch(struct MainObj* arg0);
void magma_dragoon_stagger(struct MainObj* arg0);

// magma_dragoon_death_funcs
extern void (*magma_dragoon_death_funcs[])(struct MainObj*);
void magma_dragoon_death_start(struct MainObj*);

void magma_dragoon_death_wait_explosion(struct MainObj*, s32, s32);
void magma_dragoon_death_wait_dialog(struct MainObj*);
void magma_dragoon_death_smoke(struct MainObj*);
void magma_dragoon_death_vanish(struct MainObj*);
void magma_dragoon_death_end(struct MainObj* arg0);

// magma_dragoon_state_funcs
extern void (*magma_dragoon_state_funcs[])(struct MainObj*);

void magma_dragoon_death(struct MainObj* arg0);

s32 func_8007DD0C(struct MainObj* self);

// cyber_peacock_intro_init

void cyber_peacock_intro_wait_player(struct MainObj* self);

void cyber_peacock_intro_appear_start(struct MainObj* self);

void cyber_peacock_intro_pose(struct MainObj* self);

void cyber_peacock_intro_start_health_bar(struct MainObj* self);

void cyber_peacock_intro_fill_health(struct MainObj* self);

void cyber_peacock_intro_appear(struct MainObj* self);

void cyber_peacock_intro(struct MainObj* self);

void cyber_peacock_face_player(struct MainObj* self);

u8 cyber_peacock_choose_attack(struct MainObj* self);

void cyber_peacock_start_teleport(struct MainObj* self);

void cyber_peacock_teleport_start(struct MainObj* self);

void cyber_peacock_teleport_vanish(struct MainObj* self);

// cyber_peacock_teleport_choose

void cyber_peacock_teleport_appear(struct MainObj* self);

void cyber_peacock_teleport_wait(struct MainObj* self);

void cyber_peacock_teleport(struct MainObj* self);

void cyber_peacock_rising_kick_start(struct MainObj* self);

void cyber_peacock_rising_kick_jump(struct MainObj* self);

void cyber_peacock_rising_kick_rise(struct MainObj* self);

void cyber_peacock_rising_kick_finish(struct MainObj* self);

void cyber_peacock_rising_kick(struct MainObj* self);

void cyber_peacock_slash_start(struct MainObj* self);

void cyber_peacock_slash_swing(struct MainObj* self);

void cyber_peacock_slash_finish(struct MainObj* self);

void cyber_peacock_slash(struct MainObj* self);

void cyber_peacock_spawn_laser_target(struct MainObj* self);

void cyber_peacock_spawn_missile(struct MainObj* self);

void cyber_peacock_aiming_laser_start(struct MainObj* self);

void cyber_peacock_aiming_laser_raise(struct MainObj* self);

void cyber_peacock_aiming_laser_target(struct MainObj* self);

void cyber_peacock_aiming_laser_wait(struct MainObj* self);

void cyber_peacock_aiming_laser_fire(struct MainObj* self);

void cyber_peacock_aiming_laser_next(struct MainObj* self);

void cyber_peacock_aiming_laser_finish(struct MainObj* self);

void cyber_peacock_aiming_laser(struct MainObj* self);

void cyber_peacock_attack(struct MainObj* self);

// cyber_peacock_hit_vanish

// cyber_peacock_guard_vanish

// cyber_peacock_main

void cyber_peacock_death_start(struct MainObj* self);

void cyber_peacock_death_explode(struct MainObj* self);

void cyber_peacock_death_finish(struct MainObj* self);

void cyber_peacock_death(struct BarObj* self);

void cyber_peacock_update(struct MainObj* self);

void magma_dragoon_spawn_flames(struct AnimatedObj* self, u32 arg1)
{
    struct MiscObj* obj;

    obj = find_free_misc_obj();
    if (obj != 0) {
        obj->active = 0x41;
        obj->id = 0x26;
        obj->unk2 = 2;
        obj->ext.misc_7.position = self;
    }

    obj = find_free_misc_obj();
    if (obj != 0) {
        obj->active = 0x41;
        obj->id = 0x26;
        obj->unk2 = 3;
        obj->ext.misc_7.position = self;
    }

    if (arg1 < 2U) {
        obj = find_free_misc_obj();
        if (obj != 0) {
            obj->active = 0x41;
            obj->id = 0x26;
            obj->unk2 = arg1;
            obj->ext.misc_7.position = self;
        }
    }
}

// cyber_peacock_is_player_near_random
#ifdef MMX4_SATURN
#define DRAGOON_NEAR_X 64
#define DRAGOON_NEAR_CHANCE 96

s32 func_8007DD0C(struct MainObj* self)
{
    s32 dx = g_Player.x_pos.i.hi - self->x_pos.i.hi;

    if (dx < 0)
        dx = self->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (dx > DRAGOON_NEAR_X)
        return 0;
    return (s32)get_random() <= DRAGOON_NEAR_CHANCE;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_65_magma_dragoon", func_8007DD0C);
#endif

// magma_dragoon_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007DD98(struct MainObj* arg0);
void func_8007F174(struct MainObj* arg0);
void func_8007FD24(struct MainObj* arg0);
void func_8007E4C8(struct MainObj* arg0);
void func_8007E6F8(struct MainObj* arg0);
void func_8007E95C(struct MainObj* arg0);
void func_8007F780(struct MainObj* arg0);
void func_8007FAA4(struct MainObj* arg0);
void func_8007FFFC(struct MainObj* arg0);
extern void* magma_dragoon_animations[38];
extern struct Unk_unk68 D_80107D7C[];
extern void (*magma_dragoon_step_funcs[14])(struct MainObj*);
extern struct Unk_unk68 magma_dragoon_dive_kick_attack_box;
void magma_dragoon_face_player(struct MainObj* arg0);
static struct ShotObj* main_65_spawn_shot(struct MainObj* arg0, s8 subtype)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x29;
        shot->unk2 = subtype;
        shot->unk7C = (struct WeaponObj*)arg0;
    }
    return shot;
}
static void main_65_throw(struct MainObj* arg0, s16 y_offset)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 1)
        return;
    shot = main_65_spawn_shot(arg0, 3);
    if (shot != NULL) {
        shot->x_pos.i.hi = arg0->x_pos.i.hi + (arg0->unk15 != 0 ? 0x17 : -0x17);
        shot->y_pos.i.hi = arg0->y_pos.i.hi + y_offset;
        func_8001540C(2, 4, arg0);
    }
    arg0->animation_step.fields.event = 0;
}
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007DD98(struct MainObj* arg0)
{
    if (engine_obj.stage == 0xC) {
        magma_dragoon_arena_right = 0x2B0;
        magma_dragoon_arena_center = 0x200;
        magma_dragoon_arena_left = 0x150;
        magma_dragoon_arena_floor = 0x690;
        magma_dragoon_arena_ceiling = 0x670;
    } else {
        magma_dragoon_arena_right = 0x1590;
        magma_dragoon_arena_center = 0x14E0;
        magma_dragoon_arena_left = 0x1430;
        magma_dragoon_arena_floor = 0x280;
        magma_dragoon_arena_ceiling = 0x260;
    }

    arg0->animation_table = (const u8* const*)magma_dragoon_animations;
    arg0->unk16 = VISUAL_SATURN_LAYER(5);
    arg0->attack_box = &magma_dragoon_attack_box;
    arg0->invincibility_timer = 0;
    arg0->ext.main_65.flash_timer = 0;
    arg0->unk62 = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->terrain_box = NULL;
    arg0->collision_data = D_80107D7C;
    arg0->hurt_box = NULL;
    arg0->unk40 = (u16)((OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0x160));

    if (engine_obj.stage == 0xC) {
        arg0->unk42 = OBJECT_CLUT(0x7888);
        arg0->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
        arg0->x_pos.i.hi = 0x2CE;
        arg0->y_pos.i.hi = 0x69F;
    } else {
        arg0->x_pos.i.hi = 0x15A5;
        arg0->y_pos.i.hi = 0x28F;
    }

    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    engine_obj.unk25 = 0;
    engine_obj.boss_ptr = arg0;
    arg0->contact_damage = 4;
    arg0->hp = 0;
    arg0->air_state = 0;
    arg0->unk5 = 2;
    arg0->state++;
    if (engine_obj.stage == 4)
        engine_obj.checkpoint = 3;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_65_magma_dragoon", func_8007DD98);
#endif

void magma_dragoon_intro_warning(struct MainObj* self)
{
    struct EffectObj* effect;

    effect = find_free_effect_obj();
    if (effect != 0) {
        effect->active = 1;
        effect->id = 0x18;
        effect->x_pos.i.hi = self->x_pos.i.hi;
        effect->y_pos.i.hi = self->y_pos.i.hi;
        self->ext.main_65.object = (struct MainObj*)effect;
    }
    self->unk15 = 0;
    self->unk6++;
    player_start_script_action(0x14, PLAYER_FACING_RIGHT);
    if (engine_obj.stage == 0xC) {
        background_objects[0].unk26 = 0x1B0;
        background_objects[0].unk24 = 0x1B0;
        background_objects[0].unk2A = 0x5FB;
        background_objects[0].unk28 = 0x5FB;
    } else {
        background_objects[0].unk26 = 0x1490;
        background_objects[0].unk24 = 0x1490;
        background_objects[0].unk2A = 0x1EB;
        background_objects[0].unk28 = 0x1EB;
    }
}

void magma_dragoon_intro_leap(struct MainObj* self)
{
    if (self->ext.main_65.object->active == 0) {
        self->unk6++;
        self->x_speed = 0;
        self->y_speed = FIXED(2);
        self->x_accel = FIXED(0.0078125);
        set_animation(self, 0xF);
        magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 0);
        self->air_state = 1;
        self->unk7E = 0x14;
    }
}

void magma_dragoon_intro_descend(struct MainObj* self)
{
    if ((self->y_pos.i.hi - background_objects[0].y_pos.i.hi) < 0x20) {
        self->unk6++;
        self->x_speed = FIXED(-2);
        self->y_speed = FIXED(-2);
        self->x_accel = 0;
        self->gravity = FIXED(0.1875);
        self->terrain_box = &magma_dragoon_terrain_box;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_intro_land(struct MainObj* self)
{
    if (self->collision_flags & 8) {
        set_animation(self, 0x10);
        self->air_state = 0;
        func_8001540C(2, SATURN_SOUND(2, 0x7F), self);
        self->unk6++;
        self->x_speed = 0;
        self->y_speed = 0;
        self->gravity = 0;
        magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 2);
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_intro_pose(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 0x11);
        self->unk6++;
        if (engine_obj.stage == 4) {
            func_8002217C(
                0xB, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_intro_start_health_bar(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        self->unk6++;
        play_boss_voice(3);
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_intro_ready(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0 && update_boss_music_delay() == 0) {
        set_animation(self, 0x12);
        engine_obj.enable_boss = 1;
        self->unk6++;
        self->unk7E = 3;
        self->x_speed = 0;
        self->y_speed = 0;
        self->gravity = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_intro_fill_health(struct MainObj* self)
{
    if (self->hp < 0x30) {
        if (--self->unk7E == 0) {
            func_8001540C(0, SATURN_SOUND(0xE, 0x14), 0);
            self->unk7E = 3;
        }
        self->hp++;
        update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
    } else {
        set_animation(self, 0);
        self->unk5 = 3;
        self->unk6 = 0;
        self->hurt_box = &magma_dragoon_hurt_box;
        player_end_script_action();
        if (engine_obj.stage == 0xC) {
            background_objects[0].unk26 = 0x110;
            background_objects[0].unk24 = 0x1B0;
        } else {
            background_objects[0].unk26 = 0x13F0;
            background_objects[0].unk24 = 0x1490;
        }
        background_objects[0].unk48 = 4;
        update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
    }
}

void magma_dragoon_intro(struct MainObj* self)
{
    magma_dragoon_intro_funcs[self->unk6](self);
}

void magma_dragoon_face_player(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi > self->x_pos.i.hi) {
        self->unk15 = PLAYER_FACING_RIGHT;
    } else {
        self->unk15 = 0;
    }
}

// magma_dragoon_think
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007E4C8(struct MainObj* arg0)
{
    u8 roll;

    magma_dragoon_face_player(arg0);
    roll = get_random() & 0xF;
    arg0->ext.main_65.attack_repeat = 0;
    if (arg0->hp >= 0x19) {
        if (roll < 6)
            arg0->ext.main_65.attack = 0;
        else if (roll < 10)
            arg0->ext.main_65.attack = 1;
        else if (roll < 13)
            arg0->ext.main_65.attack = 2;
        else
            arg0->ext.main_65.attack = 3;
    } else {
        if (roll < 6)
            arg0->ext.main_65.attack = 4;
        else if (roll < 9)
            arg0->ext.main_65.attack = 5;
        else
            arg0->ext.main_65.attack = 6;
    }
    switch (arg0->ext.main_65.attack) {
    case 0:
    case 1:
    case 4:
        arg0->unk5 = 4;
        break;
    case 2:
    case 5:
        arg0->unk5 = 5;
        break;
    case 3:
        arg0->unk5 = 8;
        break;
    case 6:
        arg0->unk5 = 0xA;
        break;
    }
    animate_object(ANIMATED_OBJECT(arg0));
    update_on_screen(BASE_OBJECT(arg0), 0x40, 0x40);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_65_magma_dragoon", func_8007E4C8);
#endif

void magma_dragoon_dive_kick_jump(struct MainObj* self)
{
    magma_dragoon_face_player(self);
    set_animation(self, 3);
    magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 2);
    self->air_state = 1;
    func_8001540C(2, SATURN_SOUND(0, 0x7D), self);
    self->unk6 = (u8)self->unk6 + 1;
    self->x_speed = self->unk15 != 0 ? FIXED(0.75) : FIXED(-0.75);
    self->y_speed = FIXED(4);
    self->x_accel = FIXED(0.03125);
    self->gravity = FIXED(-0.03125);
    self->ext.main_65.jump_start_y = (u16)self->y_pos.i.hi;
}

void magma_dragoon_dive_kick_rise(struct MainObj* self)
{
    if ((self->ext.main_65.jump_start_y - self->y_pos.i.hi) > 0x50) {
        self->unk6++;
        set_animation(self, 4);
        func_8001540C(2, SATURN_SOUND(1, 0x7E), self);
        self->contact_damage = 6;
        self->y_speed = FIXED(-6);
        self->x_accel = 0;
        self->gravity = 0;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

// magma_dragoon_dive_kick_dive
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007E6F8(struct MainObj* arg0)
{
    s16 x;

    arg0->attack_box = arg0->animation_step.fields.event != 0 ? &magma_dragoon_dive_kick_attack_box : &magma_dragoon_attack_box;
    if (arg0->collision_flags & 8) {
        arg0->unk6++;
        set_animation(arg0, 6);
        arg0->attack_box = &magma_dragoon_attack_box;
        arg0->contact_damage = 4;
        arg0->air_state = 0;
        func_8001540C(2, SATURN_SOUND(2, 0x7F), arg0);
    }
    if (arg0->animation_step.fields.event == 2) {
        x = arg0->x_pos.i.hi;
        if (x < g_Player.x_pos.i.hi)
            arg0->unk15 = x < magma_dragoon_arena_right - 0x50 ? PLAYER_FACING_RIGHT : 0;
        else
            arg0->unk15 = x < magma_dragoon_arena_left + 0x50 ? PLAYER_FACING_RIGHT : 0;
        arg0->x_speed = arg0->unk15 != 0 ? 0x80000 : -0x80000;
    }
    if (arg0->animation_step.fields.event == 1)
        move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_65_magma_dragoon", func_8007E6F8);
#endif

// magma_dragoon_dive_kick_land
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_65_magma_dragoon", func_8007E848);
#else
void func_8007E848(struct MainObj* self)
{
    s32 state;

    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = 0;
        if (self->ext.main_65.attack == 0) {
            state = 0xA;
        } else if (self->ext.main_65.attack == 1 || self->ext.main_65.attack_repeat++ == 0) {
            state = 0xB;
        } else {
            state = 0xC;
        }
        self->unk5 = state;
    }
    animate_object(ANIMATED_OBJECT(self));
}
#endif

void magma_dragoon_dive_kick(struct MainObj* self)
{
    magma_dragoon_dive_kick_funcs[self->unk6](self);
    update_on_screen((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_flame_burst_start(struct MainObj* self)
{
    magma_dragoon_face_player(self);
    set_animation(ANIMATED_OBJECT(self), 0xB);
    self->unk6++;
}

// magma_dragoon_flame_burst_fire
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007E95C(struct MainObj* arg0)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        shot = main_65_spawn_shot(arg0, 0);
        func_8001540C(2, (arg0->animation_step.fields.event & 1) ? 6 : 7, shot);
        arg0->animation_step.fields.event = 0;
    }
    if (arg0->animation_step.fields.relative_step != 0)
        return;
    arg0->unk6 = 0;
    if (arg0->ext.main_65.attack == 6) {
        arg0->unk5 = 6;
    } else if (arg0->ext.main_65.attack == 5) {
        arg0->unk5 = 7;
    } else {
        arg0->unk5 = 3;
        set_animation(arg0, 0);
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_65_magma_dragoon", func_8007E95C);
#endif

void magma_dragoon_flame_burst(struct MainObj* self)
{
    magma_dragoon_flame_burst_funcs[self->unk6](self);
    update_on_screen((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_fire_volley_start(struct MainObj* self)
{
    magma_dragoon_face_player(self);
    set_animation(self, 0xC);
    func_8001540C(2, SATURN_SOUND(3, 0x80), self);
    self->unk6++;
}

void magma_dragoon_fire_volley_fire(struct MainObj* self)
{
    s8 event;
    s8 shot_index;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    event = self->animation_step.fields.event;
    if (event != 0) {
        if (event == 0xA) {
            self->unk7C = 0xF0;
            self->unk6 = (u8)self->unk6 + 1;
        }
        spawn_debris(4, &magma_dragoon_fire_volley_debris, self);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x29;
            shot->unk2 = 1;
            shot->unk7C = WEAPON_OBJECT(self);
            shot_index = self->animation_step.fields.event;
            if (shot_index == 0xA) {
                self->ext.main_65.object = MAIN_OBJECT(shot);
                shot->unk7 = 1;
            } else {
                shot->unk7 = shot_index - 1;
            }
        }
        if ((u8)self->animation_step.fields.event & 1) {
            func_8001540C(2, SATURN_SOUND(6, 0x84), shot);
        } else {
            func_8001540C(2, SATURN_SOUND(7, 0x84), shot);
        }
        self->animation_step.fields.event = 0;
    }
}

void magma_dragoon_fire_volley_wait(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->unk5 = 9;
        self->unk6 = 0;
    }
}

void magma_dragoon_fire_volley(struct MainObj* self)
{
    magma_dragoon_fire_volley_funcs[self->unk6](self);
    update_on_screen((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_breath_start(struct MainObj* self)
{
    if (self->x_pos.i.hi > magma_dragoon_arena_center) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
    set_animation(self, 0xA);
    func_8001540C(2, SATURN_SOUND(3, 0x80), self);
    self->unk6++;
}

void magma_dragoon_breath_fire(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x29;
            shot->unk2 = 2;
            shot->unk7C = WEAPON_OBJECT(self);
        }
        self->ext.main_65.object = (struct MainObj*)shot;
        self->animation_step.fields.event = 0;
    }
    if (self->animation_step.fields.event == 2) {
        self->ext.main_65.object->unk6++;
        self->animation_step.fields.event = 0;
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = 0;
        if (self->ext.main_65.attack == 3) {
            self->unk5 = 0xC;
        } else {
            self->unk5 = 3;
        }
        set_animation(self, 0);
    }
}

void magma_dragoon_breath(struct MainObj* self)
{
    magma_dragoon_breath_funcs[self->unk6](self);
    update_on_screen((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_leap_center_start(struct MainObj* self)
{
    if (self->x_pos.i.hi > magma_dragoon_arena_center) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
    set_animation(self, 3);
    magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 2);
    self->air_state = 1;
    func_8001540C(2, SATURN_SOUND(0, 0x7D), self);
    self->x_speed = self->unk15 != 0 ? FIXED(5) : FIXED(-5);
    self->y_speed = FIXED(3);
    self->x_accel = 0;
    self->gravity = FIXED(-0.03125);
    self->attack_box = (const u8*)&magma_dragoon_leap_attack_box;
    self->unk6++;
}

void magma_dragoon_leap_center_glide(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));

    if (self->y_pos.i.hi < magma_dragoon_arena_ceiling) {
        self->y_pos.i.hi = magma_dragoon_arena_ceiling;
        self->y_speed = 0;
        self->gravity = 0;
    }

    if (self->unk15 == 0) {
        if (self->x_pos.i.hi < (magma_dragoon_arena_center - 0x10)) {
            self->gravity = FIXED(0.12109375);
            self->unk6++;
            return;
        }
    } else if (self->x_pos.i.hi > (magma_dragoon_arena_center + 0x10)) {
        self->gravity = FIXED(0.12109375);
        self->unk6++;
    }
}

void magma_dragoon_leap_center_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->unk6++;
        set_animation(self, 6);
        magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 2);
        self->air_state = 0;
        func_8001540C(2, SATURN_SOUND(2, 0x7F), self);
    }
}

void magma_dragoon_leap_center_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->attack_box = (const u8*)&magma_dragoon_attack_box;
        self->unk6 = 0;
        self->unk5 = 7;
    }
}

void magma_dragoon_leap_center(struct MainObj* self)
{
    magma_dragoon_leap_center_funcs[self->unk6](self);
    update_on_screen((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_leap_wall_start(struct MainObj* self)
{
    self->ext.main_65.leap_frames = 0x40;
    magma_dragoon_face_player(self);
    self->y_speed = FIXED(6);
    self->x_accel = 0;
    self->gravity = FIXED(0.1875);
    self->attack_box = (const u8*)&magma_dragoon_leap_attack_box;
    set_animation(self, 3);
    magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 2);
    self->air_state = 1;
    func_8001540C(2, SATURN_SOUND(0, 0x7D), self);
    if (self->x_pos.i.hi < magma_dragoon_arena_center) {
        self->ext.main_65.leap_to_right = 1;
    } else {
        self->ext.main_65.leap_to_right = 0;
    }
    self->unk6++;
}

// magma_dragoon_leap_wall_air
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007F174(struct MainObj* arg0)
{
    s32 distance;

    if (arg0->ext.main_65.leap_frames != 0) {
        if (arg0->ext.main_65.leap_to_right != 0)
            distance = magma_dragoon_arena_right - (arg0->x_pos.i.hi + 0x30);
        else
            distance = (arg0->x_pos.i.hi - 0x30) - magma_dragoon_arena_left;
        if (distance < 0)
            distance = -distance;
        arg0->x_speed = (distance << 16)
            / arg0->ext.main_65.leap_frames;
        if (arg0->ext.main_65.leap_to_right == 0)
            arg0->x_speed = -arg0->x_speed;
        arg0->ext.main_65.leap_frames--;
    }

    move_with_gravity(ANIMATED_OBJECT(arg0));
    if ((arg0->collision_flags & 8) != 0 && arg0->y_speed < 0) {
        if (arg0->ext.main_65.leap_to_right != 0)
            arg0->x_pos.i.hi = magma_dragoon_arena_right - 0x30;
        else
            arg0->x_pos.i.hi = magma_dragoon_arena_left + 0x30;
        set_animation(arg0, 6);
        magma_dragoon_spawn_flames(ANIMATED_OBJECT(arg0), 2);
        arg0->air_state = 0;
        func_8001540C(2, SATURN_SOUND(2, 0x7F), arg0);
        arg0->x_speed = 0;
        arg0->y_speed = 0;
        arg0->gravity = 0;
        arg0->unk6++;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_65_magma_dragoon", func_8007F174);
#endif

void magma_dragoon_leap_wall_finish(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        if (self->ext.main_65.attack == 3) {
            self->unk5 = 5;
        } else {
            self->unk5 = 3;
            set_animation(self, 0);
        }
        self->unk6 = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void magma_dragoon_leap_wall(struct MainObj* self)
{
    magma_dragoon_leap_wall_funcs[self->unk6](self);
    update_on_screen((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_fireball_start(struct MainObj* self)
{
    magma_dragoon_face_player(self);
    set_animation(self, 8);
    self->attack_box = (const u8*)&magma_dragoon_leap_attack_box;
    self->unk6++;
}

// magma_dragoon_fireball_fire
void func_8007F404(struct MainObj* self)
{
    s32 x;

    animate_object(ANIMATED_OBJECT(self));

    if (self->animation_step.fields.event == 1) {
        struct ShotObj* shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x29;
            shot->unk2 = 3;
            shot->unk7C = WEAPON_OBJECT(self);
            x = self->x_pos.i.hi;
            shot->x_pos.i.hi = self->unk15 ? x + 0x17 : x - 0x17;
            shot->y_pos.i.hi = self->y_pos.i.hi;
            func_8001540C(2, SATURN_SOUND(4, 0x81), self);
        }
        self->animation_step.fields.event = 0;
    }

    if (self->animation_step.fields.relative_step == 0) {
        if (self->ext.main_65.attack == 0) {
            self->unk5 = 0xB;
        } else if (self->ext.main_65.attack == 1) {
            self->unk5 = &func_8007DD0C != NULL ? 0xC : 9;
        } else {
            if (self->ext.main_65.attack_repeat++ == 0) {
                self->unk5 = 0xB;
            } else {
                self->unk5 = 5;
            }
        }
        self->unk6 = 0;
    }
}

void magma_dragoon_fireball(struct MainObj* self)
{
    magma_dragoon_fireball_funcs[self->unk6](self);
    update_on_screen((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_fireball_low_start(struct MainObj* self)
{
    magma_dragoon_face_player(self);
    set_animation(self, 9);
    self->attack_box = (const u8*)&magma_dragoon_leap_attack_box;
    self->unk6++;
}

// magma_dragoon_fireball_low_fire
void func_8007F5B0(struct MainObj* self)
{
    s32 x;

    animate_object(ANIMATED_OBJECT(self));

    if (self->animation_step.fields.event == 1) {
        struct ShotObj* shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x29;
            shot->unk2 = 3;
            shot->unk7C = WEAPON_OBJECT(self);
            x = self->x_pos.i.hi;
            shot->x_pos.i.hi = self->unk15 ? x + 0x17 : x - 0x17;
            shot->y_pos.i.hi = self->y_pos.i.hi + 0x28;
            func_8001540C(2, SATURN_SOUND(4, 0x81), self);
        }
        self->animation_step.fields.event = 0;
    }

    if (self->animation_step.fields.relative_step == 0) {
        self->attack_box = &magma_dragoon_leap_attack_box;
        self->unk6 = 0;
        if (self->ext.main_65.attack == 0) {
            self->unk5 = 9;
        } else if (self->ext.main_65.attack == 4) {
            self->unk5 = 4;
        } else {
            self->unk5 = 0xA;
        }
    }
}

void magma_dragoon_fireball_low(struct MainObj* self)
{
    magma_dragoon_fireball_low_funcs[self->unk6](self);
    if ((self->animation_step.fields.frame_index == 0x19 || self->animation_step.fields.frame_index == 0x1A)) {
        self->hurt_box = (const u8*)&magma_dragoon_crouch_hurt_box;
    } else {
        self->hurt_box = (const u8*)&magma_dragoon_hurt_box;
    }
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_rising_punch_start(struct MainObj* self)
{
    self->contact_damage = 8;
    magma_dragoon_face_player(self);
    set_animation(self, 5);
    func_8001540C(2, SATURN_SOUND(5, 0x82), self);
    self->attack_box = (const u8*)&magma_dragoon_leap_attack_box;
    self->unk6++;
}

// magma_dragoon_rising_punch_charge
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007F780(struct MainObj* arg0)
{
    s16 distance;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 1)
        return;
    arg0->air_state = 1;
    arg0->y_speed = 0x40000;
    arg0->gravity = 0x1C00;
    arg0->animation_step.fields.event = 0;
    arg0->unk6++;
    arg0->unk15 = g_Player.x_pos.i.hi < arg0->x_pos.i.hi ? 0 : PLAYER_FACING_RIGHT;
    distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (distance < 0)
        distance = -distance;
    arg0->x_speed = arg0->unk15 != 0 ? 0x60000 : -0x60000;
    if (distance < 0x30)
        arg0->x_accel = -0x8000;
    else if (distance < 0x60)
        arg0->x_accel = -0x4000;
    else
        arg0->x_accel = -0x2000;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_65_magma_dragoon", func_8007F780);
#endif

void magma_dragoon_rising_punch_rise(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));

    if (self->animation_step.fields.event == 2) {
        self->attack_box = (const u8*)&magma_dragoon_punch_attack_box;
    }

    if (self->unk15 != 0 ? self->x_speed < 0 : self->x_speed >= 0) {
        self->x_speed = 0;
        self->x_accel = 0;
    }

    if (self->y_speed < 0) {
        self->x_speed = 0;
        self->x_accel = 0;
        self->unk6++;
        set_animation(self, 7);
        self->attack_box = (const u8*)&magma_dragoon_attack_box;
    }
}

void magma_dragoon_rising_punch_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->unk6++;
        set_animation(self, 6);
        self->attack_box = (const u8*)&magma_dragoon_attack_box;
        self->contact_damage = 4;
        magma_dragoon_spawn_flames(ANIMATED_OBJECT(self), 2);
        self->air_state = 0;
        func_8001540C(2, SATURN_SOUND(2, 0x7F), self);
    }
}

void magma_dragoon_rising_punch_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step != 0) {
        return;
    }
    self->unk6 = 0;
    if ((self->y_pos.i.hi <= magma_dragoon_arena_floor) && (self->ext.main_65.attack == 3)) {
        if (self->ext.main_65.attack_repeat++ == 0) {
            return;
        }
    }
    self->unk5 = 9;
}

void magma_dragoon_rising_punch(struct MainObj* self)
{
    magma_dragoon_rising_punch_funcs[self->unk6](self);
    update_on_screen((struct BaseObj*)self, 0x40, 0x40);
}

// magma_dragoon_stagger_start
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007FAA4(struct MainObj* arg0)
{
    struct MiscObj* misc;

    set_animation(arg0, 0xD);
    arg0->attack_box = &magma_dragoon_attack_box;
    arg0->hurt_box = &magma_dragoon_hurt_box;
    arg0->y_speed = 0x40000;
    arg0->contact_damage = 4;
    arg0->gravity = 0x1C00;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x26;
        misc->unk2 = 4;
        misc->ext.misc_7.position = arg0;
        arg0->ext.main_65.object = (struct MainObj*)misc;
    }
    arg0->unk6++;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_65_magma_dragoon", func_8007FAA4);
#endif

void magma_dragoon_stagger_rise(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_speed < 0) {
        self->unk6++;
    }
}

void magma_dragoon_stagger_burn(struct MainObj* self)
{
    struct MainObj* child;

    animate_object(ANIMATED_OBJECT(self));
    child = self->ext.main_65.object;
    if (child->animation_step.fields.relative_step < 0) {
        child->state = 2;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->x_speed = 0;
        self->x_accel = 0;
        self->unk6++;
    }
}

void magma_dragoon_stagger_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->unk6++;
        set_animation(self, 0);
        if (self->ext.main_65.flash_timer & 1) {
            self->ext.main_65.flash_timer = 0x3D;
        } else {
            self->ext.main_65.flash_timer = 0x3E;
        }
        self->unk7C = 1;
    }
}

void magma_dragoon_stagger_recover(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (--self->unk7C == 0) {
        self->unk5 = 9;
        self->unk6 = 0;
    }
}

void magma_dragoon_stagger(struct MainObj* self)
{
    magma_dragoon_stagger_funcs[self->unk6](self);
    update_on_screen((struct BaseObj*)self, 0x40, 0x40);
}

void magma_dragoon_hold(struct MainObj* self)
{
}

// magma_dragoon_main
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007FD24(struct MainObj* arg0)
{
    s32 hit = func_8002DD04(arg0);
    u8 flash;

    if (hit < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
        update_on_screen(BASE_OBJECT(arg0), 0x40, 0x40);
        return;
    }

    if (hit > 0 && hit != 0x7F) {
        arg0->ext.main_65.flash_timer = (hit == 0x19 || hit == 0x1A) ? 2 : 0x1E;
        arg0->collision_data = D_801060F0;
        if (hit == 8 || hit == 0x11) {
            arg0->unk5 = 0xD;
            arg0->unk6 = 0;
            arg0->ext.main_65.flash_timer = 0xFF;
        }
    }

    flash = arg0->ext.main_65.flash_timer;
    if (flash != 0) {
        arg0->ext.main_65.flash_timer--;
        if ((flash & 2) != 0)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (arg0->ext.main_65.flash_timer == 0) {
            arg0->collision_data = D_80107D7C;
            arg0->unk42 &= 0x7FFF;
        }
    }

    magma_dragoon_step_funcs[(u8)arg0->unk5](arg0);
    CollisionRelated((struct PlayerObj*)arg0);
    func_8002D9BC(arg0);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_65_magma_dragoon", func_8007FD24);
#endif

void magma_dragoon_death_start(struct MainObj* self)
{
    self->unk7C = 0x7F;
    self->unk5++;
    self->unk42 &= 0x7FFF;
    self->unk7E = 0x19;
    self->invincibility_timer = 0x19;
    set_animation(self, 0xD);
    player_start_script_action(0x14, g_Player.unk15);
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

// magma_dragoon_death_flash
void func_8007FF00(struct MainObj* arg0)
{
    struct EffectObj* effect;

    if (--arg0->unk7C == 0) {
        arg0->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = -0x7F;
            effect->id = 0x1A;
            effect->x_pos.u.hi = arg0->x_pos.u.hi;
            effect->y_pos.u.hi = arg0->y_pos.u.hi;
            arg0->ext.main_65.object = effect;
        }
    }

    if (arg0->unk7E-- == 0) {
        arg0->unk42 ^= 0x8000;
        arg0->invincibility_timer -= 5;
        if (arg0->invincibility_timer > 0x19) {
            arg0->invincibility_timer = 0;
        }
        arg0->unk7E = arg0->invincibility_timer > 5 ? arg0->invincibility_timer : 5;
    }

    update_on_screen(BASE_OBJECT(arg0), 0x40, 0x40);
}

// magma_dragoon_death_begin_explosion
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007FFFC(struct MainObj* arg0)
{
    struct BaseObj* effect = (struct BaseObj*)arg0->ext.main_65.object;
    struct MiscObj* misc;
    u16 flash;
    s16 scroll;
    s16 y;

    if (effect->active == 0) {
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        if (engine_obj.stage == 0xC) {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        } else {
            engine_obj.unkF = 0x10;
        }
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    if (effect->unk7 == 0) {
        flash = arg0->unk7E;
        arg0->unk7E = flash - 1;
        if (flash == 0) {
            arg0->unk7E = 5;
            arg0->unk42 ^= 0x8000;
        }
        update_on_screen(BASE_OBJECT(arg0), 0x40, 0x40);
        return;
    }
    if (engine_obj.stage != 4)
        return;
    arg0->unk5++;
    set_animation(arg0, 0x14);
    if (magma_dragoon_arena_center < g_Player.x_pos.i.hi) {
        arg0->unk15 = 0;
        arg0->x_pos.i.hi = magma_dragoon_arena_right - 0x30;
        if (g_Player.ride_state < 0)
            qux_object.unk15 = PLAYER_FACING_RIGHT;
        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
        scroll = 0x1490;
    } else {
        arg0->unk15 = PLAYER_FACING_RIGHT;
        arg0->x_pos.i.hi = magma_dragoon_arena_left + 0x30;
        if (g_Player.ride_state < 0)
            qux_object.unk15 = 0;
        player_start_script_action(0x14, 0);
        scroll = 0x13F0;
    }
    background_objects[0].unk26 = scroll;
    background_objects[0].unk24 = scroll;
    y = magma_dragoon_arena_floor;
    arg0->y_pos.i.hi = y;
    if (g_Player.ride_state < 0) {
        qux_object.y_pos.i.hi = y;
        qux_object.x_pos.i.hi = magma_dragoon_arena_center;
    } else {
        g_Player.y_pos.i.hi = y;
        g_Player.x_pos.i.hi = magma_dragoon_arena_center;
    }
    background_objects[0].unk2A = 0x1EB;
    background_objects[0].unk28 = 0x1EB;
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x26;
        misc->unk2 = 5;
        misc->ext.misc_7.position = arg0;
        arg0->ext.main_65.smoke = (struct MainObj*)misc;
    }
    engine_obj.enable_boss = 0;
    engine_obj.boss_ptr = NULL;
    update_on_screen(BASE_OBJECT(arg0), 0x40, 0x40);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_65_magma_dragoon", func_8007FFFC);
#endif

void magma_dragoon_death_wait_explosion(struct MainObj* self, s32 arg1, s32 arg2)
{
    if (0 == self->ext.main_65.object->active) {
        self->unk5++;
#ifdef MMX4_PC
        func_8002217C(0xC, 0xFF, 0);
#else
        func_8002217C(0xC, 0xFF, arg2);
#endif
    }
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

void magma_dragoon_death_wait_dialog(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        set_animation(self, 0x13);
        self->unk7C = 0x50;
        self->unk5++;
    }
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
}

#ifdef MMX4_PC
#define MAGMA_DRAGOON_SMOKE(self, kind)                                  \
    do {                                                                 \
        s32 smoke_x = (self)->x_pos.i.hi + (get_random() & 0x3F) - 0x20; \
        s32 smoke_y = (self)->y_pos.i.hi + (get_random() & 0x1F);        \
        spawn_explosion_at(0, smoke_x, smoke_y, kind);                   \
    } while (0)
#else
#define MAGMA_DRAGOON_SMOKE(self, kind)                                      \
    spawn_explosion_at(0, (self)->x_pos.i.hi + (get_random() & 0x3F) - 0x20, \
        (self)->y_pos.i.hi + (get_random() & 0x1F), kind)
#endif

void magma_dragoon_death_smoke(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 0x28;
        self->unk5++;
    }

    if ((self->unk7C & 7) == 0) {
        MAGMA_DRAGOON_SMOKE(self, 0);
    }

    if ((self->unk7C & 3) == 4) {
        MAGMA_DRAGOON_SMOKE(self, 1);
    }

    if ((self->unk7C & 3) != 0) {
        update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
    }
}

void magma_dragoon_death_vanish(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5++;
        self->unk7C = 0x1E;
        ZeroObjectState(OBJECT_HEADER(self->ext.main_65.smoke));
    }

    if ((self->unk7C & 7) == 0) {
        MAGMA_DRAGOON_SMOKE(self, 0);
    }

    if ((self->unk7C & 3) == 4) {
        MAGMA_DRAGOON_SMOKE(self, 1);
    }

    if ((BLINK_CLOCK(self->unk7C) & 1) != 0) {
        update_on_screen(BASE_OBJECT(self), 0x40, 0x40);
    }
}

void magma_dragoon_death_end(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        engine_obj.unkF = 1;
    }
}

void magma_dragoon_death(struct MainObj* self)
{
    magma_dragoon_death_funcs[self->unk5](self);
}

void magma_dragoon_update(struct MainObj* self)
{
    self->on_screen = 0;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    CollisionRelated((struct PlayerObj*)self);
    magma_dragoon_state_funcs[self->state](self);
}

struct Unk_unk68 magma_dragoon_terrain_box = { -1, 22, 13, 17 };

struct Unk_unk68 magma_dragoon_hurt_box = { -16, -28, 31, 67 };

struct Unk_unk68 magma_dragoon_crouch_hurt_box = { -13, 18, 41, 21 };

struct Unk_unk68 magma_dragoon_attack_box = { -10, -19, 16, 58 };

struct Unk_unk68 magma_dragoon_leap_attack_box = { -2, -20, 19, 44 };

struct Unk_unk68 magma_dragoon_punch_attack_box = { -32, -54, 38, 76 };

struct Unk_unk68 magma_dragoon_dive_kick_attack_box = { -41, -12, 22, 45 };

union AnimationStep magma_dragoon_anim_0[] = {
    { 1, 0, 0, 0x00 },
};

struct Unk_unk68 magma_dragoon_anim_1[32] = {
    { 3, 0, 1, 0 },
    { 3, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 1, 0, 1, 6 },
    { 2, 0, 1, 3 },
    { 1, 0, 1, 7 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 8 },
    { 2, 0, 1, 5 },
    { 1, 0, 1, 9 },
    { 2, 0, 1, 5 },
    { 1, 0, 1, 9 },
    { 2, 0, 1, 5 },
    { 1, 0, 1, 9 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 8 },
    { 2, 0, 1, 3 },
    { 1, 0, 1, 7 },
    { 2, 0, 1, 2 },
    { 1, 0, 1, 6 },
    { 2, 0, 1, 2 },
    { 1, 0, 1, 6 },
    { 2, 0, 1, 2 },
    { 1, 0, 1, 6 },
    { 2, 0, 1, 3 },
    { 1, 0, 1, 7 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 8 },
    { 2, 0, 1, 4 },
    { 1, 0, 1, 8 },
    { 2, 0, 1, 4 },
    { 1, 0, -15, 8 },
};

union AnimationStep magma_dragoon_anim_2[] = {
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x04 },
    { 6, 0, 1, 0x05 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 3, 0, 1, 0x01 },
    { 2, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep magma_dragoon_anim_3[] = {
    { 1, 0, 0, 0x0A },
};

struct Unk_unk68 magma_dragoon_anim_4[18] = {
    { 2, 0, 1, -60 },
    { 2, 0, 1, -59 },
    { 2, 0, 1, -60 },
    { 2, 0, 1, -59 },
    { 1, 2, 1, 12 },
    { 1, 1, 1, 12 },
    { 1, 1, 1, -93 },
    { 1, 1, 1, -92 },
    { 1, 1, 1, -91 },
    { 1, 1, 1, -90 },
    { 1, 1, 1, -89 },
    { 1, 1, 1, -86 },
    { 1, 1, 1, -93 },
    { 1, 1, 1, -92 },
    { 1, 1, 1, -91 },
    { 1, 1, 1, -88 },
    { 1, 1, 1, -87 },
    { 1, 1, -11, -86 },
};

struct Unk_unk68 magma_dragoon_anim_5[19] = {
    { 2, 0, 1, 13 },
    { 2, 0, 1, 14 },
    { 2, 0, 1, 13 },
    { 2, 0, 1, 14 },
    { 2, 1, 1, 15 },
    { 2, 0, 1, 16 },
    { 2, 2, 1, 17 },
    { 1, 2, 1, 58 },
    { 1, 2, 1, 59 },
    { 1, 2, 1, 60 },
    { 1, 2, 1, 61 },
    { 1, 2, 1, 62 },
    { 1, 2, 1, 65 },
    { 1, 2, 1, 58 },
    { 1, 2, 1, 59 },
    { 1, 2, 1, 60 },
    { 1, 2, 1, 63 },
    { 1, 2, 1, 64 },
    { 1, 2, -11, 65 },
};

union AnimationStep magma_dragoon_anim_7[] = {
    { 1, 0, 0, 0x0B },
};

union AnimationStep magma_dragoon_anim_8[] = {
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 2, 1, 1, 0x12 },
    { 40, 0, 1, 0x13 },
    { 2, 0, 1, 0x12 },
    { 3, 0, 1, 0x01 },
    { 2, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep magma_dragoon_anim_9[] = {
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 2, 1, 1, 0x19 },
    { 40, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 3, 0, 1, 0x01 },
    { 2, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep magma_dragoon_anim_10[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x1B },
    { 35, 1, 1, 0x1C },
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 30, 2, 1, 0x1F },
    { 2, 0, 1, 0x01 },
    { 1, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep magma_dragoon_anim_11[] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x20 },
    { 6, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 60, 0, 1, 0x23 },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 1, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 2, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 1, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 2, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 1, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 2, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 1, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 2, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 1, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 2, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 1, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 2, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 1, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 6, 2, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 20, 1, 1, 0x24 },
    { 3, 0, 1, 0x23 },
    { 3, 0, 1, 0x01 },
    { 2, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep magma_dragoon_anim_12[55] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x20 },
    { 15, 0, 1, 0x21 },
    { 3, 0, 1, 0x26 },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x26 },
    { 1, 1, 1, 0x2B },
    { 1, 0, 1, 0x28 },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 2, 1, 0x2B },
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 3, 1, 0x27 },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x28 },
    { 1, 4, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x29 },
    { 1, 5, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x26 },
    { 1, 6, 1, 0x2B },
    { 1, 0, 1, 0x28 },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 7, 1, 0x2B },
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 8, 1, 0x27 },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x28 },
    { 1, 1, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x29 },
    { 1, 10, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x28 },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x29 },
    { 1, 0, -9, 0x2C },
};

union AnimationStep magma_dragoon_anim_13[] = {
    { 1, 0, 0, 0x2D },
};

struct Unk_unk68 magma_dragoon_anim_14[12] = {
    { 1, 0, 1, 46 },
    { 1, 0, 1, 47 },
    { 1, 0, 1, 48 },
    { 1, 0, 1, 49 },
    { 1, 0, 1, 50 },
    { 1, 0, 1, 51 },
    { 1, 0, 1, 52 },
    { 1, 0, 1, 53 },
    { 1, 0, 1, 54 },
    { 1, 0, 1, 55 },
    { 1, 0, 1, 56 },
    { 1, 0, -11, 57 },
};

struct Unk_unk68 magma_dragoon_anim_15[3] = {
    { 2, 0, 1, 6 },
    { 1, 0, 1, 86 },
    { 1, 0, -2, 86 },
};

union AnimationStep magma_dragoon_anim_16[] = {
    { 2, 0, 1, 0x54 },
    { 2, 0, 1, 0x55 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x54 },
    { 2, 0, 1, 0x55 },
    { 2, 0, 1, 0x57 },
    { 2, 0, 1, 0x58 },
    { 2, 0, 1, 0x59 },
    { 2, 0, 1, 0x5A },
    { 2, 0, 1, 0x59 },
    { 2, 0, 1, 0x5A },
    { 2, 0, 1, 0x59 },
    { 2, 0, 1, 0x5A },
    { 2, 0, 1, 0x59 },
    { 2, 0, 1, 0x5A },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x2A },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x28 },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x01 },
    { 1, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep magma_dragoon_anim_17[] = {
    { 1, 0, 0, 0x5B },
};

union AnimationStep magma_dragoon_anim_18[] = {
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 39, 0, 1, 0x0D },
    { 1, 0, 0, 0x0D },
};

struct Unk_unk68 magma_dragoon_anim_19[3] = {
    { 2, 0, 1, 92 },
    { 1, 0, 1, 93 },
    { 1, 0, -2, 93 },
};

struct Unk_unk68 magma_dragoon_anim_20[12] = {
    { 50, 0, 1, 92 },
    { 6, 0, 1, 94 },
    { 6, 0, 1, 95 },
    { 5, 0, 1, 94 },
    { 1, 0, 1, 94 },
    { 50, 0, 1, 95 },
    { 2, 0, 1, 96 },
    { 30, 0, 1, 95 },
    { 2, 0, 1, 96 },
    { 6, 0, 1, 95 },
    { 1, 0, 1, 96 },
    { 1, 0, -6, 96 },
};

struct Unk_unk68 magma_dragoon_anim_21[29] = {
    { 1, 0, 1, 100 },
    { 1, 0, 1, 101 },
    { 1, 0, 1, 102 },
    { 1, 0, 1, 103 },
    { 1, 0, 1, 104 },
    { 1, 0, 1, 105 },
    { 10, 0, 1, 118 },
    { 1, 0, 1, 106 },
    { 1, 0, 1, 107 },
    { 1, 0, 1, 108 },
    { 1, 0, 1, 109 },
    { 1, 0, 1, 110 },
    { 1, 0, 1, 111 },
    { 30, 0, 1, 118 },
    { 1, 0, 1, 112 },
    { 1, 0, 1, 113 },
    { 1, 0, 1, 114 },
    { 1, 0, 1, 115 },
    { 1, 0, 1, 116 },
    { 1, 0, 1, 117 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 106 },
    { 1, 0, 1, 107 },
    { 1, 0, 1, 108 },
    { 1, 0, 1, 109 },
    { 1, 0, 1, 110 },
    { 1, 0, 1, 111 },
    { 29, 0, 1, 118 },
    { 1, 0, -28, 118 },
};

u8 magma_dragoon_anim_22[172] = { 50, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 4, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 2, 0, 1, 97, 2, 0, 1, 92, 1, 0, 1, 97, 1, 0, 255, 92 };

union AnimationStep magma_dragoon_anim_24[] = {
    { 1, 0, 1, 0x42 },
    { 1, 0, 1, 0x43 },
    { 1, 0, 1, 0x44 },
    { 1, 0, 1, 0x45 },
    { 1, 0, 1, 0x46 },
    { 1, 0, 1, 0x47 },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4E },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x50 },
    { 1, 0, 0, 0x51 },
};

union AnimationStep magma_dragoon_anim_23[] = {
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x48 },
    { 1, 0, 1, 0x49 },
    { 1, 0, 1, 0x4A },
    { 1, 0, 0, 0x4B },
};

struct Unk_unk68 magma_dragoon_anim_25[18] = {
    { 1, 0, 1, 119 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 120 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 121 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 122 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 123 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 124 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 125 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 126 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, 127 },
    { 1, 0, -13, 118 },
};

union AnimationStep magma_dragoon_anim_26[] = {
    { 1, 0, 1, 0x80 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x81 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x82 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x83 },
    { 1, 0, 0, 0x76 },
};

union AnimationStep magma_dragoon_anim_27[] = {
    { 2, 0, 1, 0x84 },
    { 2, 0, 1, 0x85 },
    { 2, 0, 1, 0x86 },
    { 2, 0, 1, 0x87 },
    { 2, 0, 1, 0x88 },
    { 2, 0, 1, 0x89 },
    { 2, 0, 1, 0x8A },
    { 2, 0, 1, 0x8B },
    { 2, 0, 1, 0x8C },
    { 1, 0, 1, 0x8D },
    { 1, 0, 0, 0x8D },
};

struct Unk_unk68 magma_dragoon_anim_28[11] = {
    { 2, 0, 1, -114 },
    { 2, 0, 1, -113 },
    { 2, 0, 1, -112 },
    { 1, 0, 1, -111 },
    { 1, 0, 1, -110 },
    { 1, 0, 1, -109 },
    { 1, 0, 1, -107 },
    { 1, 0, 1, -111 },
    { 1, 0, 1, -110 },
    { 1, 0, 1, -108 },
    { 1, 0, -7, -107 },
};

struct Unk_unk68 magma_dragoon_anim_29[11] = {
    { 2, 0, 1, -106 },
    { 2, 0, 1, -105 },
    { 2, 0, 1, -104 },
    { 2, 0, 1, -103 },
    { 1, 0, 1, -102 },
    { 2, 0, 1, -101 },
    { 1, 0, 1, -99 },
    { 2, 0, 1, -103 },
    { 1, 0, 1, -102 },
    { 2, 0, 1, -100 },
    { 1, 0, -7, -99 },
};

struct Unk_unk68 magma_dragoon_anim_30[8] = {
    { 2, 0, 1, -98 },
    { 1, 0, 1, -97 },
    { 2, 0, 1, -96 },
    { 1, 0, 1, -94 },
    { 2, 0, 1, -98 },
    { 1, 0, 1, -97 },
    { 2, 0, 1, -95 },
    { 1, 0, -7, -94 },
};

struct Unk_unk68 magma_dragoon_anim_31[5] = {
    { 2, 0, 1, -85 },
    { 1, 0, 1, 118 },
    { 1, 0, 1, -85 },
    { 1, 0, 1, -84 },
    { 1, 0, -2, -83 },
};

union AnimationStep magma_dragoon_anim_32[] = {
    { 1, 0, 1, 0xAE },
    { 2, 0, 1, 0xAF },
    { 2, 0, 1, 0xB0 },
    { 1, 0, 1, 0xB1 },
    { 1, 0, 1, 0xB2 },
    { 1, 0, 1, 0xB3 },
    { 1, 0, 1, 0xB4 },
    { 1, 0, 0, 0xB5 },
};

union AnimationStep magma_dragoon_anim_33[] = {
    { 1, 0, 1, 0xB6 },
    { 1, 0, 1, 0xB7 },
    { 2, 0, 1, 0xB8 },
    { 2, 0, 1, 0xB9 },
    { 3, 0, 1, 0xBA },
    { 4, 0, 1, 0xBB },
    { 1, 0, 1, 0xBC },
    { 2, 0, 1, 0xBD },
    { 2, 0, 1, 0xBE },
    { 1, 0, 1, 0xBF },
    { 1, 0, 1, 0xC0 },
    { 1, 0, 1, 0xC1 },
    { 1, 0, 1, 0xC2 },
    { 1, 0, 0, 0xC3 },
};

union AnimationStep magma_dragoon_anim_34[] = {
    { 1, 0, 1, 0xC6 },
    { 1, 0, 1, 0xC7 },
    { 1, 0, 1, 0xC8 },
    { 1, 0, 1, 0xC9 },
    { 1, 0, 0, 0xCA },
};

struct Unk_unk68 magma_dragoon_anim_35[31] = {
    { 1, 0, 1, -53 },
    { 1, 0, 1, -52 },
    { 1, 0, 1, -51 },
    { 1, 0, 1, -50 },
    { 1, 0, 1, -49 },
    { 1, 0, 1, -48 },
    { 1, 0, 1, -47 },
    { 1, 0, 1, -46 },
    { 1, 0, 1, -53 },
    { 1, 0, 1, -52 },
    { 1, 0, 1, -51 },
    { 1, 0, 1, -50 },
    { 1, 0, 1, -49 },
    { 1, 0, 1, -48 },
    { 1, 1, 1, -47 },
    { 1, 0, 1, -53 },
    { 1, 0, 1, -52 },
    { 1, 0, 1, -51 },
    { 1, 0, 1, -50 },
    { 1, 0, 1, -49 },
    { 1, 0, 1, -48 },
    { 1, 0, 1, -47 },
    { 1, 0, 1, -46 },
    { 1, 0, 1, -53 },
    { 1, 0, 1, -52 },
    { 1, 0, 1, -51 },
    { 1, 0, 1, -50 },
    { 1, 0, 1, -49 },
    { 1, 0, 1, -48 },
    { 1, 2, 1, -47 },
    { 1, 0, -30, -46 },
};

union AnimationStep magma_dragoon_anim_6[] = {
    { 2, 0, 1, 0x03 },
    { 1, 0, 1, 0x07 },
    { 2, 0, 1, 0x04 },
    { 1, 0, 1, 0x08 },
    { 4, 0, 1, 0x04 },
    { 3, 0, 1, 0x03 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x01 },
    { 4, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep magma_dragoon_anim_36[] = {
    { 1, 0, 1, 0xD3 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xD4 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xD5 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xD6 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xD7 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xD8 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xD9 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xDA },
    { 1, 0, 0, 0x76 },
};

union AnimationStep magma_dragoon_anim_37[] = {
    { 1, 0, 1, 0xDB },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xDC },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xDD },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xDE },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xDF },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xE0 },
    { 1, 0, 0, 0x76 },
};

void* magma_dragoon_animations[38] = {
    magma_dragoon_anim_0,
    magma_dragoon_anim_1,
    magma_dragoon_anim_2,
    magma_dragoon_anim_3,
    magma_dragoon_anim_4,
    magma_dragoon_anim_5,
    magma_dragoon_anim_6,
    magma_dragoon_anim_7,
    magma_dragoon_anim_8,
    magma_dragoon_anim_9,
    magma_dragoon_anim_10,
    magma_dragoon_anim_11,
    magma_dragoon_anim_12,
    magma_dragoon_anim_13,
    magma_dragoon_anim_14,
    magma_dragoon_anim_15,
    magma_dragoon_anim_16,
    magma_dragoon_anim_17,
    magma_dragoon_anim_18,
    magma_dragoon_anim_19,
    magma_dragoon_anim_20,
    magma_dragoon_anim_21,
    magma_dragoon_anim_22,
    magma_dragoon_anim_23,
    magma_dragoon_anim_24,
    magma_dragoon_anim_25,
    magma_dragoon_anim_26,
    magma_dragoon_anim_27,
    magma_dragoon_anim_28,
    magma_dragoon_anim_29,
    magma_dragoon_anim_30,
    magma_dragoon_anim_31,
    magma_dragoon_anim_32,
    magma_dragoon_anim_33,
    magma_dragoon_anim_34,
    magma_dragoon_anim_35,
    magma_dragoon_anim_36,
    magma_dragoon_anim_37,
};

struct Unk_unk68 magma_dragoon_fire_volley_debris = { 36, 37, 36, 37 };

void (*magma_dragoon_intro_funcs[8])() = {
    magma_dragoon_intro_warning,
    magma_dragoon_intro_leap,
    magma_dragoon_intro_descend,
    magma_dragoon_intro_land,
    magma_dragoon_intro_pose,
    magma_dragoon_intro_start_health_bar,
    magma_dragoon_intro_ready,
    magma_dragoon_intro_fill_health,
};

void (*magma_dragoon_dive_kick_funcs[4])() = {
    magma_dragoon_dive_kick_jump,
    magma_dragoon_dive_kick_rise,
    func_8007E6F8,
    func_8007E848,
};

void (*magma_dragoon_flame_burst_funcs[2])() = {
    magma_dragoon_flame_burst_start,
    func_8007E95C,
};

void (*magma_dragoon_fire_volley_funcs[3])() = {
    magma_dragoon_fire_volley_start,
    magma_dragoon_fire_volley_fire,
    magma_dragoon_fire_volley_wait,
};

void (*magma_dragoon_breath_funcs[2])() = {
    magma_dragoon_breath_start,
    magma_dragoon_breath_fire,
};

void (*magma_dragoon_leap_center_funcs[4])() = {
    magma_dragoon_leap_center_start,
    magma_dragoon_leap_center_glide,
    magma_dragoon_leap_center_land,
    magma_dragoon_leap_center_recover,
};

void (*magma_dragoon_leap_wall_funcs[3])() = {
    magma_dragoon_leap_wall_start,
    func_8007F174,
    magma_dragoon_leap_wall_finish,
};

void (*magma_dragoon_fireball_funcs[2])() = {
    magma_dragoon_fireball_start,
    func_8007F404,
};

void (*magma_dragoon_fireball_low_funcs[2])(struct MainObj*) = {
    magma_dragoon_fireball_low_start,
    func_8007F5B0,
};

void (*magma_dragoon_rising_punch_funcs[5])() = {
    magma_dragoon_rising_punch_start,
    func_8007F780,
    magma_dragoon_rising_punch_rise,
    magma_dragoon_rising_punch_land,
    magma_dragoon_rising_punch_recover,
};

void (*magma_dragoon_stagger_funcs[5])() = {
    func_8007FAA4,
    magma_dragoon_stagger_rise,
    magma_dragoon_stagger_burn,
    magma_dragoon_stagger_fall,
    magma_dragoon_stagger_recover,
};

void (*magma_dragoon_step_funcs[14])() = {
    enemy_hit_reaction,
    magma_dragoon_hold,
    magma_dragoon_intro,
    func_8007E4C8,
    magma_dragoon_dive_kick,
    magma_dragoon_flame_burst,
    magma_dragoon_fire_volley,
    magma_dragoon_breath,
    magma_dragoon_leap_center,
    magma_dragoon_leap_wall,
    magma_dragoon_fireball,
    magma_dragoon_fireball_low,
    magma_dragoon_rising_punch,
    magma_dragoon_stagger,
};

void (*magma_dragoon_death_funcs[8])() = {
    magma_dragoon_death_start,
    func_8007FF00,
    func_8007FFFC,
    magma_dragoon_death_wait_explosion,
    magma_dragoon_death_wait_dialog,
    magma_dragoon_death_smoke,
    magma_dragoon_death_vanish,
    magma_dragoon_death_end,
};

void (*magma_dragoon_state_funcs[3])() = {
    func_8007DD98,
    func_8007FD24,
    magma_dragoon_death,
};
