// MainObj, main_object_update_funcs[48]
// 80067350..800684F8
#include "common.h"
#include "func_tables.h"

void sentry_drone_update(struct MainObj* self)
{
    sentry_drone_state_funcs[self->state](self);
}

// sentry_drone_init
INCLUDE_ASM("main/nonmatchings/mains/main_48_sentry_drone", func_8006738C);

extern u8 sentry_drone_debris[];
extern void (*sentry_drone_step_funcs[])();

void sentry_drone_main(struct MainObj* self)
{
    s8 nextState;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    SP_CUR_MAIN_OBJ->ext.main_48.saved_unk5 = self->unk5;

    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(5, sentry_drone_debris, self);
        nextState = 2;
    } else {
        sentry_drone_check_player_near(self);
        sentry_drone_step_funcs[self->unk5](self);
        func_8002D9BC(self);
        if (func_8002B160(BASE_OBJECT(self)) == 0) {
            is_on_screen(BASE_OBJECT(self));
            return;
        }
        nextState = (u8)self->state + 1;
    }

    self->state = nextState;
}

void sentry_drone_resume_step(struct MainObj* self)
{
    self->unk5 = SP_CUR_MAIN_OBJ->ext.main_48.saved_unk5;
}

void sentry_drone_drift(struct MainObj* self)
{
    sentry_drone_drift_funcs[self->unk6](self);
}

void sentry_drone_drift_start(struct MainObj* self)
{
    s32 direction = -FIXED(0.5);
    self->air_state = 1;
    self->unk6++;
    if (self->unk15 != 0) {
        direction = FIXED(0.5);
    }
    self->x_speed = direction;
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0;
    SP_CUR_MAIN_OBJ->ext.main_48.unk80 = 0x30;
    set_animation(self, 0);
}

void sentry_drone_drift_move(struct MainObj* self)
{
    s8 timer;
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    timer = --SP_CUR_MAIN_OBJ->ext.main_48.unk80;
    if (timer == 0) {
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void sentry_drone_dash(struct MainObj* self)
{
    sentry_drone_dash_funcs[self->unk6](self);
}

void sentry_drone_dash_start(struct MainObj* self)
{
    s32 velocity;
    self->air_state = 0;
    self->unk6++;
    if ((self->unk2 & 0xF) == 2) {
        self->x_speed = 0;
    } else {
        velocity = -FIXED(4);
        if (self->unk15 != 0) {
            velocity = FIXED(4);
        }
        self->x_speed = velocity;
    }
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0;
    set_animation(self, 0);
    SP_CUR_MAIN_OBJ->ext.main_48.unk80 = 0x3C;
}

void sentry_drone_dash_move(struct MainObj* self)
{
    s8 timer;
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    timer = --SP_CUR_MAIN_OBJ->ext.main_48.unk80;
    if (timer == 0) {
        self->air_state = -1;
        self->unk5 = 6;
        self->unk6 = 0;
    }
}

void sentry_drone_burst(struct MainObj* self)
{
    sentry_drone_burst_funcs[self->unk6](self);
    animate_object(self);
}

void sentry_drone_burst_start(struct MainObj* self)
{
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0;
    self->unk6++;
    set_animation(self, 1);
    SP_CUR_MAIN_OBJ->ext.main_48.unk80 = 0x14;
}

// sentry_drone_burst_aim
INCLUDE_ASM("main/nonmatchings/mains/main_48_sentry_drone", func_800678F8);

void sentry_drone_burst_wait(struct MainObj* self)
{
    if (self->animation_step.fields.event != 0) {
        self->unk6++;
    }
}

void sentry_drone_burst_fire(struct MainObj* self)
{
    struct ShotObj* shot;
    struct MiscObj* misc;

    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x1A;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->unk2 = SP_CUR_MAIN_OBJ->ext.main_48.collision_result;
        shot->unk7C = self;
        shot->unk84.value = 0;
        set_velocity_from_angle(MOVING_OBJECT(shot), (s8)SP_CUR_MAIN_OBJ->ext.main_48.collision_result & 0xFE);
        SP_CUR_MAIN_OBJ->ext.main_48.unk80 = 8;
        self->unk6++;
        SP_CUR_MAIN_OBJ->ext.main_48.unk82++;
    }
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x19;
        misc->x_pos.val = self->x_pos.val;
        misc->y_pos.val = self->y_pos.val;
        misc->unk2 = SP_CUR_MAIN_OBJ->ext.main_48.collision_result;
        misc->ext.pointer.unk50 = self;
    }
}

void sentry_drone_burst_repeat(struct MainObj* self)
{
    struct MainObj* work = SP_CUR_MAIN_OBJ;
    s8 timer;
    if (work->ext.main_48.unk82 >= 3) {
        self->unk6++;
        SP_CUR_MAIN_OBJ->ext.main_48.unk82 = 0;
        SP_CUR_MAIN_OBJ->ext.main_48.unk80 = 0x14;
    } else {
        timer = work->ext.main_48.unk80 - 1;
        work->ext.main_48.unk80 = timer;
        if (timer == 0) {
            self->unk6--;
        }
    }
}

void sentry_drone_burst_end(struct MainObj* self)
{
    struct MainObj* work = SP_CUR_MAIN_OBJ;
    s8 state = work->ext.main_48.unk80;

    if (state == 0) {
        if (++work->ext.main_48.unk83 >= 2) {
            self->unk5 = 5;
            self->unk6 = 0;
            SP_CUR_MAIN_OBJ->ext.main_48.unk83 = 0;
        } else {
            self->unk5 = 3;
            self->unk6 = 0;
        }
    } else {
        work->ext.main_48.unk80 = state - 1;
    }
}

void sentry_drone_spread(struct MainObj* self)
{
    sentry_drone_spread_funcs[self->unk6](self);
    animate_object(self);
}

void sentry_drone_spread_start(struct MainObj* self)
{
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0;
    self->unk6++;
    set_animation(self, 1);
    SP_CUR_MAIN_OBJ->ext.main_48.unk80 = 0x14;
    SP_CUR_MAIN_OBJ->ext.main_48.unk82 = 0;
    if (g_Player.x_pos.i.hi - self->x_pos.i.hi > 0) {
        self->unk15 = 0x40;
    }
    SP_CUR_MAIN_OBJ->ext.main_48.collision_result = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    func_800681C4(self);
}

// sentry_drone_spread_aim
INCLUDE_ASM("main/nonmatchings/mains/main_48_sentry_drone", func_80067DAC);

void sentry_drone_spread_fire(struct MainObj* self)
{
    struct ShotObj* shot;
    struct MiscObj* misc;

    if (self->animation_step.fields.event == 0) {
        return;
    }
    shot = find_free_shot_obj();
    if (shot != NULL) {
        shot->active = 0x41;
        shot->id = 0x1A;
        shot->x_pos.val = self->x_pos.val;
        shot->y_pos.val = self->y_pos.val;
        shot->unk2 = SP_CUR_MAIN_OBJ->ext.main_48.collision_result;
        shot->unk7C = self;
        shot->unk84.value = 0;
        set_velocity_from_angle(MOVING_OBJECT(shot), (s8)SP_CUR_MAIN_OBJ->ext.main_48.collision_result & 0xFE);
        SP_CUR_MAIN_OBJ->ext.main_48.unk80 = 8;
        self->unk6++;
        SP_CUR_MAIN_OBJ->ext.main_48.unk82++;
    }
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x19;
        misc->x_pos.val = self->x_pos.val;
        misc->y_pos.val = self->y_pos.val;
        misc->unk2 = SP_CUR_MAIN_OBJ->ext.main_48.collision_result;
        misc->ext.pointer.unk50 = self;
    }
}

void sentry_drone_spread_repeat(struct MainObj* self)
{
    if (SP_CUR_MAIN_OBJ->ext.main_48.unk82 < 9) {
        func_80068340(self);
        self->unk6 -= 2;
    } else {
        self->unk6++;
    }
}

void sentry_drone_spread_pause(struct MainObj* self)
{
    self->unk6++;
}

void sentry_drone_spread_end(struct WeaponObj* self)
{
    self->unk67 = -1;
    self->unk5 = 6;
    self->unk6 = 0;
}

void sentry_drone_drop(struct MainObj* self)
{
    sentry_drone_drop_funcs[self->unk6](self);
}

void sentry_drone_drop_start(struct MainObj* self)
{
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = FIXED(2);
    self->gravity = 0;
    self->unk6++;
    set_animation(self, 1);
}

void sentry_drone_drop_move(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void sentry_drone_check_player_near(struct MainObj* self)
{
    s32 distance;
    s32 max_distance;
    s8 state;

    if ((self->air_state == 0) && ((state = self->unk5) != 4) && (state != 5)) {
        max_distance = sentry_drone_activation_distances[(s8)SP_CUR_MAIN_OBJ->ext.main_0.index];
        distance = g_Player.x_pos.i.hi - self->x_pos.i.hi;
        if (distance >= 0) {
            if (max_distance >= distance) {
                goto activate;
            }
            return;
        }
        if (max_distance < (self->x_pos.i.hi - g_Player.x_pos.i.hi)) {
            return;
        }
    activate:
        self->unk5 = 4;
        self->unk6 = 0;
    }
}

// sentry_drone_aim
INCLUDE_ASM("main/nonmatchings/mains/main_48_sentry_drone", func_800681C4);

// sentry_drone_rotate_aim
INCLUDE_ASM("main/nonmatchings/mains/main_48_sentry_drone", func_80068340);

void sentry_drone_despawn(struct ObjectHeader* self)
{
    SP_CUR_MAIN_OBJ->ext.main_48.unk80 = 0;
    SP_CUR_MAIN_OBJ->ext.main_48.unk81 = 0;
    SP_CUR_MAIN_OBJ->ext.main_48.unk82 = 0;
    SP_CUR_MAIN_OBJ->ext.main_48.unk83 = 0;
    SP_CUR_MAIN_OBJ->ext.main_48.saved_unk5 = 0;
    SP_CUR_MAIN_OBJ->ext.main_48.collision_result = 0;
    SP_CUR_MAIN_OBJ->ext.main_48.unk86 = 0;
    SP_CUR_MAIN_OBJ->ext.main_48.unk87 = 0;
    SP_CUR_MAIN_OBJ->ext.main_48.unk88 = 0;

    if (self->unk2 & 0x80) {
        ZeroObjectState(self);
    } else {
        despawn_object(self);
    }
}

void sentry_drone_wait_for_player(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi - self->x_pos.i.hi >= 0xB0) {
        self->unk15 = 0x40;
        self->state = 1;
        self->unk5 = 3;
    }
}

union AnimationStep sentry_drone_anim_0[] = { { 0x00010001 }, { 0x01FF0001 } };

union AnimationStep sentry_drone_anim_1[] = { { 0x02010001 }, { 0x03FF0101 } };

union AnimationStep sentry_drone_anim_2[] = { { 0x0A010001 }, { 0x0BFF0101 } };

union AnimationStep sentry_drone_anim_3[] = { { 0x0E010001 }, { 0x0FFF0101 } };

union AnimationStep sentry_drone_anim_4[] = { { 0x04010001 }, { 0x05FF0101 } };

union AnimationStep sentry_drone_anim_5[] = { { 0x0C010001 }, { 0x0DFF0101 } };

union AnimationStep sentry_drone_anim_6[] = {
    { 0x10010002 },
    { 0x11010002 },
    { 0x12010002 },
    { 0x13FD0002 },
};

union AnimationStep sentry_drone_anim_7[] = {
    { 0x14010001 },
    { 0x15010001 },
    { 0x16010001 },
    { 0x17010002 },
    { 0x18010003 },
    { 0x19010004 },
    { 0x1A000005 },
};

union AnimationStep sentry_drone_anim_8[] = { { 0x1B000001 } };

union AnimationStep sentry_drone_anim_9[] = { { 0x1C000001 } };

union AnimationStep sentry_drone_anim_10[] = { { 0x1D000001 } };

union AnimationStep sentry_drone_anim_11[] = { { 0x1E000001 } };

union AnimationStep sentry_drone_anim_12[] = { { 0x1F000001 } };

union AnimationStep* sentry_drone_animations[13] = {
    sentry_drone_anim_0,
    sentry_drone_anim_1,
    sentry_drone_anim_2,
    sentry_drone_anim_3,
    sentry_drone_anim_4,
    sentry_drone_anim_5,
    sentry_drone_anim_6,
    sentry_drone_anim_7,
    sentry_drone_anim_8,
    sentry_drone_anim_9,
    sentry_drone_anim_10,
    sentry_drone_anim_11,
    sentry_drone_anim_12,
};

s8 D_800FFACC[4] = { -9, -9, 23, 18 };

u8 D_800FFAD0[4] = { 0, 7, 13, 24 };

u8 D_800FFAD4[4] = { 0, 0, 11, 11 };

s16 sentry_drone_activation_distances[4] = { 0x40, 0x50, 0x60, 0x70 };

u8 sentry_drone_debris[8] = { 8, 9, 10, 11, 12 };

void (*sentry_drone_state_funcs[])(struct MainObj*) = {
    func_8006738C,
    sentry_drone_main,
    sentry_drone_despawn,
    sentry_drone_wait_for_player,
};

void (*sentry_drone_step_funcs[7])() = {
    enemy_hit_reaction,
    sentry_drone_resume_step,
    sentry_drone_drift,
    sentry_drone_dash,
    sentry_drone_burst,
    sentry_drone_spread,
    sentry_drone_drop,
};

void (*sentry_drone_drift_funcs[2])(struct MainObj*) = { sentry_drone_drift_start, sentry_drone_drift_move };

void (*sentry_drone_dash_funcs[2])(struct MainObj*) = { sentry_drone_dash_start, sentry_drone_dash_move };

void (*sentry_drone_burst_funcs[6])(struct MainObj*) = {
    sentry_drone_burst_start,
    func_800678F8,
    sentry_drone_burst_wait,
    sentry_drone_burst_fire,
    sentry_drone_burst_repeat,
    sentry_drone_burst_end,
};

void (*sentry_drone_spread_funcs[6])(struct MainObj*) = {
    sentry_drone_spread_start,
    func_80067DAC,
    sentry_drone_spread_fire,
    sentry_drone_spread_repeat,
    sentry_drone_spread_pause,
    sentry_drone_spread_end,
};

void (*sentry_drone_drop_funcs[2])() = { sentry_drone_drop_start, sentry_drone_drop_move };

u8 D_800FFB5C[4] = { 0, 0, 13, 21 };
