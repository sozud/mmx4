// MainObj, main_object_update_funcs[0]
// 80040608..80042120
#include "common.h"
#include "func_tables.h"

void background_dragon_update(struct MainObj* arg0)
{
    background_dragon_state_funcs[arg0->state](arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_00", func_80040644);

void func_80040760(struct PlayerObj* arg0, s8 arg1)
{
    struct VisualObj* visual_obj;

    visual_obj = find_free_visual_obj();
    if (visual_obj != 0) {
        visual_obj->active = 0x41;
        visual_obj->unk50 = arg0;
        visual_obj->id = 0x0A;
        visual_obj->unk2 = arg1;
        visual_obj->state = 0;
        visual_obj->unk5 = 0;
        visual_obj->unk6 = 0;
        visual_obj->unk38 = 0;
        visual_obj->unk3C = arg0->unk3C;
        visual_obj->animation_table = arg0->animation_table;
        visual_obj->unk40 = arg0->unk40;
        visual_obj->unk42 = arg0->unk42;
        visual_obj->unk16 = 0x23;
        visual_obj->x_pos = arg0->x_pos;
        visual_obj->y_pos = arg0->y_pos;
    }
}

void background_dragon_reset(struct MainObj* arg0)
{
    arg0->unk5 = 0xC;
    func_80015D60(arg0, 0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_00", func_80040838);

INCLUDE_ASM("main/nonmatchings/mains/main_00", func_80040ABC);

INCLUDE_ASM("main/nonmatchings/mains/main_00", func_80040CCC);

void background_dragon_wait_for_animation(struct MainObj* arg0)
{
    func_80015DC8(ANIMATED_OBJECT(arg0));
    func_8002B318((struct BaseObj*)arg0, 0x90, 0x90);
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 4;
    }
}

void background_dragon_fireball_begin(struct MainObj* arg0)
{
    s16 x_pos_hi;
    s32 x_velocity;

    x_pos_hi = arg0->x_pos.i.hi;
    if (x_pos_hi >= 0xC91) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 0xC;
        arg0->unk6 = 0;
        func_8002B318((struct BaseObj*)arg0, 0x90, 0x90);
    } else {
        if (x_pos_hi >= 0xC41) {
            arg0->unk15 = 0x40;
        }
        arg0->y_pos.val = FIXED(368);
        arg0->unk6++;
        func_80015D60(arg0, 3);
        x_velocity = FIXED(-1);
        if (arg0->unk15 != 0) {
            x_velocity = FIXED(1);
        }
        arg0->unk20 = x_velocity;
        arg0->unk24 = 0;
        func_8002B318((struct BaseObj*)arg0, 0x90, 0x90);
    }
}

void background_dragon_fireball_update(struct MainObj* arg0)
{
    struct ShotObj* shot_obj;
    struct MiscObj* misc_obj;
    s32 x_pos;

    func_8002B718((struct MovingObj*)arg0);
    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (arg0->animation_step.fields.event == 1) {
        shot_obj = find_free_shot_obj();
        if (shot_obj != 0) {
            shot_obj->active = 0x41;
            shot_obj->id = 0;
            shot_obj->unk7C = (struct WeaponObj*)arg0;
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
            misc_obj->ext.ready_text.owner = (struct EffectObj*)arg0;
            misc_obj->state = 0;

            x_pos = arg0->x_pos.val;
            misc_obj->x_pos.val = x_pos + ((arg0->unk15 == 0) ? FIXED(60) : FIXED(-60));
            misc_obj->y_pos.val = arg0->y_pos.val + FIXED(68);
        }

        arg0->animation_step.fields.event = 0;
        arg0->unk20 = 0;
        arg0->unk24 = FIXED(-0.25);
        func_8001540C(2, 4, arg0);
    }

    if (arg0->animation_step.fields.relative_step < 0) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 0xC;
        arg0->unk6 = 0;
    }

    func_8002B318((struct BaseObj*)arg0, 0x90, 0x90);
}

void background_dragon_fireball_begin(struct MainObj* arg0);

void background_dragon_fireball_update(struct MainObj* arg0);

void background_dragon_fireball(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        background_dragon_fireball_begin(arg0);
    } else {
        background_dragon_fireball_update(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/mains/main_00", func_80041060);

void background_dragon_projectile_attack_update(struct MainObj* arg0)
{
    s32 value;
    struct MiscObj* misc;
    u8 index;
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event != 3) {
        func_8002B718((struct MovingObj*)arg0);
    }
    if (arg0->animation_step.fields.event == 1) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0;
            shot->unk7C = (struct WeaponObj*)arg0;
            shot->state = 0;
            shot->unk5 = 0;
            shot->unk6 = 0;
            shot->unk2 = 0;
        }
        value = FIXED(3.75);
        arg0->animation_step.fields.event = 0;
        if (arg0->unk15 != 0) {
            value = FIXED(-3.75);
        }
        arg0->unk20 = value;
        arg0->unk24 = FIXED(-1);
        func_8001540C(2, 4, arg0);
    }
    if (arg0->animation_step.fields.event == 2) {
        index = arg0->ext.main_0.index;
        if (index < 3U && engine_obj.character_state.bytes[index + 1] == 0) {
            misc = find_free_misc_obj();
            if (misc != NULL) {
                misc->active = 1;
                misc->id = 4;
                misc->ext.ready_text.owner = (struct EffectObj*)arg0;
                misc->state = 4;
                misc->unk5 = 0;
                misc->unk6 = 0;
                misc->unk2 = arg0->ext.main_0.index;
            }
            arg0->animation_step.fields.event = 0;
            func_800DABE4(arg0->ext.main_0.index + 1, 0, 0);
            arg0->ext.main_0.flags[arg0->ext.main_0.index] = 1;
            engine_obj.character_state.bytes[arg0->ext.main_0.index + 1] = 1;
            func_80028BAC(0x18, 3, 1);
        }
    }
    if (arg0->animation_step.fields.relative_step < 0) {
        func_80015D60(arg0, 0);
        arg0->unk5 = 0xC;
        arg0->unk6 = 0;
    }
    func_8002B318((struct BaseObj*)arg0, 0x90, 0x90);
}

void func_80041060(struct MainObj* arg0);

void background_dragon_projectile_attack_update(struct MainObj* arg0);

void background_dragon_projectile_attack(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        func_80041060(arg0);
    } else {
        background_dragon_projectile_attack_update(arg0);
    }
}

void background_dragon_multi_shot_begin(struct BaseObj* arg0)
{
    arg0->unk6++;
    func_80015D60(arg0, 7);
    func_8002B318(arg0, 0x90, 0x90);
}

void background_dragon_multi_shot_update(struct MainObj* arg0)
{
    struct VisualObj* visual;
    struct ShotObj* shot;

    func_80015DC8(ANIMATED_OBJECT(arg0));
    if (arg0->animation_step.fields.event == 1) {
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 0xA;
            visual->unk50 = (struct PlayerObj*)arg0;
            visual->state = 2;
            visual->unk5 = 0;
            visual->unk6 = 0;
        }
        arg0->animation_step.fields.event = 0;
        func_8001540C(2, 0xB, arg0);
    }
    if (arg0->animation_step.fields.event >= 2 && arg0->animation_step.fields.event <= 3) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0;
            shot->unk7C = (struct WeaponObj*)arg0;
            shot->state = 0;
            shot->unk5 = 0;
            shot->unk6 = 0;
            shot->unk2 = arg0->animation_step.fields.event;
        }
        arg0->animation_step.fields.event = 0;
        func_8001540C(2, 9, arg0);
    }
    if (arg0->animation_step.fields.relative_step < 0) {
        func_80015D60(arg0, 6);
        arg0->unk5 = 9;
        arg0->unk6 = 0;
    }
    func_8002B318((struct BaseObj*)arg0, 0x90, 0x90);
}

void background_dragon_multi_shot_update(struct MainObj* arg0);

void background_dragon_multi_shot(struct MainObj* arg0)
{
    if (arg0->unk6 == 0) {
        background_dragon_multi_shot_begin((struct BaseObj*)arg0);
    } else {
        background_dragon_multi_shot_update(arg0);
    }
}

void background_dragon_sequence_begin(struct MainObj* arg0)
{
    arg0->unk15 = 0;
    func_80015D60(arg0, 0);
    arg0->unk6++;
    func_8002B318(arg0, 0x90, 0x90);
}

INCLUDE_ASM("main/nonmatchings/mains/main_00", func_800415B0);

void func_80041854(struct MainObj* self)
{
    s16 count;

    if (self->animation_step.fields.event == 0) {
        self->unk24 = 0;
    }
    if (self->animation_step.fields.event == 1) {
        self->unk24 = FIXED(5.33333);
    }
    if (self->animation_step.fields.event == 2) {
        self->unk24 = FIXED(-5.33333);
    }
    func_8002B718(MOVING_OBJECT(self));
    func_80015DC8(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step < 0) {
        func_80015D60(self, 0);
        count = self->unk7E + 1;
        self->unk7E = count;
        if (count >= 3) {
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
    func_8002B318(BASE_OBJECT(self), 0x90, 0x90);
}

void background_dragon_sequence(struct MainObj* arg0)
{
    s8 state;

    state = arg0->unk6;
    if (state != 1) {
        if (state < 2) {
            if (state == 0) {
                background_dragon_sequence_begin(arg0);
                return;
            }
        }
    } else {
        func_800415B0(arg0);
        return;
    }
    func_80041854(arg0);
}

INCLUDE_ASM("main/nonmatchings/mains/main_00", func_800419B8);

void background_dragon_fly_to_route_start(struct MainObj* arg0)
{
    s32 temp_a0;

    func_8002B93C(
        MOVING_OBJECT(arg0),
        func_8002B7B0(
            OBJECT_HEADER(arg0), D_800F99C4[arg0->unk2 >> 1][0],
            D_800F99C4[arg0->unk2 >> 1][1]));

    arg0->unk20 *= 2;
    arg0->unk24 *= 2;
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));

    temp_a0 = arg0->x_pos.val - D_800F99C4[arg0->unk2 >> 1][0];
    if (temp_a0 >= 0) {
        if (temp_a0 > 0x1FFFF) {
            func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
            return;
        }
    } else if (D_800F99C4[arg0->unk2 >> 1][0] - arg0->x_pos.val > 0x1FFFF) {
        func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
        return;
    }

    temp_a0 = arg0->y_pos.val - D_800F99C4[arg0->unk2 >> 1][1];
    if (temp_a0 >= 0) {
        if (temp_a0 > 0x1FFFF) {
            func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
            return;
        }
    } else if (D_800F99C4[arg0->unk2 >> 1][1] - arg0->y_pos.val > 0x1FFFF) {
        func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
        return;
    }
    arg0->unk5 = 1;

    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
}

void background_dragon_fly_offscreen(struct MainObj* arg0)
{
    s32 target_x;
    s32 target_y;
    s32 x_velocity;
    s32 y_velocity;

    switch (arg0->unk2) {
    case 0:
        target_x = background_objects[0].x_pos.val + FIXED(-256);
        target_y = background_objects[0].y_pos.val + FIXED(-256);
        break;
    case 1:
        target_x = background_objects[0].x_pos.val + FIXED(-256);
        target_y = background_objects[0].y_pos.val + FIXED(496);
        break;
    }

    func_8002B93C(
        MOVING_OBJECT(arg0),
        func_8002B7B0(OBJECT_HEADER(arg0), target_x, target_y));

    if (arg0->ext.main_0.exit_mode == 2) {
        x_velocity = arg0->unk20 * 2;
        y_velocity = arg0->unk24 * 2;
    } else {
        x_velocity = arg0->unk20 * 4;
        y_velocity = arg0->unk24 * 4;
    }

    arg0->unk20 = x_velocity;
    *(volatile s32*)&arg0->unk24 = y_velocity;
    func_8002B694(ANIMATED_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (arg0->on_screen == 0) {
        if (arg0->ext.main_0.exit_mode != 0) {
            arg0->state = 2;
            return;
        }

        arg0->unk16 = 0x12;
        arg0->unk5 = 7;
        arg0->bg_offset = -1;
        arg0->x_pos.val = D_800F99D4[arg0->unk2].x;
        arg0->y_pos.val = D_800F99D4[arg0->unk2].y;
        arg0->ext.main_0.background_relative = 0;
        func_80015D60(arg0, 6);

        if (arg0->unk2 >= 2 && arg0->unk2 <= 3) {
            arg0->unk15 = 0x40;
        } else {
            arg0->unk15 = 0;
        }
    }

    func_8002B318(BASE_OBJECT(arg0), 0x90, 0x90);
}

void background_dragon_fly_to_staging_position(struct MainObj* arg0)
{
    func_8002B93C(
        MOVING_OBJECT(arg0),
        func_8002B7B0(
            OBJECT_HEADER(arg0),
            D_800F99D4[arg0->unk2].x,
            D_800F99D4[arg0->unk2].y));
    func_8002B718(MOVING_OBJECT(arg0));
    func_80015DC8(ANIMATED_OBJECT(arg0));

    if (arg0->on_screen == 0) {
        if (arg0->ext.main_0.exit_mode != 0) {
            arg0->state = 2;
            return;
        }

        arg0->unk16 = 0x22;
        arg0->unk5 = 0xA;
        if (arg0->unk2 >= 2 && arg0->unk2 <= 3) {
            arg0->unk15 = 0x40;
        } else {
            arg0->unk15 = 0;
        }
    }

    func_8002B318((struct BaseObj*)arg0, 0x70, 0x70);
}

void background_dragon_attach_to_background(struct MainObj* arg0)
{
    s32 y_base;
    s32 y_offset;

    func_80015D60(arg0, 0);
    arg0->x_pos.val = background_objects[0].x_pos.val + D_800F99E4[arg0->unk2].x;
    y_base = background_objects[0].y_pos.val;
    y_offset = D_800F99E4[arg0->unk2].y;
    arg0->unk5 = 6;
    arg0->unk15 = 0;
    arg0->bg_offset = 0;
    arg0->ext.main_0.background_relative = 1;
    arg0->y_pos.val = y_base + y_offset;
}

void background_dragon_noop(struct MainObj* arg0)
{
}

void background_dragon_cleanup(struct MainObj* arg0)
{
    engine_obj.enable_boss = 0;
    engine_obj.boss_ptr = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
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

u8 D_800F986C[128] = {
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

void (*D_800F9988[13])(struct MainObj*) = {
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

s32 D_800F99C4[][2] = {
    { FIXED(40), FIXED(179) },
    { FIXED(280), FIXED(179) },
};

struct FixedPointPosition D_800F99D4[2] = {
    { -0x800000, 0xB30000 },
    { -0x800000, 0x1700000 },
};

struct FixedPointPosition D_800F99E4[4] = {
    { -0x800000, -0x800000 },
    { -0x800000, 0x1700000 },
    { 0x1C00000, -0x800000 },
    { 0x1C00000, 0x1700000 },
};
