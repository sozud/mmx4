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

#ifndef VERSION_DEMO
void spike_crawler_init(struct MainObj* self)
{

    self->state = 1;
    self->unk5 = 0;
    self->unk6 = 0;
    self->unk7C = 0;
    self->unk7E = 0;
    self->bg_offset = 0;
    self->hp = 3;
    self->contact_damage = 4;
    self->invincibility_timer = 0;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->animation_table = (const u8* const*)spike_crawler_animations;
    self->hurt_box = spike_crawler_hurt_box;
    self->attack_box = spike_crawler_attack_box;
    self->terrain_box = (struct Unk_unk68*)spike_crawler_terrain_box;
    self->collision_data = D_80108484;
    self->air_state = 0;
    self->x_speed = FIXED(2);
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->ext.main_76.saved_x_velocity = self->x_speed;
    self->unk16 = VISUAL_SATURN_LAYER(5);
    set_animation(self, 0);
}
#endif

#ifndef VERSION_DEMO
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
#endif

// spike_crawler_crawl

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80091B1C(struct MainObj* arg0);
void func_80091EC4(struct MainObj* self);
#endif

#ifndef VERSION_DEMO
void func_80091B1C(struct MainObj* arg0)
{
    struct Unk_unk68* bounds;
    s16 x;
    s16 y;
    u32 reverse;

    if (!(arg0->collision_flags & 8)) {
        s32 velocity = arg0->x_speed;

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

    reverse = 0;
    bounds = arg0->terrain_box;
    y = arg0->y_pos.i.hi + bounds->unk1 + (u8)bounds->unk3 + 4;
    if (arg0->x_speed < 0) {
        x = arg0->collision_flags & 2;
        reverse = x != 0;
        x = arg0->x_pos.i.hi + bounds->unk0 - (u8)bounds->unk2;
    } else {
        if (arg0->collision_flags & 1)
            reverse = 1;
        x = arg0->x_pos.i.hi + bounds->unk0 + (u8)bounds->unk2;
    }
    if (func_8002D724(PLAYER_OBJECT(arg0), x, y) < 0x38)
        reverse = 1;
    if (reverse)
        arg0->x_speed = -arg0->x_speed;
    move_with_gravity(ANIMATED_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
}
#endif

#ifndef VERSION_DEMO
void spike_crawler_update_speed(struct MainObj* self)
{
    s16 object_y;
    s32 player_y;
    s32 distance;

    object_y = self->y_pos.i.hi - 8;
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
#endif

#ifndef VERSION_DEMO
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
#endif

#ifndef VERSION_DEMO
void spike_crawler_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}
#endif

#ifdef VERSION_DEMO
void ride_armor_pilot_stub(struct MainObj*);
void ride_armor_pilot_despawn_idle(struct MainObj*);
void general_slam_land(struct MainObj* self);
void general_slam(struct MainObj* self);

struct Unk_unk68 D_800D5E90_demo[5] = {
    { -7, 15, 33, 11 },
    { -40, -5, 50, 29 },
    { -14, -16, 39, 39 },
    { -40, -16, 65, 41 },
    { -30, -10, 49, 30 },
};

union AnimationStep D_800D5EA4_demo[1] = { { 1, 0, 0, 0x00 } };

union AnimationStep D_800D5EA8_demo[16] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 1, 0, 1, 0x06 },
    { 2, 0, 1, 0x03 },
    { 1, 0, 1, 0x07 },
    { 2, 0, 1, 0x04 },
    { 1, 0, 1, 0x08 },
    { 2, 0, 1, 0x05 },
    { 1, 0, 1, 0x09 },
    { 2, 0, 1, 0x05 },
    { 1, 0, 1, 0x09 },
    { 2, 0, 1, 0x05 },
    { 1, 0, 1, 0x09 },
    { 2, 0, 1, 0x04 },
    { 1, 0, 0, 0x08 },
};

union AnimationStep D_800D5EE8_demo[16] = {
    { 2, 0, 1, 0x03 },
    { 1, 0, 1, 0x07 },
    { 2, 0, 1, 0x02 },
    { 1, 0, 1, 0x06 },
    { 2, 0, 1, 0x02 },
    { 1, 0, 1, 0x06 },
    { 2, 0, 1, 0x02 },
    { 1, 0, 1, 0x06 },
    { 2, 0, 1, 0x03 },
    { 1, 0, 1, 0x07 },
    { 2, 0, 1, 0x04 },
    { 1, 0, 1, 0x08 },
    { 2, 0, 1, 0x04 },
    { 1, 0, 1, 0x08 },
    { 2, 0, 1, 0x04 },
    { 1, 0, -15, 0x08 },
};

union AnimationStep D_800D5F28_demo[9] = {
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x04 },
    { 6, 0, 1, 0x05 },
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 3, 0, 1, 0x01 },
    { 2, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep D_800D5F4C_demo[1] = { { 1, 0, 0, 0x0A } };

union AnimationStep D_800D5F50_demo[27] = {
    { 2, 0, 1, 0x92 },
    { 2, 0, 1, 0x93 },
    { 2, 0, 1, 0x92 },
    { 2, 0, 1, 0x93 },
    { 2, 0, 1, 0x92 },
    { 2, 0, 1, 0x93 },
    { 2, 0, 1, 0x92 },
    { 2, 0, 1, 0x93 },
    { 2, 0, 1, 0x92 },
    { 2, 0, 1, 0x93 },
    { 2, 0, 1, 0x92 },
    { 2, 0, 1, 0x93 },
    { 2, 0, 1, 0x92 },
    { 2, 0, 1, 0x93 },
    { 2, 0, 1, 0x0C },
    { 1, 0, 1, 0xA3 },
    { 1, 0, 1, 0xA4 },
    { 1, 0, 1, 0xA5 },
    { 1, 0, 1, 0xA6 },
    { 1, 0, 1, 0xA7 },
    { 1, 0, 1, 0xAA },
    { 1, 0, 1, 0xA3 },
    { 1, 0, 1, 0xA4 },
    { 1, 0, 1, 0xA5 },
    { 1, 0, 1, 0xA8 },
    { 1, 0, 1, 0xA9 },
    { 1, 0, -11, 0xAA },
};

union AnimationStep D_800D5FBC_demo[29] = {
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x11 },
    { 1, 0, 1, 0x3A },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x3C },
    { 1, 0, 1, 0x3D },
    { 1, 0, 1, 0x3E },
    { 1, 0, 1, 0x41 },
    { 1, 0, 1, 0x3A },
    { 1, 0, 1, 0x3B },
    { 1, 0, 1, 0x3C },
    { 1, 0, 1, 0x3F },
    { 1, 0, 1, 0x40 },
    { 1, 0, -11, 0x41 },
};

union AnimationStep D_800D6030_demo[1] = { { 1, 0, 0, 0x0B } };

union AnimationStep D_800D6034_demo[31] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x12 },
    { 16, 0, 1, 0x13 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x14 },
    { 6, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 2, 0, 1, 0x12 },
    { 40, 0, 1, 0x13 },
    { 2, 0, 1, 0x12 },
    { 3, 0, 1, 0x01 },
    { 2, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep D_800D60B0_demo[31] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x12 },
    { 16, 0, 1, 0x13 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x14 },
    { 6, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 1, 0, 1, 0x18 },
    { 2, 0, 1, 0x19 },
    { 40, 0, 1, 0x1A },
    { 2, 0, 1, 0x19 },
    { 3, 0, 1, 0x01 },
    { 2, 0, 1, 0x00 },
    { 1, 0, 1, 0x00 },
};

union AnimationStep D_800D612C_demo[10] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x1B },
    { 35, 0, 1, 0x1C },
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 30, 0, 1, 0x1F },
    { 2, 0, 1, 0x01 },
    { 1, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep D_800D6154_demo[29] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x20 },
    { 6, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x21 },
    { 1, 0, 1, 0x22 },
    { 2, 0, 1, 0x23 },
    { 1, 0, 1, 0x24 },
    { 1, 0, 1, 0x25 },
    { 20, 0, 1, 0x24 },
    { 3, 0, 1, 0x23 },
    { 3, 0, 1, 0x01 },
    { 2, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep D_800D61C8_demo[20] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x20 },
    { 15, 0, 1, 0x21 },
    { 3, 0, 1, 0x26 },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x2A },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x28 },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x2C },
    { 20, 0, 1, 0x27 },
    { 3, 0, 1, 0x26 },
    { 3, 0, 1, 0x01 },
    { 2, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep D_800D6218_demo[1] = { { 1, 0, 0, 0x2D } };

union AnimationStep D_800D621C_demo[12] = {
    { 1, 0, 1, 0x2E },
    { 1, 0, 1, 0x2F },
    { 1, 0, 1, 0x30 },
    { 1, 0, 1, 0x31 },
    { 1, 0, 1, 0x32 },
    { 1, 0, 1, 0x33 },
    { 1, 0, 1, 0x34 },
    { 1, 0, 1, 0x35 },
    { 1, 0, 1, 0x36 },
    { 1, 0, 1, 0x37 },
    { 1, 0, 1, 0x38 },
    { 1, 0, -11, 0x39 },
};

union AnimationStep D_800D624C_demo[3] = { { 2, 0, 1, 0x06 }, { 1, 0, 1, 0x56 }, { 1, 0, -2, 0x56 } };

union AnimationStep D_800D6258_demo[45] = {
    { 2, 0, 1, 0x54 },
    { 2, 0, 1, 0x55 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x52 },
    { 2, 0, 1, 0x53 },
    { 2, 0, 1, 0x54 },
    { 2, 0, 1, 0x55 },
    { 2, 0, 1, 0x57 },
    { 2, 0, 1, 0x58 },
    { 2, 0, 1, 0x59 },
    { 2, 0, 1, 0x5A },
    { 2, 0, 1, 0x59 },
    { 2, 0, 1, 0x5A },
    { 2, 0, 1, 0x59 },
    { 2, 0, 1, 0x5A },
    { 2, 0, 1, 0x59 },
    { 2, 0, 1, 0x5A },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x2A },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x28 },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x2B },
    { 1, 0, 1, 0x29 },
    { 1, 0, 1, 0x2C },
    { 1, 0, 1, 0x27 },
    { 1, 0, 1, 0x26 },
    { 1, 0, 1, 0x01 },
    { 1, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep D_800D630C_demo[1] = { { 1, 0, 0, 0x5B } };

union AnimationStep D_800D6310_demo[26] = {
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x0D },
    { 1, 0, 1, 0x0E },
    { 39, 0, 1, 0x0D },
    { 1, 0, 0, 0x0D },
};

union AnimationStep D_800D6378_demo[3] = { { 2, 0, 1, 0x5C }, { 1, 0, 1, 0x5D }, { 1, 0, -2, 0x5D } };

union AnimationStep D_800D6384_demo[5] = {
    { 50, 0, 1, 0x5C },
    { 6, 0, 1, 0x5E },
    { 6, 0, 1, 0x5F },
    { 5, 0, 1, 0x5E },
    { 1, 0, 0, 0x5E },
};

union AnimationStep D_800D6398_demo[7] = {
    { 50, 0, 1, 0x5F },
    { 2, 0, 1, 0x60 },
    { 30, 0, 1, 0x5F },
    { 2, 0, 1, 0x60 },
    { 6, 0, 1, 0x5F },
    { 1, 0, 1, 0x60 },
    { 1, 0, 0, 0x60 },
};

union AnimationStep D_800D63B4_demo[29] = {
    { 1, 0, 1, 0x64 },
    { 1, 0, 1, 0x65 },
    { 1, 0, 1, 0x66 },
    { 1, 0, 1, 0x67 },
    { 1, 0, 1, 0x68 },
    { 1, 0, 1, 0x69 },
    { 10, 0, 1, 0x76 },
    { 1, 0, 1, 0x6A },
    { 1, 0, 1, 0x6B },
    { 1, 0, 1, 0x6C },
    { 1, 0, 1, 0x6D },
    { 1, 0, 1, 0x6E },
    { 1, 0, 1, 0x6F },
    { 30, 0, 1, 0x76 },
    { 1, 0, 1, 0x70 },
    { 1, 0, 1, 0x71 },
    { 1, 0, 1, 0x72 },
    { 1, 0, 1, 0x73 },
    { 1, 0, 1, 0x74 },
    { 1, 0, 1, 0x75 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x6A },
    { 1, 0, 1, 0x6B },
    { 1, 0, 1, 0x6C },
    { 1, 0, 1, 0x6D },
    { 1, 0, 1, 0x6E },
    { 1, 0, 1, 0x6F },
    { 29, 0, 1, 0x76 },
    { 1, 0, 0, 0x76 },
};

union AnimationStep D_800D6428_demo[43] = {
    { 50, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 4, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 4, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 4, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 4, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 4, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 4, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 4, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 4, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x5C },
    { 2, 0, 1, 0x61 },
    { 2, 0, 1, 0x5C },
    { 1, 0, 1, 0x61 },
    { 1, 0, -1, 0x5C },
};

union AnimationStep D_800D64D4_demo[11] = {
    { 1, 0, 1, 0x42 },
    { 1, 0, 1, 0x43 },
    { 1, 0, 1, 0x44 },
    { 1, 0, 1, 0x45 },
    { 1, 0, 1, 0x46 },
    { 1, 0, 1, 0x47 },
    { 1, 0, 1, 0x4D },
    { 1, 0, 1, 0x4E },
    { 1, 0, 1, 0x4F },
    { 1, 0, 1, 0x50 },
    { 1, 0, 0, 0x51 },
};

union AnimationStep D_800D6500_demo[11] = {
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x63 },
    { 1, 0, 1, 0x48 },
    { 1, 0, 1, 0x49 },
    { 1, 0, 1, 0x4A },
    { 1, 0, 0, 0x4B },
};

union AnimationStep D_800D652C_demo[18] = {
    { 1, 0, 1, 0x77 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x78 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x79 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x7A },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x7B },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x7C },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x7D },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x7E },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x7F },
    { 1, 0, -13, 0x76 },
};

union AnimationStep D_800D6574_demo[8] = {
    { 1, 0, 1, 0x80 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x81 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x82 },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0x83 },
    { 1, 0, 0, 0x76 },
};

union AnimationStep D_800D6594_demo[11] = {
    { 2, 0, 1, 0x84 },
    { 2, 0, 1, 0x85 },
    { 2, 0, 1, 0x86 },
    { 2, 0, 1, 0x87 },
    { 2, 0, 1, 0x88 },
    { 2, 0, 1, 0x89 },
    { 2, 0, 1, 0x8A },
    { 2, 0, 1, 0x8B },
    { 2, 0, 1, 0x8C },
    { 1, 0, 1, 0x8D },
    { 1, 0, -10, 0x8D },
};

union AnimationStep D_800D65C0_demo[11] = {
    { 2, 0, 1, 0x8E },
    { 2, 0, 1, 0x8F },
    { 2, 0, 1, 0x90 },
    { 1, 0, 1, 0x91 },
    { 1, 0, 1, 0x92 },
    { 1, 0, 1, 0x93 },
    { 1, 0, 1, 0x95 },
    { 1, 0, 1, 0x91 },
    { 1, 0, 1, 0x92 },
    { 1, 0, 1, 0x94 },
    { 1, 0, -7, 0x95 },
};

union AnimationStep D_800D65EC_demo[11] = {
    { 2, 0, 1, 0x96 },
    { 2, 0, 1, 0x97 },
    { 2, 0, 1, 0x98 },
    { 2, 0, 1, 0x99 },
    { 1, 0, 1, 0x9A },
    { 2, 0, 1, 0x9B },
    { 1, 0, 1, 0x9D },
    { 2, 0, 1, 0x99 },
    { 1, 0, 1, 0x9A },
    { 2, 0, 1, 0x9C },
    { 1, 0, -7, 0x9D },
};

union AnimationStep D_800D6618_demo[8] = {
    { 2, 0, 1, 0x9E },
    { 1, 0, 1, 0x9F },
    { 2, 0, 1, 0xA0 },
    { 1, 0, 1, 0xA2 },
    { 2, 0, 1, 0x9E },
    { 1, 0, 1, 0x9F },
    { 2, 0, 1, 0xA1 },
    { 1, 0, -7, 0xA2 },
};

union AnimationStep D_800D6638_demo[5] = {
    { 2, 0, 1, 0xAB },
    { 1, 0, 1, 0x76 },
    { 1, 0, 1, 0xAB },
    { 1, 0, 1, 0xAC },
    { 1, 0, -2, 0xAD },
};

union AnimationStep D_800D664C_demo[8] = {
    { 1, 0, 1, 0xAE },
    { 2, 0, 1, 0xAF },
    { 2, 0, 1, 0xB0 },
    { 1, 0, 1, 0xB1 },
    { 1, 0, 1, 0xB2 },
    { 1, 0, 1, 0xB3 },
    { 1, 0, 1, 0xB4 },
    { 1, 0, 0, 0xB5 },
};

union AnimationStep D_800D666C_demo[14] = {
    { 1, 0, 1, 0xB6 },
    { 1, 0, 1, 0xB7 },
    { 2, 0, 1, 0xB8 },
    { 2, 0, 1, 0xB9 },
    { 3, 0, 1, 0xBA },
    { 4, 0, 1, 0xBB },
    { 1, 0, 1, 0xBC },
    { 2, 0, 1, 0xBD },
    { 2, 0, 1, 0xBE },
    { 1, 0, 1, 0xBF },
    { 1, 0, 1, 0xC0 },
    { 1, 0, 1, 0xC1 },
    { 1, 0, 1, 0xC2 },
    { 1, 0, 0, 0xC3 },
};

union AnimationStep D_800D66A4_demo[5] = {
    { 1, 0, 1, 0xC6 },
    { 1, 0, 1, 0xC7 },
    { 1, 0, 1, 0xC8 },
    { 1, 0, 1, 0xC9 },
    { 1, 0, 0, 0xCA },
};

union AnimationStep D_800D66B8_demo[8] = {
    { 1, 0, 1, 0xCB },
    { 1, 0, 1, 0xCC },
    { 1, 0, 1, 0xCD },
    { 1, 0, 1, 0xCE },
    { 1, 0, 1, 0xCF },
    { 1, 0, 1, 0xD0 },
    { 1, 0, 1, 0xD1 },
    { 1, 0, -7, 0xD2 },
};

union AnimationStep D_800D66D8_demo[27] = {
    { 3, 0, 1, 0x05 },
    { 1, 0, 1, 0x08 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x07 },
    { 2, 0, 1, 0x02 },
    { 1, 0, 1, 0x06 },
    { 2, 0, 1, 0x02 },
    { 1, 0, 1, 0x06 },
    { 2, 0, 1, 0x02 },
    { 1, 0, 1, 0x06 },
    { 2, 0, 1, 0x02 },
    { 1, 0, 1, 0x06 },
    { 2, 0, 1, 0x02 },
    { 1, 0, 1, 0x06 },
    { 2, 0, 1, 0x02 },
    { 1, 0, 1, 0x06 },
    { 2, 0, 1, 0x03 },
    { 1, 0, 1, 0x07 },
    { 2, 0, 1, 0x04 },
    { 1, 0, 1, 0x08 },
    { 14, 0, 1, 0x04 },
    { 3, 0, 1, 0x03 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x01 },
    { 19, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep* D_800D6744_demo[38] = {
    D_800D5EA4_demo,
    D_800D5EA8_demo,
    D_800D5EE8_demo,
    D_800D5F28_demo,
    D_800D5F4C_demo,
    D_800D5F50_demo,
    D_800D5FBC_demo,
    D_800D66D8_demo,
    D_800D6030_demo,
    D_800D6034_demo,
    D_800D60B0_demo,
    D_800D612C_demo,
    D_800D6154_demo,
    D_800D61C8_demo,
    D_800D6218_demo,
    D_800D621C_demo,
    D_800D624C_demo,
    D_800D6258_demo,
    D_800D630C_demo,
    D_800D6310_demo,
    D_800D6378_demo,
    D_800D6384_demo,
    D_800D6398_demo,
    D_800D63B4_demo,
    D_800D6428_demo,
    D_800D64D4_demo,
    D_800D6500_demo,
    D_800D652C_demo,
    D_800D6574_demo,
    D_800D6594_demo,
    D_800D65C0_demo,
    D_800D65EC_demo,
    D_800D6618_demo,
    D_800D6638_demo,
    D_800D664C_demo,
    D_800D666C_demo,
    D_800D66A4_demo,
    D_800D66B8_demo,
};

void (*D_800D67DC_demo[2])(struct MainObj*) = {
    enemy_hit_reaction,
    ride_armor_pilot_despawn_idle,
};

void (*spike_crawler_state_funcs[3])(struct MainObj*) = {
    ride_armor_pilot_stub,
    general_slam_land,
    general_slam,
};

extern void (*spike_crawler_state_funcs[])(struct MainObj*);
#else
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
#endif
