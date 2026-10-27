// MainObj, main_object_update_funcs[55]
// 8006EB40..8006FABC
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_55_jet_stingray_flyby.h"
#include "main/mains/main_56_jet_stingray.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/visuals/visual_03_small_effect.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/visuals/visual_03_small_effect.h"
#endif

// jet_stingray_flyby_enter_funcs
extern void (*jet_stingray_flyby_enter_funcs[])(struct MainObj*);

// jet_stingray_flyby_attack_funcs
extern void (*jet_stingray_flyby_attack_funcs[])(struct MainObj*);

// jet_stingray_flyby_charge_funcs
extern void (*jet_stingray_flyby_charge_funcs[])(struct MainObj*);

// jet_stingray_flyby_step_funcs
extern void (*jet_stingray_flyby_step_funcs[])(struct MainObj*);

// jet_stingray_flyby_init

extern struct AnimationTable12 jet_stingray_flyby_animations;
extern struct Unk_unk68 jet_stingray_flyby_attack_box;
extern struct Unk_unk68 jet_stingray_flyby_hurt_box;
extern struct Unk_unk68 D_80107978[];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006EB40(struct MainObj* self);
void func_8006ED44(struct MainObj* self);
void func_8006EF28(struct MainObj* self);
void func_8006F0DC(struct MainObj* self);
void func_8006F5F4(struct MainObj* self);
void func_8006F86C(struct MainObj* self);
extern s16 jet_stingray_flyby_explosion_offsets[16];
extern ret_u8 func_8002938C(s32);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_55_jet_stingray_flyby", func_8006EB40);
#else
void func_8006EB40(struct MainObj* self)
{
    if (engine_obj.palette_flags & 0x10) {
        self->state = 2;
        return;
    }
    self->on_screen = 1;
    self->state = 1;
    self->unk5 = 2;
    self->bg_offset = g_Player.bg_offset;
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->unk15 = PLAYER_FACING_RIGHT;
    self->contact_damage = 6;
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0;
    self->animation_table = (const u8* const*)&jet_stingray_flyby_animations;
    self->hp = 0x20;
    self->terrain_box = NULL;
    self->attack_box = &jet_stingray_flyby_attack_box;
    self->hurt_box = &jet_stingray_flyby_hurt_box;
    self->collision_data = D_80107978;
    self->y_pos = g_Player.y_pos;
    if (self->unk2 != 0) {
        self->y_pos = g_Player.y_pos;
        self->x_pos.val = background_objects[self->bg_offset].x_pos.val - 0x400000;
        self->x_speed = 0x90000;
    } else {
        self->y_pos.val = background_objects[self->bg_offset].y_pos.val + 0x400000;
        self->x_pos.val = background_objects[self->bg_offset].x_pos.val + 0x1B00000;
        self->x_speed = 0x40000;
        self->ext.main_55.unk84 = 0;
    }
    set_animation(self, 0);
}
#endif

void jet_stingray_flyby_wait_on_screen(struct MainObj* self)
{
    s32 distance;
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    distance = self->x_pos.val - background_objects[self->bg_offset].x_pos.val;
    if (distance > FIXED(48) && distance < FIXED(272)) {
        self->unk5 = 1;
    }
}

// jet_stingray_flyby_enter_straight
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_55_jet_stingray_flyby", func_8006ED44);
#else
void func_8006ED44(struct MainObj* self)
{
    u8 bit;

    switch (self->ext.main_55.unk84) {
    case 0:
        self->ext.main_55.unk84 = 1;
        self->ext.main_55.unk87 = 0;
        self->unk5 = 5;
        self->unk6 = 0;
        self->unk7 = 0;
        self->unk7C = 0;
        break;
    case 1:
        if (self->ext.main_55.unk85 == 0)
            self->ext.main_55.unk84 = 3;
        if (self->unk7C == 0xF0 || self->ext.main_55.unk85 < 5) {
            self->ext.main_55.unk87 = 1;
            self->ext.main_55.unk84 = 2;
            self->unk7C = 20;
        } else {
            self->unk7C = (s16)((u16)self->unk7C + 1);
        }
        break;
    case 2:
        if (self->unk7C == 0) {
            if (self->ext.main_55.unk88 == 0)
                self->ext.main_55.unk84 = 3;
            for (bit = 0; bit < 8; bit++) {
                if ((self->ext.main_55.unk88 >> bit) & 1) {
                    self->ext.main_55.unk88 &= ~(1 << bit);
                    self->unk7C = 30;
                    break;
                }
            }
        } else {
            self->unk7C = (s16)((u16)self->unk7C - 1);
        }
        break;
    case 3:
        self->ext.main_55.unk84 = 0;
        self->unk5 = 4;
        self->unk6 = 0;
        self->unk7 = 0;
        break;
    }
    animate_object(ANIMATED_OBJECT(self));
    self->x_speed = (s32)background_objects[(s8)self->bg_offset].unk47 * FIXED(1);
    self->y_speed = 0;
    move_object(MOVING_OBJECT(self));
    if (self->x_pos.i.hi >= 0x1E16) {
        self->unk5 = 6;
        self->unk6 = 0;
        self->x_speed = FIXED(8);
    }
}
#endif

// jet_stingray_flyby_enter_aimed
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_55_jet_stingray_flyby", func_8006EF28);
#else
void func_8006EF28(struct MainObj* self)
{
    s16 dx;
    s16 dy;

    if (self->unk6 == 0) {
        self->unk6++;
        self->unk7C = 0x5A;
    }
    animate_object(ANIMATED_OBJECT(self));
    set_velocity_from_angle(MOVING_OBJECT(self), (u8)angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)));
    self->x_speed = (s32)background_objects[self->bg_offset].unk47 * FIXED(1);
    move_object(MOVING_OBJECT(self));
    dx = (u16)g_Player.x_pos.i.hi - (u16)self->x_pos.i.hi;
    dy = g_Player.y_pos.i.hi - self->y_pos.i.hi;
    if (dx < 0x50 && (dy < 0 ? -dy : dy) < 0x20 && (u32)(get_random() & 0xF) < 3) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
    if (self->unk7C == 0) {
        self->unk5 = 4;
        self->unk6 = 0;
        self->y_speed = FIXED(2);
    } else {
        self->unk7C = (u16)self->unk7C - 1;
    }
    if (self->x_pos.i.hi >= 0x390F) {
        self->x_speed = FIXED(4);
        self->unk5 = 6;
        self->unk6 = 0;
    }
}
#endif

void jet_stingray_flyby_enter(struct MainObj* self)
{
    jet_stingray_flyby_enter_funcs[self->unk2](self);
}

// jet_stingray_flyby_cruise
void func_8006F0DC(struct MainObj* self)
{
    switch (self->unk6) {
    case 0:
        self->unk6++;
        self->x_speed = FIXED(11);
        self->y_speed = 0;
        self->unk7C = 30;
        set_animation(self, 1);

    case 1:
        if (self->unk7C != 0) {
            move_object(MOVING_OBJECT(self));
            self->unk7C = (u16)self->unk7C - 1;
        } else {
            self->x_speed = FIXED(4);
            self->unk7C = 30;
            self->unk6++;
            self->ext.main_55.distance = self->x_pos.val - background_objects[self->bg_offset].x_pos.val;
            set_animation(self, 0);
        }
        break;
    case 2:
        if (self->x_pos.val < (s32)((u32)background_objects[self->bg_offset].x_pos.val + FIXED(48))) {
            self->unk5 = 1;
            self->unk6 = 0;
        } else {
            move_object(MOVING_OBJECT(self));
        }
        break;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void jet_stingray_flyby_attack_rise(struct MainObj* self)
{
    if (self->unk2 == 1) {
        if (self->y_pos.val < background_objects[self->bg_offset].y_pos.val + FIXED(64)) {
            self->unk6 = (u8)self->unk6 + 1;
            self->y_speed = 0;
            set_animation(self, 2);
            self->unk7C = 0;
            self->unk7E = 4;
        }
    } else {
        self->unk6 = (u8)self->unk6 + 1;
        self->unk7C = 0;
        self->unk7E = 4;
        set_animation(self, 2);
    }
    animate_object(ANIMATED_OBJECT(self));
}

void jet_stingray_flyby_attack_fire(struct MainObj* self)
{
    s16 timer = self->unk7C;
    u32** animation_table;
    struct ShotObj* shot;

    if (timer == 0) {
        if (self->animation_step.fields.event == 1) {
            self->animation_step.fields.event = 0;
            shot = find_free_shot_obj();
            if (shot != 0) {
                shot->active = 0x41;
                shot->id = 0x22;
                shot->unk40 = self->unk40;
                shot->unk42 = self->unk42;
                shot->unk3C = ANIMATED_OBJECT(self)->unk3C;
                shot->bg_offset = self->bg_offset;
                shot->x_pos.val = self->x_pos.val;
                shot->y_pos.val = self->y_pos.val;
                shot->animation_table = (ANIMATED_OBJECT(self)->animation_table);
                shot->unk7C = WEAPON_OBJECT(self);
                shot->unk2 = 0;
            }
        }
        if (self->animation_step.fields.event == 2) {
            self->animation_step.fields.event = 0;
            self->unk7C = 10;
            if (--self->unk7E == 0) {
                self->unk6++;
                set_animation(self, 3);
            }
        }
        animate_object(ANIMATED_OBJECT(self));
    } else {
        self->unk7C = timer - 1;
    }
}

void jet_stingray_flyby_attack_end(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 0);
        if (self->unk2 == 1) {
            self->y_speed = FIXED(-2);
            self->unk6++;
        } else {
            self->unk5 = 1;
            self->unk6 = 0;
            self->unk7 = 0;
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void jet_stingray_flyby_attack_align(struct MainObj* self)
{
    if (ABS(g_Player.y_pos.val, self->y_pos.val) < 0x100000) {
        self->unk5 = 1;
        self->unk6 = 0;
    }
    animate_object(self);
}

void jet_stingray_flyby_attack(struct MainObj* self)
{
    jet_stingray_flyby_attack_funcs[self->unk6](self);
    self->x_speed = background_objects[self->bg_offset].unk47 << 0x10;
    move_object(MOVING_OBJECT(self));
}

void jet_stingray_flyby_charge_windup(struct MainObj* self)
{
    if (self->unk7 == 0) {
        self->unk7++;
        set_animation(self, 4);
    }
    if (self->animation_step.fields.event != 0) {
        self->unk6++;
        self->unk7 = 0;
        self->unk7C = 0;
        self->ext.main_55.unk85 = 0;
        self->ext.main_55.unk86 = 0;
    }
}

// jet_stingray_flyby_charge_fire
void func_8006F5F4(struct MainObj* self)
{
    struct ShotObj* shot;
    s32 clut_x;
    s32 clut_y;
    u8 index;
    s32 bit;
    u8 count;
    u8 next;
    u8 mask;

    if (self->unk7 == 0) {
        if (self->unk7C == 0) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0x22;
                shot->unk40 = self->unk40;
                clut_x = func_8002938C(0x37);
                clut_y = func_8002938C(0x37);
#ifdef MMX4_SATURN
                shot->unk42 = clut_x * 4 + 0x19;
#else
                shot->unk42 = ((clut_x * 4 + 0x19) % 16) | (((clut_y + 6) / 4 + 0x1E0) << 6);
#endif
                shot->unk3C = ANIMATED_OBJECT(self)->unk3C;
                shot->bg_offset = self->bg_offset;
                shot->x_pos.val = self->x_pos.val;
                shot->y_pos.val = self->y_pos.val;
                shot->animation_table = ANIMATED_OBJECT(self)->animation_table;
                shot->unk7C = WEAPON_OBJECT(self);
                shot->unk15 = self->unk15;
                shot->unk2 = 1;
                index = self->ext.main_55.unk86;
                bit = 1;
                shot->unk8A = index;
                count = self->ext.main_55.unk85 + 1;
                next = self->ext.main_55.unk86 + 1;
                mask = self->ext.main_55.unk88 | (bit << *(volatile u8*)&self->ext.main_55.unk86);
                self->ext.main_55.unk88 = mask;
                self->ext.main_55.unk85 = count;
                self->ext.main_55.unk86 = next;
            }
            if (self->ext.main_55.unk86 == 8) {
                self->unk7++;
                set_animation(self, 5);
            }
            self->unk7C = 7;
            return;
        }
        self->unk7C--;
        return;
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 1;
        self->unk6 = 0;
        self->unk7 = 0;
        set_animation(self, 0);
    }
}

void jet_stingray_flyby_charge(struct MainObj* self)
{
    jet_stingray_flyby_charge_funcs[self->unk6](self);
    self->x_speed = background_objects[self->bg_offset].unk47 << 0x10;
    animate_object(self);
    move_object(MOVING_OBJECT(self));
}

void jet_stingray_flyby_drift(struct MainObj* self)
{
    animate_object(self);
    move_object(self);
}

// jet_stingray_flyby_destroyed
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8006F86C(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->attack_box = NULL;
        self->hurt_box = NULL;
        self->ext.main_55.unk85 = 60;
        set_animation(self, 0);
    }
    if (self->unk6 == 1) {
        if (self->ext.main_55.unk85 == 0) {
            self->unk6++;
            self->x_speed = self->unk2 == 0 ? FIXED(8) : FIXED(4);
        } else {
            self->ext.main_55.unk85--;
            self->x_speed = (s32)background_objects[self->bg_offset].unk47 * FIXED(1);
        }
    }
    if ((get_random() & 0xFF) % 7 == 0) {
        u8 kind = ((u8)WEAPON_FRAME_COUNTER ^ 1) & 1;
        s16 x = (u16)self->x_pos.i.hi + (u16)jet_stingray_flyby_explosion_offsets[(get_random() & 7) * 2];
        s16 y = (u16)self->y_pos.i.hi + (u16)jet_stingray_flyby_explosion_offsets[(get_random() & 7) * 2 + 1];
        struct VisualObj* explosion = spawn_explosion_at(0, x, y, kind);
        explosion->unk16 = VISUAL_SATURN_LAYER(5);
    }
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_55_jet_stingray_flyby", func_8006F86C);
#endif

void jet_stingray_flyby_main(struct MainObj* self)
{
    if (func_8002DD04(self) < 0) {
        self->unk5 = 7;
        self->unk6 = 0;
    }

    func_8002D9BC(BASE_OBJECT(self));
    jet_stingray_flyby_step_funcs[self->unk5](self);

    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x60) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x40, 0x30);
    } else {
        self->state = 2;
    }
}

// jet_stingray_spawn_water

struct Unk_unk68 jet_stingray_flyby_attack_box = { -19, -8, 54, 12 };

struct Unk_unk68 jet_stingray_flyby_hurt_box = { -28, -12, 63, 24 };

s16 jet_stingray_flyby_explosion_offsets[16] = {
    (s16)0x000F,
    (s16)0xFFF2,
    (s16)0x0007,
    (s16)0x000E,
    (s16)0xFFF2,
    (s16)0xFFFF,
    (s16)0xFFD8,
    (s16)0xFFF5,
    (s16)0xFFC6,
    (s16)0x0003,
    (s16)0xFFC0,
    (s16)0xFFF0,
    (s16)0xFFEB,
    (s16)0xFFF2,
    (s16)0xFFC8,
    (s16)0x000F,
};

struct Unk_unk68 jet_stingray_flyby_anim_0[16] = {
    { 6, 0, 1, 0 },
    { 5, 0, 1, 1 },
    { 5, 0, 1, 2 },
    { 5, 0, 1, 3 },
    { 5, 0, 1, 4 },
    { 6, 0, 1, 5 },
    { 6, 0, 1, 6 },
    { 6, 0, 1, 7 },
    { 6, 0, 1, 4 },
    { 5, 0, 1, 5 },
    { 5, 0, 1, 2 },
    { 5, 0, 1, 3 },
    { 5, 0, 1, 0 },
    { 6, 0, 1, 1 },
    { 6, 0, 1, 8 },
    { 6, 1, -15, 9 },
};

struct Unk_unk68 jet_stingray_flyby_anim_1[4] = {
    { 2, 0, 1, 10 },
    { 2, 0, 1, 11 },
    { 2, 0, 1, 12 },
    { 2, 0, -3, 13 },
};

struct Unk_unk68 jet_stingray_flyby_anim_2[10] = {
    { 3, 0, 1, 14 },
    { 6, 0, 1, 15 },
    { 7, 0, 1, 16 },
    { 2, 0, 1, 17 },
    { 2, 0, 1, 18 },
    { 8, 0, 1, 19 },
    { 2, 0, 1, 20 },
    { 2, 1, 1, 21 },
    { 2, 0, 1, 20 },
    { 6, 2, -4, 22 },
};

union AnimationStep jet_stingray_flyby_anim_3[] = {
    { 2, 0, 1, 0x11 },
    { 8, 0, 1, 0x17 },
    { 3, 0, 1, 0x0E },
    { 2, 0, 0, 0x09 },
};

struct Unk_unk68 jet_stingray_flyby_anim_4[9] = {
    { 6, 0, 1, 24 },
    { 6, 0, 1, 25 },
    { 4, 0, 1, 26 },
    { 2, 0, 1, 27 },
    { 2, 0, 1, 28 },
    { 6, 0, 1, 29 },
    { 6, 1, 1, 30 },
    { 6, 0, 1, 31 },
    { 6, 0, -2, 32 },
};

union AnimationStep jet_stingray_flyby_anim_5[] = {
    { 2, 0, 1, 0x21 },
    { 2, 0, 0, 0x22 },
};

struct Unk_unk68 jet_stingray_flyby_anim_6[4] = {
    { 2, 0, 1, 35 },
    { 2, 0, 1, 36 },
    { 2, 0, 1, 37 },
    { 2, 0, -3, 38 },
};

struct Unk_unk68 jet_stingray_flyby_anim_7[4] = {
    { 2, 0, 1, 39 },
    { 2, 0, 1, 40 },
    { 2, 0, 1, 41 },
    { 2, 0, -3, 42 },
};

union AnimationStep jet_stingray_flyby_anim_8[] = {
    { 2, 0, 1, 0x2B },
    { 2, 0, 0, 0x2C },
};

union AnimationStep jet_stingray_flyby_anim_9[] = {
    { 2, 0, 1, 0x2D },
    { 2, 0, 0, 0x2E },
};

union AnimationStep jet_stingray_flyby_anim_10[] = {
    { 1, 0, 0, 0x2F },
};

union AnimationStep jet_stingray_flyby_anim_11[] = {
    { 1, 0, 0, 0x30 },
};

struct AnimationTable12 {
    union AnimationStep* entries[12];
    s32 count;
};

struct AnimationTable12 jet_stingray_flyby_animations = {
    {
        jet_stingray_flyby_anim_0,
        jet_stingray_flyby_anim_1,
        jet_stingray_flyby_anim_2,
        jet_stingray_flyby_anim_3,
        jet_stingray_flyby_anim_4,
        jet_stingray_flyby_anim_5,
        jet_stingray_flyby_anim_6,
        jet_stingray_flyby_anim_7,
        jet_stingray_flyby_anim_8,
        jet_stingray_flyby_anim_9,
        jet_stingray_flyby_anim_10,
        jet_stingray_flyby_anim_11,
    },
    0x00000052,
};

void (*jet_stingray_flyby_enter_funcs[2])() = {
    func_8006ED44,
    func_8006EF28,
};

void (*jet_stingray_flyby_attack_funcs[4])(struct MainObj*) = {
    jet_stingray_flyby_attack_rise,
    jet_stingray_flyby_attack_fire,
    jet_stingray_flyby_attack_end,
    jet_stingray_flyby_attack_align,
};

void (*jet_stingray_flyby_charge_funcs[2])(struct MainObj*) = {
    jet_stingray_flyby_charge_windup,
    func_8006F5F4,
};

void (*jet_stingray_flyby_step_funcs[8])(struct MainObj*) = {
    enemy_hit_reaction,
    jet_stingray_flyby_enter,
    jet_stingray_flyby_wait_on_screen,
    func_8006F0DC,
    jet_stingray_flyby_attack,
    jet_stingray_flyby_charge,
    jet_stingray_flyby_drift,
    func_8006F86C,
};

void (*jet_stingray_flyby_state_funcs[3])() = {
    func_8006EB40,
    jet_stingray_flyby_main,
    jet_stingray_flyby_despawn,
};
