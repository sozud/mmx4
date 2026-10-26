// MainObj, main_object_update_funcs[35]
// 8005EC58..8005F510
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_35_wheel_charger.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/visuals/visual_08_ice_shard.h"

extern struct Unk_unk68 wheel_charger_open_hurt_box;
extern struct Unk_unk68 wheel_charger_open_attack_box;

extern u8 wheel_charger_debris[8];

void wheel_charger_face_player(struct MainObj*);

// wheel_charger_state_funcs
extern void (*wheel_charger_state_funcs[])(struct MainObj*);

void wheel_charger_despawn(struct MainObj* arg0);

// wheel_charger_step_funcs
extern void (*wheel_charger_step_funcs[])(struct MainObj*);

void wheel_charger_drop(struct MainObj* arg0);

void wheel_charger_wait_for_player(struct MainObj* arg0);
void wheel_charger_charge(struct MainObj* arg0);

// wheel_charger_charge_funcs
void wheel_charger_charge_ready(struct MainObj*);
void wheel_charger_charge_open(struct MainObj*);

extern void (*wheel_charger_charge_funcs[])(struct MainObj*);

void wheel_charger_update(struct MainObj* self)
{
    wheel_charger_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

// wheel_charger_init

extern struct Unk_unk68 D_80107374[];
extern union AnimationStep* wheel_charger_animations[9];
extern struct Unk_unk68 D_800FE1B0;
extern struct Unk_unk68 D_800FE1B4;
extern struct Unk_unk68 D_800FE1B8;
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005ECA8(struct MainObj* arg0);
void func_8005EFB0(struct MainObj* arg0);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_35_wheel_charger", func_8005ECA8);
#else
void func_8005ECA8(struct MainObj* arg0)
{
    arg0->hp = 4;
    arg0->contact_damage = 3;
    arg0->invincibility_timer = 0;
    arg0->collision_data = D_80107374;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)wheel_charger_animations;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->terrain_box = &D_800FE1B8;
    arg0->hurt_box = &D_800FE1B0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->attack_box = &D_800FE1B4;
    arg0->unk1C.val = arg0->y_pos.val;
    switch (arg0->unk2) {
    case 0:
        arg0->x_speed = -0x28000;
        arg0->unk15 = 0;
        arg0->ext.main_35.unk80 = 0;
        arg0->unk5 = 2;
        break;
    case 1:
        arg0->unk7A = 1;
        arg0->unk15 = PLAYER_FACING_RIGHT;
        arg0->ext.main_35.unk80 = 0;
        arg0->x_speed = 0x28000;
        arg0->unk5 = 4;
        break;
    case 2:
        arg0->x_speed = -0x28000;
        arg0->unk15 = 0;
        arg0->ext.main_35.unk80 = 1;
        arg0->unk5 = 2;
        break;
    case 3:
        arg0->unk7A = 1;
        arg0->unk15 = PLAYER_FACING_RIGHT;
        arg0->ext.main_35.unk80 = 1;
        arg0->x_speed = 0x28000;
        arg0->unk5 = 4;
        break;
    }
    set_animation(arg0, 0);
    arg0->state = 1;
    arg0->unk6 = 0;
}
#endif

void wheel_charger_main(struct MainObj* self)
{
    s32 hit;

    wheel_charger_check_fall(self);
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    wheel_charger_step_funcs[self->unk5](self);
    if (self->unk5 == 4) {
        return;
    }
    if (engine_obj.stage != 3 || g_Player.x_pos.i.hi <= 0x9B6) {
        func_8002D9BC(self);
    }
    self->ext.main_35.saved_unk5 = self->unk5;
    hit = func_8002DD04(self);
    if (hit < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(5, wheel_charger_debris, self);
        drop_item(BASE_OBJECT(self), 0xC);
        self->state = 2;
    } else if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    } else {
        self->state = 2;
    }
}

void wheel_charger_despawn(struct MainObj* self)
{
    self->unk7A = 0;
    self->ext.main_35.unk80 = 0;
    self->ext.main_35.sound_timer = 0;
    self->ext.main_35.saved_unk5 = 0;
    despawn_object(OBJECT_HEADER(self));
}

void wheel_charger_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_35.saved_unk5;
}

void wheel_charger_drop(struct MainObj* self)
{
    animate_object(self);
    self->y_speed = 0x60000;
    move_object((struct MovingObj*)self);
}

// wheel_charger_fall
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_35_wheel_charger", func_8005EFB0);
#else
void func_8005EFB0(struct MainObj* arg0)
{
    u32 mode;

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->collision_flags & 8) {
        func_8001540C(2, SATURN_SOUND(0x57, 0x47), arg0);
        mode = arg0->ext.main_35.unk80;
        arg0->y_speed = 0;
        arg0->gravity = 0;
        if (mode != 0) {
            if (mode == 1) {
                arg0->ext.main_35.unk80 = 2;
                set_animation(arg0, 1);
                arg0->contact_damage = 4;
                arg0->ext.main_35.sound_timer = 1;
                arg0->unk5 = 5;
            } else {
                if (arg0->unk15 == 0)
                    arg0->x_speed = -0x40000;
                else
                    arg0->x_speed = 0x40000;
                arg0->ext.main_35.sound_timer = 1;
                arg0->unk5 = 5;
                arg0->unk6 = 3;
            }
        } else {
            arg0->unk5 = 2;
        }
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_35.unk80 == 2)
        return;
    if (arg0->unk15 == 0) {
        if (arg0->collision_flags & 2) {
            arg0->unk15 = PLAYER_FACING_RIGHT;
            arg0->x_speed = 0x28000;
        }
    } else if (arg0->collision_flags & 1) {
        arg0->unk15 = 0;
        arg0->x_speed = -0x28000;
    }
}
#endif

void wheel_charger_wait_for_player(struct MainObj* self)
{
    if ((g_Player.x_pos.i.hi - self->x_pos.i.hi) > 0xB4) {
        self->unk7A = 0;
        self->unk5 = 2;
    }
}

void wheel_charger_charge(struct MainObj* self)
{
    wheel_charger_charge_funcs[self->unk6](self);
}

void wheel_charger_charge_ready(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk7C = 10;
        self->unk6 = 1;
    }
}

void wheel_charger_charge_open(struct MainObj* self)
{
    if (self->animation_step.fields.event == 2) {
        self->hurt_box = (const u8*)&wheel_charger_open_hurt_box;
        self->attack_box = (const u8*)&wheel_charger_open_attack_box;
    }
    if (--self->unk7C == 0) {
        wheel_charger_face_player(self);
        set_animation(self, 2);
        self->unk7E = 3;
        self->unk6 = 2;
    }
}

void wheel_charger_charge_spin(struct MainObj* self)
{
    if (--self->ext.main_35.sound_timer == 0) {
        func_8001540C(2, SATURN_SOUND(0x58, 0x48), self);
        self->ext.main_35.sound_timer = 0x14;
    }
    animate_object(ANIMATED_OBJECT(self));
    if (--self->unk7E == 0) {
        func_800B0CA0(1, 2, self, 8, 1);
        self->unk7E = 3;
    }
    if (self->animation_step.fields.event != 0) {
        if (self->unk15 == 0) {
            self->x_speed = FIXED(-4);
            self->unk6 = 3;
        } else {
            self->x_speed = FIXED(4);
            self->unk6 = 3;
        }
    }
}

void wheel_charger_charge_roll(struct MainObj* self)
{
    s32 value;
    u8 mask;

    if (--self->ext.main_35.sound_timer == 0) {
        func_8001540C(2, SATURN_SOUND(0x58, 0x48), self);
        self->ext.main_35.sound_timer = 0x14;
    }

    if (--self->unk7E == 0) {
        func_800B0CA0(1, 2, self, 8, 1);
        self->unk7E = 2;
    }

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));

    mask = 9;
    if (self->unk15 == 0) {
        value = self->collision_flags & 0xA;
        mask = 0xA;
    } else {
        value = self->collision_flags & 9;
    }

    if (value == mask) {
        self->unk7C = 0x3C;
        self->unk5 = 6;
        self->unk6 = 0;
    }
}

void wheel_charger_crash(struct MainObj* self)
{
    if (--self->unk7E == 0) {
        func_800B0CA0(1, 2, self, 8, 1);
        self->unk7E = 2;
    }

    animate_object(ANIMATED_OBJECT(self));

    if (--self->unk7C == 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(5, wheel_charger_debris, self);
        self->state = 2;
    }
}

void wheel_charger_check_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (3 != self->unk5 && self->unk5 != 4) {
        if (!(self->collision_flags & 8)) {
            self->unk5 = 3;
            self->unk6 = 0;
            self->gravity = FIXED(0.234375);
        }
    }
}

void wheel_charger_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
}

struct Unk_unk68 D_800FE1B0 = { -16, -15, 29, 28 };

struct Unk_unk68 D_800FE1B4 = { -12, -11, 22, 20 };

struct Unk_unk68 D_800FE1B8 = { 0, 0, 14, 13 };

struct Unk_unk68 wheel_charger_open_hurt_box = { -16, -2, 29, 15 };

struct Unk_unk68 wheel_charger_open_attack_box = { -13, 0, 23, 11 };

union AnimationStep wheel_charger_anim_0[] = {
    { 1, 0, 1, 0x05 },
    { 1, 0, 1, 0x04 },
    { 1, 0, 1, 0x03 },
    { 1, 0, 1, 0x02 },
    { 1, 0, 1, 0x01 },
    { 1, 0, -5, 0x00 },
};

union AnimationStep wheel_charger_anim_1[] = {
    { 6, 0, 1, 0x00 },
    { 5, 0, 1, 0x06 },
    { 4, 0, 1, 0x07 },
    { 3, 2, 1, 0x08 },
    { 3, 0, 1, 0x09 },
    { 3, 0, 1, 0x0A },
    { 3, 0, 1, 0x0B },
    { 3, 0, 1, 0x0C },
    { 3, 0, 1, 0x0E },
    { 4, 0, 1, 0x0D },
    { 5, 0, 1, 0x0C },
    { 1, 1, 0, 0x0E },
};

union AnimationStep wheel_charger_anim_2[] = {
    { 1, 0, 1, 0x0E },
    { 2, 0, 1, 0x14 },
    { 3, 0, 1, 0x15 },
    { 4, 0, 1, 0x1B },
    { 3, 0, 1, 0x15 },
    { 2, 0, 1, 0x14 },
    { 14, 0, 1, 0x0E },
    { 3, 0, 1, 0x0F },
    { 3, 0, 1, 0x10 },
    { 3, 0, 1, 0x11 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 2, 1, 1, 0x13 },
    { 1, 0, 1, 0x0E },
    { 1, 0, 1, 0x0F },
    { 1, 0, 1, 0x10 },
    { 1, 0, 1, 0x11 },
    { 1, 0, 1, 0x12 },
    { 1, 0, -5, 0x13 },
};

union AnimationStep wheel_charger_anim_4[] = {
    { 1, 1, 0, 0x16 },
};

union AnimationStep wheel_charger_anim_5[] = {
    { 1, 1, 0, 0x17 },
};

union AnimationStep wheel_charger_anim_6[] = {
    { 1, 1, 0, 0x18 },
};

union AnimationStep wheel_charger_anim_7[] = {
    { 1, 1, 0, 0x19 },
};

union AnimationStep wheel_charger_anim_8[] = {
    { 1, 1, 0, 0x1A },
};

union AnimationStep* wheel_charger_animations[9] = {
    wheel_charger_anim_0,
    wheel_charger_anim_1,
    wheel_charger_anim_2,
    &wheel_charger_anim_2[18],
    wheel_charger_anim_4,
    wheel_charger_anim_5,
    wheel_charger_anim_6,
    wheel_charger_anim_7,
    wheel_charger_anim_8,
};

u8 wheel_charger_debris[8] = { 4, 5, 6, 7, 8, 0, 0, 0 };

void (*wheel_charger_state_funcs[3])() = {
    func_8005ECA8,
    wheel_charger_main,
    wheel_charger_despawn,
};

void (*wheel_charger_step_funcs[7])() = {
    enemy_hit_reaction,
    wheel_charger_resume_step,
    wheel_charger_drop,
    func_8005EFB0,
    wheel_charger_wait_for_player,
    wheel_charger_charge,
    wheel_charger_crash,
};

void (*wheel_charger_charge_funcs[4])() = {
    wheel_charger_charge_ready,
    wheel_charger_charge_open,
    wheel_charger_charge_spin,
    wheel_charger_charge_roll,
};
