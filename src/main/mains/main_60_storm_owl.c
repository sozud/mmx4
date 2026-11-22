// MainObj, main_object_update_funcs[60]
// 8007501C..8007872C
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_60_storm_owl.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/player_common.h"
#include "main/128C4.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/stage_objects.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#endif

// storm_owl_state_funcs
extern void (*storm_owl_state_funcs[])(struct MainObj*);
void storm_owl_start(struct MainObj* arg0);

void storm_owl_death(struct MainObj* arg0);

// storm_owl_start_funcs
extern void (*storm_owl_start_funcs[])(struct MainObj*);
void storm_owl_start_wait_player(struct MainObj*);

void storm_owl_start_wait_warning(struct MainObj*);
void func_800751AC(struct MainObj*);

// storm_owl_step_funcs
void storm_owl_resume_step(struct MainObj* arg0);
void storm_owl_intro(struct MainObj* arg0);
void storm_owl_patrol(struct MainObj* arg0);
void storm_owl_grab(struct MainObj* arg0);
void storm_owl_reenter(struct MainObj* arg0);
void storm_owl_feather(struct MainObj* arg0);
void storm_owl_feather_volley(struct MainObj* arg0);
void storm_owl_cyclone(struct MainObj* arg0);
void storm_owl_storm(struct MainObj* arg0);
void storm_owl_hover(struct MainObj* arg0);
void storm_owl_stagger(struct MainObj* arg0);
void storm_owl_ground_cyclone(struct MainObj* arg0);

// storm_owl_death_funcs
extern void (*storm_owl_death_funcs[])(struct MainObj*);
void storm_owl_death_start(struct MainObj*);

void storm_owl_death_finish(struct MainObj* arg0);

// storm_owl_intro_funcs
extern void (*storm_owl_intro_funcs[])(struct MainObj*);
void func_80075944(struct MainObj*);
void storm_owl_intro_land(struct MainObj*);
void storm_owl_intro_roar(struct MainObj*);
void storm_owl_intro_pose(struct MainObj*);
void storm_owl_intro_start_health_bar(struct MainObj*);
void storm_owl_intro_fill_health(struct MainObj*);

void storm_owl_intro_rise(struct MainObj*);

extern void (*storm_owl_patrol_funcs[])(struct MainObj*);
void storm_owl_patrol_start(struct MainObj*);

void storm_owl_patrol_wait(struct MainObj*);

void storm_owl_patrol_return(struct MainObj*);

extern struct Unk_unk68 storm_owl_grab_attack_box;
extern struct Unk_unk68 storm_owl_grab_terrain_box;
extern void (*storm_owl_grab_funcs[])(struct MainObj*);
void storm_owl_grab_dive(struct MainObj*);

void storm_owl_grab_carry(struct MainObj*);
void storm_owl_grab_slam(struct MainObj*);
void storm_owl_grab_leave(struct MainObj*);

// storm_owl_reenter_funcs
extern void (*storm_owl_reenter_funcs[])(struct MainObj*);

void storm_owl_reenter_wait(struct MainObj*);

// storm_owl_feather_funcs
extern void (*storm_owl_feather_funcs[])(struct MainObj*);
void storm_owl_feather_start(struct MainObj*);
void storm_owl_feather_fire(struct MainObj*);
void storm_owl_feather_takeoff(struct MainObj*);
void storm_owl_feather_leave(struct MainObj*);

// storm_owl_feather_volley_funcs
extern void (*storm_owl_feather_volley_funcs[])(struct MainObj*);
void storm_owl_feather_volley_start(struct MainObj*);
void func_80076D14(struct MainObj*);
void storm_owl_feather_volley_aim(struct MainObj*);
void storm_owl_feather_volley_release(struct MainObj*);
void storm_owl_feather_volley_wait(struct MainObj*);
void storm_owl_feather_volley_leave(struct MainObj*);

// storm_owl_cyclone_funcs
extern void (*storm_owl_cyclone_funcs[])(struct MainObj*);
void storm_owl_cyclone_start(struct MainObj*);
void storm_owl_cyclone_fire(struct MainObj*);
void storm_owl_cyclone_finish(struct MainObj*);
void storm_owl_cyclone_leave(struct MainObj*);

// storm_owl_storm_funcs
extern void (*storm_owl_storm_funcs[])(struct MainObj*);
void storm_owl_storm_start(struct MainObj*);
void storm_owl_storm_fly_to_center(struct MainObj*);
void storm_owl_storm_charge(struct MainObj*);
void storm_owl_storm_begin(struct MainObj*);
void storm_owl_storm_rain(struct MainObj*);
void func_80077580(struct MainObj*);

void storm_owl_storm_end(struct MainObj*);
void storm_owl_storm_leave(struct MainObj*);

// storm_owl_hover_funcs
extern void (*storm_owl_hover_funcs[])(struct MainObj*);
void storm_owl_hover_start(struct MainObj*);
void storm_owl_hover_wait(struct MainObj*);

// storm_owl_stagger_funcs
extern void (*storm_owl_stagger_funcs[])(struct MainObj*);
void storm_owl_stagger_start(struct MainObj*);

void storm_owl_stagger_recover(struct MainObj*);
void storm_owl_stagger_leave(struct MainObj*);

// storm_owl_ground_cyclone_funcs
extern void (*storm_owl_ground_cyclone_funcs[])(struct MainObj*);
void storm_owl_ground_cyclone_start(struct MainObj*);
void storm_owl_ground_cyclone_drop(struct MainObj*);
void storm_owl_ground_cyclone_land(struct MainObj*);
void storm_owl_ground_cyclone_fire(struct MainObj*);
void storm_owl_ground_cyclone_wait(struct MainObj* arg0);
void storm_owl_ground_cyclone_takeoff(struct MainObj*);
void storm_owl_ground_cyclone_leave(struct MainObj*);
void func_80078180(struct MainObj* arg0);

extern u8** storm_owl_patterns[];
extern u8 storm_owl_pattern_weights[][3];

void storm_owl_update(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    storm_owl_state_funcs[self->state](self);
}

void storm_owl_start(struct MainObj* self)
{
    storm_owl_start_funcs[self->unk5](self);
}

void storm_owl_start_wait_player(struct MainObj* self)
{
#ifdef VERSION_DEMO
    if (g_Player.x_pos.i.hi > 0x9D0) {
        return;
    }
    player_start_script_action(0x14, 0);
    self->unk5++;
#else
    if (engine_obj.stage == 7) {
        if (g_Player.x_pos.i.hi > 0x9E0) {
            return;
        }
        player_start_script_action(0x14, 0);
        self->unk5++;
    } else {
        if (g_Player.y_pos.i.hi < 0x6B0) {
            return;
        }
        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
        self->unk5++;
    }
#endif
}

void storm_owl_start_warning(struct MainObj* self)
{
    struct EffectObj* effect = find_free_effect_obj();

    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x18;
        self->ext.main_60.effect = effect;
    }
    self->unk5++;
}

void storm_owl_start_wait_warning(struct MainObj* self)
{
    if (self->ext.main_60.effect->active == 0) {
        self->unk5++;
    }
}

// storm_owl_start_init
void func_800751AC(struct MainObj* self)
{
    s32 x;

    self->hp = 0;
    self->contact_damage = 6;
    self->invincibility_timer = 0;
#ifdef VERSION_DEMO
    self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0xB0);
#else
    if (engine_obj.stage != 0xC) {
        self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0xB0);
    } else {
        self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0x160);
        self->sprite_frames = (const u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[0x10 / 4];
        self->unk42 = OBJECT_CLUT(0x7888);
    }
#endif
    self->bg_offset = g_Player.bg_offset;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->collision_data = D_80107B78;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->animation_table = (const u8* const*)storm_owl_animations;
    self->unk16 = VISUAL_SATURN_LAYER(5);
    self->terrain_box = &storm_owl_slam_terrain_box;
    self->hurt_box = &storm_owl_hurt_box;
    self->attack_box = &storm_owl_attack_box;
    x = self->x_pos.val;
    self->unk15 = (g_Player.x_pos.val >= x) ? PLAYER_FACING_RIGHT : 0;
    set_animation(self, 1);
    self->ext.raw[0] = 0;
    self->ext.raw[1] = 0;
    self->ext.raw[2] = 0;
    self->ext.raw[3] = 0;
    self->ext.raw[4] = 0;
    self->ext.raw[5] = 0;
    self->state = 1;
    self->unk5 = 2;
    self->unk6 = 0;
#ifndef VERSION_DEMO
    self->unk7 = 0x28;
#endif
}

#ifdef VERSION_DEMO
extern void (*D_800D5200_demo[])(struct MainObj*);
void func_8007E1A8_demo(struct MainObj* self)
{
    s32 hit;

    D_800D5200_demo[self->unk5](self);
    hit = func_8002DD04(self);
    func_8002D9BC(self);
    if (self->unk5 != 0) {
        self->ext.main_60.saved_unk5 = self->unk5;
    }
    if (hit < 0) {
        self->unk7C = 0x1E;
        self->on_screen = 0;
        self->unk7E = 5;
        self->state++;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
        return;
    }
    self->state = 3;
}
#endif

#ifdef VERSION_DEMO
void func_8007E278_demo(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->state++;
        return;
    }
    if (--self->unk7E == 0) {
        func_800AF878(BASE_OBJECT(self), 1, 0x20, 0x20);
        self->unk7E = 5;
    }
}
#endif

// storm_owl_main

#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
static void main_60_flash(struct MainObj* arg0);
static void main_60_stagger(struct MainObj* arg0);
void func_80075320(struct MainObj* arg0);
void func_80075C6C(struct MainObj* arg0);
void func_80075E78(struct MainObj* arg0);
static void main_60_release(struct MainObj* arg0);
void func_800760C4(struct MainObj* arg0);
void func_80076364(struct MainObj* arg0);
void func_8007651C(struct MainObj* arg0);
static void main_60_shot_setup(struct ShotObj* shot, struct MainObj* arg0, s8 id, s8 subtype, s8 layer);
void func_80078314(struct MainObj* arg0);
extern void (*storm_owl_step_funcs[])(struct MainObj*);
void storm_owl_spawn_hit_flash(struct PlayerObj* arg0);
void storm_owl_choose_corner(struct MainObj* arg0);
static void main_60_flash(struct MainObj* arg0)
{
    storm_owl_spawn_hit_flash((struct PlayerObj*)arg0);
    arg0->collision_data = D_801060F0;
    arg0->ext.main_60.flash_timer = 0x40;
    arg0->ext.main_60.flash_mode = 1;
}
static void main_60_stagger(struct MainObj* arg0)
{
    if (arg0->unk5 != 0xB)
        func_8001540C(2, SATURN_SOUND(0xBD, 0xBA), arg0);
    arg0->unk5 = 0xB;
    arg0->unk6 = 0;
}
static void main_60_release(struct MainObj* arg0)
{
    g_Player.stun_timer = 0;
    arg0->contact_damage = 6;
    arg0->terrain_box = &storm_owl_slam_terrain_box;
    arg0->attack_box = &storm_owl_attack_box;
    arg0->unk62 = 0;
    arg0->unk16 = VISUAL_SATURN_LAYER(5);
}
static void main_60_shot_setup(struct ShotObj* shot, struct MainObj* arg0, s8 id, s8 subtype, s8 layer)
{
    shot->active = 0x41;
    shot->id = id;
    shot->unk2 = subtype;
    shot->unk7C = (struct WeaponObj*)arg0;
    shot->animation_table = (u32**)storm_owl_animations;
    shot->unk42 = arg0->unk42;
    shot->unk3C = (void*)arg0->sprite_frames;
    shot->unk40 = arg0->unk40;
    shot->unk16 = layer;
    shot->bg_offset = arg0->bg_offset;
    shot->unk15 = arg0->unk15;
}
#endif

#ifndef VERSION_DEMO
#ifdef MMX4_SATURN
void func_80075320(struct MainObj* arg0)
{
    s32 hit = func_8002DD04(arg0);

    if (arg0->unk5 != 0)
        arg0->ext.main_60.saved_unk5 = arg0->unk5;
    if (hit < 0) {
        g_Player.spike_immune = 1;
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        return;
    }
    if (arg0->ext.main_60.flash_mode == 1) {
        if ((arg0->ext.main_60.flash_timer & 1) == 0)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (--arg0->ext.main_60.flash_timer == 0) {
            arg0->collision_data = D_80107B78;
            arg0->ext.main_60.flash_mode = 0;
        }
    } else if (hit != 0) {
        if (engine_obj.cur_character == CHARACTER_X) {
            if (hit == 7 || hit == 0x10) {
                if (arg0->unk5 != 0xB)
                    func_8001540C(2, SATURN_SOUND(0xBD, 0xBA), arg0);
                if (hit == 0x10) {
                    arg0->collision_data = D_80106070;
                    arg0->unk42 &= 0x7FFF;
                }
                arg0->unk5 = 0xB;
                arg0->unk6 = 0;
                arg0->active |= 4;
            } else {
                main_60_flash(arg0);
            }
        } else {
            switch (hit - 0x1A) {
            case 0:
            case 2:
            case 4:
            case 6:
            case 7:
            case 8:
                main_60_flash(arg0);
                break;
            case 9:
            case 10:
                if (arg0->ext.main_60.flash_mode == 0) {
                    arg0->ext.main_60.flash_mode = 2;
                    arg0->ext.main_60.flash_timer = 8;
                } else {
                    main_60_flash(arg0);
                }
                break;
            case 11:
                main_60_stagger(arg0);
                break;
            }
        }
    } else if (arg0->ext.main_60.flash_mode == 2) {
        if (--arg0->ext.main_60.flash_timer == 0)
            arg0->ext.main_60.flash_mode = 0;
    }
    if (arg0->unk17 < 2 && --arg0->unk7 == 0) {
        func_8001540C(2, (get_random() & 1) ? SATURN_SOUND(0xB7, 0xB4) : SATURN_SOUND(0xB8, 0xB5), arg0);
        arg0->unk7 = 0x28;
    }
    storm_owl_step_funcs[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x30);
}
#else
extern void (*storm_owl_step_funcs[13])();
void storm_owl_spawn_hit_flash(struct PlayerObj* arg0);

void func_80075320(struct MainObj* arg0)
{
    s32 hit = func_8002DD04(arg0);

    if (arg0->unk5 != 0)
        arg0->ext.main_60.saved_unk5 = arg0->unk5;
    if (hit < 0) {
        g_Player.spike_immune = 1;
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        return;
    }
    if (arg0->ext.main_60.flash_mode == 1) {
        if ((arg0->ext.main_60.flash_timer & 1) == 0)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (--arg0->ext.main_60.flash_timer == 0) {
            arg0->collision_data = D_80107B78;
            arg0->ext.main_60.flash_mode = 0;
        }
    } else if (hit != 0) {
        if (engine_obj.cur_character == CHARACTER_X) {
            if (hit == 7 || hit == 0x10) {
                if (arg0->unk5 != 0xB)
                    func_8001540C(2, 0xBD, arg0);
                if (hit == 0x10) {
                    arg0->collision_data = D_80106070;
                    arg0->unk42 &= 0x7FFF;
                }
                arg0->unk5 = 0xB;
                arg0->unk6 = 0;
                arg0->active |= 4;
            } else {
                arg0->collision_data = D_801060F0;
                storm_owl_spawn_hit_flash((struct PlayerObj*)arg0);
                arg0->ext.main_60.flash_timer = 0x40;
                arg0->ext.main_60.flash_mode = 1;
            }
        } else {
            switch (hit - 0x1A) {
            case 0:
            case 2:
            case 4:
            case 6:
            case 7:
            case 8:
                storm_owl_spawn_hit_flash((struct PlayerObj*)arg0);
                arg0->collision_data = D_801060F0;
                arg0->ext.main_60.flash_timer = 0x40;
                arg0->ext.main_60.flash_mode = 1;
                break;
            case 9:
            case 10:
                if (arg0->ext.main_60.flash_mode == 0) {
                    arg0->ext.main_60.flash_mode = 2;
                    arg0->ext.main_60.flash_timer = 8;
                } else {
                    storm_owl_spawn_hit_flash((struct PlayerObj*)arg0);
                    arg0->collision_data = D_801060F0;
                    arg0->ext.main_60.flash_mode = 1;
                    arg0->ext.main_60.flash_timer = 0x40;
                }
                break;
            case 11:
                if (arg0->unk5 != 0xB)
                    func_8001540C(2, 0xBD, arg0);
                arg0->unk5 = 0xB;
                arg0->unk6 = 0;
                break;
            }
        }
    } else if (arg0->ext.main_60.flash_mode == 2) {
        if (--arg0->ext.main_60.flash_timer == 0)
            arg0->ext.main_60.flash_mode = 0;
    }
    if (arg0->unk17 < 2 && --arg0->unk7 == 0) {
        if (get_random() & 1)
            func_8001540C(2, 0xB7, arg0);
        else
            func_8001540C(2, 0xB8, arg0);
        arg0->unk7 = 0x28;
    }
    storm_owl_step_funcs[arg0->unk5](arg0);
    func_8002D9BC(arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x30);
}
#endif
#endif

void storm_owl_death(struct MainObj* self)
{
#ifdef VERSION_DEMO
    ZeroObjectState(OBJECT_HEADER(self));
#else
    storm_owl_death_funcs[self->unk5](self);
#endif
}

#ifndef VERSION_DEMO
void storm_owl_death_start(struct MainObj* self)
{
    STOP_SOUND(2, 0xBC, 0x6);
    g_Player.stun_timer = 0;
    player_start_script_action(0x14, g_Player.unk15);
    self->unk5++;
    self->unk42 &= 0x7FFF;
    set_animation(self, 0xB);
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->invincibility_timer = 0x19;
    update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
}
#endif

#ifndef VERSION_DEMO
void storm_owl_death_explode(struct MainObj* self)
{
    struct EffectObj* effect;

    if (--self->unk7C == 0) {
        self->unk5 = 2;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.i.hi;
            effect->y_pos.i.hi = self->y_pos.i.hi;
            self->ext.main_60.effect = effect;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
    if (self->unk7E-- == 0) {
        self->unk42 ^= 0x8000;
        if ((self->invincibility_timer -= 5) > 0x19) {
            self->invincibility_timer = 0;
        }
        self->unk7E = self->invincibility_timer > 5 ? self->invincibility_timer : 5;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_death_finish(struct MainObj* self)
{
    struct EffectObj* effect;

    self->on_screen = 0;
    effect = self->ext.main_60.effect;
    if (effect->active != 0) {
        if (effect->unk7 == 0) {
            if (self->unk7E-- == 0) {
                self->unk42 ^= 0x8000;
                self->unk7E = 5;
            }
            update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
        }
    } else {
        self->ext.raw[0] = 0;
        self->ext.raw[1] = 0;
        self->ext.raw[2] = 0;
        self->ext.raw[3] = 0;
        self->ext.raw[4] = 0;
        self->ext.raw[5] = 0;
        engine_obj.enable_boss = 0;
        engine_obj.boss_ptr = NULL;
        if (engine_obj.stage != 0xC) {
            engine_obj.unkF = 0x10;
        } else {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        }
        ZeroObjectState(OBJECT_HEADER(self));
    }
}
#endif

void storm_owl_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_60.saved_unk5;
}

void storm_owl_intro(struct MainObj* self)
{
    storm_owl_intro_funcs[self->unk6](self);
}

// storm_owl_intro_descend
void func_80075944(struct MainObj* self)
{
    set_animation(self, 0);

#ifdef VERSION_DEMO
    self->x_pos.i.hi = 0x8F0;
    self->y_pos.i.hi = 0x1C0;
    self->y_speed = FIXED(-3);
    storm_owl_spawn_intro_wind(self);
#else
    if (engine_obj.stage == 7) {
        self->x_pos.i.hi = background_objects[0].x_pos.i.hi + 0x20;
        self->unk15 = PLAYER_FACING_RIGHT;
    } else {
        self->x_pos.i.hi = background_objects[0].x_pos.i.hi + 0x120;
        self->unk15 = 0;
    }

    self->y_pos.i.hi = background_objects[0].y_pos.i.hi - 0x20;
    self->y_speed = FIXED(-2);

    storm_owl_spawn_intro_wind(self);
    func_8001540C(2, SATURN_SOUND(0xB4, 0xB1), self);
#endif
    self->unk6++;
}

void storm_owl_intro_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->collision_flags & 8) {
        set_animation(self, 9);
        self->unk7C = DEMO_ALT(0x49, 0x7A);
        self->unk6++;
    }
}

void storm_owl_intro_roar(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
#ifndef VERSION_DEMO
        func_8001540C(2, SATURN_SOUND(0xBB, 0xB8), self);
#endif
        start_screen_shake_y(DEMO_ALT(0x18, 8), DEMO_ALT(8, 2), 1);
        storm_owl_spawn_roar(ANIMATED_OBJECT(self));
        self->unk7C = DEMO_ALT(0x2F, 9);
        self->unk6++;
    }
}

void storm_owl_intro_pose(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
#ifdef VERSION_DEMO
        DEMO_START_DIALOGUE(0xF, 0xFF);
#else
        if (engine_obj.stage == 7) {
            func_8002217C(0xF, 0xFF, (u8)engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
#endif
        self->unk6++;
    }
}

void storm_owl_intro_start_health_bar(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (abc_object.unkC == 0) {
#ifndef VERSION_DEMO
        engine_obj.boss_ptr = self;
#endif
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
#ifdef VERSION_DEMO
        engine_obj.boss_ptr = self;
#endif
        self->unk7C = 3;
        self->unk6++;
#ifndef VERSION_DEMO
        play_boss_voice(6);
#endif
    }
}

void storm_owl_intro_fill_health(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (DEMO_ALT(update_boss_music_delay(), 0) == 0) {
        if (--self->unk7C == 0) {
            func_8001540C(0, SATURN_SOUND(DEMO_ALT(0xE, 0xF), 0x14), 0);
            self->unk7C = 3;
        }
        if (DEMO_ALT((s8)++self->hp, (s8)self->hp++) == 0x30) {
            player_end_script_action();
#ifndef VERSION_DEMO
            storm_owl_choose_pattern(self);
#endif
            self->unk6++;
        }
    }
}

// storm_owl_intro_takeoff
void func_80075C6C(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    set_animation(arg0, 1);
#ifdef VERSION_DEMO
    set_velocity_from_angle(MOVING_OBJECT(arg0),
        angle_to_point(OBJECT_HEADER(arg0), (u16)storm_owl_waypoints[0].x << 16, (u16)storm_owl_waypoints[0].y << 16) & 0xFF);
#else
    arg0->ext.main_60.corner = engine_obj.stage == 7 ? 0 : 2;
    set_velocity_from_angle(MOVING_OBJECT(arg0),
        angle_to_point(OBJECT_HEADER(arg0), (storm_owl_waypoints[arg0->ext.main_60.corner].x + background_objects[0].x_pos.i.hi) << 16,
            (storm_owl_waypoints[arg0->ext.main_60.corner].y + background_objects[0].y_pos.i.hi) << 16)
            & 0xFF);
#endif
    arg0->x_speed <<= 1;
    arg0->y_speed <<= 1;
    arg0->unk6++;
}

void storm_owl_intro_rise(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
#ifdef VERSION_DEMO
    if ((u16)storm_owl_waypoints[0].y > self->y_pos.i.hi) {
#else
    self->ext.main_60.corner = (engine_obj.stage != 7) * 2;
    if ((s16)(background_objects[0].y_pos.i.hi + (u16)storm_owl_waypoints[self->ext.main_60.corner & 0xFF].y) > self->y_pos.i.hi) {
#endif
        self->x_speed = 0;
        self->y_speed = 0;
        self->unk5 = 3;
        self->unk6 = 2;
    }
}

void storm_owl_patrol(struct MainObj* self)
{
    storm_owl_patrol_funcs[self->unk6](self);
}

#ifdef VERSION_DEMO
void func_8007E710_demo(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    set_animation(arg0, 1);
    set_velocity_from_angle(MOVING_OBJECT(arg0),
        angle_to_point(OBJECT_HEADER(arg0), (u16)storm_owl_waypoints[arg0->ext.main_60.corner].x << 16,
            (u16)storm_owl_waypoints[arg0->ext.main_60.corner].y << 16)
            & 0xFF);
    arg0->x_speed <<= 1;
    arg0->y_speed <<= 1;
    arg0->unk6++;
}
#endif

#ifdef VERSION_DEMO
void func_8007E7AC_demo(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if ((self->ext.main_60.corner < 2
            && ABS((u16)storm_owl_waypoints[self->ext.main_60.corner].x, self->x_pos.i.hi) < 0x10)
        || (self->ext.main_60.corner >= 2
            && ABS((u16)storm_owl_waypoints[self->ext.main_60.corner].x, self->x_pos.i.hi) < 0x10)) {
        self->x_speed = 0;
        self->y_speed = 0;
        self->unk6++;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_patrol_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 1);
    self->unk15 = self->x_pos.val > g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
    self->unk6++;
}
#endif

// storm_owl_patrol_fly
#ifndef VERSION_DEMO
void func_80075E78(struct MainObj* arg0)
{
    s32 target_x;
    s32 target_y;
    target_x = (storm_owl_waypoints[arg0->ext.main_60.corner].x + background_objects[0].x_pos.i.hi) << 16;
    target_y = (storm_owl_waypoints[arg0->ext.main_60.corner].y + background_objects[0].y_pos.i.hi) << 16;

    set_velocity_from_angle(MOVING_OBJECT(arg0), angle_to_point(OBJECT_HEADER(arg0), target_x, target_y) & 0xFF);
    arg0->x_speed <<= 1;
    arg0->y_speed <<= 1;
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    if ((target_x - arg0->x_pos.val >= 0 ? target_x - arg0->x_pos.val : arg0->x_pos.val - target_x) <= 0x3FFFF
        && (target_y - arg0->y_pos.val >= 0 ? target_y - arg0->y_pos.val : arg0->y_pos.val - target_y) <= 0x3FFFF) {
        arg0->x_speed = 0;
        arg0->y_speed = 0;
        if (arg0->ext.main_60.pattern[0] == 0xFF)
            storm_owl_choose_pattern(arg0);
        arg0->unk5 = *arg0->ext.main_60.pattern;
        arg0->ext.main_60.pattern++;
        if (arg0->unk5 != 3)
            arg0->unk6 = 0;
        else
            arg0->unk6++;
    }
}
#endif

void storm_owl_patrol_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));

#ifdef VERSION_DEMO
    self->x_speed = storm_owl_waypoints[self->ext.main_60.corner].vx;
    self->y_speed = storm_owl_waypoints[self->ext.main_60.corner].vy;
    self->x_accel = FIXED(0.015625);
    self->unk6++;
#else
    if (self->ext.main_60.patrol_delay == 0) {
        self->x_speed = storm_owl_waypoints[self->ext.main_60.corner].vx;
        self->y_speed = storm_owl_waypoints[self->ext.main_60.corner].vy;
        self->x_accel = FIXED(0.015625);
        self->unk15 = ((~self->x_speed >> 31) & PLAYER_FACING_RIGHT);
        self->unk6++;
    } else {
        self->ext.main_60.patrol_delay--;
    }
#endif
}

// storm_owl_patrol_fall
void func_800760C4(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    move_with_gravity(ANIMATED_OBJECT(arg0));
    arg0->y_speed += 0x400;
    if ((g_Player.x_pos.i.hi - arg0->x_pos.i.hi < 0 ? arg0->x_pos.i.hi - g_Player.x_pos.i.hi : g_Player.x_pos.i.hi - arg0->x_pos.i.hi) <= 0x30) {
#ifdef VERSION_DEMO
        if (g_Player.y_pos.i.hi >= arg0->y_pos.i.hi) {
            arg0->unk5 = 4;
        }
        arg0->unk6 = 0;
        arg0->x_speed = 0;
        arg0->y_speed = 0;
#else
        if ((u8)(get_random() & 7) < 5) {
            if (g_Player.y_pos.i.hi >= arg0->y_pos.i.hi) {
                arg0->unk5 = 4;
                arg0->unk6 = 0;
                arg0->x_speed = 0;
                arg0->y_speed = 0;
            } else {
                arg0->unk5 = 6;
                arg0->unk6 = 0;
                arg0->x_speed = 0;
                arg0->y_speed = 0;
            }
        } else {
            arg0->ext.main_60.corner ^= 2;
            arg0->unk6++;
        }
#endif
    }
}

#ifndef VERSION_DEMO
void storm_owl_patrol_return(struct MainObj* self)
{
    s16 target_x;

    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    self->y_speed += FIXED(0.015625);

    target_x = background_objects[0].x_pos.i.hi + storm_owl_waypoints[self->ext.main_60.corner].x;
    if (ABS(self->x_pos.i.hi, target_x) <= 0x20) {
        self->unk6 = 0;
        self->x_speed = 0;
        self->y_speed = 0;
        self->ext.main_60.patrol_delay = 0x14;
    }
}
#endif

void storm_owl_grab(struct MainObj* self)
{
    storm_owl_grab_funcs[self->unk6](self);
}

void storm_owl_grab_dive(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 7);
    set_velocity_from_angle(MOVING_OBJECT(self),
        angle_to_object(OBJECT_HEADER(self),
            OBJECT_HEADER(&g_Player))
            & 0xFF);

    self->x_speed *= 3;
    self->y_speed *= DEMO_ALT(4, 3);
#ifndef VERSION_DEMO
    if (self->unk15 == 0 ? self->x_speed > 0 : self->x_speed < 0) {
        self->x_speed = 0;
    }
#endif
    self->attack_box = &storm_owl_grab_attack_box;
    self->terrain_box = &storm_owl_grab_terrain_box;
    self->unk62 = 3;
    self->contact_damage = 0;
    self->unk16 = 2;
    self->unk6++;
}

// storm_owl_grab_swoop
#ifdef VERSION_DEMO
void func_80076364(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    if (g_Player.stun_timer != 0) {
        if ((g_Player.x_pos.i.hi - arg0->x_pos.i.hi >= 0 ? g_Player.x_pos.i.hi - arg0->x_pos.i.hi : arg0->x_pos.i.hi - g_Player.x_pos.i.hi) >= 8) {
            if (g_Player.x_pos.i.hi > arg0->x_pos.i.hi)
                arg0->x_speed = 0x10000;
            else
                arg0->x_speed = -0x10000;
        } else {
            arg0->x_speed = 0;
        }
        arg0->y_speed = 0;
        arg0->unk6++;
        return;
    }
    if (arg0->y_pos.i.hi + 0x10 >= g_Player.y_pos.i.hi) {
        if (arg0->unk15 != 0)
            arg0->x_speed = 0x30000;
        else
            arg0->x_speed = -0x30000;
        arg0->y_speed = -0x8000;
        g_Player.stun_timer = 0;
        arg0->unk62 = 0;
        arg0->terrain_box = &storm_owl_slam_terrain_box;
        arg0->attack_box = &storm_owl_attack_box;
        arg0->unk16 = 5;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 1) {
        storm_owl_choose_corner(arg0);
        g_Player.stun_timer = 0;
        arg0->unk62 = 0;
        arg0->terrain_box = &storm_owl_slam_terrain_box;
        arg0->attack_box = &storm_owl_attack_box;
        arg0->unk16 = 5;
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}
#else
void func_80076364(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    if (arg0->y_pos.i.hi + 0x14 >= g_Player.y_pos.i.hi) {
        if (arg0->unk15 != 0)
            arg0->x_speed = 0x20000;
        else
            arg0->x_speed = -0x20000;
        arg0->y_speed = -0x10000;
        set_animation(arg0, 1);
        g_Player.stun_timer = 0;
        arg0->contact_damage = 6;
        arg0->unk62 = 0;
        arg0->terrain_box = &storm_owl_slam_terrain_box;
        arg0->attack_box = &storm_owl_attack_box;
        arg0->unk16 = VISUAL_SATURN_LAYER(5);
        arg0->unk6 = 5;
        return;
    }
    if (g_Player.stun_timer != 0) {
        func_8001540C(2, SATURN_SOUND(0xBA, 0xB7), arg0);
        if ((g_Player.x_pos.i.hi - arg0->x_pos.i.hi >= 0 ? g_Player.x_pos.i.hi - arg0->x_pos.i.hi : arg0->x_pos.i.hi - g_Player.x_pos.i.hi) >= 8) {
            if (g_Player.x_pos.i.hi > arg0->x_pos.i.hi)
                arg0->x_speed = 0x10000;
            else
                arg0->x_speed = -0x10000;
        } else {
            arg0->x_speed = 0;
        }
        arg0->y_speed = 0;
        arg0->unk6++;
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x20, 0x20) == 1) {
        storm_owl_choose_corner(arg0);
        g_Player.stun_timer = 0;
        arg0->unk62 = 0;
        arg0->contact_damage = 6;
        arg0->terrain_box = &storm_owl_slam_terrain_box;
        arg0->attack_box = &storm_owl_attack_box;
        arg0->unk16 = VISUAL_SATURN_LAYER(5);
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    }
}
#endif

// storm_owl_grab_rise
void func_8007651C(struct MainObj* arg0)
{
    s16 bg_x;
    s32 x;
    s32 left;

    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    bg_x = background_objects[0].x_pos.i.hi;
    if (ABS(g_Player.x_pos.i.hi, arg0->x_pos.i.hi) < 8) {
        x = arg0->x_pos.i.hi;
        left = bg_x;
#ifdef VERSION_DEMO
        if (x < 0x910 && arg0->x_speed < 0)
            arg0->x_speed = 0;
        else if (x > 0x9B0 && arg0->x_speed > 0)
            arg0->x_speed = 0;
#else
        if (x < left + 0x40 && arg0->x_speed < 0)
            arg0->x_speed = 0;
        else if (x > left + 0x100 && arg0->x_speed > 0)
            arg0->x_speed = 0;
        else if ((arg0->unk15 == 0 && arg0->x_speed > 0) || (arg0->unk15 != 0 && arg0->x_speed < 0))
            arg0->x_speed = 0;
#endif
        arg0->y_speed = 0x10000;
        arg0->unk7C = 0x3C;
        arg0->unk6++;
    }
}

void storm_owl_grab_carry(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->collision_flags & 4) {
        self->y_speed = 0;
        self->gravity = 0;
    }
    if (self->unk15 == 0)
        g_Player.x_pos.i.hi = self->x_pos.i.hi - 0xA;
    else
        g_Player.x_pos.i.hi = self->x_pos.i.hi + 0xA;
    g_Player.y_pos.i.hi = self->y_pos.i.hi + 0x1E;
    if (--self->unk7C == 0) {
        set_animation(self, 8);
        self->y_speed = FIXED(-4);
        self->unk6++;
    }
}

void storm_owl_grab_slam(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
#ifndef VERSION_DEMO
    if (g_Player.x_pos.i.hi <= background_objects[0].x_pos.i.hi + 0x10
        || g_Player.x_pos.i.hi >= background_objects[0].x_pos.i.hi + 0x130) {
        self->x_speed = 0;
        self->x_accel = 0;
    }
#endif
    g_Player.x_pos.i.hi = self->x_pos.i.hi;
    g_Player.y_pos.i.hi = self->y_pos.i.hi + 0x1C;
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->collision_flags & 8) {
#ifndef VERSION_DEMO
        func_8001540C(2, SATURN_SOUND(0xBB, 0xB8), self);
#endif
        start_screen_shake_y(8, DEMO_ALT(4, 2), 1);
#ifndef VERSION_DEMO
        player_damage(9);
#endif
        set_animation(self, 1);
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-2);
        } else {
            self->x_speed = FIXED(2);
        }
        self->y_speed = DEMO_ALT(FIXED(-1), FIXED(3));
        g_Player.stun_timer = 0;
        self->unk62 = 0;
        self->terrain_box = &storm_owl_slam_terrain_box;
        self->attack_box = (const u8*)&storm_owl_attack_box;
#ifdef VERSION_DEMO
        self->unk16 = 5;
#endif
        self->unk6++;
    }
}

void storm_owl_grab_leave(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
#ifndef VERSION_DEMO
    if (self->y_speed < FIXED(3.0)) {
        self->y_speed += FIXED(0.125);
    }
#endif
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
#ifdef VERSION_DEMO
        storm_owl_choose_corner(self);
#endif
        g_Player.stun_timer = 0;
        self->unk62 = 0;
#ifndef VERSION_DEMO
        self->contact_damage = 6;
#endif
        self->terrain_box = &storm_owl_slam_terrain_box;
        self->attack_box = (const u8*)&storm_owl_attack_box;
        self->unk16 = VISUAL_SATURN_LAYER(5);
        storm_owl_choose_corner(self);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void storm_owl_reenter(struct MainObj* self)
{
    storm_owl_reenter_funcs[self->unk6](self);
}

void storm_owl_reenter_warp(struct MainObj* self)
{
    u16 background_x = background_objects[0].x_pos.i.hi;
    u16 background_y = background_objects[0].y_pos.i.hi;

    animate_object(ANIMATED_OBJECT(self));
    switch (self->ext.main_60.corner) {
    case 0:
        self->x_pos.i.hi = DEMO_ALT(background_x - 0x40, 0x890);
        self->y_pos.i.hi = DEMO_ALT(background_y + 0x10, 0x200);
        break;
    case 1:
        self->x_pos.i.hi = DEMO_ALT(background_x - 0x40, 0x890);
        self->y_pos.i.hi = DEMO_ALT(background_y + 0xC8, 0x260);
        break;
    case 2:
        self->x_pos.i.hi = DEMO_ALT(background_x + 0x180, 0xA30);
        self->y_pos.i.hi = DEMO_ALT(background_y + 0x10, 0x200);
        break;
    case 3:
        self->x_pos.i.hi = DEMO_ALT(background_x + 0x180, 0xA30);
        self->y_pos.i.hi = DEMO_ALT(background_y + 0xC8, 0x260);
        break;
    }
    self->unk15 = self->x_pos.val > g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
    self->unk7C = 0x3C;
#ifndef VERSION_DEMO
    self->active = 0x41;
#endif
    self->unk6++;
}

void storm_owl_reenter_wait(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
#ifndef VERSION_DEMO
    if (self->ext.main_60.flash_mode == 1) {
        self->collision_data = (const u16*)D_801060F0;
    } else {
        self->collision_data = (const u16*)D_80107B78;
    }
#endif
    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void storm_owl_feather(struct MainObj* self)
{
    storm_owl_feather_funcs[self->unk6](self);
}

void storm_owl_feather_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 3);
    self->unk15 = self->x_pos.val > g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
    self->unk7C = 0x1F;
    self->unk6++;
}

void storm_owl_feather_fire(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        storm_owl_spawn_feather(self);
#ifndef VERSION_DEMO
        func_8001540C(2, SATURN_SOUND(0xB6, 0xB3), self);
#endif
        self->unk7C = 0x1C;
        self->unk6++;
    }
}

void storm_owl_feather_takeoff(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));

    if (--self->unk7C == 0) {
        set_animation(self, 1);
#ifdef VERSION_DEMO
        self->unk15 = self->x_pos.val < g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-2);
        } else {
            self->x_speed = FIXED(2);
        }
#else
        storm_owl_choose_corner(self);
        if (self->ext.main_60.corner >> 1) {
            self->x_speed = FIXED(2);
            self->unk15 = PLAYER_FACING_RIGHT;
        } else {
            self->x_speed = FIXED(-2);
            self->unk15 = 0;
        }
#endif
        self->y_speed = FIXED(3);
        self->unk6++;
    }
}

void storm_owl_feather_leave(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
#ifdef VERSION_DEMO
        storm_owl_choose_corner(self);
#endif
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void storm_owl_feather_volley(struct MainObj* self)
{
    storm_owl_feather_volley_funcs[self->unk6](self);
}

void storm_owl_feather_volley_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 3);
#ifdef VERSION_DEMO
    self->unk15 = self->x_pos.val > g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
#else
    self->unk15 = self->ext.main_60.corner >= 2 ? 0 : PLAYER_FACING_RIGHT;
#endif
    self->unk7C = 0x1C;
    self->collision_data = (const u16*)DEMO_ALT(D_80107B78, D_801060F0);
    self->ext.main_60.shot_count = 0;
    self->unk6++;
}

// storm_owl_feather_volley_spread
void func_80076D14(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        if (++self->ext.main_60.shot_count >= 4) {
            self->unk7C = 0x3C;
            self->unk6++;
        } else {
            self->unk7C = 0x3D;
        }
        ((void (*)())storm_owl_spawn_volley_feather)(self, self->ext.main_60.shot_count);
#ifndef VERSION_DEMO
        func_8001540C(2, SATURN_SOUND(0xB5, 0xB2), self);
#endif
    }
}

void storm_owl_feather_volley_aim(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 6);
        self->collision_data = (const u16*)D_80107B78;
        self->unk7C = 0x3C;
        self->unk6++;
    }
}

void storm_owl_feather_volley_release(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
#ifndef VERSION_DEMO
        func_8001540C(2, SATURN_SOUND(0xB6, 0xB3), self);
#endif
        self->ext.main_60.feathers_holding = 1;
        self->unk7C = 0x78;
        self->unk6++;
    }
}

void storm_owl_feather_volley_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->ext.main_60.feather_mask == 0) {
        self->ext.main_60.feathers_holding = 0;
        set_animation(self, 1);
        self->unk15 = self->x_pos.val < g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-2);
        } else {
            self->x_speed = FIXED(2);
        }
        self->y_speed = FIXED(3);
        self->unk6++;
    }
}

void storm_owl_feather_volley_leave(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
        storm_owl_choose_corner(self);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

void storm_owl_cyclone(struct MainObj* self)
{
    storm_owl_cyclone_funcs[self->unk6](self);
}

void storm_owl_cyclone_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (!(self->ext.main_60.corner % 2)) {
        set_animation(self, 4);
    } else {
        set_animation(self, 5);
    }
#ifdef VERSION_DEMO
    self->unk15 = self->x_pos.val > g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
    self->unk7C = 0x3B;
#else
    self->unk15 = (self->ext.main_60.corner >> 1) == 0 ? PLAYER_FACING_RIGHT : 0;
    self->unk7C = 0x63;
#endif
    self->unk6++;
}

#ifndef VERSION_DEMO
void storm_owl_cyclone_fire(struct MainObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    timer = --self->unk7C;
    if (timer == 0) {
        func_8001540C(2, SATURN_SOUND(0xB9, 0xB6), self);
        storm_owl_spawn_cyclones(self);
        self->unk7C = 0x1E;
        self->unk6++;
        return;
    }
    if ((timer <= 0x28) && (((timer - 0x3B) % 20) == 0)) {
        storm_owl_spawn_cyclones(self);
        func_8001540C(2, SATURN_SOUND(0xB9, 0xB6), self);
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_cyclone_finish(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        if (self->ext.main_60.pattern[0] == 3) {
            self->unk5 = 0xA;
            self->unk6 = 0;
            return;
        }
        set_animation(self, 1);
        self->unk15 = self->x_pos.val < g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-2);
        } else {
            self->x_speed = FIXED(2);
        }
        self->y_speed = FIXED(3);
        self->unk6++;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_cyclone_leave(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
        storm_owl_choose_corner(self);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_storm(struct MainObj* self)
{
    func_80078180(self);
    storm_owl_storm_funcs[self->unk6](self);
}
#endif

#ifndef VERSION_DEMO
void storm_owl_storm_start(struct MainObj* self)
{
    s32 threshold;
    s32 velocity_x;
    s32 velocity_y;

    animate_object(ANIMATED_OBJECT(self));
    threshold = (background_objects[0].x_pos.i.hi + 0xA0) << 16;
    set_velocity_from_angle(
        MOVING_OBJECT(self),
        angle_to_point(OBJECT_HEADER(self), threshold,
            (background_objects[0].y_pos.i.hi + 0x70) << 16)
            & 0xFF);

    velocity_x = self->x_speed;
    velocity_y = self->y_speed;
    velocity_x *= 2;
    velocity_y *= 2;
    self->x_speed = velocity_x;
    self->y_speed = velocity_y;

    if (velocity_y >= 1) {
        set_animation(self, 1);
    } else {
        set_animation(self, 0);
    }
    self->unk15 = threshold >= self->x_pos.val ? PLAYER_FACING_RIGHT : 0;
    self->unk6++;
}
#endif

#ifndef VERSION_DEMO
void storm_owl_storm_fly_to_center(struct MainObj* self)
{
    s32 target_x = (background_objects[0].x_pos.i.hi + 0xA0) << 16;
    s32 target_y = (background_objects[0].y_pos.i.hi + 0x70) << 16;
    s32 x;
    s32 y;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    set_velocity_from_angle(MOVING_OBJECT(self), angle_to_point(OBJECT_HEADER(self), target_x, target_y) & 0xFF);
    x = self->x_pos.val;
    self->x_speed *= 2;
    self->y_speed *= 2;
    if (x - target_x >= 0 ? x - target_x <= FIXED(3.99999) : target_x - x <= FIXED(3.99999)) {
        y = self->y_pos.val;
        if (y - target_y >= 0 ? y - target_y <= FIXED(3.99999) : target_y - y <= FIXED(3.99999)) {
            set_animation(self, 6);
            self->unk6++;
        }
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_storm_charge(struct MainObj* self)
{
    storm_owl_spawn_storm_charge(ANIMATED_OBJECT(self));
    func_8001540C(2, SATURN_SOUND(0xBE, 0xBB), self);
    self->unk7C = 0x3C;
    self->unk6++;
}
#endif

void storm_owl_storm_begin(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
#ifdef VERSION_DEMO
        storm_owl_spawn_cyclones(self);
        self->unk7C = 0x1E;
#else
        func_8001540C(2, SATURN_SOUND(0xBC, 0xB9), self);
        self->ext.main_60.storm_active = 1;
        self->ext.main_60.storm_timer = 0x10;
        self->unk7C = 0x5A;
#endif
        self->unk6++;
    }
}

#ifndef VERSION_DEMO
void storm_owl_storm_rain(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        if (--self->ext.main_60.storm_timer == 0) {
            self->unk7C = 0x3C;
            self->unk6++;
        } else {
            self->unk7C = 0x14;
        }
    }
}
#endif

// storm_owl_storm_flap
#ifndef VERSION_DEMO
void func_80077580(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        if ((get_random() & 7) < 3) {
            self->unk6++;
            func_8001540C(2, SATURN_SOUND(0xBC, 0xB9), self);
        } else {
            self->unk6 += 2;
        }
        self->unk7C = 0x1E;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_storm_rain_again(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        if (++self->ext.main_60.storm_timer >= 0x10) {
            self->unk7C = 0x3C;
            self->unk6++;
            return;
        }
        self->unk7C = 0x14;
    }
}
#endif

void storm_owl_storm_end(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
#ifndef VERSION_DEMO
        STOP_SOUND(2, 0xBC, 0x6);
#endif
        set_animation(self, 1);
#ifndef VERSION_DEMO
        self->ext.main_60.storm_active = 0;
#endif
        self->unk15 = self->x_pos.val < g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-2);
        } else {
            self->x_speed = FIXED(2);
        }
        self->y_speed = FIXED(3);
        self->unk6++;
    }
}

void storm_owl_storm_leave(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
        storm_owl_choose_corner(self);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}

#ifndef VERSION_DEMO
void storm_owl_hover(struct MainObj* self)
{
    storm_owl_hover_funcs[self->unk6](self);
}
#endif

#ifndef VERSION_DEMO
void storm_owl_hover_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 0);
    self->unk7C = 0x5A;
    self->unk6++;
}
#endif

#ifndef VERSION_DEMO
void storm_owl_hover_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_stagger(struct MainObj* self)
{
    storm_owl_stagger_funcs[self->unk6](self);
}
#endif

#ifndef VERSION_DEMO
void storm_owl_stagger_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 0xC);
    g_Player.stun_timer = 0;
    self->unk62 = 0;
    self->contact_damage = 6;
    self->terrain_box = &storm_owl_slam_terrain_box;
    self->attack_box = (const u8*)&storm_owl_attack_box;
    self->unk16 = VISUAL_SATURN_LAYER(5);
    if (self->collision_data == (const u16*)D_80107B78) {
        self->unk7C = 0x28;
    } else {
        self->unk7C = 0xF;
    }
    self->ext.main_60.feathers_holding = 0;
    self->ext.main_60.feather_mask = 0;
    storm_owl_clear_shots();
    STOP_SOUND(2, 0xBC, 0x6);
    self->unk6++;
}
#endif

#ifndef VERSION_DEMO
void storm_owl_stagger_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        set_animation(self, 1);
        self->collision_data = (const u16*)D_80107B78;
        self->x_speed = self->unk15 == 0 ? FIXED(-2) : FIXED(2);
        self->y_speed = FIXED(3);
        self->unk6++;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_stagger_leave(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if ((func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) && (self->ext.main_60.feather_mask == 0)) {
        storm_owl_choose_corner(self);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_ground_cyclone(struct MainObj* self)
{
    storm_owl_ground_cyclone_funcs[self->unk6](self);
}
#endif

#ifndef VERSION_DEMO
void storm_owl_ground_cyclone_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 1);
    if (!(self->ext.main_60.corner & 1)) {
        self->unk6++;
        self->y_speed = FIXED(-3);
    } else {
        self->unk7C = 0xA;
        self->unk6 += 2;
    }
    if (self->ext.main_60.corner <= 1) {
        self->unk15 = PLAYER_FACING_RIGHT;
    } else {
        self->unk15 = 0;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_ground_cyclone_drop(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->collision_flags & 8) {
        set_animation(self, 9);
        self->unk7C = 0x1E;
        self->unk6++;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_ground_cyclone_land(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        set_animation(self, 3);
        self->unk7C = 0x1E;
        self->unk6++;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_ground_cyclone_fire(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk7C = 0xA;
        func_8001540C(2, SATURN_SOUND(0xB4, 0xB1), self);
        func_80078314(self);
        self->unk6++;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_ground_cyclone_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk7C = 0x5F;
        self->unk6++;
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_ground_cyclone_takeoff(struct MainObj* self)
{
    if (--self->unk7C != 0) {
        return;
    }
    set_animation(self, 1);
    self->x_speed = self->unk15 == 0 ? FIXED(-2) : FIXED(2);
    self->y_speed = FIXED(3);
    self->unk6++;
}
#endif

#ifndef VERSION_DEMO
void storm_owl_ground_cyclone_leave(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 1) {
        storm_owl_choose_corner(self);
        self->unk5 = 5;
        self->unk6 = 0;
    }
}
#endif

void storm_owl_spawn_roar(struct AnimatedObj* self)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = DEMO_ALT(0x1C, 0x19);
        obj->unk2 = 0;
        obj->unk50 = PLAYER_OBJECT(self);
        obj->unk42 = self->unk42;
        obj->animation_table = storm_owl_animations;
        obj->unk3C = self->unk3C;
        obj->unk40 = self->unk40;
        obj->bg_offset = self->bg_offset;
        obj->unk16 = VISUAL_SATURN_LAYER(4);
        obj->unk15 = self->unk15;
        obj->x_pos.val = self->x_pos.val;
        obj->y_pos.val = self->y_pos.val;
    }
}

void storm_owl_spawn_intro_wind(struct MainObj* self)
{
    struct VisualObj* obj = find_free_visual_obj();

    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = DEMO_ALT(0x1C, 0x19);
        obj->unk2 = 1;
        obj->unk50 = PLAYER_OBJECT(self);
        obj->unk42 = self->unk42;
        obj->animation_table = storm_owl_animations;
        obj->unk3C = self->sprite_frames;
        obj->unk40 = self->unk40;
        obj->bg_offset = self->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = self->unk15;
#ifdef VERSION_DEMO
        obj->x_pos.i.hi = 0x8F0;
        obj->y_pos.i.hi = 0x258;
#else
        if (engine_obj.stage == 7) {
            obj->x_pos.i.hi = background_objects[0].x_pos.i.hi + 0x20;
        } else {
            obj->x_pos.i.hi = background_objects[0].x_pos.i.hi + 0x120;
        }
        obj->y_pos.i.hi = background_objects[0].y_pos.i.hi + 0x60;
#endif
    }
}

void storm_owl_spawn_feather(struct MainObj* self)
{
    struct ShotObj* shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x25;
        shot->unk2 = 0;
        shot->unk7C = WEAPON_OBJECT(self);
        shot->unk42 = self->unk42;
        shot->animation_table = storm_owl_animations;
        shot->unk3C = (void*)self->sprite_frames;
        shot->unk40 = self->unk40;
        shot->bg_offset = self->bg_offset;
        shot->unk16 = VISUAL_SATURN_LAYER(5);
        shot->unk15 = self->unk15;
    }
}

void storm_owl_spawn_volley_feather(struct MainObj* self, s8 arg1)
{
    struct ShotObj* shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x25;
        shot->unk2 = arg1;
        shot->unk7C = WEAPON_OBJECT(self);
        shot->unk42 = self->unk42;
        shot->animation_table = storm_owl_animations;
        shot->unk3C = (void*)self->sprite_frames;
        shot->unk40 = self->unk40;
        shot->bg_offset = self->bg_offset;
        shot->unk16 = VISUAL_SATURN_LAYER(5);
        shot->unk15 = self->unk15;
    }
}

void storm_owl_spawn_cyclones(struct MainObj* self)
{
    u8 variant;
    u8 i;
    struct ShotObj* shot;

    variant = ((self->ext.main_60.corner % 2) == 0) * 2;
    for (i = 0; i < 3; i++) {
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x26;
            shot->unk2 = variant + i;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk42 = self->unk42;
            shot->animation_table = (u32**)storm_owl_animations;
            shot->unk3C = self->sprite_frames;
            shot->unk40 = self->unk40;
            shot->bg_offset = (s8)(u8)self->bg_offset;
            shot->unk16 = VISUAL_SATURN_LAYER(4);
            shot->unk15 = self->unk15;
        }
    }
}

#ifndef VERSION_DEMO
void storm_owl_spawn_storm_charge(struct AnimatedObj* self)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x1C;
        obj->unk2 = 2;
        obj->unk50 = PLAYER_OBJECT(self);
        obj->unk42 = self->unk42;
        obj->animation_table = storm_owl_animations;
        obj->unk3C = self->unk3C;
        obj->unk40 = self->unk40;
        obj->bg_offset = self->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = self->unk15;
        obj->x_pos.val = self->x_pos.val;
        obj->y_pos.val = self->y_pos.val;
    }
}
#endif

// storm_owl_spawn_storm_shot
#ifndef VERSION_DEMO
void func_80078180(struct MainObj* self)
{
    struct ShotObj* shot;
    u8 i;

    if (self->ext.main_60.storm_active == 1) {
        if (--self->unk7E != 0) {
            return;
        }

        for (i = 0; i < 4; i++) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x25;
                shot->unk2 = i + 5;
                shot->unk7C = WEAPON_OBJECT(self);
                shot->unk42 = self->unk42;
                shot->animation_table = (u32**)storm_owl_animations;
                shot->unk3C = self->sprite_frames;
                shot->unk40 = self->unk40;
                shot->bg_offset = self->bg_offset;
                shot->unk16 = VISUAL_SATURN_LAYER(5);
                shot->unk15 = self->unk15;
            }
        }
    }
    self->unk7E = 0xA;
}
#endif

#ifndef VERSION_DEMO
void storm_owl_spawn_hit_flash(struct PlayerObj* self)
{
    struct VisualObj* obj = find_free_visual_obj();
    if (obj != NULL) {
        obj->active = 0x41;
        obj->id = 0x1C;
        obj->unk2 = 3;
        obj->unk50 = self;
        obj->unk42 = self->unk42;
        obj->animation_table = (u32**)storm_owl_animations;
        obj->unk3C = self->unk3C;
        obj->unk40 = self->unk40;
        obj->bg_offset = self->bg_offset;
        obj->unk16 = 3;
        obj->unk15 = self->unk15;
        obj->x_pos.val = self->x_pos.val;
        obj->y_pos.val = self->y_pos.val;
    }
}
#endif

// storm_owl_spawn_ground_cyclone
#ifndef VERSION_DEMO
void func_80078314(struct MainObj* arg0)
{
    struct VisualObj* visual;
    struct ShotObj* shot;
    u8 i;
    s16 base_y;
    u16 x;
    s16 side_x;

    for (i = 0; i < 3; i++) {
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0x1C;
            visual->unk2 = 1;
            visual->unk50 = (struct PlayerObj*)arg0;
            visual->unk42 = arg0->unk42;
            visual->animation_table = (u32**)storm_owl_animations;
            visual->unk3C = (void*)arg0->sprite_frames;
            visual->unk40 = arg0->unk40;
            visual->bg_offset = arg0->bg_offset;
            visual->unk16 = 2;
            visual->unk15 = arg0->unk15;
            switch (i) {
            case 0:
                visual->x_pos.i.hi = g_Player.x_pos.i.hi;
                break;
            case 1:
                visual->x_pos.i.hi = g_Player.x_pos.i.hi - 0x30;
                break;
            case 2:
                visual->x_pos.i.hi = g_Player.x_pos.i.hi + 0x30;
                break;
            }
            base_y = background_objects[0].y_pos.i.hi;
            visual->y_pos.i.hi = base_y + 0x60;
            visual->unk5C.fields.mode = i;
        }
    }
    for (i = 0; i < 3; i++) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x26;
            shot->unk2 = 5;
            shot->unk7C = (struct WeaponObj*)arg0;
            shot->unk42 = arg0->unk42;
            shot->animation_table = (u32**)storm_owl_animations;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->unk40 = arg0->unk40;
            shot->bg_offset = arg0->bg_offset;
            shot->unk16 = 2;
            shot->unk15 = arg0->unk15;
            switch (i) {
            case 0:
                x = g_Player.x_pos.i.hi;
                shot->x_pos.i.hi = x;
                shot->timer = 0x20;
                break;
            case 1:
                side_x = g_Player.x_pos.i.hi - 0x30;
                shot->x_pos.i.hi = side_x;
                shot->timer = 0x28;
                break;
            case 2:
                side_x = g_Player.x_pos.i.hi + 0x30;
                shot->x_pos.i.hi = side_x;
                shot->timer = 0x28;
                break;
            }
            shot->y_pos.i.hi = background_objects[0].y_pos.i.hi + 0x150;
        }
    }
}
#endif

void storm_owl_choose_corner(struct MainObj* self)
{
    s32 player_x = g_Player.x_pos.val;

    if (player_x > self->x_pos.val) {
        if (get_random_nonzero() & 1) {
            self->ext.main_60.corner = 0;
        } else {
            self->ext.main_60.corner = 1;
        }
    } else {
        if (get_random_nonzero() & 1) {
            self->ext.main_60.corner = 2;
        } else {
            self->ext.main_60.corner = 3;
        }
    }
}

#ifndef VERSION_DEMO
void storm_owl_choose_pattern(struct MainObj* self)
{
    u8 idx;
    u8** table;
    u8 rnd;
    u8 i;

    idx = (self->hp - 1) / 16;
    table = storm_owl_patterns[idx];
    rnd = get_random() & 0xF;
    for (i = 0; i < 3; i++) {
        if (rnd < storm_owl_pattern_weights[idx][i]) {
            self->ext.main_60.pattern = table[i];
            return;
        }
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_clear_shots(void)
{
    u8 clear_value;
    u32 i;
    s32 j;
    u8* dst;

    clear_value = 0;
    for (i = 0; i < 0x20; i++) {
        if ((shot_objects[i].id == 0x25) || ((shot_objects[i].unk2 != 0) && (shot_objects[i].unk2 <= 4))) {
            dst = (u8*)&shot_objects[i];
            j = sizeof(shot_objects[i]);
            while (j-- != 0) {
                *dst++ = clear_value;
            }
        }
    }
}
#endif

#ifdef VERSION_DEMO
struct Unk_unk68 storm_owl_hurt_box = { -14, -21, 30, 40 };

struct Unk_unk68 storm_owl_attack_box = { -14, -21, 30, 40 };

struct Unk_unk68 storm_owl_grab_attack_box = { -16, 15, 12, 9 };

struct Unk_unk68 storm_owl_slam_terrain_box = { 5, 19, 11, 5 };

struct Unk_unk68 storm_owl_grab_terrain_box = { 0, 27, 14, 25 };

struct Unk_unk68 storm_owl_anim_0[6] = {
    { 6, 0, 1, 6 },
    { 4, 0, 1, 7 },
    { 4, 0, 1, 8 },
    { 6, 0, 1, 9 },
    { 4, 0, 1, 10 },
    { 4, 0, 251, 11 },
};

struct Unk_unk68 storm_owl_anim_1[6] = {
    { 4, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 4, 0, 1, 3 },
    { 2, 0, 1, 4 },
    { 2, 0, 251, 5 },
};

struct Unk_unk68 storm_owl_anim_2[3] = { { 1, 0, 1, 16 }, { 2, 0, 1, 17 }, { 6, 0, 254, 18 } };

struct Unk_unk68 storm_owl_anim_3[6] = {
    { 4, 0, 1, 19 },
    { 6, 0, 1, 20 },
    { 14, 0, 1, 21 },
    { 2, 0, 1, 22 },
    { 2, 0, 1, 23 },
    { 33, 0, 251, 24 },
};

union AnimationStep storm_owl_anim_4[7] = {
    { 6, 0, 1, 0x19 },
    { 3, 0, 1, 0x1A },
    { 10, 0, 1, 0x1B },
    { 3, 0, 1, 0x1C },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 33, 0, 0, 0x1D },
};

union AnimationStep storm_owl_anim_5[7] = {
    { 6, 0, 1, 0x1E },
    { 3, 0, 1, 0x1F },
    { 10, 0, 1, 0x20 },
    { 3, 0, 1, 0x21 },
    { 2, 0, 1, 0x22 },
    { 2, 0, 1, 0x23 },
    { 33, 0, 0, 0x24 },
};

union AnimationStep storm_owl_anim_6[5] = {
    { 6, 0, 1, 0x26 },
    { 8, 0, 1, 0x25 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x29 },
    { 33, 0, 0, 0x28 },
};

u8 storm_owl_anim_7[8] = { 2, 0, 1, 12, 2, 0, 0xFF, 13 };

u8 storm_owl_anim_8[8] = { 2, 0, 1, 14, 2, 0, 0xFF, 15 };

union AnimationStep storm_owl_anim_9[12] = {
    { 6, 0, 1, 0x06 },
    { 2, 0, 1, 0x5A },
    { 2, 0, 1, 0x5B },
    { 24, 0, 1, 0x5A },
    { 8, 0, 1, 0x5C },
    { 8, 0, 1, 0x5D },
    { 8, 0, 1, 0x5E },
    { 11, 0, 1, 0x5F },
    { 2, 0, 1, 0x60 },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x60 },
    { 47, 0, 0, 0x61 },
};

union AnimationStep storm_owl_anim_10[6] = {
    { 2, 0, 1, 0x62 },
    { 2, 0, 1, 0x63 },
    { 2, 0, 1, 0x64 },
    { 1, 0, 1, 0x65 },
    { 1, 0, 1, 0x66 },
    { 1, 0, 0, 0x67 },
};

u8 storm_owl_anim_11[8] = { 2, 0, 1, 0x68, 2, 0, 0xFF, 0x69 };

struct Unk_unk68 storm_owl_anim_12[5] = {
    { 3, 0, 1, 104 },
    { 3, 0, 1, 106 },
    { 3, 0, 1, 107 },
    { 3, 0, 1, 108 },
    { 3, 0, 252, 109 },
};

struct Unk_unk68 storm_owl_anim_13[16] = {
    { 1, 0, 1, 62 },
    { 1, 0, 1, 51 },
    { 1, 0, 1, 52 },
    { 1, 0, 1, 53 },
    { 1, 0, 1, 54 },
    { 1, 0, 1, 48 },
    { 1, 0, 1, 47 },
    { 1, 0, 1, 49 },
    { 1, 0, 1, 50 },
    { 1, 0, 1, 55 },
    { 1, 0, 1, 56 },
    { 1, 0, 1, 57 },
    { 1, 0, 1, 58 },
    { 1, 0, 1, 59 },
    { 1, 0, 1, 60 },
    { 1, 0, 241, 61 },
};

struct Unk_unk68 storm_owl_anim_14[19] = {
    { 1, 0, 1, 63 },
    { 1, 0, 1, 64 },
    { 1, 0, 1, 69 },
    { 1, 0, 1, 63 },
    { 1, 0, 1, 68 },
    { 1, 0, 1, 64 },
    { 1, 0, 1, 67 },
    { 1, 0, 1, 63 },
    { 1, 0, 1, 66 },
    { 1, 0, 1, 64 },
    { 1, 0, 1, 65 },
    { 1, 0, 1, 63 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 64 },
    { 1, 0, 1, 71 },
    { 1, 0, 1, 63 },
    { 1, 0, 1, 72 },
    { 1, 0, 1, 64 },
    { 1, 0, 238, 73 },
};

union AnimationStep storm_owl_anim_15[1] = { { 1, 0, 0, 0x2E } };

union AnimationStep storm_owl_anim_16[1] = { { 1, 0, 0, 0x2D } };

union AnimationStep storm_owl_anim_17[1] = { { 1, 0, 0, 0x2A } };

union AnimationStep storm_owl_anim_18[1] = { { 1, 0, 0, 0x2C } };

union AnimationStep storm_owl_anim_19[1] = { { 1, 0, 0, 0x2B } };

union AnimationStep storm_owl_anim_20[4] = { { 8, 0, 1, 0x6E }, { 8, 0, 1, 0x6F }, { 8, 0, 1, 0x70 }, { 8, 0, 0, 0x71 } };

union AnimationStep storm_owl_anim_21[4] = { { 8, 0, 1, 0x56 }, { 8, 0, 1, 0x57 }, { 8, 0, 1, 0x58 }, { 8, 0, 0, 0x59 } };

union AnimationStep storm_owl_anim_22[4] = { { 8, 0, 1, 0x4A }, { 8, 0, 1, 0x4B }, { 8, 0, 1, 0x4C }, { 8, 0, 0, 0x4D } };

union AnimationStep storm_owl_anim_23[4] = { { 8, 0, 1, 0x4E }, { 8, 0, 1, 0x4F }, { 8, 0, 1, 0x50 }, { 8, 0, 0, 0x51 } };

union AnimationStep storm_owl_anim_24[4] = { { 8, 0, 1, 0x52 }, { 8, 0, 1, 0x53 }, { 8, 0, 1, 0x54 }, { 8, 0, 0, 0x55 } };

union AnimationStep D_800D5004_demo[9] = {
    { 1, 0, 1, 0x45 },
    { 1, 0, 1, 0x44 },
    { 1, 0, 1, 0x43 },
    { 1, 0, 1, 0x42 },
    { 1, 0, 1, 0x41 },
    { 1, 0, 1, 0x46 },
    { 1, 0, 1, 0x47 },
    { 1, 0, 1, 0x48 },
    { 1, 0, 0, 0x49 },
};

union AnimationStep D_800D5028_demo[8] = {
    { 2, 0, 1, 0xA8 },
    { 2, 0, 1, 0xA9 },
    { 2, 0, 1, 0xAA },
    { 2, 0, 1, 0xAB },
    { 2, 0, 1, 0xA8 },
    { 2, 0, 1, 0xA9 },
    { 2, 0, 1, 0xAA },
    { 2, 0, 0, 0xAB },
};

union AnimationStep D_800D5048_demo[12] = {
    { 2, 0, 1, 0x90 },
    { 2, 0, 1, 0x91 },
    { 2, 0, 1, 0x92 },
    { 2, 0, 1, 0x93 },
    { 2, 0, 1, 0x94 },
    { 2, 0, 1, 0x95 },
    { 2, 0, 1, 0x96 },
    { 2, 0, 1, 0x97 },
    { 2, 0, 1, 0x98 },
    { 2, 0, 1, 0x99 },
    { 2, 0, 1, 0x9A },
    { 2, 0, 0, 0x9B },
};

union AnimationStep D_800D5078_demo[12] = {
    { 1, 0, 1, 0xA7 },
    { 1, 0, 1, 0xA6 },
    { 1, 0, 1, 0xA5 },
    { 1, 0, 1, 0xA4 },
    { 1, 0, 1, 0xA3 },
    { 1, 0, 1, 0xA2 },
    { 1, 0, 1, 0xA1 },
    { 1, 0, 1, 0xA0 },
    { 1, 0, 1, 0x9F },
    { 1, 0, 1, 0x9E },
    { 1, 0, 1, 0x9D },
    { 1, 0, 0, 0x9C },
};

union AnimationStep D_800D50A8_demo[36] = {
    { 1, 0, 1, 0x72 },
    { 1, 0, 1, 0x73 },
    { 1, 0, 1, 0x74 },
    { 1, 0, 1, 0x75 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x77 },
    { 1, 0, 1, 0x78 },
    { 1, 0, 1, 0x79 },
    { 1, 0, 1, 0x7A },
    { 1, 0, 1, 0x7B },
    { 1, 0, 1, 0x7C },
    { 1, 0, 1, 0x7D },
    { 1, 0, 1, 0x84 },
    { 1, 0, 1, 0x85 },
    { 1, 0, 1, 0x86 },
    { 1, 0, 1, 0x87 },
    { 1, 0, 1, 0x88 },
    { 1, 0, 1, 0x89 },
    { 1, 0, 1, 0x78 },
    { 1, 0, 1, 0x79 },
    { 1, 0, 1, 0x7A },
    { 1, 0, 1, 0x7B },
    { 1, 0, 1, 0x7C },
    { 1, 0, 1, 0x7D },
    { 1, 0, 1, 0x8A },
    { 1, 0, 1, 0x8B },
    { 1, 0, 1, 0x8C },
    { 1, 0, 1, 0x8D },
    { 1, 0, 1, 0x8E },
    { 1, 0, 1, 0x8F },
    { 1, 0, 1, 0x7E },
    { 1, 0, 1, 0x7F },
    { 1, 0, 1, 0x80 },
    { 1, 0, 1, 0x81 },
    { 1, 0, 1, 0x82 },
    { 1, 0, 0, 0x83 },
};

void* storm_owl_animations[30] = {
    storm_owl_anim_0,
    storm_owl_anim_1,
    storm_owl_anim_2,
    storm_owl_anim_3,
    storm_owl_anim_4,
    storm_owl_anim_5,
    storm_owl_anim_6,
    storm_owl_anim_7,
    storm_owl_anim_8,
    storm_owl_anim_9,
    storm_owl_anim_10,
    storm_owl_anim_11,
    storm_owl_anim_12,
    storm_owl_anim_13,
    storm_owl_anim_14,
    storm_owl_anim_15,
    storm_owl_anim_16,
    storm_owl_anim_17,
    storm_owl_anim_18,
    storm_owl_anim_19,
    storm_owl_anim_20,
    storm_owl_anim_21,
    storm_owl_anim_22,
    storm_owl_anim_23,
    storm_owl_anim_24,
    D_800D5004_demo,
    D_800D5028_demo,
    D_800D5048_demo,
    D_800D5078_demo,
    D_800D50A8_demo,
};

Main60Waypoint storm_owl_waypoints[4] = {
    { 0x08E0, 0x0220, 0x00020000, 0xFFFF0000 },
    { 0x08E0, 0x0290, 0x00028000, 0x00000800 },
    { 0x09E0, 0x0220, 0xFFFE0000, 0xFFFF0000 },
    { 0x09E0, 0x0290, 0xFFFD8000, 0x00000800 },
};

void (*storm_owl_state_funcs[4])(struct MainObj*) = {
    storm_owl_start,
    func_8007E1A8_demo,
    func_8007E278_demo,
    storm_owl_death,
};

void (*storm_owl_start_funcs[4])(struct MainObj*) = {
    storm_owl_start_wait_player,
    storm_owl_start_warning,
    storm_owl_start_wait_warning,
    func_800751AC,
};

void (*D_800D5200_demo[9])(struct MainObj*) = {
    enemy_hit_reaction,
    storm_owl_resume_step,
    storm_owl_intro,
    storm_owl_patrol,
    storm_owl_grab,
    storm_owl_reenter,
    storm_owl_feather,
    storm_owl_feather_volley,
    storm_owl_cyclone,
};

void (*storm_owl_intro_funcs[8])(struct MainObj*) = {
    func_80075944,
    storm_owl_intro_land,
    storm_owl_intro_roar,
    storm_owl_intro_pose,
    storm_owl_intro_start_health_bar,
    storm_owl_intro_fill_health,
    func_80075C6C,
    storm_owl_intro_rise,
};

void (*storm_owl_patrol_funcs[4])(struct MainObj*) = {
    func_8007E710_demo,
    func_8007E7AC_demo,
    storm_owl_patrol_wait,
    func_800760C4,
};

void (*storm_owl_grab_funcs[6])(struct MainObj*) = {
    storm_owl_grab_dive,
    func_80076364,
    func_8007651C,
    storm_owl_grab_carry,
    storm_owl_grab_slam,
    storm_owl_grab_leave,
};

void (*storm_owl_reenter_funcs[2])(struct MainObj*) = {
    storm_owl_reenter_warp,
    storm_owl_reenter_wait,
};

void (*storm_owl_feather_funcs[4])(struct MainObj*) = {
    storm_owl_feather_start,
    storm_owl_feather_fire,
    storm_owl_feather_takeoff,
    storm_owl_feather_leave,
};

void (*storm_owl_feather_volley_funcs[6])(struct MainObj*) = {
    storm_owl_feather_volley_start,
    func_80076D14,
    storm_owl_feather_volley_aim,
    storm_owl_feather_volley_release,
    storm_owl_feather_volley_wait,
    storm_owl_feather_volley_leave,
};

void (*storm_owl_cyclone_funcs[4])(struct MainObj*) = {
    storm_owl_cyclone_start,
    storm_owl_storm_begin,
    storm_owl_storm_end,
    storm_owl_storm_leave,
};

#else
struct Unk_unk68 storm_owl_hurt_box = { -14, -21, 30, 40 };

struct Unk_unk68 storm_owl_attack_box = { -14, -21, 30, 40 };

struct Unk_unk68 storm_owl_grab_attack_box = { -16, 15, 12, 9 };

struct Unk_unk68 storm_owl_slam_terrain_box = { 5, 19, 11, 5 };

struct Unk_unk68 storm_owl_grab_terrain_box = { 0, 27, 14, 25 };

struct Unk_unk68 storm_owl_anim_0[6] = {
    { 6, 0, 1, 6 },
    { 4, 0, 1, 7 },
    { 4, 0, 1, 8 },
    { 6, 0, 1, 9 },
    { 4, 0, 1, 10 },
    { 4, 0, -5, 11 },
};

struct Unk_unk68 storm_owl_anim_1[6] = {
    { 4, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 4, 0, 1, 3 },
    { 2, 0, 1, 4 },
    { 2, 0, -5, 5 },
};

struct Unk_unk68 storm_owl_anim_2[3] = {
    { 1, 0, 1, 16 },
    { 2, 0, 1, 17 },
    { 6, 0, -2, 18 },
};

struct Unk_unk68 storm_owl_anim_3[6] = {
    { 4, 0, 1, 19 },
    { 6, 0, 1, 20 },
    { 14, 0, 1, 21 },
    { 2, 0, 1, 22 },
    { 2, 0, 1, 23 },
    { 33, 0, -5, 24 },
};

union AnimationStep storm_owl_anim_4[] = {
    { 6, 0, 1, 0x19 },
    { 3, 0, 1, 0x1A },
    { 10, 0, 1, 0x1B },
    { 3, 0, 1, 0x1C },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 33, 0, 0, 0x1D },
};

union AnimationStep storm_owl_anim_5[] = {
    { 6, 0, 1, 0x1E },
    { 3, 0, 1, 0x1F },
    { 10, 0, 1, 0x20 },
    { 3, 0, 1, 0x21 },
    { 2, 0, 1, 0x22 },
    { 2, 0, 1, 0x23 },
    { 33, 0, 0, 0x24 },
};

union AnimationStep storm_owl_anim_6[] = {
    { 6, 0, 1, 0x26 },
    { 8, 0, 1, 0x25 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x29 },
    { 33, 0, 0, 0x28 },
};

u8 storm_owl_anim_7[8] = { 2, 0, 1, 12, 2, 0, 255, 13 };

u8 storm_owl_anim_8[8] = { 2, 0, 1, 14, 2, 0, 255, 15 };

union AnimationStep storm_owl_anim_9[] = {
    { 6, 0, 1, 0x06 },
    { 2, 0, 1, 0x5A },
    { 2, 0, 1, 0x5B },
    { 24, 0, 1, 0x5A },
    { 8, 0, 1, 0x5C },
    { 8, 0, 1, 0x5D },
    { 8, 0, 1, 0x5E },
    { 11, 0, 1, 0x5F },
    { 2, 0, 1, 0x60 },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x60 },
    { 47, 0, 0, 0x61 },
};

union AnimationStep storm_owl_anim_10[] = {
    { 2, 0, 1, 0x62 },
    { 2, 0, 1, 0x63 },
    { 2, 0, 1, 0x64 },
    { 1, 0, 1, 0x65 },
    { 1, 0, 1, 0x66 },
    { 1, 0, 0, 0x67 },
};

u8 storm_owl_anim_11[8] = { 2, 0, 1, 104, 2, 0, 255, 105 };

struct Unk_unk68 storm_owl_anim_12[5] = {
    { 3, 0, 1, 104 },
    { 3, 0, 1, 106 },
    { 3, 0, 1, 107 },
    { 3, 0, 1, 108 },
    { 3, 0, -4, 109 },
};

struct Unk_unk68 storm_owl_anim_13[16] = {
    { 1, 0, 1, 62 },
    { 1, 0, 1, 51 },
    { 1, 0, 1, 52 },
    { 1, 0, 1, 53 },
    { 1, 0, 1, 54 },
    { 1, 0, 1, 48 },
    { 1, 0, 1, 47 },
    { 1, 0, 1, 49 },
    { 1, 0, 1, 50 },
    { 1, 0, 1, 55 },
    { 1, 0, 1, 56 },
    { 1, 0, 1, 57 },
    { 1, 0, 1, 58 },
    { 1, 0, 1, 59 },
    { 1, 0, 1, 60 },
    { 1, 0, -15, 61 },
};

struct Unk_unk68 storm_owl_anim_14[19] = {
    { 1, 0, 1, 63 },
    { 1, 0, 1, 64 },
    { 1, 0, 1, 69 },
    { 1, 0, 1, 63 },
    { 1, 0, 1, 68 },
    { 1, 0, 1, 64 },
    { 1, 0, 1, 67 },
    { 1, 0, 1, 63 },
    { 1, 0, 1, 66 },
    { 1, 0, 1, 64 },
    { 1, 0, 1, 65 },
    { 1, 0, 1, 63 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 64 },
    { 1, 0, 1, 71 },
    { 1, 0, 1, 63 },
    { 1, 0, 1, 72 },
    { 1, 0, 1, 64 },
    { 1, 0, -18, 73 },
};

union AnimationStep storm_owl_anim_15[] = {
    { 1, 0, 0, 0x2E },
};

union AnimationStep storm_owl_anim_16[] = {
    { 1, 0, 0, 0x2D },
};

union AnimationStep storm_owl_anim_17[] = {
    { 1, 0, 0, 0x2A },
};

union AnimationStep storm_owl_anim_18[] = {
    { 1, 0, 0, 0x2C },
};

union AnimationStep storm_owl_anim_19[] = {
    { 1, 0, 0, 0x2B },
};

union AnimationStep storm_owl_anim_20[] = {
    { 8, 0, 1, 0x6E },
    { 8, 0, 1, 0x6F },
    { 8, 0, 1, 0x70 },
    { 8, 0, 0, 0x71 },
};

union AnimationStep storm_owl_anim_21[] = {
    { 8, 0, 1, 0x56 },
    { 8, 0, 1, 0x57 },
    { 8, 0, 1, 0x58 },
    { 8, 0, 0, 0x59 },
};

union AnimationStep storm_owl_anim_22[] = {
    { 8, 0, 1, 0x4A },
    { 8, 0, 1, 0x4B },
    { 8, 0, 1, 0x4C },
    { 8, 0, 0, 0x4D },
};

union AnimationStep storm_owl_anim_23[] = {
    { 8, 0, 1, 0x4E },
    { 8, 0, 1, 0x4F },
    { 8, 0, 1, 0x50 },
    { 8, 0, 0, 0x51 },
};

union AnimationStep storm_owl_anim_24[] = {
    { 8, 0, 1, 0x52 },
    { 8, 0, 1, 0x53 },
    { 8, 0, 1, 0x54 },
    { 8, 0, 0, 0x55 },
};

struct Unk_unk68 storm_owl_anim_25[9] = {
    { 1, 0, 1, 69 },
    { 1, 0, 1, 68 },
    { 1, 0, 1, 67 },
    { 1, 0, 1, 66 },
    { 1, 0, 1, 65 },
    { 1, 0, 1, 70 },
    { 1, 0, 1, 71 },
    { 1, 0, 1, 72 },
    { 1, 0, -8, 73 },
};

struct Unk_unk68 storm_owl_anim_26[8] = {
    { 2, 0, 1, -88 },
    { 2, 0, 1, -87 },
    { 2, 0, 1, -86 },
    { 2, 0, 1, -85 },
    { 2, 0, 1, -88 },
    { 2, 0, 1, -87 },
    { 2, 0, 1, -86 },
    { 2, 0, -7, -85 },
};

union AnimationStep storm_owl_anim_27[] = {
    { 2, 0, 1, 0x90 },
    { 2, 0, 1, 0x91 },
    { 2, 0, 1, 0x92 },
    { 2, 0, 1, 0x93 },
    { 2, 0, 1, 0x94 },
    { 2, 0, 1, 0x95 },
    { 2, 0, 1, 0x96 },
    { 2, 0, 1, 0x97 },
    { 2, 0, 1, 0x98 },
    { 2, 0, 1, 0x99 },
    { 2, 0, 1, 0x9A },
    { 2, 0, 0, 0x9B },
};

union AnimationStep storm_owl_anim_28[] = {
    { 1, 0, 1, 0xA7 },
    { 1, 0, 1, 0xA6 },
    { 1, 0, 1, 0xA5 },
    { 1, 0, 1, 0xA4 },
    { 1, 0, 1, 0xA3 },
    { 1, 0, 1, 0xA2 },
    { 1, 0, 1, 0xA1 },
    { 1, 0, 1, 0xA0 },
    { 1, 0, 1, 0x9F },
    { 1, 0, 1, 0x9E },
    { 1, 0, 1, 0x9D },
    { 1, 0, 0, 0x9C },
};

union AnimationStep storm_owl_anim_29[] = {
    { 1, 0, 1, 0x78 },
    { 1, 0, 1, 0x79 },
    { 1, 0, 1, 0x7A },
    { 1, 0, 1, 0x7B },
    { 1, 0, 1, 0x7C },
    { 1, 0, 1, 0x78 },
    { 1, 0, 1, 0x7D },
    { 1, 0, 1, 0x72 },
    { 1, 0, 1, 0x73 },
    { 1, 0, 1, 0x74 },
    { 1, 0, 1, 0x75 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x72 },
    { 1, 0, 1, 0x77 },
    { 1, 0, 1, 0x7E },
    { 1, 0, 1, 0x7F },
    { 1, 0, 1, 0x80 },
    { 1, 0, 1, 0x81 },
    { 1, 0, 1, 0x82 },
    { 1, 0, 1, 0x7E },
    { 1, 0, 1, 0x83 },
    { 1, 0, 1, 0x7E },
    { 1, 0, 1, 0x7F },
    { 1, 0, 1, 0x80 },
    { 1, 0, 1, 0x81 },
    { 1, 0, 1, 0x82 },
    { 1, 0, 1, 0x7E },
    { 1, 0, 1, 0x83 },
    { 1, 0, 1, 0x84 },
    { 1, 0, 1, 0x85 },
    { 1, 0, 1, 0x86 },
    { 1, 0, 1, 0x87 },
    { 1, 0, 1, 0x88 },
    { 1, 0, 1, 0x84 },
    { 1, 0, 1, 0x89 },
    { 1, 0, 1, 0x84 },
    { 1, 0, 1, 0x85 },
    { 1, 0, 1, 0x86 },
    { 1, 0, 1, 0x87 },
    { 1, 0, 1, 0x88 },
    { 1, 0, 1, 0x84 },
    { 1, 0, 1, 0x89 },
    { 1, 0, 1, 0x84 },
    { 1, 0, 1, 0x85 },
    { 1, 0, 1, 0x86 },
    { 1, 0, 1, 0x87 },
    { 1, 0, 1, 0x88 },
    { 1, 0, 1, 0x84 },
    { 1, 0, 1, 0x89 },
    { 1, 0, 1, 0x8A },
    { 1, 0, 1, 0x8B },
    { 1, 0, 1, 0x8C },
    { 1, 0, 1, 0x8D },
    { 1, 0, 1, 0x8E },
    { 1, 0, 1, 0x8A },
    { 1, 0, 1, 0x8F },
    { 1, 0, 1, 0x8A },
    { 1, 0, 1, 0x8B },
    { 1, 0, 1, 0x8C },
    { 1, 0, 1, 0x8D },
    { 1, 0, 1, 0x8E },
    { 1, 0, 1, 0x8A },
    { 1, 0, 0, 0x8F },
};

void* storm_owl_animations[30] = {
    storm_owl_anim_0,
    storm_owl_anim_1,
    storm_owl_anim_2,
    storm_owl_anim_3,
    storm_owl_anim_4,
    storm_owl_anim_5,
    storm_owl_anim_6,
    storm_owl_anim_7,
    storm_owl_anim_8,
    storm_owl_anim_9,
    storm_owl_anim_10,
    storm_owl_anim_11,
    storm_owl_anim_12,
    storm_owl_anim_13,
    storm_owl_anim_14,
    storm_owl_anim_15,
    storm_owl_anim_16,
    storm_owl_anim_17,
    storm_owl_anim_18,
    storm_owl_anim_19,
    storm_owl_anim_20,
    storm_owl_anim_21,
    storm_owl_anim_22,
    storm_owl_anim_23,
    storm_owl_anim_24,
    storm_owl_anim_25,
    storm_owl_anim_26,
    storm_owl_anim_27,
    storm_owl_anim_28,
    storm_owl_anim_29,
};

Main60Waypoint storm_owl_waypoints[4] = {
    { 0x0018, 0x0028, 0x00020000, 0xFFFF0000 },
    { 0x0018, 0x00B0, 0x00028000, 0x00000800 },
    { 0x0128, 0x0028, 0xFFFE0000, 0xFFFF0000 },
    { 0x0128, 0x00B0, 0xFFFD8000, 0x00000800 },
};

u8 storm_owl_pattern_0[4] = { 3, 3, 8, 255 };

u8 storm_owl_pattern_1[4] = { 3, 3, 255, 0 };

u8 storm_owl_pattern_2[4] = { 3, 3, 8, 255 };

u8 storm_owl_pattern_3[4] = { 3, 7, 255, 0 };

u8 storm_owl_pattern_4[4] = { 12, 7, 3, 255 };

u8 storm_owl_pattern_5[4] = { 12, 12, 3, 255 };

u8 storm_owl_pattern_6[4] = { 12, 9, 3, 255 };

u8* storm_owl_patterns_high_health[2] = {
    storm_owl_pattern_0,
    storm_owl_pattern_1,
};

u8* storm_owl_patterns_mid_health[2] = {
    storm_owl_pattern_2,
    storm_owl_pattern_3,
};

u8* storm_owl_patterns_low_health[3] = {
    storm_owl_pattern_4,
    storm_owl_pattern_5,
    storm_owl_pattern_6,
};

u8** storm_owl_patterns[3] = {
    storm_owl_patterns_low_health,
    storm_owl_patterns_mid_health,
    storm_owl_patterns_high_health,
};

u8 storm_owl_pattern_weights[4][3] = {
    { 0x04, 0x0A, 0x10 },
    { 0x08, 0x10, 0x10 },
    { 0x0A, 0x10, 0x10 },
    { 0x00, 0x00, 0x00 },
};

void (*storm_owl_state_funcs[3])() = {
    storm_owl_start,
    func_80075320,
    storm_owl_death,
};

void (*storm_owl_start_funcs[4])() = {
    storm_owl_start_wait_player,
    storm_owl_start_warning,
    storm_owl_start_wait_warning,
    func_800751AC,
};

void (*storm_owl_step_funcs[13])() = {
    enemy_hit_reaction,
    storm_owl_resume_step,
    storm_owl_intro,
    storm_owl_patrol,
    storm_owl_grab,
    storm_owl_reenter,
    storm_owl_feather,
    storm_owl_feather_volley,
    storm_owl_cyclone,
    storm_owl_storm,
    storm_owl_hover,
    storm_owl_stagger,
    storm_owl_ground_cyclone,
};

void (*storm_owl_death_funcs[3])() = {
    storm_owl_death_start,
    storm_owl_death_explode,
    storm_owl_death_finish,
};

void (*storm_owl_intro_funcs[8])() = {
    func_80075944,
    storm_owl_intro_land,
    storm_owl_intro_roar,
    storm_owl_intro_pose,
    storm_owl_intro_start_health_bar,
    storm_owl_intro_fill_health,
    func_80075C6C,
    storm_owl_intro_rise,
};

void (*storm_owl_patrol_funcs[5])() = {
    storm_owl_patrol_start,
    func_80075E78,
    storm_owl_patrol_wait,
    func_800760C4,
    storm_owl_patrol_return,
};

void (*storm_owl_grab_funcs[6])() = {
    storm_owl_grab_dive,
    func_80076364,
    func_8007651C,
    storm_owl_grab_carry,
    storm_owl_grab_slam,
    storm_owl_grab_leave,
};

void (*storm_owl_reenter_funcs[2])() = {
    storm_owl_reenter_warp,
    storm_owl_reenter_wait,
};

void (*storm_owl_feather_funcs[4])() = {
    storm_owl_feather_start,
    storm_owl_feather_fire,
    storm_owl_feather_takeoff,
    storm_owl_feather_leave,
};

void (*storm_owl_feather_volley_funcs[6])() = {
    storm_owl_feather_volley_start,
    func_80076D14,
    storm_owl_feather_volley_aim,
    storm_owl_feather_volley_release,
    storm_owl_feather_volley_wait,
    storm_owl_feather_volley_leave,
};

void (*storm_owl_cyclone_funcs[4])() = {
    storm_owl_cyclone_start,
    storm_owl_cyclone_fire,
    storm_owl_cyclone_finish,
    storm_owl_cyclone_leave,
};

void (*storm_owl_storm_funcs[9])() = {
    storm_owl_storm_start,
    storm_owl_storm_fly_to_center,
    storm_owl_storm_charge,
    storm_owl_storm_begin,
    storm_owl_storm_rain,
    func_80077580,
    storm_owl_storm_rain_again,
    storm_owl_storm_end,
    storm_owl_storm_leave,
};

void (*storm_owl_hover_funcs[2])() = {
    storm_owl_hover_start,
    storm_owl_hover_wait,
};

void (*storm_owl_stagger_funcs[3])() = {
    storm_owl_stagger_start,
    storm_owl_stagger_recover,
    storm_owl_stagger_leave,
};

void (*storm_owl_ground_cyclone_funcs[7])() = {
    storm_owl_ground_cyclone_start,
    storm_owl_ground_cyclone_drop,
    storm_owl_ground_cyclone_land,
    storm_owl_ground_cyclone_fire,
    storm_owl_ground_cyclone_wait,
    storm_owl_ground_cyclone_takeoff,
    storm_owl_ground_cyclone_leave,
};
#endif
