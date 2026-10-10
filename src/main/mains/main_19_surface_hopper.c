// MainObj, main_object_update_funcs[19]
// 8005284C..8005458C
#include "common.h"
#include "func_tables.h"

extern u8 surface_hopper_debris[8];
extern void (*surface_hopper_step_funcs[6])();

void surface_hopper_update(struct MainObj* self)
{
    if (self->unk2 < 3) {
        surface_hopper_state_funcs[self->state](self);
    } else {
        surface_hopper_launched_state_funcs[self->state](self);
    }
}

// surface_hopper_init
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_800528BC);

// surface_hopper_main
void func_80052A68(struct MainObj* self)
{
    s32 collision;
    s16 x;
    s16 y;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    surface_hopper_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    collision = func_8002DD04(self);
    if (collision < 0) {
        self->x_speed = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->gravity = 0;
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(8, surface_hopper_debris, self);
        x = self->x_pos.i.hi;
        y = self->y_pos.i.hi;
        if (SP_CUR_MAIN_OBJ->ext.main_19.animation_index < 2) {
            if (self->unk15 != 0) {
                func_800BF638(BASE_OBJECT(self), 0xC, x - 0x10, y);
            } else {
                func_800BF638(BASE_OBJECT(self), 0xC, x + 0x10, y);
            }
        } else {
            func_800BF638(BASE_OBJECT(self), 0xC, x, y + 0x10);
        }
        self->state = 2;
        return;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state = 2;
    }
}

void surface_hopper_appear(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->unk6 = 1;
        set_animation(
            self, surface_hopper_appear_animations[SP_CUR_MAIN_OBJ->ext.main_19.animation_index]);
        return;
    }

    if (self->animation_step.fields.relative_step < 0) {
        self->unk5 = 2;
        self->unk6 = 0;
        SP_CUR_MAIN_OBJ->ext.main_19.unk80 = get_random() & 1;
    }

    animate_object(ANIMATED_OBJECT(self));
}

void surface_hopper_crawl(struct MainObj* self)
{
    self->unk7C++;
    surface_hopper_crawl_funcs[self->unk6](self);
}

void surface_hopper_fly(struct MainObj* self)
{
    move_object((struct MovingObj*)self);
    CollisionRelated((struct PlayerObj*)self);
    if (self->collision_flags != 0) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

// surface_hopper_crawl_start
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_80052CB8);

// surface_hopper_crawl_move
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_80052E94);

void surface_hopper_crawl_turn(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        self->unk6 = 3;
        if (SP_CUR_MAIN_OBJ->ext.main_19.animation_index < 2) {
            set_animation(self, 0xB);
        } else {
            set_animation(self, 0xA);
        }
    }
    animate_object(ANIMATED_OBJECT(self));
}

void surface_hopper_crawl_turn_end(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        self->unk6 = 0;
        SP_CUR_MAIN_OBJ->ext.main_19.unk80 ^= 1;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void surface_hopper_crawl_attach(struct MainObj* self)
{
    s32 animation;
    struct MainObj* current;

    if (self->animation_step.fields.relative_step < 0) {
        current = SP_CUR_MAIN_OBJ;
        if (current->ext.main_19.animation_index < 2) {
            animation = current->ext.main_19.unk80 == 0 ? 8 : 9;
            self->gravity = 0;
            self->x_speed = 0;
            self->x_accel = 0;
        } else {
            animation = 7;
            self->y_speed = 0;
            self->gravity = 0;
        }
        self->terrain_box = surface_hopper_attach_terrain_boxes[self->unk2 >> 1];
        set_animation(self, animation);
        self->unk6 = 5;
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
}

// surface_hopper_crawl_wall
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_80053338);

void surface_hopper_crawl_finish(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        self->unk6 = 0;
    } else {
        animate_object(self);
    }
}

void surface_hopper_leap(struct MainObj* self)
{
    surface_hopper_leap_funcs[self->unk6](self);
}

void surface_hopper_leap_start(struct MainObj* self)
{
    self->unk6 = 1;
    self->unk7C = 0;
    set_animation(self,
        surface_hopper_leap_animations[SP_CUR_MAIN_OBJ->ext.main_19.animation_index >> 1]);
}

// surface_hopper_leap_fly
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_8005368C);

// surface_hopper_pick_surface
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_800537E0);

u8 surface_hopper_aim_at_player(struct MainObj* self)
{
    u16 player_x;
    u16 player_y;
    s16 dy;
    s16 dx;
    s8 flags;

    player_x = g_Player.x_pos.u.hi;
    player_y = g_Player.y_pos.u.hi;
    dy = player_y - self->y_pos.u.hi;
    dx = player_x - self->x_pos.u.hi;
    flags = 0;

    if ((dx < 0 ? -dx : dx) < 0x40 || (dy < 0 ? -dy : dy) >= 0x60) {
        flags = 1;
    }
    if ((dx < 0 ? -dx : dx) >= 0x80) {
        flags |= 2;
    }

    set_velocity_from_angle(MOVING_OBJECT(self),
        angle_to_object(OBJECT_HEADER(self), OBJECT_HEADER(&g_Player)) & 0xFF);
    return flags;
}

u8 surface_hopper_probe_collision(struct PlayerObj* self, s16 arg1, s16 arg2)
{
    s32 saved_x_pos;
    s32 saved_y_pos;
    s32 saved_unk18;
    s32 saved_unk1C;
    u8 result;

    saved_x_pos = self->x_pos.val;
    saved_y_pos = self->y_pos.val;
    saved_unk18 = self->unk18.val;
    saved_unk1C = self->unk1C.val;
    self->unk18.val = saved_x_pos;
    self->unk1C.val = saved_y_pos;
    self->x_pos.u.hi = self->x_pos.u.hi + arg1;
    self->y_pos.u.hi = self->y_pos.u.hi + arg2;
    CollisionRelated(self);
    self->x_pos.val = saved_x_pos;
    self->y_pos.val = saved_y_pos;
    self->unk18.val = saved_unk18;
    self->unk1C.val = saved_unk1C;
    result = self->unk70;
    self->unk70 = 0;
    return result;
}

u8 surface_hopper_probe_tile(struct PlayerObj* self, s16 arg1, s16 arg2)
{
    arg1 = self->x_pos.i.hi + arg1;
    arg2 = self->y_pos.i.hi + arg2;
    return func_8002D724(self, arg1, arg2);
}

// surface_hopper_check_surface
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_80053B54);

void surface_hopper_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

// surface_hopper_launched_init
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_80053D24);

// surface_hopper_launched_main
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_80053EB8);

// surface_hopper_launched_crawl
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_8005402C);

void surface_hopper_set_launch(struct MainObj* self)
{
    s32 index;

    index = (SP_CUR_MAIN_OBJ->ext.main_19.animation_index << 2) + SP_CUR_MAIN_OBJ->ext.main_19.unk80;
    self->x_speed = surface_hopper_launch_x_speeds[index] << 16;
    self->y_speed = surface_hopper_launch_y_speeds[index] << 16;
    self->unk15 = surface_hopper_launch_facings[index];
    set_animation(self, surface_hopper_launch_animations[index]);
    self->hurt_box = surface_hopper_launch_hurt_boxes[SP_CUR_MAIN_OBJ->ext.main_19.unk80];
    self->attack_box = surface_hopper_launch_attack_boxes[SP_CUR_MAIN_OBJ->ext.main_19.unk80];
    self->terrain_box = surface_hopper_launch_terrain_boxes[SP_CUR_MAIN_OBJ->ext.main_19.unk80];
}

void surface_hopper_launch(struct MainObj* self)
{
    if (self->unk6 == 0) {
        surface_hopper_set_launch(self);
        self->unk6 = 1;
        self->unk7C = 0x1E;
        return;
    }
    self->unk7C -= 1;
    if (self->unk7C == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

union AnimationStep surface_hopper_anim_0[] = {
    { 0x00000001 },
};

union AnimationStep surface_hopper_anim_1[] = {
    { 0x01000001 },
};

union AnimationStep surface_hopper_anim_2[] = {
    { 0x0001000A },
    { 0x02010008 },
    { 0x03010008 },
    { 0x04010008 },
    { 0x05010009 },
    { 0x05010101 },
    { 0x06010002 },
    { 0x07010002 },
    { 0x00010002 },
    { 0x08010002 },
    { 0x00010002 },
    { 0x09010002 },
    { 0x00010002 },
    { 0x08010002 },
    { 0x00F30002 },
};

union AnimationStep surface_hopper_anim_3[] = {
    { 0x0101000A },
    { 0x0A010008 },
    { 0x0B010008 },
    { 0x0C010008 },
    { 0x0D010009 },
    { 0x0D010101 },
    { 0x0E010002 },
    { 0x0F010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x11010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01F30002 },
};

union AnimationStep surface_hopper_anim_4[] = {
    { 0x0101000A },
    { 0x40010008 },
    { 0x41010008 },
    { 0x42010008 },
    { 0x43010009 },
    { 0x43010101 },
    { 0x44010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x0F010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x0F010002 },
    { 0x01F30002 },
};

union AnimationStep surface_hopper_anim_5[] = {
    { 0x00010002 },
    { 0x12010002 },
    { 0x13010002 },
    { 0x14010002 },
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x17010002 },
    { 0x18F70002 },
};

union AnimationStep surface_hopper_anim_6[] = {
    { 0x01010002 },
    { 0x19010002 },
    { 0x1A010002 },
    { 0x1B010002 },
    { 0x1C010002 },
    { 0x1D010002 },
    { 0x1E010002 },
    { 0x1F010002 },
    { 0x1E010002 },
    { 0x1FF70002 },
};

union AnimationStep surface_hopper_anim_7[] = {
    { 0x18010003 },
    { 0x21010003 },
    { 0x20FE0003 },
};

union AnimationStep surface_hopper_anim_8[] = {
    { 0x1F010003 },
    { 0x22010003 },
    { 0x23FE0003 },
};

union AnimationStep surface_hopper_anim_9[] = {
    { 0x1F010003 },
    { 0x23010003 },
    { 0x22FE0003 },
};

union AnimationStep surface_hopper_anim_10[] = {
    { 0x1801000A },
    { 0x15010002 },
    { 0x14010002 },
    { 0x13010002 },
    { 0x00010002 },
    { 0x13010002 },
    { 0x00FA000A },
};

union AnimationStep surface_hopper_anim_11[] = {
    { 0x1F01000A },
    { 0x1C010002 },
    { 0x1B010002 },
    { 0x1A010002 },
    { 0x01010002 },
    { 0x1A010002 },
    { 0x01FA000A },
};

union AnimationStep surface_hopper_anim_12[] = {
    { 0x24010006 },
    { 0x25010006 },
    { 0x26010006 },
    { 0x27010003 },
    { 0x28010012 },
    { 0x29010003 },
    { 0x2A010003 },
    { 0x2B010002 },
    { 0x29010003 },
    { 0x2A010103 },
    { 0x2B010002 },
    { 0x2801000F },
    { 0x27010003 },
    { 0x26010006 },
    { 0x25010006 },
    { 0x24F10006 },
};

union AnimationStep surface_hopper_anim_13[] = {
    { 0x2C010006 },
    { 0x2D010006 },
    { 0x2E010006 },
    { 0x2F010003 },
    { 0x30010012 },
    { 0x31010003 },
    { 0x32010003 },
    { 0x33010002 },
    { 0x31010003 },
    { 0x32010103 },
    { 0x33010002 },
    { 0x3001000F },
    { 0x2F010003 },
    { 0x2E010006 },
    { 0x2D010006 },
    { 0x2CF10006 },
};

union AnimationStep surface_hopper_anim_14[] = {
    { 0x06010102 },
    { 0x07010002 },
    { 0x00010002 },
    { 0x08010002 },
    { 0x00010002 },
    { 0x09010002 },
    { 0x00010002 },
    { 0x08010002 },
    { 0x00F80002 },
};

union AnimationStep surface_hopper_anim_15[] = {
    { 0x0E010102 },
    { 0x0F010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x11010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01F80002 },
};

union AnimationStep surface_hopper_anim_16[] = {
    { 0x44010102 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x0F010002 },
    { 0x01010002 },
    { 0x10010002 },
    { 0x01010002 },
    { 0x0F010002 },
    { 0x01F80002 },
};

union AnimationStep surface_hopper_anim_17[] = {
    { 0x34010002 },
    { 0x35010001 },
    { 0x36010002 },
    { 0x37FD0001 },
};

union AnimationStep surface_hopper_anim_18[] = {
    { 0x38000001 },
};

union AnimationStep surface_hopper_anim_19[] = {
    { 0x39000001 },
};

union AnimationStep surface_hopper_anim_20[] = {
    { 0x3A000001 },
};

union AnimationStep surface_hopper_anim_21[] = {
    { 0x3B000001 },
};

union AnimationStep surface_hopper_anim_22[] = {
    { 0x3C000001 },
};

union AnimationStep surface_hopper_anim_23[] = {
    { 0x3D000001 },
};

union AnimationStep surface_hopper_anim_24[] = {
    { 0x3E000001 },
};

union AnimationStep surface_hopper_anim_25[] = {
    { 0x3F000001 },
};

union AnimationStep surface_hopper_anim_26[] = {
    { 0x45010003 },
    { 0x46010003 },
    { 0x47FE0003 },
};

union AnimationStep* surface_hopper_animations[27] = {
    surface_hopper_anim_0,
    surface_hopper_anim_1,
    surface_hopper_anim_2,
    surface_hopper_anim_3,
    surface_hopper_anim_4,
    surface_hopper_anim_5,
    surface_hopper_anim_6,
    surface_hopper_anim_7,
    surface_hopper_anim_8,
    surface_hopper_anim_9,
    surface_hopper_anim_10,
    surface_hopper_anim_11,
    surface_hopper_anim_12,
    surface_hopper_anim_13,
    surface_hopper_anim_14,
    surface_hopper_anim_15,
    surface_hopper_anim_16,
    surface_hopper_anim_17,
    surface_hopper_anim_18,
    surface_hopper_anim_19,
    surface_hopper_anim_20,
    surface_hopper_anim_21,
    surface_hopper_anim_22,
    surface_hopper_anim_23,
    surface_hopper_anim_24,
    surface_hopper_anim_25,
    surface_hopper_anim_26,
};

u8 surface_hopper_debris[8] = { 18, 19, 20, 21, 22, 23, 24, 25 };

struct Unk_unk68 D_800FC710 = { 0, -9, 27, 18 };

struct Unk_unk68 D_800FC714 = { -10, 0, 20, 25 };

struct Unk_unk68 D_800FC718 = { 0, -16, 39, 30 };

struct Unk_unk68 D_800FC71C = { -18, 0, 35, 36 };

struct Unk_unk68 D_800FC720 = { 22, 0, 22, 18 };

struct Unk_unk68 D_800FC724 = { 0, 21, 18, 21 };

struct Unk_unk68 D_800FC728 = { 16, 0, 16, 16 };

struct Unk_unk68 D_800FC72C = { 0, 16, 16, 16 };

struct Unk_unk68 D_800FC730 = { 0, -16, 16, 16 };

struct Unk_unk68 D_800FC734 = { -10, -25, 20, 25 };

struct Unk_unk68 D_800FC738 = { -18, -35, 35, 35 };

struct Unk_unk68* surface_hopper_attach_terrain_boxes[2] = {
    &D_800FC720,
    &D_800FC724,
};

struct Unk_unk68* D_800FC744[2] = {
    &D_800FC718,
    &D_800FC71C,
};

struct Unk_unk68* D_800FC74C[2] = {
    &D_800FC710,
    &D_800FC714,
};

struct Unk_unk68* surface_hopper_launch_hurt_boxes[4] = {
    &D_800FC738,
    &D_800FC718,
    &D_800FC71C,
    &D_800FC718,
};

struct Unk_unk68* surface_hopper_launch_attack_boxes[4] = {
    &D_800FC734,
    &D_800FC710,
    &D_800FC714,
    &D_800FC710,
};

struct Unk_unk68* surface_hopper_launch_terrain_boxes[4] = {
    &D_800FC730,
    &D_800FC728,
    &D_800FC72C,
    &D_800FC728,
};

void (*surface_hopper_state_funcs[3])() = {
    func_800528BC,
    func_80052A68,
    surface_hopper_despawn,
};

void (*surface_hopper_launched_state_funcs[3])() = {
    func_80053D24,
    func_80053EB8,
    surface_hopper_despawn,
};

void (*surface_hopper_step_funcs[6])() = {
    enemy_hit_reaction,
    surface_hopper_appear,
    surface_hopper_crawl,
    surface_hopper_crawl,
    surface_hopper_leap,
    surface_hopper_fly,
};

u8 surface_hopper_appear_animations[4] = { 0x0E, 0x0F, 0x10, 0x00 };

void (*surface_hopper_crawl_funcs[7])() = {
    func_80052CB8,
    func_80052E94,
    surface_hopper_crawl_turn,
    surface_hopper_crawl_turn_end,
    surface_hopper_crawl_attach,
    func_80053338,
    surface_hopper_crawl_finish,
};

u8 D_800FC7D4[4] = { 0x03, 0x04, 0x00, 0x00 };

u8 D_800FC7D8[4] = { 0x00, 0x40, 0x00, 0x00 };

void (*surface_hopper_leap_funcs[2])() = {
    surface_hopper_leap_start,
    func_8005368C,
};

u8 surface_hopper_leap_animations[4] = { 0x0D, 0x0C, 0x00, 0x00 };

s16 D_800FC7E8[6] = {
    (s16)0xFFE2,
    (s16)0x0000,
    (s16)0x001E,
    (s16)0x0000,
    (s16)0x0000,
    (s16)0x001C,
};

void (*surface_hopper_launched_step_funcs[6])() = {
    enemy_hit_reaction,
    surface_hopper_launch,
    func_8005402C,
    func_8005402C,
    func_8005402C,
    surface_hopper_fly,
};

u8 D_800FC80C[8] = { 0x02, 0x08, 0x01, 0x04, 0x01, 0x04, 0x02, 0x08 };

s16 surface_hopper_launch_x_speeds[8] = {
    (s16)0xFFFE,
    (s16)0x0000,
    (s16)0x0002,
    (s16)0x0000,
    (s16)0x0002,
    (s16)0x0000,
    (s16)0xFFFE,
    (s16)0x0000,
};

s16 surface_hopper_launch_y_speeds[8] = {
    (s16)0x0000,
    (s16)0xFFFE,
    (s16)0x0000,
    (s16)0x0002,
    (s16)0x0000,
    (s16)0x0002,
    (s16)0x0000,
    (s16)0xFFFE,
};

u8 surface_hopper_launch_facings[8] = { 0x00, 0x40, 0x40, 0x00, 0x40, 0x40, 0x00, 0x00 };

u8 surface_hopper_launch_animations[8] = { 0x1A, 0x09, 0x07, 0x08, 0x1A, 0x08, 0x07, 0x09 };
