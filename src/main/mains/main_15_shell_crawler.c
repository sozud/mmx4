// MainObj, main_object_update_funcs[15]
// 8004D930..8004E890
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_15_shell_crawler.h"
#include "main/objects.h"
#include "main/1CF60.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/collision_bounds.h"
#include "main/object_motion.h"

extern u8 shell_crawler_debris[4];

// shell_crawler_step_funcs
extern void (*shell_crawler_step_funcs[])(struct MainObj*);
void shell_crawler_walk(struct MainObj* arg0);
void shell_crawler_land(struct MainObj* arg0);

void shell_crawler_hop(struct MainObj* arg0);

void shell_crawler_despawn(struct MainObj* arg0);

void shell_crawler_buried(struct MainObj*);

extern void (*shell_crawler_state_funcs[])(struct MainObj*);

void shell_crawler_buried(struct MainObj* self)
{
    if (!(func_8002D724(PLAYER_OBJECT(self), self->x_pos.i.hi,
              self->y_pos.i.hi)
            & 0xFF)) {
        self->state = 1;
        self->unk5 = 1;
        self->unk2 = 0;
        self->hurt_box = &shell_crawler_body_box;
        self->attack_box = &shell_crawler_body_box;
    }

    if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        if (self->unk2 == 2) {
            update_on_screen(BASE_OBJECT(self), 0x25, 0x25);
        }
    } else {
        self->state = 2;
    }
}

// shell_crawler_check_hop

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004D9CC(struct MainObj* arg0);
void func_8004DCB0(struct MainObj* arg0);
static void main_15_spawn_spark(struct MainObj* arg0, u8 index);
void func_8004E300(struct MainObj* arg0);
void func_8004E490(struct MainObj* arg0);
void func_8004E55C(struct MainObj* arg0);
extern struct Unk_unk68 shell_crawler_terrain_box;
extern union AnimationStep* shell_crawler_animations[14];
static void main_15_spawn_spark(struct MainObj* arg0, u8 index)
{
    struct ShotObj* shot = find_free_shot_obj();

    if (shot == NULL)
        return;
    shot->active = 0x41;
    shot->id = 0xA;
    shot->unk42 = OBJECT_CLUT(0x7885);
    shot->bg_offset = arg0->bg_offset;
    shot->x_pos.val = arg0->x_pos.val;
    shot->unk2 = index * 2;
    shot->y_pos.val = arg0->y_pos.val;
    set_velocity_from_angle(MOVING_OBJECT(shot), (s8)(index * 2));
    arg0->unk7C = 0xA;
}
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004D9CC(struct MainObj* arg0)
{
    struct Main0Ext* ext = &arg0->ext.main_0;
    s32 dy;

    if (arg0->air_state != 0 || (ext->background_relative & 3))
        return;
    if (ext->flags[1] != 0) {
        ext->flags[1]--;
        return;
    }
    dy = arg0->y_pos.i.hi - g_Player.y_pos.i.hi;
    if (dy < 0)
        dy = -dy;
    if (dy >= 0x28) {
        ext->index = 0;
        return;
    }
    if (arg0->unk15 != 0) {
        if (g_Player.x_pos.i.hi < arg0->x_pos.i.hi + 0x50)
            ext->index++;
        else
            ext->index = 0;
    } else {
        if (arg0->x_pos.i.hi - 0x50 < g_Player.x_pos.i.hi)
            ext->index++;
        else
            ext->index = 0;
    }
    if (ext->index >= 0x3D) {
        arg0->unk5 = 4;
        arg0->unk6 = 0;
        set_animation(arg0, 7);
        ext->index = 0;
        ext->background_relative |= 2;
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_15_shell_crawler", func_8004D9CC);
#endif

// shell_crawler_check_shell
void func_8004DB10(struct MainObj* self)
{
    s16 x;
    s16 y;

    if (self->air_state != 0) {
        return;
    }

    CollisionRelated(PLAYER_OBJECT(self));
    if (!(self->collision_flags & 8)) {
        set_animation(self, 3);
        self->unk5 = 2;
        self->gravity = FIXED(0.2578125);
        self->unk6 = 0;
        self->y_speed = 0;
        self->x_accel = 0;
        self->air_state = -1;
        return;
    }

    if (self->unk15 != 0) {
        x = self->x_pos.u.hi + self->terrain_box->unk0 + self->terrain_box->unk2;
    } else {
        x = self->x_pos.u.hi - self->terrain_box->unk0 - self->terrain_box->unk2;
    }
    y = self->terrain_box->unk3 + (self->y_pos.u.hi + self->terrain_box->unk1) + 8;
    if (func_8002D724(PLAYER_OBJECT(self), x, y) != 0) {
        return;
    }

    if (self->unk2 == 1) {
        self->unk15 = self->unk15 == 0 ? PLAYER_FACING_RIGHT : 0;
        self->x_speed = -self->x_speed;
        return;
    }
    if (self->collision_flags & 3) {
        return;
    }

    set_animation(self, 2);
    self->unk5 = 5;
    self->y_speed = FIXED(3.5);
    self->unk6 = 0;
    self->gravity = FIXED(0.2578125);
    self->x_speed = self->unk15 != 0 ? FIXED(1) : FIXED(-1);
    self->air_state = 1;
}

// shell_crawler_check_shoot
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004DCB0(struct MainObj* arg0)
{
    struct Main0Ext* ext = &arg0->ext.main_0;
    struct WeaponObj* weapon;
    s32 dy;

    if (arg0->air_state != 0 || (ext->background_relative & 1))
        return;
    if (ext->flags[0] != 0) {
        ext->flags[0]--;
        return;
    }
    for (weapon = weapon_objects; weapon < weapon_objects + COUNT(weapon_objects); weapon++) {
        if (!weapon->active || weapon->id != 0)
            continue;
        if (arg0->unk15 != 0) {
            if (g_Player.unk15 == 0 && arg0->x_pos.val < g_Player.x_pos.val) {
                dy = weapon->y_pos.i.hi - arg0->y_pos.i.hi;
                if (dy < 0)
                    dy = -dy;
                if (dy < 0x18 && weapon->x_pos.i.hi < arg0->x_pos.i.hi + 0x80)
                    ext->background_relative |= 1;
            }
        } else {
            if (g_Player.unk15 != 0 && g_Player.x_pos.val < arg0->x_pos.val) {
                dy = weapon->y_pos.i.hi - arg0->y_pos.i.hi;
                if (dy < 0)
                    dy = -dy;
                if (dy < 0x18 && arg0->x_pos.i.hi - 0x80 < weapon->x_pos.i.hi)
                    ext->background_relative |= 1;
            }
        }
        if (ext->background_relative & 1) {
            arg0->unk5 = 3;
            arg0->unk6 = 0;
            set_animation(arg0, 5);
            return;
        }
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_15_shell_crawler", func_8004DCB0);
#endif

void shell_crawler_hop(struct MainObj* self)
{
    s8 state;

    animate_object(ANIMATED_OBJECT(self));
    state = self->unk6;
    if (state == 0) {
        if (self->animation_step.fields.event != 0) {
            self->unk6 = state + 1;
        }
    } else {
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->y_speed < 0) {
            self->unk6++;
            set_animation(self, 3);
            self->unk5 = 2;
            self->unk6 = 0;
            self->y_speed = 0;
            self->gravity = FIXED(0.2578125);
            self->x_accel = 0;
            self->air_state = -1;
        }
    }
}

void shell_crawler_land(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (self->unk6 == 0) {
        self->collision_data = (const u16*)D_801069F4;
        move_with_gravity(ANIMATED_OBJECT(self));
        if (self->collision_flags & 8) {
            set_animation(self, 4);
            self->unk6++;
            self->y_speed = 0;
            self->gravity = 0;
            self->x_speed = 0;
            self->x_accel = 0;
        }
    } else if (self->animation_step.fields.relative_step == 0) {
        set_animation(self, 1);
        self->unk5 = 1;
        self->unk6 = 0;
        self->air_state = 0;
    }
}

void shell_crawler_shell(struct MainObj* self)
{
    switch (self->unk6) {
    case 0:
        self->unk6++;
        set_animation(self, 5);
        self->unk7C = 0x3C;
    case 1:
        if (0 != self->animation_step.fields.event) {
            self->collision_data = D_801060F0;
            self->hurt_box = &shell_crawler_shell_box;
            self->attack_box = &shell_crawler_shell_box;
        }
        if (--self->unk7C == 0) {
            self->unk6++;
            set_animation(self, 6);
        }
        break;
    case 2:
        if (self->animation_step.fields.relative_step == 0) {
            set_animation(self, 1);
            self->ext.main_0.background_relative &= 0xFE;
            self->unk5 = 1;
            self->unk6 = 0;
            self->collision_data = D_801069F4;
            self->hurt_box = &shell_crawler_body_box;
            self->attack_box = &shell_crawler_body_box;
            self->ext.main_0.flags[0] = 0x78;
        }
        break;
    }
    animate_object(ANIMATED_OBJECT(self));
}

void shell_crawler_shoot(struct MainObj* self)
{
    struct ShotObj* shot;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->animation_step.fields.event = 0;
        shot = find_free_shot_obj();
        if (shot != NULL) {
            shot->active = 0x41;
            shot->id = 8;
            shot->x_pos.val = self->x_pos.val;
            shot->y_pos.val = self->y_pos.val;
            shot->unk3C = (void*)self->sprite_frames;
            shot->unk40 = self->unk40;
            shot->unk42 = self->unk42;
            shot->bg_offset = (u8)self->bg_offset;
            shot->animation_table = (u32**)self->animation_table;
            shot->unk15 = self->unk15;
        }
    }
    if (self->animation_step.fields.relative_step == 0) {
        self->unk5 = 1;
        self->unk6 = 0;
        set_animation(self, 1);
        self->ext.main_0.flags[1] = 0x78;
        self->ext.main_0.background_relative &= 0xFD;
    }
}

void shell_crawler_walk(struct MainObj* self)
{
    if (self->unk6 == 0) {
        self->collision_data = D_801069F4;
        self->hurt_box = &shell_crawler_body_box;
        self->attack_box = &shell_crawler_body_box;
        self->unk6++;
        set_animation(self, 1);
        self->x_speed = (self->unk15 != 0 ? FIXED(0.375) : FIXED(-0.375));
        self->x_accel = 0;
        self->y_speed = 0;
        self->gravity = 0;
    }

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (self->unk15 != 0) {
        if (self->collision_flags & 1) {
            self->unk15 = 0;
            self->x_speed = -self->x_speed;
        }
    } else if (self->collision_flags & 2) {
        self->unk15 = PLAYER_FACING_RIGHT;
        self->x_speed = -self->x_speed;
    }
}

// shell_crawler_frozen
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004E300(struct MainObj* arg0)
{
    u8 i;

    switch (arg0->unk6) {
    case 0:
        arg0->unk6++;
        arg0->gravity = 0x4200;
        arg0->air_state = -1;
        arg0->y_speed = 0;
        arg0->x_speed = 0;
        arg0->x_accel = 0;
        arg0->collision_data = D_801069F4;
        set_animation(arg0, 0xD);
        /* fallthrough */
    case 1:
        if (arg0->collision_flags & 8) {
            arg0->gravity = 0;
            arg0->air_state = 0;
        }
        move_with_gravity(ANIMATED_OBJECT(arg0));
        break;
    }
    if (func_8002DD04(arg0) != 0 || func_8002D9BC(arg0) != 0) {
        arg0->state = 2;
        spawn_explosion(BASE_OBJECT(arg0));
        for (i = 0; i < 0x10; i += 2)
            main_15_spawn_spark(arg0, i);
    }
    if (func_8002B1E8(BASE_OBJECT(arg0), 0x40, 0x40) != 0) {
        arg0->state = 2;
        return;
    }
    update_on_screen(BASE_OBJECT(arg0), 0x25, 0x25);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_15_shell_crawler", func_8004E300);
#endif

// shell_crawler_thaw
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004E490(struct MainObj* arg0)
{
    u8 i;

    if (--arg0->unk7C != 0)
        return;
    arg0->state = 2;
    for (i = 1; i < 0x10; i += 2)
        main_15_spawn_spark(arg0, i);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_15_shell_crawler", func_8004E490);
#endif

// shell_crawler_init
#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8004E55C(struct MainObj* arg0)
{
    struct Main0Ext* ext = &arg0->ext.main_0;

    arg0->unk5 = 1;
    arg0->state++;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->animation_table = (const u8* const*)shell_crawler_animations;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->terrain_box = &shell_crawler_terrain_box;
    arg0->hurt_box = &shell_crawler_body_box;
    arg0->attack_box = &shell_crawler_body_box;
    arg0->hp = 3;
    arg0->collision_data = D_801069F4;
    arg0->invincibility_timer = 0;
    arg0->air_state = 0;
    arg0->contact_damage = 1;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    ext->background_relative = 0;
    ext->flags[0] = 0;
    ext->index = 0;
    ext->flags[1] = 0;
    arg0->unk15 = g_Player.x_pos.val < arg0->x_pos.val ? 0 : PLAYER_FACING_RIGHT;
    if ((u8)(arg0->unk2 - 2) < 2) {
        arg0->state = 5;
        arg0->hurt_box = NULL;
        arg0->attack_box = NULL;
        arg0->x_pos.i.hi = (arg0->x_pos.i.hi & ~0xF) + 8;
        arg0->y_pos.i.hi = (arg0->y_pos.i.hi & ~0xF) + 0x14;
        set_animation(arg0, 0);
    } else {
        set_animation(arg0, 1);
    }
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_15_shell_crawler", func_8004E55C);
#endif

void shell_crawler_main(struct MainObj* self)
{
    s32 hit;

#ifdef MMX4_SATURN
    if (*(u16*)&engine_obj.stage == 0x201 && engine_obj.character_state.bytes[0] != 0) {
#else
    if (*(u16*)&engine_obj.stage == 0x102 && engine_obj.character_state.bytes[0] != 0) {
#endif
        if ((self->x_pos.i.hi >= 0xC0F && self->x_pos.i.hi <= 0xDF0) || (u16)(self->x_pos.i.hi - 0x100F) < 0x1E2
            || (u16)(self->x_pos.i.hi - 0x1315) < 0x1DC || (self->x_pos.i.hi >= 0x1613 && self->x_pos.i.hi <= 0x17D1)) {
            self->state = 3;
            self->unk6 = 0;
            return;
        }
    }
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    hit = func_8002DD04(self);
    if (hit < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(4, shell_crawler_debris, self);
        drop_item(BASE_OBJECT(self), 0x12);
        self->state++;
        return;
    }
    func_8004DB10(self);
    func_8004D9CC(self);
    func_8004DCB0(self);
    shell_crawler_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x40, 0x40) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x25, 0x25);
    } else {
        self->state++;
    }
}

void shell_crawler_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void shell_crawler_update(struct MainObj* self)
{
    shell_crawler_state_funcs[self->state](self);
    if (self->state != 5) {
        CollisionRelated(PLAYER_OBJECT(self));
    }
}

struct Unk_unk68 shell_crawler_terrain_box = { 0, 1, 11, 12 };

struct Unk_unk68 shell_crawler_body_box = { -11, -16, 21, 29 };

struct Unk_unk68 shell_crawler_shell_box = { -12, -4, 21, 18 };

union AnimationStep shell_crawler_anim_0[] = {
    { 1, 0, 0, 0x00 },
};

union AnimationStep shell_crawler_anim_1[] = {
    { 8, 0, 1, 0x01 },
    { 8, 0, 1, 0x02 },
    { 8, 0, 1, 0x03 },
    { 3, 0, 1, 0x04 },
    { 5, 0, 1, 0x05 },
    { 8, 0, 1, 0x06 },
    { 8, 0, 1, 0x07 },
    { 8, 0, 1, 0x08 },
    { 3, 0, 1, 0x09 },
    { 5, 0, -9, 0x0A },
};

union AnimationStep shell_crawler_anim_2[] = {
    { 6, 0, 1, 0x00 },
    { 10, 0, 1, 0x0B },
    { 2, 1, 1, 0x0C },
    { 2, 0, 1, 0x0D },
    { 3, 0, 1, 0x0E },
    { 1, 0, 0, 0x0E },
};

union AnimationStep shell_crawler_anim_3[] = {
    { 2, 0, 1, 0x0F },
    { 2, 0, -1, 0x10 },
};

union AnimationStep shell_crawler_anim_4[] = {
    { 3, 0, 1, 0x11 },
    { 10, 0, 1, 0x0B },
    { 2, 0, 1, 0x12 },
    { 3, 0, 1, 0x00 },
    { 2, 0, 1, 0x12 },
    { 1, 0, 0, 0x12 },
};

union AnimationStep shell_crawler_anim_5[] = {
    { 6, 0, 1, 0x00 },
    { 1, 0, 1, 0x12 },
    { 2, 0, 1, 0x13 },
    { 2, 1, 1, 0x14 },
    { 1, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x17 },
    { 1, 0, 0, 0x18 },
};

union AnimationStep shell_crawler_anim_6[] = {
    { 6, 0, 1, 0x18 },
    { 1, 0, 1, 0x17 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x15 },
    { 1, 0, 1, 0x14 },
    { 2, 0, 1, 0x13 },
    { 2, 0, 1, 0x12 },
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x12 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep shell_crawler_anim_7[] = {
    { 6, 0, 1, 0x00 },
    { 6, 0, 1, 0x19 },
    { 8, 0, 1, 0x1A },
    { 2, 1, 1, 0x1B },
    { 2, 0, 1, 0x1C },
    { 2, 0, 1, 0x1D },
    { 10, 0, 1, 0x00 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep shell_crawler_anim_8[] = {
    { 2, 0, 1, 0x1E },
    { 2, 0, 1, 0x1F },
    { 2, 0, -2, 0x20 },
};

union AnimationStep shell_crawler_anim_9[] = {
    { 1, 0, 0, 0x21 },
};

union AnimationStep shell_crawler_anim_10[] = {
    { 1, 0, 0, 0x22 },
};

union AnimationStep shell_crawler_anim_11[] = {
    { 1, 0, 0, 0x23 },
};

union AnimationStep shell_crawler_anim_12[] = {
    { 1, 0, 0, 0x24 },
};

union AnimationStep shell_crawler_anim_13[] = {
    { 1, 0, 0, 0x25 },
};

union AnimationStep* shell_crawler_animations[14] = {
    shell_crawler_anim_0,
    shell_crawler_anim_1,
    shell_crawler_anim_2,
    shell_crawler_anim_3,
    shell_crawler_anim_4,
    shell_crawler_anim_5,
    shell_crawler_anim_6,
    shell_crawler_anim_7,
    shell_crawler_anim_8,
    shell_crawler_anim_9,
    shell_crawler_anim_10,
    shell_crawler_anim_11,
    shell_crawler_anim_12,
    shell_crawler_anim_13,
};

u8 shell_crawler_debris[4] = { 9, 10, 11, 12 };

void (*shell_crawler_step_funcs[6])() = {
    enemy_hit_reaction,
    shell_crawler_walk,
    shell_crawler_land,
    shell_crawler_shell,
    shell_crawler_shoot,
    shell_crawler_hop,
};

void (*shell_crawler_state_funcs[6])(struct MainObj*) = {
    func_8004E55C,
    shell_crawler_main,
    shell_crawler_despawn,
    func_8004E300,
    func_8004E490,
    shell_crawler_buried,
};
