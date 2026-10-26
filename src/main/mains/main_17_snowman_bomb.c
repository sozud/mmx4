// MainObj, main_object_update_funcs[17]
// 8004FF90..80050708
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_17_snowman_bomb.h"
#include "main/1CF60.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/objects.h"

extern struct Unk_unk68 snowman_bomb_hurt_box;
extern struct Unk_unk68 snowman_bomb_attack_box;

extern union AnimationStep* snowman_bomb_animations[];
extern struct Unk_unk68 snowman_bomb_blast_hurt_box;
extern struct Unk_unk68 snowman_bomb_blast_attack_box;
extern struct Unk_unk68 snowman_bomb_blast_terrain_box;
extern u8 snowman_bomb_debris[4];

void snowman_bomb_check_fall(struct MainObj*);

// snowman_bomb_state_funcs
extern void (*snowman_bomb_state_funcs[])(struct MainObj*);

void snowman_bomb_despawn(struct MainObj*);

// snowman_bomb_step_funcs
extern void (*snowman_bomb_step_funcs[])(struct MainObj*);
void snowman_bomb_resume_step(struct MainObj* arg0);

void snowman_bomb_turn(struct MainObj* arg0);
void snowman_bomb_detonate(struct MainObj* arg0);
void snowman_bomb_fall(struct MainObj* arg0);
void snowman_bomb_wait(struct MainObj* arg0);

void snowman_bomb_face_player(struct AnimatedObj* self);

void snowman_bomb_update(struct MainObj* self)
{
    snowman_bomb_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_17_snowman_bomb", snowman_bomb_init);
#else
void snowman_bomb_init(struct MainObj* self)
{
    self->hp = 6;
    self->contact_damage = 2;
    self->invincibility_timer = 0;
    self->collision_data = D_80106AF4;
    self->bg_offset = (u8)g_Player.bg_offset;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->animation_table = (const u8* const*)snowman_bomb_animations;
    self->terrain_box = &snowman_bomb_terrain_box;
    self->hurt_box = &snowman_bomb_hurt_box;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->attack_box = &snowman_bomb_attack_box;
    snowman_bomb_face_player(ANIMATED_OBJECT(self));
    set_animation(self, 0);
    self->ext.main_17.unk80 = 4;
    self->ext.main_17.unk84 = 3;
    self->ext.main_17.unk88 = 0xC;
    self->ext.main_17.unk8C = 0;
    self->state = 1;
    self->unk5 = 2;
    self->unk6 = 0;
    self->ext.main_17.saved_unk5 = self->y_pos.val;
}
#endif

void snowman_bomb_main(struct MainObj* self)
{
    s32 collision;

    snowman_bomb_check_fall(self);
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    snowman_bomb_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    self->ext.main_17.unk90 = self->unk5;
    collision = func_8002DD04(self);
    if (func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi + self->terrain_box->unk0,
            self->terrain_box->unk3 + (self->y_pos.i.hi + self->terrain_box->unk1))
        == 0x3E) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, snowman_bomb_debris, self);
    } else if (collision < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, snowman_bomb_debris, self);
        drop_item(BASE_OBJECT(self), 0);
    } else if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
        return;
    }
    self->state = 2;
}

void snowman_bomb_despawn(struct MainObj* self)
{
    self->ext.main_17.unk80 = 0;
    self->ext.main_17.unk84 = 0;
    self->ext.main_17.unk88 = 0;
    self->ext.main_17.unk8C = 0;
    self->ext.main_17.unk90 = 0;
    self->ext.main_17.saved_unk5 = 0;
    despawn_object(OBJECT_HEADER(self));
}

void snowman_bomb_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.raw[4];
}

// snowman_bomb_hop

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80050278(struct MainObj* arg0);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_17_snowman_bomb", func_80050278);
#else
void func_80050278(struct MainObj* arg0)
{
    if (--arg0->ext.main_17.unk80 == 0) {
        arg0->x_speed = 0;
        arg0->x_accel = 0;
        arg0->y_speed = 0;
        arg0->gravity = 0;
        if ((ABS(g_Player.x_pos.i.hi, arg0->x_pos.i.hi) <= 0x60 && arg0->y_pos.i.hi - g_Player.y_pos.i.hi <= 0x10)
            || --arg0->ext.main_17.unk88 == 0) {
            if (arg0->unk15 == 0) {
                arg0->x_speed = -0x30000;
                arg0->x_accel = -0x1000;
            } else {
                arg0->x_speed = 0x30000;
                arg0->x_accel = -0x1000;
            }
            arg0->ext.main_17.unk8C = 1;
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            set_animation(arg0, 2);
        } else if (--arg0->ext.main_17.unk84 == 0) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            set_animation(arg0, 1);
        } else {
            arg0->unk7C = 0x14;
            arg0->unk5 = 6;
            arg0->unk6 = 0;
        }
        return;
    }
    if (arg0->collision_flags & 3)
        arg0->unk15 ^= PLAYER_FACING_RIGHT;
    if (arg0->unk15 == 0)
        arg0->x_speed = -0x10000;
    else
        arg0->x_speed = 0x10000;
    arg0->y_speed = 0x80000;
    arg0->ext.main_17.saved_unk5 = arg0->y_pos.val;
    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
}
#endif

void snowman_bomb_turn(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        snowman_bomb_face_player(ANIMATED_OBJECT(self));
        self->unk5 = 2;
        self->unk6 = 0;
        self->ext.main_17.unk80 = 4;
        self->ext.main_17.unk84 = 3;
        set_animation(self, 0);
    }
}

void snowman_bomb_detonate(struct MainObj* self)
{
    if (self->x_speed != 0) {
        move_with_gravity(ANIMATED_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 2) {
        self->terrain_box = &snowman_bomb_blast_terrain_box;
        self->hurt_box = &snowman_bomb_blast_hurt_box;
        self->attack_box = &snowman_bomb_blast_attack_box;
    }
    if (self->animation_step.fields.event == 1) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, snowman_bomb_debris, self);
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
        set_animation(self, 0);
    }
}

void snowman_bomb_fall(struct MainObj* self)
{
    s32 target_y;
    s32 current_y;

    if (self->collision_flags & 8) {
        if (self->ext.main_17.unk8C != 0) {
            self->unk5 = 4;
            self->unk6 = 0;
            self->air_state = 0;
        } else {
            set_animation(self, 0);
            target_y = self->ext.main_17.saved_unk5;
            current_y = self->y_pos.val;
            self->unk5 = 2;
            self->unk6 = 0;
            self->y_speed = 0;
            self->gravity = 0;
            self->x_speed = 0;
            self->x_accel = 0;
            self->air_state = 0;
            if (ABS(target_y, current_y) >= 0x80000) {
                self->ext.main_17.unk80 = 4;
                self->ext.main_17.unk84 = 3;
                self->ext.main_17.unk88 = 0xC;
            }
        }
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->x_speed == 0) {
            self->x_accel = 0;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void snowman_bomb_wait(struct MainObj* self)
{
    if (--self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->ext.main_17.unk80 = 4;
        set_animation(self, 0);
    }
}

void snowman_bomb_check_fall(struct MainObj* self)
{
    if (self->air_state == 0 && !(self->collision_flags & 8)) {
        self->unk5 = 5;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = 0x4200;
        self->air_state = 1;
    }
}

void snowman_bomb_face_player(struct AnimatedObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
}

struct Unk_unk68 snowman_bomb_hurt_box = { -8, -13, 15, 26 };

struct Unk_unk68 snowman_bomb_attack_box = { -7, -11, 12, 22 };

struct Unk_unk68 snowman_bomb_terrain_box = { 0, 0, 5, 13 };

struct Unk_unk68 snowman_bomb_blast_hurt_box = { -12, -1, 25, 13 };

struct Unk_unk68 snowman_bomb_blast_attack_box = { -10, 1, 21, 10 };

struct Unk_unk68 snowman_bomb_blast_terrain_box = { 0, 5, 13, 8 };

union AnimationStep snowman_bomb_anim_0[] = {
    { 8, 0, 1, 0x00 },
    { 3, 0, 1, 0x03 },
    { 4, 0, 1, 0x04 },
    { 6, 0, 1, 0x05 },
    { 4, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 1, 1, 0, 0x03 },
};

union AnimationStep snowman_bomb_anim_1[] = {
    { 12, 0, 1, 0x00 },
    { 6, 0, 1, 0x01 },
    { 12, 0, 1, 0x02 },
    { 6, 0, 1, 0x01 },
    { 12, 0, 1, 0x00 },
    { 6, 0, 1, 0x01 },
    { 12, 0, 1, 0x02 },
    { 6, 0, 1, 0x01 },
    { 11, 0, 1, 0x00 },
    { 12, 1, 0, 0x00 },
};

union AnimationStep snowman_bomb_anim_2[] = {
    { 5, 0, 1, 0x06 },
    { 4, 0, 1, 0x07 },
    { 4, 0, 1, 0x08 },
    { 4, 2, 1, 0x07 },
    { 60, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 29, 0, 1, 0x09 },
    { 1, 1, 0, 0x09 },
};

union AnimationStep snowman_bomb_anim_3[] = {
    { 1, 1, 0, 0x0B },
};

union AnimationStep snowman_bomb_anim_4[] = {
    { 1, 1, 0, 0x0C },
};

union AnimationStep snowman_bomb_anim_5[] = {
    { 1, 1, 0, 0x0D },
};

union AnimationStep snowman_bomb_anim_6[] = {
    { 1, 1, 0, 0x0E },
};

union AnimationStep* snowman_bomb_animations[7] = {
    snowman_bomb_anim_0,
    snowman_bomb_anim_1,
    snowman_bomb_anim_2,
    snowman_bomb_anim_3,
    snowman_bomb_anim_4,
    snowman_bomb_anim_5,
    snowman_bomb_anim_6,
};

u8 snowman_bomb_debris[4] = { 3, 4, 5, 6 };

void (*snowman_bomb_state_funcs[3])() = {
    snowman_bomb_init,
    snowman_bomb_main,
    snowman_bomb_despawn,
};

void (*snowman_bomb_step_funcs[7])(struct MainObj*) = {
    enemy_hit_reaction,
    snowman_bomb_resume_step,
    func_80050278,
    snowman_bomb_turn,
    snowman_bomb_detonate,
    snowman_bomb_fall,
    snowman_bomb_wait,
};
