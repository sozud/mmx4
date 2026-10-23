// MainObj, main_object_update_funcs[76]
// 800919C4..80091E38
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_76_spike_crawler.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/objects.h"
#include "main/1CF60.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1CF60.h"
#endif

extern s8 spike_crawler_attack_box[4];
extern s8 spike_crawler_hurt_box[4];

// spike_crawler_state_funcs
extern void (*spike_crawler_state_funcs[])(struct MainObj*);

void spike_crawler_update_speed(struct MainObj*);
void spike_crawler_main(struct MainObj*);
void spike_crawler_despawn(struct MainObj*);

void spike_crawler_update(struct MainObj* self)
{
    spike_crawler_state_funcs[self->state](self);
}

void spike_crawler_init(struct MainObj* arg0)
{
    struct MainObj* self = arg0;

    self->state = 1;
    self->unk5 = 0;
    self->unk6 = 0;
    self->unk7C = 0;
    self->unk7E = 0;
    self->bg_offset = 0;
    self->hp = 3;
    self->contact_damage = 4;
    self->invincibility_timer = 0;
    self->animation_table = (const u8* const*)spike_crawler_animations;
    self->hurt_box = spike_crawler_hurt_box;
    self->attack_box = spike_crawler_attack_box;
    self->terrain_box = (struct Unk_unk68*)spike_crawler_terrain_box;
    self->collision_data = D_80108484;
    self->air_state = 0;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->x_speed = FIXED(2);
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->ext.main_76.saved_x_velocity = self->x_speed;
    self->unk16 = VISUAL_SATURN_LAYER(5);
    set_animation(self, 0);
}

void spike_crawler_fall(struct MainObj* self)
{
    if (self->collision_flags & 8) {
        self->unk5 = 0;
        self->unk6 = 0;
        self->unk7C = 0;
        self->x_speed = self->ext.main_76.saved_x_velocity;
        self->y_speed = 0;
        self->x_accel = 0;
        self->gravity = 0;
        return;
    }

    move_with_gravity(ANIMATED_OBJECT(self));
}

// spike_crawler_crawl

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80091B1C(struct MainObj* arg0);
void func_80091EC4(struct MainObj* self);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80091B1C(struct MainObj* arg0)
{
    struct Unk_unk68* bounds;
    s32 velocity = arg0->x_speed;
    s16 x;
    s16 y;
    s32 reverse = 0;

    if (!(arg0->collision_flags & 8)) {
        arg0->unk5 = 1;
        arg0->unk6 = 0;
        arg0->unk7C = 0;
        arg0->x_speed = 0;
        arg0->y_speed = 0;
        arg0->x_accel = 0;
        arg0->gravity = 0x4200;
        arg0->ext.main_76.saved_x_velocity = velocity;
        return;
    }

    bounds = arg0->terrain_box;
    y = arg0->y_pos.i.hi + bounds->unk1 + (u8)bounds->unk3 + 4;
    if (arg0->x_speed < 0) {
        reverse = (arg0->collision_flags & 2) != 0;
        x = arg0->x_pos.i.hi + bounds->unk0 - (u8)bounds->unk2;
    } else {
        reverse = (arg0->collision_flags & 1) != 0;
        x = arg0->x_pos.i.hi + bounds->unk0 + (u8)bounds->unk2;
    }
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) < 0x38)
        reverse = 1;
    if (reverse)
        arg0->x_speed = -arg0->x_speed;
    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_76_spike_crawler", func_80091B1C);
#endif

void spike_crawler_update_speed(struct MainObj* self)
{
    s16 object_y;
    s32 player_y;
    s32 distance;

    object_y = self->y_pos.u.hi - 8;
    player_y = g_Player.y_pos.i.hi;
    distance = player_y - object_y;

    if (distance >= 0 ? distance < 0x10 : object_y - player_y < 0x10) {
        if (self->x_speed < 0) {
            self->x_speed = FIXED(-4);
        } else {
            self->x_speed = FIXED(4);
        }
        self->unk7E = 0x78;
    } else if (self->unk7E == 0) {
        if (self->x_speed < 0) {
            self->x_speed = FIXED(-2);
        } else {
            self->x_speed = FIXED(2);
        }
    } else {
        self->unk7E--;
    }
}

void spike_crawler_main(struct MainObj* self)
{
    s32 collision;

    self->unk18.val = self->x_pos.val;
    self->on_screen = 0;
    self->unk1C.val = self->y_pos.val;

    if (self->unk5 == 0) {
        if (self->unk7C != 0) {
            self->unk7C--;
        }
        spike_crawler_update_speed(self);
        if (self->unk7C == 0) {
            func_80091B1C(self);
        }
    } else {
        spike_crawler_fall(self);
    }

    CollisionRelated(PLAYER_OBJECT(self));
    collision = func_8002DD04(self);
    if (collision < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, spike_crawler_debris, self);
        self->state = 2;
        return;
    }

    if (collision != 0) {
        self->unk7C = 0x3C;
    }
    func_8002D9BC(self);
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state = 2;
    }
}

void spike_crawler_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

union AnimationStep spike_crawler_anim_0[16] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x05 },
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, -15, 0x0F },
};

union AnimationStep spike_crawler_anim_1[1] = { { 2, 0, 0, 0x10 } };

union AnimationStep spike_crawler_anim_2[1] = { { 2, 0, 0, 0x11 } };

union AnimationStep spike_crawler_anim_3[1] = { { 2, 0, 0, 0x12 } };

union AnimationStep spike_crawler_anim_4[1] = { { 2, 0, 0, 0x13 } };

union AnimationStep* spike_crawler_animations[5] = {
    spike_crawler_anim_0,
    spike_crawler_anim_1,
    spike_crawler_anim_2,
    spike_crawler_anim_3,
    spike_crawler_anim_4,
};

u8 spike_crawler_debris[4] = { 1, 2, 3, 4 };

s8 spike_crawler_terrain_box[4] = { -1, 0, 11, 11 };

s8 spike_crawler_attack_box[4] = { -9, -6, 16, 15 };

s8 spike_crawler_hurt_box[4] = { -11, -8, 20, 18 };

void (*spike_crawler_state_funcs[])(struct MainObj*) = {
    spike_crawler_init,
    spike_crawler_main,
    spike_crawler_despawn,
};
