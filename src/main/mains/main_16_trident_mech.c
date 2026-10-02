// MainObj, main_object_update_funcs[16]
// 8004E890..8004FF90
#include "common.h"
#include "func_tables.h"

void trident_mech_update(struct MainObj* self)
{
    trident_mech_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

// trident_mech_init
INCLUDE_ASM("main/nonmatchings/mains/main_16_trident_mech", func_8004E8E0);

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
INCLUDE_ASM("main/nonmatchings/mains/main_16_trident_mech", func_8004ED60);

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
INCLUDE_ASM("main/nonmatchings/mains/main_16_trident_mech", func_8004F1A0);

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
        func_8001540C(2, 0x27, self);
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
        func_8001540C(2, 0x28, self);
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
        func_8001540C(2, 0x27, self);
    }
    if (--self->unk7C == 0) {
        func_8001540C(2, 0x29, self);
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
    func_8001540C(2, 0x29, self);
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
    func_8001540C(2, 0x29, self);
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
INCLUDE_ASM("main/nonmatchings/mains/main_16_trident_mech", func_8004FAE4);

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
        self->unk15 = 0x40;
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
INCLUDE_ASM("main/nonmatchings/mains/main_16_trident_mech", func_8004FD38);

struct Unk_unk68 trident_mech_stunned_hurt_box = { -14, -28, 30, 59 };

struct Unk_unk68 trident_mech_hurt_box = { -16, -8, 34, 37 };

struct Unk_unk68 trident_mech_attack_box = { -11, -17, 19, 47 };

struct Unk_unk68 trident_mech_charge_attack_box = { -89, -1, 69, 13 };

struct Unk_unk68 D_800FBBC8 = { 2, 2, 18, 26 };

union AnimationStep trident_mech_anim_0[] = {
    { 0x00010007 },
    { 0x00000101 },
};

union AnimationStep trident_mech_anim_1[] = {
    { 0x01010007 },
    { 0x01000101 },
};

union AnimationStep trident_mech_anim_2[] = {
    { 0x0A010003 },
    { 0x0BFF0103 },
};

union AnimationStep trident_mech_anim_16[] = {
    { 0x0C010001 },
    { 0x0D010002 },
    { 0x0C000101 },
};

union AnimationStep trident_mech_anim_3[] = {
    { 0x0C010008 },
    { 0x0D010008 },
    { 0x0C01001B },
    { 0x0C000101 },
};

union AnimationStep trident_mech_anim_4[] = {
    { 0x02010003 },
    { 0x03000101 },
};

union AnimationStep trident_mech_anim_5[] = {
    { 0x04010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x07010001 },
    { 0x05010001 },
    { 0x06FB0101 },
};

union AnimationStep trident_mech_anim_6[] = {
    { 0x11010002 },
    { 0x11000101 },
};

union AnimationStep trident_mech_anim_7[] = {
    { 0x0E010001 },
    { 0x10010001 },
    { 0x0FFE0101 },
};

union AnimationStep trident_mech_anim_10[] = {
    { 0x12010001 },
    { 0x13FF0101 },
};

union AnimationStep trident_mech_anim_9[] = {
    { 0x14010001 },
    { 0x15FF0101 },
};

union AnimationStep trident_mech_anim_8[] = {
    { 0x16010001 },
    { 0x17FF0101 },
};

union AnimationStep trident_mech_anim_13[] = {
    { 0x18010014 },
    { 0x1A010002 },
    { 0x19010201 },
    { 0x19010001 },
    { 0x1B010001 },
    { 0x1C010013 },
    { 0x1C000101 },
};

union AnimationStep trident_mech_anim_14[] = {
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1D010002 },
    { 0x1E010001 },
    { 0x1E000101 },
};

union AnimationStep trident_mech_anim_15[] = {
    { 0x1F010002 },
    { 0x20010002 },
    { 0x21FE0002 },
};

union AnimationStep trident_mech_anim_17[] = {
    { 0x00010008 },
    { 0x23010002 },
    { 0x22010022 },
    { 0x22000101 },
};

union AnimationStep trident_mech_anim_18[] = {
    { 0x24010002 },
    { 0x2501000E },
    { 0x25000101 },
};

union AnimationStep trident_mech_anim_19[] = {
    { 0x26010002 },
    { 0x2701000E },
    { 0x27000101 },
};

union AnimationStep trident_mech_anim_11[] = {
    { 0x28010002 },
    { 0x29FF0102 },
};

union AnimationStep trident_mech_anim_12[] = {
    { 0x2A010002 },
    { 0x2BFF0002 },
};

union AnimationStep trident_mech_anim_20[] = {
    { 0x2C010003 },
    { 0x2D010003 },
    { 0x2E010003 },
    { 0x2F010003 },
    { 0x30010003 },
    { 0x31010003 },
    { 0x32010003 },
    { 0x33010002 },
    { 0x33000101 },
};

union AnimationStep trident_mech_anim_21[] = {
    { 0x34000101 },
};

union AnimationStep trident_mech_anim_22[] = {
    { 0x35000101 },
};

union AnimationStep trident_mech_anim_23[] = {
    { 0x36000101 },
};

union AnimationStep trident_mech_anim_24[] = {
    { 0x37000101 },
};

union AnimationStep trident_mech_anim_25[] = {
    { 0x38000101 },
};

union AnimationStep trident_mech_anim_26[] = {
    { 0x39000101 },
};

union AnimationStep trident_mech_anim_27[] = {
    { 0x3A000101 },
};

union AnimationStep trident_mech_anim_28[] = {
    { 0x3B000101 },
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
