// MainObj, main_object_update_funcs[8]
// 80047C88..800498C0
#include "common.h"
#include "func_tables.h"

void eregion_update(struct MainObj* self)
{
    u8 sound_id;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    CollisionRelated(PLAYER_OBJECT(self));
    eregion_state_funcs[self->state](self);
    sound_id = self->ext.main_8.queued_sound;
    if (sound_id != 0xFF) {
        func_8001540C(2, sound_id, self);
        self->ext.main_8.queued_sound = 0xFF;
    }
}

// eregion_init
INCLUDE_ASM("main/nonmatchings/mains/main_08_eregion", func_80047D04);

// eregion_run
INCLUDE_ASM("main/nonmatchings/mains/main_08_eregion", func_80047E58);

void eregion_pick_start(struct MainObj* self)
{
    self->unk7C = 0x2B;
    set_animation(self, 0);
    self->unk5++;
}

// eregion_pick_attack
INCLUDE_ASM("main/nonmatchings/mains/main_08_eregion", func_800480D0);

void eregion_roar_start(struct MainObj* self)
{
    self->unk6++;
    set_animation(self, 0xE);
}

void eregion_roar_wait(struct MainObj* self)
{
    if (self->animation_step.fields.event == 2) {
        self->animation_step.fields.event = 0;
        func_8001540C(2, 0x22, self);
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
    s32 x_vel;

    x_vel = FIXED(-0.5);
    self->unk6++;
    if (self->unk15 != 0) {
        x_vel = FIXED(0.5);
    }
    self->x_speed = x_vel;
    self->y_speed = FIXED(1.5);
    set_animation(self, 2);
}

void eregion_stomp_step(struct MainObj* self)
{
    s32 x_vel;
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        move_object(MOVING_OBJECT(self));
    }
    if (self->animation_step.fields.event == 1) {
        set_animation(self, 4);
        x_vel = FIXED(-1.5);
        self->unk6++;
        if (self->unk15 != 0) {
            x_vel = FIXED(1.5);
        }
        self->x_speed = x_vel;
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
    s32 x_vel;

    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        set_animation(self, 6);
        x_vel = FIXED(-0.75);
        self->unk6++;
        if (self->unk15 != 0) {
            x_vel = FIXED(0.75);
        }
        self->y_speed = FIXED(-1.5);
        self->attack_box = (const u8*)&D_800FA72C;
        self->x_speed = x_vel;
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
        func_8001540C(2, 0x18, self);
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
        func_8001540C(2, 0x18, self);
        start_screen_shake_y(0xA, 4, 2);
    }
}

void eregion_stomp(struct MainObj* self)
{
    eregion_stomp_funcs[self->unk6](self);
}

void eregion_leap_crouch(struct MainObj* self)
{
    self->y_speed = FIXED(0.75);
    self->ext.main_487.unk8A = 0;
    self->x_speed = 0;
    self->x_accel = FIXED(1.0 / 16);
    self->unk6++;
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
        self->y_speed = FIXED(-2.5);
        self->unk7E = 0x3C;
        self->x_accel = 0;
        self->x_speed = 0;
        self->unk15 ^= 0x40;
        self->unk6++;
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
        func_8001540C(2, 0x18, self);
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
INCLUDE_ASM("main/nonmatchings/mains/main_08_eregion", func_80048B04);

void eregion_wing_slash(struct MainObj* self)
{
    eregion_wing_slash_funcs[self->unk6](self);
}

void eregion_pounce_crouch(struct MainObj* self)
{
    s32 velocity = FIXED(3);
    self->unk6++;
    if (self->unk15 != 0) {
        velocity = FIXED(-3);
    }
    self->x_speed = velocity;
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
        func_8001540C(2, 0x1F, self);
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        x_velocity = FIXED(-8.5);
        if (self->unk15 != 0) {
            x_velocity = FIXED(8.5);
        }
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
        self->y_speed = FIXED(-2.5);
        self->contact_damage = 3;
        self->attack_box = (const u8*)&D_800FA72C;
        self->ext.main_8.unk88 = 1;
        self->x_speed = 0;
        self->x_accel = 0;
        self->gravity = 0;
        self->unk6++;
        self->unk15 ^= 0x40;
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
        func_8001540C(2, 0x1E, self);
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
    if (self->animation_step.fields.event >= 2) {
        func_8001540C(2, 0x1E, self);
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
    self->unk7C = 0x7F;
    self->unk7E = 0x19;
    self->ext.main_9.object_id = 0x19;
    self->unk6++;
    update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
}

void eregion_death_blink(struct MainObj* self)
{
    struct EffectObj* effect;
    s8 var_a0;

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
        self->ext.main_9.object_id -= 5;
        var_a0 = self->ext.main_9.object_id;
        self->unk42 ^= 0x8000;
        if (var_a0 < 5) {
            var_a0 = 5;
        }
        self->unk7E = var_a0;
    }
}

void eregion_death_wait_explosion(struct MainObj* self)
{
    struct MiscObj* misc;
    s8* data;
    u16 timer;

    data = (s8*)self->ext.main_9.effect;
    self->on_screen = 0;
    if (data[0] != 0) {
        if (data[7] == 0) {
            timer = self->unk7E;
            self->unk7E = timer - 1;
            if (timer == 0) {
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
    player_start_script_action(0x14, 0x40);
    ZeroObjectState(OBJECT_HEADER(self));
}

void eregion_death(struct MainObj* self)
{
    eregion_death_funcs[self->unk6](self);
}

void eregion_recoil_start(struct MainObj* self)
{
    s32 x_pos;
    u8 frame;

    self->unk6++;
    set_animation(self, 0xA);
    x_pos = self->x_pos.i.hi;
    self->x_speed = x_pos;
    frame = self->animation_step.fields.frame_index;
    if (frame >= 0x1C && frame <= 0x1D) {
        self->x_pos.i.hi = (self->unk15 != 0) ? x_pos - 0x16 : x_pos + 0x16;
    }
}

// eregion_recoil_wait
INCLUDE_ASM("main/nonmatchings/mains/main_08_eregion", func_8004932C);

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
    self->unk15 = 0x40;
    self->unk6++;
    player_start_script_action(0x15, 0);
}

void eregion_intro_leap(struct MainObj* self)
{
    s32 x_velocity;
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
        x_velocity = FIXED(-8.5);
        if (self->unk15 != 0) {
            x_velocity = FIXED(8.5);
        }
        self->y_speed = FIXED(-6);
        self->x_speed = x_velocity;
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
        self->x_pos.i.hi = 0x1240;
        self->y_speed = FIXED(-2.5);
        self->x_speed = 0;
        self->x_accel = 0;
        self->gravity = 0;
        self->unk15 = 0;
        self->unk7E = 0x78;
        self->unk6++;
    }
}

// eregion_intro_land
INCLUDE_ASM("main/nonmatchings/mains/main_08_eregion", func_8004970C);

void eregion_intro_fill_health(struct MainObj* self)
{
    if (self->hp < 0x30) {
        if (--self->unk7E == 0) {
            func_8001540C(0, 0xE, NULL);
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

u32 D_800FA724 = 0x06545922;

u32 D_800FA728 = 0x5953B4E2;

u32 D_800FA72C = 0x4760B4D7;

u32 D_800FA730 = 0xA371A3E5;

u32 D_800FA734 = 0x488118EC;

u32 D_800FA738 = 0x415ADABC;

u32 D_800FA73C = 0x415ACCBC;

u32 D_800FA740 = 0x507510EE;

u32 D_800FA744 = 0x3A6626FD;

union AnimationStep D_800FA748[] = {
    { 0x00010010 },
    { 0x01010010 },
    { 0x02010010 },
    { 0x03010010 },
    { 0x04010009 },
    { 0x05010009 },
    { 0x0601000B },
    { 0x07F9010E },
};

union AnimationStep D_800FA768[] = {
    { 0x0801004B },
    { 0x09010008 },
    { 0x0A010010 },
    { 0x0BFD0108 },
};

union AnimationStep D_800FA778[] = {
    { 0x0C010008 },
    { 0x0D010010 },
    { 0x0E010301 },
    { 0x0E010207 },
    { 0x0F010207 },
    { 0x0FFC0101 },
};

union AnimationStep D_800FA790[] = {
    { 0x08010008 },
    { 0x09010008 },
    { 0x0A010008 },
    { 0x0B010008 },
    { 0x08FC0108 },
};

union AnimationStep D_800FA7A4[] = {
    { 0x10010008 },
    { 0x11010008 },
    { 0x11010208 },
    { 0x10010208 },
    { 0x0FFC0110 },
};

union AnimationStep D_800FA7B8[] = {
    { 0x09010008 },
    { 0x0B010010 },
    { 0x09010008 },
    { 0x0AFD0110 },
};

union AnimationStep D_800FA7C8[] = {
    { 0x12010010 },
    { 0x13010008 },
    { 0x14010118 },
    { 0x0C010010 },
    { 0x0CFCFF01 },
};

union AnimationStep D_800FA7DC[] = {
    { 0x09010008 },
    { 0x0B010008 },
    { 0x09010008 },
    { 0x0A010010 },
    { 0x09010008 },
    { 0x0B010008 },
    { 0x08FA0110 },
};

union AnimationStep D_800FA7F8[] = {
    { 0x0C010008 },
    { 0x15010008 },
    { 0x1601001E },
    { 0x17010005 },
    { 0x18010208 },
    { 0x18010007 },
    { 0x1B010004 },
    { 0x18010013 },
    { 0x0CF80101 },
};

union AnimationStep D_800FA81C[] = {
    { 0x08010008 },
    { 0x08010008 },
    { 0x0901001E },
    { 0x0A010005 },
    { 0x0B010008 },
    { 0x0B010007 },
    { 0x0B010004 },
    { 0x08F90114 },
};

union AnimationStep D_800FA83C[] = {
    { 0x36010008 },
    { 0x36010008 },
    { 0x3601001E },
    { 0x36010005 },
    { 0x1901FF08 },
    { 0x36010007 },
    { 0x36010004 },
    { 0x36F90114 },
};

union AnimationStep D_800FA85C[] = {
    { 0x36010008 },
    { 0x36010008 },
    { 0x3601001E },
    { 0x36010005 },
    { 0x1A010008 },
    { 0x36010007 },
    { 0x36010004 },
    { 0x36F90114 },
};

union AnimationStep D_800FA87C[] = {
    { 0x1C010003 },
    { 0x1D010003 },
    { 0x1C010003 },
    { 0x1D010003 },
    { 0x0C010105 },
    { 0x0CFB0101 },
};

union AnimationStep D_800FA894[] = {
    { 0x0A010003 },
    { 0x0A010003 },
    { 0x0A010003 },
    { 0x0A010003 },
    { 0x0AFC0106 },
};

union AnimationStep D_800FA8A8[] = {
    { 0x0C010008 },
    { 0x1E01000C },
    { 0x1F010002 },
    { 0x20010006 },
    { 0x2001002A },
    { 0x26010004 },
    { 0x20010214 },
    { 0x20010214 },
    { 0x1F010206 },
    { 0x1E01000C },
    { 0x0C010007 },
    { 0x0CF60001 },
};

union AnimationStep D_800FA8D8[] = {
    { 0x08010008 },
    { 0x09010006 },
    { 0x0A010006 },
    { 0x0B010002 },
    { 0x0B010003 },
    { 0x08010003 },
    { 0x08010052 },
    { 0x08010006 },
    { 0x08F80114 },
};

union AnimationStep D_800FA8FC[] = {
    { 0x0C010014 },
    { 0x33010014 },
    { 0x34010216 },
    { 0x35010018 },
    { 0x3401000C },
    { 0x33010004 },
    { 0x0C010007 },
    { 0x0CF90101 },
};

union AnimationStep D_800FA91C[] = {
    { 0x08010014 },
    { 0x08010014 },
    { 0x08010016 },
    { 0x08010018 },
    { 0x0801000C },
    { 0x08010004 },
    { 0x08FA0108 },
};

union AnimationStep D_800FA938[] = {
    { 0x29010004 },
    { 0x2A010004 },
    { 0x2B010004 },
    { 0x2CFD0104 },
};

union AnimationStep D_800FA948[] = {
    { 0x2D010003 },
    { 0x2E010003 },
    { 0x2F010004 },
    { 0x30010003 },
    { 0x31010004 },
    { 0x32010002 },
    { 0x32FA0001 },
};

union AnimationStep D_800FA964[] = {
    { 0x36010008 },
    { 0x3601000C },
    { 0x36010002 },
    { 0x36010006 },
    { 0x21010206 },
    { 0x22010004 },
    { 0x23010003 },
    { 0x22010004 },
    { 0x23010003 },
    { 0x21010006 },
    { 0x22010005 },
    { 0x23010004 },
    { 0x24010003 },
    { 0x25010004 },
    { 0x27010001 },
    { 0x28010001 },
    { 0x36010006 },
    { 0x3601000C },
    { 0x36EC0108 },
};

union AnimationStep D_800FA9B0[] = {
    { 0x37010001 },
    { 0x38FF0001 },
};

union AnimationStep D_800FA9B8[] = {
    { 0x0A010001 },
    { 0x0AFF0001 },
};

union AnimationStep D_800FA9C0[] = {
    { 0x0C010008 },
    { 0x1E01000C },
    { 0x1F010002 },
    { 0x20010006 },
    { 0x2001002A },
    { 0x26010002 },
    { 0x20010103 },
    { 0x26010002 },
    { 0x20010103 },
    { 0x26010002 },
    { 0x20010203 },
    { 0x26010002 },
    { 0x20010203 },
    { 0x26010002 },
    { 0x20010303 },
    { 0x26010002 },
    { 0x20010303 },
    { 0x26010002 },
    { 0x20010403 },
    { 0x26010002 },
    { 0x20010403 },
    { 0x26010002 },
    { 0x20010503 },
    { 0x26010002 },
    { 0x20010503 },
    { 0x26010002 },
    { 0x20010603 },
    { 0x26010002 },
    { 0x20010603 },
    { 0x26010002 },
    { 0x20010703 },
    { 0x26010002 },
    { 0x20010703 },
    { 0x26010002 },
    { 0x20010803 },
    { 0x26010002 },
    { 0x20010803 },
    { 0x26010002 },
    { 0x20010903 },
    { 0x26010002 },
    { 0x20010903 },
    { 0x26010002 },
    { 0x20010A03 },
    { 0x26010002 },
    { 0x1F010A06 },
    { 0x1E01000C },
    { 0x0C010007 },
    { 0x0CF60001 },
};

union AnimationStep D_800FAA80[] = {
    { 0x08010008 },
    { 0x09010006 },
    { 0x0A010006 },
    { 0x0B010002 },
    { 0x0B010003 },
    { 0x08010003 },
    { 0x08010063 },
    { 0x08010028 },
    { 0x08010006 },
    { 0x08F80114 },
};

union AnimationStep D_800FAAA8[] = {
    { 0x39010001 },
    { 0x3A010001 },
    { 0x3B010001 },
    { 0x3C010001 },
    { 0x3D010001 },
    { 0x3E010001 },
    { 0x3F010001 },
    { 0x40010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x41010001 },
    { 0x42010001 },
    { 0x43010001 },
    { 0x44010001 },
    { 0x45010001 },
    { 0x46010001 },
    { 0x47010001 },
    { 0x48010001 },
    { 0x49010001 },
    { 0x4A010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x4B010001 },
    { 0x4C010001 },
    { 0x4C010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x4D010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x36010001 },
    { 0x4E010001 },
    { 0x4F010001 },
    { 0x50FF0001 },
};

union AnimationStep D_800FAB80[] = {
    { 0x00010010 },
    { 0x00010010 },
    { 0x00010010 },
    { 0x00010009 },
    { 0x00010009 },
    { 0x0001000B },
    { 0x00010010 },
    { 0x00F9000E },
};

union AnimationStep D_800FABA0[] = {
    { 0x01010010 },
    { 0x01010010 },
    { 0x01010010 },
    { 0x01010009 },
    { 0x01010009 },
    { 0x0101000B },
    { 0x01010010 },
    { 0x01F9000E },
};

union AnimationStep D_800FABC0[] = {
    { 0x02010008 },
    { 0x03010008 },
    { 0x04010008 },
    { 0x05010108 },
    { 0x06FC0008 },
};

union AnimationStep D_800FABD4[] = {
    { 0x08010008 },
    { 0x09010008 },
    { 0x0A010008 },
    { 0x0B010008 },
    { 0x0CFC0008 },
};

union AnimationStep D_800FABE8[] = {
    { 0x07010008 },
    { 0x02010108 },
    { 0x03010008 },
    { 0x04010008 },
    { 0x05010008 },
    { 0x06FB0008 },
};

union AnimationStep D_800FAC00[] = {
    { 0x0D010008 },
    { 0x08010008 },
    { 0x09010008 },
    { 0x0A010008 },
    { 0x0B010008 },
    { 0x0CFB0008 },
};

union AnimationStep D_800FAC18[] = {
    { 0x07010008 },
    { 0x02010108 },
    { 0x03010008 },
    { 0x04010008 },
    { 0x02010008 },
    { 0x00FB0008 },
};

union AnimationStep D_800FAC30[] = {
    { 0x0D010008 },
    { 0x08010008 },
    { 0x09010008 },
    { 0x0A010008 },
    { 0x08010008 },
    { 0x01FB0008 },
};

union AnimationStep D_800FAC48[] = {
    { 0x00010008 },
    { 0x02010008 },
    { 0x0201001E },
    { 0x02010005 },
    { 0x05010004 },
    { 0x05010007 },
    { 0x05010004 },
    { 0x05F90014 },
};

union AnimationStep D_800FAC68[] = {
    { 0x01010008 },
    { 0x08010008 },
    { 0x0801001E },
    { 0x08010005 },
    { 0x0B010004 },
    { 0x0B010007 },
    { 0x0B010004 },
    { 0x0BF90014 },
};

union AnimationStep D_800FAC88[] = {
    { 0x05010003 },
    { 0x05010003 },
    { 0x05010003 },
    { 0x05010003 },
    { 0x05FC0006 },
};

union AnimationStep D_800FAC9C[] = {
    { 0x0B010003 },
    { 0x0B010003 },
    { 0x0B010003 },
    { 0x0B010003 },
    { 0x0BFC0006 },
};

union AnimationStep D_800FACB0[] = {
    { 0x00010008 },
    { 0x0001000C },
    { 0x02010008 },
    { 0x02010050 },
    { 0x02010006 },
    { 0x0001000C },
    { 0x00FA0008 },
};

union AnimationStep D_800FACCC[] = {
    { 0x01010008 },
    { 0x0101000C },
    { 0x08010008 },
    { 0x08010050 },
    { 0x08010006 },
    { 0x0101000C },
    { 0x01FA0008 },
};

union AnimationStep D_800FACE8[] = {
    { 0x00010014 },
    { 0x00010014 },
    { 0x00010016 },
    { 0x00010018 },
    { 0x0001000C },
    { 0x00FB0004 },
};

union AnimationStep D_800FAD00[] = {
    { 0x01010014 },
    { 0x01010014 },
    { 0x01010016 },
    { 0x01010018 },
    { 0x0101000C },
    { 0x01FB0004 },
};

union AnimationStep D_800FAD18[] = {
    { 0x05010001 },
    { 0x05FF0001 },
};

union AnimationStep D_800FAD20[] = {
    { 0x0B010001 },
    { 0x0BFF0001 },
};

union AnimationStep D_800FAD28[] = {
    { 0x00010008 },
    { 0x0001000C },
    { 0x02010008 },
    { 0x02010063 },
    { 0x02010028 },
    { 0x02010006 },
    { 0x0001000C },
    { 0x00FA0008 },
};

union AnimationStep D_800FAD48[] = {
    { 0x01010008 },
    { 0x0101000C },
    { 0x08010008 },
    { 0x08010063 },
    { 0x08010028 },
    { 0x08010006 },
    { 0x0101000C },
    { 0x01FA0008 },
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
