// MainObj, main_object_update_funcs[32]
// 8005C824..8005D1F4
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_32_bomb_bat.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"

extern u8 bomb_bat_debris[4];

extern struct Unk_unk68* bomb_bat_hurt_boxes[2];

extern s32 bomb_bat_fly_speeds[2];

// bomb_bat_state_funcs
extern void (*bomb_bat_state_funcs[])(struct MainObj*);

void bomb_bat_despawn(struct MainObj*);

// bomb_bat_step_funcs
extern void (*bomb_bat_step_funcs[])(struct MainObj*);
void bomb_bat_resume_step(struct MainObj* arg0);
void bomb_bat_hover(struct MainObj* arg0);
void bomb_bat_drop(struct MainObj* arg0);
void bomb_bat_fly_off(struct MainObj* arg0);
void bomb_bat_flee(struct MainObj* arg0);
void bomb_bat_dive(struct MainObj* arg0);

// bomb_bat_hover_funcs
extern void (*bomb_bat_hover_funcs[])(struct MainObj*);
void bomb_bat_hover_start(struct MainObj*);

// bomb_bat_move_funcs
void bomb_bat_drop_start(struct MainObj*);
void bomb_bat_drop_release(struct MainObj*);
void bomb_bat_fly_off_start(struct MainObj*);
void bomb_bat_fly_off_move(struct MainObj* arg0);
void bomb_bat_flee_start(struct MainObj*);
void bomb_bat_flee_move(struct MainObj* arg0);

void bomb_bat_dive_wait(struct MainObj*);
void bomb_bat_dive_fall(struct MainObj*);
void bomb_bat_face_player(struct MainObj*);

extern void (*bomb_bat_move_funcs[])(struct MainObj*);
extern void (*bomb_bat_dive_funcs[])(struct MainObj*);

void bomb_bat_update(struct MainObj* self)
{
    bomb_bat_state_funcs[self->state](self);
}

// bomb_bat_init
void func_8005C860(struct MainObj* self)
{
    self->active = 0x41;
    self->hp = 3;
    self->contact_damage = 3;
    self->invincibility_timer = 0;
    self->bg_offset = g_Player.bg_offset;
    self->collision_data = (const u16*)D_80107274;
    self->animation_table = (const u8* const*)bomb_bat_animations;
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->hurt_box = (const u8*)&bomb_bat_body_box;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    self->air_state = 0;
    self->terrain_box = NULL;
    self->attack_box = (const u8*)D_800FDC88;
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    set_animation(self, 0);
    self->ext.main_32.unk80 = 0;
    self->ext.main_32.unk84 = 0;
    self->ext.main_32.unk88 = 0;
    self->ext.main_32.unk8C = 0;
    self->ext.main_32.unk90 = 0;
    self->ext.main_32.saved_unk5 = 0;
    self->state++;
    switch (self->unk2) {
    case 0:
        self->unk5 = 2;
        break;
    case 1:
        self->unk5 = 5;
        break;
    default:
        self->unk5 = 6;
        break;
    }
    self->unk6 = 0;
}

void bomb_bat_main(struct MainObj* self)
{
    s32 hit;
    u8 i;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    bomb_bat_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (self->unk5 != 0) {
        self->ext.main_32.saved_unk5 = self->unk5;
    }
    for (i = 0; i < 2 - self->ext.main_32.unk88; i++) {
        self->hurt_box = (const u8*)bomb_bat_hurt_boxes[i];
        hit = func_8002DD04(self);
        if (hit < 0) {
            if (i == 0 && self->ext.main_32.unk88 == 0) {
                bomb_bat_drop_bomb(self);
            }
            spawn_explosion(BASE_OBJECT(self));
            spawn_debris(4, bomb_bat_debris, self);
            drop_item(BASE_OBJECT(self), 8);
            self->state++;
            return;
        }
        if (hit != 0) {
            break;
        }
    }
    if (func_8002B1E8(BASE_OBJECT(self), 0x20, 0x20) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
    } else {
        self->state++;
    }
}

void bomb_bat_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void bomb_bat_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_32.saved_unk5;
}

void bomb_bat_hover(struct MainObj* self)
{
    bomb_bat_face_player(self);
    bomb_bat_hover_funcs[self->unk6](self);
}

void bomb_bat_hover_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->unk7C = 0xC8;
    self->unk6++;
}

// bomb_bat_hover_track

extern s32 D_800FDC98[2];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005CB90(struct MainObj* arg0);
void func_8005CF9C(struct MainObj* arg0);
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_32_bomb_bat", func_8005CB90);
#else
void func_8005CB90(struct MainObj* arg0)
{
    u8 angle;

    animate_object(ANIMATED_OBJECT(arg0));
    move_object(MOVING_OBJECT(arg0));
    angle = angle_to_point(OBJECT_HEADER(arg0), g_Player.x_pos.val, g_Player.y_pos.val - 0x500000);
    set_velocity_from_angle(MOVING_OBJECT(arg0), angle);
    arg0->x_speed += arg0->x_speed / 2;
    if ((g_Player.x_pos.val - arg0->x_pos.val >= 0 ? g_Player.x_pos.val - arg0->x_pos.val : arg0->x_pos.val - g_Player.x_pos.val)
            <= (arg0->x_speed >= 0 ? arg0->x_speed : -arg0->x_speed) + 0x20000
        || --arg0->unk7C == 0) {
        arg0->unk5 = 3;
        arg0->unk6 = 0;
    }
}
#endif

void bomb_bat_drop(struct MainObj* self)
{
    bomb_bat_move_funcs[self->unk6](self);
}

void bomb_bat_drop_start(struct MainObj* self)
{
    set_animation(self, 1);
    self->x_speed = 0;
    self->ext.main_32.unk80 = 5;
    self->hurt_box = (const u8*)&bomb_bat_body_box;
    self->attack_box = (const u8*)&bomb_bat_body_box;
    self->unk6++;
}

void bomb_bat_drop_release(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.main_32.unk80 == 0) {
        self->ext.main_32.unk88 = 1;
        bomb_bat_drop_bomb(self);
        self->ext.main_32.unk80 = 13;
        self->unk6++;
    }
}

void bomb_bat_drop_end(struct MainObj* self)
{
    animate_object((struct AnimatedObj*)self);
    if (--self->ext.main_32.unk80 == 0) {
        set_animation(self, 3);
        self->unk5 = 4;
        self->unk6 = 0;
    }
}

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_32_bomb_bat", bomb_bat_fly_off);
#else
void bomb_bat_fly_off(struct MainObj* self)
{
    bomb_bat_move_funcs[self->unk6 + 2](self);
}
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_32_bomb_bat", bomb_bat_fly_off_start);
#else
void bomb_bat_fly_off_start(struct MainObj* self)
{
    s32* velocity;
    s32 selected;
    u8 step;

    set_animation(self, 3);
    velocity = bomb_bat_fly_speeds;
    if (self->unk15 & PLAYER_FACING_RIGHT) {
        velocity++;
    }
    selected = *velocity;
    step = self->unk6;
    self->y_speed = FIXED(0.3125);
    self->x_speed = selected;
    self->unk6 = step + 1;
}
#endif

void bomb_bat_fly_off_move(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_32_bomb_bat", bomb_bat_flee);
#else
void bomb_bat_flee(struct MainObj* self)
{
    bomb_bat_move_funcs[self->unk6 + 4](self);
}
#endif

#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_32_bomb_bat", bomb_bat_flee_start);
#else
void bomb_bat_flee_start(struct MainObj* self)
{
    s32* velocity;
    s32 selected;

    set_animation(self, 3);
    velocity = bomb_bat_fly_speeds;
    if (self->unk15 & PLAYER_FACING_RIGHT) {
        velocity++;
    }
    selected = *velocity;
    self->attack_box = (const u8*)&bomb_bat_body_box;
    self->y_speed = 0;
    self->ext.main_32.unk88 = 1;
    self->x_speed = selected;
    self->unk6++;
}
#endif

void bomb_bat_flee_move(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
}

void bomb_bat_dive(struct MainObj* self)
{
    bomb_bat_dive_funcs[self->unk6](self);
}

// bomb_bat_dive_start
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_32_bomb_bat", func_8005CF9C);
#else
void func_8005CF9C(struct MainObj* arg0)
{
    u16 spread;

    set_animation(arg0, 3);
    spread = (get_random() << 8) + get_random();
    arg0->x_speed = D_800FDC98[(arg0->unk15 & PLAYER_FACING_RIGHT) != 0];
    if (get_random() & 1)
        arg0->x_speed += spread;
    else
        arg0->x_speed -= spread;
    arg0->x_accel = -0x1000;
    arg0->y_speed = 0x18000;
    arg0->attack_box = (const u8*)&bomb_bat_body_box;
    arg0->ext.main_32.unk88 = 1;
    if (arg0->unk2 == 2) {
        arg0->unk7C = get_random() & 0x3F;
        arg0->unk6++;
    } else {
        arg0->unk6 += 2;
    }
}
#endif

void bomb_bat_dive_wait(struct MainObj* self)
{
    s32 unused[1];
    s16 timer = self->unk7C;
    if (timer == 0) {
        self->unk6++;
    } else {
        self->unk7C = timer - 1;
    }
}

void bomb_bat_dive_fall(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    self->y_speed += 0x100;
}

void bomb_bat_face_player(struct MainObj* self)
{
    if (self->x_pos.val > g_Player.x_pos.val) {
        self->unk15 = 0;
    } else {
        self->unk15 = PLAYER_FACING_RIGHT;
    }
}

void bomb_bat_drop_bomb(struct MainObj* self)
{
    struct ShotObj* temp_v0;

    temp_v0 = find_free_shot_obj();
    if (temp_v0 != NULL) {
        temp_v0->active = 0x41;
        temp_v0->id = 7;
        temp_v0->unk2 = 0;
        temp_v0->unk40 = self->unk40;
        temp_v0->unk42 = self->unk42;
        temp_v0->animation_table = (u32**)self->animation_table;
        temp_v0->unk3C = (u8*)self->sprite_frames;
        temp_v0->bg_offset = self->bg_offset;
        temp_v0->unk15 = self->unk15;
        temp_v0->x_pos.val = self->x_pos.val;
        temp_v0->y_pos.val = self->y_pos.val;
        temp_v0->unk7C = WEAPON_OBJECT(self);
        temp_v0->unk16 = VISUAL_SATURN_LAYER(6);
    }
}

struct Unk_unk68 bomb_bat_body_box = { -11, -10, 21, 23 };

struct Unk_unk68 D_800FDC84 = { -9, 13, 16, 19 };

struct Unk_unk68 D_800FDC88[2] = {
    { -11, -10, 20, 42 },
    { -10, 27, 26, 3 },
};

s32 bomb_bat_fly_speeds[2] = { (s32)0xFFFD0000, (s32)0x00030000 };

s32 D_800FDC98[2] = { (s32)0xFFFC8000, (s32)0x00038000 };

union AnimationStep bomb_bat_anim_0[] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, 1, 0x01 },
    { 4, 0, 1, 0x02 },
    { 3, 0, 1, 0x03 },
    { 3, 0, 1, 0x04 },
    { 5, 0, -5, 0x05 },
};

union AnimationStep bomb_bat_anim_1[] = {
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x03 },
    { 3, 0, 1, 0x08 },
    { 3, 0, 1, 0x09 },
    { 3, 0, 0, 0x0A },
};

union AnimationStep bomb_bat_anim_2[] = {
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x0B },
    { 2, 0, -3, 0x0D },
};

union AnimationStep bomb_bat_anim_3[] = {
    { 5, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x10 },
    { 5, 0, 1, 0x11 },
    { 3, 0, 1, 0x12 },
    { 3, 0, -5, 0x13 },
};

union AnimationStep bomb_bat_anim_4[] = {
    { 1, 0, 0, 0x14 },
};

union AnimationStep bomb_bat_anim_5[] = {
    { 1, 0, 0, 0x15 },
};

union AnimationStep bomb_bat_anim_6[] = {
    { 1, 0, 0, 0x16 },
};

union AnimationStep bomb_bat_anim_7[] = {
    { 1, 0, 0, 0x17 },
};

union AnimationStep* bomb_bat_animations[8] = {
    bomb_bat_anim_0,
    bomb_bat_anim_1,
    bomb_bat_anim_2,
    bomb_bat_anim_3,
    bomb_bat_anim_4,
    bomb_bat_anim_5,
    bomb_bat_anim_6,
    bomb_bat_anim_7,
};

u8 bomb_bat_debris[4] = { 0x04, 0x05, 0x06, 0x07 };

void (*bomb_bat_state_funcs[3])() = {
    func_8005C860,
    bomb_bat_main,
    bomb_bat_despawn,
};

struct Unk_unk68* bomb_bat_hurt_boxes[2] = {
    &bomb_bat_body_box,
    &D_800FDC84,
};

void (*bomb_bat_step_funcs[7])() = {
    enemy_hit_reaction,
    bomb_bat_resume_step,
    bomb_bat_hover,
    bomb_bat_drop,
    bomb_bat_fly_off,
    bomb_bat_flee,
    bomb_bat_dive,
};

void (*bomb_bat_hover_funcs[2])() = {
    bomb_bat_hover_start,
    func_8005CB90,
};

void (*bomb_bat_move_funcs[6])() = {
    bomb_bat_drop_start,
    bomb_bat_drop_release,
    bomb_bat_fly_off_start,
    bomb_bat_fly_off_move,
    bomb_bat_flee_start,
    bomb_bat_flee_move,
};

void (*bomb_bat_dive_funcs[3])() = {
    func_8005CF9C,
    bomb_bat_dive_wait,
    bomb_bat_dive_fall,
};
