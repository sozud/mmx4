// MainObj, main_object_update_funcs[61]
// 8007872C..8007B90C
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_61_split_mushroom.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/player_common.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/stage_objects.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/128C4.h"
#include "main/1E1BC.h"
#endif

extern s32 split_mushroom_walk_speeds[3];
extern struct Unk_unk68 split_mushroom_terrain_box;

// split_mushroom_state_funcs
extern void (*split_mushroom_state_funcs[])(struct MainObj*);
void func_8007877C(struct MainObj*);

void split_mushroom_death(struct MainObj* arg0);

// split_mushroom_step_funcs
void split_mushroom_intro(struct MainObj* arg0);
void split_mushroom_stun(struct MainObj* arg0);
void split_mushroom_spore_rain(struct MainObj* arg0);
void split_mushroom_walk(struct MainObj* arg0);
void split_mushroom_dash(struct MainObj* arg0);
void split_mushroom_combo(struct MainObj* arg0);
void split_mushroom_wall_jump(struct MainObj* arg0);

// split_mushroom_death_funcs
extern void (*split_mushroom_death_funcs[])(struct MainObj*);
void split_mushroom_death_start(struct MainObj*);

void split_mushroom_death_finish(struct MainObj*);

// split_mushroom_intro_funcs
extern void (*split_mushroom_intro_funcs[])(struct MainObj*);

void split_mushroom_intro_drop(struct MainObj*);
void split_mushroom_intro_bounce(struct MainObj*);
void split_mushroom_intro_land(struct MainObj*);

void split_mushroom_intro_start_health_bar(struct MainObj*);
void split_mushroom_intro_fill_health(struct MainObj*);

// split_mushroom_stun_funcs
extern void (*split_mushroom_stun_funcs[])(struct MainObj*);
void split_mushroom_stun_start(struct MainObj*);

void split_mushroom_stun_fall(struct MainObj*);
void split_mushroom_stun_merge(struct MainObj*);

void split_mushroom_stun_land(struct MainObj*);
void split_mushroom_stun_split(struct MainObj*);

// split_mushroom_spore_rain_funcs
extern void (*split_mushroom_spore_rain_funcs[])(struct MainObj*);

void split_mushroom_spore_rain_split(struct MainObj*);
void split_mushroom_spore_rain_land(struct MainObj*);
void split_mushroom_spore_rain_recover(struct MainObj*);
void split_mushroom_spore_rain_finish(struct MainObj*);

// split_mushroom_walk_funcs
extern void (*split_mushroom_walk_funcs[])(struct MainObj*);
void split_mushroom_walk_start(struct MainObj*);
void split_mushroom_walk_move(struct MainObj*);

void split_mushroom_walk_fall(struct MainObj*);
void func_8007A444(struct MainObj*);

// split_mushroom_dash_funcs
extern void (*split_mushroom_dash_funcs[])(struct MainObj*);

void split_mushroom_dash_bounce(struct MainObj*);
void split_mushroom_dash_land(struct MainObj*);
void split_mushroom_dash_recover(struct MainObj*);
void split_mushroom_dash_finish(struct MainObj*);

// split_mushroom_combo_funcs
extern void (*split_mushroom_combo_funcs[])(struct MainObj*);

void split_mushroom_combo_swing(struct MainObj*);
void func_8007AE2C(struct MainObj*);
void split_mushroom_combo_repeat(struct MainObj*);
void split_mushroom_combo_sync(struct MainObj*);
void split_mushroom_combo_end(struct MainObj*);
void split_mushroom_combo_restart(struct MainObj*);

// split_mushroom_wall_jump_funcs
extern void (*split_mushroom_wall_jump_funcs[])(struct MainObj*);

void split_mushroom_wall_jump_air(struct MainObj*);

void split_mushroom_wall_jump_cling(struct MainObj*);

void split_mushroom_wall_jump_turn(struct MainObj*);
void split_mushroom_wall_jump_land(struct MainObj*);
void split_mushroom_wall_jump_finish(struct MainObj*);

void split_mushroom_load_palette(void);

void split_mushroom_update(struct MainObj* self)
{
    split_mushroom_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

// split_mushroom_init
void func_8007877C(struct MainObj* self)
{
    self->contact_damage = 5;
    self->hp = 0;
    self->invincibility_timer = 0;
    self->collision_data = D_80107BF8;

    if (engine_obj.stage != 0xC) {
        self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0xB0);
        self->unk15 = PLAYER_FACING_RIGHT;
    } else {
        self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0x160);
        self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 4);
        self->unk42 = OBJECT_CLUT(0x7888);
        self->unk15 = 0;
    }

    self->bg_offset = g_Player.bg_offset;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->gravity = FIXED(0.21875);
    self->animation_table = (const u8* const*)split_mushroom_animations;
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->hurt_box = &split_mushroom_hurt_box;
    self->attack_box = &split_mushroom_attack_box;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->air_state = 0;
    self->terrain_box = &split_mushroom_terrain_box;

    set_animation(self, 5);

    self->ext.main_61.flash_timer = 0;
    self->ext.main_61.split = 0;
    self->ext.main_61.stunned = 0;
    self->ext.main_61.split_hits = 3;
    self->ext.main_61.merge = 0;
    self->ext.main_61.hit_lock = 0;
    self->ext.main_61.active = 0;
    self->ext.main_61.speed_level = 0;
    self->ext.main_61.split_done = 0;
    split_mushroom_load_palette();
    self->state = 1;
    self->unk5 = 1;
    self->unk6 = 0;
}

// split_mushroom_main
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8002217C(arg_u16 message, u8 portrait, s32 delay_only);
ret_s8 func_8002DD04(struct MainObj* object);
#endif

extern s16 split_mushroom_hop_speeds[];
extern void (*split_mushroom_step_funcs[8])();
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800788E4(struct MainObj* arg0);
void func_800793AC(struct MainObj* arg0);
void func_80079824(struct MainObj* arg0);
void func_80079A8C(struct MainObj* arg0);
void func_80079B50(struct MainObj* arg0);
void func_8007A2B4(struct MainObj* arg0);
void func_8007A4EC(struct MainObj* arg0);
static void main61_wall_hit(struct MainObj* arg0);
void func_8007A96C(struct MainObj* arg0);
void func_8007AB1C(struct MainObj* arg0);
void func_8007B1BC(struct MainObj* arg0);
void func_8007B418(struct MainObj* arg0);
void func_8007B6BC(struct AnimatedObj* obj);
extern struct Unk_unk68 D_80107BF8[];
extern struct Unk_unk68 split_mushroom_wall_terrain_box;
static void main61_wall_hit(struct MainObj* arg0)
{
    func_8001540C(2, 0xA8, arg0);
    split_mushroom_spawn_afterimage(arg0);
    if (!(background_objects[g_Player.bg_offset].unk34 & 0x10))
        start_screen_shake_x(0x10, 8, 2);
}
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_61_split_mushroom", func_800788E4);
#else
void func_800788E4(struct MainObj* arg0)
{
    s32 hit;
    s8 flash;
    struct VisualObj* visual;
    struct MainObj* other;
    struct ShotObj* shot;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    ((void (*)(struct MainObj*))split_mushroom_step_funcs[arg0->unk5])(arg0);
    if (arg0->unk2 == 0 && arg0->ext.main_61.active == 0)
        return;
    hit = 0;
    if (arg0->ext.main_61.split != 0xFF && arg0->ext.main_61.hit_lock == 0 && arg0->unk2 == 0)
        hit = func_8002DD04(arg0);
    flash = (s8)arg0->ext.main_61.flash_timer;
    if (flash == 0) {
        arg0->ext.main_61.hit_lock = 0;
        if (hit < 0) {
            g_Player.spike_immune = 1;
            STOP_SOUND(2, 0xA7, 0x6);
            if (arg0->unk2 == 0) {
                arg0->state = 2;
                arg0->unk5 = 0;
                if (arg0->ext.main_61.split != 0) {
                    arg0->ext.main_61.partner->on_screen = 0;
                    ZeroObjectState(OBJECT_HEADER(arg0->ext.main_61.partner));
                }
            } else {
                arg0->ext.main_61.partner->state = 2;
                arg0->ext.main_61.partner->unk5 = 0;
                arg0->on_screen = 0;
                ZeroObjectState(OBJECT_HEADER(arg0));
            }
            return;
        }
        if (hit != 0 && hit != 0x7F) {
            if (arg0->unk5 != 6 && hit != 2 && hit != 0xB && hit != 0x21 && (u32)(get_random() & 0xF) < 4) {
                shot = find_free_shot_obj();
                if (shot != NULL) {
                    shot->active = 0x41;
                    shot->id = 0x27;
                    shot->unk2 = 0;
                    shot->unk40 = arg0->unk40;
                    shot->unk42 = arg0->unk42;
                    shot->animation_table = (void*)arg0->animation_table;
                    shot->unk3C = (void*)arg0->sprite_frames;
                    shot->unk15 = arg0->unk15;
                    shot->bg_offset = arg0->bg_offset;
                    shot->x_pos.val = arg0->x_pos.val;
                    shot->y_pos.val = arg0->y_pos.val;
                    shot->unk15 = arg0->unk15;
                    if (arg0->unk2 == 0)
                        shot->unk7C = (struct WeaponObj*)arg0;
                    else
                        shot->unk7C = (struct WeaponObj*)arg0->ext.main_61.partner;
                    shot->state = 7;
                }
            }
            if ((u32)(hit - 0x19) < 2) {
                arg0->ext.main_61.flash_timer = 6;
                arg0->ext.main_61.hit_lock = 1;
            } else {
                arg0->ext.main_61.flash_timer = 0x40;
            }
            if (hit != 2 && hit != 0xB && hit != 0x21) {
                visual = find_free_visual_obj();
                if (visual != NULL) {
                    visual->active = 0x41;
                    visual->id = 0x22;
                    visual->unk2 = 1;
                    visual->unk16 = 0;
                    visual->unk40 = arg0->unk40;
                    visual->unk42 = arg0->unk42;
                    visual->animation_table = (void*)arg0->animation_table;
                    visual->unk3C = (void*)arg0->sprite_frames;
                    visual->unk15 = arg0->unk15;
                    visual->bg_offset = arg0->bg_offset;
                    visual->unk15 = 0;
                    visual->unk50 = (struct PlayerObj*)arg0;
                    visual->unk5C.value = arg0->ext.main_61.flash_timer;
                    visual->state = 0;
                    set_animation(visual, 0x14);
                }
            }
            arg0->collision_data = D_801060F0;
            arg0->unk42 |= 0x8000;
            if ((hit == 2 || hit == 0xB || hit == 0x21) && arg0->ext.main_61.stunned == 0) {
                STOP_SOUND(2, 0xA7, 0x6);
                arg0->ext.main_61.stunned = 1;
                set_animation(arg0, 0x13);
                arg0->unk7E = 1;
                arg0->invincibility_timer = 1;
                arg0->unk5 = 2;
                arg0->unk6 = 0;
                if (arg0->ext.main_61.split != 0) {
                    if (arg0->unk2 == 0) {
                        if (--arg0->ext.main_61.split_hits == 0)
                            arg0->ext.main_61.merge = 1;
                    } else {
                        other = arg0->ext.main_61.partner;
                        if (--other->ext.main_61.split_hits == 0)
                            arg0->ext.main_61.partner->ext.main_61.merge = 1;
                    }
                    set_animation(arg0->ext.main_61.partner, 0x13);
                    arg0->ext.main_61.partner->invincibility_timer = 1;
                    arg0->ext.main_61.partner->unk5 = 2;
                    arg0->ext.main_61.partner->unk6 = 0;
                }
            }
        }
    } else {
        arg0->ext.main_61.flash_timer = --flash;
        if (flash == 0) {
            arg0->collision_data = D_80107BF8;
            arg0->unk42 &= 0x7FFF;
        } else if (flash & 1) {
            arg0->unk42 |= 0x8000;
        } else {
            arg0->unk42 &= 0x7FFF;
        }
    }
    if (arg0->ext.main_61.blink_timer != 0) {
        if ((--arg0->ext.main_61.blink_timer & 1) == 0) {
            arg0->on_screen = 0;
            return;
        }
    }
    arg0->ext.main_61.speed_level = 0;
    if (arg0->hp < 0x20)
        arg0->ext.main_61.speed_level = 1;
    else if (arg0->hp < 0x10)
        arg0->ext.main_61.speed_level = 2;
    if ((u32)((u8)arg0->unk5 - 1) >= 2)
        func_8002D9BC(arg0);
    update_on_screen(BASE_OBJECT(arg0), 0x60, 0x60);
}
#endif

void split_mushroom_death(struct MainObj* self)
{
    split_mushroom_death_funcs[self->unk5](self);
}

void split_mushroom_death_start(struct MainObj* self)
{
    g_Player.stun_timer = 0;
    player_start_script_action(0x14, g_Player.unk15);
    self->unk5 = 1;
    self->unk42 &= 0x7FFF;
    set_animation(self, 0x15);
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->invincibility_timer = 0x19;
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_61_split_mushroom", split_mushroom_death_explode);
#else
void split_mushroom_death_explode(struct MainObj* self)
{
    struct EffectObj* effect;
    u8 value;

    if (--self->unk7C == 0) {
        self->unk5 = 2;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.i.hi;
            effect->y_pos.i.hi = self->y_pos.i.hi;
            self->ext.main_61.data.effect = effect;
        }
    }

    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);

    if (self->unk7E-- == 0) {
        self->unk42 ^= 0x8000;
        self->invincibility_timer -= 5;
        if ((s8)self->invincibility_timer > 0x19) {
            self->invincibility_timer = 0;
        }
        value = self->invincibility_timer;
        if ((s8)self->invincibility_timer < 5) {
            value = 5;
        }
        self->unk7E = (s8)value;
    }
}
#endif

void split_mushroom_death_finish(struct MainObj* self)
{
    struct EffectObj* effect = self->ext.main_61.data.effect;
    self->on_screen = 0;
    if (effect->active != 0) {
        if (effect->unk7 == 0) {
            if (self->unk7E-- == 0) {
                self->unk7E = 5;
                self->unk42 ^= 0x8000;
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

void split_mushroom_intro(struct MainObj* self)
{
    split_mushroom_intro_funcs[self->unk6](self);
}

void split_mushroom_intro_wait_player(struct MainObj* self)
{
    struct EffectObj* effect;

    if (3 == engine_obj.stage) {
        if (engine_obj.cur_character == 0 ? g_Player.y_pos.i.hi < 0x1CC : g_Player.y_pos.i.hi < 0x1CB) {
            effect = find_free_effect_obj();
            if (effect != NULL) {
                effect->active = 1;
                effect->id = 0x18;
                self->ext.main_61.data.effect = effect;
            }
            player_start_script_action(0x14, 0);
        } else {
            return;
        }
    } else {
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            self->ext.main_61.data.effect = effect;
        }
        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
    }
    self->unk6 = 1;
}

void split_mushroom_intro_drop(struct MainObj* self)
{
    if (0 == *self->ext.main_61.data.script) {
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 0;
        engine_obj.boss_ptr = self;
        self->y_pos.i.hi = background_objects[g_Player.bg_offset].y_pos.i.hi - 0x20;
        self->ext.main_61.active = 1;
        func_8001540C(2, SATURN_SOUND(0xA7, 0x2A), self);
        self->unk7C = 2;
        self->unk6 = 2;
    }
}

void split_mushroom_intro_bounce(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk7C == 0 && self->y_speed < 0) {
        STOP_SOUND(2, 0xA7, 0x6);
        set_animation(self, 3);
        self->unk7C = 0xFF;
    }
    if (self->collision_flags & 8) {
        if (self->unk7C == 0xFF) {
            set_animation(self, 0xA);
            func_8001540C(2, SATURN_SOUND(0xA6, 0x29), self);
            self->unk6 = 3;
        } else {
            func_8001540C(2, SATURN_SOUND(0xA8, 0x2B), self);
            self->y_speed = FIXED(6);
            self->unk7C--;
            func_8001540C(2, SATURN_SOUND(0xA5, 0x28), self);
        }
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void split_mushroom_intro_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation((struct Unk19*)self, 17);
        self->unk6 = 4;
    }
}

// split_mushroom_intro_talk
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_61_split_mushroom", func_800793AC);
#else
void func_800793AC(struct MainObj* arg0)
{
    s32 i;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        func_8001540C(2, SATURN_SOUND(0xA9, 0x2C), arg0);
        for (i = 0; i < 5; i++) {
            struct ShotObj* shot = find_free_shot_obj();

            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x27;
                shot->unk2 = i;
                shot->unk40 = arg0->unk40;
                shot->unk42 = arg0->unk42;
                shot->animation_table = (void*)arg0->animation_table;
                shot->unk3C = (void*)arg0->sprite_frames;
                shot->unk15 = arg0->unk15;
                shot->bg_offset = arg0->bg_offset;
                shot->x_pos.val = arg0->x_pos.val;
                shot->y_pos.val = arg0->y_pos.val;
                shot->unk15 = arg0->unk15;
                if (arg0->unk2 == 0)
                    shot->unk7C = (struct WeaponObj*)arg0;
                else
                    shot->unk7C = (struct WeaponObj*)arg0->ext.main_61.partner;
                shot->state = 7;
            }
        }
    }
    if (arg0->animation_step.fields.event == 2) {
        if (engine_obj.stage == 3) {
            func_8002217C(0xA, 0xFF, (u8)engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
        arg0->unk6 = 5;
    }
}
#endif

void split_mushroom_intro_start_health_bar(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        set_animation(self, 0);
        self->unk7E = 3;
        self->unk6 = 6;
        play_boss_voice(2);
    }
}

void split_mushroom_intro_fill_health(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (update_boss_music_delay() != 0) {
        return;
    }
    if (--self->unk7E == 0) {
        func_8001540C(0, SATURN_SOUND(0xE, 0x14), NULL);
        self->unk7E = 3;
    }
    if (++self->hp == 0x30) {
        set_animation(self, 2);
        self->unk5 = 7;
        self->unk6 = 0;
        player_end_script_action();
    }
}

void split_mushroom_stun(struct MainObj* self)
{
    split_mushroom_stun_funcs[self->unk6](self);
}

void split_mushroom_stun_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk2 == 0) {
        if (--self->unk7E == 0) {
            self->unk7E = 0xC;
            func_8001540C(2, SATURN_SOUND(0xAB, 0x2E), self);
        }
    }
    if (self->animation_step.fields.event != 0) {
        self->contact_damage = 5;
        self->terrain_box = &split_mushroom_terrain_box;
        self->unk7C = 0x1E;
        self->unk6 = 1;
    }
}

void split_mushroom_stun_wait(struct MainObj* self)
{
    if (--self->unk7C != 0) {
        return;
    }

    if (self->ext.main_61.split != 0) {
        if (self->unk2 == 0) {
            if (self->ext.main_61.merge != 0) {
                self->unk6 = 3;
                return;
            }
        } else if (self->ext.main_61.partner->ext.main_61.merge != 0) {
            self->ext.main_61.blink_timer = 0xFF;
            self->unk15 = self->ext.main_61.partner->unk15;
            self->unk6 = 4;
            return;
        }

        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = 0x3800;
        self->unk6 = 5;
        return;
    }

    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0x3800;
    self->unk6 = 2;
}

void split_mushroom_stun_fall(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->invincibility_timer = 0;
        set_animation(self, 2);
        self->unk5 = 7;
        self->unk6 = 0;
    }
}

void split_mushroom_stun_merge(struct MainObj* self)
{
    if (self->ext.main_61.split == 0) {
        self->ext.main_61.split_hits = 3;
        self->ext.main_61.merge = 0;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.21875);
        self->unk6 = 2;
    }
}

// split_mushroom_stun_rejoin
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_61_split_mushroom", func_80079824);
#else
void func_80079824(struct MainObj* arg0)
{
    u8 angle;

    if ((arg0->x_pos.i.hi - arg0->ext.main_61.partner->x_pos.i.hi >= 0 ? arg0->x_pos.i.hi - arg0->ext.main_61.partner->x_pos.i.hi : arg0->ext.main_61.partner->x_pos.i.hi - arg0->x_pos.i.hi) < 4
        && (arg0->y_pos.i.hi - arg0->ext.main_61.partner->y_pos.i.hi >= 0 ? arg0->y_pos.i.hi - arg0->ext.main_61.partner->y_pos.i.hi : arg0->ext.main_61.partner->y_pos.i.hi - arg0->y_pos.i.hi) < 4) {
        arg0->ext.main_61.partner->ext.main_61.split = 0;
        arg0->on_screen = 0;
        ZeroObjectState(OBJECT_HEADER(arg0));
        return;
    }
    angle = angle_to_object(OBJECT_HEADER(arg0), OBJECT_HEADER(arg0->ext.main_61.partner));
    set_velocity_from_angle(MOVING_OBJECT(arg0), angle);
    arg0->x_speed *= 4;
    arg0->y_speed *= 4;
    move_object(MOVING_OBJECT(arg0));
}
#endif

void split_mushroom_stun_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->invincibility_timer = 0;
        set_animation(self, 0);
        self->unk7C = 0x14;
        self->unk6 = 6;
    }
}

void split_mushroom_stun_split(struct MainObj* self)
{
    struct MainObj* parent;
    int one;

    if ((--self->unk7C << 16) == 0) {
        parent = self->ext.main_61.partner;
        if (parent->unk5 != 6) {
            if (self->x_pos.i.hi < background_objects[g_Player.bg_offset].x_pos.i.hi + 0xA0) {
                self->unk15 = PLAYER_FACING_RIGHT;
            } else {
                self->unk15 = 0;
            }
        } else {
            self->unk15 = (parent->unk15 ^ PLAYER_FACING_RIGHT);
        }
        one = 1;
        self->ext.main_61.split = one;
        set_animation(self, 2);
        self->ext.main_61.split_done = one;
        self->ext.main_61.combo_count = 0;
        self->unk5 = 6;
        self->unk6 = 7;
    }
}

void split_mushroom_spore_rain(struct MainObj* self)
{
    split_mushroom_spore_rain_funcs[self->unk6](self);
}

// split_mushroom_spore_rain_start
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_61_split_mushroom", func_80079A8C);
#else
void func_80079A8C(struct MainObj* arg0)
{
    s32 target;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;
    arg0->ext.main_61.stunned = 1;
    target = background_objects[g_Player.bg_offset].x_pos.val + 0xA00000 - arg0->x_pos.val;
    arg0->y_speed = 0x85C00;
    arg0->gravity = 0x3800;
    arg0->unk7C = 0x30;
    arg0->unk6 = 1;
    arg0->x_speed = target / 48;
    func_8001540C(2, SATURN_SOUND(0xA5, 0x28), arg0);
}
#endif

// split_mushroom_spore_rain_jump
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80079B50(struct MainObj* arg0)
{
    s32 row;
    s32 col;
    s32 x_step;
    s8 phase;
    u16 delay;
    u16 base_y;
    s16 base_x;
    s16 y;

    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    set_animation(arg0, 4);
    phase = 0;
    delay = 0x104;
    base_y = background_objects[g_Player.bg_offset].y_pos.i.hi - 0x20;
    base_x = background_objects[g_Player.bg_offset].x_pos.i.hi - 0x10;
    for (row = 0; row < 0xC0; row += 0x20) {
        y = base_y - row;
        for (col = 0, x_step = 0; col < 10; col++, x_step += 0x40) {
            if (!(col & 1)) {
                struct VisualObj* visual = find_free_visual_obj();

                if (visual == NULL)
                    continue;
                visual->active = 0x41;
                visual->id = 0x22;
                visual->unk2 = 0;
                visual->x_pos.i.hi = base_x + phase + x_step;
                visual->y_pos.i.hi = y;
                visual->unk15 = 0;
                visual->bg_offset = arg0->bg_offset;
                visual->animation_table = (void*)arg0->animation_table;
                visual->unk40 = arg0->unk40;
                visual->unk3C = (void*)arg0->sprite_frames;
                visual->unk42 = arg0->unk42 & 0x7FFF;
                visual->unk16 = row < 0x41 ? 0x13 : 0x12;
                visual->unk5C.value = phase;
                visual->unk50 = (struct PlayerObj*)arg0;
                visual->state = 0;
                visual->unk5C.fields.unk5E = delay;
                set_animation(visual, 0xE);
            } else {
                struct MiscObj* misc = find_free_misc_obj();

                if (misc == NULL)
                    continue;
                misc->active = 0x41;
                misc->id = 0x1E;
                misc->unk2 = 0;
                misc->x_pos.i.hi = base_x + phase + x_step;
                misc->y_pos.i.hi = y;
                misc->unk15 = 0;
                misc->bg_offset = arg0->bg_offset;
                misc->animation_table = (void*)arg0->animation_table;
                misc->unk40 = arg0->unk40;
                misc->unk3C = (void*)arg0->sprite_frames;
                misc->unk42 = arg0->unk42 & 0x7FFF;
                misc->unk16 = row < 0x41 ? 0x13 : 0x12;
                misc->ext.misc_30.unk54 = phase;
                misc->ext.misc_30.owner = arg0;
                misc->state = 0;
                misc->ext.misc_30.unk56 = delay;
                set_animation(misc, 0xE);
            }
        }
        phase ^= 0x20;
        delay += 0x20;
    }
    arg0->unk7C = 0xF0;
    arg0->unk6 = 2;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_61_split_mushroom", func_80079B50);
#endif

void split_mushroom_spore_rain_split(struct MainObj* self)
{
    s32 rnd;
    struct MainObj* clone;

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C != 0) {
        return;
    }
    func_8001540C(2, SATURN_SOUND(0xAA, 0x2D), self);
    self->ext.main_61.split = 1;
    rnd = get_random();
    clone = find_free_main_obj();
    if (clone != NULL) {
        clone->hp = 0x7F;
        clone->active = 0x41;
        clone->id = 0x3D;
        clone->unk2 = 1;
        clone->contact_damage = 5;
        clone->x_pos.val = self->x_pos.val;
        clone->y_pos.val = self->y_pos.val;
        clone->air_state = 0;
        clone->collision_data = self->collision_data;
        clone->hurt_box = self->hurt_box;
        clone->attack_box = self->attack_box;
        clone->terrain_box = self->terrain_box;
        clone->bg_offset = self->bg_offset;
        clone->animation_table = self->animation_table;
        clone->unk40 = self->unk40;
        clone->collision_flags = 0;
        clone->sprite_frames = self->sprite_frames;
        clone->unk42 = self->unk42 & 0x7FFF;
        clone->unk16 = self->unk16;
        clone->hp = 0x30;
        if (!(rnd & 1)) {
            clone->unk15 = PLAYER_FACING_RIGHT;
            clone->x_speed = FIXED(-2.75);
        } else {
            clone->unk15 = 0;
            clone->x_speed = FIXED(2.75);
        }
        clone->gravity = FIXED(0.21875);
        clone->x_accel = 0;
        clone->y_speed = 0;
        clone->state = 1;
        clone->unk5 = 3;
        clone->unk6 = 3;
        set_animation(clone, 3);
        clone->ext.main_61.partner = self;
        self->ext.main_61.partner = clone;
        clone->ext.main_61.split = 1;
        clone->ext.main_61.blink_timer = 0x7F;
    }
    set_animation(self, 3);
    if (!(rnd & 1)) {
        self->unk15 = 0;
        self->x_speed = FIXED(2.75);
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
        self->x_speed = FIXED(-2.75);
    }
    self->gravity = FIXED(0.21875);
    self->x_accel = 0;
    self->y_speed = 0;
    self->ext.main_61.stunned = 0;
    self->unk6 = 3;
}

void split_mushroom_spore_rain_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        set_animation(self, 0xA);
        func_8001540C(2, SATURN_SOUND(0xA6, 0x29), self);
        self->unk6 = 4;
    }
}

void split_mushroom_spore_rain_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->ext.main_61.blink_timer = 0;
        set_animation(self, 0);
        self->unk7C = 0x1E;
        self->unk6 = 5;
    }
}

void split_mushroom_spore_rain_finish(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->y_speed = 0;
        if (self->unk2 == 0) {
            self->unk7C = 6;
            self->unk5 = 4;
            self->unk6 = 0;
        } else {
            self->unk7C = 6;
            set_animation(self, 2);
            self->unk5 = 4;
            self->unk6 = 2;
        }
    }
}

void split_mushroom_walk(struct MainObj* self)
{
    split_mushroom_walk_funcs[self->unk6](self);
}

void split_mushroom_walk_start(struct MainObj* self)
{
    set_animation(self, 1);
    if (self->unk15 == 0) {
        self->x_speed = -split_mushroom_walk_speeds[self->ext.main_61.speed_level];
    } else {
        self->x_speed = split_mushroom_walk_speeds[self->ext.main_61.speed_level];
    }
    self->unk6 = 1;
}

void split_mushroom_walk_move(struct MainObj* self)
{
    u16 timer;
    u16 timer2;

    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (0 == self->unk15) {
        if ((self->collision_flags & 2) == 0) {
            goto done;
        }
        timer = self->unk7C;
        self->unk15 = PLAYER_FACING_RIGHT;
        timer--;
        self->unk7C = timer;
        if ((timer << 16) == 0) {
            goto destroy;
        }
        goto update;
    }

    if ((self->collision_flags & 1) == 0) {
        goto done;
    }
    timer2 = self->unk7C;
    self->unk15 = 0;
    timer2--;
    self->unk7C = timer2;
    if ((timer2 << 16) != 0) {
        goto update;
    }

destroy:
    func_8007B6BC(ANIMATED_OBJECT(self));
    goto done;

update:
    set_animation(self, 2);
    self->unk6 = 2;

done:;
}

// split_mushroom_walk_jump
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_61_split_mushroom", func_8007A2B4);
#else
void func_8007A2B4(struct MainObj* arg0)
{
    s16 speed = split_mushroom_hop_speeds[arg0->ext.main_61.speed_level];

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;
    if (arg0->unk15 == 0)
        arg0->x_speed = -0xE30000 / speed;
    else
        arg0->x_speed = 0xE30000 / speed;
    arg0->y_speed = (speed + 1) * 0x3800 / 2;
    arg0->gravity = 0x3800;
    move_with_gravity(ANIMATED_OBJECT(arg0));
    func_8001540C(2, SATURN_SOUND(0xA5, 0x28), arg0);
    arg0->unk6 = 3;
    arg0->unk7 = 0;
}
#endif

void split_mushroom_walk_fall(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if ((self->unk7 == 0) && (self->y_speed < 0)) {
        set_animation(self, 3);
        self->unk7 = 1;
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        set_animation(self, 0xA);
        func_8001540C(2, SATURN_SOUND(0xA6, 0x29), self);
        self->unk6 = 4;
    }
}

// split_mushroom_walk_turn
void func_8007A444(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 0) {
        return;
    }
    self->unk15 ^= PLAYER_FACING_RIGHT;
    if (--self->unk7C == 0) {
        func_8007B6BC(ANIMATED_OBJECT(self));
    } else {
        self->unk6 = 0;
    }
}

void split_mushroom_dash(struct MainObj* self)
{
    split_mushroom_dash_funcs[self->unk6](self);
}

// split_mushroom_dash_start
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_61_split_mushroom", func_8007A4EC);
#else
void func_8007A4EC(struct MainObj* arg0)
{
    struct MiscObj* misc;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    if (arg0->unk15 == 0)
        arg0->x_speed = (s32)0xFFF9B1C8;
    else
        arg0->x_speed = 0x64E38;
    if (arg0->unk7E == 3) {
        arg0->y_speed = 0;
        arg0->gravity = 0;
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 0x16;
            misc->unk2 = 8;
            misc->unk15 = arg0->unk15;
            misc->x_pos.i.hi = arg0->x_pos.i.hi;
            misc->y_pos.i.hi = arg0->y_pos.i.hi;
            misc->bg_offset = arg0->bg_offset;
            misc->animation_table = (void*)arg0->animation_table;
            misc->unk40 = arg0->unk40;
            misc->unk3C = (void*)arg0->sprite_frames;
            misc->unk42 = arg0->unk42 & 0x7FFF;
            misc->unk16 = VISUAL_SATURN_LAYER(5);
            misc->ext.misc_22.owner = arg0;
            misc->ext.misc_22.timer = 0x24;
            set_animation(misc, 0x18);
            misc->state = 0;
            misc->unk5 = 0;
            misc->unk6 = 1;
        }
    } else {
        arg0->y_speed = 0x5D31C;
        arg0->gravity = 0x3800;
    }
    arg0->unk6 = 1;
}
#endif

void split_mushroom_dash_bounce(struct MainObj* self)
{
    u16 resetValue;

    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));

    if (self->unk15 != 0) {
        goto state1;
    }
    if ((self->collision_flags & 2) == 0) {
        goto done;
    }

    func_8001540C(2, SATURN_SOUND(0xA8, 0x2B), self);
    split_mushroom_spawn_afterimage(self);
    if ((background_objects[g_Player.bg_offset].unk34 & 0x10) == 0) {
        start_screen_shake_x(0x10, 8, 2);
    }

    if (--self->unk7E == 0) {
        goto complete;
    }
    self->unk15 = PLAYER_FACING_RIGHT;
    resetValue = 0xA;
    goto reset;

state1:
    if ((self->collision_flags & 1) == 0) {
        goto done;
    }

    func_8001540C(2, SATURN_SOUND(0xA8, 0x2B), self);
    split_mushroom_spawn_afterimage(self);
    if ((background_objects[g_Player.bg_offset].unk34 & 0x10) == 0) {
        start_screen_shake_x(0x10, 8, 2);
    }

    if (--self->unk7E != 0) {
        goto state_off;
    }

complete:
    self->unk15 ^= PLAYER_FACING_RIGHT;
    set_animation(self, 3);
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0x3800;
    STOP_SOUND(2, 0xA7, 0x6);
    self->unk6 = 2;
    goto done;

state_off:
    resetValue = 0xA;
    self->unk15 = 0;
reset:
    self->unk7C = resetValue;
    self->unk6 = 0;
done:
    return;
}

void split_mushroom_dash_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        set_animation(self, 0xA);
        func_8001540C(2, SATURN_SOUND(0xA6, 0x29), self);
        self->unk6 = 3;
    }
}

void split_mushroom_dash_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->contact_damage = 5;
        set_animation(self, 0);
        self->unk7C = 0x28;
        self->unk6 = 4;
    }
}

void split_mushroom_dash_finish(struct MainObj* self)
{

    if (--self->unk7C != 0) {
        return;
    }
    if (self->unk2 == 0) {
        self->unk7C = 6;
        self->unk5 = 4;
        self->unk6 = 0;
        return;
    }
    self->unk7C = 6;
    set_animation(self, 2);
    self->unk5 = 4;
    self->unk6 = 2;
}

void split_mushroom_combo(struct MainObj* self)
{
    split_mushroom_combo_funcs[self->unk6](self);
}

// split_mushroom_combo_jump
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007A96C(struct MainObj* arg0)
{
    s32 offset;
    s32 target;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    offset = arg0->unk15 != 0 ? (s32)0xFEE80000 : (s32)0xFFD40000;
    target = background_objects[g_Player.bg_offset].x_pos.val - (arg0->x_pos.val + offset);
    if (arg0->ext.main_61.combo_count == 0) {
        arg0->x_speed = target / 48;
        arg0->y_speed = 0x55C00;
        func_8001540C(2, SATURN_SOUND(0xA5, 0x28), arg0);
    } else {
        arg0->x_speed = target / 36;
        func_8001540C(2, SATURN_SOUND(0xA5, 0x28), arg0);
        arg0->y_speed = 0x5D31C;
    }
    arg0->gravity = 0x3800;
    move_with_gravity(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 1;
    arg0->unk7 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_61_split_mushroom", func_8007A96C);
#endif

// split_mushroom_combo_dash
void func_8007AB1C(struct MainObj* arg0)
{
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_61.stunned != 0 && arg0->y_speed < 0)
        arg0->ext.main_61.stunned = 0;
    animate_object(ANIMATED_OBJECT(arg0));
    if ((s8)arg0->ext.main_61.combo_count == 0) {
        if (arg0->unk7 == 0) {
            set_animation(arg0, 3);
            arg0->unk7 = 1;
        }
        if (!(arg0->collision_flags & 8))
            return;
        if (arg0->ext.main_61.split_done == 0) {
            func_8001540C(2, SATURN_SOUND(0xA9, 0x2C), arg0);
            func_8001540C(2, SATURN_SOUND(0xA8, 0x2B), arg0);
        } else {
            func_8001540C(2, SATURN_SOUND(0xA6, 0x29), arg0);
            arg0->ext.main_61.split_done = 0;
        }
        arg0->contact_damage = 5;
        set_animation(arg0, 0);
        arg0->unk7C = 0x28;
        arg0->unk6 = 5;
        arg0->unk15 ^= PLAYER_FACING_RIGHT;
        return;
    }
    if (arg0->unk7E == 0) {
        if (ABS(arg0->x_pos.i.hi, g_Player.x_pos.i.hi) < 0x1C) {
            STOP_SOUND(2, 0xA7, 0x6);
            arg0->unk7C = 0x14;
            arg0->unk6 = 2;
        }
    }
    if (arg0->unk15 == 0) {
        if (!(arg0->collision_flags & 2))
            return;
        func_8001540C(2, 0xA8, arg0);
        split_mushroom_spawn_afterimage(arg0);
        if (!(background_objects[g_Player.bg_offset].unk34 & 0x10))
            start_screen_shake_x(0x10, 8, 2);
        arg0->unk15 = PLAYER_FACING_RIGHT;
        arg0->unk7E = 0;
        arg0->unk7C = 0xA;
        arg0->unk6 = 0;
    } else {
        if (!(arg0->collision_flags & 1))
            return;
        func_8001540C(2, 0xA8, arg0);
        split_mushroom_spawn_afterimage(arg0);
        if (!(background_objects[g_Player.bg_offset].unk34 & 0x10))
            start_screen_shake_x(0x10, 8, 2);
        arg0->unk7E = 0;
        arg0->unk15 = 0;
        arg0->unk7C = 0xA;
        arg0->unk6 = 0;
    }
}

void split_mushroom_combo_swing(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        func_8001540C(2, SATURN_SOUND(0xAC, 0x2F), self);
        set_animation(self, 8);
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.21875);
        self->unk6 = 3;
    }
}

// split_mushroom_combo_slam
void func_8007AE2C(struct MainObj* self)
{
    s32 i;

    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (!(self->collision_flags & 8)) {
        return;
    }
    func_8001540C(2, SATURN_SOUND(0xA8, 0x2B), self);
    if (!(background_objects[g_Player.bg_offset].unk34 & 1)) {
        start_screen_shake_y(0x10, 8, 2);
    }
    for (i = 0; i < 4; ++i) {
        struct ShotObj* shot = find_free_shot_obj();
        if (shot == NULL) {
            continue;
        }
        shot->active = 0x41;
        shot->id = 0x27;
        shot->unk2 = i;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->animation_table = (u32**)self->animation_table;
        shot->unk3C = (void*)self->sprite_frames;
        shot->unk15 = self->unk15;
        shot->bg_offset = self->bg_offset;
        shot->x_pos = self->x_pos;
        shot->y_pos = self->y_pos;
        shot->unk15 = self->unk15;
        if (self->unk2 == 0) {
            shot->unk7C = WEAPON_OBJECT(self);
        } else {
            shot->unk7C = self->ext.main_61.partner;
        }
        shot->state = 0;
    }
    set_animation(self, 9);
    self->unk7C = 0x30;
    self->unk6 = 4;
}

void split_mushroom_combo_repeat(struct MainObj* self)
{
    s8 temp_v0_2;

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        temp_v0_2 = self->ext.main_61.combo_count - 1;
        self->ext.main_61.combo_count = temp_v0_2;
        if (temp_v0_2 == 0) {
            set_animation(self, 0xF);
            self->unk6 = 6;
        } else {
            set_animation(self, 5);
            func_8001540C(2, SATURN_SOUND(0xA7, 0x2A), self);
            self->unk6 = 0;
            self->unk7C = 0x28;
            self->unk7E = 1;
        }
    }
}

void split_mushroom_combo_sync(struct MainObj* self)
{
    self->unk7C--;
    if (self->unk7C == 0) {
        self->unk7C = 1;
        self->unk5 = 5;
        self->unk6 = 4;
        return;
    }

    if ((self->unk2 != 0) && (self->ext.main_61.partner->unk5 == 6 && self->ext.main_61.partner->unk6 == 5)) {
        self->unk7C = 1;
        self->unk5 = 5;
        self->unk6 = 4;
        self->ext.main_61.partner->unk7C = 1;
        self->ext.main_61.partner->unk5 = 5;
        self->ext.main_61.partner->unk6 = 4;
    }
}

void split_mushroom_combo_end(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation((struct Unk19*)self, 2);
        self->unk6 = 7;
    }
}

void split_mushroom_combo_restart(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk7C = 1;
        self->unk6 = 0;
    }
}

void split_mushroom_wall_jump(struct MainObj* self)
{
    split_mushroom_wall_jump_funcs[self->unk6](self);
}

// split_mushroom_wall_jump_start
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007B1BC(struct MainObj* arg0)
{
    s32 offset;
    s32 target;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 0)
        return;
    arg0->terrain_box = &split_mushroom_wall_terrain_box;
    if (arg0->x_pos.i.hi < background_objects[g_Player.bg_offset].x_pos.i.hi + 0xA0)
        arg0->unk15 = PLAYER_FACING_RIGHT;
    else
        arg0->unk15 = 0;
    offset = arg0->unk15 != 0 ? (s32)0xFEE80000 : (s32)0xFFD40000;
    target = background_objects[g_Player.bg_offset].x_pos.val - (arg0->x_pos.val + offset);
    arg0->x_speed = target / 48;
    arg0->y_speed = 0x706AA;
    func_8001540C(2, SATURN_SOUND(0xA5, 0x28), arg0);
    arg0->gravity = 0x3800;
    move_with_gravity(ANIMATED_OBJECT(arg0));
    arg0->unk6 = 1;
    arg0->unk7 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_61_split_mushroom", func_8007B1BC);
#endif

void split_mushroom_wall_jump_air(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if ((self->unk7 == 0) && (self->y_speed < 0)) {
        self->unk7 = 1;
        set_animation(self, 3);
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk15 == 0) {
        if ((self->collision_flags & 2) == 0) {
            return;
        }
    } else if ((self->collision_flags & 1) == 0) {
        return;
    }
    self->ext.main_61.stunned = 0;
    set_animation(self, 6);
    self->unk7C = 0x28;
    self->unk6 = 2;
}

void split_mushroom_wall_jump_cling(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->terrain_box = &split_mushroom_terrain_box;
        set_animation(self, 7);
        self->unk7C = 0x28;
        self->unk6 = 3;
        self->unk7E = 6;
    }
}

// split_mushroom_wall_jump_shoot
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_61_split_mushroom", func_8007B418);
#else
void func_8007B418(struct MainObj* arg0)
{
    struct ShotObj* shot;
    s16 count;

    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    count = arg0->unk7E;
    arg0->unk7E = count - 1;
    if (count == 0) {
        set_animation(arg0, 0x17);
        arg0->unk6 = 4;
        return;
    }
    func_8001540C(2, SATURN_SOUND(0xAA, 0x2D), arg0);
    arg0->unk7C = 0x28;
    shot = find_free_shot_obj();
    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 0x27;
    shot->unk2 = 0;
    shot->unk40 = arg0->unk40;
    if (engine_obj.stage == 3)
        shot->unk42 = 0x78CC;
    else
        shot->unk42 = 0x788C;
    shot->unk68 = arg0->terrain_box;
    shot->unk54 = arg0->hurt_box;
    shot->unk50.data = arg0->attack_box;
    shot->animation_table = (void*)arg0->animation_table;
    shot->unk3C = (void*)arg0->sprite_frames;
    shot->unk15 = arg0->unk15 ^ PLAYER_FACING_RIGHT;
    shot->bg_offset = arg0->bg_offset;
    shot->x_pos.val = arg0->x_pos.val;
    shot->y_pos.val = arg0->y_pos.val;
    if (arg0->unk2 == 0)
        shot->unk7C = (struct WeaponObj*)arg0;
    else
        shot->unk7C = (struct WeaponObj*)arg0->ext.main_61.partner;
    shot->state = 4;
    shot->unk6 = 0;
}
#endif

void split_mushroom_wall_jump_turn(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk15 ^= PLAYER_FACING_RIGHT;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.21875);
        set_animation(self, 3);
        self->unk6 = 5;
    }
}

void split_mushroom_wall_jump_land(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        func_8001540C(2, SATURN_SOUND(0xA6, 0x29), self);
        self->unk6 = 6;
    }
}

void split_mushroom_wall_jump_finish(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 2);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void split_mushroom_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
}

// split_mushroom_turn_around
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_61_split_mushroom", func_8007B6BC);
#else
void func_8007B6BC(struct AnimatedObj* obj)
{
    struct MainObj* arg0 = (struct MainObj*)obj;
    s16 hp;

    if (arg0->unk2 == 0)
        hp = arg0->hp;
    else
        hp = arg0->ext.main_61.partner->hp;
    if (hp > 0x18) {
        set_animation(arg0, 5);
        func_8001540C(2, SATURN_SOUND(0xA7, 0x2A), arg0);
        arg0->unk7C = 0x28;
        arg0->unk7E = 3;
        arg0->contact_damage = 6;
        arg0->unk5 = 5;
        arg0->unk6 = 0;
    } else {
        set_animation(arg0, 5);
        func_8001540C(2, SATURN_SOUND(0xA7, 0x2A), arg0);
        if (arg0->unk2 == 0)
            arg0->unk7C = 0x28;
        else
            arg0->unk7C = 0x50;
        arg0->unk7E = 1;
        arg0->ext.main_61.combo_count = 2;
        arg0->contact_damage = 9;
        arg0->unk5 = 6;
        arg0->unk6 = 0;
    }
}
#endif

void split_mushroom_load_palette(void)
{
    s32 i;
    u16* source;
    u16* destination;

    source = SP_PALETTE_BANK[53];
    if (engine_obj.stage == 3) {
        destination = SP_PALETTES[60];
    } else {
        destination = SP_PALETTES[44];
    }
    i = 0;
    do {
        *destination++ = *source++;
        i++;
    } while (i < 0x40);
    need_palette_load |= 1;
}

void split_mushroom_spawn_afterimage(struct MainObj* self)
{
    struct MainObj* source;
    struct MiscObj* temp_v0;

    source = self;
    temp_v0 = find_free_misc_obj();
    if (temp_v0 != 0) {
        temp_v0->active = 0x41;
        temp_v0->id = 0x16;
        temp_v0->unk2 = 8;
        temp_v0->unk15 = source->unk15;
        temp_v0->x_pos.i.hi = source->x_pos.i.hi;
        temp_v0->y_pos.i.hi = source->y_pos.i.hi;
        temp_v0->bg_offset = (u8)source->bg_offset;
        temp_v0->animation_table = (u32**)source->animation_table;
        temp_v0->unk40 = source->unk40;
        temp_v0->unk3C = (void*)source->sprite_frames;
        temp_v0->unk42 = source->unk42 & 0x7FFF;
        temp_v0->unk16 = VISUAL_SATURN_LAYER(5);
        temp_v0->ext.misc_22.owner = source;
        temp_v0->ext.misc_22.timer = 0xA;
        set_animation(temp_v0, 0x19);
        temp_v0->state = 0;
        temp_v0->unk5 = 0;
        temp_v0->unk6 = 1;
    }
}

struct Unk_unk68 split_mushroom_attack_box = { -11, -16, 20, 35 };

struct Unk_unk68 split_mushroom_hurt_box = { -16, -17, 30, 37 };

struct Unk_unk68 split_mushroom_terrain_box = { 0, 0, 8, 23 };

struct Unk_unk68 split_mushroom_wall_terrain_box = { -16, 0, 8, 23 };

s16 split_mushroom_hop_speeds[4] = {
    (s16)0x0040,
    (s16)0x003A,
    (s16)0x0034,
    (s16)0x0000,
};

s32 split_mushroom_walk_speeds[3] = {
    FIXED(3),
    FIXED(4.5),
    FIXED(6),
};

struct Unk_unk68 split_mushroom_anim_0[4] = {
    { 13, 0, 1, 0 },
    { 11, 0, 1, 1 },
    { 13, 0, 1, 2 },
    { 13, 1, -3, 1 },
};

struct Unk_unk68 split_mushroom_anim_1[8] = {
    { 3, 0, 1, 3 },
    { 5, 0, 1, 4 },
    { 4, 0, 1, 5 },
    { 3, 0, 1, 6 },
    { 3, 0, 1, 7 },
    { 5, 0, 1, 8 },
    { 4, 0, 1, 9 },
    { 3, 1, -7, 10 },
};

union AnimationStep split_mushroom_anim_2[] = {
    { 2, 0, 1, 0x00 },
    { 3, 0, 1, 0x0B },
    { 2, 0, 1, 0x0C },
    { 1, 1, 0, 0x0D },
};

union AnimationStep split_mushroom_anim_3[] = {
    { 1, 1, 0, 0x0E },
};

struct Unk_unk68 split_mushroom_anim_4[9] = {
    { 3, 0, 1, 15 },
    { 3, 0, 1, 16 },
    { 3, 0, 1, 17 },
    { 3, 0, 1, 18 },
    { 3, 0, 1, 19 },
    { 3, 0, 1, 20 },
    { 3, 0, 1, 21 },
    { 3, 0, 1, 22 },
    { 3, 1, -7, 23 },
};

struct Unk_unk68 split_mushroom_anim_5[8] = {
    { 2, 0, 1, 24 },
    { 2, 0, 1, 25 },
    { 2, 0, 1, 26 },
    { 2, 0, 1, 27 },
    { 2, 0, 1, 28 },
    { 2, 0, 1, 29 },
    { 2, 0, 1, 30 },
    { 2, 0, -7, 31 },
};

union AnimationStep split_mushroom_anim_6[] = {
    { 3, 0, 1, 0x20 },
    { 1, 1, 0, 0x21 },
};

union AnimationStep split_mushroom_anim_7[] = {
    { 4, 0, 1, 0x22 },
    { 3, 0, 1, 0x6E },
    { 3, 0, 1, 0x21 },
    { 24, 0, 1, 0x75 },
    { 27, 0, 1, 0x76 },
    { 1, 1, 0, 0x76 },
};

union AnimationStep split_mushroom_anim_23[] = {
    { 3, 0, 1, 0x73 },
    { 2, 0, 1, 0x74 },
    { 9, 0, 1, 0x73 },
    { 1, 1, 0, 0x73 },
};

union AnimationStep split_mushroom_anim_8[] = {
    { 1, 1, 0, 0x23 },
};

union AnimationStep split_mushroom_anim_9[] = {
    { 2, 0, 1, 0x24 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x28 },
    { 9, 0, 1, 0x29 },
    { 1, 1, 0, 0x29 },
};

union AnimationStep split_mushroom_anim_10[] = {
    { 3, 0, 1, 0x2A },
    { 3, 0, 1, 0x2B },
    { 1, 1, 0, 0x2B },
};

union AnimationStep split_mushroom_anim_11[] = {
    { 3, 0, 1, 0x2C },
    { 3, 0, 1, 0x2D },
    { 3, 0, 1, 0x2E },
    { 3, 0, 1, 0x2F },
    { 8, 1, 1, 0x30 },
    { 8, 1, 1, 0x31 },
    { 8, 1, 1, 0x32 },
    { 8, 1, -3, 0x31 },
};

union AnimationStep split_mushroom_anim_13[] = {
    { 8, 1, 1, 0x33 },
    { 8, 1, 1, 0x34 },
    { 8, 1, 1, 0x35 },
    { 8, 1, 1, 0x36 },
    { 7, 0, 1, 0x37 },
    { 1, 2, 0, 0x37 },
};

struct Unk_unk68 split_mushroom_anim_14[4] = {
    { 4, 0, 1, 56 },
    { 4, 0, 1, 57 },
    { 4, 0, 1, 58 },
    { 4, 1, -3, 59 },
};

union AnimationStep split_mushroom_anim_15[] = {
    { 3, 0, 1, 0x10 },
    { 4, 0, 1, 0x0F },
    { 6, 0, 1, 0x3C },
    { 2, 0, 1, 0x2A },
    { 3, 0, 1, 0x2B },
    { 1, 1, 0, 0x00 },
};

union AnimationStep split_mushroom_anim_16[] = {
    { 2, 0, 1, 0x3D },
    { 2, 0, 1, 0x3E },
    { 2, 0, 1, 0x3F },
    { 2, 0, 1, 0x40 },
    { 2, 0, 1, 0x41 },
    { 2, 0, 1, 0x42 },
    { 2, 0, 1, 0x43 },
    { 2, 0, 1, 0x44 },
    { 2, 0, 1, 0x45 },
    { 2, 0, 1, 0x46 },
    { 2, 0, 1, 0x47 },
    { 2, 0, 1, 0x48 },
    { 2, 0, 1, 0x49 },
    { 2, 0, 1, 0x4A },
    { 2, 0, 1, 0x4B },
    { 1, 0, 1, 0x4C },
    { 1, 1, 0, 0x4C },
};

union AnimationStep split_mushroom_anim_17[] = {
    { 20, 0, 1, 0x00 },
    { 24, 0, 1, 0x4D },
    { 8, 0, 1, 0x4E },
    { 2, 0, 1, 0x4D },
    { 1, 1, 1, 0x4F },
    { 31, 0, 1, 0x4F },
    { 1, 0, 1, 0x50 },
    { 1, 2, 0, 0x50 },
};

union AnimationStep split_mushroom_anim_18[] = {
    { 2, 0, 1, 0x51 },
    { 2, 1, 1, 0x52 },
    { 3, 1, 1, 0x53 },
    { 3, 1, 1, 0x54 },
    { 3, 1, 1, 0x55 },
    { 3, 1, 1, 0x56 },
    { 4, 1, 1, 0x57 },
    { 4, 1, 1, 0x58 },
    { 4, 0, 1, 0x59 },
    { 3, 0, 1, 0x5A },
    { 1, 2, 0, 0x5A },
};

union AnimationStep split_mushroom_anim_19[] = {
    { 2, 0, 1, 0x5B },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x5D },
    { 2, 0, 1, 0x5E },
    { 2, 0, 1, 0x5F },
    { 2, 0, 1, 0x60 },
    { 2, 0, 1, 0x5B },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x5D },
    { 2, 0, 1, 0x5E },
    { 2, 0, 1, 0x5F },
    { 2, 0, 1, 0x60 },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x62 },
    { 2, 0, 1, 0x63 },
    { 2, 0, 1, 0x64 },
    { 2, 0, 1, 0x65 },
    { 2, 0, 1, 0x66 },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x62 },
    { 2, 0, 1, 0x63 },
    { 2, 0, 1, 0x64 },
    { 2, 0, 1, 0x65 },
    { 2, 0, 1, 0x66 },
    { 2, 0, 1, 0x67 },
    { 2, 0, 1, 0x68 },
    { 2, 0, 1, 0x69 },
    { 2, 0, 1, 0x6A },
    { 2, 0, 1, 0x6B },
    { 2, 0, 1, 0x6C },
    { 2, 0, 1, 0x67 },
    { 2, 0, 1, 0x68 },
    { 2, 0, 1, 0x69 },
    { 2, 0, 1, 0x6A },
    { 2, 0, 1, 0x6B },
    { 2, 0, 1, 0x6C },
    { 5, 0, 1, 0x6D },
    { 1, 1, 0, 0x6D },
};

struct Unk_unk68 split_mushroom_anim_20[4] = {
    { 4, 0, 1, 111 },
    { 4, 0, 1, 112 },
    { 4, 0, 1, 113 },
    { 4, 0, -3, 114 },
};

union AnimationStep split_mushroom_anim_21[] = {
    { 1, 1, 0, 0x77 },
};

struct Unk_unk68 split_mushroom_anim_22[9] = {
    { 2, 0, 1, 15 },
    { 2, 0, 1, 16 },
    { 2, 0, 1, 17 },
    { 2, 0, 1, 18 },
    { 2, 0, 1, 19 },
    { 2, 0, 1, 20 },
    { 2, 0, 1, 21 },
    { 2, 0, 1, 22 },
    { 2, 1, -7, 23 },
};

struct Unk_unk68 split_mushroom_anim_24[5] = {
    { 1, 0, 1, 120 },
    { 1, 0, 1, 121 },
    { 1, 0, 1, 122 },
    { 1, 0, 1, 123 },
    { 1, 0, -4, 124 },
};

union AnimationStep split_mushroom_anim_25[] = {
    { 1, 0, 1, 0x7D },
    { 1, 0, 1, 0x7E },
    { 1, 0, 1, 0x7F },
    { 1, 0, 1, 0x80 },
    { 1, 0, -4, 0x81 },
};

void* split_mushroom_animations[26] = {
    split_mushroom_anim_0,
    split_mushroom_anim_1,
    split_mushroom_anim_2,
    split_mushroom_anim_3,
    split_mushroom_anim_4,
    split_mushroom_anim_5,
    split_mushroom_anim_6,
    split_mushroom_anim_7,
    split_mushroom_anim_8,
    split_mushroom_anim_9,
    split_mushroom_anim_10,
    split_mushroom_anim_11,
    &split_mushroom_anim_11[4],
    split_mushroom_anim_13,
    split_mushroom_anim_14,
    split_mushroom_anim_15,
    split_mushroom_anim_16,
    split_mushroom_anim_17,
    split_mushroom_anim_18,
    split_mushroom_anim_19,
    split_mushroom_anim_20,
    split_mushroom_anim_21,
    split_mushroom_anim_22,
    split_mushroom_anim_23,
    split_mushroom_anim_24,
    split_mushroom_anim_25,
};

void (*split_mushroom_state_funcs[3])() = {
    func_8007877C,
    func_800788E4,
    split_mushroom_death,
};

void (*split_mushroom_step_funcs[8])() = {
    enemy_hit_reaction,
    split_mushroom_intro,
    split_mushroom_stun,
    split_mushroom_spore_rain,
    split_mushroom_walk,
    split_mushroom_dash,
    split_mushroom_combo,
    split_mushroom_wall_jump,
};

void (*split_mushroom_death_funcs[3])(struct MainObj*) = {
    split_mushroom_death_start,
    split_mushroom_death_explode,
    split_mushroom_death_finish,
};

void (*split_mushroom_intro_funcs[7])() = {
    split_mushroom_intro_wait_player,
    split_mushroom_intro_drop,
    split_mushroom_intro_bounce,
    split_mushroom_intro_land,
    func_800793AC,
    split_mushroom_intro_start_health_bar,
    split_mushroom_intro_fill_health,
};

void (*split_mushroom_stun_funcs[7])() = {
    split_mushroom_stun_start,
    split_mushroom_stun_wait,
    split_mushroom_stun_fall,
    split_mushroom_stun_merge,
    func_80079824,
    split_mushroom_stun_land,
    split_mushroom_stun_split,
};

void (*split_mushroom_spore_rain_funcs[6])() = {
    func_80079A8C,
    func_80079B50,
    split_mushroom_spore_rain_split,
    split_mushroom_spore_rain_land,
    split_mushroom_spore_rain_recover,
    split_mushroom_spore_rain_finish,
};

void (*split_mushroom_walk_funcs[5])() = {
    split_mushroom_walk_start,
    split_mushroom_walk_move,
    func_8007A2B4,
    split_mushroom_walk_fall,
    func_8007A444,
};

void (*split_mushroom_dash_funcs[5])() = {
    func_8007A4EC,
    split_mushroom_dash_bounce,
    split_mushroom_dash_land,
    split_mushroom_dash_recover,
    split_mushroom_dash_finish,
};

void (*split_mushroom_combo_funcs[8])() = {
    func_8007A96C,
    func_8007AB1C,
    split_mushroom_combo_swing,
    func_8007AE2C,
    split_mushroom_combo_repeat,
    split_mushroom_combo_sync,
    split_mushroom_combo_end,
    split_mushroom_combo_restart,
};

void (*split_mushroom_wall_jump_funcs[7])() = {
    func_8007B1BC,
    split_mushroom_wall_jump_air,
    split_mushroom_wall_jump_cling,
    func_8007B418,
    split_mushroom_wall_jump_turn,
    split_mushroom_wall_jump_land,
    split_mushroom_wall_jump_finish,
};
