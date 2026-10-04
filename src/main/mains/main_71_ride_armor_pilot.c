// MainObj, main_object_update_funcs[71]
// 80089AA4..8008ADFC
#include "common.h"
#include "func_tables.h"

extern void* ride_armor_pilot_animations[31];
extern struct Unk_unk68 ride_armor_pilot_terrain_box;

// ride_armor_pilot_init
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_80089AA4);
#else
void func_80089AA4(struct MainObj* self)
{
    s32 x_pos;
    s32 y_pos;
    s8 damage;

    x_pos = self->x_pos.val;
    y_pos = self->y_pos.val;
    self->state = 1;
    self->unk5 = 2;
    self->on_screen = 1;
    self->hp = 0x18;
    damage = 5;
    do {
    } while (0); // Empty loop: scheduling barrier for perfect match
    self->animation_table = (const u8* const*)ride_armor_pilot_animations;
    self->hurt_box = ride_armor_pilot_hurt_box;
    self->attack_box = ride_armor_pilot_attack_box;
    self->terrain_box = &ride_armor_pilot_terrain_box;
    self->unk6 = 0;
    self->unk7 = 0;
    self->unk7C = 0;
    self->contact_damage = damage;
    self->invincibility_timer = 0;
    self->collision_data = D_80108184;
    self->air_state = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk16 = 5;
    self->ext.main_71.unk8A = 0;
    self->ext.main_71.unk89 = 0;
    self->ext.main_71.unk88 = 0;
    self->ext.main_71.unk87 = 0;
    self->ext.main_71.unk86 = 0;
    self->ext.main_71.unk8D = 0;
    self->unk18.val = x_pos;
    self->unk1C.val = y_pos;
}
#endif

void ride_armor_pilot_spawn_dust(struct VisualObj* self, u8 arg1)
{
    struct VisualObj* obj;

    obj = find_free_visual_obj();
    if (obj == NULL) {
        return;
    }
    obj->active = self->active;
    obj->id = 0xC;
    obj->unk2 = arg1;
    obj->x_pos.val = self->x_pos.val;
    obj->y_pos.val = self->y_pos.val;
    obj->animation_table = self->animation_table;
    obj->unk40 = self->unk40;
    obj->unk3C = self->unk3C;
    obj->unk42 = self->unk42 & 0x7FFF;
    obj->unk16 = self->unk16;
    obj->unk15 = self->unk15;
    obj->unk50 = (struct PlayerObj*)self;
}

u8 ride_armor_pilot_update_facing(struct MainObj* self)
{
    u8 flags;

    if (self->unk2 == 0) {
        flags = self->ext.main_71.unk8A;
        if (flags != 0) {
            if (flags & 1) {
                self->unk15 = 0x40;
            } else {
                self->unk15 = 0;
            }
            return 1;
        }
    } else {
        if ((self->x_pos.i.hi - g_Player.x_pos.i.hi) < 0) {
            self->unk15 = 0x40;
        } else {
            self->unk15 = 0;
        }
    }

    return 0;
}

// ride_armor_pilot_check_walls
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_80089C7C);

void ride_armor_pilot_set_step(struct BaseObj* self, s8 arg1)
{
    self->unk5 = arg1;
    self->unk6 = 0;
}

void ride_armor_pilot_check_dash(struct MainObj* self)
{
    if (self->unk5 < 2) {
        return;
    }
    if (self->unk5 == 6) {
        return;
    }
    if (self->unk5 == 7) {
        return;
    }
    if (self->unk5 == 0xB) {
        return;
    }
    if (self->ext.main_71.unk88 == 0) {
        return;
    }
    if (self->ext.main_71.unk8D & 8) {
        return;
    }
    if (self->air_state != 0) {
        return;
    }
    if (self->ext.main_71.unk86 == 0) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 6);
    }
}

void ride_armor_pilot_return_to_idle(struct MainObj* self)
{
    self->unk5 = 2;
    self->unk6 = 0;
    self->ext.main_71.unk88 = 0;
    self->ext.main_71.unk86 = 0;
    self->ext.main_71.unk87 = 0;
    self->hurt_box = ride_armor_pilot_hurt_box;
    self->attack_box = ride_armor_pilot_attack_box;
    self->contact_damage = 5;
}

void ride_armor_pilot_apply_x_speed(struct MainObj* self)
{
    self->x_pos.val += self->x_speed;
}

void ride_armor_pilot_set_walk_speed(struct MainObj* self)
{
    if (self->unk15 != 0) {
        self->x_speed = FIXED(1.375);
    } else {
        self->x_speed = FIXED(-1.375);
    }
}

void ride_armor_pilot_set_jump_speed(struct MainObj* self)
{
    s32 velocity;

    if (ride_armor_pilot_update_facing(self) & 0xFF) {
        velocity = self->ext.main_71.unk84 << 8;
        if (self->unk15 == 0) {
            velocity = -velocity;
        }
        self->x_speed = velocity;
    }
}

void ride_armor_pilot_set_scripted_speed(struct MainObj* self)
{
    s32 var_v1;
    u8 temp_a1;

    temp_a1 = self->ext.main_71.unk8A;
    if (temp_a1 != 0) {
        var_v1 = self->ext.main_71.unk84 << 8;
        if (!(temp_a1 & 1)) {
            var_v1 = -var_v1;
        }
        self->x_speed = var_v1;
    }
}

void ride_armor_pilot_stub(struct MainObj* self, s32 arg1, s32 arg2)
{
}

// ride_armor_pilot_idle
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_8008A064);

// ride_armor_pilot_walk
void func_8008A180(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        set_animation(self, 1);
        self->ext.main_71.unk84 = 0x160;
        ride_armor_pilot_update_facing(self);
        self->hurt_box = ride_armor_pilot_hurt_box;
        self->attack_box = ride_armor_pilot_attack_box;
        self->contact_damage = 5;
        self->ext.main_71.unk8D &= 0xF3;
    }

    if (!(self->collision_flags & 8)) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
        return;
    }

    if (!(self->ext.main_71.unk8D & 2)) {
        if (!(ride_armor_pilot_update_facing(self) & 0xFF)) {
            ride_armor_pilot_return_to_idle(self);
            return;
        }
        if (self->ext.main_71.unk86 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 8);
            return;
        }
        if (self->ext.main_71.unk87 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 9);
            return;
        }
        ride_armor_pilot_set_walk_speed(self);
        ride_armor_pilot_apply_x_speed(self);
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0) {
            func_8001540C(2, 0x3D, self);
        }
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void ride_armor_pilot_punch(struct MainObj* self)
{
    s8 event;

    if (self->unk6 == 0) {
        self->unk6++;
        set_animation(self, 9);
        ride_armor_pilot_stub(self, 2, 0);
        func_8001540C(2, 0x41, self);
    }

    if (self->animation_step.fields.relative_step == 0) {
        ride_armor_pilot_return_to_idle(self);
        self->ext.main_71.unk87 = 0;
        return;
    }

    event = self->animation_step.fields.event;
    if (event == 1) {
        self->attack_box = &ride_armor_pilot_punch_box;
        self->contact_damage = 6;
    } else if (event == 2) {
        self->attack_box = ride_armor_pilot_attack_box;
        self->contact_damage = 5;
    }

    animate_object(ANIMATED_OBJECT(self));
}

// ride_armor_pilot_jump
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_8008A3B0);

// ride_armor_pilot_land
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_8008A4D8);

// ride_armor_pilot_jump_punch
void func_8008A60C(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6++;
        ride_armor_pilot_stub(self, 0, 1);
        set_animation(self, 0xA);
        func_8001540C(2, 0x41, self);
    }

    if (self->collision_flags & 8) {
        ride_armor_pilot_set_step(BASE_OBJECT(self), 5);
        return;
    }

    if (!(self->ext.main_71.unk8D & 2)) {
        self->x_speed = 0;
        self->x_accel = 0;
        ride_armor_pilot_set_scripted_speed(self);

        if ((self->y_speed >= 0) && (self->collision_flags & 4)) {
            self->y_speed = 0;
        }

        if (self->animation_step.fields.relative_step == 0) {
            s32 state = 8;
            if (self->y_speed < 0) {
                state = 4;
            }
            self->unk5 = state;
        } else {
            s32 fall_speed = FIXED(-5.875);
            if (self->y_speed < fall_speed) {
                self->y_speed = fall_speed;
            }
            move_with_gravity(ANIMATED_OBJECT(self));
        }

        if (self->animation_step.fields.event == 1) {
            self->attack_box = &ride_armor_pilot_punch_box;
            self->contact_damage = 6;
        } else if (self->animation_step.fields.event == 2) {
            self->attack_box = ride_armor_pilot_attack_box;
            self->contact_damage = 5;
        }
    }

    animate_object(ANIMATED_OBJECT(self));
}

// ride_armor_pilot_dash
void func_8008A778(struct MainObj* self)
{
    if (self->unk6 == 0) {
        ride_armor_pilot_update_facing(self);
        self->unk6 = 1;
        self->ext.main_71.unk84 = 0x420;

        if (self->unk15 != 0) {
            self->x_speed = FIXED(4.125);
        } else {
            self->x_speed = FIXED(-4.125);
        }

        self->ext.main_71.unk8E = 0x1E;
        ride_armor_pilot_spawn_dust(VISUAL_OBJECT(self), 5);
        set_animation(self, 5);
        func_8001540C(2, 0x3F, self);
        self->ext.main_71.unk8D |= 4;
    }

    if (!(self->ext.main_71.unk8D & 2)) {
        if (self->ext.main_71.unk86 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 8);
        } else if (self->ext.main_71.unk87 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 0xB);
        } else if (!(self->collision_flags & 8)) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 4);
        } else if (!(self->collision_flags & 3)) {
            ride_armor_pilot_apply_x_speed(self);
            if (self->ext.main_71.unk8E-- < 0) {
                ride_armor_pilot_set_step(BASE_OBJECT(self), 7);
                return;
            }
        } else {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 7);
            return;
        }
    }

    animate_object(ANIMATED_OBJECT(self));
}

// ride_armor_pilot_dash_end
void func_8008A8E4(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        self->ext.main_71.unk84 = 0x160;
        set_animation(self, 6);
        self->hurt_box = ride_armor_pilot_hurt_box;
        self->attack_box = ride_armor_pilot_attack_box;
        self->contact_damage = 5;
        self->ext.main_71.unk8D &= 0xFB;
    }

    if (!(self->ext.main_71.unk8D & 2)) {
        if (self->animation_step.fields.relative_step == 0) {
            ride_armor_pilot_return_to_idle(self);
            return;
        }
        if (self->ext.main_71.unk86 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 8);
            return;
        }
        if (self->ext.main_71.unk87 != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 9);
            return;
        }
        if (self->ext.main_71.unk8A != 0) {
            ride_armor_pilot_set_step(BASE_OBJECT(self), 3);
            return;
        }
    }

    animate_object(ANIMATED_OBJECT(self));
}

// ride_armor_pilot_guard
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_8008A9F4);

// ride_armor_pilot_fall
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_8008AAF4);

void ride_armor_pilot_reset(struct MainObj* self)
{
    ride_armor_pilot_return_to_idle(self);
}

// ride_armor_pilot_main
INCLUDE_ASM("main/nonmatchings/mains/main_71_ride_armor_pilot", func_8008AC40);

void ride_armor_pilot_despawn_remove(struct MainObj* self)
{
    self->unk42 &= 0x7FFF;
    despawn_object(OBJECT_HEADER(self));
}

void ride_armor_pilot_despawn_idle(void)
{
}

void ride_armor_pilot_despawn_idle2(void)
{
}

void ride_armor_pilot_despawn(struct MainObj* self)
{
    ride_armor_pilot_despawn_funcs[self->unk5](self);
}

void ride_armor_pilot_update(struct MainObj* self)
{
    ride_armor_pilot_state_funcs[self->state](self);
}

#ifdef MMX4_WIN32
struct Unk_unk68 ride_armor_pilot_anim_0[5] = {
#else
struct Unk_unk68 ride_armor_pilot_anim_0[13] = {
#endif
    { 100, 0, 1, 0 },
    { 7, 0, 1, 11 },
    { 1, 1, 1, 12 },
    { 49, 0, 1, 12 },
    { 8, 0, -4, 11 },
#ifdef MMX4_WIN32
};

struct Unk_unk68 ride_armor_pilot_anim_1[8] = {
#endif
    { 6, 0, 1, 1 },
    { 6, 1, 1, 2 },
    { 6, 0, 1, 3 },
    { 10, 0, 1, 4 },
    { 6, 0, 1, 5 },
    { 6, 0, 1, 6 },
    { 6, 0, 1, 7 },
    { 10, 0, -8, 8 },
};

union AnimationStep ride_armor_pilot_anim_2[] = {
    { 0x09000006 },
};

union AnimationStep ride_armor_pilot_anim_3[] = {
    { 0x0A000006 },
};

union AnimationStep ride_armor_pilot_anim_4[] = {
    { 0x0B010002 },
    { 0x0C010008 },
    { 0x0B010007 },
    { 0x00000008 },
};

union AnimationStep ride_armor_pilot_anim_5[] = {
    { 0x0D010004 },
    { 0x0E000008 },
};

union AnimationStep ride_armor_pilot_anim_6[] = {
    { 0x0D000004 },
};

union AnimationStep ride_armor_pilot_anim_7[] = {
    { 0x0F010001 },
    { 0x10010001 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x10010003 },
    { 0x0F000006 },
};

u8 ride_armor_pilot_anim_8[16] = { 2, 0, 1, 17, 2, 0, 1, 18, 2, 17, 1, 17, 2, 17, 255, 18 };

union AnimationStep ride_armor_pilot_anim_9[] = {
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x1A010001 },
    { 0x1B010001 },
    { 0x1C010001 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F010001 },
    { 0x20010101 },
    { 0x21010001 },
    { 0x20010001 },
    { 0x21010001 },
    { 0x20010001 },
    { 0x21000010 },
    { 0x12000205 },
    { 0x0F000005 },
};

union AnimationStep ride_armor_pilot_anim_10[] = {
    { 0x09010001 },
    { 0x22010001 },
    { 0x23010001 },
    { 0x24010001 },
    { 0x25010001 },
    { 0x26010001 },
    { 0x27010001 },
    { 0x28010001 },
    { 0x29010001 },
    { 0x28010001 },
    { 0x29010001 },
    { 0x28010001 },
    { 0x29010006 },
    { 0x2A000006 },
    { 0x2B000006 },
};

union AnimationStep ride_armor_pilot_anim_11[] = {
    { 0x16010005 },
    { 0x17000004 },
};

union AnimationStep ride_armor_pilot_anim_12[] = {
    { 0x18010001 },
    { 0x19010001 },
    { 0x1A000001 },
};

union AnimationStep ride_armor_pilot_anim_13[] = {
    { 0x10010001 },
    { 0x12010001 },
    { 0x11000001 },
};

u8 ride_armor_pilot_anim_14[12] = { 1, 0, 1, 17, 1, 0, 1, 20, 1, 0, 255, 21 };

union AnimationStep ride_armor_pilot_anim_15[] = {
    { 0x11010005 },
    { 0x12010002 },
    { 0x0F000002 },
};

union AnimationStep ride_armor_pilot_anim_16[] = {
    { 0x2C010005 },
    { 0x2D010005 },
    { 0x2E010005 },
    { 0x2F010005 },
    { 0x30010005 },
    { 0x31010005 },
    { 0x32010005 },
    { 0x33010005 },
    { 0x34000005 },
};

struct Unk_unk68 ride_armor_pilot_anim_17[12] = {
    { 2, 0, 1, 53 },
    { 2, 0, 1, 54 },
    { 2, 0, 1, 55 },
    { 2, 0, 1, 56 },
    { 2, 0, 1, 57 },
    { 2, 0, 1, 58 },
    { 1, 0, 1, 53 },
    { 1, 0, 1, 54 },
    { 1, 0, 1, 55 },
    { 1, 0, 1, 56 },
    { 1, 0, 1, 57 },
    { 1, 0, -11, 58 },
};

union AnimationStep ride_armor_pilot_anim_24[] = {
    { 0x3B000002 },
};

union AnimationStep ride_armor_pilot_anim_25[] = {
    { 0x3C000002 },
};

union AnimationStep ride_armor_pilot_anim_26[] = {
    { 0x3D000002 },
};

union AnimationStep ride_armor_pilot_anim_27[] = {
    { 0x3E000002 },
};

union AnimationStep ride_armor_pilot_anim_28[] = {
    { 0x3F000002 },
};

union AnimationStep ride_armor_pilot_anim_29[] = {
    { 0x40000002 },
};

union AnimationStep ride_armor_pilot_anim_30[] = {
    { 0x41000002 },
};

struct Unk_unk68 ride_armor_pilot_anim_22[4] = {
    { 1, 0, 1, 66 },
    { 2, 0, 1, 67 },
    { 1, 0, 1, 66 },
    { 2, 0, -3, 67 },
};

struct Unk_unk68 ride_armor_pilot_anim_23[4] = {
    { 1, 0, 1, 68 },
    { 2, 0, 1, 69 },
    { 1, 0, 1, 68 },
    { 2, 0, -3, 69 },
};

void* ride_armor_pilot_animations[31] = {
    ride_armor_pilot_anim_0,
#ifdef MMX4_WIN32
    ride_armor_pilot_anim_1,
#else
    &ride_armor_pilot_anim_0[5],
#endif
    ride_armor_pilot_anim_2,
    ride_armor_pilot_anim_3,
    ride_armor_pilot_anim_4,
    ride_armor_pilot_anim_5,
    ride_armor_pilot_anim_6,
    ride_armor_pilot_anim_7,
    ride_armor_pilot_anim_8,
    ride_armor_pilot_anim_9,
    ride_armor_pilot_anim_10,
    ride_armor_pilot_anim_11,
    ride_armor_pilot_anim_12,
    ride_armor_pilot_anim_13,
    ride_armor_pilot_anim_14,
    ride_armor_pilot_anim_15,
    ride_armor_pilot_anim_16,
    ride_armor_pilot_anim_17,
    ride_armor_pilot_anim_17,
    ride_armor_pilot_anim_17,
    ride_armor_pilot_anim_16,
    ride_armor_pilot_anim_17,
    ride_armor_pilot_anim_22,
    ride_armor_pilot_anim_23,
    ride_armor_pilot_anim_24,
    ride_armor_pilot_anim_25,
    ride_armor_pilot_anim_26,
    ride_armor_pilot_anim_27,
    ride_armor_pilot_anim_28,
    ride_armor_pilot_anim_29,
    ride_armor_pilot_anim_30,
};

u8 ride_armor_pilot_hurt_box[4] = { 0xED, 0xDD, 40, 69 };

u8 ride_armor_pilot_attack_box[4] = { 0xF4, 0xE7, 24, 56 };

struct Unk_unk68 ride_armor_pilot_terrain_box = { 0, -1, 15, 33 };

struct Unk_unk68 ride_armor_pilot_guard_box = { -39, -16, 49, 48 };

struct Unk_unk68 ride_armor_pilot_punch_box = { -55, -47, 65, 77 };

struct Unk_unk68 ride_armor_pilot_debris[2] = {
    { 24, 25, 26, 27 },
    { 28, 29, 30, 0 },
};

void (*ride_armor_pilot_step_funcs[12])() = {
    enemy_hit_reaction,
    ride_armor_pilot_reset,
    func_8008A064,
    func_8008A180,
    func_8008AAF4,
    func_8008A4D8,
    func_8008A778,
    func_8008A8E4,
    func_8008A3B0,
    ride_armor_pilot_punch,
    func_8008A60C,
    func_8008A9F4,
};

void (*ride_armor_pilot_despawn_funcs[3])() = {
    ride_armor_pilot_despawn_remove,
    ride_armor_pilot_despawn_idle,
    ride_armor_pilot_despawn_idle2,
};

void (*ride_armor_pilot_state_funcs[3])() = {
    func_80089AA4,
    func_8008AC40,
    ride_armor_pilot_despawn,
};
