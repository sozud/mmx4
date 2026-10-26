// MainObj, main_object_update_funcs[2]
// 80042914..80043340
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_02_item_carrier.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/objects.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#endif

void item_carrier_hide(struct MainObj* arg0);
void item_carrier_despawn(struct MainObj* arg0);

// item_carrier_action_funcs
void item_carrier_approach(struct MainObj* arg0);
void item_carrier_hover(struct MainObj* arg0);

void item_carrier_leave(struct MainObj* arg0);

// item_carrier_approach_funcs
void item_carrier_approach_start(struct MainObj* arg0);
void item_carrier_approach_fly(struct MainObj*);
void item_carrier_approach_stop(struct MainObj*);

// item_carrier_hover_funcs
extern void (*item_carrier_hover_funcs[])(struct MainObj*);
void item_carrier_hover_start(struct MainObj* arg0);
void item_carrier_hover_bob(struct MainObj* arg0);

void item_carrier_drop_rise(struct MainObj* arg0);

void item_carrier_drop_landed(struct MainObj* arg0);

// item_carrier_leave_funcs
void item_carrier_leave_start(struct MainObj*);

void item_carrier_leave_side(struct MainObj* arg0);

// item_carrier_leave_side_funcs
void item_carrier_leave_side_start(struct MainObj*);
void item_carrier_leave_side_turn(struct MainObj*);
void item_carrier_leave_side_fly(struct MainObj*);

extern void (*item_carrier_state_funcs[])(struct MainObj*);
extern void (*item_carrier_approach_funcs[])(struct MainObj*);
extern void (*item_carrier_drop_funcs[])(struct MainObj*);
extern void (*item_carrier_leave_funcs[])(struct MainObj*);
extern void (*item_carrier_leave_side_funcs[])(struct MainObj*);

extern struct Unk_unk68 item_carrier_hitboxes;
extern struct Unk_unk68 item_carrier_capsule_hurtbox;
extern u8 item_carrier_debris[];
extern u8 item_carrier_capsule_debris[];

void item_carrier_update(struct MainObj* self)
{
    item_carrier_state_funcs[self->state](self);
}

// item_carrier_check_needed
#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80042950(struct MainObj* arg0);
void func_80042AFC(struct MainObj* arg0);
extern struct Unk_unk68* item_carrier_part_hurtboxes[2];
extern u8* item_carrier_part_debris[2];
extern u8 item_carrier_part_debris_counts[4];
extern void (*item_carrier_action_funcs[])(struct MainObj*);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_02_item_carrier", func_80042950);
#else
#define HD_MODE(o) (((u8*)&(o)->ext)[0])
void func_80042950(struct MainObj* arg0)
{
    struct PlayerObj* player = &g_Player;
    u8 weapon;
    u8 flags;

    arg0->active |= 4;
    weapon = player->weapon;
    flags = 0;
    if (player->hp <= (s8)engine_obj.max_hp / 2) {
        flags = 1;
        HD_MODE(arg0) = 1;
    }
    if (engine_obj.cur_character == 0 && weapon != 0 && player->weapon_energy[weapon] <= 0x18) {
        flags |= 2;
        HD_MODE(arg0) = 3;
    }
    if (flags != 0) {
        if (flags == 3) {
            if (player->hp <= player->weapon_energy[weapon])
                HD_MODE(arg0) = 1;
            else
                HD_MODE(arg0) = 3;
        }
        arg0->state++;
    } else {
        despawn_object(OBJECT_HEADER(arg0));
    }
}
#endif

// item_carrier_init
void func_80042A48(struct MainObj* self)
{
    self->unk5 = 0;
    self->unk2 = 0;
    self->state++;
    self->bg_offset = g_Player.bg_offset;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->unk15 = (g_Player.x_pos.val >= self->x_pos.val) << PLAYER_FACING_SHIFT;
    self->animation_table = (const u8* const*)item_carrier_animations;
    self->unk16 = VISUAL_SATURN_LAYER(4);
    self->hp = 1;
    self->contact_damage = 1;
    self->attack_box = NULL;
    self->terrain_box = NULL;
    self->collision_data = (const u16*)D_801063F0;
    self->air_state = 0;
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0;
    set_animation(self, 0);
}

// item_carrier_main
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80042AFC(struct MainObj* arg0)
{
    struct ItemObj* item;
    s32 i;

    if (arg0->unk2 == 0) {
        for (i = 0; i < 2; i++) {
            arg0->hurt_box = (const u8*)item_carrier_part_hurtboxes[i];
            if (func_8002DD04(arg0) < 0) {
                spawn_explosion(BASE_OBJECT(arg0));
                spawn_debris(item_carrier_part_debris_counts[i], item_carrier_part_debris[i], arg0);
                if (i == 0) {
                    arg0->unk2 = 2;
                    arg0->unk5 = 2;
                    arg0->unk6 = 0;
                    arg0->hp = 1;
                    break;
                }
                goto spawn_item;
            }
        }
    } else if (func_8002DD04(arg0) < 0) {
        spawn_explosion(BASE_OBJECT(arg0));
        spawn_debris(3, item_carrier_capsule_debris, arg0);
    spawn_item:
        item = find_free_item_obj();
        if (item != NULL) {
            item->active = 0x21;
            item->id = 2;
            item->unk2 = (u8)arg0->ext.main_10.timer;
            item->x_pos.val = arg0->x_pos.val;
            item->y_pos.val = arg0->y_pos.val;
            item->backref = NULL;
            item->bg_offset = arg0->bg_offset;
        }
        arg0->state = (u8)arg0->state + 1;
        return;
    }

    item_carrier_action_funcs[arg0->unk5](arg0);
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
        return;
    }
    arg0->state = (u8)arg0->state + 1;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_02_item_carrier", func_80042AFC);
#endif

void item_carrier_hide(struct MainObj* self)
{
    self->on_screen = 0;
    self->state++;
}

void item_carrier_despawn(struct MainObj* self)
{
    despawn_object_permanently(OBJECT_HEADER(self));
}

void item_carrier_approach(struct MainObj* self)
{
    item_carrier_approach_funcs[self->unk6](self);
}

void item_carrier_approach_start(struct MainObj* self)
{
    self->unk6++;
    self->x_speed = self->unk15 != 0 ? 0x20000 : -0x20000;
    set_animation(self, 0);
}

void item_carrier_approach_fly(struct MainObj* self)
{
    s32 distance;
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (self->x_pos.val - g_Player.x_pos.val < 0) {
        distance = g_Player.x_pos.val - self->x_pos.val;
    } else {
        distance = self->x_pos.val - g_Player.x_pos.val;
    }
    if (distance > FIXED(64)) {
        return;
    }
    self->unk6++;
    self->x_speed = 0;
    set_animation(self, 1);
}

void item_carrier_approach_stop(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 1;
        self->unk6 = 0;
    }
}

void item_carrier_hover(struct MainObj* self)
{
    item_carrier_hover_funcs[self->unk6](self);
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void item_carrier_hover_start(struct MainObj* self)
{
    self->unk6++;
    self->unk7C = 0x12C;
    self->unk7E = 0xA;
    self->x_speed = 0;
    self->y_speed = 0x2000;
    set_animation(self, 3);
}

void item_carrier_hover_bob(struct MainObj* self)
{
    s16 timer;
    s16 countdown;

    timer = self->unk7E;
    if (timer == 0) {
        self->unk7E = 0x14;
        self->y_speed = -self->y_speed;
    } else {
        self->unk7E = timer - 1;
    }
    countdown = --self->unk7C;
    if ((countdown << 0x10) == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void item_carrier_hover_turn(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 0;
        self->unk6 = 0;
        if ((self->x_pos.val - g_Player.x_pos.val) < 0) {
            self->unk15 = PLAYER_FACING_RIGHT;
        } else {
            self->unk15 = 0;
        }
    }
}

void item_carrier_drop(struct MainObj* self)
{
    item_carrier_drop_funcs[self->unk6](self);
}

void item_carrier_drop_start(struct MainObj* self)
{
    self->unk6++;
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = 0x40000;
    self->gravity = 0x4200;
    self->terrain_box = &item_carrier_hitboxes;
    self->hurt_box = &item_carrier_capsule_hurtbox;
    self->attack_box = NULL;
    self->air_state = -1;
    set_animation(self, 4);
    CollisionRelated(PLAYER_OBJECT(self));
    if ((self->collision_flags & 0xF) == 0xF) {
        self->x_pos.val = self->unk18.val;
        self->y_pos.val = self->unk1C.val;
        self->unk6 = 3;
        self->air_state = 0;
    }
}

void item_carrier_drop_rise(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_speed < 0) {
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->unk6++;
    }
    CollisionRelated(PLAYER_OBJECT(self));
}

void item_carrier_drop_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->unk6++;
        self->gravity = 0;
        self->air_state = 0;
        set_animation(self, 4);
    }
    CollisionRelated(PLAYER_OBJECT(self));
}

void item_carrier_drop_landed(struct MainObj* self)
{
}

void item_carrier_leave(struct MainObj* self)
{
    item_carrier_leave_funcs[self->unk6](self);
}

void item_carrier_leave_start(struct MainObj* self)
{
    if ((self->y_pos.val > g_Player.y_pos.val)) {
        self->unk6 = 1;
    } else {
        self->unk6 = 2;
    }
    self->unk7 = 0;
}

void item_carrier_leave_up(struct MainObj* self)
{
    if (self->unk7 == 0) {
        self->unk7++;
        self->x_speed = 0;
        self->y_speed = FIXED(1);
    } else {
        animate_object(ANIMATED_OBJECT(self));
        move_object(MOVING_OBJECT(self));
        if (self->on_screen == 0) {
            self->state++;
        }
    }
}

void item_carrier_leave_side(struct MainObj* self)
{
    item_carrier_leave_side_funcs[self->unk7](self);
}

void item_carrier_leave_side_start(struct MainObj* self)
{
    self->y_speed = 0;
    self->unk7++;
    set_animation(self, 2);
}

void item_carrier_leave_side_turn(struct MainObj* self)
{
    s32 velocity;
    animate_object(ANIMATED_OBJECT(self));
    velocity = FIXED(-2);
    if (self->animation_step.fields.relative_step == 0) {
        self->unk7++;
        if (self->unk15 != 0) {
            velocity = FIXED(2);
        }
        self->y_speed = FIXED(0.14453125);
        self->x_speed = velocity;
        set_animation(self, 0);
        self->unk7C = 0x258;
    }
}

void item_carrier_leave_side_fly(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (self->on_screen == 0) {
        self->state++;
    }
}

struct Unk_unk68 item_carrier_body_box = { -1, -15, 17, 23 };

struct Unk_unk68 item_carrier_hitboxes = { 0, -1, 10, 13 };

struct Unk_unk68 D_800F9B28 = { -18, -9, 34, 17 };

struct Unk_unk68 D_800F9B2C = { -12, -38, 25, 31 };

struct Unk_unk68 D_800F9B30 = { -13, -38, 25, 44 };

struct Unk_unk68 item_carrier_capsule_hurtbox = { -10, -19, 20, 32 };

union AnimationStep item_carrier_anim_0[] = {
    { 5, 0, 1, 0x00 },
    { 5, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 5, 0, 1, 0x01 },
    { 5, 0, 1, 0x00 },
    { 5, 0, -5, 0x03 },
};

union AnimationStep item_carrier_anim_1[] = {
    { 5, 0, 1, 0x04 },
    { 5, 0, 1, 0x05 },
    { 5, 0, 1, 0x06 },
    { 5, 0, 1, 0x07 },
    { 5, 0, 1, 0x08 },
    { 4, 0, 1, 0x09 },
    { 1, 0, 0, 0x09 },
};

union AnimationStep item_carrier_anim_2[] = {
    { 5, 0, 1, 0x09 },
    { 5, 0, 1, 0x08 },
    { 5, 0, 1, 0x07 },
    { 5, 0, 1, 0x06 },
    { 5, 0, 1, 0x05 },
    { 4, 0, 1, 0x04 },
    { 1, 0, 0, 0x04 },
};

union AnimationStep item_carrier_anim_3[] = {
    { 5, 0, 1, 0x0A },
    { 5, 0, 1, 0x0B },
    { 5, 0, 1, 0x0C },
    { 5, 0, 1, 0x0B },
    { 5, 0, 1, 0x0A },
    { 5, 0, -5, 0x0D },
};

union AnimationStep item_carrier_anim_4[] = {
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x13 },
    { 2, 0, 1, 0x14 },
    { 2, 0, -7, 0x15 },
};

union AnimationStep item_carrier_anim_5[] = {
    { 3, 0, 1, 0x16 },
    { 3, 0, 1, 0x17 },
    { 3, 0, 1, 0x18 },
    { 3, 0, 1, 0x19 },
    { 3, 0, 1, 0x1A },
    { 3, 0, -5, 0x1B },
};

union AnimationStep item_carrier_anim_6[] = { { 1, 0, 0, 0x1C } };

union AnimationStep item_carrier_anim_7[] = { { 1, 0, 0, 0x1D } };

union AnimationStep item_carrier_anim_8[] = {
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 2, 0, 1, 0x20 },
    { 2, 0, 1, 0x21 },
    { 2, 0, 1, 0x22 },
    { 2, 0, 1, 0x23 },
    { 2, 0, 1, 0x24 },
    { 2, 0, 1, 0x25 },
    { 2, 0, 1, 0x26 },
    { 2, 0, 1, 0x27 },
    { 2, 0, 1, 0x28 },
    { 2, 0, -11, 0x29 },
};

union AnimationStep item_carrier_anim_9[] = { { 1, 0, 0, 0x2A } };

union AnimationStep item_carrier_anim_10[] = { { 1, 0, 0, 0x2B } };

union AnimationStep* item_carrier_animations[11] = {
    item_carrier_anim_0,
    item_carrier_anim_1,
    item_carrier_anim_2,
    item_carrier_anim_3,
    item_carrier_anim_4,
    item_carrier_anim_5,
    item_carrier_anim_6,
    item_carrier_anim_7,
    item_carrier_anim_8,
    item_carrier_anim_9,
    item_carrier_anim_10,
};

u8 item_carrier_debris[4] = { 5, 6, 7, 0 };

u8 item_carrier_capsule_debris[4] = { 8, 9, 10, 0 };

u8 D_800F9C4C[8] = { 5, 6, 7, 8, 9, 10, 0, 0 };

void (*item_carrier_state_funcs[])(struct MainObj*) = {
    func_80042950,
    func_80042A48,
    func_80042AFC,
    item_carrier_hide,
    item_carrier_despawn,
};

struct Unk_unk68* item_carrier_part_hurtboxes[] = {
    &D_800F9B28,
    &D_800F9B2C,
};

u8* item_carrier_part_debris[] = {
    item_carrier_debris,
    D_800F9C4C,
};

u8 item_carrier_part_debris_counts[] = { 3, 6, 0, 0 };

void (*item_carrier_action_funcs[])() = {
    item_carrier_approach,
    item_carrier_hover,
    item_carrier_drop,
    item_carrier_leave,
};

void (*item_carrier_approach_funcs[])() = {
    item_carrier_approach_start,
    item_carrier_approach_fly,
    item_carrier_approach_stop,
};

void (*item_carrier_hover_funcs[])() = {
    item_carrier_hover_start,
    item_carrier_hover_bob,
    item_carrier_hover_turn,
};

void (*item_carrier_drop_funcs[])() = {
    item_carrier_drop_start,
    item_carrier_drop_rise,
    item_carrier_drop_fall,
    item_carrier_drop_landed,
};

void (*item_carrier_leave_funcs[])() = {
    item_carrier_leave_start,
    item_carrier_leave_up,
    item_carrier_leave_side,
};

void (*item_carrier_leave_side_funcs[])() = {
    item_carrier_leave_side_start,
    item_carrier_leave_side_turn,
    item_carrier_leave_side_fly,
};
