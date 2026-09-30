// MainObj, main_object_update_funcs[23]
// 80055C54..80056788
#include "common.h"
#include "func_tables.h"

void bee_hive_update(struct MainObj* self);

// bee_hive_init

// bee_hive_main

void bee_hive_despawn(struct MainObj* self);

void bee_hive_resume_step(struct MainObj* self);

void bee_hive_open(struct MainObj* self);

void bee_hive_open_start(struct MainObj* self);

// bee_hive_open_move

void bee_hive_open_end(struct MainObj* self);

void bee_hive_wait(struct MainObj* self);

void bee_hive_wait_start(struct MainObj* self);

void bee_hive_wait_watch(struct MainObj* self);

void bee_hive_release(struct MainObj* self);

void bee_hive_release_start(struct MainObj* self);

void func_800559BC(struct MainObj*);

void bee_hive_release_wait(struct MainObj* self);

void bee_hive_release_pause(struct MainObj* self);

void bee_hive_shake(struct MainObj* self);

void bee_hive_shake_start(struct MainObj* self);

void bee_hive_shake_end(struct MainObj* self);

void bee_hive_explode(struct MainObj* self);

void bee_hive_explode_start(struct MainObj* self);

void bee_hive_explode_smoke(struct MainObj* self);

void bee_hive_explode_done(void);

// bee_hive_spawn_bees

void slope_skier_read_slope(struct MainObj* self)
{
    struct Unk_unk68* collision;
    s16 x_pos;
    s32 y_pos;
    u8 result;

    self->ext.main_23.unk81 = self->ext.main_23.unk80;
    x_pos = self->x_pos.i.hi;
    collision = self->terrain_box;
    y_pos = (s16)(collision->unk3
        + ((u16)self->y_pos.i.hi + (s8)(u8)collision->unk1) + 1);

    result = func_8002D724(PLAYER_OBJECT(self), x_pos, y_pos);
    if (result == 0) {
        result = ((s32(*)(struct PlayerObj*, s16, s32))func_8002D724)(
            PLAYER_OBJECT(self), x_pos, y_pos + 0x10);
        if (result == 0) {
            self->ext.main_23.unk80 = 3;
            return;
        }
    }

    if (result > 0x10 && result <= 0x1E) {
        if (result >= 0x19) {
            self->ext.main_23.unk80 = 2;
            if (result >= 0x1B) {
                if (self->unk15 == 0)
                    self->ext.main_23.unk80 = 0x82;
            } else if (self->unk15 != 0) {
                self->ext.main_23.unk80 = 0x82;
            }
        } else {
            self->ext.main_23.unk80 = 1;
            if (result >= 0x15) {
                if (self->unk15 == 0)
                    self->ext.main_23.unk80 = 0x81;
            } else if (self->unk15 != 0) {
                self->ext.main_23.unk80 = 0x81;
            }
        }
    } else if (result == 0x3E) {
        if (self->on_screen != 0) {
            spawn_explosion(BASE_OBJECT(self));
            spawn_debris(7, slope_skier_debris, self);
            self->state = (u8)self->state + 1;
        }
    } else if (result != 0x10) {
        self->ext.main_23.unk80 = 0;
    }
}

void slope_skier_land(struct MainObj* self)
{
    s8 step;
    u8 background_relative;
    u8 background_offset;

    step = self->unk6;
    if (step == 0) {
        self->unk6 = step + 1;
        slope_skier_read_slope(self);
        background_relative = self->ext.main_23.unk80;
        background_offset = background_relative & 0x7F;
        if (background_relative & 0x80) {
            self->unk15 ^= 0x40;
        }
        set_animation(self, background_offset + 0x12);
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk5 = 1;
        self->unk6 = 0;
    }
}

void slope_skier_fall(struct MainObj* self)
{
    s8 step;

    animate_object(ANIMATED_OBJECT(self));
    step = self->unk6;
    if (step == 0) {
        self->unk6 = step + 1;
        self->gravity = FIXED(0.2578125);
        self->y_speed = 0;
        self->air_state = -1;
    }
    if (self->collision_flags & 8) {
        self->unk5 = 3;
        self->unk6 = 0;
        self->air_state = 0;
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

// slope_skier_jump_start
INCLUDE_ASM("main/nonmatchings/mains/main_23_slope_skier", func_80055F1C);

void slope_skier_jump_rise(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_speed < 0) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void slope_skier_jump(struct MainObj* self)
{
    slope_skier_jump_funcs[self->unk6](self);
}

// slope_skier_step_5
INCLUDE_ASM("main/nonmatchings/mains/main_23_slope_skier", func_80056054);

void slope_skier_slide_start(struct MainObj* self)
{
    s32 velocity;

    self->unk6++;
    slope_skier_read_slope(self);
    velocity = FIXED(-4.5);
    if (self->unk15 != 0) {
        velocity = FIXED(4.5);
    }
    self->x_speed = velocity;
    set_animation(self, (self->ext.main_23.unk80 & 0x7F) + 4);
    func_8001540C(2, 0x3A, self);
}

// slope_skier_slide_move
INCLUDE_ASM("main/nonmatchings/mains/main_23_slope_skier", func_800562AC);

void slope_skier_slide_idle(void)
{
}

void slope_skier_slide(struct MainObj* self)
{
    slope_skier_slide_funcs[self->unk6](self);
}

// slope_skier_init
INCLUDE_ASM("main/nonmatchings/mains/main_23_slope_skier", func_800564B4);

void slope_skier_wait_for_player(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi - self->x_pos.i.hi > 0xC0) {
        self->unk5 = 1;
    }
}

void slope_skier_main(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    if (self->air_state == 0 && !(self->collision_flags & 8)) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(7, slope_skier_debris, self);
        drop_item(BASE_OBJECT(self), 0x16);
    } else {
        func_8002D9BC(self);
        slope_skier_step_funcs[self->unk5](self);
        if (func_8002B1E8(BASE_OBJECT(self), 0x60, 0x40) == 0) {
            update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
            return;
        }
    }
    self->state = (u8)self->state + 1;
}

void slope_skier_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void slope_skier_update(struct MainObj* self)
{
    slope_skier_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

struct Unk_unk68 slope_skier_hurt_box[] = {
    { 0, 12, 16, 2 },
};

struct Unk_unk68 slope_skier_terrain_box = { -11, -16, 21, 29 };

struct Unk_unk68 D_800FCB50 = { 3, 3, 3, 0 };

union AnimationStep slope_skier_anim_0[] = {
    { 0x06000001 },
};

union AnimationStep slope_skier_anim_1[] = {
    { 0x07010003 },
    { 0x08010003 },
    { 0x09010003 },
    { 0x0A010009 },
    { 0x09010003 },
    { 0x08010003 },
    { 0x01000003 },
};

union AnimationStep slope_skier_anim_2[] = {
    { 0x07010003 },
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0F010009 },
    { 0x0E010003 },
    { 0x0D010003 },
    { 0x03000003 },
};

union AnimationStep slope_skier_anim_3[] = {
    { 0x07010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x14010009 },
    { 0x13010003 },
    { 0x12010003 },
    { 0x05000003 },
};

union AnimationStep slope_skier_anim_4[] = {
    { 0x00010003 },
    { 0x01FF0003 },
};

union AnimationStep slope_skier_anim_5[] = {
    { 0x02010003 },
    { 0x03FF0003 },
};

union AnimationStep slope_skier_anim_6[] = {
    { 0x04010003 },
    { 0x05FF0003 },
};

union AnimationStep slope_skier_anim_7[] = {
    { 0x08010003 },
    { 0x09010003 },
    { 0x0A01000F },
    { 0x09010003 },
    { 0x08010003 },
    { 0x0B010003 },
    { 0x0C000003 },
};

union AnimationStep slope_skier_anim_8[] = {
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0F01000F },
    { 0x0E010003 },
    { 0x0D010003 },
    { 0x10010003 },
    { 0x11000003 },
};

union AnimationStep slope_skier_anim_9[] = {
    { 0x12010003 },
    { 0x13010003 },
    { 0x1401000F },
    { 0x13010003 },
    { 0x12010003 },
    { 0x15010003 },
    { 0x16000003 },
};

union AnimationStep slope_skier_anim_13[] = {
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A010002 },
    { 0x09010002 },
    { 0x08000001 },
};

union AnimationStep slope_skier_anim_14[] = {
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0F01000C },
    { 0x0E010003 },
    { 0x08000003 },
};

union AnimationStep slope_skier_anim_15[] = {
    { 0x12010003 },
    { 0x13010003 },
    { 0x1401000C },
    { 0x13010003 },
    { 0x0D000003 },
};

union AnimationStep slope_skier_anim_16[] = {
    { 0x24010003 },
    { 0x25010009 },
    { 0x24010003 },
    { 0x2B010003 },
    { 0x2C010003 },
    { 0x2D010015 },
    { 0x2C010003 },
    { 0x2B010003 },
    { 0x24010003 },
    { 0x25000003 },
};

union AnimationStep slope_skier_anim_17[] = {
    { 0x24010003 },
    { 0x25010009 },
    { 0x24010003 },
    { 0x26010003 },
    { 0x27010003 },
    { 0x28010015 },
    { 0x27010003 },
    { 0x26010003 },
    { 0x24010003 },
    { 0x25000003 },
};

union AnimationStep slope_skier_anim_18[] = {
    { 0x1E010003 },
    { 0x1F01000F },
    { 0x1E010003 },
    { 0x01010002 },
    { 0x01000101 },
};

union AnimationStep slope_skier_anim_19[] = {
    { 0x20010003 },
    { 0x2101000F },
    { 0x22010003 },
    { 0x05010002 },
    { 0x05000101 },
};

union AnimationStep slope_skier_anim_20[] = {
    { 0x22010003 },
    { 0x2301000F },
    { 0x22010003 },
    { 0x05010002 },
    { 0x05000101 },
};

union AnimationStep slope_skier_anim_10[] = {
    { 0x08010003 },
    { 0x17010003 },
    { 0x18010203 },
    { 0x19010003 },
    { 0x18010003 },
    { 0x1901000F },
    { 0x18010003 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C01000F },
    { 0x1B010003 },
    { 0x1A010003 },
    { 0x1D000103 },
};

union AnimationStep slope_skier_anim_11[] = {
    { 0x0D010003 },
    { 0x0E010003 },
    { 0x0F010009 },
    { 0x0E010003 },
    { 0x17010003 },
    { 0x18010203 },
    { 0x19010003 },
    { 0x18010003 },
    { 0x1901000F },
    { 0x18010003 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C01000F },
    { 0x1B010003 },
    { 0x1A010003 },
    { 0x1D000103 },
};

union AnimationStep slope_skier_anim_12[] = {
    { 0x12010003 },
    { 0x13010003 },
    { 0x14010009 },
    { 0x13010003 },
    { 0x17010003 },
    { 0x18010203 },
    { 0x19010003 },
    { 0x18010003 },
    { 0x1901000F },
    { 0x18010003 },
    { 0x1A010003 },
    { 0x1B010003 },
    { 0x1C01000F },
    { 0x1B010003 },
    { 0x1A010003 },
    { 0x1D000103 },
};

union AnimationStep slope_skier_anim_21[] = {
    { 0x29010002 },
    { 0x2A010002 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x29FC0012 },
};

union AnimationStep slope_skier_anim_22[] = {
    { 0x2A000001 },
};

union AnimationStep slope_skier_anim_23[] = {
    { 0x2E010002 },
    { 0x2F010002 },
    { 0x30010002 },
    { 0x31010002 },
    { 0x32010002 },
    { 0x33010002 },
    { 0x34010002 },
    { 0x35010002 },
    { 0x36010002 },
    { 0x37010002 },
    { 0x38010002 },
    { 0x39010002 },
    { 0x3A010002 },
    { 0x3B010002 },
    { 0x3CFF0002 },
};

union AnimationStep slope_skier_anim_24[] = {
    { 0x3D000001 },
};

union AnimationStep slope_skier_anim_25[] = {
    { 0x3E000001 },
};

union AnimationStep slope_skier_anim_26[] = {
    { 0x3F000001 },
};

union AnimationStep slope_skier_anim_27[] = {
    { 0x40000001 },
};

union AnimationStep slope_skier_anim_28[] = {
    { 0x41000001 },
};

union AnimationStep slope_skier_anim_29[] = {
    { 0x42000001 },
};

union AnimationStep slope_skier_anim_30[] = {
    { 0x43000001 },
};

union AnimationStep* slope_skier_animations[] = {
    slope_skier_anim_0,
    slope_skier_anim_1,
    slope_skier_anim_2,
    slope_skier_anim_3,
    slope_skier_anim_4,
    slope_skier_anim_5,
    slope_skier_anim_6,
    slope_skier_anim_7,
    slope_skier_anim_8,
    slope_skier_anim_9,
    slope_skier_anim_10,
    slope_skier_anim_11,
    slope_skier_anim_12,
    slope_skier_anim_13,
    slope_skier_anim_14,
    slope_skier_anim_15,
    slope_skier_anim_16,
    slope_skier_anim_17,
    slope_skier_anim_18,
    slope_skier_anim_19,
    slope_skier_anim_20,
    slope_skier_anim_21,
    slope_skier_anim_22,
    slope_skier_anim_23,
    slope_skier_anim_24,
    slope_skier_anim_25,
    slope_skier_anim_26,
    slope_skier_anim_27,
    slope_skier_anim_28,
    slope_skier_anim_29,
    slope_skier_anim_30,
};

u8 slope_skier_debris[] = {
    0x18,
    0x19,
    0x1A,
    0x1B,
    0x1C,
    0x1D,
    0x1E,
    0x00,
};

void (*slope_skier_jump_funcs[])() = {
    func_80055F1C,
    slope_skier_jump_rise,
};

struct VisualSpawnOffset D_800FCE90[5] = {
    { -23, -5 },
    { -23, 2 },
    { -29, 1 },
    { -29, 4 },
    { -39, -2 },
};

struct Unk_unk68 D_800FCE9C[] = {
    { -1, -6, 246, 0 },
};

void (*slope_skier_slide_funcs[])() = {
    slope_skier_slide_start,
    func_800562AC,
    slope_skier_slide_idle,
};

void (*slope_skier_step_funcs[])() = {
    enemy_hit_reaction,
    slope_skier_slide,
    slope_skier_fall,
    slope_skier_land,
    slope_skier_jump,
    func_80056054,
    slope_skier_wait_for_player,
};

void (*slope_skier_state_funcs[])() = {
    func_800564B4,
    slope_skier_main,
    slope_skier_despawn,
};
