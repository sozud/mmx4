// MainObj, main_object_update_funcs[75]
// 8008FA0C..800919C4
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_75_general.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/player_common.h"
#include "main/128C4.h"
#include "main/55C4.h"
#include "main/stage_objects.h"
#include "main/collision_bounds.h"
#include "main/1E1BC.h"
#include "main/collision.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#endif

// general_intro_funcs
extern void (*general_intro_funcs[])(struct MainObj*);
void general_intro_wait_player(struct MainObj*);

void general_intro_lock_camera(struct MainObj*);
void general_intro_enter(struct MainObj*);
void general_intro_land(struct MainObj*);
void general_intro_dialogue(struct MainObj*);
void general_intro_fill_health(struct MainObj*);
void general_intro_finish(struct MainObj*);

// general_fly_funcs
extern void (*general_fly_funcs[])(struct MainObj*);
void general_fly_descend(struct MainObj*);
void general_fly_start(struct MainObj*);

// general_punch_funcs
extern void (*general_punch_funcs[])(struct MainObj*);
void general_punch_rise(struct MainObj*);

void general_punch_wait(struct MainObj*);

void general_punch_wait_return(struct MainObj*);
void general_punch_recover(struct MainObj*);

// general_orbs_funcs
extern void (*general_orbs_funcs[])(struct MainObj*);
void general_orbs_descend(struct MainObj*);
void general_orbs_fire(struct MainObj*);
void general_orbs_wait(struct MainObj*);
void general_orbs_recover(struct MainObj*);

// general_slam_funcs
extern void (*general_slam_funcs[])(struct MainObj*);

void general_slam_land(struct MainObj*);

// general_step_funcs
void general_resume_step(struct MainObj* arg0);

void general_fly(struct MainObj* arg0);
void general_punch(struct MainObj* arg0);
void general_orbs(struct MainObj* arg0);
void general_slam(struct MainObj* arg0);

// general_death_funcs
void general_death_start(struct MainObj*);

void general_death_wait_explosion(struct MainObj*);

// general_state_funcs
extern void (*general_state_funcs[])(struct MainObj*);
void general_intro(struct MainObj*);

void func_80091898(struct MainObj*);

extern void (*general_death_funcs[5])();

u8 general_at_position(struct ObjectHeader* self, s16 arg1, s16 arg2)
{
    s16 temp_v1;
    s16 temp_a0;

    temp_v1 = self->x_pos.i.hi;
    if ((temp_v1 - arg1 >= 0) ? (temp_v1 - arg1 < 3) : (arg1 - temp_v1 < 3)) {
        temp_a0 = self->y_pos.i.hi;
        if ((temp_a0 - arg2 >= 0) ? (temp_a0 - arg2 < 3) : (arg2 - temp_a0 < 3)) {
            return 1;
        }
    }
    return 0;
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_75_general", general_pick_script);
#else
void general_pick_script(struct MainObj* self)
{
    s32 low_health = self->hp < 0x19;
    const u8** scripts = general_scripts[low_health];
    u8 roll = get_random();
    u8 i = 0;
    u8* weights = &general_script_weights[low_health * 2];
    roll = (roll >> 2) & 0xF;
    while (i < 2) {
        if (roll < weights[i]) {
            self->ext.main_75.script = scripts[i];
            return;
        }
        i++;
    }
}
#endif

void general_intro_wait_player(struct MainObj* self)
{
    struct EffectObj* effect;

    if (g_Player.capsule_state == 0) {
#ifndef MMX4_SATURN
        if (g_Player.x_pos.i.hi > 0xD30) {
            background_objects[1].unk3 = 0;
        }
#endif
        self->active |= 4;
        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
        self->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x18;
            self->ext.main_75.object.effect = effect;
        }
    }
}

// general_intro_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
u8 general_at_position(struct ObjectHeader*, s16, s16);
void func_8002217C(arg_u16 message, u8 portrait, s32 delay_only);
ret_s8 func_8002DD04(struct MainObj* object);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8008FBCC(struct MainObj* self);
void func_80091218(struct MainObj* self);
void func_8009027C(struct MainObj* self);
void func_800905D4(struct MainObj* self);
void func_800915C4(struct MainObj* self);
void func_800917AC(struct MainObj* self);
extern struct Unk_unk68 D_801059BC;
extern struct Unk_unk68 D_801059C4[5];
extern void* general_animations[46];
extern struct Unk_unk68 D_80108404[];
extern struct Unk_unk68 D_80108384[];
extern struct Unk_unk68 D_801059C0;
extern void (*general_step_funcs[7])();
// src/main/mains/main_75_general.c

extern union AnimationStep* final_cutscene_animations[1];
extern ret_u8 func_8002938C(s32);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8008FBCC(struct MainObj* self)
{
    struct Main75Ext* ext = &self->ext.main_75;
    struct ShotObj* shot;

    if (ext->object.shot != NULL && ext->object.shot->active != 0)
        return;
    self->hp = 0;
    self->contact_damage = 5;
    self->invincibility_timer = 0;
    self->x_pos.i.hi = 0xE98;
    self->unk5++;
    self->y_pos.i.hi = 0x27B;
    self->unk40 = (OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0xB0);
    self->unk18.val = self->x_pos.val;
    self->unk16 = VISUAL_SATURN_LAYER(5);
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->terrain_box = NULL;
    self->unk1C.val = self->y_pos.val;
    self->collision_data = D_80107B78;
    self->contact_damage = 9;
    self->animation_table = (const u8* const*)general_animations;
    self->hurt_box = D_801059C4;
    self->attack_box = &D_801059BC;
    self->bg_offset = g_Player.bg_offset;
    self->unk15 = (g_Player.x_pos.val >= self->x_pos.val) << PLAYER_FACING_SHIFT;
    set_animation(self, 0);
    memset(ext, 0, sizeof(*ext));
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x37;
        shot->unk2 = 1;
        shot->unk7C = (struct WeaponObj*)self;
        ext->object.shot = shot;
    }
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x37;
        shot->unk2 = 0;
        shot->unk7C = (struct WeaponObj*)self;
        ext->thruster = shot;
    }
    player_end_script_action();
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_75_general", func_8008FBCC);
#endif

void general_intro_lock_camera(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi > 0xDF0) {
        self->unk5++;
        self->ext.main_75.background_unk1E = background_objects[0].unk1E;
        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
        background_objects[0].unk26 = 0xDD0;
        background_objects[0].unk2A = 0x190;
        engine_obj.enable_boss = 1;
        engine_obj.unk25 = 1;
        engine_obj.boss_ptr = self;
    }
}

void general_intro_enter(struct MainObj* self)
{
    if (self->unk6 == 0) {
        if (background_objects[0].x_pos.i.hi == background_objects[0].unk26) {
            set_animation(self, 1);
            self->unk6++;
        }
    } else {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0) {
            self->animation_step.fields.event = 0;
            set_animation(self->ext.main_75.thruster, 2);
            self->ext.main_75.thruster->timer = 1;
            self->ext.main_75.thruster->unk84.shot_55.x = 0x18;
            self->ext.main_75.thruster->unk84.shot_55.y = 0;
        }
        if (self->animation_step.fields.relative_step == 0) {
            self->unk5++;
            self->unk6 = 0;
            set_animation(self, 3);
            set_animation(self->ext.main_75.thruster, 4);
        }
    }
}

void general_intro_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->ext.main_75.thruster->animation_step.fields.relative_step == 0) {
        self->unk5++;
        self->ext.main_75.object.shot->unk5++;
        func_8001540C(2, SATURN_SOUND(8, 0xE2), self);
        self->unk7C = 0x1E;
    }
}

void general_intro_dialogue(struct MainObj* self)
{
    if (self->unk6 == 0) {
        if (--self->unk7C == 0) {
            if (engine_obj.stage == 0xB) {
                if (engine_obj.cur_character == CHARACTER_X) {
                    func_8002217C(
                        0x29, 0xFF, engine_obj.character_state.bytes[8]);
                } else {
                    func_8002217C(
                        0x21, 0xFF, engine_obj.character_state.bytes[8]);
                }
                engine_obj.character_state.bytes[8] = 1;
            }
            self->unk6++;
        }
    } else if (abc_object.unkC == 0) {
        self->unk6 = 0;
        self->unk5++;
        play_boss_voice(0xB);
        self->unk7C = 1;
    }
}

void general_intro_fill_health(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (update_boss_music_delay() != 0) {
        return;
    }

    if (self->hp < 0x30) {
        if (--self->unk7C == 0) {
            func_8001540C(0, SATURN_SOUND(0xE, 0x14), 0);
            self->unk7C = 2;
        }
        self->hp++;
    } else {
        self->unk5++;
        background_objects[0].unk26 = self->ext.main_75.background_unk1E;
        background_objects[0].unk48 = 2;
    }
}

void general_intro_finish(struct MainObj* self)
{
    if (background_objects[0].unk1E == background_objects[0].unk26) {
        player_end_script_action();
        background_objects[0].unk48 = 8;
        self->state++;
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
    }
}

void general_intro(struct MainObj* self)
{
    general_intro_funcs[self->unk5](self);
    if (self->unk5 >= 2) {
        update_on_screen(BASE_OBJECT(self), 0xA0, 0xA0);
    }
}

void general_rise(struct MainObj* self)
{
    u8 temp_unk6;

    if (self->unk7 == 0) {
        self->unk7++;
        set_animation(self, 8);
        set_animation(self->ext.main_75.thruster, 5);
        self->ext.main_75.thruster->unk84.shot_55.x = 0x18;
        self->ext.main_75.thruster->unk84.shot_55.y = 4;
        self->y_speed = FIXED(0.5);
        self->unk7C = 0x3C;
        self->terrain_box = &D_801059D8;
    } else {
        animate_object(ANIMATED_OBJECT(self));
        move_object(MOVING_OBJECT(self));
        if (--self->unk7C == 0) {
            temp_unk6 = self->unk6;
            self->unk5 = 2;
            self->unk7 = 0;
            *(volatile u8*)&self->unk6 = temp_unk6 + 1;
            self->unk6 = 0;
        }
    }
}

// general_move
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8009027C(struct MainObj* self)
{
    struct Main75Ext* ext = &self->ext.main_75;
    u8 next;

    switch (self->unk6) {
    case 0:
        self->unk6 = 1;
        set_animation(self, 8);
        if (self->y_pos.i.hi >= 0x24B) {
            set_animation(ext->thruster, 5);
            func_8001540C(2, SATURN_SOUND(1, 0xDB), self);
        } else {
            set_animation(ext->thruster, 6);
            func_8001540C(2, SATURN_SOUND(2, 0xDC), self);
        }
        ext->thruster->unk84.shot_55.x = self->unk15 != 0 ? -0x18 : 0x18;
        ext->thruster->unk84.shot_55.y = 4;
        break;
    case 1:
        set_velocity_from_angle(MOVING_OBJECT(self),
            (u8)angle_to_point(OBJECT_HEADER(self),
                self->unk15 != 0 ? 0xD7E0000 : 0xEC50000, 0x24B0000));
        animate_object(ANIMATED_OBJECT(self));
        move_object(MOVING_OBJECT(self));
        if (general_at_position(OBJECT_HEADER(self), self->unk15 != 0 ? 0xD7E : 0xEC5, 0x24B)) {
            self->unk7C = 0x3C;
            self->x_speed = 0;
            self->y_speed = 0;
            self->unk6++;
            set_animation(ext->thruster, 7);
            STOP_SOUND(2, 2, 0x6);
        }
        break;
    case 2:
        animate_object(ANIMATED_OBJECT(self));
        if (--self->unk7C != 0)
            break;
        if (ext->script == NULL || *ext->script == 0xFF)
            general_pick_script(self);
        next = *ext->script;
        self->unk6 = 0;
        self->unk7 = 0;
        ext->script++;
        self->unk5 = next;
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_75_general", func_8009027C);
#endif

void general_fly_descend(struct MainObj* self)
{
    self->unk6++;
    set_animation(self->ext.main_75.thruster, 6);
    func_8001540C(2, SATURN_SOUND(2, 0xDC), self);
    self->x_speed = 0;
    self->y_speed = FIXED(-0.5);
    self->ext.main_75.random_index = (get_random() & 0xFF) % 3U;
    self->unk7C = self->ext.main_75.random_index * 0x3C;
}

void general_fly_start(struct MainObj* self)
{
    s16 temp_v0;
    s16 var_a0;
    struct WeaponObj* weapon;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    temp_v0 = self->unk7C;
    if (temp_v0 == 0) {
        self->unk6++;
        STOP_SOUND(2, 2, 0x6);
        set_animation(self->ext.main_75.thruster, 5);
        func_8001540C(2, SATURN_SOUND(1, 0xDB), self);
        self->x_speed = self->unk15 != 0 ? FIXED(2) : FIXED(-2);
        weapon = (struct WeaponObj*)self->ext.main_75.thruster;
        self->y_speed = 0;
        self->terrain_box = &D_801059D8;
        var_a0 = self->unk15 != 0 ? -0x18 : 0x18;
        ((u16*)&weapon->unk84)[0] = var_a0;
        ((u16*)&self->ext.main_75.thruster->unk84)[1] = 4;
        return;
    }
    self->unk7C = temp_v0 - 1;
}

// general_fly_cross
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_75_general", func_800905D4);
#else
void func_800905D4(struct MainObj* self)
{
    u8 turned;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    turned = 0;
    if (self->ext.main_75.random_index == 0 && self->y_pos.i.hi + 0x30 < g_Player.y_pos.i.hi
        && (self->x_pos.i.hi - g_Player.x_pos.i.hi >= 0 ? self->x_pos.i.hi - g_Player.x_pos.i.hi : g_Player.x_pos.i.hi - self->x_pos.i.hi) < 8) {
        self->unk5 = 6;
        self->unk6 = 0;
        self->unk7 = 0;
        self->unk7C = 0x1E;
        return;
    }
    if (self->collision_flags & 3) {
        if (self->unk15 != 0) {
            if (self->collision_flags & 1)
                turned = 1;
        } else if (self->collision_flags & 2) {
            turned = 1;
        }
        if (turned) {
            self->unk5 = 2;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk15 ^= PLAYER_FACING_RIGHT;
            self->x_speed = 0;
            self->y_speed = 0;
        }
    }
}
#endif

void general_fly(struct MainObj* self)
{
    general_fly_funcs[self->unk6](self);
}

void general_punch_rise(struct MainObj* self)
{
    struct ShotObj* shot;
    s16 timer;

    if (self->unk7 == 0) {
        self->unk7++;
        set_animation(self, 8);
        set_animation(self->ext.main_75.thruster, 5);
        func_8001540C(2, SATURN_SOUND(1, 0xDB), self);
        self->ext.main_75.thruster->unk84.shot_55.x = (self->unk15 != 0 ? -0x18 : 0x18);
        self->ext.main_75.thruster->unk84.shot_55.y = 4;
        self->x_speed = 0;
        self->y_speed = FIXED(0.5);
        self->unk7C = 0x3C;
        self->terrain_box = &D_801059D8;
        self->ext.main_75.bob_step = 1;
        self->ext.main_75.bob_timer = 0xA;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    timer = --self->unk7C;
    if (timer == 0) {
        self->unk6++;
        self->unk7 = 0;
        set_animation(self, 0xB);
        STOP_SOUND(2U, 1U, 0x6);
        set_animation(self->ext.main_75.thruster, 7);
        self->y_speed = 0;
    }
}

void general_punch_launch(struct MainObj* self)
{
    struct ShotObj* first;
    struct ShotObj* second;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        first = find_free_shot_obj();
        if (first != NULL) {
            first->active = 0x41;
            first->id = 0x37;
            first->unk2 = 2;
            first->unk7C = WEAPON_OBJECT(self);
            general_fists[0] = first;
        }
        second = find_free_shot_obj();
        if (second != NULL) {
            second->active = 0x41;
            second->id = 0x37;
            second->unk2 = 3;
            second->unk7C = WEAPON_OBJECT(self);
            general_fists[1] = second;
        }
        first->unk8C.shot = second;
        second->unk8C.shot = first;
    }
    if (self->animation_step.fields.frame_index == 0x1E) {
        shot = self->ext.main_75.thruster;
        shot->unk84.shot_55.x = self->unk15 != 0 ? -0x20 : 0x20;
        self->ext.main_75.thruster->unk84.shot_55.y = -4;
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7C = 0x3C;
        self->unk6++;
    }
}

void general_punch_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk6++;
        set_animation(self, 0xC);
        self->unk7C = 0x46;
        self->unk7E = 0;
    }
}

void general_punch_rings(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x37;
            shot->unk2 = self->unk7E + 4;
            shot->unk7C = WEAPON_OBJECT(self);
            self->unk7E ^= 1;
        }
        self->unk7C = 0x3C;
    }
}

void general_punch_wait_return(struct MainObj* self)
{
    if ((general_fists[0]->timer == 0x80) && (general_fists[1]->timer == 0x80)) {
        self->unk6++;
        general_fists[0]->state++;
        general_fists[1]->state++;
        set_animation(self, 0x17);
    }
}

void general_punch_recover(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
    }
}

void general_punch(struct MainObj* self)
{
    general_punch_funcs[self->unk6](self);
    if ((self->unk6 >= 3) && (WEAPON_FRAME_COUNTER % 10 == 0)) {
        self->y_pos.i.hi += self->ext.main_75.bob_step;
        if (--self->ext.main_75.bob_timer == 0) {
            self->ext.main_75.bob_timer = 0xA;
            self->ext.main_75.bob_step *= -1;
        }
    }
}

void general_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_75.saved_unk5;
}

void general_orbs_descend(struct MainObj* self)
{
    self->unk6++;
    set_animation(self->ext.main_75.thruster, 6);
    func_8001540C(2, SATURN_SOUND(2, 0xDC), NULL);
    self->x_speed = 0;
    self->y_speed = FIXED(-0.5);
    self->unk7C = 0x64;
    self->ext.main_75.orbs_ready = 0;
    self->ext.main_75.bob_step = 1;
    self->ext.main_75.bob_timer = 0xA;
}

void general_orbs_fire(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (--self->unk7C == 0) {
        STOP_SOUND(2, 2, 0x6);
        set_animation(self->ext.main_75.thruster, 7);
        self->unk6++;
        shot = find_free_shot_obj();
        if (shot != 0) {
            shot->active = 0x41;
            shot->id = 0x37;
            shot->unk2 = 9;
            shot->unk7C = WEAPON_OBJECT(self);
        }
        func_8001540C(2, SATURN_SOUND(3, 0xDD), self);
    }
}

void general_orbs_wait(struct MainObj* self)
{
    if (self->ext.main_75.orbs_ready != 0) {
        self->unk7C = 0x78;
        self->unk6++;
    }
}

void general_orbs_recover(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->unk7 = 0;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void general_orbs(struct MainObj* self)
{
    general_orbs_funcs[self->unk6](self);
    if (WEAPON_FRAME_COUNTER % 10 == 0) {
        self->y_pos.i.hi += self->ext.main_75.bob_step;
        if (--self->ext.main_75.bob_timer == 0) {
            self->ext.main_75.bob_timer = 0xA;
            self->ext.main_75.bob_step *= -1;
        }
    }
}

void general_slam_windup(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->unk7 == 0) {
        if (--self->unk7C == 0) {
            self->unk7++;
            set_animation(self, 9);
            set_animation(self->ext.main_75.thruster, 6);
            func_8001540C(2, SATURN_SOUND(2, 0xDC), 0);
            self->ext.main_75.thruster->unk84.shot_55.x = (self->unk15 != 0 ? -0x18 : 0x18);
            self->ext.main_75.thruster->unk84.shot_55.y = -0x10;
            self->terrain_box = &D_801059DC;
        }
    } else if (self->animation_step.fields.event != 0) {
        self->x_speed = 0;
        self->y_speed = FIXED(-5);
        self->unk6++;
        self->unk7 = 0;
    }
}

void general_slam_fall(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (self->collision_flags & 8) {
        self->unk6++;
        STOP_SOUND(2, 2, 0x6);
        set_animation(self, 0xA);
        func_8001540C(2, SATURN_SOUND(0, 0xDA), self);
        self->ext.main_75.thruster->timer = 0;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x37;
            shot->unk2 = 6;
            shot->unk7C = WEAPON_OBJECT(self);
        }
        start_screen_shake_x(0x14, 4, 2);
    }
}

void general_slam_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk7C = 0x28;
        self->unk6++;
    }
}

void general_slam_rise(struct MainObj* self)
{
    s16 temp_v0;
    s16 var_a0;
    struct ShotObj* weapon_view;

    temp_v0 = self->unk7C;
    if (temp_v0 == 0) {
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.relative_step == 0) {
            self->unk6++;
            set_animation(self, 8);
            set_animation(self->ext.main_75.thruster, 5);
            func_8001540C(2, SATURN_SOUND(1, 0xDB), self);
            self->ext.main_75.thruster->timer = 1;
            weapon_view = self->ext.main_75.thruster;
            var_a0 = self->unk15 != 0 ? -0x18 : 0x18;
            weapon_view->unk84.halves[0] = var_a0;
            self->ext.main_75.thruster->unk84.halves[1] = 4;
            self->x_speed = 0;
            self->y_speed = FIXED(5);
            self->unk7C = 0xF;
            self->terrain_box = &D_801059D8;
        }
    } else {
        self->unk7C = temp_v0 - 1;
    }
}

void general_slam_ascend(struct MainObj* self)
{
    s32 velocity;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (--self->unk7C == 0) {
        self->unk6++;
        velocity = self->unk15 != 0 ? FIXED(2) : FIXED(-2);
        self->x_speed = velocity;
        self->y_speed = 0;
    }
}

void general_slam_leave(struct MainObj* self)
{
    u8 flags;
    u8 reset;

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    flags = self->collision_flags;
    reset = 0;
    if (flags & 3) {
        if (self->unk15 != 0) {
            if (flags & 1) {
                reset = 1;
            }
        } else if (flags & 2) {
            reset = 1;
        }
        if (reset != 0) {
            self->unk5 = 2;
            self->unk6 = 0;
            self->unk7 = 0;
            self->unk15 ^= PLAYER_FACING_RIGHT;
            self->x_speed = 0;
        }
    }
}

void general_slam(struct MainObj* self)
{
    general_slam_funcs[self->unk6](self);
}

// general_fight
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80091218(struct MainObj* self)
{
    struct Main75Ext* ext = &self->ext.main_75;
    struct ShotObj* shot;
    s32 hit;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    CollisionRelated((struct PlayerObj*)self);
    self->collision_data = D_80108404;
    self->hurt_box = D_801059C4;
    func_8002DD04(self);
    if (ext->hit_active == 0)
        self->collision_data = D_80108384;
    self->hurt_box = &D_801059C0;
    hit = func_8002DD04(self);
    if (self->unk5 != 0)
        ext->saved_unk5 = self->unk5;
    if (ext->hit_active != 0) {
        if (!(ext->hit_timer & 1))
            self->unk42 |= 0x8000;
        else
            self->unk42 &= 0x7FFF;
        if (--ext->hit_timer == 0)
            ext->hit_active = 0;
    } else if (hit < 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
        self->unk42 &= 0x7FFF;
        g_Player.spike_immune = 1;
        return;
    } else if (hit != 0) {
        s32 spawn = 0;
        s32 flash = 1;

        if (engine_obj.cur_character == 0) {
            if (hit == 0x12 || hit == 9)
                spawn = 1;
            else if (hit == 0x7F)
                flash = 0;
        } else if (hit == 0x1E) {
            spawn = 1;
        } else if (hit < 0x1F) {
            if (hit < 0x1A && hit >= 0x18)
                flash = 0;
        } else if (hit == 0x7F) {
            flash = 0;
        }
        if (spawn) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x37;
                shot->unk2 = 8;
                shot->unk7C = (struct WeaponObj*)self;
            }
        }
        if (flash) {
            self->collision_data = D_801060F0;
            ext->hit_timer = 0x40;
            ext->hit_active = 1;
        }
    }
    general_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_75_general", func_80091218);
#endif

void general_death_start(struct MainObj* self)
{
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_75.blink_delay = 0x19;
    background_objects[0].unk26 = background_objects[0].x_pos.u.hi;
    g_Player.stun_timer = 0;
    player_start_script_action(0x15, 0);
    self->unk5++;
    self->unk6 = 0;
    self->unk42 &= 0x7FFF;
    set_animation(self, 0x24);
    self->ext.main_75.thruster->timer = 0;
    self->ext.main_75.bob_timer = 0xA;
    self->ext.main_75.bob_step = 1;
}

void general_death_blink(struct MainObj* self)
{
    struct EffectObj* effect;
    s8 var_a0;
    s16 var_a1;

    if (--self->unk7C == 0) {
        self->unk5++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = -0x7F;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.i.hi;
            effect->y_pos.i.hi = self->y_pos.i.hi;
            self->ext.main_75.object.effect = effect;
        }
    }
    if (self->unk7E-- == 0) {
        self->unk42 ^= 0x8000;
        self->ext.main_75.blink_delay -= 5;
        var_a0 = self->ext.main_75.blink_delay;
        var_a1 = var_a0 < 6 ? 5 : var_a0;
        self->unk7E = var_a1;
    }
}

// general_death_explode
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800915C4(struct MainObj* self)
{
    struct ObjectHeader* effect = OBJECT_HEADER(self->ext.main_75.object.effect);
    u16 timer;
    s32 column, row;

    self->on_screen = 0;
    if (effect->active == 0)
        return;
    if (effect->unk7 == 0) {
        timer = (u16)self->unk7E;
        self->unk7E = timer - 1;

        if (timer == 0) {
            self->unk7E = 5;
            self->unk42 ^= 0x8000;
        }
        return;
    }

    self->unk5++;
    background_objects[0].unk24 = background_objects[0].x_pos.u.hi;
    background_objects[0].unk26 = background_objects[0].x_pos.u.hi;
    background_objects[0].unk28 = background_objects[0].y_pos.u.hi;
    background_objects[0].unk2A = background_objects[0].y_pos.u.hi;
    self->unk40 = (OBJECT_STAGE_TEXTURE(1)) + OBJECT_TEXTURE_OFFSET(0xB0);
    self->sprite_frames = (const u8*)SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0xA3));
    column = func_8002938C(0xA3) * 4 + 0x18;
    row = func_8002938C(0xA3) + 6;
#ifdef MMX4_SATURN
    self->unk42 = column;
#else
    self->unk42 = (column % 16) | ((row / 4 + 0x1E0) << 6);
#endif
    self->animation_table = (const u8* const*)final_cutscene_animations;
    self->x_pos.u.hi = background_objects[0].x_pos.u.hi + 0xE0;
    self->y_pos.u.hi = background_objects[0].y_pos.u.hi + 0x68;
    self->unk15 = 0;
    set_animation(self, 0);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_75_general", func_800915C4);
#endif

void general_death_wait_explosion(struct MainObj* self)
{
    if (self->ext.main_75.object.child->active == 0) {
        player_start_script_action(0x14, PLAYER_FACING_RIGHT);
        self->unk7C = 0x78;
        self->unk5++;
    }
}

// general_death_finish
void func_800917AC(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk6 == 0) {
        self->unk7C = (u16)self->unk7C - 1;
        if (self->unk7C == 0) {
            start_screen_shake_y(10, 2, 2);
            self->unk7E = 10;
            func_8002217C(engine_obj.cur_character == 0 ? 0x2A : 0x22, 6, 0);
            self->unk6++;
        }
    } else {
        if (abc_object.unkC == 0)
            engine_obj.unkF = 1;
        self->unk7E = (u16)self->unk7E - 1;
        if (self->unk7E == 0) {
            start_screen_shake_y(10, 2, 2);
            self->unk7E = 10;
        }
    }
}

// general_death
void func_80091898(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    general_death_funcs[self->unk5](self);
    if (WEAPON_FRAME_COUNTER % 10 == 0) {
        self->y_pos.i.hi += self->ext.main_75.bob_step;
        if (--self->ext.main_75.bob_timer == 0) {
            self->ext.main_75.bob_timer = 0xA;
            self->ext.main_75.bob_step *= -1;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

void general_update(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    general_state_funcs[self->state](self);
}

struct Unk_unk68 D_801059BC = { -43, -48, 82, -125 };

struct Unk_unk68 D_801059C0 = { -28, -86, 38, 38 };

struct Unk_unk68 D_801059C4[5] = {
    { -34, -34, 57, 126 },
    { 0, 74, 12, 7 },
    { -14, -21, 30, 40 },
    { -14, -21, 30, 40 },
    { -16, 15, 12, 9 },
};

struct Unk_unk68 D_801059D8 = { 0, 18, 61, 9 };

struct Unk_unk68 D_801059DC = { 0, 71, 40, 11 };

union AnimationStep D_801059E0[] = {
    { 1, 0, 0, 0x00 },
};

union AnimationStep D_801059E4[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x03 },
    { 20, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x07 },
    { 40, 0, 1, 0x07 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x09 },
    { 40, 0, 1, 0x09 },
    { 27, 1, 1, 0x09 },
    { 1, 0, 0, 0x09 },
};

union AnimationStep D_80105A1C[] = {
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 20, 0, 0, 0x0E },
};

u8 D_80105A30[8] = { 1, 0, 1, 9, 1, 0, 255, 9 };

union AnimationStep D_80105A38[] = {
    { 2, 0, 1, 0x11 },
    { 1, 0, 1, 0x0E },
    { 1, 0, 0, 0x0E },
};

struct Unk_unk68 D_80105A44[3] = {
    { 1, 0, 1, 15 },
    { 1, 0, 1, 16 },
    { 1, 0, -2, 17 },
};

struct Unk_unk68 D_80105A50[3] = {
    { 1, 0, 1, 17 },
    { 1, 0, 1, 14 },
    { 1, 0, -2, 14 },
};

union AnimationStep D_80105A5C[] = {
    { 1, 0, 0, 0x0E },
};

u8 D_80105A60[8] = { 1, 0, 1, 23, 1, 0, 255, 23 };

union AnimationStep D_80105A68[] = {
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x19 },
    { 30, 0, 1, 0x19 },
    { 2, 1, 0, 0x19 },
};

union AnimationStep D_80105A78[] = {
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 1, 1, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x09 },
    { 19, 0, 1, 0x09 },
    { 1, 0, 0, 0x09 },
};

union AnimationStep D_80105AD4[] = {
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x17 },
    { 2, 1, 1, 0x1E },
    { 2, 0, 0, 0x1E },
};

union AnimationStep D_80105AE4[] = {
    { 1, 0, 0, 0x20 },
};

union AnimationStep D_80105AE8[] = {
    { 1, 0, 0, 0x21 },
};

union AnimationStep D_80105AEC[] = {
    { 2, 0, 1, 0x21 },
    { 2, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 2, 0, 1, 0x22 },
    { 20, 0, 0, 0x21 },
};

struct Unk_unk68 D_80105B00[4] = {
    { 1, 0, 1, 35 },
    { 1, 0, 1, 36 },
    { 1, 0, 1, 35 },
    { 1, 0, -3, 37 },
};

struct Unk_unk68 D_80105B10[3] = {
    { 1, 0, 1, 44 },
    { 1, 0, 1, 45 },
    { 1, 0, -2, 46 },
};

union AnimationStep D_80105B1C[] = {
    { 3, 0, 1, 0x22 },
    { 3, 0, 1, 0x2F },
    { 3, 1, 1, 0x30 },
    { 3, 0, 0, 0x32 },
};

union AnimationStep D_80105B2C[] = {
    { 1, 0, 0, 0x31 },
};

union AnimationStep D_80105B30[] = {
    { 2, 0, 1, 0x31 },
    { 2, 0, 1, 0x32 },
    { 2, 0, 1, 0x31 },
    { 2, 0, 1, 0x32 },
    { 20, 0, 0, 0x31 },
};

struct Unk_unk68 D_80105B44[4] = {
    { 1, 0, 1, 51 },
    { 1, 0, 1, 52 },
    { 1, 0, 1, 51 },
    { 1, 0, -3, 53 },
};

struct Unk_unk68 D_80105B54[3] = {
    { 1, 0, 1, 60 },
    { 1, 0, 1, 61 },
    { 1, 0, -2, 62 },
};

union AnimationStep D_80105B60[] = {
    { 3, 0, 1, 0x32 },
    { 3, 0, 1, 0x30 },
    { 3, 1, 1, 0x2F },
    { 3, 0, 0, 0x22 },
};

union AnimationStep D_80105B70[] = {
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x17 },
    { 2, 0, 0, 0x17 },
};

union AnimationStep D_80105B80[] = {
    { 2, 0, 1, 0x3F },
    { 2, 0, 1, 0x40 },
    { 2, 0, 1, 0x41 },
    { 2, 0, 1, 0x42 },
    { 2, 0, 1, 0x43 },
    { 2, 0, 1, 0x44 },
    { 2, 0, 1, 0x45 },
    { 2, 0, 0, 0x46 },
};

struct Unk_unk68 D_80105BA0[3] = {
    { 1, 0, 1, 71 },
    { 1, 0, 1, 72 },
    { 1, 1, -2, 73 },
};

union AnimationStep D_80105BAC[] = {
    { 2, 0, 1, 0x46 },
    { 2, 0, 1, 0x45 },
    { 2, 0, 1, 0x44 },
    { 2, 0, 1, 0x43 },
    { 2, 0, 1, 0x42 },
    { 2, 0, 1, 0x41 },
    { 2, 0, 1, 0x40 },
    { 2, 0, 0, 0x3F },
};

union AnimationStep D_80105BCC[] = {
    { 1, 0, 1, 0x4A },
    { 1, 0, 1, 0x4B },
    { 1, 0, 1, 0x4C },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4E },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x50 },
    { 1, 0, 0, 0x51 },
};

struct Unk_unk68 D_80105BEC[3] = {
    { 1, 0, 1, 81 },
    { 1, 0, 1, 81 },
    { 1, 1, -2, 81 },
};

union AnimationStep D_80105BF8[] = {
    { 1, 0, 1, 0x51 },
    { 1, 0, 1, 0x50 },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x4E },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4C },
    { 1, 0, 1, 0x4B },
    { 1, 0, 0, 0x4A },
};

union AnimationStep D_80105C18[] = {
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x53 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x53 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x53 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x53 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x53 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x53 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x53 },
    { 1, 0, 1, 0x54 },
    { 1, 0, 1, 0x52 },
    { 1, 0, 1, 0x53 },
    { 1, 0, 0, 0x54 },
};

struct Unk_unk68 D_80105C78[3] = {
    { 1, 0, 1, 85 },
    { 1, 0, 1, 86 },
    { 1, 0, -2, 87 },
};

struct Unk_unk68 D_80105C84[4] = {
    { 1, 0, 1, 88 },
    { 1, 0, 1, 89 },
    { 1, 0, 1, 90 },
    { 1, 0, -2, 91 },
};

struct Unk_unk68 D_80105C94[16] = {
    { 1, 0, 1, 92 },
    { 1, 0, 1, 94 },
    { 1, 0, 1, 93 },
    { 1, 0, 1, 94 },
    { 1, 0, 1, 92 },
    { 1, 0, 1, 95 },
    { 1, 0, 1, 93 },
    { 1, 0, 1, 95 },
    { 1, 0, 1, 92 },
    { 1, 0, 1, 96 },
    { 1, 0, 1, 93 },
    { 1, 0, 1, 96 },
    { 1, 0, 1, 92 },
    { 1, 0, 1, 95 },
    { 1, 0, 1, 93 },
    { 1, 0, -15, 95 },
};

struct Unk_unk68 D_80105CD4[16] = {
    { 1, 0, 1, 97 },
    { 1, 0, 1, 99 },
    { 1, 0, 1, 98 },
    { 1, 0, 1, 99 },
    { 1, 0, 1, 97 },
    { 1, 0, 1, 100 },
    { 1, 0, 1, 98 },
    { 1, 0, 1, 100 },
    { 1, 0, 1, 97 },
    { 1, 0, 1, 101 },
    { 1, 0, 1, 98 },
    { 1, 0, 1, 99 },
    { 1, 0, 1, 97 },
    { 1, 0, 1, 100 },
    { 1, 0, 1, 98 },
    { 1, 0, -15, 100 },
};

struct Unk_unk68 D_80105D14[8] = {
    { 1, 0, 1, 104 },
    { 1, 0, 1, 105 },
    { 1, 0, 1, 106 },
    { 1, 0, 1, 107 },
    { 1, 0, 1, 108 },
    { 1, 0, 1, 109 },
    { 1, 0, 1, 110 },
    { 1, 0, -7, 111 },
};

union AnimationStep D_80105D34[] = {
    { 1, 0, 0, 0x19 },
};

union AnimationStep D_80105D38[] = {
    { 2, 0, 1, 0x71 },
    { 2, 0, 1, 0x72 },
    { 2, 0, 1, 0x73 },
    { 2, 0, 1, 0x72 },
    { 2, 0, 1, 0x73 },
    { 2, 0, 1, 0x72 },
    { 2, 0, 0, 0x73 },
};

union AnimationStep D_80105D54[] = {
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
    { 1, 0, 1, 0x7E },
    { 1, 0, 1, 0x7F },
    { 1, 0, 1, 0x80 },
    { 1, 0, 1, 0x81 },
    { 1, 0, 1, 0x82 },
    { 1, 0, 1, 0x83 },
    { 1, 0, 1, 0x84 },
    { 1, 0, -17, 0x85 },
};

union AnimationStep D_80105D9C[] = {
    { 1, 0, 0, 0x86 },
};

union AnimationStep D_80105DA0[] = {
    { 1, 0, 0, 0x87 },
};

union AnimationStep D_80105DA4[] = {
    { 1, 0, 0, 0x88 },
};

union AnimationStep D_80105DA8[] = {
    { 1, 0, 0, 0x89 },
};

union AnimationStep D_80105DAC[] = {
    { 1, 0, 0, 0x8A },
};

union AnimationStep D_80105DB0[] = {
    { 1, 0, 0, 0x8B },
};

union AnimationStep D_80105DB4[] = {
    { 1, 0, 0, 0x8C },
};

void* general_animations[46] = {
    D_801059E0,
    D_801059E4,
    D_80105A1C,
    D_80105A30,
    D_80105A38,
    D_80105A44,
    D_80105A50,
    D_80105A5C,
    D_80105A60,
    D_80105A68,
    D_80105A78,
    D_80105AD4,
    D_80105AE4,
    D_80105AE8,
    D_80105AEC,
    D_80105B00,
    D_80105B10,
    D_80105B1C,
    D_80105B2C,
    D_80105B30,
    D_80105B44,
    D_80105B54,
    D_80105B60,
    D_80105B70,
    D_80105B80,
    D_80105BA0,
    D_80105BAC,
    D_80105BCC,
    D_80105BEC,
    D_80105BF8,
    D_80105C18,
    D_80105C78,
    D_80105C84,
    D_80105C94,
    D_80105CD4,
    D_80105D14,
    D_80105D34,
    D_80105D38,
    D_80105D54,
    D_80105D9C,
    D_80105DA0,
    D_80105DA4,
    D_80105DA8,
    D_80105DAC,
    D_80105DB0,
    D_80105DB4,
};

u8 D_80105E70[4] = { 3, 3, 255, 0 };

union AnimationStep D_80105E74[] = {
    { 4, -1, 0, 0x00 },
};

u8 D_80105E78[4] = { 3, 5, 5, 255 };

void* D_80105E7C[2] = {
    D_80105E70,
    D_80105E74,
};

void* D_80105E84[2] = {
    D_80105E74,
    D_80105E78,
};

void* general_scripts[2] = {
    D_80105E7C,
    D_80105E84,
};

u8 general_script_weights[4] = { 0x09, 0x10, 0x09, 0x10 };

void (*general_intro_funcs[])(struct MainObj*) = {
    general_intro_wait_player,
    func_8008FBCC,
    general_intro_lock_camera,
    general_intro_enter,
    general_intro_land,
    general_intro_dialogue,
    general_intro_fill_health,
    general_intro_finish,
};

void (*general_fly_funcs[3])() = { general_fly_descend, general_fly_start, func_800905D4 };

void (*general_punch_funcs[6])() = {
    general_punch_rise,
    general_punch_launch,
    general_punch_wait,
    general_punch_rings,
    general_punch_wait_return,
    general_punch_recover,
};

void (*general_orbs_funcs[4])() = { general_orbs_descend, general_orbs_fire, general_orbs_wait, general_orbs_recover };

void (*general_slam_funcs[6])(struct MainObj*) = {
    general_slam_windup,
    general_slam_fall,
    general_slam_land,
    general_slam_rise,
    general_slam_ascend,
    general_slam_leave,
};

void (*general_step_funcs[7])() = {
    enemy_hit_reaction,
    general_resume_step,
    func_8009027C,
    general_fly,
    general_punch,
    general_orbs,
    general_slam,
};

#ifdef MMX4_PC
void (*general_death_funcs[5])(struct MainObj*) = {
#else
void (*general_death_funcs[5])() = {
#endif
    general_death_start,
    general_death_blink,
    func_800915C4,
    general_death_wait_explosion,
    func_800917AC,
};

void (*general_state_funcs[])(struct MainObj*) = {
    general_intro,
    func_80091218,
    func_80091898,
};
