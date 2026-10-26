// MainObj, main_object_update_funcs[31]
// 8005B894..8005C824
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_31_thorn_trap.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/misc/misc_02_rubble.h"
#include "main/objects.h"
#include "main/visuals/visual_03_small_effect.h"
#include "main/object_motion.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/object_motion.h"
#endif

extern struct Unk_unk68 thorn_trap_open_hurt_box[];

extern struct Unk_unk68 thorn_trap_strike_boxes[];
extern struct Unk_unk68 D_800FD9F8[];
extern struct Unk_unk68 D_800FD9FC[];
extern struct Unk_unk68 D_800FDA00[];
extern struct Unk_unk68 D_800FDA04[];
extern struct Unk_unk68 D_800FDA08[];

void thorn_trap_despawn(struct MainObj*);

// thorn_trap_step_funcs
void thorn_trap_idle(struct MainObj* arg0);

void thorn_trap_windup(struct MainObj* arg0);
void thorn_trap_strike(struct MainObj* arg0);
void thorn_trap_extend(struct MainObj* arg0);

void thorn_trap_extend_high(struct MainObj* arg0);

extern void (*thorn_trap_state_funcs[])(struct MainObj*);

extern union AnimationStep* thorn_trap_animations[21];
extern s8 D_800FDC40[8];

void thorn_trap_update(struct MainObj* self)
{
    thorn_trap_state_funcs[self->state](self);
}

// thorn_trap_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005B8D0(struct MainObj* self);
void func_8005BA2C(struct MainObj* self);
void func_8005BDE4(struct MainObj* self);
void func_8005BFC0(struct MainObj* self);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_31_thorn_trap", func_8005B8D0);
#else
void func_8005B8D0(struct MainObj* self)
{
    s32 variant;

    self->active |= 4;
    self->state++;
    self->unk5 = 2;
    self->bg_offset = g_Player.bg_offset;
    if (!(self->unk2 & 1)) {
        self->x_pos.val = background_objects[0].x_pos.val - 0x6C0000;
        self->unk15 = 0;
    } else {
        self->x_pos.val = background_objects[0].x_pos.val + 0x1AC0000;
        self->unk15 = PLAYER_FACING_RIGHT;
    }
    variant = ((s8)self->unk2 >> 1) % 3;
    self->animation_table = (const u8* const*)thorn_trap_animations;
    self->unk16 = 0x21;
    self->terrain_box = NULL;
    self->hurt_box = NULL;
    self->attack_box = thorn_trap_attack_box;
    self->hp = 6;
    self->contact_damage = 6;
    self->invincibility_timer = 0;
    self->unk62 = 0;
    self->air_state = 0;
    self->unk7C = 0x96;
    ((u8*)&self->ext)[2] = 0;
    if (variant == 0)
        *(s16*)&self->ext = 0x60;
    else if (variant == 1)
        *(s16*)&self->ext = 0x80;
    else
        *(s16*)&self->ext = 0xB0;
    set_animation(self, 1);
    update_on_screen(BASE_OBJECT(self), 0x70, 0x30);
}
#endif

void thorn_trap_idle(struct MainObj* self)
{
}

// thorn_trap_wait
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_31_thorn_trap", func_8005BA2C);
#else
void func_8005BA2C(struct MainObj* self)
{
    s32 step;
    s32 x;
    s32 pos;

    if (self->unk7C != 0) {
        self->unk7C--;
        return;
    }
    step = self->ext.main_31.distance;
    if (step < 0) {
        if (self->unk2 < 6) {
            set_animation(self, 2);
            self->unk5 = 4;
        } else if (self->unk2 < 0xC) {
            if (self->ext.main_31.unk82 != 0) {
                self->unk5 = 7;
                set_animation(self, 7);
            } else {
                self->unk5 = 6;
                set_animation(self, 3);
            }
        } else if (self->ext.main_31.unk82 != 0) {
            self->unk5 = 9;
            set_animation(self, 4);
        } else {
            self->unk5 = 8;
            set_animation(self, 3);
        }
        return;
    }
    x = self->x_pos.i.hi;
    if (self->unk15 != 0) {
        if (step > 8)
            step = 8;
        pos = x - step;
    } else {
        if (step > 8)
            step = 8;
        pos = x + step;
    }
    self->x_pos.i.hi = pos;
    self->ext.main_31.distance -= 8;
    animate_object(ANIMATED_OBJECT(self));
}
#endif

void thorn_trap_open(struct MainObj* self)
{
    s8 object_variant;

    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 2);
        object_variant = self->unk2;
        if (object_variant < 6) {
            self->unk5 = 4;
            return;
        }
        if (object_variant < 0xC) {
            if (self->ext.main_0.flags[0] != 0) {
                self->unk5 = 7;
                set_animation(self, 7);
                return;
            }
            self->unk5 = 6;
        } else {
            if (self->ext.main_0.flags[0] != 0) {
                self->unk5 = 9;
                set_animation(self, 4);
                return;
            }
            self->unk5 = 8;
        }
        set_animation(self, 3);
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void thorn_trap_windup(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 9);
        self->unk5 = 5;
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
}

void thorn_trap_strike(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->contact_damage = 9;
        self->attack_box = &thorn_trap_strike_boxes;
        func_8002D9BC(self);
        self->attack_box = &D_800FD9F8;
        func_8002D9BC(self);
        self->attack_box = &D_800FD9FC;
        func_8002D9BC(self);
        self->attack_box = &D_800FDA00;
        func_8002D9BC(self);
        self->attack_box = &D_800FDA04;
        func_8002D9BC(self);
        self->attack_box = &D_800FDA08;
        func_8002D9BC(self);
        self->contact_damage = 6;
        self->attack_box = &thorn_trap_attack_box;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void thorn_trap_extend(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->hurt_box = (const u8*)&thorn_trap_open_hurt_box;
        self->ext.main_0.flags[0] = 1;
        self->animation_step.fields.event = 0;
    }
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 7);
        self->unk5 = 7;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

// thorn_trap_extended
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_31_thorn_trap", func_8005BDE4);
#else
void func_8005BDE4(struct MainObj* self)
{
    u8 choice;
    struct ShotObj* shot;

    if (self->animation_step.fields.event != 0) {
        if (self->unk2 > 9)
            choice = (u8)get_random_nonzero() % 3;
        else
            choice = (u8)get_random_nonzero() % 2;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x11;
            shot->unk7C = (struct WeaponObj*)self;
            shot->state = 0;
            shot->unk5 = 0;
            shot->unk6 = 0;
            shot->x_pos.val = self->x_pos.val + (self->unk15 != 0 ? -(D_800FDC40[choice * 2] << 16) : D_800FDC40[choice * 2] << 16);
            shot->y_pos.val = self->y_pos.val + (D_800FDC40[choice * 2 + 1] << 16);
            shot->unk2 = 0;
            self->animation_step.fields.event = 0;
        }
    }
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 0);
        self->unk5 = 3;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}
#endif

void thorn_trap_extend_high(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->hurt_box = (const u8*)&thorn_trap_open_hurt_box;
        self->ext.main_0.flags[0] = 1;
        self->animation_step.fields.event = 0;
    }
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 4);
        self->unk5 = 9;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

// thorn_trap_extended_high
void func_8005BFC0(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        struct ShotObj* shot;
        s32 direction;

        get_random_nonzero();
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x11;
            shot->unk7C = (struct WeaponObj*)self;
            shot->state = 0;
            shot->x_pos.val = self->x_pos.val + (self->unk15 ? -0x540000 : 0x540000);
            shot->y_pos.val = self->y_pos.val - 0x20000;
            shot->unk2 = 1;
            shot->unk6 = angle_to_object(OBJECT_HEADER(shot), OBJECT_HEADER(&g_Player));
            direction = shot->unk6;
            if (self->unk15)
                direction += self->animation_step.fields.event + 1;
            else
                direction -= self->animation_step.fields.event - 1;
            shot->unk6 = direction & 0x1F;
            self->animation_step.fields.event = 0;
        }
    }
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 0);
        self->unk5 = 3;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

// thorn_trap_main
void func_8005C0E4(struct MainObj* self)
{
    u8 health;
    u8 secondary_health;
    const void* saved_bounds;
    s16 x;

    self->collision_data = D_801071F4;
    self->unk65 = self->ext.main_31.unk83;

    if (func_8002DD04(self) < 0) {
        self->unk5 = 0;
        self->state++;
        self->unk42 &= 0x7FFF;
        update_on_screen(BASE_OBJECT(self), 0x70, 0x30);
        return;
    }

    health = self->unk65;
    secondary_health = self->ext.main_31.unk84;
    saved_bounds = self->hurt_box;
    self->collision_data = D_801060F0;
    self->hurt_box = D_800FDA0C;

    self->ext.main_31.unk83 = health;
    self->unk65 = secondary_health;
    func_8002DD04(self);
    self->hurt_box = saved_bounds;
    self->ext.main_31.unk84 = self->unk65;

    thorn_trap_step_funcs[self->unk5](self);

    if ((self->y_pos.val - background_objects[self->bg_offset].y_pos.val) > FIXED(168)) {
        x = self->x_pos.val >> 16;
        self->state++;
        self->unk5 = 0;

        spawn_explosion_at(0, self->unk15 != 0 ? x - 0x47 : x + 0x47, self->y_pos.u.hi + 1, 0);

        x = self->x_pos.val >> 16;
        spawn_explosion_at(0, self->unk15 == 0 ? x + 0x28 : x - 0x28, self->y_pos.i.hi, 1);

        x = self->x_pos.val >> 16;
        spawn_explosion_at(0, self->unk15 == 0 ? x + 0xC : x - 0xC, self->y_pos.u.hi - 1, 0xFF);

        x = self->x_pos.val >> 16;
        spawn_explosion_at(0, self->unk15 == 0 ? x - 0x15 : x + 0x15, self->y_pos.u.hi + 2, 0xFF);

        x = self->x_pos.val >> 16;
        spawn_explosion_at(0, self->unk15 == 0 ? x - 0x33 : x + 0x33, self->y_pos.u.hi - 1, 0xFF);

        x = self->x_pos.val >> 16;
        spawn_explosion_at(0, self->unk15 == 0 ? x - 0x50 : x + 0x50, self->y_pos.i.hi, 0xFF);

        spawn_debris_offset(5, D_800FDC28, self,
            self->unk15 != 0 ? FIXED(-71) : FIXED(71), FIXED(1));

        spawn_debris_offset(1, D_800FDC30, self,
            self->unk15 != 0 ? FIXED(-40) : FIXED(40), 0);

        spawn_debris_offset(1, D_800FDC34, self,
            self->unk15 != 0 ? FIXED(-12) : FIXED(12), FIXED(-1));

        spawn_debris_offset(1, D_800FDC38, self,
            self->unk15 != 0 ? FIXED(21) : FIXED(-21), FIXED(2));

        spawn_debris_offset(1, D_800FDC3C, self,
            self->unk15 != 0 ? FIXED(51) : FIXED(-51), FIXED(-1));
    }

    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x70, 0x30);
        return;
    }
    despawn_object(OBJECT_HEADER(self));
}

// thorn_trap_break
void func_8005C474(struct MainObj* self)
{
    u8 health;
    const void* saved_bounds;
    s16 x;

    if (self->unk5 == 0) {
        self->unk5++;

        x = self->x_pos.val >> 16;
        spawn_explosion_at(0, self->unk15 == 0 ? x + 0x4D : x - 0x4D, self->y_pos.i.hi, 1);

        spawn_debris_offset(5, D_800FDC28, self,
            self->unk15 != 0 ? FIXED(-77) : FIXED(77), 0);

        set_animation(self, 0xB);
    }

    if ((self->y_pos.val - background_objects[self->bg_offset].y_pos.val) > FIXED(168)) {
        self->state++;

        x = self->x_pos.val >> 16;
        spawn_explosion_at(0, self->unk15 == 0 ? x + 0x47 : x - 0x47, self->y_pos.u.hi + 1, 0);

        x = self->x_pos.val >> 16;
        spawn_explosion_at(0, self->unk15 == 0 ? x + 0x28 : x - 0x28, self->y_pos.i.hi, 1);

        x = self->x_pos.val >> 16;
        spawn_explosion_at(0, self->unk15 == 0 ? x + 0xC : x - 0xC, self->y_pos.u.hi - 1, 0xFF);

        x = self->x_pos.val >> 16;
        spawn_explosion_at(0, self->unk15 == 0 ? x - 0x15 : x + 0x15, self->y_pos.u.hi + 2, 0xFF);

        x = self->x_pos.val >> 16;
        spawn_explosion_at(0, self->unk15 == 0 ? x - 0x33 : x + 0x33, self->y_pos.u.hi - 1, 0xFF);

        x = self->x_pos.val >> 16;
        spawn_explosion_at(0, self->unk15 == 0 ? x - 0x50 : x + 0x50, self->y_pos.i.hi, 0xFF);

        spawn_debris_offset(5, D_800FDC28, self,
            self->unk15 != 0 ? FIXED(-71) : FIXED(71), FIXED(1));

        spawn_debris_offset(1, D_800FDC30, self,
            self->unk15 != 0 ? FIXED(-40) : FIXED(40), 0);

        spawn_debris_offset(1, D_800FDC34, self,
            self->unk15 != 0 ? FIXED(-12) : FIXED(12), FIXED(-1));

        spawn_debris_offset(1, D_800FDC38, self,
            self->unk15 != 0 ? FIXED(21) : FIXED(-21), FIXED(2));

        spawn_debris_offset(1, D_800FDC3C, self,
            self->unk15 != 0 ? FIXED(51) : FIXED(-51), FIXED(-1));
    }

    health = self->ext.main_31.unk83;
    saved_bounds = self->hurt_box;
    self->collision_data = D_801060F0;
    self->hurt_box = D_800FDA0C;
    self->unk65 = health;
    func_8002DD04(self);
    self->hurt_box = saved_bounds;
    self->ext.main_31.unk84 = self->unk65;

    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x70, 0x30);
        return;
    }
    despawn_object(OBJECT_HEADER(self));
}

void thorn_trap_despawn(struct MainObj* self)
{
    despawn_object_permanently(OBJECT_HEADER(self));
}

struct Unk_unk68 thorn_trap_open_hurt_box[] = {
    { 58, -27, 0x18, 0x33 },
};

struct Unk_unk68 thorn_trap_attack_box[] = {
    { -105, -16, 0xC0, 0x1F },
};

struct Unk_unk68 thorn_trap_strike_boxes[] = {
    { -95, 15, 7, 0x15 },
};

struct Unk_unk68 D_800FD9F8[] = {
    { -59, -44, 7, 0x18 },
};

struct Unk_unk68 D_800FD9FC[] = {
    { -16, -28, 7, 0xF },
};

struct Unk_unk68 D_800FDA00[] = {
    { -20, -15, 7, 0x11 },
};

struct Unk_unk68 D_800FDA04[] = {
    { 23, 12, 7, 0x13 },
};

struct Unk_unk68 D_800FDA08[] = {
    { 48, -36, 7, 0x13 },
};

struct Unk_unk68 D_800FDA0C[] = {
    { -105, -15, 0xB3, 0x1C },
};

union AnimationStep thorn_trap_anim_0[] = {
    { 1, 0, 1, 0x0D },
    { 1, 0, -1, 0x0D },
    { 13, 0, 1, 0x01 },
    { 13, 0, 1, 0x02 },
    { 16, 0, 1, 0x03 },
    { 16, 0, 1, 0x04 },
    { 16, 0, 1, 0x05 },
    { 16, 0, 1, 0x06 },
    { 15, 0, 1, 0x07 },
    { 1, 0, -7, 0x07 },
};

union AnimationStep thorn_trap_anim_1[] = {
    { 4, 0, 1, 0x02 },
    { 4, 0, 1, 0x03 },
    { 4, 0, 1, 0x04 },
    { 4, 0, 1, 0x05 },
    { 4, 0, 1, 0x06 },
    { 3, 0, 1, 0x07 },
    { 1, 0, -6, 0x07 },
};

union AnimationStep thorn_trap_anim_2[] = {
    { 4, 0, 1, 0x02 },
    { 4, 0, 1, 0x03 },
    { 4, 0, 1, 0x04 },
    { 4, 0, 1, 0x05 },
    { 4, 0, 1, 0x06 },
    { 4, 0, 1, 0x07 },
    { 4, 0, 1, 0x02 },
    { 3, 0, 1, 0x00 },
    { 1, 0, -8, 0x00 },
};

union AnimationStep thorn_trap_anim_3[] = {
    { 8, 0, 1, 0x08 },
    { 8, 0, 1, 0x09 },
    { 8, 1, 1, 0x0A },
    { 8, 0, 1, 0x0B },
    { 8, 0, 1, 0x0C },
    { 15, 0, 1, 0x0D },
    { 6, 0, 1, 0x0E },
    { 7, 0, 1, 0x0F },
    { 6, 0, 1, 0x0E },
    { 4, 0, 1, 0x0D },
    { 1, 0, -1, 0x0D },
};

union AnimationStep thorn_trap_anim_4[] = {
    { 5, 0, 1, 0x0D },
    { 5, 0, 1, 0x10 },
    { 5, 0, 1, 0x11 },
    { 9, 0, 1, 0x12 },
    { 5, 0, 1, 0x2C },
    { 10, 1, 1, 0x2D },
    { 10, 3, 1, 0x2D },
    { 6, 5, 1, 0x2D },
    { 5, 0, 1, 0x2C },
    { 9, 0, 1, 0x12 },
    { 5, 0, 1, 0x11 },
    { 5, 0, 1, 0x10 },
    { 4, 0, 1, 0x0D },
    { 1, 0, -11, 0x0D },
};

union AnimationStep thorn_trap_anim_5[] = {
    { 4, 0, 1, 0x14 },
    { 4, 0, 1, 0x15 },
    { 4, 0, 1, 0x16 },
    { 4, 0, 1, 0x17 },
    { 4, 0, 1, 0x18 },
    { 4, 1, 1, 0x19 },
    { 4, 0, 1, 0x1A },
    { 3, 0, 1, 0x1B },
    { 1, 0, -8, 0x1B },
};

union AnimationStep thorn_trap_anim_6[] = {
    { 3, 0, 1, 0x1C },
    { 1, 0, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 3, 0, 1, 0x1F },
    { 4, 0, 1, 0x20 },
    { 3, 0, 1, 0x1F },
    { 101, 0, 1, 0x1E },
    { 3, 0, 1, 0x1F },
    { 3, 0, 1, 0x20 },
    { 3, 0, 1, 0x1F },
    { 3, 0, 1, 0x20 },
    { 3, 0, 1, 0x1F },
    { 3, 0, 1, 0x20 },
    { 1, 0, 0, 0x20 },
};

union AnimationStep thorn_trap_anim_7[] = {
    { 5, 0, 1, 0x0D },
    { 6, 0, 1, 0x2E },
    { 7, 0, 1, 0x2F },
    { 6, 1, 1, 0x2E },
    { 7, 0, 1, 0x2F },
    { 6, 1, 1, 0x2E },
    { 7, 0, 1, 0x2F },
    { 6, 1, 1, 0x2E },
    { 7, 0, 1, 0x2F },
    { 6, 1, 1, 0x2E },
    { 4, 0, 1, 0x0D },
    { 1, 0, -11, 0x0D },
};

union AnimationStep thorn_trap_anim_8[] = {
    { 2, 0, 1, 0x21 },
    { 2, 0, 1, 0x22 },
    { 2, 0, 1, 0x23 },
    { 2, 0, 1, 0x24 },
    { 2, 0, 1, 0x25 },
    { 1, 0, 1, 0x26 },
    { 1, 0, -6, 0x26 },
};

union AnimationStep thorn_trap_anim_9[] = {
    { 1, 0, 1, 0x00 },
    { 5, 0, 1, 0x30 },
    { 4, 0, 1, 0x31 },
    { 2, 0, 1, 0x32 },
    { 1, 1, 0, 0x32 },
};

union AnimationStep thorn_trap_anim_10[] = {
    { 1, 0, 1, 0x32 },
    { 4, 0, 1, 0x31 },
    { 5, 0, 1, 0x30 },
    { 3, 0, 1, 0x31 },
    { 1, 0, 0, 0x31 },
};

union AnimationStep thorn_trap_anim_11[] = {
    { 1, 0, 0, 0x13 },
};

union AnimationStep thorn_trap_anim_12[] = {
    { 1, 0, 0, 0x27 },
};

union AnimationStep thorn_trap_anim_13[] = {
    { 1, 0, 0, 0x28 },
};

union AnimationStep thorn_trap_anim_14[] = {
    { 1, 0, 0, 0x29 },
};

union AnimationStep thorn_trap_anim_15[] = {
    { 1, 0, 0, 0x2A },
};

union AnimationStep thorn_trap_anim_16[] = {
    { 1, 0, 0, 0x2B },
};

union AnimationStep thorn_trap_anim_17[] = {
    { 1, 0, 0, 0x33 },
};

union AnimationStep thorn_trap_anim_18[] = {
    { 1, 0, 0, 0x34 },
};

union AnimationStep thorn_trap_anim_19[] = {
    { 1, 0, 0, 0x35 },
};

union AnimationStep thorn_trap_anim_20[] = {
    { 1, 0, 0, 0x36 },
};

union AnimationStep* thorn_trap_animations[] = {
    thorn_trap_anim_0,
    thorn_trap_anim_1,
    thorn_trap_anim_2,
    thorn_trap_anim_3,
    thorn_trap_anim_4,
    thorn_trap_anim_5,
    thorn_trap_anim_6,
    thorn_trap_anim_7,
    thorn_trap_anim_8,
    thorn_trap_anim_9,
    thorn_trap_anim_10,
    thorn_trap_anim_11,
    thorn_trap_anim_12,
    thorn_trap_anim_13,
    thorn_trap_anim_14,
    thorn_trap_anim_15,
    thorn_trap_anim_16,
    thorn_trap_anim_17,
    thorn_trap_anim_18,
    thorn_trap_anim_19,
    thorn_trap_anim_20,
};

u8 D_800FDC28[] = {
    0x0C,
    0x0D,
    0x0E,
    0x0F,
    0x10,
    0x00,
    0x00,
    0x00,
};

u8 D_800FDC30[] = {
    0x11,
    0x00,
    0x00,
    0x00,
};

u8 D_800FDC34[] = {
    0x12,
    0x00,
    0x00,
    0x00,
};

u8 D_800FDC38[] = {
    0x13,
    0x00,
    0x00,
    0x00,
};

u8 D_800FDC3C[] = {
    0x14,
    0x00,
    0x00,
    0x00,
};

s8 D_800FDC40[8] = {
    54,
    -2,
    19,
    -9,
    -14,
    7,
    0,
    0,
};

void (*thorn_trap_state_funcs[])(struct MainObj*) = {
    func_8005B8D0,
    func_8005C0E4,
    func_8005C474,
    thorn_trap_despawn,
};

void (*thorn_trap_step_funcs[10])() = {
    enemy_hit_reaction,
    thorn_trap_idle,
    func_8005BA2C,
    thorn_trap_open,
    thorn_trap_windup,
    thorn_trap_strike,
    thorn_trap_extend,
    func_8005BDE4,
    thorn_trap_extend_high,
    func_8005BFC0,
};
