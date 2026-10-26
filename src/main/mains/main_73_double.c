// MainObj, main_object_update_funcs[73]
// 8008BA38..8008D3B8
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_73_double.h"
#include "main/objects.h"
#include "main/player_common.h"
#include "main/128C4.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/stage_objects.h"
#include "main/collision_bounds.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#include "main/collision_bounds.h"
#endif

extern struct Unk_unk68 double_dive_attack_box;
extern struct Unk_unk68 double_dive_hurt_box;

// double_intro_talk_funcs
extern void (*double_intro_talk_funcs[])(struct MainObj*);

// double_intro_funcs
extern void (*double_intro_funcs[])(struct MainObj*);

// double_wait_funcs
extern void (*double_wait_funcs[])(struct MainObj*);

// double_energy_ball_funcs
extern void (*double_energy_ball_funcs[])(struct MainObj*);

// double_dive_funcs
extern void (*double_dive_funcs[])(struct MainObj*);

// double_aerial_shot_funcs
extern void (*double_aerial_shot_funcs[])(struct MainObj*);

void func_8008CBF8(struct MainObj*);

// double_death_funcs
extern void (*double_death_funcs[7])(struct MainObj*);

// double_state_funcs
extern void (*double_state_funcs[])(struct MainObj*);

// double_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

extern struct Unk_unk68 double_slide_attack_box;
extern struct Unk_unk68 double_slide_hurt_box;
extern struct Unk_unk68 D_80108204[];
extern void (*double_step_funcs[6])(struct MainObj*);
extern u8* double_script_table_0[2];
extern void* double_script_table_1[2];
extern void* double_animations[31];
extern struct Unk_unk68 double_terrain_box;
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8008CD80(struct MainObj* self);
void func_8008C10C(struct MainObj* self);
void func_8008BA38(struct MainObj* self);
void func_8008BB6C(struct MainObj* self);
void func_8008C664(struct MainObj* self);
void double_spawn_afterimage(struct MainObj*, s8);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_73_double", func_8008BA38);
#else
void func_8008BA38(struct MainObj* self)
{
    s32 index;

    if (engine_obj.cur_character != 0) {
        despawn_object_permanently(OBJECT_HEADER(self));
        return;
    }
    self->state = 0;
    self->unk5 = 1;
    self->unk6 = 0;
    self->unk7 = 0;
    self->unk7C = 0x80;
    self->on_screen = 0;
    self->hp = 0;
    self->contact_damage = 6;
    self->invincibility_timer = 0;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    self->animation_table = (const u8* const*)double_animations;
    self->hurt_box = &double_hurt_box;
    self->attack_box = &double_attack_box;
    self->terrain_box = &double_terrain_box;
    self->collision_data = D_80108204;
    self->air_state = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk16 = VISUAL_SATURN_LAYER(4);
    self->ext.main_73.blink_delay = 0;
    self->ext.main_73.unk8A = 0;
    self->bg_offset = g_Player.bg_offset;
    index = func_8002938C(0x49);
    {
        struct MainObj* o = self;
        u32 tex = OBJECT_STAGE_TEXTURE(index);
        o->animation_table = (const u8* const*)double_animations;
        o->unk16 = VISUAL_SATURN_LAYER(4);
        o->unk40 = tex;
        set_animation(o, 0);
    }
}
#endif

// double_intro_warning
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_73_double", func_8008BB6C);
#else
void func_8008BB6C(struct MainObj* self)
{
    struct Main73Ext* ext = &self->ext.main_73;
    struct EffectObj* effect;

    if (g_Player.capsule_state != 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    switch (self->unk6) {
    case 0:
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            ext->unk80.effect = effect;
        }
        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
        self->unk6 = 1;
        self->unk7 = 0;
        break;
    case 1:
        effect = ext->unk80.effect;
        if (effect->active == 0) {
            self->unk6 = 2;
            self->contact_damage = 6;
            self->invincibility_timer = -0x80;
            self->hp = 0;
            self->unk62 = 0;
            self->unk63 = 2;
            self->unk7C = 0x20;
            engine_obj.enable_boss = 0;
            engine_obj.unk25 = 0;
            engine_obj.boss_ptr = self;
        }
        break;
    case 2:
        if (--self->unk7C == 0) {
            self->unk5 = 2;
            self->unk6 = 0;
            self->unk7 = 0;
        }
        break;
    }
    is_on_screen(BASE_OBJECT(self));
}
#endif

void double_intro_dialogue(struct MainObj* self)
{
    self->on_screen = 1;
    self->unk7C = 2;
    self->unk6++;
    func_8002217C(
        0x27, 0xFF, engine_obj.character_state.bytes[9]);
    engine_obj.character_state.bytes[9] = 1;
}

void double_intro_wait_dialogue(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        self->unk6++;
        engine_obj.enable_boss = 1;
        func_8001540C(2, SATURN_SOUND(0xF8, 0xD5), NULL);
    }
}

void double_intro_voice(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        play_boss_voice(0xA);
    }
    animate_object(ANIMATED_OBJECT(self));
}

void double_intro_fill_health(struct MainObj* self)
{

    if (update_boss_music_delay() == 0) {
        if (self->animation_step.fields.relative_step == 0) {
            if (self->hp < 0x30) {
                if (--self->unk7C == 0) {
                    func_8001540C(0, SATURN_SOUND(0xE, 0x14), 0);
                    self->unk7C = 2;
                }
                self->hp++;
                return;
            }
            self->state = 1;
            self->unk5 = 2;
            self->unk6 = 0;
            self->unk7 = 0;
            self->invincibility_timer = 0;
            self->ext.main_73.cycle_step = 0;
            player_end_script_action();
            return;
        }
        animate_object(ANIMATED_OBJECT(self));
    }
}

void double_intro_talk(struct MainObj* self)
{
    double_intro_talk_funcs[self->unk6](self);
    is_on_screen(BASE_OBJECT(self));
}

void double_intro(struct MainObj* self)
{
    double_intro_funcs[self->unk5](self);
}

void double_face_player(struct MainObj* self)
{
    if (self->collision_flags & 3) {
        if (self->collision_flags & 1) {
            self->unk15 = 0;
        } else {
            self->unk15 = PLAYER_FACING_RIGHT;
        }
    } else if ((self->x_pos.i.hi - g_Player.x_pos.i.hi) < 0) {
        self->unk15 = PLAYER_FACING_RIGHT;
    } else {
        self->unk15 = 0;
    }
}

void double_spawn_shot(struct MainObj* self, s32 arg1, s32 arg2)
{
    struct ShotObj* temp_v0;

    temp_v0 = find_free_shot_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x41;
        temp_v0->id = arg1 + 0x30;
        temp_v0->unk2 = arg2;
        temp_v0->x_pos.val = self->x_pos.val;
        temp_v0->y_pos.val = self->y_pos.val;
        temp_v0->animation_table = (u32**)self->animation_table;
        temp_v0->unk40 = self->unk40;
        temp_v0->unk3C = (u8*)self->sprite_frames;
        temp_v0->unk42 = self->unk42 & 0x7FFF;
        temp_v0->unk16 = self->unk16;
        temp_v0->unk7C = WEAPON_OBJECT(self);
        temp_v0->unk15 = self->unk15;
    }
}

void double_spawn_afterimage(struct MainObj* self, s8 arg1)
{
    struct MainObj* source;
    struct MiscObj* temp_v0;

    source = self;
    temp_v0 = find_free_misc_obj();
    if (temp_v0 != 0) {
        temp_v0->active = 0x41;
        temp_v0->id = 0x31;
        temp_v0->unk2 = arg1;
        temp_v0->x_pos.val = source->x_pos.val;
        temp_v0->y_pos.val = source->y_pos.val;
        temp_v0->animation_table = (u32**)source->animation_table;
        temp_v0->unk40 = source->unk40;
        temp_v0->unk3C = (u8*)source->sprite_frames;
        temp_v0->unk42 = source->unk42 & 0x7FFF;
        temp_v0->unk16 = source->unk16;
        temp_v0->ext.pointer.unk50 = source;
        temp_v0->unk15 = 0;
    }
}

void double_wait_start(struct MainObj* self)
{
    self->unk7 = 0;
    self->unk7C = 0x3C;
    self->unk6++;
    double_face_player(self);
    set_animation(self, 1);
}

// double_pick_attack
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_73_double", func_8008C10C);
#else
void func_8008C10C(struct MainObj* self)
{
    u8 frame;

    if (self->unk7C == 0) {
        if (self->ext.main_73.cycle_step == 0) {
            if (self->hp > 0x18) {
                self->ext.main_73.cycle_script = double_script_table_0[get_random() & 1];
            } else {
                self->ext.main_73.cycle_script = (u8*)double_script_table_1[get_random() & 1];
            }
        }
        frame = self->ext.main_73.cycle_script[++self->ext.main_73.cycle_step];
        self->unk5 = frame;
        if ((s8)frame == -1) {
            self->ext.main_73.cycle_step = 0;
            self->unk5 = 2;
        }
        self->unk6 = 0;
        self->unk7 = 0;
    } else {
        self->unk7C--;
        animate_object(ANIMATED_OBJECT(self));
    }
}
#endif

void double_wait(struct MainObj* self)
{
    double_wait_funcs[self->unk6](self);
}

void double_energy_ball_windup(struct MainObj* self)
{
    self->unk6++;
    set_animation(self, 3);
    func_8001540C(2, SATURN_SOUND(0xF4, 0xD1), NULL);
}

void double_spawn_shot(struct MainObj*, s32, s32);

void double_energy_ball_throw(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7C = 0x32;
        self->unk6++;
        double_face_player(self);
        return;
    }

    if (self->animation_step.fields.event != 0) {
        double_face_player(self);
        double_spawn_shot(self, 0, 0);
        func_8001540C(2, SATURN_SOUND(0xF5, 0xD2), 0);
    }

    animate_object(ANIMATED_OBJECT(self));
}

void double_energy_ball_recover(struct MainObj* self)
{
    s16 timer = self->unk7C;

    if (timer == 0) {
        self->unk5 = 2;
        self->unk6 = 1;
        self->unk7C = 0;
        double_face_player(self);
        return;
    }
    self->unk7C = timer - 1;
    animate_object(ANIMATED_OBJECT(self));
}

void double_energy_ball(struct MainObj* self)
{
    double_energy_ball_funcs[self->unk6](self);
}

void double_dive_leap(struct MainObj* self)
{
    self->unk6++;
    self->x_accel = 0;
    self->x_speed = 0;
    self->y_speed = FIXED(8);
    self->gravity = 0;
    self->contact_damage = 9;
    set_animation(self, 4);
    func_8001540C(2, SATURN_SOUND(0xF6, 0xD3), NULL);
}

void double_dive_rise(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (self->animation_step.fields.event != 0) {
        self->unk6++;
    }
}

void double_dive_climb(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 4) {
        self->unk6 += 1;
        set_animation(self, 5);
        func_8001540C(2, SATURN_SOUND(0xF7, 0xD4), NULL);
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
        animate_object(ANIMATED_OBJECT(self));
    }
}

void double_dive_aim(struct MainObj* self)
{
    u8 animation;

    if (self->animation_step.fields.relative_step < 0) {
        self->unk6++;
        self->animation_step.fields.event = 0;
        self->hurt_box = &double_dive_hurt_box;
        self->attack_box = &double_dive_attack_box;
        animation = angle_to_object(
                        OBJECT_HEADER(self), OBJECT_HEADER(&g_Player))
            | 0x10;
        if ((animation & 0xFF) < 0x14U) {
            animation = 0x14;
        }
        if ((animation & 0xFF) > 0x1C) {
            animation = 0x1C;
        }
        set_velocity_from_angle(MOVING_OBJECT(self), animation & 0xFF);
        self->gravity = 0;
        self->x_accel = 0;
        self->x_speed *= 8;
        self->y_speed *= 8;
        if ((self->x_pos.i.hi - g_Player.x_pos.i.hi) < 0) {
            self->unk15 = PLAYER_FACING_RIGHT;
        } else {
            self->unk15 = 0;
        }
        move_with_gravity(ANIMATED_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
}

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_73_double", double_dive_fall);
#else
void double_dive_fall(struct MainObj* self)
{
    s32 flags;
    u16 mask;

    flags = self->collision_flags;
    if (flags & 8) {
        self->unk6++;
        self->unk7C = 0x1E;
        set_animation(self, 6);
        self->hurt_box = &double_hurt_box;
        self->attack_box = &double_attack_box;
        func_8001540C(2, SATURN_SOUND(0xF1, 0xCE), 0);
        return;
    }

    if (self->unk15 != 0) {
        mask = 2;
    } else {
        mask = 1;
    }
    if (mask & flags) {
        self->x_speed = 0;
        self->x_accel = 0;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}
#endif

// double_dive_slide
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_73_double", func_8008C664);
#else
void func_8008C664(struct MainObj* self)
{
    s32 direction;
    u16 facing;

    if (--self->unk7C == 0) {
        self->unk6++;
        facing = 0;
        if (self->collision_flags & 3)
            facing = (self->collision_flags >> 1) & 1;
        else if (self->x_pos.i.hi - g_Player.x_pos.i.hi < 0)
            facing = 1;
        if (facing) {
            self->unk15 = PLAYER_FACING_RIGHT;
            direction = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
            if ((u8)(direction - 2) < 14)
                direction = 1;
            if ((u8)(direction - 0x11) < 15)
                direction = 0;
        } else {
            self->unk15 = 0;
            direction = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
            if ((u8)direction < 14)
                direction = 15;
            if ((u8)direction >= 17)
                direction = 16;
        }
        set_velocity_from_angle(MOVING_OBJECT(self), direction & 0xFF);
        self->gravity = 0;
        self->x_accel = 0;
        self->x_speed *= 8;
        self->y_speed *= 8;
        move_with_gravity(ANIMATED_OBJECT(self));
        set_animation(self, 7);
        self->hurt_box = &double_slide_hurt_box;
        self->attack_box = &double_slide_attack_box;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}
#endif

void double_dive_hit_wall(struct MainObj* self)
{
    if (self->collision_flags & 3) {
        self->unk6++;
        self->unk7C = 0x1E;
        start_screen_shake_x(8, 4, 2);
        set_animation(self, 8);
        self->hurt_box = (const u8*)&double_hurt_box;
        self->attack_box = (const u8*)&double_attack_box;
        func_8001540C(2, SATURN_SOUND(0xF7, 0xD4), 0);
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
        animate_object(ANIMATED_OBJECT(self));
    }
}

void double_dive_stun(struct MainObj* self)
{
    s16 timer = self->unk7C;

    if (timer == 0) {
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->x_accel = 0;
        self->x_speed = 0;
        self->unk6++;
        return;
    }
    self->unk7C = timer - 1;
    animate_object(ANIMATED_OBJECT(self));
}

void double_dive_land(struct MainObj* self)
{
    if (self->collision_flags & 8) {
        self->unk5 = 2;
        self->unk6 = 1;
        self->unk7C = 0;
        self->contact_damage = 6;
        double_face_player(self);
        func_8001540C(2, SATURN_SOUND(0xF1, 0xCE), NULL);
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

void double_dive(struct MainObj* self)
{
    double_dive_funcs[self->unk6](self);
}

void double_aerial_shot_jump(struct MainObj* self)
{
    self->unk6++;
    self->y_speed = FIXED(5);
    self->x_accel = 0;
    self->x_speed = 0;
    self->gravity = FIXED(0.2578125);
    self->ext.main_73.shot_count = 0;
    set_animation(self, 2);
}

void double_aerial_shot_fire(struct MainObj* self)
{
    if (self->y_speed < 0) {
        self->unk6++;
        self->unk7C = 0x32;
        set_animation(self, 9);
        double_spawn_shot(self, 1, 0);
        self->ext.main_73.shot_count++;
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

void double_aerial_shot_hang(struct MainObj* self)
{
    s16 timer;

    timer = self->unk7C;
    if (timer == 0) {
        set_animation(self, 0xA);
        if (self->ext.main_73.shot_count < 2) {
            self->unk6 += 1;
            self->unk7C = 0x14;
            self->x_speed = 0;
            self->x_accel = 0;
            self->y_speed = 0;
            self->gravity = FIXED(0.2578125);
            set_animation(self, 2);
            self->ext.main_73.effect.position.x = self->x_pos.u.hi;
            self->ext.main_73.effect.position.y = self->y_pos.u.hi + 0x28;
            return;
        }
        self->unk6 += 3;
        self->unk7C = 0x1E;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        return;
    }
    self->unk7C = timer - 1;
    animate_object(ANIMATED_OBJECT(self));
}

void double_aerial_shot_fire_again(struct MainObj* arg)
{
    struct MainObj* self;
    s16 targetY;

    self = arg;

    if (--self->unk7C == 0) {
        self->unk6 = 2;
        *(volatile u16*)&self->unk7C = 0;
        self->unk7C = 0x32;
        set_animation(self, 9);
        double_spawn_shot(self, 1, 1);
        self->ext.main_73.shot_count++;
        return;
    }

    targetY = (s16)self->ext.main_73.effect.position.y;
    if (targetY > self->y_pos.i.hi) {
        if (self->y_speed < FIXED(-4)) {
            self->y_speed = FIXED(-4);
            self->gravity = 0;
        }
        move_with_gravity(ANIMATED_OBJECT(self));
    } else {
        self->y_pos.i.hi = targetY;
    }
    animate_object(ANIMATED_OBJECT(self));
}

// double_aerial_shot_wait
void func_8008CBF8(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk6 = 2;
        *(volatile s16*)&self->unk7C = 0;
        self->unk7C = 0x5A;
        set_animation(self, 9);
        double_spawn_shot(self, 1, 1);
        self->ext.main_73.shot_count++;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void double_aerial_shot_drop(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk6++;
        set_animation(self, 2);
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void double_aerial_shot_land(struct MainObj* self)
{
    if (self->collision_flags & 8) {
        self->unk5 = 2;
        self->unk6 = 1;
        self->unk7C = 0;
        double_face_player(self);
        set_animation(self, 1);
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

void double_aerial_shot(struct MainObj* self)
{
    double_aerial_shot_funcs[self->unk6](self);
}

// double_run
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_73_double", func_8008CD80);
#else
void func_8008CD80(struct MainObj* self)
{
    s32 collision;

    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    double_step_funcs[self->unk5](self);
    CollisionRelated(PLAYER_OBJECT(self));
    collision = func_8002DD04(self);

    if (self->ext.main_73.blink_delay != 0) {
        if (--self->ext.main_73.blink_delay == 0) {
            self->collision_data = D_80108204;
            self->unk42 &= 0x7FFF;
        } else if (self->ext.main_73.blink_delay & 1) {
            self->unk42 |= 0x8000;
        } else {
            self->unk42 &= 0x7FFF;
        }
    } else if (collision < 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
        self->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
    } else if (collision > 0 && collision != 0x7F) {
        self->collision_data = D_801060F0;
        if ((u32)(collision - 0x13) < 2 || (u32)(collision - 0x15) < 2 || collision == 0x17) {
            self->ext.main_73.blink_delay = 0x40;
        } else {
            self->ext.main_73.blink_delay = 0x40;
            if (get_random() & 1) {
                double_spawn_shot(self, 2, 0);
                double_spawn_shot(self, 2, 1);
            } else {
                double_spawn_shot(self, 3, 0);
                double_spawn_shot(self, 3, 1);
            }
            double_spawn_afterimage(self, 0);
            double_spawn_afterimage(self, 1);
            double_spawn_afterimage(self, 2);
            double_spawn_afterimage(self, 3);
        }
    }
    func_8002D9BC(self);
    is_on_screen(BASE_OBJECT(self));
}
#endif

void double_death_flicker(struct MainObj* self)
{
    s16 timer = self->unk7C, next_timer = timer;
    if (timer == 0) {
        next_timer = 0x10;
        self->unk42 = self->unk42 | 0x8000;
        self->unk7C = next_timer;
    } else {
        next_timer--;
        self->unk7C = next_timer;
        self->unk42 = self->unk42 & 0x7FFF;
    }
}

void double_death_start(struct MainObj* self)
{
    u8 var_a1;

    if ((self->x_pos.val - g_Player.x_pos.val) < 0) {
        var_a1 = 0;
        self->unk15 = PLAYER_FACING_RIGHT;
    } else {
        var_a1 = PLAYER_FACING_RIGHT;
        self->unk15 = 0;
    }
    player_start_script_action(0x14, var_a1);
    self->unk5 = 1;
    self->x_accel = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->gravity = FIXED(0.2578125);
    self->unk7C = 0x10;
    self->unk7E = 0x10;
    self->unk42 &= 0x7FFF;
    set_animation(self, 0xB);
    is_on_screen(BASE_OBJECT(self));
}

void double_death_fall(struct MainObj* self)
{
    double_death_flicker(self);
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->unk5 = 2;
        self->gravity = 0;
        self->y_speed = 0;
        set_animation(self, 0);
        self->unk7E = 0x3C;
        set_animation(self, 0x1E);
    }
    CollisionRelated(PLAYER_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void double_death_wait(struct MainObj* self)
{
    double_death_flicker(self);
    if (--self->unk7E == 0) {
        self->unk5 = 3;
        func_8002217C(0x28, 5, 0);
        engine_obj.enable_boss = 0;
    }
    is_on_screen(BASE_OBJECT(self));
}

void double_death_wait_dialogue(struct MainObj* self)
{
    double_death_flicker(self);
    if (abc_object.unkC == 0) {
        self->unk5 = 4;
        self->unk7C = 0x19;
        self->ext.main_73.blink_delay = 0x19;
        self->unk42 &= 0x7FFF;
    }
    is_on_screen(BASE_OBJECT(self));
}

void double_death_blink(struct MainObj* self)
{
    struct EffectObj* effect;
    if (--self->unk7C == 0) {
        self->unk5 = 5;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.u.hi = self->x_pos.u.hi;
            effect->y_pos.u.hi = self->y_pos.u.hi;
            self->ext.main_73.unk80.effect = effect;
        }
    }
    is_on_screen(BASE_OBJECT(self));
    if (self->unk7E-- == 0) {
        u8 unk8B;
        unk8B = self->ext.main_73.blink_delay;
        self->unk42 ^= 0x8000;
        unk8B -= 5;
        self->ext.main_73.blink_delay = unk8B;
        if (unk8B > 0x19) {
            self->ext.main_73.blink_delay = 0;
        }
        self->unk7E = self->ext.main_73.blink_delay > 5 ? self->ext.main_73.blink_delay : 5;
    }
}

void double_death_wait_explosion(struct MainObj* self)
{
    s8* script = self->ext.main_73.unk80.script;

    self->on_screen = 0;
    if (*script != 0) {
        if (script[7] == 0) {
            if (self->unk7E-- == 0) {
                self->unk7E = 5;
                self->unk42 ^= 0x8000;
            }
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        self->unk7C = 1;
        self->unk5 = 6;
    }
}

void double_death_finish(struct MainObj* self)
{
    self->unk7C -= 1;
    if (self->unk7C == 0) {
        engine_obj.unkF = 1;
        ZeroObjectState(OBJECT_HEADER(self));
    }
}

void double_death(struct MainObj* self)
{
    double_death_funcs[self->unk5](self);
}

void double_update(struct MainObj* self)
{
    double_state_funcs[self->state](self);
}

union AnimationStep double_anim_0[] = {
    { 8, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 6, 0, 1, 0x02 },
    { 6, 0, 1, 0x03 },
    { 3, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 2, 0, 1, 0x05 },
    { 3, 0, 1, 0x06 },
    { 3, 0, 1, 0x07 },
    { 6, 0, 1, 0x08 },
    { 8, 0, 1, 0x09 },
    { 4, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0A },
    { 1, 0, 1, 0x0B },
    { 1, 0, 1, 0x0A },
    { 1, 0, 1, 0x0B },
    { 1, 0, 1, 0x0A },
    { 1, 0, 1, 0x0B },
    { 36, 0, 1, 0x0A },
    { 1, 0, 0, 0x0A },
};

struct Unk_unk68 double_anim_1[4] = {
    { 12, 0, 1, 12 },
    { 10, 0, 1, 13 },
    { 12, 0, 1, 14 },
    { 10, 0, -3, 13 },
};

struct Unk_unk68 double_anim_2[6] = {
    { 3, 0, 1, 15 },
    { 6, 0, 1, 16 },
    { 12, 0, 1, 19 },
    { 10, 0, 1, 20 },
    { 12, 0, 1, 21 },
    { 10, 0, -3, 20 },
};

union AnimationStep double_anim_3[] = {
    { 3, 0, 1, 0x0F },
    { 5, 0, 1, 0x10 },
    { 4, 0, 1, 0x16 },
    { 12, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 1, 1, 1, 0x19 },
    { 1, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 12, 0, 0, 0x1B },
};

u8 double_anim_4[16] = { 3, 0, 1, 15, 6, 0, 1, 16, 2, 1, 1, 17, 2, 0, 255, 18 };

struct Unk_unk68 double_anim_5[7] = {
    { 4, 0, 1, 28 },
    { 12, 0, 1, 29 },
    { 2, 0, 1, 30 },
    { 2, 1, 1, 31 },
    { 1, 0, 1, 32 },
    { 1, 0, 1, 33 },
    { 1, 0, -2, 34 },
};

union AnimationStep double_anim_6[] = {
    { 4, 0, 1, 0x23 },
    { 12, 0, 0, 0x24 },
};

struct Unk_unk68 double_anim_7[5] = {
    { 2, 0, 1, 37 },
    { 2, 1, 1, 38 },
    { 1, 0, 1, 39 },
    { 1, 0, 1, 40 },
    { 1, 0, -2, 41 },
};

union AnimationStep double_anim_8[] = {
    { 2, 0, 1, 0x2A },
    { 3, 0, 0, 0x13 },
};

u8 double_anim_9[8] = { 2, 0, 1, 43, 2, 0, 255, 44 };

union AnimationStep double_anim_10[] = {
    { 2, 0, 1, 0x2D },
    { 2, 0, 1, 0x2E },
    { 2, 0, 1, 0x2D },
    { 2, 0, 1, 0x2E },
    { 1, 0, 1, 0x2D },
    { 1, 0, 1, 0x2E },
    { 1, 0, 1, 0x2D },
    { 1, 0, 1, 0x2E },
    { 1, 0, 1, 0x2D },
    { 1, 0, 1, 0x2E },
    { 18, 0, 0, 0x2D },
};

union AnimationStep double_anim_11[] = {
    { 4, 0, 1, 0x32 },
    { 3, 0, 1, 0x31 },
    { 2, 0, 1, 0x30 },
    { 2, 0, 1, 0x2F },
    { 1, 0, 1, 0x30 },
    { 1, 0, 1, 0x2F },
    { 1, 0, 1, 0x30 },
    { 8, 0, 0, 0x2F },
};

struct Unk_unk68 double_anim_12[4] = {
    { 1, 0, 1, 51 },
    { 1, 0, 1, 52 },
    { 1, 0, 1, 53 },
    { 1, 0, -3, 54 },
};

union AnimationStep double_anim_13[] = {
    { 1, 0, 1, 0x37 },
    { 2, 0, 1, 0x38 },
    { 3, 0, 1, 0x39 },
    { 4, 0, 0, 0x3A },
};

u8 double_anim_14[8] = { 2, 0, 1, 59, 2, 0, 255, 60 };

u8 double_anim_15[8] = { 2, 0, 1, 61, 2, 0, 255, 62 };

struct Unk_unk68 double_anim_16[5] = {
    { 2, 0, 1, 63 },
    { 2, 0, 1, 64 },
    { 1, 0, 1, 65 },
    { 1, 0, 1, 66 },
    { 1, 0, -2, 67 },
};

union AnimationStep double_anim_17[] = {
    { 2, 0, 1, 0x44 },
    { 3, 0, 1, 0x45 },
    { 3, 0, 1, 0x46 },
    { 3, 0, 1, 0x47 },
    { 3, 0, 1, 0x48 },
    { 2, 0, 1, 0x46 },
    { 2, 0, 1, 0x47 },
    { 2, 0, 1, 0x48 },
    { 1, 0, 1, 0x46 },
    { 1, 0, 1, 0x47 },
    { 1, 0, 1, 0x48 },
    { 1, 0, 1, 0x46 },
    { 1, 0, 1, 0x47 },
    { 1, 0, 1, 0x48 },
    { 24, 0, 0, 0x46 },
};

u8 double_anim_18[8] = { 3, 0, 1, 73, 3, 0, 255, 74 };

u8 double_anim_19[8] = { 3, 0, 1, 75, 3, 0, 255, 76 };

struct Unk_unk68 double_anim_20[8] = {
    { 4, 0, 1, 70 },
    { 4, 0, 1, 77 },
    { 6, 0, 1, 78 },
    { 4, 0, 1, 77 },
    { 4, 0, 1, 70 },
    { 4, 0, 1, 79 },
    { 6, 0, 1, 80 },
    { 4, 0, -7, 79 },
};

#ifdef MMX4_PC

union AnimationStep double_mine_animation_steps[] = {
    { 6, 0, 1, 0x51 },
    { 4, 0, 1, 0x52 },
    { 3, 0, 1, 0x53 },
    { 2, 0, 1, 0x54 },
    { 18, 0, 0, 0x58 },
    { 2, 0, 1, 0x58 },
    { 1, 0, 1, 0x59 },
    { 1, 0, 1, 0x5A },
    { 1, 0, 1, 0x5B },
    { 1, 1, 1, 0x5C },
    { 2, 0, 1, 0x5D },
    { 2, 0, 1, 0x5E },
    { 2, 0, 0, 0x5F },
};
#define double_anim_21 (double_mine_animation_steps)
#define double_anim_22 (double_mine_animation_steps + 5)
#else
union AnimationStep double_anim_21[] = {
    { 6, 0, 1, 0x51 },
    { 4, 0, 1, 0x52 },
    { 3, 0, 1, 0x53 },
    { 2, 0, 1, 0x54 },
    { 18, 0, 0, 0x58 },
};

union AnimationStep double_anim_22[] = {
    { 2, 0, 1, 0x58 },
    { 1, 0, 1, 0x59 },
    { 1, 0, 1, 0x5A },
    { 1, 0, 1, 0x5B },
    { 1, 1, 1, 0x5C },
    { 2, 0, 1, 0x5D },
    { 2, 0, 1, 0x5E },
    { 2, 0, 0, 0x5F },
};
#endif

struct Unk_unk68 double_anim_23[3] = {
    { 1, 0, 1, 96 },
    { 1, 0, 1, 97 },
    { 1, 0, -2, 98 },
};

union AnimationStep double_anim_24[] = {
    { 5, 0, 1, 0x55 },
    { 4, 0, 1, 0x56 },
    { 3, 0, 1, 0x57 },
    { 12, 0, 0, 0x63 },
};

struct Unk_unk68 double_anim_25[3] = {
    { 1, 0, 1, 99 },
    { 1, 0, 1, 100 },
    { 1, 0, -2, 101 },
};

union AnimationStep double_anim_26[] = {
    { 2, 0, 0, 0x66 },
};

union AnimationStep double_anim_27[] = {
    { 2, 0, 0, 0x67 },
};

union AnimationStep double_anim_28[] = {
    { 2, 0, 0, 0x68 },
};

union AnimationStep double_anim_29[] = {
    { 2, 0, 0, 0x69 },
};

union AnimationStep double_anim_30[] = {
    { 2, 0, 0, 0x6A },
};

void* double_animations[31] = {
    double_anim_0,
    double_anim_1,
    double_anim_2,
    double_anim_3,
    double_anim_4,
    double_anim_5,
    double_anim_6,
    double_anim_7,
    double_anim_8,
    double_anim_9,
    double_anim_10,
    double_anim_11,
    double_anim_12,
    double_anim_13,
    double_anim_14,
    double_anim_15,
    double_anim_16,
    double_anim_17,
    double_anim_18,
    double_anim_19,
    double_anim_20,
    double_anim_21,
    double_anim_22,
    double_anim_23,
    double_anim_24,
    double_anim_25,
    double_anim_26,
    double_anim_27,
    double_anim_28,
    double_anim_29,
    double_anim_30,
};

struct Unk_unk68 double_attack_box = { -9, -36, 29, 54 };

struct Unk_unk68 double_hurt_box = { -14, -41, 35, 59 };

struct Unk_unk68 double_terrain_box = { 0, 0, 19, 19 };

struct Unk_unk68 double_dive_attack_box = { -5, -23, 20, 84 };

struct Unk_unk68 double_dive_hurt_box = { -14, -53, 32, 79 };

struct Unk_unk68 double_slide_attack_box = { -57, -11, 90, 23 };

struct Unk_unk68 double_slide_hurt_box = { -27, -8, 85, 30 };

u8 double_script_0_0[8] = { 2, 3, 2, 4, 255, 0, 0, 0 };

u8 double_script_0_1[8] = { 2, 4, 2, 4, 255, 0, 0, 0 };

u8 double_script_1_0[8] = { 2, 3, 3, 2, 4, 255, 0, 0 };

union AnimationStep double_script_1_1[] = {
    { 2, 4, 2, 0x04 },
    { 5, -1, 0, 0x00 },
};

u8* double_script_table_0[2] = {
    double_script_0_0,
    double_script_0_1,
};

void* double_script_table_1[2] = {
    double_script_1_0,
    double_script_1_1,
};

void (*double_intro_talk_funcs[4])(struct MainObj*) = {
    double_intro_dialogue,
    double_intro_wait_dialogue,
    double_intro_voice,
    double_intro_fill_health,
};

void (*double_intro_funcs[3])() = {
    func_8008BA38,
    func_8008BB6C,
    double_intro_talk,
};

void (*double_wait_funcs[2])() = {
    double_wait_start,
    func_8008C10C,
};

void (*double_energy_ball_funcs[3])() = {
    double_energy_ball_windup,
    double_energy_ball_throw,
    double_energy_ball_recover,
};

void (*double_dive_funcs[9])() = {
    double_dive_leap,
    double_dive_rise,
    double_dive_climb,
    double_dive_aim,
    double_dive_fall,
    func_8008C664,
    double_dive_hit_wall,
    double_dive_stun,
    double_dive_land,
};

void (*double_aerial_shot_funcs[7])() = {
    double_aerial_shot_jump,
    double_aerial_shot_fire,
    double_aerial_shot_hang,
    double_aerial_shot_fire_again,
    func_8008CBF8,
    double_aerial_shot_drop,
    double_aerial_shot_land,
};

void (*double_step_funcs[6])() = {
    enemy_hit_reaction,
    enemy_hit_reaction,
    double_wait,
    double_energy_ball,
    double_dive,
    double_aerial_shot,
};

void (*double_death_funcs[7])(struct MainObj*) = {
    double_death_start,
    double_death_fall,
    double_death_wait,
    double_death_wait_dialogue,
    double_death_blink,
    double_death_wait_explosion,
    double_death_finish,
};

void (*double_state_funcs[3])() = {
    double_intro,
    func_8008CD80,
    double_death,
};
