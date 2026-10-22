// MainObj, main_object_update_funcs[2]
// 80042914..80043340
#include "common.h"
#include "main/mains/main_02_item_carrier.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"
#include "main/objects.h"

#ifdef MMX4_PC
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
#ifdef MMX4_PC
void func_80042950(struct MainObj* arg0);
void func_80042AFC(struct MainObj* arg0);
extern struct Unk_unk68* item_carrier_part_hurtboxes[2];
extern u8* item_carrier_part_debris[2];
extern u8 item_carrier_part_debris_counts[4];
extern void (*item_carrier_action_funcs[])(struct MainObj*);
#endif

#ifdef MMX4_PC
void func_80042950(struct MainObj* arg0)
{
    u8* ext = (u8*)&arg0->ext;
    u8 weapon;
    s32 flags;

    arg0->active = (u8)arg0->active | 4;
    weapon = (u8)g_Player.weapon;
    flags = 0;
    if (((s8)engine_obj.max_hp / 2) >= g_Player.hp) {
        flags = 1;
        ext[0] = 1;
    }
    if (engine_obj.cur_character == 0) {
        if (weapon != 0 && g_Player.weapon_energy[weapon] < 0x19) {
            flags |= 2;
            ext[0] = 3;
        }
    }
    if ((flags & 0xFF) == 0) {
        despawn_object(OBJECT_HEADER(arg0));
        return;
    }
    if ((flags & 0xFF) == 3) {
        ext[0] = g_Player.weapon_energy[weapon] >= g_Player.hp ? 1 : 3;
    }
    arg0->state = (u8)arg0->state + 1;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_02_item_carrier", func_80042950);
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
    self->unk15 = (g_Player.x_pos.val >= self->x_pos.val) << 6;
    self->animation_table = (const u8* const*)item_carrier_animations;
    self->unk16 = 4;
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
#ifdef MMX4_PC
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
            self->unk15 = 0x40;
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
    { 0x00010005 },
    { 0x01010005 },
    { 0x02010005 },
    { 0x01010005 },
    { 0x00010005 },
    { 0x03FB0005 },
};

union AnimationStep item_carrier_anim_1[] = {
    { 0x04010005 },
    { 0x05010005 },
    { 0x06010005 },
    { 0x07010005 },
    { 0x08010005 },
    { 0x09010004 },
    { 0x09000001 },
};

union AnimationStep item_carrier_anim_2[] = {
    { 0x09010005 },
    { 0x08010005 },
    { 0x07010005 },
    { 0x06010005 },
    { 0x05010005 },
    { 0x04010004 },
    { 0x04000001 },
};

union AnimationStep item_carrier_anim_3[] = {
    { 0x0A010005 },
    { 0x0B010005 },
    { 0x0C010005 },
    { 0x0B010005 },
    { 0x0A010005 },
    { 0x0DFB0005 },
};

union AnimationStep item_carrier_anim_4[] = {
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010002 },
    { 0x15F90002 },
};

union AnimationStep item_carrier_anim_5[] = {
    { 0x16010003 },
    { 0x17010003 },
    { 0x18010003 },
    { 0x19010003 },
    { 0x1A010003 },
    { 0x1BFB0003 },
};

union AnimationStep item_carrier_anim_6[] = { { 0x1C000001 } };

union AnimationStep item_carrier_anim_7[] = { { 0x1D000001 } };

union AnimationStep item_carrier_anim_8[] = {
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x20010002 },
    { 0x21010002 },
    { 0x22010002 },
    { 0x23010002 },
    { 0x24010002 },
    { 0x25010002 },
    { 0x26010002 },
    { 0x27010002 },
    { 0x28010002 },
    { 0x29F50002 },
};

union AnimationStep item_carrier_anim_9[] = { { 0x2A000001 } };

union AnimationStep item_carrier_anim_10[] = { { 0x2B000001 } };

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
