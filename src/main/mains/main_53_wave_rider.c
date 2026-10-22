// MainObj, main_object_update_funcs[53]
// 8006AF70..8006BB00
#include "common.h"
#include "main/mains/main_53_wave_rider.h"
#include "main/misc/misc_00_static_sprite.h"
#include "main/1CF60.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"
#include "main/objects.h"

#ifdef MMX4_PC
#include "main/visuals/visual_08_ice_shard.h"
#endif

extern struct Unk_unk68 wave_rider_body_hurt_box;
extern struct Unk_unk68 wave_rider_rider_hurt_box[2];
extern u8 wave_rider_debris[8];
extern u8 wave_rider_rider_debris[8];

// wave_rider_wait_funcs
extern void (*wave_rider_wait_funcs[])(struct MainObj*);

// wave_rider_step_funcs
extern void (*wave_rider_step_funcs[])(struct MainObj*);
void wave_rider_idle(struct MainObj* arg0);

void wave_rider_catch_up(struct MainObj* arg0);
void wave_rider_leap(struct MainObj* arg0);
void wave_rider_air(struct MainObj* arg0);

// wave_rider_state_funcs
extern void (*wave_rider_state_funcs[])(struct MainObj*);
void wave_rider_wait(struct MainObj* arg0);
void wave_rider_main(struct MainObj*);
void wave_rider_despawn(struct MainObj* arg0);

// wave_rider_init
#ifdef MMX4_PC
void func_8006AF70(struct MainObj* arg0);
void func_8006B2A4(struct MainObj* arg0);
void func_8006B398(struct MainObj* arg0);
void func_8006B5F8(struct MainObj* arg0);
void func_8006B6B0(struct MainObj* arg0);
extern union AnimationStep* wave_rider_animations[27];
extern struct Unk_unk68 wave_rider_terrain_box;
extern struct Unk_unk68 wave_rider_attack_box;
extern struct Unk_unk68 D_80107878[];
void wave_rider_move(struct MainObj*);
s32 wave_rider_check_camera(struct MainObj*);
#endif

#ifdef MMX4_PC
void func_8006AF70(struct MainObj* arg0)
{
    struct ShotObj* shot;
    struct VisualObj* visual;

    arg0->ext.main_53.unk84 = 0;
    switch (arg0->unk2) {
    case 0:
    case 1:
    case 2:
        arg0->x_speed = 0x80000;
        arg0->unk5 = 1;
        break;
    case 3:
        arg0->x_speed = 0x54000;
        arg0->unk5 = 2;
        arg0->state++;
        break;
    default:
        arg0->x_speed = 0x54000;
        arg0->unk5 = 5;
        arg0->state++;
        break;
    }
    arg0->unk15 = arg0->unk2 == 4 ? 0 : 0x40;
    arg0->ext.main_53.unk80 = func_8002D724(PLAYER_OBJECT(arg0), arg0->x_pos.i.hi,
        (s16)(arg0->y_pos.i.hi + 0x20));
    arg0->animation_table = (const u8* const*)wave_rider_animations;
    arg0->terrain_box = &wave_rider_terrain_box;
    arg0->attack_box = &wave_rider_attack_box;
    arg0->unk7C = 0x3C;
    arg0->collision_data = D_80107878;
    arg0->unk16 = 5;
    arg0->invincibility_timer = 0;
    arg0->unk62 = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;
    arg0->hp = 6;
    arg0->contact_damage = 5;
    arg0->air_state = 0;
    arg0->bg_offset = g_Player.bg_offset;
    set_animation(arg0, 0);
    if (arg0->unk2 == 0) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0x1C;
            shot->unk2 = 0;
            shot->unk7C = WEAPON_OBJECT(arg0);
        }
    }
    visual = find_free_visual_obj();
    if (visual != NULL) {
        visual->active = 0x41;
        visual->id = 0x15;
        visual->unk50 = PLAYER_OBJECT(arg0);
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_53_wave_rider", func_8006AF70);
#endif

void wave_rider_wait_offscreen(struct MainObj* self)
{
    if (self->x_pos.val < background_objects[self->bg_offset].x_pos.val - 0x20) {
        if (self->unk2 == 2) {
            self->unk5 = 5;
        } else {
            self->unk5 = 2;
        }
        self->state++;
    }
}

void wave_rider_wait(struct MainObj* self)
{
    wave_rider_wait_funcs[self->unk5](self);
}

void wave_rider_idle(struct MainObj* self)
{
}

// wave_rider_probe_tile
u8 func_8006B1C4(struct MainObj* self, u8 side)
{
    s16 x;
    s16 y;
    u8 tile;

    if (self->unk15 == 0) {
        x = self->x_pos.u.hi + (s8)(u8)self->terrain_box->unk0;
    } else {
        x = self->x_pos.u.hi - (s8)(u8)self->terrain_box->unk0;
    }
    y = self->terrain_box->unk3 + (self->y_pos.u.hi + (s8)(u8)self->terrain_box->unk1);
    y += 1;
    if (side != 0) {
        y -= 16;
    }
scan:
    tile = func_8002D724(PLAYER_OBJECT(self), x, y);
    if (tile == 0x10) {
        y -= 16;
        goto scan;
    }
    return tile;
}

// wave_rider_float
#ifdef MMX4_PC
void func_8006B2A4(struct MainObj* arg0)
{
    struct Main53Ext* ext = &arg0->ext.main_53;

    ext->unk81 = func_8006B1C4(arg0, 0);
    arg0->air_state = 0;
    if (ext->unk81 == ext->unk80) {
        animate_object(ANIMATED_OBJECT(arg0));
        return;
    }
    switch (ext->unk81) {
    case 0:
        set_animation(arg0, 2);
        arg0->y_speed = 0x68000;
        arg0->gravity = 0x5000;
        arg0->air_state = 1;
        arg0->unk6++;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        set_animation(arg0, 2);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        set_animation(arg0, 1);
        break;
    case 0x38:
        set_animation(arg0, 0);
        break;
    }
    ext->unk80 = ext->unk81;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_53_wave_rider", func_8006B2A4);
#endif

// wave_rider_bob
#ifdef MMX4_PC
void func_8006B398(struct MainObj* arg0)
{
    struct Main53Ext* ext = &arg0->ext.main_53;
    u8 tile;
    s16 x;
    s16 y;

    animate_object(ANIMATED_OBJECT(arg0));
    tile = func_8006B1C4(arg0, 0);
    ext->unk81 = tile;
    if (arg0->unk7E != 0) {
        arg0->unk7E--;
        return;
    }
    if (tile == 0)
        return;
    if (ext->unk84 != 0)
        arg0->x_speed = arg0->x_pos.val < background_objects[arg0->bg_offset].x_pos.val + 0x400000
            ? 0x80000
            : 0x50000;
    else
        arg0->x_speed = arg0->unk2 == 4 ? 0x10000 : 0x60000;
    arg0->x_accel = 0;
    arg0->air_state = 0;
    arg0->unk6 = 0;
    set_animation(arg0, 0);
    if (ext->unk81 == 0x24)
        return;
    x = arg0->x_pos.i.hi;
    y = arg0->y_pos.i.hi;
    if (arg0->unk15 != 0)
        func_800B10E4(2, (s16)(x - 0x18), (s16)(y + 9), (s16)(x + 0xA), (s16)(y + 0x19), 0x10);
    else
        func_800B10E4(2, (s16)(x + 0x18), (s16)(y + 9), (s16)(x - 0xA), (s16)(y + 0x19), 0x10);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_53_wave_rider", func_8006B398);
#endif

void wave_rider_move(struct MainObj* self)
{
    if (self->unk6 == 0) {
        func_8006B2A4(self);
    } else {
        func_8006B398(self);
    }
    move_with_gravity(self);
}

s32 wave_rider_check_camera(struct MainObj* self)
{
    s32 background_x;
    s32 x;
    s32 distance;

    self->ext.main_53.unk84 = 1;
    wave_rider_move(self);
    if (self->air_state != 0) {
        return 0;
    }
    x = self->x_pos.val - FIXED(64);
    background_x = background_objects[self->bg_offset].x_pos.val;
    distance = x - background_x;
    if (distance < 0) {
        distance = background_x - x;
    }
    return distance <= 0x1FFFF;
}

// wave_rider_ride
#ifdef MMX4_PC
void func_8006B5F8(struct MainObj* arg0)
{
    if (wave_rider_check_camera(arg0) != 0) {
        switch (arg0->unk2) {
        case 0:
            arg0->x_speed = 0x60000;
            arg0->unk5 = 3;
            arg0->unk7C = 0x28;
            break;
        case 1:
            set_animation(arg0, 2);
            arg0->x_speed = 0x90000;
            arg0->y_speed = 0x80000;
            arg0->gravity = 0x5000;
            arg0->unk5 = 2;
            arg0->air_state = 1;
            arg0->unk6 = 1;
            arg0->unk7E = 2;
            break;
        }
    }
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x20);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_53_wave_rider", func_8006B5F8);
#endif

// wave_rider_ride_back
#ifdef MMX4_PC
void func_8006B6B0(struct MainObj* arg0)
{
    u8 tile;
    s32 animation;

    arg0->ext.main_53.unk84 = 0;
    wave_rider_move(arg0);
    if (arg0->unk7C != 0) {
        arg0->unk7C--;
        update_on_screen(BASE_OBJECT(arg0), 0x30, 0x20);
        return;
    }
    if (arg0->air_state != 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x30, 0x20);
        return;
    }
    tile = func_8006B1C4(arg0, 0);
    arg0->ext.main_53.unk81 = tile;
    if (tile == 0)
        animation = 3;
    else if (tile < 5)
        animation = 5;
    else if (tile < 9)
        animation = 4;
    else
        animation = 3;
    set_animation(arg0, animation);
    arg0->unk5 = 4;
    arg0->x_speed = 0x80000;
    arg0->x_accel = 0;
    arg0->air_state = 1;
    update_on_screen(BASE_OBJECT(arg0), 0x30, 0x20);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_53_wave_rider", func_8006B6B0);
#endif

void wave_rider_catch_up(struct MainObj* self)
{
    if (self->x_pos.val - background_objects[self->bg_offset].x_pos.val > FIXED(160)) {
        self->x_speed = FIXED(5);
        self->unk5 = 2;
        set_animation(self, 0);
    }
    self->ext.main_53.unk81 = func_8006B1C4(self, 0);
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    update_on_screen(BASE_OBJECT(self), 0x30, 0x20);
}

void wave_rider_leap(struct MainObj* self)
{
    set_animation(self, 2);
    if (self->unk2 == 4) {
        self->x_speed = FIXED(-1);
    } else {
        self->x_speed = FIXED(11);
    }
    self->y_speed = FIXED(8);
    self->gravity = FIXED(0.3125);
    self->air_state = 1;
    self->unk5 = 6;
    update_on_screen(BASE_OBJECT(self), 0x30, 0x20);
}

void wave_rider_air(struct MainObj* self)
{
    wave_rider_move(self);
    update_on_screen(BASE_OBJECT(self), 0x30, 0x20);
}

void wave_rider_main(struct MainObj* self)
{
    s8 destroyed;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    self->unk65 = self->ext.main_53.unk82;
    self->hurt_box = &wave_rider_body_hurt_box;
    destroyed = func_8002DD04(self) < 0;
    if (!destroyed) {
        self->ext.main_53.unk82 = self->unk65;
        self->hurt_box = wave_rider_rider_hurt_box;
        self->unk65 = self->ext.main_53.unk83;
        destroyed = func_8002DD04(self) < 0;
    }
    if (destroyed) {
        self->unk5 = 0;
        self->state++;
        self->unk42 &= 0x7FFF;
        spawn_debris(8, wave_rider_debris, self);
        spawn_debris(7, wave_rider_rider_debris, self);
        spawn_explosion(BASE_OBJECT(self));
        return;
    }
    self->ext.main_53.unk83 = self->unk65;
    wave_rider_step_funcs[self->unk5](self);
    if ((u8)func_8006B1C4(self, 1) == 0x24) {
        if (self->ext.main_53.unk85 == 0) {
            self->x_pos.i.hi -= 8;
            self->y_pos.i.hi += 0x10;
            spawn_common_effect(self, 4);
            self->ext.main_53.unk85 = 2;
            self->x_pos.i.hi += 8;
            self->y_pos.i.hi -= 0x10;
        } else {
            self->ext.main_53.unk85--;
        }
    } else {
        self->ext.main_53.unk85 = 0;
    }
    CollisionRelated(PLAYER_OBJECT(self));
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) != 0) {
        self->unk5 = 0;
        self->state++;
    }
}

void wave_rider_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void wave_rider_update(struct MainObj* self)
{
    wave_rider_state_funcs[self->state](self);
}

struct Unk_unk68 wave_rider_terrain_box = { -7, 15, 33, 11 };

struct Unk_unk68 wave_rider_body_hurt_box = { -40, -5, 50, 29 };

struct Unk_unk68 wave_rider_rider_hurt_box[2] = {
    { -14, -16, 39, 39 },
    { -40, -16, 65, 41 },
};

struct Unk_unk68 wave_rider_attack_box = { -30, -10, 49, 30 };

union AnimationStep wave_rider_anim_0[] = {
    { 0x00010002 },
    { 0x04010002 },
    { 0x05010006 },
    { 0x04010001 },
    { 0x00010001 },
    { 0x06010003 },
    { 0x00000101 },
};

union AnimationStep wave_rider_anim_1[] = {
    { 0x01010002 },
    { 0x07010002 },
    { 0x08010006 },
    { 0x07010001 },
    { 0x01010001 },
    { 0x09010003 },
    { 0x01000001 },
};

union AnimationStep wave_rider_anim_2[] = {
    { 0x02010002 },
    { 0x0A010002 },
    { 0x0B010006 },
    { 0x0A010001 },
    { 0x02010001 },
    { 0x0C010003 },
    { 0x02000101 },
};

union AnimationStep wave_rider_anim_3[] = {
    { 0x00010002 },
    { 0x02010002 },
    { 0x03000008 },
};

union AnimationStep wave_rider_anim_4[] = {
    { 0x01010002 },
    { 0x00010002 },
    { 0x02010002 },
    { 0x03000008 },
};

union AnimationStep wave_rider_anim_5[] = {
    { 0x02010002 },
    { 0x03000008 },
};

union AnimationStep wave_rider_anim_11[] = {
    { 0x0D010001 },
    { 0x0E010001 },
    { 0x0FFE0001 },
};

union AnimationStep wave_rider_anim_6[] = {
    { 0x10010002 },
    { 0x11010001 },
    { 0x12010001 },
    { 0x13010001 },
    { 0x14010002 },
    { 0x15010001 },
    { 0x15FA0001 },
};

union AnimationStep wave_rider_anim_7[] = {
    { 0x16010002 },
    { 0x17010001 },
    { 0x18010001 },
    { 0x19010001 },
    { 0x1A010002 },
    { 0x1B010001 },
    { 0x1BFA0001 },
};

union AnimationStep wave_rider_anim_8[] = {
    { 0x1C010002 },
    { 0x1D010001 },
    { 0x1E010001 },
    { 0x1F010001 },
    { 0x20010002 },
    { 0x21010001 },
    { 0x21FA0001 },
};

union AnimationStep wave_rider_anim_9[] = {
    { 0x22010002 },
    { 0x23010001 },
    { 0x24010001 },
    { 0x25010001 },
    { 0x26010002 },
    { 0x27010001 },
    { 0x27FA0001 },
};

union AnimationStep wave_rider_anim_10[] = {
    { 0x28010003 },
    { 0x29010002 },
    { 0x2A010002 },
    { 0x2B010003 },
    { 0x2C010003 },
    { 0x2D010002 },
    { 0x2E010002 },
    { 0x2F010002 },
    { 0x2FF80001 },
};

union AnimationStep wave_rider_anim_12[] = {
    { 0x30000001 },
};

union AnimationStep wave_rider_anim_13[] = {
    { 0x31000001 },
};

union AnimationStep wave_rider_anim_14[] = {
    { 0x32000001 },
};

union AnimationStep wave_rider_anim_15[] = {
    { 0x33000001 },
};

union AnimationStep wave_rider_anim_16[] = {
    { 0x34000001 },
};

union AnimationStep wave_rider_anim_17[] = {
    { 0x35000001 },
};

union AnimationStep wave_rider_anim_18[] = {
    { 0x36000001 },
};

union AnimationStep wave_rider_anim_19[] = {
    { 0x37000001 },
};

union AnimationStep wave_rider_anim_20[] = {
    { 0x38000001 },
};

union AnimationStep wave_rider_anim_21[] = {
    { 0x39000001 },
};

union AnimationStep wave_rider_anim_22[] = {
    { 0x3A000001 },
};

union AnimationStep wave_rider_anim_23[] = {
    { 0x3B000001 },
};

union AnimationStep wave_rider_anim_24[] = {
    { 0x3C000001 },
};

union AnimationStep wave_rider_anim_25[] = {
    { 0x3D000001 },
};

union AnimationStep wave_rider_anim_26[] = {
    { 0x3E000001 },
};

union AnimationStep* wave_rider_animations[27] = {
    wave_rider_anim_0,
    wave_rider_anim_1,
    wave_rider_anim_2,
    wave_rider_anim_3,
    wave_rider_anim_4,
    wave_rider_anim_5,
    wave_rider_anim_6,
    wave_rider_anim_7,
    wave_rider_anim_8,
    wave_rider_anim_9,
    wave_rider_anim_10,
    wave_rider_anim_11,
    wave_rider_anim_12,
    wave_rider_anim_13,
    wave_rider_anim_14,
    wave_rider_anim_15,
    wave_rider_anim_16,
    wave_rider_anim_17,
    wave_rider_anim_18,
    wave_rider_anim_19,
    wave_rider_anim_20,
    wave_rider_anim_21,
    wave_rider_anim_22,
    wave_rider_anim_23,
    wave_rider_anim_24,
    wave_rider_anim_25,
    wave_rider_anim_26,
};

u8 wave_rider_debris[8] = { 12, 13, 14, 15, 16, 17, 18, 19 };

u8 wave_rider_rider_debris[8] = { 20, 21, 22, 23, 24, 25, 26, 0 };

void (*wave_rider_wait_funcs[2])(struct MainObj*) = {
    func_8006AF70,
    wave_rider_wait_offscreen,
};

void (*wave_rider_step_funcs[7])(struct MainObj*) = {
    enemy_hit_reaction,
    wave_rider_idle,
    func_8006B5F8,
    func_8006B6B0,
    wave_rider_catch_up,
    wave_rider_leap,
    wave_rider_air,
};

void (*wave_rider_state_funcs[3])() = {
    wave_rider_wait,
    wave_rider_main,
    wave_rider_despawn,
};
