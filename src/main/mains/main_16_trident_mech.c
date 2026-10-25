// MainObj, main_object_update_funcs[16]
// 8004E890..8004FF90
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_16_trident_mech.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/1CF60.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1CF60.h"
#endif

extern struct Unk_unk68 trident_mech_charge_attack_box;

void trident_mech_check_fall(struct MainObj*);

extern u8 trident_mech_debris[12];

// trident_mech_state_funcs
extern void (*trident_mech_state_funcs[])(struct MainObj*);

void trident_mech_explode(struct MainObj*);
void trident_mech_despawn(struct MainObj*);

// trident_mech_step_funcs
extern void (*trident_mech_step_funcs[11])();

void trident_mech_idle(struct MainObj* arg0);
void trident_mech_fall(struct MainObj* arg0);
void trident_mech_jump(struct MainObj* arg0);
void func_8004F1A0(struct MainObj* arg0);
void trident_mech_charge(struct MainObj* arg0);
void trident_mech_fan_shot(struct MainObj* arg0);
void trident_mech_double_shot(struct MainObj* arg0);

void trident_mech_wait_behind(struct MainObj* arg0);

// trident_mech_idle_funcs
void trident_mech_idle_start(struct MainObj*);

void trident_mech_jump_start(struct MainObj*);
void trident_mech_jump_rise(struct MainObj*);

// trident_mech_charge_funcs
void trident_mech_charge_start(struct MainObj*);
void trident_mech_charge_wind_up(struct MainObj*);
void trident_mech_charge_attack(struct MainObj*);

void trident_mech_fan_shot_end(struct MainObj*);

void trident_mech_double_shot_recover(struct MainObj*);

extern void (*trident_mech_idle_funcs[])(struct MainObj*);
extern void (*trident_mech_jump_funcs[])(struct MainObj*);
extern void (*trident_mech_charge_funcs[])(struct MainObj*);
extern void (*trident_mech_fan_shot_funcs[])(struct MainObj*);
extern void (*trident_mech_double_shot_funcs[])(struct MainObj*);

void trident_mech_face_player(struct AnimatedObj* self);
void trident_mech_fire_tracked_shot(struct MainObj* self);

void trident_mech_update(struct MainObj* self)
{
    trident_mech_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

// trident_mech_init

extern union AnimationStep* trident_mech_animations[];
extern struct Unk_unk68 D_800FBBC8;
extern struct Unk_unk68 D_80106A74[];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004E8E0(struct MainObj* arg0);
void func_8004FD38(struct MainObj* arg0, s32 animation);
void func_8004ED60(struct MainObj* arg0);
void func_8004FAE4(struct MainObj* self);
extern void* common_effect_animations[];
extern ret_u8 func_8002938C(s32);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_16_trident_mech", func_8004E8E0);
#else
void func_8004E8E0(struct MainObj* arg0)
{
    arg0->hp = 0x10;
    arg0->contact_damage = 3;
    arg0->invincibility_timer = 0;
    arg0->collision_data = D_80106A74;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)trident_mech_animations;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->terrain_box = &D_800FBBC8;
    arg0->hurt_box = &trident_mech_stunned_hurt_box;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->attack_box = &trident_mech_attack_box;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    trident_mech_face_player(ANIMATED_OBJECT(arg0));

    arg0->ext.main_16.unk80 = 0;
    arg0->ext.main_16.unk84 = 0;
    arg0->ext.main_16.unk8C = 0;
    arg0->ext.main_16.unk90 = 0;
    arg0->ext.main_16.shot_09_active = 1;

    switch (arg0->unk2) {
    case 0:
        set_animation(ANIMATED_OBJECT(arg0), 0);
        arg0->unk5 = 2;
        break;
    case 1:
        set_animation(ANIMATED_OBJECT(arg0), 2);
        arg0->unk5 = 2;
        break;
    case 2:
        set_animation(ANIMATED_OBJECT(arg0), 1);
        arg0->unk7C = 0x14;
        arg0->unk5 = 9;
        break;
    case 3:
        set_animation(ANIMATED_OBJECT(arg0), 2);
        arg0->unk5 = 0xA;
        break;
    case 4:
        set_animation(ANIMATED_OBJECT(arg0), 0x11);
        arg0->unk7E = 3;
        arg0->unk5 = 8;
        arg0->unk42 += 2;
        break;
    case 5:
        set_animation(ANIMATED_OBJECT(arg0), 2);
        arg0->unk7E = 3;
        arg0->unk5 = 2;
        arg0->unk42 += 2;
        break;
    }

    arg0->state = 1;
    arg0->unk6 = 0;
    arg0->unk7 = 0;
}
#endif

void trident_mech_main(struct MainObj* self)
{
    s32 collision;

    trident_mech_check_fall(self);
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    if (self->unk7 == 0) {
        func_8004FD38(self, 2);
        self->unk7 = 1;
    }

    trident_mech_step_funcs[self->unk5](self);
    if (self->unk5 == 0xA) {
        return;
    }

    if (engine_obj.character_state.bytes[0] != 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(0xB, trident_mech_debris, self);
        self->ext.main_16.shot_09_active = 0;
        self->unk7C = 0x20;
        self->unk7E = 6;
        self->on_screen = 0;
        self->state = 2;
        return;
    }

    func_8002D9BC(self);
    collision = func_8002DD04(self);
    if (collision < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(0xB, trident_mech_debris, self);
        drop_item(BASE_OBJECT(self), 0x13);
        self->ext.main_16.shot_09_active = 0;
        self->unk7C = 0x20;
        self->unk7E = 6;
        self->on_screen = 0;
        self->state = 2;
        return;
    }

    if ((collision == 0x1B || collision == 0x1C) && self->ext.main_16.unk8C != 1) {
        self->hurt_box = &trident_mech_stunned_hurt_box;
        set_animation(self, 0xE);
        self->ext.main_16.unk90 = 0;
        self->unk5 = 1;
        self->unk6 = 0;
    }

    if (self->state == 2) {
        return;
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x68, 0xA8) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x48, 0x48);
        return;
    }
    self->ext.main_16.shot_09_active = 0;
    self->state = 3;
}

void trident_mech_explode(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->state = 3;
    } else if (--self->unk7E == 0) {
        self->unk7E = 6;
        func_800AF878(self, 1, 24, 32);
    }
}

void trident_mech_despawn(struct MainObj* self)
{
    self->ext.main_16.unk80 = 0;
    self->ext.main_16.unk84 = 0;
    self->ext.main_16.unk88 = 0;
    self->ext.main_16.unk8C = 0;
    self->ext.main_16.unk90 = 0;
    self->ext.main_16.shot_09_active = 0;
    despawn_object(OBJECT_HEADER(self));
}

void trident_mech_idle(struct MainObj* self)
{
    trident_mech_idle_funcs[self->unk6](self);
}

void trident_mech_idle_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->unk7C = 0x1E;
    self->unk6 = 1;
    self->ext.main_16.unk8C = 2;
}

// trident_mech_idle_think
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_16_trident_mech", func_8004ED60);
#else
#define TRIDENT_STATE6(arg0)                                    \
    do {                                                        \
        (arg0)->ext.main_16.unk8C = 1;                          \
        (arg0)->invincibility_timer = engine_obj.cur_character; \
        trident_mech_fire_tracked_shot(arg0);                   \
        (arg0)->unk5 = 6;                                       \
        (arg0)->unk6 = 0;                                       \
    } while (0)
#define TRIDENT_STATE4(arg0)                        \
    do {                                            \
        set_animation(ANIMATED_OBJECT(arg0), 0x10); \
        (arg0)->ext.main_16.unk80 = 1;              \
        (arg0)->ext.main_16.unk90 = 1;              \
        (arg0)->unk5 = 4;                           \
        (arg0)->unk6 = 0;                           \
    } while (0)
void func_8004ED60(struct MainObj* arg0)
{
    s8 random;

    trident_mech_face_player(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    if (--arg0->unk7C != 0)
        return;
    arg0->ext.main_16.unk8C = 0;
    if ((g_Player.x_pos.i.hi - arg0->x_pos.i.hi < 0 ? arg0->x_pos.i.hi - g_Player.x_pos.i.hi : g_Player.x_pos.i.hi - arg0->x_pos.i.hi) <= 0x60) {
        if (weapon_objects[0].active == 0 && (get_random() & 7) >= 5) {
            TRIDENT_STATE4(arg0);
        } else {
            arg0->ext.main_16.unk8C = 1;
            arg0->invincibility_timer = engine_obj.cur_character;
            trident_mech_fire_tracked_shot(arg0);
            arg0->unk5 = 6;
            arg0->unk6 = 0;
        }
        return;
    }
    random = get_random() & 0xF;
    if (weapon_objects[0].active != 0) {
        if (random < 0xC) {
            set_animation(ANIMATED_OBJECT(arg0), 0x10);
            arg0->ext.main_16.unk80 = 0;
            arg0->ext.main_16.unk90 = 1;
            arg0->unk5 = 4;
            arg0->unk6 = 0;
        } else if (random >= 0xE) {
            TRIDENT_STATE6(arg0);
        } else {
            TRIDENT_STATE4(arg0);
        }
    } else if (random < 0xC) {
        set_animation(ANIMATED_OBJECT(arg0), 0x11);
        arg0->unk5 = 8;
        arg0->unk6 = 0;
    } else if (random < 0xE) {
        TRIDENT_STATE4(arg0);
    } else {
        TRIDENT_STATE6(arg0);
    }
}
#endif

void trident_mech_fall(struct MainObj* self)
{
    if (self->collision_flags & 8) {
        set_animation(self, 3);
        self->hurt_box = (const u8*)&trident_mech_hurt_box;
        self->air_state = 0;
        func_8004FD38(self, 5);
        func_8004FD38(self, 2);
        self->unk5 = 5;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = 0;
        return;
    }

    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

void trident_mech_jump(struct MainObj* self)
{
    trident_mech_jump_funcs[self->unk6](self);
}

void trident_mech_jump_launch_pod(struct MainObj* self)
{
    struct MiscObj* misc;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        misc = find_free_misc_obj();
        if (misc != 0) {
            misc->active = 0x41;
            misc->id = 5;
            misc->unk40 = self->unk40;
            misc->unk42 = self->unk42 & 0x7FFF;
            misc->animation_table = (u32**)self->animation_table;
            misc->unk3C = (void*)self->sprite_frames;
            misc->bg_offset = self->bg_offset;
            misc->x_pos.val = self->x_pos.val;
            misc->y_pos.val = self->y_pos.val;
            misc->unk15 = self->unk15;
            misc->ext.misc_7.position = &self->ext.main_16.unk90;
            misc->state = 0;
        }
        func_8004FD38(self, 5);
        set_animation(self, 2);
        self->unk6 = 1;
    }
}

void trident_mech_jump_start(struct MainObj* self)
{
    self->y_speed = FIXED(8.25);
    self->gravity = FIXED(0.375);
    self->air_state = 1;
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    self->unk6 = 2;
}

void trident_mech_jump_rise(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->y_speed == 0) {
        self->ext.main_16.unk90 = 0;
        if (self->ext.main_16.unk80 == 0) {
            self->unk5 = 2;
            self->unk6 = 0;
            self->air_state = 0;
            return;
        }
        trident_mech_face_player(ANIMATED_OBJECT(self));
        set_animation(self, 6);
        self->ext.main_16.unk80 = 0;
        self->unk5 = 7;
        self->unk6 = 0;
    }
}

// trident_mech_land
void func_8004F1A0(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 0) {
        return;
    }
    self->hurt_box = &trident_mech_stunned_hurt_box;
    trident_mech_face_player(ANIMATED_OBJECT(self));
    if (self->unk2 >= 4) {
        self->unk7E = 3;
        set_animation(ANIMATED_OBJECT(self), 0x11);
        self->unk5 = 8;
    } else {
        set_animation(ANIMATED_OBJECT(self), 0);
        self->unk5 = 2;
    }
    self->unk6 = 0;
}

void trident_mech_charge(struct MainObj* self)
{
    trident_mech_charge_funcs[self->unk6](self);
}

void trident_mech_charge_start(struct MainObj* self)
{
    set_animation(self, 4);
    self->unk7C = 0x1E;
    self->unk6 = 1;
}

void trident_mech_charge_wind_up(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk7C % 10 == 0) {
        func_8001540C(2, SATURN_SOUND(0x27, 0x20), self);
    }
    if (--self->unk7C == 0) {
        set_animation(self, 0xD);
        self->invincibility_timer = 0;
        self->unk6 = 2;
        self->ext.main_16.unk88 = 0;
    }
}

void trident_mech_charge_attack(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->unk7C = (u16)self->unk7C ^ self->ext.main_16.unk88;
    if (self->unk7C == 0) {
        self->contact_damage = 3;
        self->attack_box = &trident_mech_attack_box;
    } else {
        self->contact_damage = 6;
        self->attack_box = &trident_mech_charge_attack_box;
    }
    if (self->animation_step.fields.event == 2) {
        self->ext.main_16.unk88 = 1;
        func_8001540C(2, SATURN_SOUND(0x28, 0x21), self);
    }
    if (self->animation_step.fields.event == 1) {
        self->contact_damage = 3;
        self->attack_box = &trident_mech_attack_box;
        trident_mech_face_player(ANIMATED_OBJECT(self));
        set_animation(self, 0);
        self->ext.main_16.unk8C = 0;
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void trident_mech_fan_shot(struct MainObj* self)
{
    trident_mech_fan_shot_funcs[self->unk6](self);
}

void trident_mech_fan_shot_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 7);
        self->unk6 = 1;
        self->unk7C = 8;
        self->ext.main_16.unk80 = 0x18;
        self->ext.main_16.unk88 = 0;
        if (self->unk15 == 0) {
            self->ext.main_16.unk84 = -4;
        } else {
            self->ext.main_16.unk84 = 4;
        }
    }
}

void trident_mech_fan_shot_fire(struct MainObj* self)
{
    struct ShotObj* shot;
    u8 facing;

    animate_object(ANIMATED_OBJECT(self));
    if (self->unk7C == 8) {
        func_8001540C(2, SATURN_SOUND(0x27, 0x20), self);
    }
    if (--self->unk7C == 0) {
        func_8001540C(2, SATURN_SOUND(0x29, 0x22), self);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 9;
            shot->unk2 = self->ext.main_16.unk88;
            shot->unk40 = self->unk40;
            shot->unk42 = self->unk42;
            shot->animation_table = (u32**)self->animation_table;
            shot->unk3C = (void*)self->sprite_frames;
            shot->bg_offset = self->bg_offset;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            facing = self->unk15;
            shot->state = 3;
            shot->unk15 = facing;
        }

        self->ext.main_16.unk80 &= 0x1F;
#ifdef MMX4_PC
        if (shot != NULL)
#endif
            set_velocity_from_angle(MOVING_OBJECT(shot), (u8)self->ext.main_16.unk80);
        self->ext.main_16.unk80 += self->ext.main_16.unk84;
        if ((s32)self->ext.main_16.unk80 < 0x10) {
            set_animation(self, 7);
            self->unk6 = 2;
        } else {
            self->unk7C = 8;
            self->ext.main_16.unk88++;
        }
    }
}

void trident_mech_fan_shot_end(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 2);
        self->unk5 = 2;
        self->unk6 = 0;
        self->air_state = 0;
    }
}

void trident_mech_double_shot(struct MainObj* self)
{
    trident_mech_double_shot_funcs[self->unk6](self);
}

void trident_mech_double_shot_first(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 0) {
        return;
    }

    set_animation(self, 0x12);
    func_8001540C(2, SATURN_SOUND(0x29, 0x22), self);
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 9;
        shot->unk2 = 3;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->animation_table = (u32**)self->animation_table;
        shot->unk3C = (void*)self->sprite_frames;
        shot->unk15 = self->unk15;
        shot->bg_offset = self->bg_offset;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->unk15 = self->unk15;
        if (self->unk15 == 0) {
            shot->x_vel.val = FIXED(-1);
        } else {
            shot->x_vel.val = FIXED(1);
        }
        shot->y_vel.val = 0;
        shot->state = 3;
    }
    self->unk7C = 0x14;
    self->unk6 = 1;
}

void trident_mech_double_shot_second(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C != 0) {
        return;
    }

    set_animation(self, 0x13);
    func_8001540C(2, SATURN_SOUND(0x29, 0x22), self);
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 9;
        shot->unk2 = 4;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->animation_table = (u32**)self->animation_table;
        shot->unk3C = (void*)self->sprite_frames;
        shot->unk15 = self->unk15;
        shot->bg_offset = self->bg_offset;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->unk15 = self->unk15;
        if (self->unk15 == 0) {
            shot->x_vel.val = FIXED(-1);
        } else {
            shot->x_vel.val = FIXED(1);
        }
        shot->y_vel.val = 0;
        shot->state = 3;
    }
    if (self->unk2 >= 4) {
        trident_mech_face_player(ANIMATED_OBJECT(self));
        self->unk7C = 0x3C;
    } else {
        self->unk7C = 0x14;
    }
    self->unk6 = 2;
}

void trident_mech_double_shot_recover(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C != 0) {
        return;
    }
    if (self->unk2 >= 4) {
        if (--self->unk7E != 0) {
            self->unk6 = 0;
            return;
        }
        set_animation(self, 0x10);
        self->ext.main_16.unk80 = 1;
        self->ext.main_16.unk90 = 1;
        self->unk5 = 4;
    } else {
        set_animation(self, 0);
        self->unk5 = 2;
    }
    self->unk6 = 0;
}

void trident_mech_throw_pod(struct MainObj* self)
{
    struct MiscObj* misc;

    if (--self->unk7C == 0) {
        misc = find_free_misc_obj();
        if (misc != NULL) {
            misc->active = 0x41;
            misc->id = 5;
            misc->unk2 = 0;
            misc->unk40 = self->unk40;
            misc->unk42 = self->unk42 & 0x7FFF;
            misc->animation_table = self->animation_table;
            misc->unk3C = self->sprite_frames;
            misc->unk15 = self->unk15;
            misc->bg_offset = (s8)(u8)self->bg_offset;
            misc->x_pos.val = self->x_pos.val;
            misc->y_pos.val = self->y_pos.val;
            misc->unk15 = self->unk15;
            misc->ext.misc_5.animation = 0x14;
            misc->state = 3;
        }
        self->ext.main_16.unk80 = 0;
        self->ext.main_16.unk90 = 1;
        self->unk5 = 4;
        self->unk6 = 0;
    }
}

void trident_mech_wait_behind(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi - self->x_pos.i.hi > 0x10) {
        self->unk5 = 2;
        self->y_pos.i.hi -= 0x28;
    }
}

// trident_mech_stunned
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_16_trident_mech", func_8004FAE4);
#else
void func_8004FAE4(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->contact_damage = 3;
    if (self->animation_step.fields.event == 0)
        return;

    self->hurt_box = &trident_mech_stunned_hurt_box;
    if (self->unk2 >= 4) {
        if (!(self->collision_flags & 8)) {
            self->air_state = 0;
            self->y_speed = 0;
            self->gravity = 0;
            self->unk5 = 2;
        } else {
            set_animation(ANIMATED_OBJECT(self), 0x11);
            self->unk5 = 8;
        }
    } else if (!(self->collision_flags & 8)) {
        self->air_state = 0;
        self->y_speed = 0;
        self->gravity = 0;
        self->unk5 = 2;
    } else {
        func_8004FD38(self, 2);
        if (self->ext.main_16.unk8C != 0 && (get_random() & 4)) {
            self->invincibility_timer = (u8)engine_obj.cur_character;
            trident_mech_fire_tracked_shot(self);
            self->ext.main_16.unk8C = 1;
            self->unk5 = 6;
        } else {
            set_animation(ANIMATED_OBJECT(self), 0);
            self->unk5 = 2;
        }
    }
    self->unk6 = 0;
}
#endif

void trident_mech_check_fall(struct MainObj* self)
{
    if ((self->air_state == 0) && (self->unk5 != 0xA) && !(self->collision_flags & 8)) {
        self->unk5 = 3;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->x_accel = 0;
        self->air_state = 1;
    }
}

void trident_mech_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
}

void trident_mech_fire_tracked_shot(struct MainObj* obj)
{
    struct ShotObj* shot;

    shot = find_free_shot_obj();

    if (shot != 0) {

        shot->active = 0x41;
        shot->id = 9;
        shot->unk2 = 0;
        shot->unk40 = obj->unk40;
        shot->unk42 = obj->unk42;
        shot->animation_table = ANIMATED_OBJECT(obj)->animation_table;
        shot->unk3C = ANIMATED_OBJECT(obj)->unk3C;
        shot->unk15 = obj->unk15;
        shot->bg_offset = obj->bg_offset;
        shot->x_pos.val = obj->x_pos.val;
        shot->y_pos.val = obj->y_pos.val;
        shot->unk15 = obj->unk15;
        shot->unk7C = (struct WeaponObj*)&obj->ext.main_16.shot_09_active;
        shot->state = 0;
    }
}

// trident_mech_set_part
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004FD38(struct MainObj* arg0, s32 animation)
{
    struct MiscObj* misc;
    struct Unk_unk68* bounds;
    s16 x;
    s16 y;
    s32 resource;

    if (arg0->air_state != 0)
        return;

    bounds = arg0->terrain_box;
    x = arg0->x_pos.i.hi + bounds->unk0;
    y = arg0->y_pos.i.hi + bounds->unk1 + bounds->unk3 - 4;
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) != 0x24)
        return;

    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 5;
        misc->animation_table = (u32**)common_effect_animations;
        misc->unk42 = OBJECT_CLUT(0x7888);
        misc->unk40 = (u16)((u32)OBJECT_STAGE_TEXTURE(4));
        misc->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 4);
        misc->bg_offset = arg0->bg_offset;
        misc->y_pos.val = arg0->y_pos.val + FIXED(6);
        misc->unk15 = arg0->unk15;
        if ((s8)animation == 2) {
            misc->unk2 = 1;
            misc->ext.misc_5.owner = arg0;
            misc->x_pos.val = arg0->x_pos.val - FIXED(13);
        } else {
            misc->unk2 = 0;
            misc->x_pos.val = arg0->x_pos.val;
        }
        misc->ext.misc_5.animation = (s8)animation;
        misc->state = 3;
    }

    if ((s8)animation != 2)
        return;

    misc = find_free_misc_obj();
    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 5;
    misc->unk2 = 1;
    misc->animation_table = (u32**)common_effect_animations;
    resource = func_8002938C(0x84);
    misc->unk40 = (u16)((u32)OBJECT_STAGE_TEXTURE(resource));
    resource = func_8002938C(0x84);
    misc->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, resource);
    misc->unk42 = OBJECT_CLUT(0x7888);
    misc->bg_offset = arg0->bg_offset;
    misc->y_pos.val = arg0->y_pos.val + FIXED(6);
    misc->unk15 = arg0->unk15;
    misc->state = 3;
    misc->ext.misc_5.animation = (s8)animation;
    misc->ext.misc_5.owner = arg0;
    misc->x_pos.val = arg0->x_pos.val + FIXED(13);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_16_trident_mech", func_8004FD38);
#endif

struct Unk_unk68 trident_mech_stunned_hurt_box = { -14, -28, 30, 59 };

struct Unk_unk68 trident_mech_hurt_box = { -16, -8, 34, 37 };

struct Unk_unk68 trident_mech_attack_box = { -11, -17, 19, 47 };

struct Unk_unk68 trident_mech_charge_attack_box = { -89, -1, 69, 13 };

struct Unk_unk68 D_800FBBC8 = { 2, 2, 18, 26 };

union AnimationStep trident_mech_anim_0[] = {
    { 7, 0, 1, 0x00 },
    { 1, 1, 0, 0x00 },
};

union AnimationStep trident_mech_anim_1[] = {
    { 7, 0, 1, 0x01 },
    { 1, 1, 0, 0x01 },
};

union AnimationStep trident_mech_anim_2[] = {
    { 3, 0, 1, 0x0A },
    { 3, 1, -1, 0x0B },
};

union AnimationStep trident_mech_anim_16[] = {
    { 1, 0, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 1, 1, 0, 0x0C },
};

union AnimationStep trident_mech_anim_3[] = {
    { 8, 0, 1, 0x0C },
    { 8, 0, 1, 0x0D },
    { 27, 0, 1, 0x0C },
    { 1, 1, 0, 0x0C },
};

union AnimationStep trident_mech_anim_4[] = {
    { 3, 0, 1, 0x02 },
    { 1, 1, 0, 0x03 },
};

union AnimationStep trident_mech_anim_5[] = {
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x08 },
    { 1, 0, 1, 0x09 },
    { 1, 0, 1, 0x07 },
    { 1, 0, 1, 0x05 },
    { 1, 1, -5, 0x06 },
};

union AnimationStep trident_mech_anim_6[] = {
    { 2, 0, 1, 0x11 },
    { 1, 1, 0, 0x11 },
};

union AnimationStep trident_mech_anim_7[] = {
    { 1, 0, 1, 0x0E },
    { 1, 0, 1, 0x10 },
    { 1, 1, -2, 0x0F },
};

union AnimationStep trident_mech_anim_10[] = {
    { 1, 0, 1, 0x12 },
    { 1, 1, -1, 0x13 },
};

union AnimationStep trident_mech_anim_9[] = {
    { 1, 0, 1, 0x14 },
    { 1, 1, -1, 0x15 },
};

union AnimationStep trident_mech_anim_8[] = {
    { 1, 0, 1, 0x16 },
    { 1, 1, -1, 0x17 },
};

union AnimationStep trident_mech_anim_13[] = {
    { 20, 0, 1, 0x18 },
    { 2, 0, 1, 0x1A },
    { 1, 2, 1, 0x19 },
    { 1, 0, 1, 0x19 },
    { 1, 0, 1, 0x1B },
    { 19, 0, 1, 0x1C },
    { 1, 1, 0, 0x1C },
};

union AnimationStep trident_mech_anim_14[] = {
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1D },
    { 1, 0, 1, 0x1E },
    { 1, 1, 0, 0x1E },
};

union AnimationStep trident_mech_anim_15[] = {
    { 2, 0, 1, 0x1F },
    { 2, 0, 1, 0x20 },
    { 2, 0, -2, 0x21 },
};

union AnimationStep trident_mech_anim_17[] = {
    { 8, 0, 1, 0x00 },
    { 2, 0, 1, 0x23 },
    { 34, 0, 1, 0x22 },
    { 1, 1, 0, 0x22 },
};

union AnimationStep trident_mech_anim_18[] = {
    { 2, 0, 1, 0x24 },
    { 14, 0, 1, 0x25 },
    { 1, 1, 0, 0x25 },
};

union AnimationStep trident_mech_anim_19[] = {
    { 2, 0, 1, 0x26 },
    { 14, 0, 1, 0x27 },
    { 1, 1, 0, 0x27 },
};

union AnimationStep trident_mech_anim_11[] = {
    { 2, 0, 1, 0x28 },
    { 2, 1, -1, 0x29 },
};

union AnimationStep trident_mech_anim_12[] = {
    { 2, 0, 1, 0x2A },
    { 2, 0, -1, 0x2B },
};

union AnimationStep trident_mech_anim_20[] = {
    { 3, 0, 1, 0x2C },
    { 3, 0, 1, 0x2D },
    { 3, 0, 1, 0x2E },
    { 3, 0, 1, 0x2F },
    { 3, 0, 1, 0x30 },
    { 3, 0, 1, 0x31 },
    { 3, 0, 1, 0x32 },
    { 2, 0, 1, 0x33 },
    { 1, 1, 0, 0x33 },
};

union AnimationStep trident_mech_anim_21[] = {
    { 1, 1, 0, 0x34 },
};

union AnimationStep trident_mech_anim_22[] = {
    { 1, 1, 0, 0x35 },
};

union AnimationStep trident_mech_anim_23[] = {
    { 1, 1, 0, 0x36 },
};

union AnimationStep trident_mech_anim_24[] = {
    { 1, 1, 0, 0x37 },
};

union AnimationStep trident_mech_anim_25[] = {
    { 1, 1, 0, 0x38 },
};

union AnimationStep trident_mech_anim_26[] = {
    { 1, 1, 0, 0x39 },
};

union AnimationStep trident_mech_anim_27[] = {
    { 1, 1, 0, 0x3A },
};

union AnimationStep trident_mech_anim_28[] = {
    { 1, 1, 0, 0x3B },
};

union AnimationStep* trident_mech_animations[29] = {
    trident_mech_anim_0,
    trident_mech_anim_1,
    trident_mech_anim_2,
    trident_mech_anim_3,
    trident_mech_anim_4,
    trident_mech_anim_5,
    trident_mech_anim_6,
    trident_mech_anim_7,
    trident_mech_anim_8,
    trident_mech_anim_9,
    trident_mech_anim_10,
    trident_mech_anim_11,
    trident_mech_anim_12,
    trident_mech_anim_13,
    trident_mech_anim_14,
    trident_mech_anim_15,
    trident_mech_anim_16,
    trident_mech_anim_17,
    trident_mech_anim_18,
    trident_mech_anim_19,
    trident_mech_anim_20,
    trident_mech_anim_21,
    trident_mech_anim_22,
    trident_mech_anim_23,
    trident_mech_anim_24,
    trident_mech_anim_25,
    trident_mech_anim_26,
    trident_mech_anim_27,
    trident_mech_anim_28,
};

u8 trident_mech_debris[12] = { 21, 22, 23, 24, 25, 25, 25, 25, 26, 27, 28, 0 };

void (*trident_mech_state_funcs[4])() = {
    func_8004E8E0,
    trident_mech_main,
    trident_mech_explode,
    trident_mech_despawn,
};

void (*trident_mech_step_funcs[11])() = {
    enemy_hit_reaction,
    func_8004FAE4,
    trident_mech_idle,
    trident_mech_fall,
    trident_mech_jump,
    func_8004F1A0,
    trident_mech_charge,
    trident_mech_fan_shot,
    trident_mech_double_shot,
    trident_mech_throw_pod,
    trident_mech_wait_behind,
};

void (*trident_mech_idle_funcs[2])() = {
    trident_mech_idle_start,
    func_8004ED60,
};

void (*trident_mech_jump_funcs[3])(struct MainObj*) = {
    trident_mech_jump_launch_pod,
    trident_mech_jump_start,
    trident_mech_jump_rise,
};

void (*trident_mech_charge_funcs[3])(struct MainObj*) = {
    trident_mech_charge_start,
    trident_mech_charge_wind_up,
    trident_mech_charge_attack,
};

void (*trident_mech_fan_shot_funcs[3])(struct MainObj*) = {
    trident_mech_fan_shot_start,
    trident_mech_fan_shot_fire,
    trident_mech_fan_shot_end,
};

void (*trident_mech_double_shot_funcs[3])(struct MainObj*) = {
    trident_mech_double_shot_first,
    trident_mech_double_shot_second,
    trident_mech_double_shot_recover,
};
