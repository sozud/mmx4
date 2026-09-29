// MainObj, main_object_update_funcs[71]
// 80089AA4..8008ADFC
#include "common.h"
#include "func_tables.h"

// ride_armor_pilot_init
INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089AA4);

void ride_armor_pilot_spawn_dust(struct VisualObj* self, u8 arg1)
{
    struct VisualObj* obj;
    u8 active;
    u8 unk16;
    u8 unk15;

    obj = find_free_visual_obj();
    if (obj == NULL) {
        return;
    }
    active = self->active;
    obj->id = 0xC;
    obj->unk2 = arg1;
    obj->active = active;
    obj->x_pos.val = self->x_pos.val;
    obj->y_pos.val = self->y_pos.val;
    obj->animation_table = self->animation_table;
    obj->unk40 = self->unk40;
    obj->unk3C = self->unk3C;
    obj->unk42 = self->unk42 & 0x7FFF;
    unk16 = self->unk16;
    obj->unk16 = unk16;
    unk15 = self->unk15;
    obj->unk50 = (struct PlayerObj*)self;
    obj->unk15 = unk15;
}

s32 ride_armor_pilot_update_facing(struct MainObj* self)
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
INCLUDE_ASM("main/nonmatchings/mains/main_71", func_80089C7C);

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
    self->hurt_box = ride_armor_pilot_hurt_box;
    self->attack_box = ride_armor_pilot_attack_box;
    self->unk6 = 0;
    self->ext.main_71.unk88 = 0;
    self->ext.main_71.unk86 = 0;
    self->ext.main_71.unk87 = 0;
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
INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A064);

// ride_armor_pilot_walk
INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A180);

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
INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A3B0);

// ride_armor_pilot_land
INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A4D8);

// ride_armor_pilot_jump_punch
INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A60C);

// ride_armor_pilot_dash
INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A778);

// ride_armor_pilot_dash_end
INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A8E4);

// ride_armor_pilot_guard
INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008A9F4);

// ride_armor_pilot_fall
INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008AAF4);

void ride_armor_pilot_reset(struct MainObj* self)
{
    ride_armor_pilot_return_to_idle(self);
}

// ride_armor_pilot_main
INCLUDE_ASM("main/nonmatchings/mains/main_71", func_8008AC40);

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

struct Unk_unk68 ride_armor_pilot_anim_0[13] = {
    { 100, 0, 1, 0 },
    { 7, 0, 1, 11 },
    { 1, 1, 1, 12 },
    { 49, 0, 1, 12 },
    { 8, 0, -4, 11 },
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
    &ride_armor_pilot_anim_0[5],
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
