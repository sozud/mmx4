// MainObj, main_object_update_funcs[6]
// 80046B30..800473C8
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_06_bulldozer.h"
#include "main/1CF60.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/visuals/visual_03_small_effect.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/1E1BC.h"
#include "main/visuals/visual_03_small_effect.h"
#endif

// bulldozer_state_funcs
extern void (*bulldozer_state_funcs[])(struct MainObj*);

void bulldozer_cleanup(struct MainObj*);

// bulldozer_step_funcs
void bulldozer_resume_step(struct MainObj* arg0);
void bulldozer_rev(struct MainObj* arg0);
void bulldozer_charge(struct MainObj* arg0);

// bulldozer_rev_funcs
void bulldozer_rev_begin(struct MainObj*);
void bulldozer_rev_wait(struct MainObj*);

// bulldozer_charge_funcs
void bulldozer_charge_start(struct MainObj*);
void bulldozer_charge_move(struct MainObj* arg0);

extern void (*bulldozer_rev_funcs[])(struct MainObj*);
extern void (*bulldozer_charge_funcs[])(struct MainObj*);

void bulldozer_update(struct MainObj* self)
{
    bulldozer_state_funcs[self->state](self);
    CollisionRelated(PLAYER_OBJECT(self));
}

// bulldozer_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
ret_s8 func_8002DD04(struct MainObj* object);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80046B80(struct MainObj* arg0);
void func_80046C8C(struct MainObj* arg0);
extern struct Unk_unk68 D_801065F0[];
extern struct Unk_unk68 bulldozer_terrain_box;
extern struct Unk_unk68 bulldozer_hurt_boxes[2];
extern struct Unk_unk68 D_800FA430;
extern struct Unk_unk68 D_800FA434[2];
extern union AnimationStep* D_800FA4E8[16];
extern u8 bulldozer_debris[16];
extern void (*bulldozer_step_funcs[])(struct MainObj*);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80046B80(struct MainObj* arg0)
{
    arg0->hp = 0x7F;
    arg0->contact_damage = 4;
    arg0->unk7C = 0;
    arg0->invincibility_timer = 0;
    arg0->collision_data = (const u16*)D_801065F0;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : PLAYER_FACING_RIGHT;
    arg0->animation_table = (const u8* const*)D_800FA4E8;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->terrain_box = &bulldozer_terrain_box;
    arg0->hurt_box = (const u8*)bulldozer_hurt_boxes;
    arg0->attack_box = (const u8*)bulldozer_hurt_boxes;
    arg0->ext.main_6.armor_broken = 0;
    arg0->ext.main_6.ground_probe_distance = 0;
    arg0->ext.main_6.armor_health = 0x12;
    arg0->ext.main_6.core_health = 9;
    arg0->ext.main_6.hitbox_toggle = 0;
    arg0->air_state = 0;
    set_animation(arg0, 0);
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->unk6 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_06_bulldozer", func_80046B80);
#endif

// bulldozer_main
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80046C8C(struct MainObj* arg0)
{
    s32 facing_offset;

    bulldozer_check_fall(arg0);
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    bulldozer_step_funcs[arg0->unk5](arg0);

    arg0->hp = 0x7F;
    arg0->ext.main_6.hitbox_toggle ^= 1;
    if (arg0->ext.main_6.hitbox_toggle != 0) {
        arg0->hurt_box = (const u8*)arg0->hurt_box + 4;
        arg0->attack_box = (const u8*)arg0->attack_box + 4;
    } else {
        arg0->hurt_box = (const u8*)arg0->hurt_box - 4;
        arg0->attack_box = (const u8*)arg0->attack_box - 4;
    }
    func_8002D9BC(arg0);
    arg0->ext.main_6.saved_step = arg0->unk5;

    if (func_8002DD04(arg0) != 0) {
        if (arg0->ext.main_6.armor_broken == 0
            && arg0->ext.main_6.hitbox_toggle == 0) {
            arg0->ext.main_6.armor_health
                += arg0->hp - 0x7F;
        } else {
            arg0->ext.main_6.core_health += arg0->hp - 0x7F;
        }

        if ((s32)arg0->ext.main_6.core_health < 0) {
            if (arg0->ext.main_6.armor_broken == 0) {
                facing_offset = arg0->unk15 != 0 ? -0x24 : 0x24;
                spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi, 1);
                spawn_explosion(BASE_OBJECT(arg0));
                facing_offset = arg0->unk15 != 0 ? 0x20 : -0x20;
                spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi, 1);
                facing_offset = arg0->unk15 != 0 ? 0x18 : -0x18;
                spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi - 0x1B, 1);
                spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi - 0x37, 1);
                spawn_debris(0xF, bulldozer_debris, arg0);
            } else {
                spawn_explosion(BASE_OBJECT(arg0));
                facing_offset = arg0->unk15 != 0 ? -0x24 : 0x24;
                spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                    arg0->y_pos.i.hi, 1);
                spawn_debris(8, bulldozer_debris + 7, arg0);
            }
            drop_item(BASE_OBJECT(arg0), 0x13);
            arg0->state = 2;
            return;
        }

        if (arg0->ext.main_6.armor_broken == 0
            && (s32)arg0->ext.main_6.armor_health < 0) {
            facing_offset = arg0->unk15 != 0 ? 0x20 : -0x20;
            spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                arg0->y_pos.i.hi, 1);
            facing_offset = arg0->unk15 != 0 ? 0x18 : -0x18;
            spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                arg0->y_pos.i.hi - 0x1B, 1);
            spawn_explosion_at(0, arg0->x_pos.i.hi + facing_offset,
                arg0->y_pos.i.hi - 0x37, 1);
            spawn_debris(7, bulldozer_debris, arg0);
            set_animation(arg0, 1);
            arg0->contact_damage = 3;
            arg0->terrain_box = &D_800FA430;
            arg0->hurt_box = (const u8*)D_800FA434;
            arg0->attack_box = (const u8*)D_800FA434;
            arg0->unk5 = 2;
            arg0->unk6 = 0;
            arg0->ext.main_6.armor_broken = 1;
        }
    }

    if (func_8002B1E8(BASE_OBJECT(arg0), 0x68, 0x68) != 0) {
        arg0->state = 2;
    } else {
        update_on_screen(BASE_OBJECT(arg0), 0x48, 0x48);
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_06_bulldozer", func_80046C8C);
#endif

void bulldozer_cleanup(struct MainObj* self)
{
    self->ext.main_6.armor_broken = 0;
    self->ext.main_6.ground_probe_distance = 0;
    self->ext.main_6.armor_health = 0;
    self->ext.main_6.core_health = 0;
    self->ext.main_6.hitbox_toggle = 0;
    self->ext.main_6.saved_step = 0;
    despawn_object(OBJECT_HEADER(self));
    STOP_SOUND(2, 2, 0x6);
}

void bulldozer_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_6.saved_step;
}

void bulldozer_rev(struct MainObj* self)
{
    bulldozer_rev_funcs[self->unk6](self);
}

void bulldozer_rev_begin(struct MainObj* self)
{
    if (self->ext.main_6.armor_broken == 0) {
        self->ext.main_6.ground_probe_distance = 0x48;
        set_animation(self, 0);
    } else {
        self->ext.main_6.ground_probe_distance = 8;
        set_animation(self, 1);
    }
    self->unk7C = 0x28;
    self->unk6 = 1;
    animate_object(ANIMATED_OBJECT(self));
    func_8001540C(2, 2, self);
}

void bulldozer_rev_wait(struct MainObj* self)
{
    if (self->unk7C == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    } else {
        self->unk7C--;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void bulldozer_charge(struct MainObj* self)
{
    bulldozer_charge_funcs[self->unk6](self);
}

void bulldozer_charge_start(struct MainObj* self)
{
    if (self->unk15 & PLAYER_FACING_RIGHT) {
        if (self->ext.main_6.armor_broken == 0) {
            self->x_speed = FIXED(0.5);
        } else {
            self->x_speed = FIXED(2);
        }
    } else {
        if (self->ext.main_6.armor_broken == 0) {
            self->x_speed = FIXED(-0.5);
        } else {
            self->x_speed = FIXED(-2);
        }
    }
    self->unk6 = 1;
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
}

void bulldozer_charge_move(struct MainObj* self)
{
    s16 x;
    s16 y;

    if (self->unk15 != 0) {
        x = self->x_pos.u.hi + (s8)(u8)self->terrain_box->unk0 + self->ext.main_6.ground_probe_distance;
    } else {
        x = (self->x_pos.u.hi - (s8)(u8)self->terrain_box->unk0) - self->ext.main_6.ground_probe_distance;
    }

    y = self->terrain_box->unk3 + (self->y_pos.u.hi + (s8)(u8)self->terrain_box->unk1);
    if (func_8002D724(PLAYER_OBJECT(self), x, y) == 0x38) {
        move_object(MOVING_OBJECT(self));
    }
    animate_object(ANIMATED_OBJECT(self));
}

void bulldozer_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->collision_flags & 8) {
        self->unk5 = 2;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = 0;
        self->x_speed = 0;
        self->x_accel = 0;
        self->air_state = 0;
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

void bulldozer_check_fall(struct MainObj* self)
{
    if (self->air_state == 0 && !(self->collision_flags & 8)) {
        self->unk5 = 4;
        self->unk6 = 0;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->x_speed = 0;
        self->x_accel = 0;
        self->air_state = 1;
    }
}

struct Unk_unk68 bulldozer_terrain_box = { 1, -28, 47, 45 };

struct Unk_unk68 bulldozer_hurt_boxes[2] = {
    { -50, -69, 46, 86 },
    { -18, -18, 68, 34 },
};

struct Unk_unk68 D_800FA430 = { -15, -1, 34, 18 };

struct Unk_unk68 D_800FA434[2] = {
    { -18, -18, 68, 34 },
    { -18, -18, 68, 34 },
};

union AnimationStep D_800FA43C[] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 3, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 3, 0, 1, 0x04 },
    { 3, 0, 1, 0x05 },
    { 3, 0, 1, 0x06 },
    { 3, 0, -7, 0x07 },
};

union AnimationStep D_800FA45C[] = {
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, -3, 0x0B },
};

union AnimationStep D_800FA46C[] = {
    { 1, 0, 0, 0x0C },
};

union AnimationStep D_800FA470[] = {
    { 1, 0, 0, 0x0D },
};

union AnimationStep D_800FA474[] = {
    { 1, 0, 0, 0x0E },
};

union AnimationStep D_800FA478[] = {
    { 1, 0, 0, 0x0F },
};

union AnimationStep D_800FA47C[] = {
    { 3, 0, 1, 0x10 },
    { 3, 0, 1, 0x11 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x14 },
    { 3, 0, 1, 0x15 },
    { 3, 0, 1, 0x16 },
    { 3, 0, 1, 0x17 },
    { 3, 0, 1, 0x18 },
    { 3, 0, 1, 0x19 },
    { 3, 0, 1, 0x1A },
    { 3, 0, -11, 0x1B },
};

union AnimationStep D_800FA4AC[] = {
    { 1, 0, 0, 0x1C },
};

union AnimationStep D_800FA4B0[] = {
    { 1, 0, 0, 0x1D },
};

union AnimationStep D_800FA4B4[] = {
    { 1, 0, 0, 0x1E },
};

union AnimationStep D_800FA4B8[] = {
    { 1, 0, 0, 0x1F },
};

union AnimationStep D_800FA4BC[] = {
    { 1, 0, 0, 0x20 },
};

union AnimationStep D_800FA4C0[] = {
    { 1, 0, 0, 0x21 },
};

union AnimationStep D_800FA4C4[] = {
    { 1, 0, 0, 0x22 },
};

union AnimationStep D_800FA4C8[] = {
    { 3, 0, 1, 0x23 },
    { 3, 0, 1, 0x24 },
    { 3, 0, 1, 0x25 },
    { 3, 0, -3, 0x26 },
};

union AnimationStep D_800FA4D8[] = {
    { 3, 0, 1, 0x27 },
    { 3, 0, 1, 0x28 },
    { 3, 0, 1, 0x29 },
    { 3, 0, -3, 0x2A },
};

union AnimationStep* D_800FA4E8[] = {
    D_800FA43C,
    D_800FA45C,
    D_800FA46C,
    D_800FA470,
    D_800FA474,
    D_800FA478,
    D_800FA47C,
    D_800FA4AC,
    D_800FA4B0,
    D_800FA4B4,
    D_800FA4B8,
    D_800FA4BC,
    D_800FA4C0,
    D_800FA4C4,
    D_800FA4C8,
    D_800FA4D8,
};

u8 bulldozer_debris[16] = {
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x0F,
    0x08,
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x0F,
    0x00,
};

void (*bulldozer_state_funcs[])() = {
    func_80046B80,
    func_80046C8C,
    bulldozer_cleanup,
};

void (*bulldozer_step_funcs[])() = {
    enemy_hit_reaction,
    bulldozer_resume_step,
    bulldozer_rev,
    bulldozer_charge,
    bulldozer_fall,
};

void (*bulldozer_rev_funcs[])() = {
    bulldozer_rev_begin,
    bulldozer_rev_wait,
};

void (*bulldozer_charge_funcs[])() = {
    bulldozer_charge_start,
    bulldozer_charge_move,
};
