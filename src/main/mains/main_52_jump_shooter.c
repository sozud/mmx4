// MainObj, main_object_update_funcs[52]
// 8006A50C..8006AF70
#include "common.h"
#include "func_tables.h"

extern u8 jump_shooter_debris[];
extern void (*jump_shooter_step_funcs[])(struct MainObj*);

void jump_shooter_update(struct MainObj* self)
{
    jump_shooter_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

// jump_shooter_init
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_52_jump_shooter", func_8006A55C);
#else
void func_8006A55C(struct MainObj* self)
{
    const u8* const* animations = (const u8* const*)jump_shooter_animations;

    self->hp = 9;
    self->contact_damage = 3;
    self->invincibility_timer = 0;
    self->collision_data = D_801077F8;
    self->bg_offset = g_Player.bg_offset;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->animation_table = animations;
    self->unk16 = 6;
    self->terrain_box = &jump_shooter_terrain_box;
    self->hurt_box = &jump_shooter_hurt_box;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->attack_box = &jump_shooter_attack_box;
    jump_shooter_face_player(ANIMATED_OBJECT(self));
    self->unk7C = 0x5A;
    self->ext.main_52.unk80 = 0;
    self->ext.main_52.unk8C = 0;
    self->state = 1;
    self->unk5 = 3;
    self->unk6 = 0;
}
#endif

void jump_shooter_main(struct MainObj* self)
{
    s32 hit;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    jump_shooter_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    self->ext.main_52.saved_unk5 = self->unk5;
    hit = func_8002DD04(self);
    if (hit < 0) {
        spawn_explosion(self);
        spawn_debris(3, &jump_shooter_debris, self);
        drop_item(BASE_OBJECT(self), 0);
    } else if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }
    self->state = 2;
}

void jump_shooter_despawn(struct MainObj* self)
{
    self->ext.raw[0] = 0;
    self->ext.raw[1] = 0;
    self->ext.raw[2] = 0;
    self->ext.raw[3] = 0;
    self->ext.raw[4] = 0;
    self->ext.raw[5] = 0;
    despawn_object(OBJECT_HEADER(self));
}

void jump_shooter_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_52.saved_unk5;
}

void jump_shooter_fire(struct MainObj* self)
{
    jump_shooter_fire_funcs[self->unk6](self);
}

void jump_shooter_fire_aim(struct MainObj* self)
{
    jump_shooter_face_player(ANIMATED_OBJECT(self));
    func_8006AE80(self);
    if (self->ext.main_52.unk80 == 0) {
        set_animation(self, self->ext.main_52.unk88 + 0x12);
    } else {
        set_animation(self, self->ext.main_52.unk88 + 0x17);
    }
    self->unk6 = 1;
}

void jump_shooter_fire_ready(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk6 = 2;
        self->unk7C = 2;
        self->unk7E = 0xC;
    }
}

void jump_shooter_fire_shots(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7E != 0) {
        return;
    }
    if (self->ext.main_52.unk80 == 0) {
        set_animation(self, self->ext.main_52.unk88 + 2);
    } else {
        set_animation(self, self->ext.main_52.unk88 + 7);
    }
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x1B;
        shot->unk2 = self->ext.main_52.unk88 + self->ext.main_52.unk80 * 5;
        shot->unk40 = self->unk40;
        shot->unk42 = self->unk42;
        shot->animation_table = (u32**)self->animation_table;
        shot->unk3C = (void*)self->sprite_frames;
        shot->bg_offset = self->bg_offset;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->unk15 = self->unk15;
        set_velocity_from_angle(MOVING_OBJECT(shot), self->ext.main_52.unk84);
        shot->state = 0;
    }
    if (--self->unk7C == 0) {
        self->unk7C = 0x1E;
        self->unk6 = 3;
        self->ext.main_52.unk8C = 0;
    } else {
        self->unk7E = 0x10;
    }
}

void jump_shooter_fire_end(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7C == 0) {
        self->ext.main_52.unk8C = 0;
        self->unk7C = 0x5A;
        if (self->ext.main_52.unk80 == 0) {
            self->unk5 = 3;
            self->unk6 = 0;
        } else {
            self->x_speed = 0;
            self->gravity = FIXED(0.25);
            self->unk5 = 4;
            self->unk6 = 1;
        }
    }
}

void jump_shooter_walk(struct MainObj* self)
{
    jump_shooter_walk_funcs[self->unk6](self);
}

void jump_shooter_walk_start(struct MainObj* self)
{
    jump_shooter_face_player(ANIMATED_OBJECT(self));
    if (self->unk15 == 0) {
        self->x_speed = FIXED(-1.8);
    } else {
        self->x_speed = FIXED(1.8);
    }
    set_animation(self, 0);
    self->unk6 = 1;
}

// jump_shooter_walk_move
INCLUDE_ASM("main/nonmatchings/mains/main_52_jump_shooter", func_8006AAB4);

void jump_shooter_jump(struct MainObj* self)
{
    jump_shooter_jump_funcs[self->unk6](self);
}

void jump_shooter_jump_launch(struct MainObj* self)
{
    s8 event;

    animate_object(ANIMATED_OBJECT(self));
    event = self->animation_step.fields.event;
    if (2 == event) {
        u8 direction;

        self->ext.main_52.unk80 = 1;
        self->y_speed = FIXED(6);
        self->gravity = FIXED(0.25);
        direction = self->ext.main_52.unk8C;
        if (direction == 0) {
            if (self->unk15 != 0) {
                self->x_speed = FIXED(1.8);
            } else {
                self->x_speed = FIXED(-1.8);
            }
        } else if (direction == 1) {
            self->x_speed = 0;
        } else if (direction == event) {
            if (self->unk15 == 0) {
                self->x_speed = FIXED(1.8);
            } else {
                self->x_speed = FIXED(-1.8);
            }
        }
        move_with_gravity(ANIMATED_OBJECT(self));
        self->unk6 = 1;
    }
}

void jump_shooter_jump_air(struct MainObj* self)
{
    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->y_speed == 0 && self->ext.main_52.unk8C != 0) {
        self->gravity = 0;
        self->unk5 = 2;
        self->unk6 = 0;
    }
    if (self->collision_flags & 8) {
        self->y_speed = 0;
        self->gravity = 0;
        set_animation(self, 0x11);
        self->unk6 = 2;
    }
}

void jump_shooter_jump_land(struct MainObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.event != 0) {
        self->ext.main_52.unk80 = 0;
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void jump_shooter_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = 0x40;
    }
}

// jump_shooter_aim_at_player
INCLUDE_ASM("main/nonmatchings/mains/main_52_jump_shooter", func_8006AE80);

struct Unk_unk68 jump_shooter_hurt_box = { -14, -19, 25, 33 };

struct Unk_unk68 jump_shooter_attack_box = { -10, -18, 16, 30 };

struct Unk_unk68 jump_shooter_terrain_box = { 0, 0, 6, 15 };

union AnimationStep jump_shooter_anim_0[] = {
    { 0x0F010008 },
    { 0x10010008 },
    { 0x11010007 },
    { 0x12010008 },
    { 0x13010008 },
    { 0x14FB0107 },
};

union AnimationStep jump_shooter_anim_1[] = {
    { 0x00010008 },
    { 0x01010006 },
    { 0x02010003 },
    { 0x02010201 },
    { 0x03010006 },
    { 0x04000106 },
};

union AnimationStep jump_shooter_anim_2[] = {
    { 0x16010001 },
    { 0x15010006 },
    { 0x15000101 },
};

union AnimationStep jump_shooter_anim_3[] = {
    { 0x18010001 },
    { 0x17010006 },
    { 0x17000101 },
};

union AnimationStep jump_shooter_anim_4[] = {
    { 0x1A010001 },
    { 0x19010006 },
    { 0x19000101 },
};

union AnimationStep jump_shooter_anim_5[] = {
    { 0x1C010001 },
    { 0x1B010006 },
    { 0x1B000101 },
};

union AnimationStep jump_shooter_anim_6[] = {
    { 0x1E010001 },
    { 0x1D010006 },
    { 0x1D000101 },
};

union AnimationStep jump_shooter_anim_7[] = {
    { 0x06010001 },
    { 0x05010006 },
    { 0x05000101 },
};

union AnimationStep jump_shooter_anim_8[] = {
    { 0x08010001 },
    { 0x07010006 },
    { 0x07000101 },
};

union AnimationStep jump_shooter_anim_9[] = {
    { 0x0A010001 },
    { 0x09010006 },
    { 0x09000101 },
};

union AnimationStep jump_shooter_anim_10[] = {
    { 0x0C010001 },
    { 0x0B010006 },
    { 0x0B000101 },
};

union AnimationStep jump_shooter_anim_11[] = {
    { 0x0E010001 },
    { 0x0D010006 },
    { 0x0D000101 },
};

union AnimationStep jump_shooter_anim_12[] = {
    { 0x1F010001 },
    { 0x20010001 },
    { 0x21FE0001 },
};

union AnimationStep jump_shooter_anim_13[] = {
    { 0x22000101 },
};

union AnimationStep jump_shooter_anim_14[] = {
    { 0x23000101 },
};

union AnimationStep jump_shooter_anim_15[] = {
    { 0x24000101 },
};

union AnimationStep jump_shooter_anim_16[] = {
    { 0x25000101 },
};

union AnimationStep jump_shooter_anim_17[] = {
    { 0x03010006 },
    { 0x01010005 },
    { 0x01000101 },
};

union AnimationStep jump_shooter_anim_18[] = {
    { 0x17010002 },
    { 0x15010001 },
    { 0x15000101 },
};

union AnimationStep jump_shooter_anim_19[] = {
    { 0x17000101 },
};

union AnimationStep jump_shooter_anim_20[] = {
    { 0x17010002 },
    { 0x19010001 },
    { 0x19000101 },
};

union AnimationStep jump_shooter_anim_21[] = {
    { 0x17010002 },
    { 0x19010002 },
    { 0x1B010001 },
    { 0x1B000101 },
};

union AnimationStep jump_shooter_anim_22[] = {
    { 0x17010002 },
    { 0x19010002 },
    { 0x1B010002 },
    { 0x1D010001 },
    { 0x1D000101 },
};

union AnimationStep jump_shooter_anim_23[] = {
    { 0x07010002 },
    { 0x05010001 },
    { 0x05000101 },
};

union AnimationStep jump_shooter_anim_24[] = {
    { 0x07000101 },
};

union AnimationStep jump_shooter_anim_25[] = {
    { 0x07010002 },
    { 0x09010001 },
    { 0x09000101 },
};

union AnimationStep jump_shooter_anim_26[] = {
    { 0x07010002 },
    { 0x09010002 },
    { 0x0B010001 },
    { 0x0B000101 },
};

union AnimationStep jump_shooter_anim_27[] = {
    { 0x07010002 },
    { 0x09010002 },
    { 0x0B010002 },
    { 0x0D010001 },
    { 0x0D000101 },
};

union AnimationStep* jump_shooter_animations[28] = {
    jump_shooter_anim_0,
    jump_shooter_anim_1,
    jump_shooter_anim_2,
    jump_shooter_anim_3,
    jump_shooter_anim_4,
    jump_shooter_anim_5,
    jump_shooter_anim_6,
    jump_shooter_anim_7,
    jump_shooter_anim_8,
    jump_shooter_anim_9,
    jump_shooter_anim_10,
    jump_shooter_anim_11,
    jump_shooter_anim_12,
    jump_shooter_anim_13,
    jump_shooter_anim_14,
    jump_shooter_anim_15,
    jump_shooter_anim_16,
    jump_shooter_anim_17,
    jump_shooter_anim_18,
    jump_shooter_anim_19,
    jump_shooter_anim_20,
    jump_shooter_anim_21,
    jump_shooter_anim_22,
    jump_shooter_anim_23,
    jump_shooter_anim_24,
    jump_shooter_anim_25,
    jump_shooter_anim_26,
    jump_shooter_anim_27,
};

u8 jump_shooter_debris[4] = { 13, 14, 15, 16 };

void (*jump_shooter_state_funcs[3])() = {
    func_8006A55C,
    jump_shooter_main,
    jump_shooter_despawn,
};

void (*jump_shooter_step_funcs[5])() = {
    enemy_hit_reaction,
    jump_shooter_resume_step,
    jump_shooter_fire,
    jump_shooter_walk,
    jump_shooter_jump,
};

void (*jump_shooter_fire_funcs[4])(struct MainObj*) = {
    jump_shooter_fire_aim,
    jump_shooter_fire_ready,
    jump_shooter_fire_shots,
    jump_shooter_fire_end,
};

void (*jump_shooter_walk_funcs[2])(struct MainObj*) = {
    jump_shooter_walk_start,
    func_8006AAB4,
};

void (*jump_shooter_jump_funcs[3])(struct MainObj*) = {
    jump_shooter_jump_launch,
    jump_shooter_jump_air,
    jump_shooter_jump_land,
};
