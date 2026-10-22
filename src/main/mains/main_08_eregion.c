// MainObj, main_object_update_funcs[8]
// 80047C88..800498C0
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_08_eregion.h"
#include "main/objects.h"
#include "main/player_common.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/stage_objects.h"
#include "main/visuals/visual_08_ice_shard.h"
#include "main/collision_bounds.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

// eregion_state_funcs
extern void (*eregion_state_funcs[])(struct MainObj*);

void eregion_death(struct MainObj* arg0);

void eregion_roar(struct MainObj* arg0);
void eregion_stomp(struct MainObj* arg0);
void eregion_leap(struct MainObj* arg0);
void eregion_wing_slash(struct MainObj* arg0);
void eregion_pounce(struct MainObj* arg0);
void eregion_spread(struct MainObj* arg0);
void eregion_fireball(struct MainObj* arg0);
void eregion_intro(struct MainObj* arg0);

// eregion_roar_funcs
void eregion_roar_start(struct MainObj*);
void eregion_roar_wait(struct MainObj*);

// eregion_stomp_funcs
void eregion_stomp_lift(struct MainObj* arg0);
void eregion_stomp_step(struct MainObj*);
void eregion_stomp_follow(struct MainObj*);
void eregion_stomp_advance(struct MainObj*);
void eregion_stomp_drop(struct MainObj*);
void eregion_stomp_land(struct MainObj*);

// eregion_leap_funcs
void eregion_leap_crouch(struct MainObj*);
void eregion_leap_jump(struct MainObj*);
void eregion_leap_rise(struct MainObj*);
void eregion_fall(struct MainObj*);
void eregion_land(struct MainObj*);

// eregion_pounce_funcs
void eregion_pounce_crouch(struct MainObj*);
void eregion_pounce_jump(struct MainObj*);

// eregion_death_funcs
void eregion_death_start(struct MainObj*);

void eregion_death_wait_explosion(struct MainObj*);

// eregion_recoil_funcs
extern void (*eregion_recoil_funcs[])(struct MainObj*);

void func_8004970C(struct MainObj*);
void eregion_intro_fill_health(struct MainObj*);

extern void (*eregion_roar_funcs[])(struct MainObj*);
extern void (*eregion_stomp_funcs[])(struct MainObj*);
extern void (*eregion_leap_funcs[])(struct MainObj*);
extern void (*eregion_wing_slash_funcs[])(struct MainObj*);
extern void (*eregion_pounce_funcs[])(struct MainObj*);
extern void (*eregion_fireball_funcs[])(struct MainObj*);
extern void (*eregion_spread_funcs[])(struct MainObj*);
extern void (*eregion_death_funcs[])(struct MainObj*);
extern void (*eregion_intro_funcs[])(struct MainObj*);

void eregion_update(struct MainObj* self)
{

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    CollisionRelated(PLAYER_OBJECT(self));
    eregion_state_funcs[self->state](self);
    if (self->ext.main_8.queued_sound != 0xFF) {
        func_8001540C(2, self->ext.main_8.queued_sound, self);
        self->ext.main_8.queued_sound = 0xFF;
    }
}

// eregion_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80047E58(struct MainObj* arg0);
void func_8004932C(struct MainObj* arg0);
void func_800480D0(struct MainObj* arg0);
void func_80048B04(struct MainObj* arg0);
void func_80047D04(struct MainObj* arg0);
extern union AnimationStep* D_800FAD68[];
extern u32 D_800FA724;
extern u32 D_800FA728;
extern u32 D_800FA738;
extern u32 D_800FA73C;
extern u32 D_800FA740;
extern u32 D_800FA744;
extern struct Unk_unk68 D_801066F0[];
extern void (*eregion_step_funcs[])(struct MainObj*);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80047D04(struct MainObj* arg0)
{
    struct VisualObj* visual;

    arg0->ext.main_8.queued_sound = 0xFF;
    arg0->ext.main_8.unk8B = 0;
    arg0->ext.main_8.unk8C = 0;
    arg0->on_screen = 1;
    arg0->unk15 = 0;
    arg0->bg_offset = 0;
    arg0->air_state = 1;
    arg0->hp = 0;
    arg0->contact_damage = 3;
    arg0->invincibility_timer = 0;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->animation_table = (const u8* const*)D_800FAD68;
    arg0->terrain_box = (struct Unk_unk68*)&D_800FA724;
    arg0->collision_data = (const u16*)D_801066F0;
    arg0->hurt_box = (const u8*)&D_800FA728;
    arg0->attack_box = (const u8*)&D_800FA72C;
    arg0->ext.main_8.unk84 = &D_800FA72C;
    arg0->ext.main_8.unk88 = 1;
    arg0->ext.main_8.unk80 = 0;
    arg0->unk40 = (u16)((OBJECT_STAGE_TEXTURE(0)) + OBJECT_TEXTURE_OFFSET(0xB0));
    engine_obj.unk25 = 2;
    engine_obj.boss_ptr = arg0;
    set_animation(arg0, 0);
    arg0->unk5 = 9;
    arg0->state++;

    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 6;
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->unk2 = 0;
    }
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 6;
        visual->unk50 = (struct PlayerObj*)arg0;
        visual->unk2 = 5;
    }
    arg0->x_pos.val = FIXED(0xF60);
    arg0->y_pos.val = FIXED(0x170);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_08_eregion", func_80047D04);
#endif

// eregion_run
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80047E58(struct MainObj* arg0)
{
    s32 collision;
    u8 frame;

    arg0->hurt_box = engine_obj.cur_character == 0
        ? (const void*)&D_800FA740
        : (const void*)&D_800FA744;
    arg0->collision_data = (const u16*)D_801060F0;
    arg0->unk65 = arg0->ext.main_8.unk8B;
    func_8002DD04(arg0);

    arg0->collision_data = (const u16*)D_801066F0;
    frame = arg0->animation_step.fields.frame_index;
    if (frame >= 0x16 && frame < 0x18)
        arg0->hurt_box = (const void*)&D_800FA73C;
    else if (frame >= 0x1F && frame < 0x21)
        arg0->hurt_box = (const void*)&D_800FA738;
    else
        arg0->hurt_box = (const void*)&D_800FA728;

    arg0->ext.main_8.unk8B = arg0->unk65;
    arg0->unk65 = arg0->ext.main_8.unk8C;
    collision = func_8002DD04(arg0);
    if (collision < 0) {
        arg0->state = 2;
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
        g_Player.spike_immune = 1;
        return;
    }
    if (collision > 0) {
        func_8001540C(2, SATURN_SOUND(0x21, 0x0C), arg0);
        arg0->invincibility_timer = 0x1E;
        if (arg0->unk7C != 0) {
            arg0->state = 3;
            arg0->unk5 = 0;
            arg0->unk6 = 0;
            arg0->unk42 |= 0x8000;
        }
    }

    arg0->ext.main_8.unk8C = arg0->unk65;
    eregion_step_funcs[arg0->unk5](arg0);

    if (arg0->invincibility_timer != 0) {
        s8 timer = arg0->invincibility_timer--;
        if (timer & 2)
            arg0->unk42 |= 0x8000;
        else
            arg0->unk42 &= 0x7FFF;
        if (arg0->invincibility_timer == 0)
            arg0->unk42 &= 0x7FFF;
    }

    func_8002D9BC(arg0);
    if (arg0->ext.main_8.unk88 != 0) {
        arg0->attack_box = arg0->ext.main_8.unk80;
        func_8002D9BC(arg0);
        arg0->attack_box = arg0->ext.main_8.unk84;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x90, 0x90);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_08_eregion", func_80047E58);
#endif

void eregion_pick_start(struct MainObj* self)
{
    self->unk7C = 0x2B;
    set_animation(self, 0);
    self->unk5++;
}

// eregion_pick_attack
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800480D0(struct MainObj* arg0)
{
    s32 distance;
    u16 timer;
    u8 choice;

    animate_object(ANIMATED_OBJECT(arg0));
    timer = (u16)arg0->unk7C;
    arg0->unk7C = (s16)(timer - 1);
    if (timer != 0)
        return;

    arg0->unk7C = 0;
    if (arg0->ext.main_8.unk8A++ >= 2) {
        arg0->ext.main_8.unk8A = 0;
        arg0->unk5 = arg0->hp < 0x19 ? 6 : 4;
        return;
    }

    distance = arg0->x_pos.i.hi - g_Player.x_pos.i.hi;
    if (distance < 0)
        distance = -distance;
    if (arg0->hp >= 0x19) {
        if (distance < 0x90) {
            if (arg0->unk15 != 0) {
                choice = 0x12B0 - arg0->x_pos.i.hi < 0xD0 ? 4 : 5;
            } else {
                choice = arg0->x_pos.i.hi - 0x11A0 < 0xD0 ? 4 : 5;
            }
        } else {
            choice = get_random_nonzero() % 8 < 3 ? 3 : 8;
        }
    } else if (distance < 0x90) {
        choice = get_random_nonzero() % 8 < 6 ? 7 : 5;
    } else {
        choice = get_random_nonzero() % 8 < 7 ? 7 : 6;
    }
    arg0->unk5 = choice;

    if (arg0->unk15 != 0) {
        if (g_Player.x_pos.val < arg0->x_pos.val)
            arg0->unk5 = 4;
    } else if (g_Player.x_pos.val >= arg0->x_pos.val) {
        arg0->unk5 = 4;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_08_eregion", func_800480D0);
#endif

void eregion_roar_start(struct MainObj* self)
{
    self->unk6++;
    set_animation(self, 0xE);
}

void eregion_roar_wait(struct MainObj* self)
{
    if (self->animation_step.fields.event == 2) {
        self->animation_step.fields.event = 0;
        func_8001540C(2, SATURN_SOUND(0x22, 0x0D), self);
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void eregion_roar(struct MainObj* self)
{
    eregion_roar_funcs[self->unk6](self);
}

void eregion_stomp_lift(struct MainObj* self)
{
    self->unk6++;
    self->x_speed = self->unk15 != 0 ? FIXED(0.5) : FIXED(-0.5);
    self->y_speed = FIXED(1.5);
    set_animation(self, 2);
}

void eregion_stomp_step(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        move_object(MOVING_OBJECT(self));
    }
    if (self->animation_step.fields.event == 1) {
        set_animation(self, 4);
        self->unk6++;
        self->x_speed = self->unk15 != 0 ? FIXED(1.5) : FIXED(-1.5);
        self->y_speed = 0;
        self->attack_box = (const u8*)&D_800FA730;
        self->ext.main_8.unk88 = 0;
    }
}

void eregion_stomp_follow(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        move_object(MOVING_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step < 0) {
        self->unk6++;
    }
}

void eregion_stomp_advance(struct MainObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 4);
        self->unk6++;
    }
}

void eregion_stomp_drop(struct MainObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 6);
        self->unk6++;
        self->x_speed = self->unk15 != 0 ? FIXED(0.75) : FIXED(-0.75);
        self->y_speed = FIXED(-1.5);
        self->attack_box = (const u8*)&D_800FA72C;
        self->ext.main_36.saved_unk5 = 1;
    }
}

void eregion_stomp_land(struct MainObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        func_800B0CA0(0x21, 2, self, 0x18, 6);
        func_800B0CA0(0x22, 2, self, 0x18, 6);
        func_8001540C(2, SATURN_SOUND(0x18, 0x03), self);
        start_screen_shake_y(0xA, 4, 2);
        self->animation_step.fields.event = 0;
    }
    if (self->collision_flags & 8) {
        if (self->unk15 != 0) {
            if (g_Player.x_pos.val < self->x_pos.val) {
                self->unk5 = 4;
            } else {
                self->unk5 = 5;
            }
        } else {
            if (g_Player.x_pos.val < self->x_pos.val) {
                self->unk5 = 5;
            } else {
                self->unk5 = 4;
            }
        }
        self->unk6 = 0;
        func_800B0CA0(0x21, 2, self, 0x18, 6);
        func_800B0CA0(0x22, 2, self, 0x18, 6);
        func_8001540C(2, SATURN_SOUND(0x18, 0x03), self);
        start_screen_shake_y(0xA, 4, 2);
    }
}

void eregion_stomp(struct MainObj* self)
{
    eregion_stomp_funcs[self->unk6](self);
}

void eregion_leap_crouch(struct MainObj* self)
{
    self->ext.main_487.unk8A = 0;
    self->unk6++;
    self->x_speed = 0;
    self->y_speed = FIXED(0.75);
    self->x_accel = FIXED(1.0 / 16);
    set_animation(self, 2);
}

void eregion_leap_jump(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        move_with_gravity(ANIMATED_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        self->y_speed = FIXED(3);
        set_animation(self, 4);
        self->unk6++;
    }
}

void eregion_leap_rise(struct MainObj* self)
{
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->y_pos.i.hi < 0x90) {
        if (self->unk15 != 0) {
            self->x_pos.i.hi = 0x12B0;
        } else {
            self->x_pos.i.hi = 0x11A0;
        }
        self->x_accel = 0;
        self->x_speed = 0;
        self->y_speed = FIXED(-2.5);
        self->unk15 ^= PLAYER_FACING_RIGHT;
        self->unk6++;
        self->unk7E = 0x3C;
    }
}

void eregion_fall(struct MainObj* self)
{
    if (self->unk7E != 0) {
        self->unk7E--;
        return;
    }

    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        set_animation(self, 6);
        self->unk6++;
    }
}

void eregion_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        func_800B0CA0(0x21, 2, self, 0x18, 6);
        func_800B0CA0(0x22, 2, self, 0x18, 6);
        func_8001540C(2, SATURN_SOUND(0x18, 0x03), self);
        start_screen_shake_y(0xA, 4, 2);
        self->animation_step.fields.event = 0;
    }
    if (self->animation_step.fields.event < 0) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void eregion_leap(struct MainObj* self)
{
    eregion_leap_funcs[self->unk6](self);
}

void eregion_wing_slash_start(struct MainObj* self)
{
    struct ShotObj* shot;
    struct VisualObj* visual;
    self->unk6++;
    set_animation(self, 8);
    shot = find_free_shot_obj();
    if (shot != 0) {
        shot->active = 0x41;
        shot->id = 4;
        shot->unk7C = WEAPON_OBJECT(self);
        shot->state = 0;
        shot->unk5 = 0;
        shot->unk6 = 0;
    }
    visual = find_free_visual_obj();
    if (visual != 0) {
        visual->active = 0x41;
        visual->id = 6;
        visual->state = 0;
        visual->unk5 = 0;
        visual->unk6 = 0;
        visual->unk50 = PLAYER_OBJECT(self);
        visual->unk2 = 1;
    }

    self->x_speed = self->x_pos.i.hi;
}

// eregion_wing_slash_swing
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80048B04(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));

    if (arg0->animation_step.fields.frame_index != 0xC) {
        if (arg0->unk15 != 0) {
            arg0->x_pos.u.hi = arg0->x_speed - 8;
        } else {
            arg0->x_pos.u.hi = arg0->x_speed + 8;
        }
    }

    if (arg0->animation_step.fields.event == 2) {
        func_8001540C(2, SATURN_SOUND(0x19, 0x04), BASE_OBJECT(arg0));
        arg0->animation_step.fields.event = 0;
    }
    if (arg0->animation_step.fields.event == 1) {
        arg0->unk5 = 0;
        arg0->unk6 = 0;
        arg0->x_pos.u.hi = arg0->x_speed;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_08_eregion", func_80048B04);
#endif

void eregion_wing_slash(struct MainObj* self)
{
    eregion_wing_slash_funcs[self->unk6](self);
}

void eregion_pounce_crouch(struct MainObj* self)
{
    self->unk6++;
    self->x_speed = self->unk15 != 0 ? FIXED(-3) : FIXED(3);
    self->y_speed = FIXED(1.5);
    set_animation(self, 2);
}

void eregion_pounce_jump(struct MainObj* self)
{
    s32 x_velocity;

    if (self->animation_step.fields.event != 0) {
        move_object(MOVING_OBJECT(self));
    }
    if (self->animation_step.fields.event == 3) {
        func_8001540C(2, SATURN_SOUND(0x1F, 0x0A), self);
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        x_velocity = self->unk15 != 0 ? FIXED(8.5) : FIXED(-8.5);
        self->x_speed = x_velocity;
        self->y_speed = FIXED(-4);
        self->gravity = FIXED(-0.1875);
        self->x_accel = 0;
        self->unk6++;
        set_animation(self, 4);
        self->contact_damage = 5;
        self->attack_box = (const u8*)&D_800FA730;
        self->ext.main_8.unk88 = 0;
        self->unk7E = 0x14;
    }
}

void eregion_pounce_rise(struct MainObj* self)
{
    if (self->unk7E != 0) {
        self->unk7E--;
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
    }
    if (self->animation_step.fields.event != 0) {
        animate_object(ANIMATED_OBJECT(self));
    }
    if (self->y_pos.i.hi < 0x90) {
        if (self->unk15 != 0) {
            self->x_pos.i.hi = 0x12B0;
        } else {
            self->x_pos.i.hi = 0x11A0;
        }
        self->unk6++;
        self->x_speed = 0;
        self->y_speed = FIXED(-2.5);
        self->x_accel = 0;
        self->gravity = 0;
        self->unk15 ^= PLAYER_FACING_RIGHT;
        self->contact_damage = 3;
        self->attack_box = (const u8*)&D_800FA72C;
        self->ext.main_8.unk88 = 1;
    }
}

void eregion_pounce(struct MainObj* self)
{
    eregion_pounce_funcs[self->unk6](self);
}

void eregion_fireball_open(struct MainObj* self)
{
    struct VisualObj* visual;

    self->unk6++;
    set_animation(self, 0xC);
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 6;
        visual->unk50 = PLAYER_OBJECT(self);
        visual->unk2 = 2;
    }
}

void eregion_fireball_fire(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        func_8001540C(2, SATURN_SOUND(0x1E, 0x09), self);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            self->animation_step.fields.event = 0;
            shot->active = 0x41;
            shot->id = 3;
            shot->unk2 = 0;
            shot->unk7C = WEAPON_OBJECT(self);
        }
    }
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void eregion_fireball(struct MainObj* self)
{
    eregion_fireball_funcs[self->unk6](self);
}

void eregion_spread_open(struct MainObj* self)
{
    struct VisualObj* visual;

    self->unk6++;
    set_animation(self, 0x12);
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 6;
        visual->unk50 = PLAYER_OBJECT(self);
        visual->unk2 = 2;
    }
}

void eregion_spread_fire(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event > 1) {
        func_8001540C(2, SATURN_SOUND(0x1E, 0x09), self);
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 3;
            shot->unk2 = self->animation_step.fields.event;
            shot->unk7C = WEAPON_OBJECT(self);
            self->animation_step.fields.event = 0;
        }
    }
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void eregion_spread(struct MainObj* self)
{
    eregion_spread_funcs[self->unk6](self);
}

void eregion_death_start(struct MainObj* self)
{
    player_start_script_action(0x14, g_Player.unk15);
    self->unk7 = 1;
    self->unk6++;
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_9.object_id = 0x19;
    update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
}

void eregion_death_blink(struct MainObj* self)
{
    struct EffectObj* effect;
    s8 var_a0;
    s16 var_a1;

    if (--self->unk7C == 0) {
        self->unk6++;
        effect = find_free_effect_obj();
        if (effect != NULL) {
            effect->active = 1;
            effect->id = 0x1A;
            effect->x_pos.i.hi = self->x_pos.i.hi;
            effect->y_pos.i.hi = self->y_pos.i.hi;
            self->ext.main_9.effect = effect;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
    if (self->unk7E-- == 0) {
        self->unk42 ^= 0x8000;
        self->ext.main_9.object_id -= 5;
        var_a0 = self->ext.main_9.object_id;
        var_a1 = var_a0 > 5 ? var_a0 : 5;
        self->unk7E = var_a1;
    }
}

void eregion_death_wait_explosion(struct MainObj* self)
{
    struct MiscObj* misc;
    s8* data;

    data = (s8*)self->ext.main_9.effect;
    self->on_screen = 0;
    if (data[0] != 0) {
        if (data[7] == 0) {
            if (self->unk7E-- == 0) {
                self->unk7E = 5;
                self->unk42 = self->unk42 ^ 0x8000;
            }
            update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
            return;
        }
        self->unk7 = -0x80;
        return;
    }
    misc = find_free_misc_obj();
    if (misc != 0) {
        misc->active = 0x41;
        misc->id = 0x2E;
        misc->state = 0;
    }
    player_start_script_action(0x14, PLAYER_FACING_RIGHT);
    ZeroObjectState(OBJECT_HEADER(self));
}

void eregion_death(struct MainObj* self)
{
    eregion_death_funcs[self->unk6](self);
}

void eregion_recoil_start(struct MainObj* self)
{
    self->unk6++;
    set_animation(self, 0xA);
    self->x_speed = self->x_pos.i.hi;
    if (self->animation_step.fields.frame_index == 0x1C || self->animation_step.fields.frame_index == 0x1D) {
        s16 x_speed = self->x_speed;
        self->x_pos.i.hi = x_speed + (self->unk15 != 0 ? -0x16 : 0x16);
    }
}

// eregion_recoil_wait
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004932C(struct MainObj* arg0)
{
    s32 x_pos = arg0->x_speed;
    u8 frame = arg0->animation_step.fields.frame_index;

    if (frame >= 0x1C && frame <= 0x1D) {
        x_pos += arg0->unk15 != 0 ? -0x16 : 0x16;
    }
    arg0->x_pos.i.hi = (s16)x_pos;
    arg0->unk42 &= 0x7FFF;
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 0) {
        arg0->state = 1;
        if (arg0->unk7C != 0) {
            set_animation(ANIMATED_OBJECT(arg0), 0);
            arg0->unk5 = 1;
            arg0->unk7C = 1;
        } else {
            eregion_pick_start(arg0);
        }
        arg0->unk6 = 0;
        arg0->x_pos.i.hi = (s16)arg0->x_speed;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_08_eregion", func_8004932C);
#endif

void eregion_recoil(struct MainObj* self)
{
    s8 timer;

    eregion_recoil_funcs[self->unk6](self);
    func_8002D9BC(self);
    if (self->ext.main_9.animation_timer != 0) {
        self->attack_box = self->ext.main_9.animation_1;
        func_8002D9BC(self);
        self->attack_box = self->ext.main_9.animation_2;
    }

    timer = self->invincibility_timer;
    if (timer != 0) {
        self->invincibility_timer = timer - 1;
        self->unk42 = (timer & 2) ? self->unk42 | 0x8000
                                  : self->unk42 & 0x7FFF;
        if (self->invincibility_timer == 0) {
            self->unk42 &= 0x7FFF;
        }
    }
    update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
}

void eregion_intro_warning(struct MainObj* self)
{
    struct EffectObj* effect;

    effect = find_free_effect_obj();
    if (effect != NULL) {
        effect->active = 1;
        effect->id = 0x18;
        effect->x_pos.u.hi = self->x_pos.u.hi;
        effect->y_pos.u.hi = self->y_pos.u.hi;
        self->ext.main_9.effect = effect;
    }
    self->unk15 = PLAYER_FACING_RIGHT;
    self->unk6++;
    player_start_script_action(0x15, 0);
}

void eregion_intro_leap(struct MainObj* self)
{
    struct VisualObj* visual;

    if (self->ext.main_9.effect->active == 0) {
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 6;
            visual->unk50 = PLAYER_OBJECT(self);
            visual->unk2 = 3;
        }
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 6;
            visual->unk50 = PLAYER_OBJECT(self);
            visual->unk2 = 4;
        }
        self->unk6 = (u8)self->unk6 + 1;
        start_screen_shake_y(-1, 4, 2);
        self->x_speed = self->unk15 != 0 ? FIXED(8.5) : FIXED(-8.5);
        self->y_speed = FIXED(-6);
        self->x_accel = 0;
        self->gravity = FIXED(-0.09375);
        set_animation(self, 4);
        self->unk7E = 0x14;
    }
}

void eregion_intro_rise(struct MainObj* self)
{
    if (self->unk7E != 0) {
        self->unk7E--;
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
    }

    if (self->animation_step.fields.event != 0) {
        animate_object(ANIMATED_OBJECT(self));
    }

    if (self->y_pos.i.hi < 0x90) {
        start_screen_shake_y(-1, 4, 2);
        self->unk6++;
        self->x_pos.i.hi = 0x1240;
        self->x_speed = 0;
        self->y_speed = FIXED(-2.5);
        self->x_accel = 0;
        self->gravity = 0;
        self->unk15 = 0;
        self->unk7E = 0x78;
    }
}

// eregion_intro_land
void func_8004970C(struct MainObj* self)
{
    if (self->unk7E != 0) {
        self->unk7E--;
        return;
    }

    animate_object(ANIMATED_OBJECT(self));

    if (self->animation_step.fields.event == 1) {
        func_800B0CA0(0x21, 2, self, 0x18, 6);
        func_800B0CA0(0x22, 2, self, 0x18, 6);
        func_8001540C(2, SATURN_SOUND(0x18, 0x03), self);
        start_screen_shake_y(0xA, 4, 2);
        self->animation_step.fields.event = 0;
    }

    if (self->animation_step.fields.event < 0) {
        self->unk6++;
        engine_obj.enable_boss = 1;
        self->ext.main_9.animation_1 = (const u8*)&D_800FA734;
        self->unk7E = 3;
    }
}

void eregion_intro_fill_health(struct MainObj* self)
{
    if (self->hp < 0x30) {
        if (--self->unk7E == 0) {
            func_8001540C(0, SATURN_SOUND(0xE, 0x14), NULL);
            self->unk7E = 3;
        }
        self->hp++;
    } else {
        self->unk5 = 2;
        self->unk6 = 0;
        player_end_script_action();
    }
}

void eregion_intro(struct MainObj* self)
{
    eregion_intro_funcs[self->unk6](self);
}

#ifdef MMX4_SATURN
u32 D_800FA724 = 0x22595406;
#else
u32 D_800FA724 = 0x06545922;
#endif

#ifdef MMX4_SATURN
u32 D_800FA728 = 0xE2B45359;
#else
u32 D_800FA728 = 0x5953B4E2;
#endif

#ifdef MMX4_SATURN
u32 D_800FA72C = 0xD7B46047;
#else
u32 D_800FA72C = 0x4760B4D7;
#endif

#ifdef MMX4_SATURN
u32 D_800FA730 = 0xE5A371A3;
#else
u32 D_800FA730 = 0xA371A3E5;
#endif

#ifdef MMX4_SATURN
u32 D_800FA734 = 0xEC188148;
#else
u32 D_800FA734 = 0x488118EC;
#endif

#ifdef MMX4_SATURN
u32 D_800FA738 = 0xBCDA5A41;
#else
u32 D_800FA738 = 0x415ADABC;
#endif

#ifdef MMX4_SATURN
u32 D_800FA73C = 0xBCCC5A41;
#else
u32 D_800FA73C = 0x415ACCBC;
#endif

#ifdef MMX4_SATURN
u32 D_800FA740 = 0xEE107550;
#else
u32 D_800FA740 = 0x507510EE;
#endif

#ifdef MMX4_SATURN
u32 D_800FA744 = 0xFD26663A;
#else
u32 D_800FA744 = 0x3A6626FD;
#endif

union AnimationStep D_800FA748[] = {
    { 16, 0, 1, 0x00 },
    { 16, 0, 1, 0x01 },
    { 16, 0, 1, 0x02 },
    { 16, 0, 1, 0x03 },
    { 9, 0, 1, 0x04 },
    { 9, 0, 1, 0x05 },
    { 11, 0, 1, 0x06 },
    { 14, 1, -7, 0x07 },
};

union AnimationStep D_800FA768[] = {
    { 75, 0, 1, 0x08 },
    { 8, 0, 1, 0x09 },
    { 16, 0, 1, 0x0A },
    { 8, 1, -3, 0x0B },
};

union AnimationStep D_800FA778[] = {
    { 8, 0, 1, 0x0C },
    { 16, 0, 1, 0x0D },
    { 1, 3, 1, 0x0E },
    { 7, 2, 1, 0x0E },
    { 7, 2, 1, 0x0F },
    { 1, 1, -4, 0x0F },
};

union AnimationStep D_800FA790[] = {
    { 8, 0, 1, 0x08 },
    { 8, 0, 1, 0x09 },
    { 8, 0, 1, 0x0A },
    { 8, 0, 1, 0x0B },
    { 8, 1, -4, 0x08 },
};

union AnimationStep D_800FA7A4[] = {
    { 8, 0, 1, 0x10 },
    { 8, 0, 1, 0x11 },
    { 8, 2, 1, 0x11 },
    { 8, 2, 1, 0x10 },
    { 16, 1, -4, 0x0F },
};

union AnimationStep D_800FA7B8[] = {
    { 8, 0, 1, 0x09 },
    { 16, 0, 1, 0x0B },
    { 8, 0, 1, 0x09 },
    { 16, 1, -3, 0x0A },
};

union AnimationStep D_800FA7C8[] = {
    { 16, 0, 1, 0x12 },
    { 8, 0, 1, 0x13 },
    { 24, 1, 1, 0x14 },
    { 16, 0, 1, 0x0C },
    { 1, -1, -4, 0x0C },
};

union AnimationStep D_800FA7DC[] = {
    { 8, 0, 1, 0x09 },
    { 8, 0, 1, 0x0B },
    { 8, 0, 1, 0x09 },
    { 16, 0, 1, 0x0A },
    { 8, 0, 1, 0x09 },
    { 8, 0, 1, 0x0B },
    { 16, 1, -6, 0x08 },
};

union AnimationStep D_800FA7F8[] = {
    { 8, 0, 1, 0x0C },
    { 8, 0, 1, 0x15 },
    { 30, 0, 1, 0x16 },
    { 5, 0, 1, 0x17 },
    { 8, 2, 1, 0x18 },
    { 7, 0, 1, 0x18 },
    { 4, 0, 1, 0x1B },
    { 19, 0, 1, 0x18 },
    { 1, 1, -8, 0x0C },
};

union AnimationStep D_800FA81C[] = {
    { 8, 0, 1, 0x08 },
    { 8, 0, 1, 0x08 },
    { 30, 0, 1, 0x09 },
    { 5, 0, 1, 0x0A },
    { 8, 0, 1, 0x0B },
    { 7, 0, 1, 0x0B },
    { 4, 0, 1, 0x0B },
    { 20, 1, -7, 0x08 },
};

union AnimationStep D_800FA83C[] = {
    { 8, 0, 1, 0x36 },
    { 8, 0, 1, 0x36 },
    { 30, 0, 1, 0x36 },
    { 5, 0, 1, 0x36 },
    { 8, -1, 1, 0x19 },
    { 7, 0, 1, 0x36 },
    { 4, 0, 1, 0x36 },
    { 20, 1, -7, 0x36 },
};

union AnimationStep D_800FA85C[] = {
    { 8, 0, 1, 0x36 },
    { 8, 0, 1, 0x36 },
    { 30, 0, 1, 0x36 },
    { 5, 0, 1, 0x36 },
    { 8, 0, 1, 0x1A },
    { 7, 0, 1, 0x36 },
    { 4, 0, 1, 0x36 },
    { 20, 1, -7, 0x36 },
};

union AnimationStep D_800FA87C[] = {
    { 3, 0, 1, 0x1C },
    { 3, 0, 1, 0x1D },
    { 3, 0, 1, 0x1C },
    { 3, 0, 1, 0x1D },
    { 5, 1, 1, 0x0C },
    { 1, 1, -5, 0x0C },
};

union AnimationStep D_800FA894[] = {
    { 3, 0, 1, 0x0A },
    { 3, 0, 1, 0x0A },
    { 3, 0, 1, 0x0A },
    { 3, 0, 1, 0x0A },
    { 6, 1, -4, 0x0A },
};

union AnimationStep D_800FA8A8[] = {
    { 8, 0, 1, 0x0C },
    { 12, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 6, 0, 1, 0x20 },
    { 42, 0, 1, 0x20 },
    { 4, 0, 1, 0x26 },
    { 20, 2, 1, 0x20 },
    { 20, 2, 1, 0x20 },
    { 6, 2, 1, 0x1F },
    { 12, 0, 1, 0x1E },
    { 7, 0, 1, 0x0C },
    { 1, 0, -10, 0x0C },
};

union AnimationStep D_800FA8D8[] = {
    { 8, 0, 1, 0x08 },
    { 6, 0, 1, 0x09 },
    { 6, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 3, 0, 1, 0x0B },
    { 3, 0, 1, 0x08 },
    { 82, 0, 1, 0x08 },
    { 6, 0, 1, 0x08 },
    { 20, 1, -8, 0x08 },
};

union AnimationStep D_800FA8FC[] = {
    { 20, 0, 1, 0x0C },
    { 20, 0, 1, 0x33 },
    { 22, 2, 1, 0x34 },
    { 24, 0, 1, 0x35 },
    { 12, 0, 1, 0x34 },
    { 4, 0, 1, 0x33 },
    { 7, 0, 1, 0x0C },
    { 1, 1, -7, 0x0C },
};

union AnimationStep D_800FA91C[] = {
    { 20, 0, 1, 0x08 },
    { 20, 0, 1, 0x08 },
    { 22, 0, 1, 0x08 },
    { 24, 0, 1, 0x08 },
    { 12, 0, 1, 0x08 },
    { 4, 0, 1, 0x08 },
    { 8, 1, -6, 0x08 },
};

union AnimationStep D_800FA938[] = {
    { 4, 0, 1, 0x29 },
    { 4, 0, 1, 0x2A },
    { 4, 0, 1, 0x2B },
    { 4, 1, -3, 0x2C },
};

union AnimationStep D_800FA948[] = {
    { 3, 0, 1, 0x2D },
    { 3, 0, 1, 0x2E },
    { 4, 0, 1, 0x2F },
    { 3, 0, 1, 0x30 },
    { 4, 0, 1, 0x31 },
    { 2, 0, 1, 0x32 },
    { 1, 0, -6, 0x32 },
};

union AnimationStep D_800FA964[] = {
    { 8, 0, 1, 0x36 },
    { 12, 0, 1, 0x36 },
    { 2, 0, 1, 0x36 },
    { 6, 0, 1, 0x36 },
    { 6, 2, 1, 0x21 },
    { 4, 0, 1, 0x22 },
    { 3, 0, 1, 0x23 },
    { 4, 0, 1, 0x22 },
    { 3, 0, 1, 0x23 },
    { 6, 0, 1, 0x21 },
    { 5, 0, 1, 0x22 },
    { 4, 0, 1, 0x23 },
    { 3, 0, 1, 0x24 },
    { 4, 0, 1, 0x25 },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x28 },
    { 6, 0, 1, 0x36 },
    { 12, 0, 1, 0x36 },
    { 8, 1, -20, 0x36 },
};

#if defined(MMX4_PC) && !defined(MMX4_WIN32)
static struct {
    union AnimationStep D_800FA948[7];
    union AnimationStep D_800FA964[19];
} eregion_anim_run = {
    {
        { 3, 0, 1, 0x2D },
        { 3, 0, 1, 0x2E },
        { 4, 0, 1, 0x2F },
        { 3, 0, 1, 0x30 },
        { 4, 0, 1, 0x31 },
        { 2, 0, 1, 0x32 },
        { 1, 0, -6, 0x32 },
    },
    {
        { 8, 0, 1, 0x36 },
        { 12, 0, 1, 0x36 },
        { 2, 0, 1, 0x36 },
        { 6, 0, 1, 0x36 },
        { 6, 2, 1, 0x21 },
        { 4, 0, 1, 0x22 },
        { 3, 0, 1, 0x23 },
        { 4, 0, 1, 0x22 },
        { 3, 0, 1, 0x23 },
        { 6, 0, 1, 0x21 },
        { 5, 0, 1, 0x22 },
        { 4, 0, 1, 0x23 },
        { 3, 0, 1, 0x24 },
        { 4, 0, 1, 0x25 },
        { 1, 0, 1, 0x27 },
        { 1, 0, 1, 0x28 },
        { 6, 0, 1, 0x36 },
        { 12, 0, 1, 0x36 },
        { 8, 1, -20, 0x36 },
    },
};
#define D_800FA948 eregion_anim_run.D_800FA948
#define D_800FA964 eregion_anim_run.D_800FA964
#endif

union AnimationStep D_800FA9B0[] = {
    { 1, 0, 1, 0x37 },
    { 1, 0, -1, 0x38 },
};

union AnimationStep D_800FA9B8[] = {
    { 1, 0, 1, 0x0A },
    { 1, 0, -1, 0x0A },
};

union AnimationStep D_800FA9C0[] = {
    { 8, 0, 1, 0x0C },
    { 12, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 6, 0, 1, 0x20 },
    { 42, 0, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 1, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 1, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 2, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 2, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 3, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 3, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 4, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 4, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 5, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 5, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 6, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 6, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 7, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 7, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 8, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 8, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 9, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 9, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 3, 10, 1, 0x20 },
    { 2, 0, 1, 0x26 },
    { 6, 10, 1, 0x1F },
    { 12, 0, 1, 0x1E },
    { 7, 0, 1, 0x0C },
    { 1, 0, -10, 0x0C },
};

union AnimationStep D_800FAA80[] = {
    { 8, 0, 1, 0x08 },
    { 6, 0, 1, 0x09 },
    { 6, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 3, 0, 1, 0x0B },
    { 3, 0, 1, 0x08 },
    { 99, 0, 1, 0x08 },
    { 40, 0, 1, 0x08 },
    { 6, 0, 1, 0x08 },
    { 20, 1, -8, 0x08 },
};

union AnimationStep D_800FAAA8[] = {
    { 1, 0, 1, 0x39 },
    { 1, 0, 1, 0x3A },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x3C },
    { 1, 0, 1, 0x3D },
    { 1, 0, 1, 0x3E },
    { 1, 0, 1, 0x3F },
    { 1, 0, 1, 0x40 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x41 },
    { 1, 0, 1, 0x42 },
    { 1, 0, 1, 0x43 },
    { 1, 0, 1, 0x44 },
    { 1, 0, 1, 0x45 },
    { 1, 0, 1, 0x46 },
    { 1, 0, 1, 0x47 },
    { 1, 0, 1, 0x48 },
    { 1, 0, 1, 0x49 },
    { 1, 0, 1, 0x4A },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x4B },
    { 1, 0, 1, 0x4C },
    { 1, 0, 1, 0x4C },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x4E },
    { 1, 0, 1, 0x4F },
    { 1, 0, -1, 0x50 },
};

union AnimationStep D_800FAB80[] = {
    { 16, 0, 1, 0x00 },
    { 16, 0, 1, 0x00 },
    { 16, 0, 1, 0x00 },
    { 9, 0, 1, 0x00 },
    { 9, 0, 1, 0x00 },
    { 11, 0, 1, 0x00 },
    { 16, 0, 1, 0x00 },
    { 14, 0, -7, 0x00 },
};

union AnimationStep D_800FABA0[] = {
    { 16, 0, 1, 0x01 },
    { 16, 0, 1, 0x01 },
    { 16, 0, 1, 0x01 },
    { 9, 0, 1, 0x01 },
    { 9, 0, 1, 0x01 },
    { 11, 0, 1, 0x01 },
    { 16, 0, 1, 0x01 },
    { 14, 0, -7, 0x01 },
};

union AnimationStep D_800FABC0[] = {
    { 8, 0, 1, 0x02 },
    { 8, 0, 1, 0x03 },
    { 8, 0, 1, 0x04 },
    { 8, 1, 1, 0x05 },
    { 8, 0, -4, 0x06 },
};

union AnimationStep D_800FABD4[] = {
    { 8, 0, 1, 0x08 },
    { 8, 0, 1, 0x09 },
    { 8, 0, 1, 0x0A },
    { 8, 0, 1, 0x0B },
    { 8, 0, -4, 0x0C },
};

union AnimationStep D_800FABE8[] = {
    { 8, 0, 1, 0x07 },
    { 8, 1, 1, 0x02 },
    { 8, 0, 1, 0x03 },
    { 8, 0, 1, 0x04 },
    { 8, 0, 1, 0x05 },
    { 8, 0, -5, 0x06 },
};

union AnimationStep D_800FAC00[] = {
    { 8, 0, 1, 0x0D },
    { 8, 0, 1, 0x08 },
    { 8, 0, 1, 0x09 },
    { 8, 0, 1, 0x0A },
    { 8, 0, 1, 0x0B },
    { 8, 0, -5, 0x0C },
};

union AnimationStep D_800FAC18[] = {
    { 8, 0, 1, 0x07 },
    { 8, 1, 1, 0x02 },
    { 8, 0, 1, 0x03 },
    { 8, 0, 1, 0x04 },
    { 8, 0, 1, 0x02 },
    { 8, 0, -5, 0x00 },
};

union AnimationStep D_800FAC30[] = {
    { 8, 0, 1, 0x0D },
    { 8, 0, 1, 0x08 },
    { 8, 0, 1, 0x09 },
    { 8, 0, 1, 0x0A },
    { 8, 0, 1, 0x08 },
    { 8, 0, -5, 0x01 },
};

union AnimationStep D_800FAC48[] = {
    { 8, 0, 1, 0x00 },
    { 8, 0, 1, 0x02 },
    { 30, 0, 1, 0x02 },
    { 5, 0, 1, 0x02 },
    { 4, 0, 1, 0x05 },
    { 7, 0, 1, 0x05 },
    { 4, 0, 1, 0x05 },
    { 20, 0, -7, 0x05 },
};

union AnimationStep D_800FAC68[] = {
    { 8, 0, 1, 0x01 },
    { 8, 0, 1, 0x08 },
    { 30, 0, 1, 0x08 },
    { 5, 0, 1, 0x08 },
    { 4, 0, 1, 0x0B },
    { 7, 0, 1, 0x0B },
    { 4, 0, 1, 0x0B },
    { 20, 0, -7, 0x0B },
};

union AnimationStep D_800FAC88[] = {
    { 3, 0, 1, 0x05 },
    { 3, 0, 1, 0x05 },
    { 3, 0, 1, 0x05 },
    { 3, 0, 1, 0x05 },
    { 6, 0, -4, 0x05 },
};

union AnimationStep D_800FAC9C[] = {
    { 3, 0, 1, 0x0B },
    { 3, 0, 1, 0x0B },
    { 3, 0, 1, 0x0B },
    { 3, 0, 1, 0x0B },
    { 6, 0, -4, 0x0B },
};

union AnimationStep D_800FACB0[] = {
    { 8, 0, 1, 0x00 },
    { 12, 0, 1, 0x00 },
    { 8, 0, 1, 0x02 },
    { 80, 0, 1, 0x02 },
    { 6, 0, 1, 0x02 },
    { 12, 0, 1, 0x00 },
    { 8, 0, -6, 0x00 },
};

union AnimationStep D_800FACCC[] = {
    { 8, 0, 1, 0x01 },
    { 12, 0, 1, 0x01 },
    { 8, 0, 1, 0x08 },
    { 80, 0, 1, 0x08 },
    { 6, 0, 1, 0x08 },
    { 12, 0, 1, 0x01 },
    { 8, 0, -6, 0x01 },
};

union AnimationStep D_800FACE8[] = {
    { 20, 0, 1, 0x00 },
    { 20, 0, 1, 0x00 },
    { 22, 0, 1, 0x00 },
    { 24, 0, 1, 0x00 },
    { 12, 0, 1, 0x00 },
    { 4, 0, -5, 0x00 },
};

union AnimationStep D_800FAD00[] = {
    { 20, 0, 1, 0x01 },
    { 20, 0, 1, 0x01 },
    { 22, 0, 1, 0x01 },
    { 24, 0, 1, 0x01 },
    { 12, 0, 1, 0x01 },
    { 4, 0, -5, 0x01 },
};

union AnimationStep D_800FAD18[] = {
    { 1, 0, 1, 0x05 },
    { 1, 0, -1, 0x05 },
};

union AnimationStep D_800FAD20[] = {
    { 1, 0, 1, 0x0B },
    { 1, 0, -1, 0x0B },
};

union AnimationStep D_800FAD28[] = {
    { 8, 0, 1, 0x00 },
    { 12, 0, 1, 0x00 },
    { 8, 0, 1, 0x02 },
    { 99, 0, 1, 0x02 },
    { 40, 0, 1, 0x02 },
    { 6, 0, 1, 0x02 },
    { 12, 0, 1, 0x00 },
    { 8, 0, -6, 0x00 },
};

union AnimationStep D_800FAD48[] = {
    { 8, 0, 1, 0x01 },
    { 12, 0, 1, 0x01 },
    { 8, 0, 1, 0x08 },
    { 99, 0, 1, 0x08 },
    { 40, 0, 1, 0x08 },
    { 6, 0, 1, 0x08 },
    { 12, 0, 1, 0x01 },
    { 8, 0, -6, 0x01 },
};

union AnimationStep* D_800FAD68[] = {
    D_800FA748,
    D_800FA768,
    D_800FA778,
    D_800FA790,
    D_800FA7A4,
    D_800FA7B8,
    D_800FA7C8,
    D_800FA7DC,
    D_800FA7F8,
    D_800FA81C,
    D_800FA87C,
    D_800FA894,
    D_800FA8A8,
    D_800FA8D8,
    D_800FA8FC,
    D_800FA91C,
    D_800FA9B0,
    D_800FA9B8,
    D_800FA9C0,
    D_800FAA80,
    D_800FA83C,
    D_800FA85C,
    D_800FA964,
    D_800FA938,
    D_800FA948,
    D_800FAAA8,
};

union AnimationStep* D_800FADD0[] = {
    D_800FAB80,
    D_800FABA0,
    D_800FABC0,
    D_800FABD4,
    D_800FABE8,
    D_800FAC00,
    D_800FAC18,
    D_800FAC30,
    D_800FAC48,
    D_800FAC68,
    D_800FAC88,
    D_800FAC9C,
    D_800FACB0,
    D_800FACCC,
    D_800FACE8,
    D_800FAD00,
    D_800FAD18,
    D_800FAD20,
    D_800FAD28,
    D_800FAD48,
};

void (*eregion_state_funcs[4])(struct MainObj*) = {
    func_80047D04,
    func_80047E58,
    eregion_death,
    eregion_recoil,
};

s16 D_800FAE30[4] = { -1, 1, 1, -1 };

void (*eregion_step_funcs[10])() = {
    eregion_pick_start,
    func_800480D0,
    eregion_roar,
    eregion_stomp,
    eregion_leap,
    eregion_wing_slash,
    eregion_pounce,
    eregion_spread,
    eregion_fireball,
    eregion_intro,
};

void (*eregion_roar_funcs[2])() = {
    eregion_roar_start,
    eregion_roar_wait,
};

void (*eregion_stomp_funcs[7])(struct MainObj*) = {
    eregion_stomp_lift,
    eregion_stomp_step,
    eregion_stomp_follow,
    eregion_stomp_advance,
    eregion_stomp_advance,
    eregion_stomp_drop,
    eregion_stomp_land,
};

void (*eregion_leap_funcs[5])(struct MainObj*) = {
    eregion_leap_crouch,
    eregion_leap_jump,
    eregion_leap_rise,
    eregion_fall,
    eregion_land,
};

void (*eregion_wing_slash_funcs[2])(struct MainObj*) = {
    eregion_wing_slash_start,
    func_80048B04,
};

void (*eregion_pounce_funcs[5])() = {
    eregion_pounce_crouch,
    eregion_pounce_jump,
    eregion_pounce_rise,
    eregion_fall,
    eregion_land,
};

void (*eregion_fireball_funcs[2])() = {
    eregion_fireball_open,
    eregion_fireball_fire,
};

void (*eregion_spread_funcs[2])() = {
    eregion_spread_open,
    eregion_spread_fire,
};

void (*eregion_death_funcs[3])(struct MainObj*) = {
    eregion_death_start,
    eregion_death_blink,
    eregion_death_wait_explosion,
};

void (*eregion_recoil_funcs[2])(struct MainObj*) = {
    eregion_recoil_start,
    func_8004932C,
};

void (*eregion_intro_funcs[6])(struct MainObj*) = {
    eregion_intro_warning,
    eregion_intro_leap,
    eregion_intro_rise,
    eregion_fall,
    func_8004970C,
    eregion_intro_fill_health,
};
