// MainObj, main_object_update_funcs[48]
// 80067350..800684F8
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_48_sentry_drone.h"
#include "main/objects.h"
#include "main/object_motion.h"
#include "main/1E1BC.h"
#include "main/55C4.h"

extern s16 sentry_drone_activation_distances[];

void sentry_drone_main(struct MainObj*);
void sentry_drone_despawn(struct MainObj*);
void sentry_drone_wait_for_player(struct MainObj*);

void sentry_drone_drift(struct MainObj* arg0);
void sentry_drone_dash(struct MainObj* arg0);
void sentry_drone_burst(struct MainObj* arg0);
void sentry_drone_spread(struct MainObj* arg0);
void sentry_drone_drop(struct MainObj* arg0);

void sentry_drone_drift_move(struct MainObj*);

void sentry_drone_dash_move(struct MainObj*);

// sentry_drone_burst_funcs
extern void (*sentry_drone_burst_funcs[])(struct MainObj*);
void sentry_drone_burst_start(struct MainObj*);
void func_800678F8(struct MainObj*);
void sentry_drone_burst_wait(struct MainObj* arg0);

void sentry_drone_burst_repeat(struct MainObj*);
void sentry_drone_burst_end(struct MainObj*);

// sentry_drone_spread_funcs
extern void (*sentry_drone_spread_funcs[])(struct MainObj*);
void sentry_drone_spread_start(struct MainObj*);

void sentry_drone_spread_repeat(struct MainObj*);
void sentry_drone_spread_pause(struct MainObj* arg0);
void sentry_drone_spread_end(struct MainObj* arg0);

// sentry_drone_drop_funcs
void sentry_drone_drop_start(struct MainObj*);
void sentry_drone_drop_move(struct MainObj* arg0);
void sentry_drone_check_player_near(struct MainObj* arg0);

extern void (*sentry_drone_state_funcs[])(struct MainObj*);
extern void (*sentry_drone_drift_funcs[])(struct MainObj*);
extern void (*sentry_drone_dash_funcs[])(struct MainObj*);
extern void (*sentry_drone_drop_funcs[])(struct MainObj*);

extern u32 D_801076F8[];
extern union AnimationStep* sentry_drone_animations[13];
extern s8 D_800FFACC[4];
extern u8 D_800FFAD0[4];
extern u8 D_800FFAD4[4];

void sentry_drone_update(struct MainObj* self)
{
    sentry_drone_state_funcs[self->state](self);
}

// sentry_drone_init
void func_8006738C(struct MainObj* self)
{
    self->bg_offset = g_Player.bg_offset;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(0x30));
    self->sprite_frames = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(0x30)];
    self->unk42 = OBJECT_STAGE_CLUT(0x30);
    self->animation_table = (const u8* const*)sentry_drone_animations;
    self->unk16 = VISUAL_SATURN_LAYER(4);
    self->terrain_box = (struct Unk_unk68*)D_800FFAD0;
    self->attack_box = D_800FFAD4;
    self->hurt_box = D_800FFACC;
    self->collision_data = D_801076F8;
    self->air_state = 0;
    self->invincibility_timer = 0;
    self->hp = 5;
    self->contact_damage = 3;
    self->state = 1;
    self->unk6 = 0;
    SP_CUR_MAIN_OBJ->ext.main_48.unk81 = get_random() & 3;
    if (self->unk2 & 0x80) {
        set_animation(self, 0);
        self->unk5 = 2;
        self->air_state = 1;
    } else {
        self->unk15 = 0;
        set_animation(self, 0);
        self->air_state = 0;
        self->unk5 = 3;
    }
    if ((u8)(self->unk2 & 0xF) == 1) {
        self->state = 3;
    }
}

extern u8 sentry_drone_debris[];
extern void (*sentry_drone_step_funcs[])();

void sentry_drone_main(struct MainObj* self)
{
    s32 hit;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    SP_CUR_MAIN_OBJ->ext.main_48.saved_unk5 = self->unk5;

    hit = func_8002DD04(self);
    if (hit < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(5, sentry_drone_debris, self);
        self->state = 2;
    } else {
        sentry_drone_check_player_near(self);
        sentry_drone_step_funcs[self->unk5](self);
        func_8002D9BC(self);
        if (func_8002B160(BASE_OBJECT(self)) == 0) {
            is_on_screen(BASE_OBJECT(self));
            return;
        }
        self->state = (u8)self->state + 1;
    }
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
    self->air_state = 1;
    self->unk6++;
    self->x_speed = self->unk15 != 0 ? FIXED(0.5) : -FIXED(0.5);
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
    self->unk6++;
    self->air_state = 0;
    if ((self->unk2 & 0xF) == 2) {
        self->x_speed = 0;
    } else {
        velocity = self->unk15 != 0 ? FIXED(4) : -FIXED(4);
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
    self->unk6++;
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0;
    set_animation(self, 1);
    SP_CUR_MAIN_OBJ->ext.main_48.unk80 = 0x14;
}

// sentry_drone_burst_aim
void func_800678F8(struct MainObj* self)
{
    if (--SP_CUR_MAIN_OBJ->ext.main_48.unk80 == 0) {
        if (g_Player.x_pos.i.hi - self->x_pos.i.hi > 0) {
            self->unk15 = PLAYER_FACING_RIGHT;
        }
        SP_CUR_MAIN_OBJ->ext.main_48.collision_result = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
        switch ((s8)SP_CUR_MAIN_OBJ->ext.main_48.collision_result & 0xFE) {
        case 2:
        case 4:
        case 6:
            self->unk15 = PLAYER_FACING_RIGHT;
        case 10:
        case 12:
        case 14:
            if ((s8)SP_CUR_MAIN_OBJ->ext.main_48.collision_result >= 0xA) {
                self->unk15 = 0;
            }
            set_animation(self, 4);
            break;
        case 8:
            set_animation(self, 2);
            break;
        case 18:
        case 20:
        case 22:
            self->unk15 = 0;
        case 26:
        case 28:
        case 30:
            if ((s8)SP_CUR_MAIN_OBJ->ext.main_48.collision_result >= 0x1A) {
                self->unk15 = PLAYER_FACING_RIGHT;
            }
            set_animation(self, 5);
            break;
        case 24:
            set_animation(self, 3);
            break;
        case 0:
            self->unk15 = PLAYER_FACING_RIGHT;
            break;
        case 16:
            self->unk15 = 0;
            break;
        }
        self->unk6++;
    }
}

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
    if (3 <= work->ext.main_48.unk82) {
        self->unk6++;
        SP_CUR_MAIN_OBJ->ext.main_48.unk82 = 0;
        SP_CUR_MAIN_OBJ->ext.main_48.unk80 = 0x14;
    } else {
        if (--work->ext.main_48.unk80 == 0) {
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
    self->unk6++;
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = 0;
    self->gravity = 0;
    set_animation(self, 1);
    SP_CUR_MAIN_OBJ->ext.main_48.unk80 = 0x14;
    SP_CUR_MAIN_OBJ->ext.main_48.unk82 = 0;
    if (g_Player.x_pos.i.hi - self->x_pos.i.hi > 0) {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
    SP_CUR_MAIN_OBJ->ext.main_48.collision_result = angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player));
    func_800681C4(self);
}

// sentry_drone_spread_aim
void func_80067DAC(struct MainObj* self)
{
    if (--SP_CUR_MAIN_OBJ->ext.main_48.unk80 == 0) {
        switch ((s8)SP_CUR_MAIN_OBJ->ext.main_48.collision_result & 0xFE) {
        case 2:
        case 4:
        case 6:
            self->unk15 = PLAYER_FACING_RIGHT;
        case 10:
        case 12:
        case 14:
            if ((s8)SP_CUR_MAIN_OBJ->ext.main_48.collision_result >= 0xA) {
                self->unk15 = 0;
            }
            set_animation(self, 4);
            break;
        case 8:
            set_animation(self, 2);
            break;
        case 18:
        case 20:
        case 22:
            self->unk15 = 0;
        case 26:
        case 28:
        case 30:
            if ((s8)SP_CUR_MAIN_OBJ->ext.main_48.collision_result >= 0x1A) {
                self->unk15 = PLAYER_FACING_RIGHT;
            }
            set_animation(self, 5);
            break;
        case 24:
            set_animation(self, 3);
            break;
        case 0:
            self->unk15 = PLAYER_FACING_RIGHT;
            set_animation(self, 1);
            break;
        case 16:
            self->unk15 = 0;
            set_animation(self, 1);
            break;
        }
        self->unk6++;
    }
}

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

void sentry_drone_spread_end(struct MainObj* self)
{
    self->air_state = -1;
    self->unk5 = 6;
    self->unk6 = 0;
}

void sentry_drone_drop(struct MainObj* self)
{
    sentry_drone_drop_funcs[self->unk6](self);
}

void sentry_drone_drop_start(struct MainObj* self)
{
    self->unk6++;
    self->x_speed = 0;
    self->x_accel = 0;
    self->y_speed = FIXED(2);
    self->gravity = 0;
    set_animation(self, 1);
}

void sentry_drone_drop_move(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void sentry_drone_check_player_near(struct MainObj* self)
{
    s16 max_distance;
    s8 state;

    if ((self->air_state == 0) && ((state = self->unk5) != 4) && (state != 5)) {
        max_distance = sentry_drone_activation_distances[(s8)SP_CUR_MAIN_OBJ->ext.main_0.index];
        if (ABS(g_Player.x_pos.i.hi, self->x_pos.i.hi) <= max_distance) {
            self->unk5 = 4;
            self->unk6 = 0;
        }
    }
}

// sentry_drone_aim

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800681C4(struct MainObj* arg0);
void func_80068340(struct MainObj* arg0);
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800681C4(struct MainObj* arg0)
{
    struct Main48Ext* ext = &SP_CUR_MAIN_OBJ->ext.main_48;

    ext->unk88 = ext->collision_result & 0xFE;
    switch ((u32)((s8)ext->collision_result & 0xFE)) {
    case 0:
        ext->unk86 = 0x1E;
        ext->unk87 = 2;
        break;
    case 2:
    case 4:
    case 6:
        ext->unk86 = 0;
        ext->unk87 = 8;
        break;
    case 8:
        ext->unk86 = 6;
        ext->unk87 = 0xA;
        break;
    case 10:
    case 12:
    case 14:
        ext->unk86 = 8;
        ext->unk87 = 0x10;
        break;
    case 16:
        ext->unk86 = 0xE;
        ext->unk87 = 0x12;
        break;
    case 18:
    case 20:
    case 22:
        ext->unk86 = 0x10;
        ext->unk87 = 0x18;
        break;
    case 24:
        ext->unk86 = 0x16;
        ext->unk87 = 0x1A;
        break;
    case 26:
    case 28:
    case 30:
        ext->unk86 = 0x18;
        ext->unk87 = 0;
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_48_sentry_drone", func_800681C4);
#endif

// sentry_drone_rotate_aim
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80068340(struct MainObj* arg0)
{
    struct Main48Ext* ext = &SP_CUR_MAIN_OBJ->ext.main_48;

    switch ((u32)(s8)(ext->unk82 - 1)) {
    case 0:
    case 4:
        ext->collision_result = ext->unk86;
        break;
    case 2:
    case 6:
        ext->collision_result = ext->unk87;
        break;
    case 1:
    case 3:
    case 5:
    case 7:
        ext->collision_result = ext->unk88;
        break;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_48_sentry_drone", func_80068340);
#endif

void sentry_drone_despawn(struct MainObj* self)
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
        ZeroObjectState((struct ObjectHeader*)self);
    } else {
        despawn_object((struct ObjectHeader*)self);
    }
}

void sentry_drone_wait_for_player(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi - self->x_pos.i.hi >= 0xB0) {
        self->unk15 = PLAYER_FACING_RIGHT;
        self->state = 1;
        self->unk5 = 3;
    }
}

union AnimationStep sentry_drone_anim_0[] = { { 1, 0, 1, 0x00 }, { 1, 0, -1, 0x01 } };

union AnimationStep sentry_drone_anim_1[] = { { 1, 0, 1, 0x02 }, { 1, 1, -1, 0x03 } };

union AnimationStep sentry_drone_anim_2[] = { { 1, 0, 1, 0x0A }, { 1, 1, -1, 0x0B } };

union AnimationStep sentry_drone_anim_3[] = { { 1, 0, 1, 0x0E }, { 1, 1, -1, 0x0F } };

union AnimationStep sentry_drone_anim_4[] = { { 1, 0, 1, 0x04 }, { 1, 1, -1, 0x05 } };

union AnimationStep sentry_drone_anim_5[] = { { 1, 0, 1, 0x0C }, { 1, 1, -1, 0x0D } };

union AnimationStep sentry_drone_anim_6[] = {
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 2, 0, -3, 0x13 },
};

union AnimationStep sentry_drone_anim_7[] = {
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x15 },
    { 1, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 3, 0, 1, 0x18 },
    { 4, 0, 1, 0x19 },
    { 5, 0, 0, 0x1A },
};

union AnimationStep sentry_drone_anim_8[] = { { 1, 0, 0, 0x1B } };

union AnimationStep sentry_drone_anim_9[] = { { 1, 0, 0, 0x1C } };

union AnimationStep sentry_drone_anim_10[] = { { 1, 0, 0, 0x1D } };

union AnimationStep sentry_drone_anim_11[] = { { 1, 0, 0, 0x1E } };

union AnimationStep sentry_drone_anim_12[] = { { 1, 0, 0, 0x1F } };

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

#ifndef MMX4_WIN32
u8 D_800FFB5C[4] = { 0, 0, 13, 21 };
#endif
