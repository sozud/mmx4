// MainObj, main_object_update_funcs[19]
// 8005284C..8005458C
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_19_surface_hopper.h"
#include "main/object_motion.h"
#include "main/1CF60.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/items/item_01_stage_block.h"
#include "main/objects.h"
#include "main/collision_bounds.h"

#if defined(MMX4_PC) || defined(MMX4_SATURN)
#include "main/collision_bounds.h"
#endif

extern u8 surface_hopper_appear_animations[4];

void func_80052A68(struct MainObj*);
void surface_hopper_despawn(struct MainObj* arg0);

void surface_hopper_despawn(struct MainObj* arg0);

// surface_hopper_step_funcs
void surface_hopper_appear(struct MainObj* arg0);
void surface_hopper_crawl(struct MainObj* arg0);
void surface_hopper_crawl(struct MainObj* arg0);
void surface_hopper_leap(struct MainObj* arg0);
void surface_hopper_fly(struct MainObj* arg0);

// surface_hopper_crawl_funcs
extern void (*surface_hopper_crawl_funcs[])(struct MainObj*);

void surface_hopper_crawl_turn_end(struct MainObj*);
void surface_hopper_crawl_attach(struct MainObj*);

void surface_hopper_crawl_finish(struct MainObj*);

// surface_hopper_leap_funcs
void surface_hopper_leap_start(struct MainObj*);

extern u8 surface_hopper_leap_animations[];

void surface_hopper_fly(struct MainObj* arg0);

extern void (*surface_hopper_state_funcs[])(struct MainObj*);
extern void (*surface_hopper_launched_state_funcs[])(struct MainObj*);
extern void (*surface_hopper_leap_funcs[])(struct MainObj*);

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

extern s16 D_800FC7E8[6];
extern void (*surface_hopper_launched_step_funcs[6])(struct MainObj*);
extern union AnimationStep* surface_hopper_animations[27];
extern struct Unk_unk68* D_800FC744[2];
extern struct Unk_unk68* D_800FC74C[2];
extern struct Unk_unk68 D_80106BF4[];
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800528BC(struct MainObj* arg0);
u16 func_800537E0(struct MainObj* arg0, u8 direction, u8 vertical);
void func_80052CB8(struct MainObj* arg0);
u8 func_80053B54(struct MainObj* arg0);
void func_80052E94(struct MainObj* arg0);
void func_8005368C(struct MainObj* arg0);
void func_80053338(struct MainObj* arg0);
void func_80053D24(struct MainObj* self);
void func_80053EB8(struct MainObj* self);
void func_8005402C(struct MainObj* self);
extern u8 D_800FC7D4[4];
extern u8 D_800FC7D8[4];
u8 surface_hopper_probe_collision(struct PlayerObj*, s16, s16);
u8 surface_hopper_probe_tile(struct PlayerObj*, s16, s16);
u8 surface_hopper_aim_at_player(struct MainObj*);
// src/main/mains/main_19_surface_hopper.c

extern u8 D_800FC80C[8];
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_800528BC);
#else
void func_800528BC(struct MainObj* arg0)
{
    arg0->state = 1;
    arg0->unk5 = 2;
    arg0->hp = 4;
    arg0->contact_damage = 3;
    arg0->unk6 = 0;
    arg0->on_screen = 1;
    arg0->unk7C = 0;
    arg0->invincibility_timer = 0;
    arg0->animation_table = (const u8* const*)surface_hopper_animations;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    CollisionRelated(PLAYER_OBJECT(arg0));
    arg0->air_state = 0;
    arg0->x_speed = 0;
    arg0->y_speed = 0;
    arg0->x_accel = 0;
    arg0->gravity = 0;

    switch (arg0->unk2) {
    case 0:
        arg0->x_speed = FIXED(8);
        arg0->unk15 = PLAYER_FACING_RIGHT;
        break;
    case 1:
        arg0->x_speed = FIXED(-8);
        arg0->unk15 = 0;
        break;
    case 2:
        arg0->y_speed = FIXED(8);
        break;
    }
    arg0->unk16 = VISUAL_SATURN_LAYER(6);

    SP_CUR_MAIN_OBJ->ext.main_19.unk80 = get_random() & 1;
#ifdef MMX4_PC
    if (SP_CUR_MAIN_OBJ->ext.main_19.unk8A > 0x17)
        SP_CUR_MAIN_OBJ->ext.main_19.unk8A = 1;
#endif
    SP_CUR_MAIN_OBJ->ext.main_19.animation_index = (u8)arg0->unk2;
    arg0->hurt_box = D_800FC744[arg0->unk2 >> 1];
    arg0->attack_box = D_800FC74C[arg0->unk2 >> 1];
    arg0->terrain_box = surface_hopper_attach_terrain_boxes[arg0->unk2 >> 1];
    arg0->collision_data = D_80106BF4;
    func_8002C808(PLAYER_OBJECT(arg0));
    if (arg0->collision_flags != 0)
        arg0->unk5 = 2;
    else
        arg0->unk5 = 5;
}
#endif

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
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80052CB8(struct MainObj* arg0)
{
    u8 animation;
    u16 probe_result;

    if (arg0->ext.main_19.animation_index < 2) {
        if (arg0->ext.main_19.animation_index == 0) {
            arg0->unk15 = PLAYER_FACING_RIGHT;
            arg0->ext.main_19.unk82 = 1;
        } else {
            arg0->unk15 = 0;
            arg0->ext.main_19.unk82 = 2;
        }
        arg0->ext.main_19.unk84 = (get_random() & 1) ? 0x50 : 0x20;
        probe_result = func_800537E0(arg0, arg0->ext.main_19.unk80, 0);
        if (probe_result != 0)
            arg0->ext.main_19.unk80 ^= 1;
        animation = D_800FC7D4[arg0->ext.main_19.unk80];
        arg0->ext.main_19.unk8A = 0x15;
    } else {
        arg0->ext.main_19.unk84 = (get_random() & 1) ? 0x40 : 0x20;
        if (func_800537E0(arg0, arg0->ext.main_19.unk80, 1) != 0)
            arg0->ext.main_19.unk80 ^= 1;
        arg0->unk15 = D_800FC7D8[arg0->ext.main_19.unk80];
        arg0->ext.main_19.unk8A = 0x17;
        arg0->ext.main_19.unk82 = 4;
        animation = 2;
    }

    arg0->terrain_box = surface_hopper_attach_terrain_boxes[arg0->unk2 >> 1];
    set_animation(ANIMATED_OBJECT(arg0), animation);
    arg0->unk6 = 1;
    arg0->ext.main_19.unk86 = arg0->x_pos.u.hi;
    arg0->ext.main_19.unk88 = arg0->y_pos.u.hi;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_80052CB8);
#endif

// surface_hopper_crawl_move
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_80052E94);
#else
void func_80052E94(struct MainObj* arg0)
{
    u8 flags;

    if (SP_CUR_MAIN_OBJ->ext.main_19.animation_index < 2) {
        if (arg0->animation_step.fields.relative_step < 0) {
            if ((arg0->y_pos.i.hi - (s16)SP_CUR_MAIN_OBJ->ext.main_19.unk88 >= 0 ? arg0->y_pos.i.hi - (s16)SP_CUR_MAIN_OBJ->ext.main_19.unk88 : (s16)SP_CUR_MAIN_OBJ->ext.main_19.unk88 - arg0->y_pos.i.hi) <= SP_CUR_MAIN_OBJ->ext.main_19.unk84 && (u16)func_800537E0(arg0, SP_CUR_MAIN_OBJ->ext.main_19.unk80, 0) == 0)
                goto near;

            flags = surface_hopper_aim_at_player(arg0);
            if (flags & 1) {
                arg0->unk6 = 4;
                if (arg0->y_speed < 0)
                    SP_CUR_MAIN_OBJ->ext.main_19.unk80 = 1;
                else
                    SP_CUR_MAIN_OBJ->ext.main_19.unk80 = 0;
                arg0->x_speed = 0;
                arg0->y_speed *= 3;
                set_animation(ANIMATED_OBJECT(arg0), 6);
            } else if (func_80053B54(arg0) != 0) {
                arg0->unk5 = 4;
                arg0->unk6 = 0;
            } else {
                arg0->unk6 = 2;
                set_animation(ANIMATED_OBJECT(arg0), 6);
            }
        } else if (arg0->animation_step.fields.event != 0) {
            if (SP_CUR_MAIN_OBJ->ext.main_19.unk80 == 0)
                arg0->y_pos.u.hi -= SP_CUR_MAIN_OBJ->ext.main_19.unk8A;
            else
                arg0->y_pos.u.hi += SP_CUR_MAIN_OBJ->ext.main_19.unk8A;
            arg0->animation_step.fields.event = 0;
        }
    } else {
        if (arg0->animation_step.fields.relative_step < 0) {
            if ((arg0->x_pos.i.hi - (s16)SP_CUR_MAIN_OBJ->ext.main_19.unk86 >= 0 ? arg0->x_pos.i.hi - (s16)SP_CUR_MAIN_OBJ->ext.main_19.unk86 : (s16)SP_CUR_MAIN_OBJ->ext.main_19.unk86 - arg0->x_pos.i.hi) <= SP_CUR_MAIN_OBJ->ext.main_19.unk84 && (u16)func_800537E0(arg0, SP_CUR_MAIN_OBJ->ext.main_19.unk80, 1) == 0) {
            near:
                if (arg0->unk7C >= 0x3C && func_80053B54(arg0) != 0) {
                stun:
                    arg0->unk5 = 4;
                    arg0->unk6 = 0;
                }
                goto update_animation;
            }

            flags = surface_hopper_aim_at_player(arg0);
            if (flags & 2) {
                arg0->unk6 = 4;
                if (arg0->x_speed >= 0) {
                    arg0->unk15 = PLAYER_FACING_RIGHT;
                    SP_CUR_MAIN_OBJ->ext.main_19.unk80 = 1;
                } else {
                    arg0->unk15 = 0;
                    SP_CUR_MAIN_OBJ->ext.main_19.unk80 = 0;
                }
                arg0->y_speed = 0;
                arg0->x_speed *= 3;
                set_animation(ANIMATED_OBJECT(arg0), 5);
            } else if (func_80053B54(arg0) != 0) {
                goto stun;
            } else {
                arg0->unk6 = 2;
                set_animation(ANIMATED_OBJECT(arg0), 5);
            }
        } else if (arg0->animation_step.fields.event != 0) {
            if (SP_CUR_MAIN_OBJ->ext.main_19.unk80 == 0)
                arg0->x_pos.u.hi -= SP_CUR_MAIN_OBJ->ext.main_19.unk8A;
            else
                arg0->x_pos.u.hi += SP_CUR_MAIN_OBJ->ext.main_19.unk8A;
            arg0->animation_step.fields.event = 0;
        }
    }

update_animation:
    animate_object(ANIMATED_OBJECT(arg0));
}
#endif

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
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80053338(struct MainObj* arg0)
{
    struct Unk_unk68* bounds;
    s16 probe_x;
    s16 probe_y;
    s32 distance;
    s32 nearby;
    u8 collision;
    u8 direction;

    move_object(MOVING_OBJECT(arg0));
    CollisionRelated(PLAYER_OBJECT(arg0));
    bounds = arg0->terrain_box;
    nearby = 0;
    if (arg0->ext.main_19.animation_index < 2) {
        probe_y = arg0->y_pos.i.hi;
        if (arg0->ext.main_19.unk80 == 0)
            probe_y -= (u8)bounds->unk3;
        else
            probe_y += (u8)bounds->unk3;
        probe_x = arg0->x_pos.i.hi + (arg0->unk15 != 0 ? 4 : -4);
        distance = g_Player.y_pos.i.hi - arg0->y_pos.i.hi;
    } else {
        probe_x = arg0->x_pos.i.hi;
        if (arg0->unk15 == 0)
            probe_x -= (u8)bounds->unk2;
        else
            probe_x += (u8)bounds->unk2;
        probe_y = arg0->y_pos.i.hi - 4;
        distance = g_Player.x_pos.i.hi - arg0->x_pos.i.hi;
    }
    if (distance < 0)
        distance = -distance;
    if (distance < 0x18)
        nearby = 1;

    collision = func_8002D724(PLAYER_OBJECT(arg0), probe_x, probe_y);
    if ((arg0->collision_flags & (u8)~arg0->ext.main_19.unk82) == 0 && collision >= 0x38 && !nearby) {
        animate_object(ANIMATED_OBJECT(arg0));
        return;
    }

    if (arg0->ext.main_19.animation_index < 2) {
        set_animation(ANIMATED_OBJECT(arg0), 0xB);
        arg0->unk6 = 6;
        arg0->ext.main_19.unk80 ^= 1;
        direction = arg0->ext.main_19.unk80;
        if ((arg0->collision_flags >> (direction + 2)) & 1)
            arg0->ext.main_19.unk80 = direction ^ 1;
    } else {
        set_animation(ANIMATED_OBJECT(arg0), 0xA);
        arg0->unk6 = 6;
        arg0->unk15 ^= PLAYER_FACING_RIGHT;
        arg0->ext.main_19.unk80 ^= 1;
        direction = arg0->ext.main_19.unk80;
        if ((arg0->collision_flags >> direction) & 1)
            arg0->ext.main_19.unk80 = direction ^ 1;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_80053338);
#endif

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
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_8005368C);
#else
void func_8005368C(struct MainObj* arg0)
{
    struct ShotObj* shot;
    u8 index;

    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->unk5 = 2;
        arg0->unk6 = 0;
        SP_CUR_MAIN_OBJ->ext.main_19.unk80 = get_random() & 1;
        return;
    }
    if (arg0->animation_step.fields.event != 0) {
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 0xB;
            index = SP_CUR_MAIN_OBJ->ext.main_19.animation_index * 2;
            shot->x_pos.i.hi = arg0->x_pos.i.hi + D_800FC7E8[index];
            shot->y_pos.i.hi = arg0->y_pos.i.hi + D_800FC7E8[(u8)(index | 1)];
            shot->animation_table = (u32**)arg0->animation_table;
            shot->unk40 = arg0->unk40;
            shot->unk3C = (void*)arg0->sprite_frames;
            shot->unk42 = arg0->unk42 & 0x7FFF;
            shot->unk16 = arg0->unk16;
            shot->unk7C = (struct WeaponObj*)arg0;
            shot->unk15 = arg0->unk15;
            set_velocity_from_angle(MOVING_OBJECT(shot), SP_CUR_MAIN_OBJ->ext.main_19.unk83);
        }
        arg0->animation_step.fields.event = 0;
    } else {
        animate_object(ANIMATED_OBJECT(arg0));
    }
}
#endif

// surface_hopper_pick_surface
#if defined(MMX4_PC) || defined(MMX4_SATURN)
u16 func_800537E0(struct MainObj* arg0, u8 direction, u8 vertical)
{
    struct Unk_unk68* bounds = arg0->terrain_box;
    s32 first;
    s32 second;
    s16 probe;
    s16 edge;

    if (vertical == 0) {
        if (direction == 0) {
            probe = -(u16)arg0->ext.main_19.unk8A;
            edge = probe - (u8)bounds->unk3;
        } else {
            probe = arg0->ext.main_19.unk8A;
            edge = probe + (u8)bounds->unk3;
        }
        if (arg0->unk15 == 0) {
            first = surface_hopper_probe_collision(PLAYER_OBJECT(arg0), -1, probe);
            second = surface_hopper_probe_tile(PLAYER_OBJECT(arg0), -4, edge);
        } else {
            first = surface_hopper_probe_collision(PLAYER_OBJECT(arg0), 1, probe);
            second = surface_hopper_probe_tile(PLAYER_OBJECT(arg0), 4, edge);
        }
        if ((first & 0xF) == (1 << arg0->ext.main_19.animation_index))
            return (u8)second < 0x38;
        return 1;
    }

    if (direction == 0) {
        probe = -(u16)arg0->ext.main_19.unk8A;
        edge = probe - (u8)bounds->unk2;
    } else {
        probe = arg0->ext.main_19.unk8A;
        edge = probe + (u8)bounds->unk2;
    }
    first = surface_hopper_probe_collision(PLAYER_OBJECT(arg0), probe, -1);
    second = surface_hopper_probe_tile(PLAYER_OBJECT(arg0), edge, -4);
    if ((first & 0xF) == 4)
        return (u8)second < 0x38;
    return 1;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_800537E0);
#endif

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
#if defined(MMX4_PC) || defined(MMX4_SATURN)
u8 func_80053B54(struct MainObj* arg0)
{
    s32 dx = (s16)(g_Player.x_pos.i.hi - arg0->x_pos.i.hi);
    s32 dy = (s16)(g_Player.y_pos.i.hi - arg0->y_pos.i.hi);
    u8 direction;
    s32 selected = 0;

    if (dx < 0)
        dx = -dx;
    if (dy < 0)
        dy = -dy;
    direction = (u8)angle_to_object(
        OBJECT_HEADER(arg0), OBJECT_HEADER(&g_Player));

    if (arg0->ext.main_19.animation_index < 2) {
        if (dx < 0x40 && dy >= 0x60)
            return 0;
        if (arg0->ext.main_19.animation_index == 0)
            selected = (u8)(direction - 8) < 0x11;
        else
            selected = (u8)(direction - 9) >= 0xF;
    } else {
        if (dx >= 0x80)
            return 0;
        selected = (u8)(direction - 0x10) < 0x11;
    }

    if (selected)
        arg0->ext.main_19.unk83 = direction & 0x1E;
    return selected;
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_80053B54);
#endif

void surface_hopper_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

// surface_hopper_launched_init
#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_80053D24);
#else
void func_80053D24(struct MainObj* self)
{
    s32 vx;
    s32 vy;

    self->state = 1;
    self->unk5 = 2;
    self->hp = 31;
    self->contact_damage = 3;
    self->animation_table = (const u8* const*)surface_hopper_animations;
    self->unk16 = VISUAL_SATURN_LAYER(6);
    self->unk6 = 0;
    self->unk7C = 0;
    self->on_screen = 1;
    self->invincibility_timer = 0;
    self->air_state = 0;
    self->unk42++;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    SP_CUR_MAIN_OBJ->ext.main_19.unk82 = 0x38;
    SP_CUR_MAIN_OBJ->ext.main_19.animation_index = ((u8)self->unk2 - 3) & 1;
    SP_CUR_MAIN_OBJ->ext.main_19.unk83 = 1;
    vy = 0;
    vx = 0;
    self->x_speed = 0;
    self->y_speed = 0;
    self->x_accel = 0;
    self->gravity = 0;
    switch ((s8)((u8)self->unk2 - 3)) {
    case 0:
    case 1:
        vy = FIXED(-8);
        SP_CUR_MAIN_OBJ->ext.main_19.unk80 = 0;
        break;
    case 2:
    case 3:
        vx = FIXED(8);
        SP_CUR_MAIN_OBJ->ext.main_19.unk80 = 1;
        break;
    case 4:
    case 5:
        vx = FIXED(-8);
        SP_CUR_MAIN_OBJ->ext.main_19.unk80 = 3;
        break;
    }
    surface_hopper_set_launch(self);
    self->x_speed = vx;
    self->y_speed = vy;
    self->hurt_box = NULL;
    self->collision_data = D_801060F0;
    func_8002C808(PLAYER_OBJECT(self));
    if (self->collision_flags & 8)
        self->unk5 = 2;
    else
        self->unk5 = 5;
}
#endif

// surface_hopper_launched_main
void func_80053EB8(struct MainObj* self)
{
    s32 hit;
    self->unk18 = self->x_pos;
    self->unk1C = self->y_pos;
    surface_hopper_launched_step_funcs[self->unk5](self);
    func_8002D9BC(BASE_OBJECT(self));
    hit = func_8002DD04(self);
    if (hit < 0) {
        u16 x;
        u16 y;
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(8, surface_hopper_debris, self);
        x = self->x_pos.u.hi;
        y = self->y_pos.u.hi;
        if (SP_CUR_MAIN_OBJ->ext.main_19.unk80 != 2) {
            switch (SP_CUR_MAIN_OBJ->ext.main_19.unk80) {
            case 0:
                y += 16;
                break;
            case 1:
                x -= 16;
                break;
            case 3:
                x += 16;
                break;
            }
            func_800BF638(BASE_OBJECT(self), 12, (s16)(x + 16), (s16)y);
        }
        self->state = 2;
        return;
    }
    if (hit != 0) {
        self->unk5 = 1;
        self->unk6 = 0;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
    } else {
        self->state = 2;
    }
    if (SP_CUR_MAIN_OBJ->ext.main_19.unk82 > 0x38) {
        self->state = 2;
    }
}

// surface_hopper_launched_crawl
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005402C(struct MainObj* self)
{
    struct Main19Ext* ext = &SP_CUR_MAIN_OBJ->ext.main_19;
    u16 x;
    u16 y;
    u8 orientation;
    u8 mask;
    if (self->unk6 == 0) {
        surface_hopper_set_launch(self);
        self->unk6 = 1;
        return;
    }
    x = self->x_pos.u.hi;
    y = self->y_pos.u.hi;
    orientation = ext->unk80;
    if (ext->animation_index == 0) {
        if (orientation == 2)
            y -= 2;
        if (orientation == 3) {
            x -= 2;
            y -= 2;
        }
    } else {
        if (orientation == 1) {
            x += 2;
            y -= 2;
        }
        if (orientation == 2) {
            x -= 2;
            y -= 2;
        }
        if (orientation == 3) {
            x -= 2;
            y += 2;
        }
    }
    ext->unk82 = func_8002D724(PLAYER_OBJECT(self), (s16)x, (s16)y);
    mask = D_800FC80C[ext->animation_index * 4 + ext->unk80];
    if (ext->unk82 < 0x38) {
        self->x_pos.u.hi = ext->unk86;
        self->y_pos.u.hi = ext->unk88;
        ext->unk83 ^= 1;
        ext->unk80 = (ext->unk80 + (ext->animation_index == 0 ? 1 : -1)) & 3;
        surface_hopper_set_launch(self);
    } else if (self->collision_flags & mask) {
        struct Unk_unk68* bounds = self->terrain_box;
        switch (mask) {
        case 1:
            self->x_pos.u.hi += bounds->unk0 + bounds->unk2;
            self->y_pos.u.hi += bounds->unk1;
            ext->unk80 = 1;
            break;
        case 2:
            self->x_pos.u.hi -= bounds->unk0 + bounds->unk2;
            self->y_pos.u.hi += bounds->unk1;
            ext->unk80 = 3;
            break;
        case 4:
        case 8:
            self->x_pos.u.hi += orientation == 1 ? -bounds->unk0 : bounds->unk0;
            self->y_pos.u.hi += mask == 4 ? -(bounds->unk1 + bounds->unk3) : bounds->unk1 + bounds->unk3;
            ext->unk80 = mask == 4 ? 2 : 0;
            break;
        default:
            animate_object(ANIMATED_OBJECT(self));
            break;
        }
        surface_hopper_set_launch(self);
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
    ext->unk86 = self->x_pos.u.hi;
    ext->unk88 = self->y_pos.u.hi;
    move_with_gravity(ANIMATED_OBJECT(self));
    CollisionRelated(PLAYER_OBJECT(self));
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_19_surface_hopper", func_8005402C);
#endif

void surface_hopper_set_launch(struct MainObj* self)
{
    s32 index;

    index = (SP_CUR_MAIN_OBJ->ext.main_19.animation_index << 2) + SP_CUR_MAIN_OBJ->ext.main_19.unk80;
#ifdef MMX4_PC
    self->x_speed = surface_hopper_launch_x_speeds[index] * FIXED(1);
    self->y_speed = surface_hopper_launch_y_speeds[index] * FIXED(1);
#else
    self->x_speed = surface_hopper_launch_x_speeds[index] << 16;
    self->y_speed = surface_hopper_launch_y_speeds[index] << 16;
#endif
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
    { 1, 0, 0, 0x00 },
};

union AnimationStep surface_hopper_anim_1[] = {
    { 1, 0, 0, 0x01 },
};

union AnimationStep surface_hopper_anim_2[] = {
    { 10, 0, 1, 0x00 },
    { 8, 0, 1, 0x02 },
    { 8, 0, 1, 0x03 },
    { 8, 0, 1, 0x04 },
    { 9, 0, 1, 0x05 },
    { 1, 1, 1, 0x05 },
    { 2, 0, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x08 },
    { 2, 0, -13, 0x00 },
};

union AnimationStep surface_hopper_anim_3[] = {
    { 10, 0, 1, 0x01 },
    { 8, 0, 1, 0x0A },
    { 8, 0, 1, 0x0B },
    { 8, 0, 1, 0x0C },
    { 9, 0, 1, 0x0D },
    { 1, 1, 1, 0x0D },
    { 2, 0, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x10 },
    { 2, 0, -13, 0x01 },
};

union AnimationStep surface_hopper_anim_4[] = {
    { 10, 0, 1, 0x01 },
    { 8, 0, 1, 0x40 },
    { 8, 0, 1, 0x41 },
    { 8, 0, 1, 0x42 },
    { 9, 0, 1, 0x43 },
    { 1, 1, 1, 0x43 },
    { 2, 0, 1, 0x44 },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x0F },
    { 2, 0, -13, 0x01 },
};

union AnimationStep surface_hopper_anim_5[] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x13 },
    { 2, 0, 1, 0x14 },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x17 },
    { 2, 0, -9, 0x18 },
};

union AnimationStep surface_hopper_anim_6[] = {
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x19 },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x1C },
    { 2, 0, 1, 0x1D },
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 2, 0, 1, 0x1E },
    { 2, 0, -9, 0x1F },
};

union AnimationStep surface_hopper_anim_7[] = {
    { 3, 0, 1, 0x18 },
    { 3, 0, 1, 0x21 },
    { 3, 0, -2, 0x20 },
};

union AnimationStep surface_hopper_anim_8[] = {
    { 3, 0, 1, 0x1F },
    { 3, 0, 1, 0x22 },
    { 3, 0, -2, 0x23 },
};

union AnimationStep surface_hopper_anim_9[] = {
    { 3, 0, 1, 0x1F },
    { 3, 0, 1, 0x23 },
    { 3, 0, -2, 0x22 },
};

union AnimationStep surface_hopper_anim_10[] = {
    { 10, 0, 1, 0x18 },
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x14 },
    { 2, 0, 1, 0x13 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x13 },
    { 10, 0, -6, 0x00 },
};

union AnimationStep surface_hopper_anim_11[] = {
    { 10, 0, 1, 0x1F },
    { 2, 0, 1, 0x1C },
    { 2, 0, 1, 0x1B },
    { 2, 0, 1, 0x1A },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x1A },
    { 10, 0, -6, 0x01 },
};

union AnimationStep surface_hopper_anim_12[] = {
    { 6, 0, 1, 0x24 },
    { 6, 0, 1, 0x25 },
    { 6, 0, 1, 0x26 },
    { 3, 0, 1, 0x27 },
    { 18, 0, 1, 0x28 },
    { 3, 0, 1, 0x29 },
    { 3, 0, 1, 0x2A },
    { 2, 0, 1, 0x2B },
    { 3, 0, 1, 0x29 },
    { 3, 1, 1, 0x2A },
    { 2, 0, 1, 0x2B },
    { 15, 0, 1, 0x28 },
    { 3, 0, 1, 0x27 },
    { 6, 0, 1, 0x26 },
    { 6, 0, 1, 0x25 },
    { 6, 0, -15, 0x24 },
};

union AnimationStep surface_hopper_anim_13[] = {
    { 6, 0, 1, 0x2C },
    { 6, 0, 1, 0x2D },
    { 6, 0, 1, 0x2E },
    { 3, 0, 1, 0x2F },
    { 18, 0, 1, 0x30 },
    { 3, 0, 1, 0x31 },
    { 3, 0, 1, 0x32 },
    { 2, 0, 1, 0x33 },
    { 3, 0, 1, 0x31 },
    { 3, 1, 1, 0x32 },
    { 2, 0, 1, 0x33 },
    { 15, 0, 1, 0x30 },
    { 3, 0, 1, 0x2F },
    { 6, 0, 1, 0x2E },
    { 6, 0, 1, 0x2D },
    { 6, 0, -15, 0x2C },
};

union AnimationStep surface_hopper_anim_14[] = {
    { 2, 1, 1, 0x06 },
    { 2, 0, 1, 0x07 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x08 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x09 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x08 },
    { 2, 0, -8, 0x00 },
};

union AnimationStep surface_hopper_anim_15[] = {
    { 2, 1, 1, 0x0E },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x11 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x10 },
    { 2, 0, -8, 0x01 },
};

union AnimationStep surface_hopper_anim_16[] = {
    { 2, 1, 1, 0x44 },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x0F },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x10 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x0F },
    { 2, 0, -8, 0x01 },
};

union AnimationStep surface_hopper_anim_17[] = {
    { 2, 0, 1, 0x34 },
    { 1, 0, 1, 0x35 },
    { 2, 0, 1, 0x36 },
    { 1, 0, -3, 0x37 },
};

union AnimationStep surface_hopper_anim_18[] = {
    { 1, 0, 0, 0x38 },
};

union AnimationStep surface_hopper_anim_19[] = {
    { 1, 0, 0, 0x39 },
};

union AnimationStep surface_hopper_anim_20[] = {
    { 1, 0, 0, 0x3A },
};

union AnimationStep surface_hopper_anim_21[] = {
    { 1, 0, 0, 0x3B },
};

union AnimationStep surface_hopper_anim_22[] = {
    { 1, 0, 0, 0x3C },
};

union AnimationStep surface_hopper_anim_23[] = {
    { 1, 0, 0, 0x3D },
};

union AnimationStep surface_hopper_anim_24[] = {
    { 1, 0, 0, 0x3E },
};

union AnimationStep surface_hopper_anim_25[] = {
    { 1, 0, 0, 0x3F },
};

union AnimationStep surface_hopper_anim_26[] = {
    { 3, 0, 1, 0x45 },
    { 3, 0, 1, 0x46 },
    { 3, 0, -2, 0x47 },
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

u8 D_800FC7D8[4] = { 0x00, PLAYER_FACING_RIGHT, 0x00, 0x00 };

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

void (*surface_hopper_launched_step_funcs[6])(struct MainObj*) = {
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

u8 surface_hopper_launch_facings[8] = { 0x00, PLAYER_FACING_RIGHT, PLAYER_FACING_RIGHT, 0x00, PLAYER_FACING_RIGHT, PLAYER_FACING_RIGHT, 0x00, 0x00 };

u8 surface_hopper_launch_animations[8] = { 0x1A, 0x09, 0x07, 0x08, 0x1A, 0x08, 0x07, 0x09 };
