// MainObj, main_object_update_funcs[43]
// 800631C8..80065930
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_43_web_spider.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/player_common.h"
#include "main/128C4.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/misc/misc_15_vent.h"
#include "main/misc/misc_16_vent_puff.h"

void func_80065168(struct MainObj* arg0, s16 x, s16 y);
void web_spider_check_big_web(struct MainObj* self);

void func_80065168(struct MainObj* arg0, s16 x, s16 y);
void web_spider_check_big_web(struct MainObj* self);

extern u8 web_spider_move_timers[];
extern u8 web_spider_attack_cooldowns[4];
extern const u8* web_spider_swing_animations[];

extern struct Unk_unk68 D_800FF5B0;

extern u8 web_spider_swing_sets[];

extern struct Unk_unk68 web_spider_attack_box;
extern struct Unk_unk68 web_spider_hurt_box;

// web_spider_state_funcs
void web_spider_intro(struct MainObj*);

void web_spider_death(struct MainObj*);

void spiderling_run(struct MainObj*);
void spiderling_despawn(struct MainObj* arg0);

void web_spider_intro_setup(struct MainObj*);

void web_spider_intro_spawn_thread(struct MainObj*);
void web_spider_intro_wait(struct MainObj*);
void web_spider_intro_descend(struct MainObj*);
void web_spider_intro_pose(struct MainObj*);
void web_spider_intro_start_health_bar(struct MainObj*);
void web_spider_intro_fill_health(struct MainObj*);
void web_spider_intro_climb(struct MainObj*);

// web_spider_step_funcs
void web_spider_fall(struct MainObj* arg0);
void web_spider_drop(struct MainObj* arg0);
void web_spider_shoot(struct MainObj* arg0);
void web_spider_swing(struct MainObj* arg0);
void web_spider_attack(struct MainObj* arg0);
void web_spider_big_web(struct MainObj* arg0);

// web_spider_shoot_funcs
void web_spider_shoot_start(struct MainObj*);
void func_8006E0B0_demo(struct MainObj*);
void web_spider_shoot_fire(struct AnimatedObj*);

// web_spider_swing_funcs
void web_spider_swing_start(struct MainObj*);

void web_spider_swing_wait(struct MainObj*);

// web_spider_fall_funcs
extern void (*web_spider_fall_funcs[])(struct MainObj*);
void web_spider_fall_start(struct MainObj*);
void web_spider_fall_slow(struct MainObj*);
void web_spider_fall_land(struct MainObj*);
void web_spider_fall_crash(struct MainObj*);

void web_spider_death_start(struct MainObj*);

// spiderling_step_funcs
extern void (*spiderling_step_funcs[])(struct MainObj*);
void spiderling_fall(struct MainObj* arg0);

void spiderling_leave(struct MainObj* arg0);

extern void (*web_spider_state_funcs[])(struct MainObj*);
extern void (*spiderling_state_funcs[])(struct MainObj*);
extern void (*web_spider_intro_funcs[])(struct MainObj*);
extern void (*web_spider_drop_funcs[])(struct MainObj*);
extern void (*web_spider_shoot_funcs[])(struct MainObj*);
extern void (*web_spider_swing_funcs[])(struct MainObj*);
extern void (*web_spider_big_web_funcs[])(struct MainObj*);
extern void (*web_spider_death_funcs[])(struct MainObj*);

void func_800643B0(struct MainObj* arg0);
void web_spider_attack_web(struct MainObj* arg0);

void web_spider_update(struct MainObj* self)
{
    if (self->unk2 == 0) {
        web_spider_state_funcs[self->state](self);
    } else {
        spiderling_state_funcs[self->state](self);
    }
}

void web_spider_intro(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    web_spider_intro_funcs[self->unk5](self);
    if (self->unk5 >= 2) {
        is_on_screen(BASE_OBJECT(self));
    }
}

void web_spider_intro_warning(struct MainObj* self)
{
    struct EffectObj* effect;

    if (g_Player.capsule_state == 0) {
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            self->ext.main_43.effect = effect;
        }
        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
#ifdef VERSION_DEMO
        background_objects[0].unk26 = 0x1210;
        background_objects[0].unk24 = 0x1230;
        background_objects[0].unk2A = 0x500;
        web_spider_arena_x = 0x500;
#else
        web_spider_arena_x = background_objects[0].unk26;
        web_spider_arena_y = background_objects[0].unk2A;
#endif
        self->unk5 = 1;
        self->unk6 = 0;
        self->unk7 = 0;
    }
}

void web_spider_intro_setup(struct MainObj* self)
{
    s32* archive;
    s32 offset;

    if (self->ext.main_43.effect->active == 0) {
        self->unk5 = 2;
        self->hurt_box = &web_spider_hurt_box;
        self->attack_box = &web_spider_attack_box;
        self->terrain_box = NULL;
        self->collision_data = D_801075F4;
        self->bg_offset = g_Player.bg_offset;
#ifdef VERSION_DEMO
        self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0xB0);
#else
        if (engine_obj.stage != 0xC) {
            self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0xB0);
        } else {
            self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0x160);
            archive = SP_MENU_FRAMES;
            offset = archive[4];
            self->sprite_frames = (u8*)archive + offset;
            self->unk42 = OBJECT_CLUT(0x7888);
        }
#endif
        self->animation_table = (const u8* const*)web_spider_animations;
        self->unk16 = VISUAL_SATURN_LAYER(4);
        self->hp = 0;
        self->contact_damage = DEMO_ALT(6, 5);
        self->invincibility_timer = -0x80;
        self->unk62 = 0;
        self->unk63 = 2;
        self->unk7C = 7;
        self->ext.main_43.flash_timer = 0;
        self->ext.main_43.shot = NULL;
        self->ext.main_43.hurt_collision = 0;
        self->ext.main_43.big_web_done = 0;
        engine_obj.enable_boss = DEMO_ALT(0, 1);
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = self;
    }
}

// web_spider_intro_enter

extern void (*web_spider_step_funcs[7])();
extern RECT* web_spider_swing_paths[6];
extern u8 D_800FF724[16];
extern struct FixedPointPosition spiderling_velocities[8];
extern struct Unk_unk68 D_800FF5B4;
extern struct Unk_unk68 D_800FF5B8;
extern struct Unk_unk68 D_800FF5BC;
#if defined(MMX4_PC) || defined(MMX4_SATURN)
static u8 main43_column(s16 index);
void func_8006346C(struct MainObj* arg0);
void func_8006398C(struct MainObj* arg0);
void func_80063B20(struct MainObj* arg0);
void func_80065168(struct MainObj* arg0, s16 x, s16 y);
void func_80064154(struct MainObj* arg0);
void func_800646EC(struct MainObj* arg0);
void func_80065574(struct MainObj* arg0);
void web_spider_check_big_web(struct MainObj* arg0);
extern u16 web_spider_arena_y;
u8 angle_from_delta(s32 arg0, s32 arg1);
static u8 main43_column(s16 index)
{
#ifdef MMX4_SATURN
    static const u8 following_pointer_byte = 0x00;
#else
    static const u8 following_pointer_byte = 0x6C;
#endif

    return index < 16 ? D_800FF724[index] : following_pointer_byte;
}
#endif

void func_8006346C(struct MainObj* arg0)
{
    s32 value;
    u16 arena_x;

    switch (arg0->unk6) {
    case 0:
#if defined(MMX4_PC) || defined(MMX4_SATURN)
        value = main43_column(arg0->unk7C);
#else
        value = D_800FF724[arg0->unk7C];
#endif
        arg0->unk7C = *(volatile u16*)&arg0->unk7C + 1;
        arg0->unk7E = 0x10;
        arena_x = DEMO_ALT(web_spider_arena_x, 0x1210);
        arg0->x_pos.i.hi = arena_x + 0x30 + (value << 5);
        arg0->unk6 = 1;
        vent_spawn_puffs((struct MiscObj*)arg0, 2);
        return;
    case 1:
        if (--arg0->unk7E == 0) {
            if (arg0->unk7C >= 0x11) {
                arg0->unk5 = 3;
                arg0->unk6 = 0;
                arg0->unk7C = 0;
                arg0->x_pos.i.hi = DEMO_ALT(web_spider_arena_x, 0x1210) + 0xF0;
            } else {
                arg0->unk6 = 0;
            }
        }
        return;
    case 2:
        arg0->x_pos.i.hi = DEMO_ALT(web_spider_arena_x, 0x1210) + 0x30 + (arg0->unk7C * 32);
        arg0->unk7C++;
        arg0->unk7E = 0x14;
        arg0->unk6 = 3;
        vent_spawn_puffs((struct MiscObj*)arg0, 2);
        return;
    case 3:
        if (--arg0->unk7E == 0) {
            if (arg0->unk7C >= 7) {
                arg0->unk5 = 3;
                arg0->unk6 = 0;
                arg0->unk7C = 0;
            } else {
                arg0->unk6 = 2;
            }
        }
        return;
    default:
        return;
    }
}

void web_spider_intro_spawn_thread(struct MainObj* self)
{
    vent_spawn_mixed_puffs(self, 8);
    self->unk7C = 0x40;
    self->unk5 = 4;
    self->ext.main_43.shot = web_spider_spawn_thread(self, 0);
}

void web_spider_intro_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 5;
        self->x_speed = 0;
        self->x_accel = 0;
        self->y_speed = FIXED(-8);
        self->gravity = 0;
        set_animation(self, 0);
    }
}

void web_spider_intro_descend(struct MainObj* self)
{
    if (self->unk6 == 0) {
        if (self->y_pos.i.hi - background_objects[self->bg_offset].y_pos.i.hi >= 0x88) {
            self->unk6 = 1;
            self->unk7C = 0x1E;
            self->y_speed = FIXED(1);
            set_animation(self, 1);
        } else {
            move_with_gravity(ANIMATED_OBJECT(self));
        }
        animate_object(ANIMATED_OBJECT(self));
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
        self->unk7C--;
        if (self->unk7C == 0) {
            self->y_speed = 0;
            self->gravity = 0;
            self->unk5 = 6;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk7C = 2;
        } else if (self->unk7C == 0xF) {
            self->y_speed = FIXED(-1);
        }
        animate_object(ANIMATED_OBJECT(self));
    }
}

#ifndef VERSION_DEMO
void web_spider_intro_pose(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->unk5 = 7;
        if (engine_obj.stage == 1) {
#ifdef MMX4_PC
            func_8002217C(8, 0xFF, (u8)engine_obj.character_state.bytes[8]);
#else
            func_8002217C(8, 0xFF, engine_obj.character_state.bytes[8]);
#endif
            engine_obj.character_state.bytes[8] = 1;
        }
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void web_spider_intro_start_health_bar(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        self->unk5 = 8;
        engine_obj.enable_boss = 1;
        play_boss_voice(0);
    }
}

#endif

#ifdef VERSION_DEMO
void web_spider_intro_fill_health(struct MainObj* self)
{
    s16 timer;

    if (self->animation_step.fields.relative_step == 0) {
        if (self->hp < 0x30) {
            timer = --self->unk7C;
            if (timer == 0) {
                func_8001540C(0, 0xF, 0);
                self->unk7C = 2;
            }
            self->hp++;
            return;
        }
        self->unk5 = 7;
        self->y_speed = FIXED(3.5);
        player_end_script_action();
        set_animation(self, 0x1F);
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}
#else
void web_spider_intro_fill_health(struct MainObj* self)
{
    s16 timer;

    animate_object(ANIMATED_OBJECT(self));
    if ((update_boss_music_delay() == 0) && (self->animation_step.fields.relative_step == 0)) {
        if (self->hp < 0x30) {
            timer = --self->unk7C;
            if (timer == 0) {
                func_8001540C(0, SATURN_SOUND(0xE, 0x14), 0);
                self->unk7C = 2;
            }
            self->hp++;
            return;
        }
        self->unk5 = 9;
        self->y_speed = FIXED(3.5);
        player_end_script_action();
        set_animation(self, 0x1F);
    }
}
#endif

void web_spider_intro_climb(struct MainObj* self)
{
    if (self->on_screen == 0) {
        self->state = 1;
        self->unk5 = 2;
        self->invincibility_timer = 0;
        return;
    }
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        func_8001540C(2, SATURN_SOUND(0x70, 0x23), self);
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

// web_spider_main
void func_8006398C(struct MainObj* arg0)
{
    s32 result;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    web_spider_check_big_web(arg0);
    ((void (*)(struct MainObj*))web_spider_step_funcs[arg0->unk5])(arg0);
#ifdef VERSION_DEMO
    func_8002D9BC(arg0);
#endif
    result = -1;
    if (arg0->hp > 0)
        result = func_8002DD04(arg0);
    if (arg0->ext.main_43.flash_timer != 0) {
        if ((arg0->ext.main_43.flash_timer & 1) == 0)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (--arg0->ext.main_43.flash_timer == 0) {
            arg0->collision_data = D_801075F4;
            arg0->ext.main_43.hurt_collision = 0;
        }
    } else if (result < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
#ifndef VERSION_DEMO
        g_Player.spike_immune = 1;
#endif
    } else if (result != 0 && result != 0x7F) {
        arg0->collision_data = D_801060F0;
        arg0->ext.main_43.flash_timer = 0x40;
        web_spider_spawn_web_piece((struct VisualObj*)arg0, 0);
        arg0->ext.main_43.hurt_collision = 1;
    }
#ifndef VERSION_DEMO
    func_8002D9BC(arg0);
#endif
    is_on_screen(BASE_OBJECT(arg0));
}

void web_spider_drop(struct MainObj* self)
{
    web_spider_drop_funcs[self->unk6](self);
}

// web_spider_drop_start
void func_80063B20(struct MainObj* arg0)
{
    s32 threshold;

    switch (arg0->unk7) {
    case 0:
        arg0->unk7 = 1;
#ifdef VERSION_DEMO
        arg0->unk7C = 0x40;
        if ((u32)(get_random() & 7) < 5)
            arg0->ext.main_43.unk94 = (g_Player.x_pos.i.hi - 0x1210) / 40;
        else
            arg0->ext.main_43.unk94 = get_random() & 7;
        arg0->x_pos.i.hi = 0x1210 + 0x30 + (arg0->ext.main_43.unk94 << 5);
#else
        if (g_Player.stun_timer != 0)
            arg0->unk7C = 0x10;
        else
            arg0->unk7C = 0x40;
        if (g_Player.stun_timer == 0) {
            if ((u32)(get_random() & 7) < 5)
                arg0->ext.main_43.unk94 = ((g_Player.x_pos.i.hi - (s16)web_spider_arena_x) / 40 + 4) & 7;
            else
                arg0->ext.main_43.unk94 = get_random() & 7;
        } else {
            arg0->ext.main_43.unk94 = (g_Player.x_pos.i.hi - (s16)web_spider_arena_x) / 40;
        }
        arg0->x_pos.i.hi = web_spider_arena_x + 0x30 + (arg0->ext.main_43.unk94 << 5);
#endif
        arg0->y_speed = 0;
        arg0->gravity = 0x8000;
        vent_spawn_mixed_puffs((struct MiscObj*)arg0, 8);
        set_animation(arg0, 0);
        break;
    case 1:
        if (arg0->unk7C == 0) {
            if (arg0->y_speed <= -0x80000) {
                arg0->y_speed = -0x80000;
                arg0->gravity = 0;
            }
#ifdef VERSION_DEMO
            if (get_random() & 1)
#else
            if (g_Player.stun_timer != 0 || (get_random() & 3) != 0)
#endif
                threshold = 0x80;
            else
                threshold = 0x50;
            if (arg0->y_pos.i.hi - background_objects[arg0->bg_offset].y_pos.i.hi >= threshold) {
                arg0->unk7 = 2;
                arg0->unk7C = 0xA;
                arg0->y_speed = 0x10000;
                arg0->gravity = 0;
                set_animation(arg0, 0x20);
            }
            move_with_gravity(ANIMATED_OBJECT(arg0));
        } else {
            arg0->unk7C--;
        }
        break;
    case 2:
        move_with_gravity(ANIMATED_OBJECT(arg0));
        arg0->unk7C--;
        if (arg0->unk7C == 0) {
            arg0->y_speed = 0;
            arg0->gravity = 0;
        }
        if (arg0->unk7C == 0xF)
            arg0->y_speed = -0x10000;
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk6 = 1;
            arg0->unk7 = 0;
            arg0->unk7C = 0xA;
            set_animation(arg0, 0x21);
        }
        animate_object(ANIMATED_OBJECT(arg0));
        break;
    }
}

void web_spider_drop_climb(struct MainObj* self)
{
    switch (self->unk7) {
    case 0:
        if (self->unk7C == 0) {
#ifdef VERSION_DEMO
            if ((get_random() & 0xF) != 0) {
#else
            if ((get_random() & 0xF) != 0 && g_Player.stun_timer == 0) {
#endif
                self->unk5 = 3;
                self->unk6 = 0;
                self->unk7 = 0;
                if (self->x_pos.i.hi - g_Player.x_pos.i.hi >= 0) {
                    self->unk15 = 0;
                } else {
                    self->unk15 = PLAYER_FACING_RIGHT;
                }
            } else {
                self->y_speed = FIXED(3.5);
                self->gravity = 0;
                self->unk7 = 1;
                set_animation(self, 0x1F);
                func_8001540C(2, 0x70, self);
            }
        } else {
            self->unk7C--;
        }
        break;
    case 1:
        if (self->on_screen == 0) {
            self->unk7 = 2;
            self->unk7C = 8;
            if (self->ext.main_43.hurt_collision != 0) {
                self->collision_data = D_801075F4;
                self->ext.main_43.hurt_collision = 0;
            }
        }
        if (self->animation_step.fields.event != 0) {
            self->animation_step.fields.event = 0;
            func_8001540C(2, 0x70, self);
        }
        animate_object(ANIMATED_OBJECT(self));
        move_with_gravity(ANIMATED_OBJECT(self));
        break;
    case 2:
        if (--self->unk7C == 0) {
            self->unk6 = 0;
            self->unk7 = 0;
        }
        break;
    }
}

void web_spider_shoot(struct MainObj* self)
{
    web_spider_shoot_funcs[self->unk6](self);
}

#ifdef VERSION_DEMO
void func_8006E0B0_demo(struct MainObj* self)
{
    self->unk6 = 1;
    if (self->hp >= 0x26) {
        self->unk7 = 3;
        set_animation(self, 3);
    } else {
        self->unk7 = 4;
        set_animation(self, 0x26);
    }
}
#else
void web_spider_shoot_start(struct MainObj* self)
{
    self->unk6 = 1;
    set_animation(self, 3);
}

#endif

void web_spider_shoot_fire(struct AnimatedObj* self)
{
    if (self->animation_step.fields.relative_step != 0) {
        if (self->animation_step.fields.event == 1) {
            web_spider_spawn_web_shot(self, self->unk7);
            self->animation_step.fields.event = 0;
            func_8001540C(2, 0x72, self);
        }
        if (self->animation_step.fields.event == 2) {
            self->animation_step.fields.event = 0;
            web_spider_spawn_web_flash(self);
        }
    } else {
        self->y_vel.val = FIXED(3.5);
        self->unk2C = 0;
        self->unk5 = 2;
        self->unk6 = 1;
        self->unk7 = 1;
        set_animation(self, 0x1F);
        func_8001540C(2, 0x70, self);
    }
    animate_object(self);
}

void web_spider_swing(struct MainObj* self)
{
    web_spider_swing_funcs[self->unk6](self);
}

void web_spider_swing_start(struct MainObj* self)
{
    self->unk6 = 1;
    self->ext.main_43.move_direction = 0;
    self->ext.main_43.animation_set = web_spider_swing_sets[get_random() & 0xF];
    web_spider_set_move_timer(self);
    self->ext.main_43.animation_index = 0;
    self->ext.main_43.animation_length = 7;
    web_spider_set_swing_animation(self);
}

// web_spider_swing_move
void func_80064154(struct MainObj* arg0)
{
    const u16* point;
    s16 dx;
    s16 dy;

    if (arg0->ext.main_43.attack_cooldown == 0) {
#ifndef VERSION_DEMO
        arg0->ext.main_43.unk94 = 0;
        if (g_Player.stun_timer != 0) {
            arg0->ext.main_43.unk94 = 1;
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            return;
        }
#endif
        dx = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
        dy = arg0->y_pos.i.hi - g_Player.y_pos.i.hi;
        if ((dx < 0 ? -dx : dx) >= 0x40 && (dy < 0 ? -dy : dy) >= 0x50) {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            return;
        }
    } else {
        arg0->ext.main_43.attack_cooldown--;
    }
    point = (const u16*)web_spider_swing_paths[arg0->ext.main_43.animation_set] + arg0->ext.main_43.animation_index * 2;
#ifdef VERSION_DEMO
    dx = point[0];
    dy = point[1];
#else
    dx = point[0] + web_spider_arena_x + 0x10;
    dy = point[1] + web_spider_arena_y;
#endif
    func_80065168(arg0, dx, dy);
    if (--arg0->unk7C == 0) {
        arg0->ext.main_43.animation_index++;
        if (arg0->ext.main_43.animation_length < arg0->ext.main_43.animation_index) {
            arg0->unk6 = 2;
            arg0->ext.main_43.animation_index = 0;
            arg0->unk7C = 0x20;
            web_spider_set_move_timer(arg0);
        } else {
            web_spider_set_move_timer(arg0);
            web_spider_set_swing_animation(arg0);
        }
    }
    if (arg0->animation_step.fields.event != 0) {
        arg0->animation_step.fields.event = 0;
        func_8001540C(2, 0x70, arg0);
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void web_spider_swing_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk6 = 0;
    }
}

void web_spider_attack(struct MainObj* self)
{
#ifdef VERSION_DEMO
    if (self->ext.main_43.attack_count == 0) {
        func_800643B0(self);
    } else {
        web_spider_attack_web(self);
    }
#else
    if (self->ext.main_43.unk94 == 0) {
        if (self->ext.main_43.attack_count == 0) {
            func_800643B0(self);
        } else {
            web_spider_attack_web(self);
        }
    } else {
        func_800643B0(self);
    }
#endif
}

// web_spider_attack_spiderlings
void func_800643B0(struct MainObj* arg0)
{
    struct MainObj* child;
    u32 i;

    switch (arg0->unk6) {
    case 0:
        arg0->unk6 = 1;
        set_animation(arg0, 0xB);
        break;
    case 1:
        if (arg0->animation_step.fields.relative_step != 0) {
            if (arg0->animation_step.fields.event != 0) {
                for (i = 0; i < 4; i++) {
                    child = find_free_main_obj();
                    if (child == NULL)
                        continue;
                    child->active = 0x41;
                    child->id = 0x2B;
                    child->unk2 = i + 1;
                    child->x_pos.val = arg0->x_pos.val;
                    child->y_pos.val = arg0->y_pos.val;
                    child->y_pos.i.hi -= 0x18;
                    child->animation_table = arg0->animation_table;
                    child->unk40 = arg0->unk40;
                    child->sprite_frames = arg0->sprite_frames;
                    child->unk42 = arg0->unk42 & 0x7FFF;
                    child->unk16 = arg0->unk16;
                    child->unk15 = arg0->unk15;
                    child->ext.main_43.effect = (struct EffectObj*)arg0;
                }
                arg0->animation_step.fields.event = 0;
                func_8001540C(2, 0x71, arg0);
            }
        } else {
            arg0->unk6 = 2;
            set_animation(arg0, 0xC);
        }
        break;
    case 2:
        if (arg0->animation_step.fields.relative_step != 0)
            break;
        arg0->unk5 = 4;
        arg0->unk6 = 1;
        arg0->unk7 = 0;
        set_animation(arg0, arg0->ext.main_43.animation_id);
        web_spider_set_attack_cooldown(arg0);
        arg0->ext.main_43.attack_count++;
        if (arg0->ext.main_43.attack_count >= 3)
            arg0->ext.main_43.attack_count = 0;
        break;
    }
    animate_object(ANIMATED_OBJECT(arg0));
}

void web_spider_attack_web(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
#ifdef VERSION_DEMO
        if (self->hp >= 0x10) {
            self->unk7 = 3;
            set_animation(self, 0xA);
        } else {
            self->unk7 = 4;
            set_animation(self, 0x26);
        }
#else
        set_animation(self, 0xA);
#endif
        if (self->x_pos.i.hi - g_Player.x_pos.i.hi >= 0) {
            self->unk15 = 0;
        } else {
            self->unk15 = PLAYER_FACING_RIGHT;
        }
        return;
    }
    if (self->animation_step.fields.relative_step != 0) {
        if (self->animation_step.fields.event == 1) {
            web_spider_spawn_web_shot(ANIMATED_OBJECT(self), self->unk7);
            self->animation_step.fields.event = 0;
            func_8001540C(2, 0x72, self);
        }
        if (self->animation_step.fields.event == 2) {
            self->animation_step.fields.event = 0;
            web_spider_spawn_web_flash(ANIMATED_OBJECT(self));
        }
    } else {
        self->unk5 = 4;
        self->unk6 = 1;
        self->unk7 = 0;
        set_animation(self, self->ext.main_43.animation_id);
        web_spider_set_attack_cooldown(self);
        self->ext.main_43.attack_count++;
        if (self->ext.main_43.attack_count >= 3) {
            self->ext.main_43.attack_count = 0;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void web_spider_big_web(struct MainObj* self)
{
    web_spider_big_web_funcs[self->unk6](self);
}

// web_spider_big_web_start
void func_800646EC(struct MainObj* arg0)
{
    switch (arg0->unk7) {
    case 0:
        arg0->unk7 = 1;
        arg0->ext.main_43.attack_count = 0;
        arg0->ext.main_43.attack_cooldown = 0;
        arg0->unk7C = 0xC0;
        arg0->x_pos.i.hi = DEMO_ALT(web_spider_arena_x, 0x1210) + 0xB0;
        arg0->x_pos.i.lo = 0;
        arg0->y_speed = 0;
        arg0->gravity = 0x8000;
        arg0->ext.main_43.flash_timer = 0;
        arg0->collision_data = D_801060F0;
        vent_spawn_mixed_puffs((struct MiscObj*)arg0, 8);
        set_animation(arg0, 0);
        break;
    case 1:
        if (arg0->unk7C == 0) {
            if (arg0->y_speed <= -0x80000) {
                arg0->y_speed = -0x80000;
                arg0->gravity = 0;
            }
            if (arg0->y_pos.i.hi - background_objects[arg0->bg_offset].y_pos.i.hi >= 0x58) {
                arg0->unk7 = 2;
                arg0->unk7C = 0x1E;
                set_animation(arg0, 0x20);
                arg0->y_speed = 0x10000;
                arg0->gravity = 0;
            }
            move_with_gravity(ANIMATED_OBJECT(arg0));
        } else {
            arg0->unk7C--;
        }
        break;
    case 2:
        move_with_gravity(ANIMATED_OBJECT(arg0));
        arg0->unk7C--;
        if (arg0->unk7C == 0) {
            arg0->y_speed = 0;
            arg0->gravity = 0;
        }
        if (arg0->unk7C == 0xF)
            arg0->y_speed = -0x10000;
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk6 = 1;
            arg0->unk7 = 0;
            arg0->unk7C = 0x14;
            set_animation(arg0, 0x21);
        }
        animate_object(ANIMATED_OBJECT(arg0));
        break;
    }
}

void web_spider_big_web_spin(struct MainObj* arg0)
{
    struct VisualObj* self = VISUAL_OBJECT(arg0);
    s8 state = self->unk7;
    u32 i;

    switch (state) {
    case 0:
        self->unk7 = 1;
        set_animation(self, 4);
        break;
    case 1:
        if (self->animation_step.fields.relative_step == 0) {
            self->unk7 = 2;
        } else if (self->animation_step.fields.event != 0) {
            for (i = 0; i < 4U; i++) {
                web_spider_spawn_web_piece(self, (i + 1) & 0xFF);
            }
            self->animation_step.fields.event = 0;
            func_8001540C(2, 0x73, self);
        }
        animate_object(ANIMATED_OBJECT(self));
        break;
    case 2:
        self->unk6 = 2;
        self->unk7 = 0;
        break;
    }
}

void web_spider_big_web_center(struct MainObj* self)
{
    switch (self->unk7) {
    case 0:
        self->unk7 = 1;
        self->ext.main_43.shot->state = 2;
        self->y_speed = FIXED(1);
        self->gravity = FIXED(0.5);
        set_animation(self, 5);
        break;
    case 1:
        if (self->animation_step.fields.relative_step != 0) {
            if (self->animation_step.fields.event != 0) {
                self->animation_step.fields.event = 0;
                self->y_speed = 0;
                self->gravity = 0;
            }
            animate_object(ANIMATED_OBJECT(self));
            move_with_gravity(ANIMATED_OBJECT(self));
        } else {
            self->unk7 = 2;
        }
        break;
    case 2:
        self->unk5 = 4;
        self->unk6 = 0;
        self->unk7 = 0;
        self->x_pos.i.hi = DEMO_ALT(web_spider_arena_x + 0xA0, 0x12C0);
        self->y_pos.i.hi = DEMO_ALT(web_spider_arena_y + 0x70, 0x570);
        self->x_pos.i.lo = 0;
        self->y_pos.i.lo = 0;
        web_spider_set_attack_cooldown(self);
        self->collision_data = D_801075F4;
        break;
    }
}

void web_spider_fall(struct MainObj* self)
{
    web_spider_fall_funcs[self->unk6](self);
    CollisionRelated((struct PlayerObj*)self);
}

void web_spider_fall_start(struct MainObj* self)
{
    self->unk6 = 1;
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = FIXED(4);
    self->gravity = FIXED(0.25);
    set_animation(self, 0xD);
    self->terrain_box = &D_800FF5B0;
    self->collision_data = (const u16*)D_801060F0;
    self->ext.main_43.hurt_collision = 1;
}

void web_spider_fall_slow(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = 2;
        self->y_speed = 0;
        self->gravity = FIXED(0.5);
        set_animation(self, 0xE);
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void web_spider_fall_land(struct MainObj* self)
{
    if (self->collision_flags & 8) {
        self->unk6 = 3;
        self->y_speed = 0;
        self->gravity = 0;
        set_animation(self, 0xF);
        self->terrain_box = NULL;
#ifndef VERSION_DEMO
        func_8001540C(2, 0x74, self);
#endif
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
}

void web_spider_fall_crash(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6 = 4;
        set_animation(self, 0x10);
    } else if (self->animation_step.fields.event != 0) {
        self->hp -= 4;
        self->animation_step.fields.event = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void web_spider_fall_rethread(struct MainObj* self)
{
    struct ShotObj* shot;

    if (self->animation_step.fields.relative_step != 0) {
        if (self->animation_step.fields.event != 0) {
            self->ext.main_43.shot = web_spider_spawn_thread(self, 1);
            self->animation_step.fields.event = 0;
            if (self->unk15 == 0) {
                self->ext.main_43.shot->unk84.value = FIXED(8);
            } else {
                self->ext.main_43.shot->unk84.value = FIXED(-8);
            }
        }
    } else {
        shot = self->ext.main_43.shot;
        if (shot->unk5 == 0) {
            self->y_speed = FIXED(3.5);
            self->gravity = 0;
            self->unk5 = 2;
            self->unk6 = 1;
            self->unk7 = 1;
            set_animation(self, 0x1F);
            shot->unk84.value = 0;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void web_spider_check_big_web(struct MainObj* self)
{
#ifdef MMX4_BIG_ENDIAN
    if (self->ext.main_43.big_web_done == 0 && self->state < 2 && self->unk5 == 2 && self->unk6 == 1 && self->unk7 == 2 && self->hp < 0x18) {
#else
    if (self->ext.main_43.big_web_done == 0 && self->state < 2 && self->unk5 == 2 && (*(u32*)&self->state & 0xFFFF0000) == 0x02010000 && self->hp < 0x18) {
#endif
        self->unk5 = 6;
        self->unk6 = 0;
        self->unk7 = 0;
        self->ext.main_43.big_web_done = 1;
        self->collision_data = (const u16*)D_801060F0;
        self->ext.main_43.hurt_collision = 1;
    }
}

struct ShotObj* web_spider_spawn_thread(struct MainObj* self, s32 variant)
{
    struct ShotObj* shot;
    struct ShotObj* result = self->ext.main_43.shot;

    if (result == NULL) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x17;
            shot->unk2 = variant;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            shot->animation_table = ANIMATED_OBJECT(self)->animation_table;
            shot->unk40 = self->unk40;
            shot->unk3C = ANIMATED_OBJECT(self)->unk3C;
            shot->unk42 = self->unk42 & 0x7FFF;
            shot->unk16 = self->unk16;
            shot->unk7C = WEAPON_OBJECT(self);
            shot->unk15 = self->unk15;
            shot->unk84.value = 0;
            self->ext.main_43.shot = shot;
        }
        result = shot;
    }
    return result;
}

void web_spider_spawn_web_piece(struct VisualObj* self, u8 arg1)
{
    struct VisualObj* visual;

    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 0x11;
        visual->unk2 = arg1;
        visual->x_pos.val = self->x_pos.val;
        visual->y_pos.val = self->y_pos.val;
        visual->animation_table = self->animation_table;
        visual->unk40 = self->unk40;
        visual->unk3C = self->unk3C;
        visual->unk42 = self->unk42 & 0x7FFF;
        visual->unk16 = self->unk16;
        visual->unk50 = (struct PlayerObj*)self;
        visual->unk15 = self->unk15;
    }
}

void web_spider_spawn_web_flash(struct AnimatedObj* arg0)
{
    struct AnimatedObj* self;
    struct VisualObj* visual;

    self = arg0;
    visual = find_free_visual_obj();
    if (visual != 0) {
        visual->active = 0x41;
        visual->id = 0x14;
        visual->unk2 = 1;
        visual->x_pos.val = self->x_pos.val;
        visual->y_pos.val = self->y_pos.val + FIXED(28);
        visual->animation_table = self->animation_table;
        visual->unk40 = self->unk40;
        visual->unk3C = self->unk3C;
        visual->unk42 = self->unk42 & 0x7FFF;
        visual->unk16 = self->unk16;
        visual->unk50 = (struct PlayerObj*)self;
        visual->unk15 = self->unk15;
    }
}

void web_spider_spawn_web_shot(struct AnimatedObj* self, u8 arg1)
{
    struct ShotObj* shot;
    s32 x_offset;

    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x16;
        shot->unk2 = arg1;
        x_offset = -0x12;
        if (self->unk15 != 0) {
            x_offset = 0x12;
        }
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->x_pos.i.hi += x_offset;
        shot->y_pos.i.hi += 0x26;
        shot->animation_table = self->animation_table;
        shot->unk40 = self->unk40;
        shot->unk3C = self->unk3C;
        shot->unk42 = self->unk42 & 0x7FFF;
        shot->unk16 = self->unk16;
        shot->unk7C = WEAPON_OBJECT(self);
        shot->unk15 = self->unk15;
    }
}

// web_spider_aim_swing
void func_80065168(struct MainObj* arg0, s16 x, s16 y)
{
    s32 dx = arg0->x_pos.val - (x << 16);
    s32 dy = arg0->y_pos.val - (y << 16);
    u8 direction = angle_from_delta(dx, dy);

    if ((arg0->ext.main_43.move_direction ^ direction) & 0x10) {
        arg0->x_pos.i.lo = 0;
        arg0->y_pos.i.lo = 0;
    } else {
        arg0->x_pos.val -= dx / arg0->unk7C;
        arg0->y_pos.val -= dy / arg0->unk7C;
    }
    arg0->ext.main_43.move_direction = direction;
}

#ifdef MMX4_PC

static u8 web_spider_retail_timer_byte(u8 offset)
{
    static const u8 bytes[20] = {
        0x10, 0x14, 0x18, 0x20, 0x5A, 0x50, 0x44, 0x32, 0x0C, 0x53, 0x06, 0x80, 0x7C, 0x53, 0x06, 0x80, 0x58, 0x54, 0x06, 0x80
    };
    return bytes[offset];
}
#endif

void web_spider_set_move_timer(struct MainObj* self)
{
#ifdef MMX4_PC
    self->unk7C = web_spider_retail_timer_byte((self->hp & 0x7F) >> 3);
#else
    self->unk7C = web_spider_move_timers[(self->hp & 0x7F) >> 3];
#endif
}

void web_spider_set_attack_cooldown(struct MainObj* self)
{
    if (self->ext.main_43.attack_cooldown == 0) {
        int cooldown_index = (self->hp & 0x7F) >> 3;
#ifdef MMX4_PC
        self->ext.main_43.attack_cooldown = web_spider_retail_timer_byte(cooldown_index + 4);
#else
        self->ext.main_43.attack_cooldown = web_spider_attack_cooldowns[cooldown_index];
#endif
    }
}

void web_spider_set_swing_animation(struct MainObj* self)
{
    const u8* animation_table;
    u8 animation_id;

    animation_table = web_spider_swing_animations[self->ext.main_43.animation_set];
    animation_id = animation_table[self->ext.main_43.animation_index];
    self->ext.main_43.animation_id = animation_id;
    set_animation(self, animation_id);
}

void web_spider_death_start(struct MainObj* self)
{
    self->unk5 = 1;
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_43.flash_timer = 0x19;
    self->unk42 &= 0x7FFF;
#ifndef VERSION_DEMO
    player_start_script_action(0x14, g_Player.unk15);
#endif
    set_animation(self, 0x22);
    is_on_screen(BASE_OBJECT(self));
}

void web_spider_death_explode(struct MainObj* self)
{
    struct EffectObj* effect;
    if (0 == --self->unk7C) {
        self->unk5 = 2;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.i.hi;
            effect->y_pos.i.hi = self->y_pos.i.hi;
            self->ext.main_43.effect = effect;
        }
    }
    is_on_screen(BASE_OBJECT(self));
    if (self->unk7E-- == 0) {
        self->unk42 ^= 0x8000;
        if ((self->ext.main_43.flash_timer -= 5) > 0x19) {
            self->ext.main_43.flash_timer = 0;
        }
        self->unk7E = self->ext.main_43.flash_timer > 5 ? self->ext.main_43.flash_timer : 5;
    }
}

void web_spider_death_finish(struct MainObj* self)
{
    struct EffectObj* effect = self->ext.main_43.effect;
    self->on_screen = 0;
    if (effect->active != 0) {
        if (effect->unk7 == 0) {
            if (self->unk7E-- == 0) {
                self->unk42 ^= 0x8000;
                self->unk7E = 5;
            }
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
#ifdef VERSION_DEMO
        engine_obj.unkF = 0x10;
#else
        if (engine_obj.stage == 1) {
            engine_obj.unkF = 0x10;
        } else {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        }
#endif
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
}

void web_spider_death(struct MainObj* self)
{
    web_spider_death_funcs[self->unk5](self);
}

// spiderling_init
void func_80065574(struct MainObj* arg0)
{
    s32* velocity;

    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
    arg0->unk7C = 0;
    arg0->on_screen = 1;
    arg0->hp = 3;
    arg0->contact_damage = DEMO_ALT(4, 3);
    arg0->invincibility_timer = 0;
    arg0->unk62 = 0;
    arg0->unk63 = 1;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->air_state = 0;
    velocity = (s32*)&spiderling_velocities[((arg0->unk2 - 1) & 3) * 2];
    arg0->x_speed = *velocity++;
    arg0->x_accel = *velocity++;
    arg0->y_speed = *velocity++;
    arg0->gravity = *velocity++;
    arg0->unk16 = 3;
    arg0->collision_flags = 0;
    arg0->hurt_box = &D_800FF5B8;
    arg0->attack_box = &D_800FF5B4;
    arg0->terrain_box = &D_800FF5BC;
    arg0->collision_data = D_801075F4;
    set_animation(arg0, 0x1B);
}

void spiderling_run(struct MainObj* self)
{
    s32 hit;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    spiderling_step_funcs[self->unk5](self);
    CollisionRelated(PLAYER_OBJECT(self));
#ifdef VERSION_DEMO
    func_8002D9BC(self);
#endif
    hit = func_8002DD04(self);
    if (hit < 0) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 2;
        return;
    }
    if (self->ext.main_43.effect->state == 2) {
        spawn_explosion(BASE_OBJECT(self));
        self->state = 2;
        return;
    }
#ifndef VERSION_DEMO
    func_8002D9BC(self);
#endif
    is_on_screen(BASE_OBJECT(self));
}

void spiderling_fall(struct MainObj* self)
{
    if (self->collision_flags & 3) {
        self->x_speed = 0;
        self->x_accel = 0;
    }
    if (self->collision_flags & 8) {
        self->unk5 = 3;
        self->unk6 = 0;
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->gravity = 0;
        set_animation(self, 0x1C);
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
}

void spiderling_crawl(struct MainObj* self)
{
    if (self->unk6 == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            if (self->x_pos.val - g_Player.x_pos.val < 0) {
                self->x_speed = FIXED(1.5);
                self->unk15 = PLAYER_FACING_RIGHT;
            } else {
                self->x_speed = FIXED(-1.5);
                self->unk15 = 0;
            }
            self->unk6 = 1;
            set_animation(self, 0x1D);
        }
        animate_object(ANIMATED_OBJECT(self));
        return;
    }
    if (self->collision_flags & 3) {
        self->unk5 = 4;
        self->unk6 = 0;
        self->unk7 = 0;
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->gravity = 0;
        self->unk15 = 0;
        if (self->collision_flags & 1) {
            self->unk15 = PLAYER_FACING_RIGHT;
        }
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
}

void spiderling_leave(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->y_speed = FIXED(1.5);
        self->unk6 = 1;
        set_animation(self, 0x1E);
        return;
    }
    if (self->on_screen == 0) {
        self->state = 2;
    }
    animate_object(self);
    move_with_gravity(ANIMATED_OBJECT(self));
}

void spiderling_despawn(struct MainObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

union AnimationStep D_800FEF94[] = {
    { 7, 0, 1, 0x00 },
    { 1, 0, -1, 0x00 },
};

union AnimationStep D_800FEF9C[] = {
    { 2, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 17, 0, 1, 0x03 },
    { 6, 0, 1, 0x04 },
    { 8, 0, 1, 0x05 },
    { 6, 0, 1, 0x06 },
    { 8, 0, 1, 0x07 },
    { 6, 0, 1, 0x06 },
    { 7, 0, 1, 0x05 },
    { 7, 0, 1, 0x08 },
    { 8, 0, 1, 0x09 },
    { 8, 0, 1, 0x08 },
    { 10, DEMO_ALT(1, 0), 1, 0x05 },
    { 10, 0, 1, 0x06 },
    { 8, 0, 1, 0x07 },
    { 43, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 32, 0, 1, 0x0C },
    { 1, 0, 0, 0x0C },
};

union AnimationStep D_800FEFE8[] = {
    { 2, 1, 1, 0x05 },
    { 2, 0, 1, 0x0D },
    { 3, 0, 1, 0x0F },
    { 2, 0, 1, 0x0D },
    { 2, 1, 1, 0x05 },
    { 3, 0, 1, 0x0E },
    { 1, 0, -6, 0x0E },
};

union AnimationStep D_800FF004[] = {
    { 5, 1, 1, 0x05 },
    { 5, 0, 1, 0x0D },
    { 7, 0, 1, 0x0F },
    { 5, DEMO_ALT(1, 0), 1, 0x0D },
    { 5, DEMO_ALT(0, 1), 1, 0x05 },
    { 7, 0, 1, 0x0E },
    { 1, 0, -6, 0x0E },
};

union AnimationStep D_800FF020[] = {
    { 5, 0, 1, 0x05 },
    { 8, 0, 1, 0x10 },
    { 4, 0, 1, 0x01 },
    { 4, 0, 1, 0x02 },
    { 5, 2, 1, 0x11 },
    { 5, 0, 1, 0x12 },
    { 15, 0, 1, 0x13 },
    { 2, 1, 1, 0x14 },
    { 40, 0, 1, 0x15 },
    { 1, 0, 0, 0x15 },
};

union AnimationStep D_800FF048[] = {
    { 3, 0, 1, 0x05 },
    { 4, 0, 1, 0x10 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 3, 2, 1, 0x11 },
    { 3, 0, 1, 0x12 },
    { 8, 0, 1, 0x13 },
    { 2, 1, 1, 0x14 },
    { 24, 0, 1, 0x15 },
    { 3, 0, 1, 0x12 },
    { 8, 0, 1, 0x13 },
    { 2, 1, 1, 0x14 },
    { 24, 0, 1, 0x15 },
    { 1, 0, 0, 0x15 },
};

union AnimationStep D_800FF080[] = {
    { 3, 0, 1, 0x05 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 5, 1, 1, 0x11 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x01 },
    { 60, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep D_800FF0B8[] = {
    { 13, 0, 1, 0x05 },
    { 3, 1, 1, 0x16 },
    { 5, 0, 1, 0x17 },
    { 8, 0, 1, 0x18 },
    { 4, 0, 1, 0x17 },
    { 19, 0, 1, 0x16 },
    { 1, 0, 0, 0x16 },
};

union AnimationStep D_800FF0D4[] = {
    { 5, 0, 1, 0x16 },
    { 5, 1, 1, 0x19 },
    { 5, 0, 1, 0x1A },
    { 5, 0, 1, 0x1B },
    { 5, 1, 1, 0x1C },
    { 5, 0, 1, 0x1D },
    { 5, 0, 1, 0x1E },
    { 5, 1, 1, 0x1F },
    { 1, 0, 0, 0x1F },
};

union AnimationStep D_800FF0F8[] = {
    { 5, 0, 1, 0x20 },
    { 5, 1, 1, 0x21 },
    { 5, 0, 1, 0x22 },
    { 5, 0, 1, 0x23 },
    { 5, 1, 1, 0x24 },
    { 5, 0, 1, 0x25 },
    { 5, 0, 1, 0x26 },
    { 5, 1, 1, 0x27 },
    { 1, 0, 0, 0x27 },
};

union AnimationStep D_800FF11C[] = {
    { 5, 0, 1, 0x16 },
    { 5, 1, 1, 0x1F },
    { 5, 0, 1, 0x1E },
    { 5, 0, 1, 0x1D },
    { 5, 1, 1, 0x1C },
    { 5, 0, 1, 0x1B },
    { 5, 0, 1, 0x1A },
    { 5, 1, 1, 0x19 },
    { 1, 0, 0, 0x19 },
};

union AnimationStep D_800FF140[] = {
    { 5, 0, 1, 0x20 },
    { 5, 1, 1, 0x27 },
    { 5, 0, 1, 0x26 },
    { 5, 0, 1, 0x25 },
    { 5, 1, 1, 0x24 },
    { 5, 0, 1, 0x23 },
    { 5, 0, 1, 0x22 },
    { 5, 1, 1, 0x21 },
    { 1, 0, 0, 0x21 },
};

union AnimationStep D_800FF164[] = {
    { 3, 0, 1, 0x16 },
    { 3, 0, 1, 0x28 },
    { 3, 0, 1, 0x29 },
    { 3, 0, 1, 0x2A },
    { 3, 2, 1, 0x2B },
    { 3, 0, 1, 0x2C },
    { 10, 0, 1, 0x2D },
    { 2, 1, 1, 0x2E },
    { 64, 0, 1, 0x2F },
    { 1, 0, 0, 0x2F },
};

union AnimationStep D_800FF18C[] = {
    { 3, 0, 1, 0x16 },
    { 3, 0, 1, 0x28 },
    { 3, 0, 1, 0x29 },
    { 3, 0, 1, 0x2A },
    { 3, 2, 1, 0x2B },
    { 3, 0, 1, 0x2C },
    { 10, 0, 1, 0x2D },
    { 2, 1, 1, 0x2E },
    { 64, 0, 1, 0x2F },
    { 3, 0, 1, 0x2C },
    { 10, 0, 1, 0x2D },
    { 2, 1, 1, 0x2E },
    { 22, 0, 1, 0x2F },
    { 1, 0, 0, 0x2F },
};

union AnimationStep D_800FF1C4[] = {
    { 10, 0, 1, 0x16 },
    { 1, 0, 1, 0x30 },
    { 1, 0, 1, 0x31 },
    { 1, 0, 1, 0x30 },
    { 1, 0, 1, 0x32 },
    { 1, 0, 1, 0x30 },
    { 1, 0, 1, 0x31 },
    { 1, 0, 1, 0x30 },
    { 1, 0, 1, 0x32 },
    { 1, 0, 1, 0x30 },
    { 1, 0, 1, 0x31 },
    { 1, 0, 1, 0x30 },
    { 1, 0, 1, 0x32 },
    { 2, 0, 1, 0x2D },
    { 2, 0, 1, 0x2C },
    { 2, 0, 1, 0x2B },
    { 2, 0, 1, 0x2A },
    { 2, 0, 1, 0x33 },
    { 2, 0, 1, 0x34 },
    { 2, 0, 1, 0x35 },
    { 2, 0, 1, 0x37 },
    { 2, 0, 1, 0x36 },
    { 32, 0, 1, 0x37 },
    { 1, 1, 1, 0x37 },
    { 2, 0, 1, 0x36 },
    { 40, 0, 1, 0x37 },
    { 1, 0, 0, 0x37 },
};

union AnimationStep D_800FF230[] = {
    { 2, 0, 1, 0x35 },
    { 2, 0, 1, 0x34 },
    { 2, 0, 1, 0x38 },
    { 32, 0, 1, 0x16 },
    { 1, 0, 0, 0x16 },
};

union AnimationStep D_800FF244[] = {
    { 3, 0, 1, 0x05 },
    { 3, 0, 1, 0x39 },
    { 3, 0, 1, 0x3A },
    { 3, 0, 1, 0x3B },
    { 1, 0, 0, 0x3B },
};

union AnimationStep D_800FF258[] = {
    { 3, 0, 1, 0x3C },
    { 3, 0, -1, 0x3D },
};

union AnimationStep D_800FF260[] = {
    { 2, 1, 1, 0x3E },
    { 2, 0, 1, 0x3F },
    { 3, 0, 1, 0x40 },
    { 3, 0, 1, 0x41 },
    { 5, 0, 1, 0x3B },
    { 4, 0, 1, 0x3C },
    { 3, 1, 1, 0x3E },
    { 4, 0, 1, 0x3A },
    { 4, 0, 1, 0x3B },
    { 20, 0, 1, 0x42 },
    { 6, 0, 1, 0x43 },
    { 3, 0, 1, 0x44 },
    { 3, 0, 1, 0x45 },
    { 10, 0, 1, 0x46 },
    { 3, 0, 1, 0x45 },
    { 3, 0, 1, 0x44 },
    { 3, 0, 1, 0x43 },
    { 3, 0, 1, 0x47 },
    { 3, 0, 1, 0x48 },
    { 3, 0, 1, 0x49 },
    { 3, 0, 1, 0x4A },
    { 6, 0, 1, 0x4B },
    { 30, 0, 1, 0x4A },
    { 1, 0, 0, 0x4A },
};

union AnimationStep D_800FF2C0[] = {
    { 4, 0, 1, 0x4B },
    { 4, 0, 1, 0x4C },
    { 4, 0, 1, 0x4D },
    { 3, 0, 1, 0x4F },
    { 3, 1, 1, 0x4E },
    { 3, 0, 1, 0x4F },
    { 3, 0, 1, 0x50 },
    { 3, 0, 1, 0x4F },
    { 31, 0, 1, 0x4E },
    { 1, 0, 0, 0x4E },
};

union AnimationStep D_800FF2E8[] = {
    { 1, 0, 1, 0x51 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x53 },
    { 1, 0, -3, 0x54 },
};

union AnimationStep D_800FF2F8[] = {
    { 1, 0, 1, 0x55 },
    { 1, 0, 1, 0x56 },
    { 1, 0, 1, 0x57 },
    { 1, 0, 1, 0x58 },
    { 1, 0, 1, 0x59 },
    { 1, 0, 1, 0x5A },
    { 1, 0, 1, 0x5B },
    { 1, 0, 1, 0x5C },
    { 1, 0, 1, 0x5D },
    { 1, 0, 1, 0x5E },
    { 1, 0, 1, 0x5F },
    { 1, 0, 1, 0x60 },
    { 1, 0, 1, 0x61 },
    { 1, 0, 1, 0x62 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 0, 0x63 },
};

union AnimationStep D_800FF338[] = {
    { 1, 0, 1, 0x64 },
    { 1, 0, 1, 0x65 },
    { 1, 0, -2, 0x66 },
};

union AnimationStep D_800FF344[] = {
    { 1, 0, 1, 0x66 },
    { 1, 0, 1, 0x67 },
    { 1, 0, 1, 0x68 },
    { 1, 0, 1, 0x66 },
    { 1, 0, 1, 0x67 },
    { 1, 0, 1, 0x68 },
    { 1, 0, 1, 0x66 },
    { 1, 0, 1, 0x67 },
    { 1, 0, 1, 0x68 },
    { 1, 0, 1, 0x67 },
    { 1, 0, 1, 0x68 },
    { 1, 0, 1, 0x67 },
    { 1, 0, 1, 0x68 },
    { 1, 0, 1, 0x67 },
    { 1, 0, 1, 0x68 },
    { 1, 0, 0, 0x68 },
};

union AnimationStep D_800FF384[] = {
    { 2, 0, 1, 0x69 },
    { 2, 0, 1, 0x6A },
    { 2, 0, 1, 0x69 },
    { 2, 0, 1, 0x6A },
    { 1, 0, 1, 0x69 },
    { 1, 0, 1, 0x6A },
    { 1, 0, 1, 0x69 },
    { 1, 0, -7, 0x6A },
};

union AnimationStep D_800FF3A4[] = {
    { 1, 0, 1, 0x6B },
    { 1, 0, 1, 0x6C },
    { 1, 0, 1, 0x6D },
    { 1, 0, -3, 0x6E },
};

union AnimationStep D_800FF3B4[] = {
    { 1, 0, 1, 0x6F },
    { 1, 0, 1, 0x70 },
    { 1, 0, 1, 0x71 },
    { 1, 0, 1, 0x70 },
    { 1, 0, 1, 0x72 },
    { 1, 0, 1, 0x70 },
    { 1, 0, -6, 0x70 },
};

union AnimationStep D_800FF3D0[] = {
    { 1, 0, 1, 0x73 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x74 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x75 },
    { 1, 0, 1, 0x76 },
    { 1, 0, -6, 0x76 },
};

union AnimationStep D_800FF3EC[] = {
    { 5, 0, 1, 0x77 },
    { 5, 0, 1, 0x78 },
    { 5, 0, 1, 0x79 },
    { 5, 0, 1, 0x7A },
    { 6, 1, 1, 0x7B },
    { 5, 0, 1, 0x7C },
    { 4, 0, 1, 0x7D },
    { 4, 0, 1, 0x7E },
    { 4, 0, 1, 0x7F },
    { 4, 0, 1, 0x80 },
    { 6, 0, 1, 0x81 },
    { 6, 1, 1, 0x82 },
    { 6, 0, 1, 0x83 },
    { 6, 0, -13, 0x84 },
};

union AnimationStep D_800FF424[] = {
    { 8, 1, 1, 0x77 },
    { 4, 0, 1, 0x78 },
    { 4, 0, 1, 0x79 },
    { 4, 0, 1, 0x7A },
    { 8, 1, 1, 0x7B },
    { 4, 0, 1, 0x7A },
    { 4, 0, 1, 0x79 },
    { 4, 0, -7, 0x78 },
};

union AnimationStep D_800FF444[] = {
    { 8, 0, 1, 0x85 },
    { 4, 0, 1, 0x86 },
    { 4, 0, 1, 0x87 },
    { 4, 0, 1, 0x88 },
    { 8, 0, 1, 0x89 },
    { 4, 0, 1, 0x8A },
    { 4, 0, 1, 0x8B },
    { 4, 0, 1, 0x8C },
    { 1, 0, -8, 0x8C },
};

union AnimationStep D_800FF468[] = {
    { 4, 0, 1, 0x8D },
    { 2, 0, 1, 0x8E },
    { 8, 0, 1, 0x8F },
    { 4, 0, 1, 0x8E },
    { 4, 0, 1, 0x8D },
    { 1, 0, 0, 0x8D },
};

union AnimationStep D_800FF480[] = {
    { 4, 0, 1, 0x8D },
    { 2, 0, 1, 0x90 },
    { 8, 0, 1, 0x91 },
    { 4, 0, 1, 0x92 },
    { 4, 0, 1, 0x93 },
    { 4, 0, 1, 0x90 },
    { 4, 0, -6, 0x8D },
};

union AnimationStep D_800FF49C[] = {
    { 4, 0, 1, 0x94 },
    { 2, 0, 1, 0x95 },
    { 8, 0, 1, 0x96 },
    { 4, 0, 1, 0x97 },
    { 4, 0, 1, 0x98 },
    { 4, 0, 1, 0x95 },
    { 4, 0, -6, 0x94 },
};

union AnimationStep D_800FF4B8[] = {
    { 2, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 17, 0, 1, 0x03 },
    { 6, 0, 1, 0x04 },
    { 8, 0, 1, 0x05 },
    { 6, 0, 1, 0x06 },
    { 8, 0, 1, 0x07 },
    { 6, 0, 1, 0x06 },
    { 1, 0, 0, 0x06 },
};

union AnimationStep D_800FF4DC[] = {
    { 7, 0, 1, 0x05 },
    { 7, 0, 1, 0x08 },
    { 8, 0, 1, 0x09 },
    { 8, 0, 1, 0x08 },
    { 10, 0, 1, 0x05 },
    { 10, 0, 1, 0x06 },
    { 8, 0, 1, 0x07 },
    { 8, 0, 1, 0x06 },
    { 1, 0, 0, 0x06 },
};

union AnimationStep D_800FF500[] = {
    { 1, 0, 0, 0x3C },
};

union AnimationStep* web_spider_animations[40] = {
    D_800FEF94,
    D_800FEF9C,
    D_800FF004,
    D_800FF020,
    D_800FF080,
    D_800FF0B8,
    D_800FF0D4,
    D_800FF0F8,
    D_800FF11C,
    D_800FF140,
    D_800FF164,
    D_800FF1C4,
    D_800FF230,
    D_800FF244,
    D_800FF258,
    D_800FF260,
    D_800FF2C0,
    D_800FF2E8,
    D_800FF2F8,
    D_800FF338,
    D_800FF344,
    D_800FF384,
    D_800FF3A4,
    D_800FF3B4,
    D_800FF3D0,
    D_800FF3EC,
    D_800FF424,
    D_800FF444,
    D_800FF468,
    D_800FF480,
    D_800FF49C,
    D_800FEFE8,
    D_800FF4B8,
    D_800FF4DC,
    D_800FF500,
    D_800FF500,
    D_800FF500,
    D_800FF500,
    D_800FF048,
    D_800FF18C,
};

u8 web_spider_debris[4] = { 13, 14, 15, 16 };

struct Unk_unk68 web_spider_attack_box = { -21, -21, 40, 34 };

struct Unk_unk68 web_spider_hurt_box = { -23, -30, 44, 57 };

struct Unk_unk68 D_800FF5B0 = { 0, 0, 24, 19 };

struct Unk_unk68 D_800FF5B4 = { -5, -8, 11, 15 };

struct Unk_unk68 D_800FF5B8 = { -10, -8, 18, 15 };

struct Unk_unk68 D_800FF5BC = { 0, 0, 8, 8 };

#define SWING_X(x) DEMO_ALT(x, 0x1220 + (x))
#define SWING_Y(y) DEMO_ALT(y, 0x500 + (y))

RECT D_800FF5C0[4] = {
    { SWING_X(112), SWING_Y(56), SWING_X(160), SWING_Y(0) },
    { SWING_X(208), SWING_Y(56), SWING_X(160), SWING_Y(104) },
    { SWING_X(112), SWING_Y(152), SWING_X(160), SWING_Y(192) },
    { SWING_X(208), SWING_Y(152), SWING_X(160), SWING_Y(104) },
};

RECT D_800FF5E0[4] = {
    { SWING_X(112), SWING_Y(56), SWING_X(64), SWING_Y(104) },
    { SWING_X(112), SWING_Y(152), SWING_X(160), SWING_Y(104) },
    { SWING_X(208), SWING_Y(56), SWING_X(256), SWING_Y(104) },
    { SWING_X(208), SWING_Y(152), SWING_X(160), SWING_Y(104) },
};

RECT D_800FF600[4] = {
    { SWING_X(112), SWING_Y(152), SWING_X(64), SWING_Y(104) },
    { SWING_X(112), SWING_Y(152), SWING_X(160), SWING_Y(104) },
    { SWING_X(208), SWING_Y(135), SWING_X(256), SWING_Y(104) },
    { SWING_X(208), SWING_Y(152), SWING_X(160), SWING_Y(104) },
};

RECT D_800FF620[4] = {
    { SWING_X(208), SWING_Y(56), SWING_X(160), SWING_Y(16) },
    { SWING_X(112), SWING_Y(56), SWING_X(160), SWING_Y(104) },
    { SWING_X(208), SWING_Y(152), SWING_X(160), SWING_Y(192) },
    { SWING_X(112), SWING_Y(152), SWING_X(160), SWING_Y(104) },
};

RECT D_800FF640[4] = {
    { SWING_X(208), SWING_Y(56), SWING_X(256), SWING_Y(104) },
    { SWING_X(208), SWING_Y(152), SWING_X(160), SWING_Y(104) },
    { SWING_X(112), SWING_Y(56), SWING_X(64), SWING_Y(104) },
    { SWING_X(112), SWING_Y(152), SWING_X(160), SWING_Y(104) },
};

RECT D_800FF660[4] = {
    { SWING_X(208), SWING_Y(152), SWING_X(256), SWING_Y(104) },
    { SWING_X(208), SWING_Y(152), SWING_X(160), SWING_Y(104) },
    { SWING_X(112), SWING_Y(152), SWING_X(64), SWING_Y(104) },
    { SWING_X(112), SWING_Y(152), SWING_X(160), SWING_Y(104) },
};

u8 D_800FF680[8] = { 8, 9, 6, 7, 7, 6, 9, 8 };

u8 D_800FF688[8] = { 8, 7, 6, 9, 9, 6, 7, 8 };

u8 D_800FF690[8] = { 7, 8, 6, 9, 6, 9, 7, 8 };

u8 D_800FF698[8] = { 6, 9, 8, 7, 9, 6, 7, 8 };

u8 D_800FF6A0[8] = { 9, 6, 7, 9, 8, 7, 6, 8 };

u8 D_800FF6A8[8] = { 6, 9, 7, 9, 7, 8, 6, 8 };

RECT* web_spider_swing_paths[6] = {
    D_800FF5C0,
    D_800FF5E0,
    D_800FF600,
    D_800FF620,
    D_800FF640,
    D_800FF660,
};

const u8* web_spider_swing_animations[6] = {
    D_800FF680,
    D_800FF688,
    D_800FF690,
    D_800FF698,
    D_800FF6A0,
    D_800FF6A8,
};

#if defined(MMX4_SATURN) || defined(VERSION_DEMO)
extern u16 web_spider_arena_x;
extern u16 web_spider_arena_y;
#else
u16 web_spider_arena_x = 0x0000;

u16 web_spider_arena_y = 0x0000;
#endif

void (*web_spider_state_funcs[3])(struct MainObj*) = {
    web_spider_intro,
    func_8006398C,
    web_spider_death,
};

void (*spiderling_state_funcs[3])() = {
    func_80065574,
    spiderling_run,
    spiderling_despawn,
};

void (*web_spider_intro_funcs[DEMO_ALT(10, 8)])(struct MainObj*) = {
    web_spider_intro_warning,
    web_spider_intro_setup,
    func_8006346C,
    web_spider_intro_spawn_thread,
    web_spider_intro_wait,
    web_spider_intro_descend,
#ifndef VERSION_DEMO
    web_spider_intro_pose,
    web_spider_intro_start_health_bar,
#endif
    web_spider_intro_fill_health,
    web_spider_intro_climb,
};

u8 D_800FF724[16] = { 0x07, 0x05, 0x06, 0x04, 0x02, 0x03, 0x01, 0x00, 0x01, 0x00, 0x03, 0x02, 0x05, 0x04, 0x07, 0x06 };

void (*web_spider_step_funcs[7])() = {
    enemy_hit_reaction,
    web_spider_fall,
    web_spider_drop,
    web_spider_shoot,
    web_spider_swing,
    web_spider_attack,
    web_spider_big_web,
};

void (*web_spider_drop_funcs[3])() = {
    func_80063B20,
    web_spider_drop_climb,
    web_spider_drop_climb,
};

void (*web_spider_shoot_funcs[3])() = {
    DEMO_ALT(web_spider_shoot_start, func_8006E0B0_demo),
    web_spider_shoot_fire,
    web_spider_shoot_fire,
};

void (*web_spider_swing_funcs[3])(struct MainObj*) = {
    web_spider_swing_start,
    func_80064154,
    web_spider_swing_wait,
};

u8 web_spider_swing_sets[16] = { 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x02, 0x03, 0x04, 0x05, 0x02, 0x03, 0x04, 0x05, 0x02, 0x03 };

void (*web_spider_big_web_funcs[3])() = {
    func_800646EC,
    web_spider_big_web_spin,
    web_spider_big_web_center,
};

void (*web_spider_fall_funcs[5])(struct MainObj*) = {
    web_spider_fall_start,
    web_spider_fall_slow,
    web_spider_fall_land,
    web_spider_fall_crash,
    web_spider_fall_rethread,
};

u8 web_spider_move_timers[4] = { 0x10, 0x14, 0x18, 0x20 };

u8 web_spider_attack_cooldowns[4] = { 0x5A, 0x50, 0x44, 0x32 };

void (*web_spider_death_funcs[3])(struct MainObj*) = {
    web_spider_death_start,
    web_spider_death_explode,
    web_spider_death_finish,
};

struct FixedPointPosition spiderling_velocities[8] = {
    { (s32)0x00010000, (s32)0x00000000 },
    { (s32)0x00058000, (s32)0x00004000 },
    { (s32)0x00028000, (s32)0x00000000 },
    { (s32)0x00058000, (s32)0x00004000 },
    { (s32)0xFFFD8000, (s32)0x00000000 },
    { (s32)0x00058000, (s32)0x00004000 },
    { (s32)0xFFFF0000, (s32)0x00000000 },
    { (s32)0x00058000, (s32)0x00004000 },
};

void (*spiderling_step_funcs[5])(struct MainObj*) = {
    enemy_hit_reaction,
    enemy_hit_reaction,
    spiderling_fall,
    spiderling_crawl,
    spiderling_leave,
};
