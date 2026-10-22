// MainObj, main_object_update_funcs[64]
// 8007C30C..8007DC54
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_64_cyber_peacock.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/player_common.h"
#include "main/128C4.h"
#include "main/55C4.h"
#include "main/1E1BC.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#endif

extern struct Unk_unk68 cyber_peacock_rising_kick_attack_box;
extern struct Unk_unk68 cyber_peacock_rising_kick_hurt_box;
extern struct Unk_unk68 cyber_peacock_slash_attack_box;
extern struct Unk_unk68 cyber_peacock_slash_hurt_box;
extern struct Unk_unk68 cyber_peacock_slash_swing_attack_box;
extern struct Unk_unk68 cyber_peacock_slash_swing_hurt_box;

extern u8 cyber_peacock_attacks[32];
extern u8 cyber_peacock_attacks_low_health[32];

// cyber_peacock_intro_appear_funcs
extern void (*cyber_peacock_intro_appear_funcs[])(struct MainObj*);

// cyber_peacock_intro_funcs
extern void (*cyber_peacock_intro_funcs[])(struct MainObj*);

// cyber_peacock_teleport_funcs
extern void (*cyber_peacock_teleport_funcs[])(struct MainObj*);

// cyber_peacock_rising_kick_funcs
extern void (*cyber_peacock_rising_kick_funcs[])(struct MainObj*);

// cyber_peacock_slash_funcs
extern void (*cyber_peacock_slash_funcs[])(struct MainObj*);

// cyber_peacock_aiming_laser_funcs
extern void (*cyber_peacock_aiming_laser_funcs[])(struct MainObj*);

// cyber_peacock_attack_funcs
extern void (*cyber_peacock_attack_funcs[])(struct MainObj*);

// cyber_peacock_death_funcs
extern void (*cyber_peacock_death_funcs[])(struct BarObj*);

// cyber_peacock_state_funcs
extern void (*cyber_peacock_state_funcs[])(struct MainObj*);

// cyber_peacock_intro_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007C30C(struct MainObj* arg0);
void func_8007CA68(struct MainObj* arg0);
void func_8007D5D0(struct MainObj* arg0);
void func_8007D710(struct MainObj* arg0);
void func_8007D838(struct MainObj* arg0);
extern struct Unk_unk68 cyber_peacock_intro_hurt_box;
extern struct Unk_unk68 D_80107CFC[];
extern u8 cyber_peacock_attack_animations[];
extern u8 cyber_peacock_attack_steps[];
void cyber_peacock_face_player(struct MainObj* arg0);
u8 cyber_peacock_choose_attack(struct MainObj* arg0);
void cyber_peacock_start_teleport(struct MainObj* arg0);
extern void (*cyber_peacock_step_funcs[6])();
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007C30C(struct MainObj* arg0)
{
    arg0->unk7C = 0x80;
    arg0->contact_damage = 5;
    arg0->animation_table = (const u8* const*)cyber_peacock_animations;
    arg0->hurt_box = &cyber_peacock_intro_hurt_box;
    arg0->attack_box = &cyber_peacock_hit_box;
    arg0->collision_data = D_80107CFC;
    arg0->state = 0;
    arg0->unk5 = 1;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
    arg0->on_screen = 0;
    arg0->unk2 = 0;
    arg0->hp = 0;
    arg0->invincibility_timer = 0;
    arg0->ext.main_64.saved_health = 0;
    arg0->ext.main_64.flash_timer = 0;
    arg0->ext.main_64.force_laser = 0;
    arg0->ext.main_64.hit_count = 0;
    arg0->terrain_box = NULL;
    arg0->air_state = 0;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->unk16 = 3;
    arg0->ext.main_64.shot_count = 0;
    arg0->ext.main_64.unk8A = 0;
    arg0->ext.main_64.skip_attack = 1;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    engine_obj.character_state.bytes[7] = 0;
    if (engine_obj.stage == 6) {
        arg0->ext.main_64.arena_x = 0x3E0;
        arg0->ext.main_64.arena_y = 0x900;
    } else {
        arg0->ext.main_64.arena_x = 0x410;
        arg0->ext.main_64.arena_y = 0x600;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_64_cyber_peacock", func_8007C30C);
#endif

void cyber_peacock_intro_wait_player(struct MainObj* self)
{
    struct EffectObj* effect;
    s32* archive;

    if (g_Player.capsule_state != 0) {
        return;
    }
    switch (self->unk6) {
    case 0:
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            self->ext.main_64.object = effect;
        }
        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
        self->unk6 = 1;
        self->unk7 = 0;
        break;
    case 1:
        effect = self->ext.main_64.object;
        if (effect->active != 0) {
            break;
        }
        self->unk6 = 2;
        self->bg_offset = g_Player.bg_offset;
        if (engine_obj.stage != 0xC) {
            self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0xB0);
        } else {
            self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0x160);
            self->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[4];
            self->unk42 = OBJECT_CLUT(0x7888);
        }
        self->animation_table = (const u8* const*)cyber_peacock_animations;
        self->unk16 = VISUAL_SATURN_LAYER(4);
        self->hp = 0;
        self->contact_damage = 5;
        self->invincibility_timer = -0x80;
        self->unk62 = 0;
        self->unk63 = 2;
        self->unk7C = 0x20;
        engine_obj.enable_boss = 0;
        engine_obj.unk25 = 0;
        engine_obj.boss_ptr = self;
        break;
    case 2:
        if (--self->unk7C == 0) {
            self->unk5 = 2;
            self->unk6 = 0;
            self->unk7 = 0;
        }
        break;
    }
}

void cyber_peacock_intro_appear_start(struct MainObj* self)
{
    self->on_screen = 1;
    self->unk6++;
    set_animation(self, 0);
}

void cyber_peacock_intro_pose(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7C = 2;
        self->unk6 += 1;
        if (engine_obj.stage == 6) {
            func_8002217C(
                0xE, 0xFF, engine_obj.character_state.bytes[8]);
            engine_obj.character_state.bytes[8] = 1;
        }
    } else {
        if (self->animation_step.fields.event != 0) {
            self->animation_step.fields.event = 0;
            func_8001540C(2, SATURN_SOUND(0xC1, 0x88), self);
        }
        animate_object(ANIMATED_OBJECT(self));
    }
}

void cyber_peacock_intro_start_health_bar(struct MainObj* self)
{
    if (abc_object.unkC == 0) {
        self->unk6++;
        set_animation(self, 1);
        engine_obj.enable_boss = 1;
        play_boss_voice(5);
    }
}

void cyber_peacock_intro_fill_health(struct MainObj* self)
{
    s8 health;

    if (update_boss_music_delay() != 0) {
        return;
    }
    if (self->animation_step.fields.relative_step == 0) {
        health = self->hp;
        if (health < 0x30) {
            if (--self->unk7C == 0) {
                func_8001540C(0, SATURN_SOUND(0xE, 0x14), 0);
                self->unk7C = 2;
            }
            self->hp++;
            return;
        }
        self->ext.main_64.saved_health = health;
        self->state = 1;
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
        self->invincibility_timer = 0;
        player_end_script_action();
        return;
    }
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        func_8001540C(2, SATURN_SOUND(0xC2, 0x89), self);
    }
    animate_object(ANIMATED_OBJECT(self));
}

void cyber_peacock_intro_appear(struct MainObj* self)
{
    cyber_peacock_intro_appear_funcs[self->unk6](self);
    is_on_screen(BASE_OBJECT(self));
}

void cyber_peacock_intro(struct MainObj* self)
{
    cyber_peacock_intro_funcs[self->unk5](self);
}

void cyber_peacock_face_player(struct MainObj* self)
{
    if ((self->x_pos.val - g_Player.x_pos.val) < 0) {
        self->unk15 = PLAYER_FACING_RIGHT;
    } else {
        self->unk15 = 0;
    }
}

u8 cyber_peacock_choose_attack(struct MainObj* self)
{
    if (self->ext.main_64.skip_attack == 0) {
        if (self->ext.main_64.force_laser == 0) {
            if (self->hp < 0x18) {
                return cyber_peacock_attacks_low_health[get_random() & 0x1F];
            }
            return cyber_peacock_attacks[get_random() & 0x1F];
        }
        return 3;
    }
    return 0;
}

void cyber_peacock_start_teleport(struct MainObj* self)
{
    self->ext.main_64.target_x = self->x_pos.u.hi;
    self->ext.main_64.target_y = self->y_pos.u.hi;
    self->x_speed = 0;
    self->x_accel = FIXED(1);
    self->y_speed = 0;
    self->gravity = 0;
    self->hurt_box = NULL;
    self->attack_box = NULL;
    func_8001540C(2, SATURN_SOUND(0xC6, 0x8D), self);
}

void cyber_peacock_teleport_start(struct MainObj* self)
{
    cyber_peacock_start_teleport(self);
    self->unk6++;
    self->unk7 = 0;
    set_animation(self, 2);
    self->ext.main_64.skip_attack = 0;
}

void cyber_peacock_teleport_vanish(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        self->unk7 = 0;
        self->unk7C = 0x50;
        set_animation(self, 0x22);
        self->contact_damage = 5;
        return;
    }
    self->x_speed += self->x_accel;
    if (SHAKE_ENABLED) {
        if (BLINK_CLOCK(BLINK_CLOCK(WEAPON_FRAME_COUNTER)) & 1) {
            self->x_pos.val = ((s16)self->ext.main_64.target_x << 0x10) + self->x_speed;
        } else {
            self->x_pos.val = ((s16)self->ext.main_64.target_x << 0x10) - self->x_speed;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

// cyber_peacock_teleport_choose
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007CA68(struct MainObj* arg0)
{
    s16 timer = --arg0->unk7C;
    u8 attack;
    s16 base;

    if (timer != 0) {
        if (timer == 0x14) {
            arg0->ext.main_64.target_x = g_Player.x_pos.i.hi;
            arg0->ext.main_64.target_y = g_Player.y_pos.i.hi - 0x18;
        }
        animate_object(ANIMATED_OBJECT(arg0));
        return;
    }
    arg0->unk7 = 0;
    arg0->unk6++;
    arg0->x_pos.i.hi = arg0->ext.main_64.target_x;
    arg0->y_pos.i.hi = arg0->ext.main_64.target_y;
    cyber_peacock_face_player(arg0);
    attack = cyber_peacock_choose_attack(arg0);
    arg0->ext.main_64.next_step = cyber_peacock_attack_steps[attack];
    set_animation(arg0, cyber_peacock_attack_animations[attack]);
    arg0->unk2 = attack;
    if (attack == 0) {
        func_8001540C(2, SATURN_SOUND(0xC7, 0x8E), arg0);
        return;
    }
    base = arg0->ext.main_64.arena_x;
    switch ((s8)attack) {
    case 1:
        arg0->y_pos.i.hi = arg0->ext.main_64.arena_y + 0xB3;
        arg0->ext.main_64.target_y = arg0->y_pos.i.hi;
        func_8001540C(2, SATURN_SOUND(0xC7, 0x8E), arg0);
        break;
    case 2:
        if (g_Player.x_pos.i.hi - base < 0xA0) {
            arg0->x_pos.i.hi = base + 0x90;
            arg0->unk15 = PLAYER_FACING_RIGHT;
        } else {
            arg0->x_pos.i.hi = base + 0xE0;
            arg0->unk15 = 0;
        }
        arg0->ext.main_64.target_x = arg0->x_pos.i.hi;
        arg0->y_pos.i.hi = arg0->ext.main_64.arena_y + 0xB3;
        arg0->ext.main_64.target_y = arg0->y_pos.i.hi;
        break;
    case 3:
        if (g_Player.x_pos.i.hi - base < 0xA0) {
            arg0->x_pos.i.hi = base + 0x110;
            arg0->unk15 = 0;
        } else {
            arg0->x_pos.i.hi = base + 0x50;
            arg0->unk15 = PLAYER_FACING_RIGHT;
        }
        arg0->ext.main_64.target_x = arg0->x_pos.i.hi;
        arg0->y_pos.i.hi = arg0->ext.main_64.arena_y + 0x70;
        arg0->ext.main_64.target_y = arg0->y_pos.i.hi;
        break;
    }
    arg0->unk2--;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_64_cyber_peacock", func_8007CA68);
#endif

void cyber_peacock_teleport_appear(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        self->unk7 = 0;
        self->unk7C = 0x14;
        self->hurt_box = (const u8*)&cyber_peacock_hit_box;
        self->attack_box = (const u8*)&cyber_peacock_hit_box;
        self->contact_damage = 5;
        func_8001540C(2, SATURN_SOUND(0xC6, 0x8D), self);
        return;
    }

    self->x_speed -= self->x_accel;
    if (SHAKE_ENABLED) {
        if (BLINK_CLOCK(BLINK_CLOCK(WEAPON_FRAME_COUNTER)) & 1) {
            self->x_pos.val = ((s16)self->ext.main_64.target_x << 0x10) + self->x_speed;
        } else {
            self->x_pos.val = ((s16)self->ext.main_64.target_x << 0x10) - self->x_speed;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void cyber_peacock_teleport_wait(struct MainObj* self)
{

    if (--self->unk7C == 0) {
        self->unk5 = self->ext.main_64.next_step;
        self->unk6 = 0;
        self->unk7 = 0;
        self->ext.main_64.hit_count = 0;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void cyber_peacock_teleport(struct MainObj* self)
{
    cyber_peacock_teleport_funcs[self->unk6](self);
}

void cyber_peacock_rising_kick_start(struct MainObj* self)
{
    self->unk6++;
    set_animation(self, 4);
    self->hurt_box = (const u8*)&cyber_peacock_rising_kick_hurt_box;
    self->attack_box = (const u8*)&cyber_peacock_rising_kick_attack_box;
    self->contact_damage = 6;
}

void cyber_peacock_rising_kick_jump(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->air_state = 1;
        self->x_speed = 0;
        self->unk6++;
        self->x_accel = 0;
        self->y_speed = FIXED(8);
        self->gravity = FIXED(0.34375);
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void cyber_peacock_rising_kick_rise(struct MainObj* self)
{
    if (self->y_speed < 0) {
        self->unk6++;
        set_animation(self, 5);
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

void cyber_peacock_rising_kick_finish(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 2;
        self->unk6 = 1;
        cyber_peacock_start_teleport(self);
        self->x_speed = FIXED(22);
        self->air_state = 0;
        set_animation(self, 0x22);
        self->contact_damage = 5;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void cyber_peacock_rising_kick(struct MainObj* self)
{
    cyber_peacock_rising_kick_funcs[self->unk6](self);
}

void cyber_peacock_slash_start(struct MainObj* self)
{
    self->unk7C = 0;
    self->unk6++;
    set_animation(self, 6);
    func_8001540C(2, SATURN_SOUND(0xC9, 0x90), self);
    self->hurt_box = (const u8*)&cyber_peacock_slash_hurt_box;
    self->attack_box = (const u8*)&cyber_peacock_slash_attack_box;
    self->contact_damage = 9;
}

void cyber_peacock_slash_swing(struct MainObj* self)
{
    u16 counter;

    if (self->animation_step.fields.relative_step < 0) {
        counter = ++self->unk7C;
        if ((s16)counter > 3) {
            self->unk6 += 1;
            set_animation(self, 7);
            self->hurt_box = (const u8*)&cyber_peacock_slash_hurt_box;
            self->attack_box = (const u8*)&cyber_peacock_slash_attack_box;
            return;
        }
    } else if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        self->hurt_box = (const u8*)&cyber_peacock_slash_swing_hurt_box;
        self->attack_box = (const u8*)&cyber_peacock_slash_swing_attack_box;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void cyber_peacock_slash_finish(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 2;
        self->unk6 = 1;
        cyber_peacock_start_teleport(self);
        self->x_speed = FIXED(22);
        set_animation(self, 0x22);
        self->contact_damage = 5;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void cyber_peacock_slash(struct MainObj* self)
{
    cyber_peacock_slash_funcs[self->unk6](self);
}

void cyber_peacock_spawn_laser_target(struct MainObj* self)
{
    s8 active;

    struct ItemObj* item = find_free_item_obj();
    if (item != NULL) {
        active = self->active;
        item->id = 0x17;
        item->active = active;
        item->unk2 = self->ext.main_64.shot_count;
        item->x_pos.val = self->x_pos.val;
        item->y_pos.val = self->y_pos.val;
        item->animation_table = (void*)self->animation_table;
        item->unk40 = self->unk40;
        item->sprite_frames = (void*)self->sprite_frames;
        item->unk42 = self->unk42 & 0x7FFF;
        item->unk16 = self->unk16;
        item->unk15 = self->unk15;
        item->backref = (void*)self;
        self->ext.main_64.object = item;
        func_8001540C(2, SATURN_SOUND(0xC4, 0x8B), self);
    }
}

void cyber_peacock_spawn_missile(struct MainObj* self)
{
    struct ShotObj* shot;

    shot = find_free_shot_obj();
    if (shot != 0) {
        shot->active = self->active;
        shot->id = 0x2A;
        shot->unk2 = self->ext.main_64.shot_count;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->animation_table = self->animation_table;
        shot->unk40 = self->unk40;
        shot->unk3C = self->sprite_frames;
        shot->unk42 = self->unk42 & 0x7FFF;
        shot->unk16 = self->unk16;
        shot->unk15 = 0;
        shot->unk7C = self->ext.main_64.object;
        shot->backref = self;
        func_8001540C(2, SATURN_SOUND(0xC3, 0x8A), self);
    }
}

void cyber_peacock_aiming_laser_start(struct MainObj* self)
{
    self->ext.main_64.shot_count = 0;
    self->unk6++;
    set_animation(self, 0x25);
}

void cyber_peacock_aiming_laser_raise(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7C = 0x1E;
        self->unk6++;
        set_animation(self, 9);
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void cyber_peacock_aiming_laser_target(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        cyber_peacock_spawn_laser_target(self);
        set_animation(self, 0x24);
        self->unk7C = 0x1E;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void cyber_peacock_aiming_laser_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk6++;
        set_animation(self, 0xC);
    }
}

void cyber_peacock_aiming_laser_fire(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->unk6++;
        cyber_peacock_spawn_missile(self);
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void cyber_peacock_aiming_laser_next(struct MainObj* self)
{
    self->ext.main_64.shot_count++;
    if (self->ext.main_64.shot_count >= 8) {
        self->unk7C = 0x3C;
        self->unk6++;
        set_animation(self, 2);
        return;
    }
    self->unk7C = 0x5A;
    self->unk6 = 3;
    set_animation_frame(ANIMATED_OBJECT(self), 9, 3);
}

void cyber_peacock_aiming_laser_finish(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        self->ext.main_64.shot_count = 0;
        self->unk2 = 0;
        self->unk5 = 2;
        self->unk6 = 1;
        cyber_peacock_start_teleport(self);
        self->x_speed = FIXED(22);
        set_animation(self, 0x22);
        self->contact_damage = 5;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void cyber_peacock_aiming_laser(struct MainObj* self)
{
    cyber_peacock_aiming_laser_funcs[self->unk6](self);
}

void cyber_peacock_attack(struct MainObj* self)
{
    cyber_peacock_attack_funcs[self->unk2](self);
}

// cyber_peacock_hit_vanish
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007D5D0(struct MainObj* arg0)
{
    switch (arg0->unk6) {
    case 0:
        arg0->ext.main_64.shot_count = 0;
        arg0->unk6++;
        cyber_peacock_start_teleport(arg0);
        set_animation(arg0, 0x20);
        break;
    case 1:
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk6++;
            arg0->unk7C = 0x3C;
            set_animation(arg0, 0x22);
            break;
        }
        arg0->x_speed += arg0->x_accel;
        if (WEAPON_FRAME_COUNTER & 1)
            arg0->x_pos.val = ((s16)arg0->ext.main_64.target_x << 16) + arg0->x_speed;
        else
            arg0->x_pos.val = ((s16)arg0->ext.main_64.target_x << 16) - arg0->x_speed;
        animate_object(ANIMATED_OBJECT(arg0));
        break;
    case 2:
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        cyber_peacock_start_teleport(arg0);
        arg0->x_speed = 0x160000;
        arg0->ext.main_64.flash_timer = 0;
        set_animation(arg0, 0x22);
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_64_cyber_peacock", func_8007D5D0);
#endif

// cyber_peacock_guard_vanish
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007D710(struct MainObj* arg0)
{
    s16 count;

    switch (arg0->unk6) {
    case 0:
        arg0->ext.main_64.shot_count = 0;
        arg0->unk7C = 0;
        arg0->unk7 = 0;
        arg0->unk6++;
        set_animation(arg0, 0x21);
        func_8001540C(2, SATURN_SOUND(0xC8, 0x8F), arg0);
        arg0->attack_box = NULL;
        arg0->hurt_box = NULL;
        break;
    case 1:
        count = arg0->unk7C;
        if (count >= 3) {
            arg0->unk7C = 0x3C;
            arg0->unk6++;
            set_animation(arg0, 0x22);
            break;
        }
        if (arg0->animation_step.fields.relative_step < 0)
            arg0->unk7C = count + 1;
        animate_object(ANIMATED_OBJECT(arg0));
        break;
    case 2:
        arg0->unk5 = 2;
        arg0->unk6 = 1;
        cyber_peacock_start_teleport(arg0);
        arg0->x_speed = 0x160000;
        arg0->ext.main_64.flash_timer = 0;
        set_animation(arg0, 0x22);
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_64_cyber_peacock", func_8007D710);
#endif

// cyber_peacock_main
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8007D838(struct MainObj* arg0)
{
    s32 hit;

    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    if (arg0->ext.main_64.hit_count >= 7) {
        arg0->ext.main_64.hit_count = 0;
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        arg0->unk7 = 0;
    }
    ((void (*)(struct MainObj*))cyber_peacock_step_funcs[arg0->unk5])(arg0);
    hit = func_8002DD04(arg0);
    if (arg0->ext.main_64.flash_timer != 0) {
        arg0->ext.main_64.flash_timer--;
        arg0->hp = arg0->ext.main_64.saved_health;
        if (arg0->ext.main_64.flash_timer & 1)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
    } else if (hit < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
    } else if (hit > 0 && hit != 0x7F) {
        if (hit == 4 || hit == 0x24) {
            arg0->unk5 = 5;
            arg0->unk6 = 0;
            arg0->unk7 = 0;
            arg0->ext.main_64.flash_timer = 0x40;
            arg0->ext.main_64.saved_health = arg0->hp;
        } else {
            arg0->ext.main_64.flash_timer = 0x40;
            arg0->ext.main_64.saved_health = arg0->hp;
            arg0->ext.main_64.hit_count++;
        }
    }
    func_8002D9BC(arg0);
    is_on_screen(BASE_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_64_cyber_peacock", func_8007D838);
#endif

void cyber_peacock_death_start(struct MainObj* self)
{
    self->unk5 = 1;
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_64.flash_timer = 0x19;
    self->unk42 &= 0x7FFF;
    player_start_script_action(0x14, g_Player.unk15);
    set_animation(self, 0x20);
    is_on_screen(BASE_OBJECT(self));
}

void cyber_peacock_death_explode(struct MainObj* self)
{
    struct EffectObj* effect;
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.u.hi = self->x_pos.u.hi;
            effect->y_pos.u.hi = self->y_pos.u.hi;
            self->ext.main_64.object = effect;
        }
    }
    is_on_screen(BASE_OBJECT(self));
    if (self->unk7E-- == 0) {
        u8 unk92;
        self->unk42 ^= 0x8000;
        self->ext.main_64.flash_timer = unk92 = self->ext.main_64.flash_timer - 5;
        if (unk92 > 0x19) {
            self->ext.main_64.flash_timer = 0;
        }
        self->unk7E = self->ext.main_64.flash_timer > 5 ? self->ext.main_64.flash_timer : 5;
    }
}

void cyber_peacock_death_finish(struct MainObj* self)
{
    struct EffectObj* effect = self->ext.main_64.object;
    self->on_screen = 0;
    if (effect->active != 0) {
        if (effect->unk7 == 0) {
            if (self->unk7E-- == 0) {
                self->unk7E = 5;
                self->unk42 ^= 0x8000;
            }
            is_on_screen(BASE_OBJECT(self));
        }
    } else {
        if (engine_obj.stage != 0xC) {
            engine_obj.unkF = 0x10;
        } else {
            engine_obj.unkF = -0x80;
            engine_obj.character_state.bytes[engine_obj.checkpoint + 6] = 1;
            engine_obj.checkpoint += 9;
        }
        ZeroObjectState(OBJECT_HEADER(self));
        return;
    }
}

void cyber_peacock_death(struct BarObj* self)
{
    cyber_peacock_death_funcs[self->unk5](self);
}

void cyber_peacock_update(struct MainObj* self)
{
    cyber_peacock_state_funcs[self->state](self);
}

// cyber_peacock_is_player_near_random

union AnimationStep cyber_peacock_anim_0[] = {
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x13 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x13 },
    { 2, 0, 1, 0x14 },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x14 },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 3, 1, 1, 0x19 },
    { 3, 0, 1, 0x1A },
    { 3, 0, 1, 0x1B },
    { 3, 0, 1, 0x1C },
    { 3, 0, 1, 0x1D },
    { 3, 0, 1, 0x1E },
    { 3, 0, 1, 0x1F },
    { 3, 0, 1, 0x20 },
    { 3, 0, 1, 0x21 },
    { 3, 0, 1, 0x22 },
    { 4, 0, 1, 0x23 },
    { 5, 0, 1, 0x24 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x18 },
    { 15, 0, 1, 0x01 },
    { 1, 0, 0, 0x01 },
};

union AnimationStep cyber_peacock_anim_1[] = {
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 10, 0, 1, 0x03 },
    { 1, 1, 1, 0x03 },
    { 3, 0, 1, 0x04 },
    { 3, 0, 1, 0x2C },
    { 18, 0, 1, 0x2D },
    { 20, 0, 1, 0x05 },
    { 3, 0, 1, 0x2E },
    { 3, 0, 0, 0x2E },
};

union AnimationStep cyber_peacock_anim_2[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 0, 0x26 },
};

union AnimationStep cyber_peacock_anim_3[] = {
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 0, 0x00 },
};

union AnimationStep cyber_peacock_anim_35[] = {
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x28 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x28 },
    { 2, 0, 1, 0x25 },
    { 6, 0, 0, 0x28 },
    { 5, 0, 1, 0x29 },
    { 5, 0, 1, 0x2A },
    { 6, 0, 0, 0x2B },
};

struct Unk_unk68 cyber_peacock_anim_4[8] = {
    { 3, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, 1, 42 },
    { 3, 1, 1, 43 },
    { 1, 0, 1, 47 },
    { 1, 0, 1, 48 },
    { 1, 0, 1, 49 },
    { 1, 0, -3, 50 },
};

union AnimationStep cyber_peacock_anim_5[] = {
    { 1, 0, 1, 0x2F },
    { 1, 0, 1, 0x33 },
    { 1, 0, 1, 0x34 },
    { 1, 0, 1, 0x2F },
    { 1, 0, 1, 0x33 },
    { 1, 0, 1, 0x34 },
    { 1, 0, 1, 0x2F },
    { 1, 0, 1, 0x33 },
    { 1, 0, 0, 0x34 },
};

struct Unk_unk68 cyber_peacock_anim_6[18] = {
    { 6, 0, 1, 0 },
    { 4, 0, 1, 53 },
    { 4, 0, 1, 54 },
    { 5, 0, 1, 55 },
    { 3, 0, 1, 56 },
    { 3, 0, 1, 57 },
    { 1, 0, 1, 58 },
    { 1, 0, 1, 59 },
    { 1, 0, 1, 57 },
    { 1, 0, 1, 58 },
    { 1, 0, 1, 59 },
    { 1, 0, 1, 60 },
    { 1, 0, 1, 61 },
    { 1, 1, 1, 62 },
    { 1, 0, 1, 58 },
    { 1, 0, 1, 61 },
    { 1, 0, 1, 62 },
    { 1, 0, -2, 58 },
};

union AnimationStep cyber_peacock_anim_7[] = {
    { 1, 0, 1, 0x3D },
    { 2, 0, 1, 0x3F },
    { 3, 0, 1, 0x40 },
    { 4, 0, 1, 0x41 },
    { 5, 0, 1, 0x42 },
    { 6, 0, 1, 0x39 },
    { 1, 0, 1, 0x43 },
    { 1, 0, 1, 0x39 },
    { 1, 0, 1, 0x43 },
    { 1, 0, 1, 0x39 },
    { 1, 0, 1, 0x43 },
    { 1, 0, 1, 0x39 },
    { 1, 0, 1, 0x43 },
    { 1, 0, 1, 0x39 },
    { 1, 0, 1, 0x43 },
    { 1, 0, 0, 0x39 },
};

union AnimationStep cyber_peacock_anim_8[] = {
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x44 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x44 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 0, 0x44 },
};

union AnimationStep cyber_peacock_anim_37[] = {
    { 3, 0, 1, 0x45 },
    { 18, 0, 1, 0x46 },
    { 20, 0, 0, 0x00 },
};

union AnimationStep cyber_peacock_anim_9[] = {
    { 8, 0, 1, 0x00 },
    { 8, 0, 1, 0x47 },
    { 8, 0, 1, 0x48 },
    { 18, 0, 1, 0x49 },
    { 2, 0, 1, 0x4A },
    { 2, 0, 1, 0x4B },
    { 2, 0, 1, 0x4C },
    { 2, 0, 1, 0x4A },
    { 2, 0, 1, 0x4B },
    { 2, 0, 1, 0x4C },
    { 3, 0, 1, 0x4D },
    { 3, 0, 1, 0x4E },
    { 3, 0, 1, 0x4F },
    { 10, 0, 1, 0x50 },
    { 3, 0, 1, 0x51 },
    { 3, 0, 1, 0x52 },
    { 3, 0, 1, 0x53 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x53 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x53 },
    { 20, 0, 0, 0x54 },
};

u8 cyber_peacock_anim_10[8] = { 1, 0, 1, 88, 1, 0, 255, 89 };

struct Unk_unk68 cyber_peacock_anim_11[4] = {
    { 2, 0, 1, 88 },
    { 2, 0, 1, 90 },
    { 2, 0, 1, 91 },
    { 2, 0, -3, 92 },
};

union AnimationStep cyber_peacock_anim_12[] = {
    { 8, 0, 1, 0x55 },
    { 2, 0, 1, 0x56 },
    { 1, 0, 1, 0x57 },
    { 2, 0, 1, 0x55 },
    { 2, 0, 1, 0x91 },
    { 30, 0, 0, 0x92 },
};

union AnimationStep cyber_peacock_anim_36[] = {
    { 1, 0, 0, 0x55 },
};

u8 cyber_peacock_anim_13[8] = { 2, 0, 1, 109, 2, 0, 255, 110 };

u8 cyber_peacock_anim_14[8] = { 2, 0, 1, 111, 2, 0, 255, 112 };

u8 cyber_peacock_anim_15[8] = { 2, 0, 1, 113, 2, 0, 255, 114 };

u8 cyber_peacock_anim_16[8] = { 2, 0, 1, 115, 2, 0, 255, 116 };

u8 cyber_peacock_anim_17[8] = { 2, 0, 1, 117, 2, 0, 255, 118 };

u8 cyber_peacock_anim_18[8] = { 2, 0, 1, 119, 2, 0, 255, 120 };

u8 cyber_peacock_anim_19[8] = { 2, 0, 1, 121, 2, 0, 255, 122 };

u8 cyber_peacock_anim_20[8] = { 2, 0, 1, 123, 2, 0, 255, 124 };

u8 cyber_peacock_anim_21[8] = { 2, 0, 1, 93, 2, 0, 255, 94 };

u8 cyber_peacock_anim_22[8] = { 2, 0, 1, 95, 2, 0, 255, 96 };

u8 cyber_peacock_anim_23[8] = { 2, 0, 1, 97, 2, 0, 255, 98 };

u8 cyber_peacock_anim_24[8] = { 2, 0, 1, 99, 2, 0, 255, 100 };

u8 cyber_peacock_anim_25[8] = { 2, 0, 1, 101, 2, 0, 255, 102 };

u8 cyber_peacock_anim_26[8] = { 2, 0, 1, 103, 2, 0, 255, 104 };

u8 cyber_peacock_anim_27[8] = { 2, 0, 1, 105, 2, 0, 255, 106 };

u8 cyber_peacock_anim_28[8] = { 2, 0, 1, 107, 2, 0, 255, 108 };

union AnimationStep cyber_peacock_anim_29[] = {
    { 1, 0, 1, 0x7D },
    { 2, 0, 1, 0x7E },
    { 3, 0, 1, 0x7F },
    { 3, 0, 1, 0x80 },
    { 4, 0, 0, 0x81 },
};

struct Unk_unk68 cyber_peacock_anim_30[3] = {
    { 2, 0, 1, -123 },
    { 1, 0, 1, -122 },
    { 1, 0, -2, -112 },
};

struct Unk_unk68 cyber_peacock_anim_31[3] = {
    { 1, 0, 1, -126 },
    { 2, 0, 1, -125 },
    { 2, 0, -2, -124 },
};

union AnimationStep cyber_peacock_anim_32[] = {
    { 2, 0, 1, 0x87 },
    { 2, 0, 1, 0x88 },
    { 2, 0, 1, 0x87 },
    { 2, 0, 1, 0x88 },
    { 2, 0, 1, 0x87 },
    { 2, 0, 1, 0x88 },
    { 2, 0, 1, 0x87 },
    { 2, 0, 1, 0x88 },
    { 2, 0, 1, 0x87 },
    { 2, 0, 1, 0x88 },
    { 2, 0, 1, 0x87 },
    { 2, 0, 0, 0x88 },
};

struct Unk_unk68 cyber_peacock_anim_33[10] = {
    { 4, 0, 1, -121 },
    { 4, 0, 1, -119 },
    { 4, 0, 1, -118 },
    { 4, 0, 1, -117 },
    { 4, 0, 1, -118 },
    { 4, 0, 1, -116 },
    { 4, 0, 1, -115 },
    { 4, 0, 1, -114 },
    { 4, 0, 1, -113 },
    { 4, 0, -9, -116 },
};

union AnimationStep cyber_peacock_anim_34[] = {
    { 4, 0, 0, 0x34 },
};

void* cyber_peacock_animations[38] = {
    cyber_peacock_anim_0,
    cyber_peacock_anim_1,
    cyber_peacock_anim_2,
    cyber_peacock_anim_3,
    cyber_peacock_anim_4,
    cyber_peacock_anim_5,
    cyber_peacock_anim_6,
    cyber_peacock_anim_7,
    cyber_peacock_anim_8,
    cyber_peacock_anim_9,
    cyber_peacock_anim_10,
    cyber_peacock_anim_11,
    cyber_peacock_anim_12,
    cyber_peacock_anim_13,
    cyber_peacock_anim_14,
    cyber_peacock_anim_15,
    cyber_peacock_anim_16,
    cyber_peacock_anim_17,
    cyber_peacock_anim_18,
    cyber_peacock_anim_19,
    cyber_peacock_anim_20,
    cyber_peacock_anim_21,
    cyber_peacock_anim_22,
    cyber_peacock_anim_23,
    cyber_peacock_anim_24,
    cyber_peacock_anim_25,
    cyber_peacock_anim_26,
    cyber_peacock_anim_27,
    cyber_peacock_anim_28,
    cyber_peacock_anim_29,
    cyber_peacock_anim_30,
    cyber_peacock_anim_31,
    cyber_peacock_anim_32,
    cyber_peacock_anim_33,
    cyber_peacock_anim_34,
    cyber_peacock_anim_35,
    cyber_peacock_anim_36,
    cyber_peacock_anim_37,
};

struct Unk_unk68 cyber_peacock_hit_box = { -6, -27, 17, 64 };

struct Unk_unk68 cyber_peacock_intro_hurt_box = { -11, -27, 27, 70 };

struct Unk_unk68 cyber_peacock_rising_kick_attack_box = { -30, -35, 56, 64 };

struct Unk_unk68 cyber_peacock_rising_kick_hurt_box = { -18, -37, 32, 71 };

struct Unk_unk68 cyber_peacock_slash_attack_box = { -12, -9, 28, 52 };

struct Unk_unk68 cyber_peacock_slash_hurt_box = { -32, -12, 44, 55 };

struct Unk_unk68 cyber_peacock_slash_swing_attack_box = { -87, -50, -61, 92 };

struct Unk_unk68 cyber_peacock_slash_swing_hurt_box = { -32, -12, 44, 55 };

void (*cyber_peacock_intro_appear_funcs[4])() = {
    cyber_peacock_intro_appear_start,
    cyber_peacock_intro_pose,
    cyber_peacock_intro_start_health_bar,
    cyber_peacock_intro_fill_health,
};

void (*cyber_peacock_intro_funcs[3])() = {
    func_8007C30C,
    cyber_peacock_intro_wait_player,
    cyber_peacock_intro_appear,
};

u8 cyber_peacock_attacks[32] = { 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03 };

u8 cyber_peacock_attacks_low_health[32] = { 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03 };

u8 cyber_peacock_attack_animations[8] = { 0x03, 0x23, 0x03, 0x08, 0x23, 0x00, 0x00, 0x00 };

u8 cyber_peacock_attack_steps[8] = { 0x02, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00 };

void (*cyber_peacock_teleport_funcs[5])() = {
    cyber_peacock_teleport_start,
    cyber_peacock_teleport_vanish,
    func_8007CA68,
    cyber_peacock_teleport_appear,
    cyber_peacock_teleport_wait,
};

void (*cyber_peacock_rising_kick_funcs[4])() = {
    cyber_peacock_rising_kick_start,
    cyber_peacock_rising_kick_jump,
    cyber_peacock_rising_kick_rise,
    cyber_peacock_rising_kick_finish,
};

void (*cyber_peacock_slash_funcs[3])() = {
    cyber_peacock_slash_start,
    cyber_peacock_slash_swing,
    cyber_peacock_slash_finish,
};

void (*cyber_peacock_aiming_laser_funcs[7])() = {
    cyber_peacock_aiming_laser_start,
    cyber_peacock_aiming_laser_raise,
    cyber_peacock_aiming_laser_target,
    cyber_peacock_aiming_laser_wait,
    cyber_peacock_aiming_laser_fire,
    cyber_peacock_aiming_laser_next,
    cyber_peacock_aiming_laser_finish,
};

void (*cyber_peacock_attack_funcs[4])() = {
    cyber_peacock_rising_kick,
    cyber_peacock_slash,
    cyber_peacock_aiming_laser,
    cyber_peacock_rising_kick,
};

void (*cyber_peacock_step_funcs[6])() = {
    enemy_hit_reaction,
    enemy_hit_reaction,
    cyber_peacock_teleport,
    cyber_peacock_attack,
    func_8007D5D0,
    func_8007D710,
};

void (*cyber_peacock_death_funcs[3])() = {
    cyber_peacock_death_start,
    cyber_peacock_death_explode,
    cyber_peacock_death_finish,
};

void (*cyber_peacock_state_funcs[3])() = {
    cyber_peacock_intro,
    func_8007D838,
    cyber_peacock_death,
};
