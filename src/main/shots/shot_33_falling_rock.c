// ShotObj, shot_object_update_funcs[33]
// 800A03B8..800A16FC
#include "common.h"
#include "main/shots/shot_33_falling_rock.h"
#include "main/1CF60.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/CB184.h"
#include "main/collision.h"
#include "main/misc/misc_02_rubble.h"
#include "main/object_motion.h"
#include "main/objects.h"
#include "main/stage_objects.h"
#include "main/collision_bounds.h"

// falling_rock_state_funcs
extern void (*falling_rock_state_funcs[])(struct ShotObj*);

void func_800A068C(struct ShotObj*);
void falling_rock_a_despawn(struct ShotObj*);

void falling_rock_b_despawn(struct ShotObj*);

void func_800A12EC(struct ShotObj*);
void falling_rock_c_despawn(struct ShotObj*);
#include "weapon_resources.h"

extern union AnimationStep* falling_rock_a_animations[];
extern union AnimationStep* falling_rock_b_animations[];
extern struct Unk_unk68 falling_rock_box_0[];
extern struct Unk_unk68 falling_rock_box_1[];
extern struct Unk_unk68 falling_rock_box_2[];
extern struct Unk_unk68 falling_rock_box_3[];
extern struct Unk_unk68 falling_rock_box_4[];
extern struct Unk_unk68 falling_rock_box_5[];
extern union AnimationStep* falling_rock_c_animations[];
extern u8 falling_rock_debris_2[];
extern u8 falling_rock_debris_3[];
#include "compiler.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

extern u8 falling_rock_debris_0[], falling_rock_debris_1[];
extern u8 falling_rock_debris_4[], falling_rock_debris_5[], falling_rock_debris_6[];
extern union AnimationStep* falling_rock_d_animations[];

void falling_rock_update(struct ShotObj* self)
{
    falling_rock_state_funcs[self->state](self);
}

// falling_rock_a_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
static void shot_33_load_graphics(struct ShotObj* arg0, s32 id);
static void shot_33_spawn_shadow(struct ShotObj* arg0, s8 shadow_kind, s8 unk6, s32 animation);
void func_800A03F4(struct ShotObj* arg0);
void func_800A0A38(struct ShotObj* arg0);
void func_800A0C4C(struct ShotObj* arg0);
void func_800A0FE8(struct ShotObj* arg0);
extern union AnimationStep* falling_rock_a_animations[];
extern struct Unk_unk68 falling_rock_box_0[];
extern struct Unk_unk68 falling_rock_box_3[];
extern ret_u8 func_8002938C(s32);
static void shot_33_load_graphics(struct ShotObj* arg0, s32 id)
{
    s32 resource;

    arg0->bg_offset = g_Player.bg_offset;
    resource = func_8002938C(id);
    arg0->unk40 = OBJECT_STAGE_TEXTURE(resource);
    resource = func_8002938C(id);
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[resource];
    arg0->unk42 = OBJECT_STAGE_CLUT(id);
}
static void shot_33_spawn_shadow(struct ShotObj* arg0, s8 shadow_kind, s8 unk6,
    s32 animation)
{
    struct MiscObj* misc = find_free_misc_obj();

    if (misc == NULL)
        return;
    misc->active = 0x41;
    misc->id = 0x1B;
    misc->unk16 = shadow_kind;
    misc->unk40 = arg0->unk40;
    misc->unk42 = arg0->unk42 & 0x7FFF;
    misc->animation_table = arg0->animation_table;
    misc->unk3C = arg0->unk3C;
    misc->bg_offset = arg0->bg_offset;
    misc->x_pos.val = arg0->x_pos.val;
    misc->y_pos.val = arg0->y_pos.val;
    misc->ext.misc_5.owner = (struct MainObj*)arg0;
    misc->state = 0;
    misc->unk6 = unk6;
    misc->unk7 = 0;
    misc->unk15 = arg0->unk15;
    set_animation(misc, animation);
    arg0->unk7C = (struct WeaponObj*)misc;
}
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800A03F4(struct ShotObj* arg0)
{
    s32 random;

    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk5C = 0xF;
    arg0->on_screen = 1;
    arg0->unk60 = 3;
    arg0->unk42 &= 0x7FFF;
    shot_33_load_graphics(arg0, 0x8E);
    arg0->animation_table = (u32**)falling_rock_a_animations;
    random = get_random();
    random = ((random & 1) << 8) + (get_random() & 0xFF) + 0x40;
    arg0->x_pos.i.hi = background_objects[g_Player.bg_offset].x_pos.i.hi + random;
    arg0->x_vel.val = -0x10000;
    arg0->y_vel.val = -0x10000;
    arg0->unk28 = 0x400;
    arg0->unk2C = 0x400;
    arg0->unk68 = falling_rock_box_3;
    arg0->unk54 = (const u8*)falling_rock_box_0;
    arg0->unk50.data = (const u8*)falling_rock_box_0;
    arg0->unk16 = 1;
    arg0->unk15 = 0;
    arg0->unk62 = 2;
    arg0->y_pos.i.hi = background_objects[g_Player.bg_offset].y_pos.i.hi - 0x40;
    set_animation(arg0, 1);
    shot_33_spawn_shadow(arg0, 0, 0, 0);
    arg0->state = 1;
    arg0->unk5 = 0;
}
#else
INCLUDE_ASM("main/nonmatchings/shots/shot_33_falling_rock", func_800A03F4);
#endif

// falling_rock_a_fall
static MMX4_INLINE s32 falling_rock_tile_attribute(struct PlayerObj* object, s16 x, s16 y)
{
#if defined(MMX4_PC) || defined(MMX4_WIN32)
    return func_8002D724(object, x, y);
#else
    return ((s32(*)(struct PlayerObj*, s16, s16))func_8002D724)(object, x, y);
#endif
}

void func_800A068C(struct ShotObj* self)
{
    u8 collided;
    s32 result;
    s16 collision_x;
    s16 collision_y;
    self->unk42 &= 0x7FFF;
    switch (self->unk5) {
    case 0:
        move_with_gravity(ANIMATED_OBJECT(self));
        animate_object(ANIMATED_OBJECT(self));
        result = falling_rock_tile_attribute((struct PlayerObj*)self, (((u16)self->x_pos.i.hi) + self->unk68->unk0) - self->unk68->unk2, self->unk68->unk3 + (((u16)self->y_pos.i.hi) + self->unk68->unk1));
        collided = result != 0;
        collision_x = (((u16)self->x_pos.i.hi) + self->unk68->unk0) - self->unk68->unk2;
        collision_y = ((u16)self->y_pos.i.hi) + self->unk68->unk1;
        if (falling_rock_tile_attribute((struct PlayerObj*)self, collision_x, collision_y) != 0) {
            collided = 1;
        }
        collision_x = ((u16)self->x_pos.i.hi) + self->unk68->unk0;
        collision_y = self->unk68->unk3 + (((u16)self->y_pos.i.hi) + self->unk68->unk1);
        if (falling_rock_tile_attribute((struct PlayerObj*)self, collision_x, collision_y) != 0) {
            collided = 1;
        }
        if (collided != 0) {
            if (!(background_objects[g_Player.bg_offset].unk34 & 0x10)) {
                start_screen_shake_x(0x10, 6, 2);
            }
            self->x_vel.val = 0;
            self->unk28 = 0;
            self->y_vel.val = 0;
            self->unk2C = 0;
            set_animation(self, 2);
            self->unk5 = 1;
            return;
        }
        func_8002D9BC(self);
        if (func_8002BB80((struct MainObj*)self, (struct MainObj*)(&g_Player)) != 0) {
            set_animation(self, 2);
            self->unk5 = 1;
        }
        result = func_8002DD04((struct MainObj*)self);
        if (result < 0) {
            set_animation(self, 2);
            self->unk5 = 1;
        } else if (((result == 3) || (result == 0xC)) || (result == 0x22)) {
            self->unk84.value = 8;
            set_animation(self, 8);
            self->unk7C->active = 0;
            self->unk7C->on_screen = 0;
            self->unk5 = 2;
        }
        break;

    case 1:
        animate_object(ANIMATED_OBJECT(self));
        if (self->animation_step.fields.event != 0) {
            spawn_debris(5, falling_rock_debris_0, self);
            if (self->on_screen != 0) {
                func_8001540C(2, SATURN_SOUND(0xA0, 0x70), self);
            }
            self->state = 2;
        }
        break;

    case 2:
        if ((--self->unk84.value) == 0) {
            spawn_debris(5, falling_rock_debris_1, self);
            self->state = 2;
        }
        break;
    }

    if ((background_objects[g_Player.bg_offset].y_pos.i.hi + 0x150) < self->y_pos.i.hi) {
        self->state = 2;
        return;
    }
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

void falling_rock_a_despawn(struct ShotObj* self)
{
    self->unk62 = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

// falling_rock_b_init
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_33_falling_rock", func_800A0A38);
#else
void func_800A0A38(struct ShotObj* arg0)
{
    struct MiscObj* misc;

    arg0->on_screen = 1;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk5C = 0x7F;
    arg0->unk60 = 6;
    arg0->unk42 &= 0x7FFF;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(0x8C));
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(0x8C)];
    arg0->unk42 = OBJECT_STAGE_CLUT(0x8C);
    arg0->animation_table = (u32**)falling_rock_b_animations;
    arg0->unk16 = 0;
    if (arg0->unk15 != 0)
        arg0->x_vel.val = -0x38000;
    else
        arg0->x_vel.val = 0x38000;
    arg0->y_vel.val = 0;
    arg0->unk28 = 0;
    arg0->unk2C = 0;
    arg0->unk68 = falling_rock_box_4;
    arg0->unk54 = (const u8*)falling_rock_box_1;
    arg0->unk50.data = (const u8*)falling_rock_box_1;
    set_animation(arg0, 1);
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x1B;
        misc->unk16 = 1;
        misc->unk40 = arg0->unk40;
        misc->unk42 = arg0->unk42 & 0x7FFF;
        misc->animation_table = arg0->animation_table;
        misc->unk3C = arg0->unk3C;
        misc->bg_offset = arg0->bg_offset;
        misc->x_pos.val = arg0->x_pos.val;
        misc->y_pos.val = arg0->y_pos.val;
        misc->unk15 = arg0->unk15;
        misc->ext.misc_5.owner = (struct MainObj*)arg0;
        misc->state = 0;
        misc->unk6 = 1;
        misc->unk7 = 0;
        set_animation(misc, 0);
        arg0->unk7C = (struct WeaponObj*)misc;
    }
    arg0->state = 4;
    arg0->unk5 = 0;
}
#endif

// falling_rock_b_fall
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_33_falling_rock", func_800A0C4C);
#else
void func_800A0C4C(struct ShotObj* arg0)
{
    s32 collision;

    arg0->unk42 &= 0x7FFF;
    if (arg0->unk5 == 0) {
        if (!(background_objects[g_Player.bg_offset].unk34 & 0x10))
            start_screen_shake_x(8, 4, 2);
        move_with_gravity(ANIMATED_OBJECT(arg0));
        animate_object(ANIMATED_OBJECT(arg0));
        CollisionRelated((struct PlayerObj*)arg0);
        if (!(arg0->unk70 & 8))
            arg0->unk2C = 0x8000;
        if (arg0->unk70 & 8)
            arg0->unk2C = 0;
        if (arg0->unk15 != 0) {
            if (arg0->unk70 & 2) {
                if (!(background_objects[g_Player.bg_offset].unk34 & 0x10))
                    start_screen_shake_x(0x10, 6, 2);
                spawn_debris(5, falling_rock_debris_2, arg0);
                if (arg0->on_screen != 0)
                    func_8001540C(2, 0xA0, arg0);
                arg0->state = 5;
                return;
            }
        } else if (arg0->unk70 & 1) {
            if (!(background_objects[g_Player.bg_offset].unk34 & 0x10))
                start_screen_shake_x(0x10, 6, 2);
            spawn_debris(5, falling_rock_debris_2, arg0);
            if (arg0->on_screen != 0)
                func_8001540C(2, 0xA0, arg0);
            arg0->state = 5;
            return;
        }
        func_8002D9BC(arg0);
        if (func_8002BB80((struct MainObj*)arg0, (struct MainObj*)&g_Player) != 0) {
            spawn_debris(5, falling_rock_debris_2, arg0);
            if (arg0->on_screen != 0)
                func_8001540C(2, 0xA0, arg0);
            arg0->state = 5;
        }
        collision = func_8002DD04((struct MainObj*)arg0);
        if (collision < 0) {
            spawn_debris(5, falling_rock_debris_2, arg0);
            if (arg0->on_screen != 0)
                func_8001540C(2, 0xA0, arg0);
            arg0->state = 5;
        } else if (collision == 3 || collision == 0xC || collision == 0x22) {
            arg0->unk84.value = 8;
            set_animation(arg0, 7);
            arg0->unk7C->active = 0;
            arg0->unk7C->on_screen = 0;
            arg0->unk5 = 1;
        }
    } else if (--arg0->unk84.value == 0) {
        spawn_debris(5, falling_rock_debris_3, arg0);
        arg0->state = 5;
    }
    if (arg0->y_pos.i.hi > background_objects[g_Player.bg_offset].y_pos.i.hi + 0x150) {
        arg0->state = 5;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x60, 0x60);
}
#endif

void falling_rock_b_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

// falling_rock_c_init
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/shots/shot_33_falling_rock", func_800A0FE8);
#else
void func_800A0FE8(struct ShotObj* arg0)
{
    struct MiscObj* misc;

    if (engine_obj.character_state.bytes[0] != 0) {
        arg0->state = 8;
        return;
    }
    arg0->on_screen = 1;
    arg0->unk58.animation_steps = D_80105FF0;
    arg0->unk5C = 0xF;
    arg0->unk60 = 6;
    arg0->unk42 &= 0x7FFF;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(0x8D));
    arg0->unk3C = (u8*)SP_MENU_FRAMES + SP_MENU_FRAMES[func_8002938C(0x8D)];
    arg0->unk42 = OBJECT_STAGE_CLUT(0x8D);
    arg0->animation_table = (u32**)falling_rock_c_animations;
    arg0->unk16 = 0;
    arg0->unk15 = 0;
    arg0->x_vel.val = 0;
    arg0->unk28 = 0;
    if (arg0->unk2 == 0) {
        set_animation(arg0, 3);
        arg0->y_vel.val = -0x18000;
        arg0->unk2C = 0x2000;
        arg0->y_pos.i.hi = background_objects[g_Player.bg_offset].y_pos.i.hi - 0x40;
    } else {
        set_animation(arg0, 1);
        arg0->y_vel.val = 0xA0000;
        arg0->unk2C = 0x2000;
        if (engine_obj.substage != 0 && arg0->x_pos.i.hi > 0x60 && arg0->x_pos.i.hi < 0x4E0)
            arg0->y_pos.i.hi = 0x330;
        else
            arg0->y_pos.i.hi = background_objects[g_Player.bg_offset].y_pos.i.hi + 0x130;
    }
    arg0->unk68 = falling_rock_box_5;
    arg0->unk54 = (const u8*)falling_rock_box_2;
    arg0->unk50.data = (const u8*)falling_rock_box_2;
    misc = find_free_misc_obj();
    if (misc != NULL) {
        misc->active = 0x41;
        misc->id = 0x1B;
        misc->unk16 = 1;
        misc->unk40 = arg0->unk40;
        misc->unk42 = arg0->unk42 & 0x7FFF;
        misc->animation_table = arg0->animation_table;
        misc->unk3C = arg0->unk3C;
        misc->bg_offset = arg0->bg_offset;
        misc->x_pos.val = arg0->x_pos.val;
        misc->y_pos.val = arg0->y_pos.val;
        misc->unk15 = arg0->unk15;
        misc->ext.misc_5.owner = (struct MainObj*)arg0;
        misc->state = 0;
        misc->unk6 = 1;
        misc->unk7 = 0;
        if (arg0->unk2 == 0)
            set_animation(misc, 2);
        else
            set_animation(misc, 0);
        arg0->unk7C = (struct WeaponObj*)misc;
    }
    arg0->state = 7;
    arg0->unk5 = 0;
}
#endif

// falling_rock_c_fall
void func_800A12EC(struct ShotObj* self)
{
    u8 flags;
    s32 tile;
    u16 timer;
    self->unk42 &= 0x7FFF;
    if (self->unk5 == 0) {
        move_with_gravity(ANIMATED_OBJECT(self));
        CollisionRelated((struct PlayerObj*)self);
        flags = self->unk70;
        if (flags & 4) {
            if ((engine_obj.substage != 0) && (((u32)(((u16)self->x_pos.i.hi) - 0x61)) < 0x47F)) {
                if (self->unk6 != 0) {
                    self->y_pos.i.hi -= 0x28;
                    if (self->on_screen != 0) {
                        func_8001540C(2, SATURN_SOUND(0xA0, 0x70), self);
                    }
                    func_800C842C(7, falling_rock_debris_6, self, 0x9A, falling_rock_d_animations);
                    self->y_pos.i.hi += 0x28;
                }
                apply_tile_effect(self->unk6, (s16)(self->x_pos.i.hi - 0x18), (s16)(self->y_pos.i.hi - 0x58));
            }
            if (!(background_objects[g_Player.bg_offset].unk34 & 0x10)) {
                start_screen_shake_x(0x10, 6, 2);
            }
            if (self->on_screen != 0) {
                func_8001540C(2, SATURN_SOUND(0xA0, 0x70), self);
            }
            spawn_debris(5, falling_rock_debris_4, self);
            self->state = 8;
            return;
        }
        if (flags & 8) {
            if (!(background_objects[g_Player.bg_offset].unk34 & 0x10)) {
                start_screen_shake_x(0x10, 6, 2);
            }
            if (self->on_screen != 0) {
                func_8001540C(2, SATURN_SOUND(0xA0, 0x70), self);
            }
            spawn_debris(5, falling_rock_debris_4, self);
            self->state = 8;
            return;
        }
        if (self->y_vel.val == 0) {
            if (self->unk2 == 2) {
                self->state = 8;
                return;
            }
            set_animation(self, 3);
            set_animation(self->unk7C, 2);
        }
        animate_object(ANIMATED_OBJECT(self));
        func_8002D9BC(self);
        if (func_8002BB80((struct MainObj*)self, (struct MainObj*)(&g_Player)) != 0) {
            if (self->on_screen != 0) {
                func_8001540C(2, SATURN_SOUND(0xA0, 0x70), self);
            }
            spawn_debris(5, falling_rock_debris_4, self);
            self->state = 8;
        }
        tile = func_8002DD04((struct MainObj*)self);
        if ((tile < 0) || (engine_obj.character_state.fields.active != 0)) {
            if (self->on_screen != 0) {
                func_8001540C(2, SATURN_SOUND(0xA0, 0x70), self);
            }
            self->unk84.effect->ext.effect_33.timer = 0xB4;
            spawn_debris(5, falling_rock_debris_4, self);
            self->state = 8;
        } else if (((tile == 3) || (tile == 0xC)) || (tile == 0x22)) {
            self->timer = 8;
            set_animation(self, 9);
            self->unk7C->active = 0;
            self->unk7C->on_screen = 0;
            self->unk5 = 1;
        }
    } else {
        timer = self->timer - 1;
        self->timer = timer;
        if ((timer << 0x10) == 0) {
            self->unk84.effect->ext.effect_33.timer = 0xB4;
            spawn_debris(5, falling_rock_debris_5, self);
            self->state = 8;
        }
    }
    if ((background_objects[g_Player.bg_offset].y_pos.i.hi + 0x150) < self->y_pos.i.hi) {
        self->state = 8;
        return;
    }
    update_on_screen(BASE_OBJECT(self), 0x60, 0x60);
}

void falling_rock_c_despawn(struct ShotObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

struct Unk_unk68 falling_rock_box_0[] = {
    { -20, -23, 0x23, 0x22 },
};

struct Unk_unk68 falling_rock_box_1[] = {
    { -17, -20, 0x23, 0x26 },
};

struct Unk_unk68 falling_rock_box_2[] = {
    { -17, -18, 0x23, 0x26 },
};

struct Unk_unk68 falling_rock_box_3[] = {
    { -3, -6, 0x12, 0x12 },
};

struct Unk_unk68 falling_rock_box_4[] = {
    { 0, -1, 0x14, 0x13 },
};

struct Unk_unk68 falling_rock_box_5[] = {
    { 0, -1, 0x14, 0x13 },
};

u8 falling_rock_debris_0[] = {
    0x03,
    0x04,
    0x05,
    0x06,
    0x07,
    0x00,
    0x00,
    0x00,
};

u8 falling_rock_debris_1[] = {
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x00,
    0x00,
    0x00,
};

u8 falling_rock_debris_2[] = {
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x00,
    0x00,
    0x00,
};

u8 falling_rock_debris_3[] = {
    0x08,
    0x09,
    0x0A,
    0x0B,
    0x0C,
    0x00,
    0x00,
    0x00,
};

u8 falling_rock_debris_4[] = {
    0x04,
    0x05,
    0x06,
    0x07,
    0x08,
    0x00,
    0x00,
    0x00,
};

u8 falling_rock_debris_5[] = {
    0x0A,
    0x0B,
    0x0C,
    0x0D,
    0x0E,
    0x00,
    0x00,
    0x00,
};

u8 falling_rock_debris_6[] = {
    0x00,
    0x01,
    0x02,
    0x03,
    0x04,
    0x05,
    0x06,
    0x00,
};

union AnimationStep D_801092B8[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 2, 1, -3, 0x03 },
};

union AnimationStep D_801092C8[] = {
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x05 },
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 1, -6, 0x0A },
};

union AnimationStep D_801092E4[] = {
    { 2, 0, 1, 0x0B },
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 1, 1, 0, 0x0D },
};

union AnimationStep D_801092F4[] = {
    { 1, 1, 0, 0x0E },
};

union AnimationStep D_801092F8[] = {
    { 1, 1, 0, 0x0F },
};

union AnimationStep D_801092FC[] = {
    { 1, 1, 0, 0x10 },
};

union AnimationStep D_80109300[] = {
    { 1, 1, 0, 0x11 },
};

union AnimationStep D_80109304[] = {
    { 1, 1, 0, 0x12 },
};

union AnimationStep D_80109308[] = {
    { 1, 1, 0, 0x13 },
};

union AnimationStep D_8010930C[] = {
    { 1, 1, 0, 0x14 },
};

union AnimationStep D_80109310[] = {
    { 1, 1, 0, 0x15 },
};

union AnimationStep D_80109314[] = {
    { 1, 1, 0, 0x16 },
};

union AnimationStep D_80109318[] = {
    { 1, 1, 0, 0x17 },
};

union AnimationStep D_8010931C[] = {
    { 1, 1, 0, 0x18 },
};

union AnimationStep* falling_rock_a_animations[] = {
    D_801092B8,
    D_801092C8,
    D_801092E4,
    D_801092F4,
    D_801092F8,
    D_801092FC,
    D_80109300,
    D_80109304,
    D_80109308,
    D_8010930C,
    D_80109310,
    D_80109314,
    D_80109318,
    D_8010931C,
};

union AnimationStep D_80109358[] = {
    { 5, 0, 1, 0x00 },
    { 5, 0, 1, 0x01 },
    { 5, 0, 1, 0x02 },
    { 5, 0, 1, 0x03 },
    { 5, 1, -4, 0x04 },
};

union AnimationStep D_8010936C[] = {
    { 4, 0, 1, 0x05 },
    { 4, 0, 1, 0x06 },
    { 4, 0, 1, 0x07 },
    { 4, 0, 1, 0x08 },
    { 4, 0, 1, 0x09 },
    { 4, 0, 1, 0x0A },
    { 4, 0, 1, 0x0B },
    { 4, 1, -7, 0x0C },
};

union AnimationStep D_8010938C[] = {
    { 1, 1, 0, 0x0D },
};

union AnimationStep D_80109390[] = {
    { 1, 1, 0, 0x0E },
};

union AnimationStep D_80109394[] = {
    { 1, 1, 0, 0x0F },
};

union AnimationStep D_80109398[] = {
    { 1, 1, 0, 0x10 },
};

union AnimationStep D_8010939C[] = {
    { 1, 1, 0, 0x11 },
};

union AnimationStep D_801093A0[] = {
    { 1, 1, 0, 0x12 },
};

union AnimationStep D_801093A4[] = {
    { 1, 1, 0, 0x13 },
};

union AnimationStep D_801093A8[] = {
    { 1, 1, 0, 0x14 },
};

union AnimationStep D_801093AC[] = {
    { 1, 1, 0, 0x15 },
};

union AnimationStep D_801093B0[] = {
    { 1, 1, 0, 0x16 },
};

union AnimationStep D_801093B4[] = {
    { 1, 1, 0, 0x17 },
};

union AnimationStep* falling_rock_b_animations[] = {
    D_80109358,
    D_8010936C,
    D_8010938C,
    D_80109390,
    D_80109394,
    D_80109398,
    D_8010939C,
    D_801093A0,
    D_801093A4,
    D_801093A8,
    D_801093AC,
    D_801093B0,
    D_801093B4,
};

union AnimationStep D_801093EC[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 2, 1, -3, 0x03 },
};

union AnimationStep D_801093FC[] = {
    { 2, 0, 1, 0x04 },
    { 2, 0, 1, 0x05 },
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 1, -7, 0x0B },
};

union AnimationStep D_8010941C[] = {
    { 2, 0, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 1, -3, 0x0F },
};

union AnimationStep D_8010942C[] = {
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x13 },
    { 2, 0, 1, 0x14 },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 2, 1, -7, 0x17 },
};

union AnimationStep D_8010944C[] = {
    { 1, 1, 0, 0x18 },
};

union AnimationStep D_80109450[] = {
    { 1, 1, 0, 0x19 },
};

union AnimationStep D_80109454[] = {
    { 1, 1, 0, 0x1A },
};

union AnimationStep D_80109458[] = {
    { 1, 1, 0, 0x1B },
};

union AnimationStep D_8010945C[] = {
    { 1, 1, 0, 0x1C },
};

union AnimationStep D_80109460[] = {
    { 1, 1, 0, 0x1D },
};

union AnimationStep D_80109464[] = {
    { 1, 1, 0, 0x1E },
};

union AnimationStep D_80109468[] = {
    { 1, 1, 0, 0x1F },
};

union AnimationStep D_8010946C[] = {
    { 1, 1, 0, 0x20 },
};

union AnimationStep D_80109470[] = {
    { 1, 1, 0, 0x21 },
};

union AnimationStep D_80109474[] = {
    { 1, 1, 0, 0x22 },
};

union AnimationStep* falling_rock_c_animations[] = {
    D_801093EC,
    D_801093FC,
    D_8010941C,
    D_8010942C,
    D_8010944C,
    D_80109450,
    D_80109454,
    D_80109458,
    D_8010945C,
    D_80109460,
    D_80109464,
    D_80109468,
    D_8010946C,
    D_80109470,
    D_80109474,
};

union AnimationStep D_801094B4[] = {
    { 1, 1, 0, 0x00 },
};

union AnimationStep D_801094B8[] = {
    { 1, 1, 0, 0x01 },
};

union AnimationStep D_801094BC[] = {
    { 1, 1, 0, 0x02 },
};

union AnimationStep D_801094C0[] = {
    { 1, 1, 0, 0x03 },
};

union AnimationStep D_801094C4[] = {
    { 1, 1, 0, 0x04 },
};

union AnimationStep D_801094C8[] = {
    { 1, 1, 0, 0x05 },
};

union AnimationStep D_801094CC[] = {
    { 1, 1, 0, 0x06 },
};

union AnimationStep* falling_rock_d_animations[] = {
    D_801094B4,
    D_801094B8,
    D_801094BC,
    D_801094C0,
    D_801094C4,
    D_801094C8,
    D_801094CC,
};

void (*falling_rock_state_funcs[])(struct ShotObj*) = {
    func_800A03F4,
    func_800A068C,
    falling_rock_a_despawn,
    func_800A0A38,
    func_800A0C4C,
    falling_rock_b_despawn,
    func_800A0FE8,
    func_800A12EC,
    falling_rock_c_despawn,
};
