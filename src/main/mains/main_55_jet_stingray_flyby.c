// MainObj, main_object_update_funcs[55]
// 8006EB40..8006FABC
#include "common.h"
#include "func_tables.h"

// jet_stingray_flyby_init
INCLUDE_ASM("main/nonmatchings/mains/main_55_jet_stingray_flyby", func_8006EB40);

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
INCLUDE_ASM("main/nonmatchings/mains/main_55_jet_stingray_flyby", func_8006ED44);

// jet_stingray_flyby_enter_aimed
INCLUDE_ASM("main/nonmatchings/mains/main_55_jet_stingray_flyby", func_8006EF28);

void jet_stingray_flyby_enter(struct MainObj* self)
{
    jet_stingray_flyby_enter_funcs[self->unk2](self);
}

// jet_stingray_flyby_cruise
INCLUDE_ASM("main/nonmatchings/mains/main_55_jet_stingray_flyby", func_8006F0DC);

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
INCLUDE_ASM("main/nonmatchings/mains/main_55_jet_stingray_flyby", func_8006F5F4);

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
INCLUDE_ASM("main/nonmatchings/mains/main_55_jet_stingray_flyby", func_8006F86C);

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
    { 0x11010002 },
    { 0x17010008 },
    { 0x0E010003 },
    { 0x09000002 },
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
    { 0x21010002 },
    { 0x22000002 },
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
    { 0x2B010002 },
    { 0x2C000002 },
};

union AnimationStep jet_stingray_flyby_anim_9[] = {
    { 0x2D010002 },
    { 0x2E000002 },
};

union AnimationStep jet_stingray_flyby_anim_10[] = {
    { 0x2F000001 },
};

union AnimationStep jet_stingray_flyby_anim_11[] = {
    { 0x30000001 },
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
