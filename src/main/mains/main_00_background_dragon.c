// MainObj, main_object_update_funcs[0]
// 80040608..80042120
#include "common.h"
#include "func_tables.h"

void background_dragon_update(struct MainObj* self)
{
    background_dragon_state_funcs[self->state](self);
}

// background_dragon_init
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_80040644);

void background_dragon_spawn_trail(struct PlayerObj* self, s8 arg1)
{
    struct VisualObj* visual_obj;

    visual_obj = find_free_visual_obj();
    if (visual_obj != 0) {
        visual_obj->unk50 = self;
        visual_obj->active = 0x41;
        visual_obj->id = 0x0A;
        visual_obj->unk2 = arg1;
        visual_obj->state = 0;
        visual_obj->unk5 = 0;
        visual_obj->unk6 = 0;
        visual_obj->unk38 = 0;
        visual_obj->unk3C = self->unk3C;
        visual_obj->animation_table = self->animation_table;
        visual_obj->unk40 = self->unk40;
        visual_obj->unk42 = self->unk42;
        visual_obj->unk16 = 0x23;
        visual_obj->x_pos = self->x_pos;
        visual_obj->y_pos = self->y_pos;
    }
}

void background_dragon_reset(struct MainObj* self)
{
    self->unk5 = 0xC;
    set_animation(self, 0);
}

// background_dragon_main
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_80040838);

// background_dragon_pick_step
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_80040ABC);

// background_dragon_hover
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_80040CCC);

void background_dragon_wait_for_animation(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    update_on_screen((struct BaseObj*)self, 0x90, 0x90);
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5 = 4;
    }
}

void background_dragon_fireball_begin(struct MainObj* self)
{
    s16 x_pos_hi;
    s32 x_velocity;

    x_pos_hi = self->x_pos.i.hi;
    if (x_pos_hi > 0xC90) {
        set_animation(self, 0);
        self->unk5 = 0xC;
        self->unk6 = 0;
        update_on_screen((struct BaseObj*)self, 0x90, 0x90);
    } else {
        if (x_pos_hi > 0xC40) {
            self->unk15 = 0x40;
        }
        self->y_pos.val = FIXED(368);
        self->unk6++;
        set_animation(self, 3);
        x_velocity = FIXED(-1);
        if (self->unk15 != 0) {
            x_velocity = FIXED(1);
        }
        self->x_speed = x_velocity;
        self->y_speed = 0;
        update_on_screen((struct BaseObj*)self, 0x90, 0x90);
    }
}

void background_dragon_fireball_update(struct MainObj* self)
{
    struct ShotObj* shot_obj;
    struct MiscObj* misc_obj;
    s32 x_pos;

    move_object((struct MovingObj*)self);
    animate_object(ANIMATED_OBJECT(self));

    if (self->animation_step.fields.event == 1) {
        shot_obj = find_free_shot_obj();
        if (shot_obj != 0) {
            shot_obj->active = 0x41;
            shot_obj->id = 0;
            shot_obj->unk7C = (struct WeaponObj*)self;
            shot_obj->state = 0;
            shot_obj->unk5 = 0;
            shot_obj->unk6 = 0;
            shot_obj->unk2 = 1;
        }

        misc_obj = find_free_misc_obj();
        if (misc_obj != 0) {
            misc_obj->active = 0x41;
            misc_obj->id = 4;
            misc_obj->unk2 = 3;
            misc_obj->ext.ready_text.owner = (struct EffectObj*)self;
            misc_obj->state = 0;

            x_pos = self->x_pos.val;
            misc_obj->x_pos.val = x_pos + ((self->unk15 == 0) ? FIXED(60) : FIXED(-60));
            misc_obj->y_pos.val = self->y_pos.val + FIXED(68);
        }

        self->animation_step.fields.event = 0;
        self->x_speed = 0;
        self->y_speed = FIXED(-0.25);
        func_8001540C(2, 4, self);
    }

    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 0);
        self->unk5 = 0xC;
        self->unk6 = 0;
    }

    update_on_screen((struct BaseObj*)self, 0x90, 0x90);
}

void background_dragon_fireball_begin(struct MainObj* self);

void background_dragon_fireball_update(struct MainObj* self);

void background_dragon_fireball(struct MainObj* self)
{
    if (self->unk6 == 0) {
        background_dragon_fireball_begin(self);
    } else {
        background_dragon_fireball_update(self);
    }
}

// background_dragon_projectile_attack_begin
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_80041060);

void background_dragon_projectile_attack_update(struct MainObj* self)
{
    s32 value;
    struct MiscObj* misc;
    u8 index;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 3) {
        move_object((struct MovingObj*)self);
    }
    if (self->animation_step.fields.event == 1) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0;
            shot->unk7C = (struct WeaponObj*)self;
            shot->state = 0;
            shot->unk5 = 0;
            shot->unk6 = 0;
            shot->unk2 = 0;
        }
        value = FIXED(3.75);
        self->animation_step.fields.event = 0;
        if (self->unk15 != 0) {
            value = FIXED(-3.75);
        }
        self->x_speed = value;
        self->y_speed = FIXED(-1);
        func_8001540C(2, 4, self);
    }
    if (self->animation_step.fields.event == 2) {
        index = self->ext.main_0.index;
        if (index < 3U && engine_obj.character_state.bytes[index + 1] == 0) {
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 1;
                misc->id = 4;
                misc->ext.ready_text.owner = (struct EffectObj*)self;
                misc->state = 4;
                misc->unk5 = 0;
                misc->unk6 = 0;
                misc->unk2 = self->ext.main_0.index;
            }
            self->animation_step.fields.event = 0;
            apply_tile_effect(self->ext.main_0.index + 1, 0, 0);
            self->ext.main_0.flags[self->ext.main_0.index] = 1;
            engine_obj.character_state.bytes[self->ext.main_0.index + 1] = 1;
            start_screen_shake_y(0x18, 3, 1);
        }
    }
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 0);
        self->unk5 = 0xC;
        self->unk6 = 0;
    }
    update_on_screen((struct BaseObj*)self, 0x90, 0x90);
}

void func_80041060(struct MainObj* self);

void background_dragon_projectile_attack_update(struct MainObj* self);

void background_dragon_projectile_attack(struct MainObj* self)
{
    if (self->unk6 == 0) {
        func_80041060(self);
    } else {
        background_dragon_projectile_attack_update(self);
    }
}

void background_dragon_multi_shot_begin(struct BaseObj* self)
{
    self->unk6++;
    set_animation(self, 7);
    update_on_screen(self, 0x90, 0x90);
}

void background_dragon_multi_shot_update(struct MainObj* self)
{
    struct VisualObj* visual;
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 1) {
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0xA;
            visual->unk50 = (struct PlayerObj*)self;
            visual->state = 2;
            visual->unk5 = 0;
            visual->unk6 = 0;
        }
        self->animation_step.fields.event = 0;
        func_8001540C(2, 0xB, self);
    }
    if (self->animation_step.fields.event >= 2 && self->animation_step.fields.event <= 3) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0;
            shot->unk7C = (struct WeaponObj*)self;
            shot->state = 0;
            shot->unk5 = 0;
            shot->unk6 = 0;
            shot->unk2 = self->animation_step.fields.event;
        }
        self->animation_step.fields.event = 0;
        func_8001540C(2, 9, self);
    }
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 6);
        self->unk5 = 9;
        self->unk6 = 0;
    }
    update_on_screen((struct BaseObj*)self, 0x90, 0x90);
}

void background_dragon_multi_shot_update(struct MainObj* self);

void background_dragon_multi_shot(struct MainObj* self)
{
    if (self->unk6 == 0) {
        background_dragon_multi_shot_begin((struct BaseObj*)self);
    } else {
        background_dragon_multi_shot_update(self);
    }
}

void background_dragon_sequence_begin(struct MainObj* self)
{
    self->unk15 = 0;
    set_animation(self, 0);
    self->unk6++;
    update_on_screen(self, 0x90, 0x90);
}

// background_dragon_swoop
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_800415B0);

void background_dragon_sequence_bob(struct MainObj* self)
{

    if (self->animation_step.fields.event == 0) {
        self->y_speed = 0;
    }
    if (self->animation_step.fields.event == 1) {
        self->y_speed = FIXED(5.33333);
    }
    if (self->animation_step.fields.event == 2) {
        self->y_speed = FIXED(-5.33333);
    }
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step < 0) {
        set_animation(self, 0);
        if (++self->unk7E > 2) {
            self->unk7E = 0;
            if (self->ext.main_0.exit_mode != 0) {
                self->unk5 = 8;
            } else {
                self->unk5 = 6;
            }
        } else {
            if (self->ext.main_0.exit_mode != 0) {
                self->unk5 = 8;
            } else {
                self->unk5 = 5;
            }
        }
        self->unk6 = 0;
    }
    update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
}

void background_dragon_sequence(struct MainObj* self)
{
    s8 state;

    state = self->unk6;
    if (state != 1) {
        if (state < 2) {
            if (state == 0) {
                background_dragon_sequence_begin(self);
                return;
            }
        }
    } else {
        func_800415B0(self);
        return;
    }
    background_dragon_sequence_bob(self);
}

// background_dragon_chase
INCLUDE_ASM("main/nonmatchings/mains/main_00_background_dragon", func_800419B8);

void background_dragon_fly_to_route_start(struct MainObj* self)
{
    s32 temp_a0;

    set_velocity_from_angle(
        MOVING_OBJECT(self),
        angle_to_point(
            OBJECT_HEADER(self), background_dragon_perch_points[self->unk2 >> 1][0],
            background_dragon_perch_points[self->unk2 >> 1][1]));

    self->x_speed *= 2;
    self->y_speed *= 2;
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));

    temp_a0 = self->x_pos.val - background_dragon_perch_points[self->unk2 >> 1][0];
    if (temp_a0 >= 0) {
        if (temp_a0 >= 0x20000) {
            update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
            return;
        }
    } else if (background_dragon_perch_points[self->unk2 >> 1][0] - self->x_pos.val >= 0x20000) {
        update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
        return;
    }

    temp_a0 = self->y_pos.val - background_dragon_perch_points[self->unk2 >> 1][1];
    if (temp_a0 >= 0) {
        if (temp_a0 > 0x1FFFF) {
            update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
            return;
        }
    } else if (background_dragon_perch_points[self->unk2 >> 1][1] - self->y_pos.val >= 0x20000) {
        update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
        return;
    }
    self->unk5 = 1;

    update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
}

void background_dragon_fly_offscreen(struct MainObj* self)
{
    s32 target_x;
    s32 target_y;

    switch (self->unk2) {
    case 0:
        target_x = background_objects[0].x_pos.val + FIXED(-256);
        target_y = background_objects[0].y_pos.val + FIXED(-256);
        break;
    case 1:
        target_x = background_objects[0].x_pos.val + FIXED(-256);
        target_y = background_objects[0].y_pos.val + FIXED(496);
        break;
    }

    set_velocity_from_angle(
        MOVING_OBJECT(self),
        angle_to_point(OBJECT_HEADER(self), target_x, target_y));

    if (self->ext.main_0.exit_mode == 2) {
        self->x_speed = self->x_speed * 2;
        *(volatile s32*)&self->y_speed = self->y_speed * 2;
    } else {
        self->x_speed = self->x_speed * 4;
        *(volatile s32*)&self->y_speed = self->y_speed * 4;
    }

    move_with_gravity(ANIMATED_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));

    if (self->on_screen == 0) {
        if (self->ext.main_0.exit_mode != 0) {
            self->state = 2;
            return;
        }

        self->unk16 = 0x12;
        self->unk5 = 7;
        self->bg_offset = -1;
        self->x_pos.val = background_dragon_route_starts[self->unk2].x;
        self->y_pos.val = background_dragon_route_starts[self->unk2].y;
        self->ext.main_0.background_relative = 0;
        set_animation(self, 6);

        if (self->unk2 >= 2 && self->unk2 <= 3) {
            self->unk15 = 0x40;
        } else {
            self->unk15 = 0;
        }
    }

    update_on_screen(BASE_OBJECT(self), 0x90, 0x90);
}

void background_dragon_fly_to_staging_position(struct MainObj* self)
{
    set_velocity_from_angle(
        MOVING_OBJECT(self),
        angle_to_point(
            OBJECT_HEADER(self),
            background_dragon_route_starts[self->unk2].x,
            background_dragon_route_starts[self->unk2].y));
    move_object(MOVING_OBJECT(self));
    animate_object(ANIMATED_OBJECT(self));

    if (self->on_screen == 0) {
        if (self->ext.main_0.exit_mode != 0) {
            self->state = 2;
            return;
        }

        self->unk16 = 0x22;
        self->unk5 = 0xA;
        if (self->unk2 >= 2 && self->unk2 <= 3) {
            self->unk15 = 0x40;
        } else {
            self->unk15 = 0;
        }
    }

    update_on_screen((struct BaseObj*)self, 0x70, 0x70);
}

void background_dragon_attach_to_background(struct MainObj* self)
{
    set_animation(self, 0);
    self->x_pos.val = background_objects[0].x_pos.val + background_dragon_staging_offsets[self->unk2].x;
    self->y_pos.val = background_objects[0].y_pos.val + background_dragon_staging_offsets[self->unk2].y;
    self->unk5 = 6;
    self->unk15 = 0;
    self->bg_offset = 0;
    self->ext.main_0.background_relative = 1;
}

void background_dragon_noop(struct MainObj* self)
{
}

void background_dragon_cleanup(struct MainObj* self)
{
    engine_obj.enable_boss = 0;
    engine_obj.boss_ptr = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

union AnimationStep D_800F96F4[] = {
    { 0x0001FF10 },
    { 0x01010108 },
    { 0x02010110 },
    { 0x01FDFF08 },
};

union AnimationStep D_800F9704[] = {
    { 0x00010008 },
    { 0x03010003 },
    { 0x04010003 },
    { 0x0501000A },
    { 0x06010019 },
    { 0x0601030F },
    { 0x07010102 },
    { 0x08010213 },
    { 0x08F80001 },
};

union AnimationStep D_800F9728[] = {
    { 0x09010105 },
    { 0x0A010010 },
    { 0x0AFE0001 },
};

union AnimationStep D_800F9734[] = {
    { 0x00010008 },
    { 0x0B01000A },
    { 0x0C010003 },
    { 0x0D010004 },
    { 0x0E010019 },
    { 0x0F010102 },
    { 0x10010028 },
    { 0x10F90001 },
};

union AnimationStep D_800F9754[] = {
    { 0x11010105 },
    { 0x12010025 },
    { 0x12FE0001 },
};

union AnimationStep D_800F9760[] = {
    { 0x13010008 },
    { 0x14010008 },
    { 0x15010008 },
    { 0x16010008 },
    { 0x17010008 },
    { 0x18FB0108 },
};

union AnimationStep D_800F9778[] = {
    { 0x19010008 },
    { 0x1A010008 },
    { 0x1B010008 },
    { 0x1CFD0008 },
};

union AnimationStep D_800F9788[] = {
    { 0x1B010003 },
    { 0x1D010003 },
    { 0x1E010003 },
    { 0x1F010136 },
    { 0x1F010003 },
    { 0x1E010203 },
    { 0x1F010014 },
    { 0x1F010003 },
    { 0x1E010303 },
    { 0x1F010013 },
    { 0x1FF30001 },
};

union AnimationStep D_800F97B4[] = {
    { 0x20010003 },
    { 0x21010003 },
    { 0x22010003 },
    { 0x23010003 },
    { 0x24010003 },
    { 0x25010003 },
    { 0x20010003 },
    { 0x21010003 },
    { 0x22010003 },
    { 0x23010003 },
    { 0x24010003 },
    { 0x25010002 },
    { 0x25EE0001 },
};

union AnimationStep D_800F97E8[] = {
    { 0x1F010003 },
    { 0x1E010003 },
    { 0x1FFE0014 },
};

union AnimationStep D_800F97F4[] = {
    { 0x26010002 },
    { 0x27010002 },
    { 0x28010002 },
    { 0x29FD0002 },
};

union AnimationStep D_800F9804[] = {
    { 0x2A010001 },
    { 0x2B010003 },
    { 0x2C010003 },
    { 0x2D010003 },
    { 0x2E010003 },
    { 0x2FFB0003 },
};

union AnimationStep D_800F981C[] = {
    { 0x31010003 },
    { 0x3201003C },
    { 0x31010002 },
    { 0x31FD0001 },
};

union AnimationStep D_800F982C[] = {
    { 0x30010103 },
    { 0x30010103 },
    { 0x3001003C },
    { 0x30010203 },
    { 0x30010202 },
    { 0x30FF0201 },
};

union AnimationStep D_800F9844[] = {
    { 0x31010003 },
    { 0x32010003 },
    { 0x3301003C },
    { 0x32010003 },
    { 0x31010002 },
    { 0x31FB0001 },
};

union AnimationStep D_800F985C[] = {
    { 0x30010103 },
    { 0x3001003C },
    { 0x30010202 },
    { 0x30FF0201 },
};

u8 background_dragon_attack_map[128] = {
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x01,
    0x00,
    0x00,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x06,
    0x06,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x05,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x02,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x06,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x03,
    0x07,
    0x07,
    0x07,
    0x07,
    0x07,
    0x07,
    0x07,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
    0x08,
};

s16 D_800F98EC[36] = {
    (s16)0xFFD3,
    (s16)0x0021,
    (s16)0x0000,
    (s16)0x001E,
    (s16)0xFFD4,
    (s16)0x001F,
    (s16)0xFFE0,
    (s16)0x003B,
    (s16)0xFFDF,
    (s16)0x0050,
    (s16)0x0029,
    (s16)0x0053,
    (s16)0x0013,
    (s16)0xFFFF,
    (s16)0xFFDD,
    (s16)0xFFF5,
    (s16)0xFFDD,
    (s16)0xFFF5,
    (s16)0xFFF3,
    (s16)0xFFF5,
    (s16)0xFFF3,
    (s16)0xFFE0,
    (s16)0x0037,
    (s16)0x000B,
    (s16)0xFFCC,
    (s16)0x000F,
    (s16)0xFFEE,
    (s16)0x000D,
    (s16)0xFFE7,
    (s16)0x0024,
    (s16)0x0010,
    (s16)0x0021,
    (s16)0x0016,
    (s16)0xFFE3,
    (s16)0xFFE7,
    (s16)0xFFE3,
};

union AnimationStep* D_800F9934[16] = {
    D_800F96F4,
    D_800F9704,
    D_800F9728,
    D_800F9734,
    D_800F9754,
    D_800F9760,
    D_800F9778,
    D_800F9788,
    D_800F97B4,
    D_800F97E8,
    D_800F97F4,
    D_800F9804,
    D_800F981C,
    D_800F982C,
    D_800F9844,
    D_800F985C,
};

void (*background_dragon_state_funcs[])(struct MainObj*) = {
    func_80040644,
    func_80040838,
    background_dragon_cleanup,
};

s16 D_800F9980[4] = { -1, 1, 1, -1 };

void (*background_dragon_step_funcs[13])(struct MainObj*) = {
    background_dragon_reset,
    background_dragon_wait_for_animation,
    background_dragon_fireball,
    background_dragon_projectile_attack,
    background_dragon_multi_shot,
    background_dragon_sequence,
    func_800419B8,
    background_dragon_fly_to_route_start,
    background_dragon_fly_offscreen,
    background_dragon_fly_to_staging_position,
    background_dragon_attach_to_background,
    background_dragon_noop,
    func_80040CCC,
};

u16 D_800F99BC[4] = { 0x6A0, 0x8A0, 0xAA0, 0 };

s32 background_dragon_perch_points[][2] = {
    { FIXED(40), FIXED(179) },
    { FIXED(280), FIXED(179) },
};

struct FixedPointPosition background_dragon_route_starts[2] = {
    { -0x800000, 0xB30000 },
    { -0x800000, 0x1700000 },
};

struct FixedPointPosition background_dragon_staging_offsets[4] = {
    { -0x800000, -0x800000 },
    { -0x800000, 0x1700000 },
    { 0x1C00000, -0x800000 },
    { 0x1C00000, 0x1700000 },
};
