// MainObj, main_object_update_funcs[23]
// 80055C54..80056788
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_22_bee_hive.h"
#include "main/mains/main_23_slope_skier.h"
#include "main/objects.h"
#include "main/1CF60.h"
#include "main/1E1BC.h"
#include "main/55C4.h"
#include "main/collision.h"
#include "main/object_motion.h"

extern u8 slope_skier_debris[];

void slope_skier_jump_rise(struct MainObj*);

// slope_skier_slide_funcs
void slope_skier_slide_start(struct MainObj*);

void slope_skier_slide_idle(void);

// slope_skier_step_funcs
void slope_skier_slide(struct MainObj* arg0);
void slope_skier_fall(struct MainObj* arg0);
void slope_skier_land(struct MainObj* arg0);
void slope_skier_jump(struct MainObj* arg0);

void slope_skier_wait_for_player(struct MainObj* arg0);

// slope_skier_state_funcs
extern void (*slope_skier_state_funcs[])(struct MainObj*);

void slope_skier_main(struct MainObj* arg0);
void slope_skier_despawn(struct MainObj* arg0);

extern void (*slope_skier_jump_funcs[])(struct MainObj*);
extern void (*slope_skier_slide_funcs[])(struct MainObj*);
extern void (*slope_skier_step_funcs[])(struct MainObj*);

extern union AnimationStep* slope_skier_animations[31];
extern struct Unk_unk68 slope_skier_hurt_box[];
extern struct Unk_unk68 slope_skier_terrain_box;
extern struct Unk_unk68 D_80106DF4[];
extern struct VisualSpawnOffset D_800FCE90[5];
extern struct Unk_unk68 D_800FCE9C[];
extern union AnimationStep jet_drone_anim_3[];
#if defined(MMX4_PC) || defined(MMX4_SATURN)

static struct VisualObj* main_23_spawn_visual(struct MainObj* arg0, u8 facing);
#endif

void bee_hive_update(struct MainObj* self);

// bee_hive_init

// bee_hive_main

void bee_hive_despawn(struct MainObj* self);

void bee_hive_resume_step(struct MainObj* self);

void bee_hive_open(struct MainObj* self);

void bee_hive_open_start(struct MainObj* self);

// bee_hive_open_move

void bee_hive_open_end(struct MainObj* self);

void bee_hive_wait(struct MainObj* self);

void bee_hive_wait_start(struct MainObj* self);

void bee_hive_wait_watch(struct MainObj* self);

void bee_hive_release(struct MainObj* self);

void bee_hive_release_start(struct MainObj* self);

void func_800559BC(struct MainObj*);

void bee_hive_release_wait(struct MainObj* self);

void bee_hive_release_pause(struct MainObj* self);

void bee_hive_shake(struct MainObj* self);

void bee_hive_shake_start(struct MainObj* self);

void bee_hive_shake_end(struct MainObj* self);

void bee_hive_explode(struct MainObj* self);

void bee_hive_explode_start(struct MainObj* self);

void bee_hive_explode_smoke(struct MainObj* self);

void bee_hive_explode_done(void);

// bee_hive_spawn_bees

void slope_skier_read_slope(struct MainObj* self)
{
    s16 x_pos;
    s32 y_pos;
    u8 result;

    self->ext.main_23.unk81 = self->ext.main_23.unk80;
    x_pos = self->x_pos.i.hi;
    y_pos = (s16)(self->terrain_box->unk3
        + ((u16)self->y_pos.i.hi + (s8)(u8)self->terrain_box->unk1) + 1);

    result = func_8002D724(PLAYER_OBJECT(self), x_pos, y_pos);
    if (result == 0) {
#ifdef MMX4_PC
        result = func_8002D724(PLAYER_OBJECT(self), x_pos, (s16)(y_pos + 0x10));
#else
        result = ((s32(*)(struct PlayerObj*, s16, s32))func_8002D724)(
            PLAYER_OBJECT(self), x_pos, y_pos + 0x10);
#endif
        if (result == 0) {
            self->ext.main_23.unk80 = 3;
            return;
        }
    }

    if (result > 0x10 && result <= 0x1E) {
        if (result >= 0x19) {
            self->ext.main_23.unk80 = 2;
            if (result >= 0x1B) {
                if (self->unk15 == 0)
                    self->ext.main_23.unk80 = 0x82;
            } else if (self->unk15 != 0) {
                self->ext.main_23.unk80 = 0x82;
            }
        } else {
            self->ext.main_23.unk80 = 1;
            if (result >= 0x15) {
                if (self->unk15 == 0)
                    self->ext.main_23.unk80 = 0x81;
            } else if (self->unk15 != 0) {
                self->ext.main_23.unk80 = 0x81;
            }
        }
    } else if (result == 0x3E) {
        if (self->on_screen != 0) {
            spawn_explosion(BASE_OBJECT(self));
            spawn_debris(7, slope_skier_debris, self);
            self->state = (u8)self->state + 1;
        }
    } else if (result != 0x10) {
        self->ext.main_23.unk80 = 0;
    }
}

void slope_skier_land(struct MainObj* self)
{
    s8 step;
    u8 background_relative;
    u8 background_offset;

    step = self->unk6;
    if (step == 0) {
        self->unk6 = step + 1;
        slope_skier_read_slope(self);
        background_relative = self->ext.main_23.unk80;
        background_offset = background_relative & 0x7F;
        if (background_relative & 0x80) {
            self->unk15 ^= PLAYER_FACING_RIGHT;
        }
        set_animation(self, background_offset + 0x12);
        return;
    }
    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event != 0) {
        self->unk5 = 1;
        self->unk6 = 0;
    }
}

void slope_skier_fall(struct MainObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (self->unk6 == 0) {
        self->unk6 = self->unk6 + 1;
        self->y_speed = 0;
        self->gravity = FIXED(0.2578125);
        self->air_state = -1;
    }
    if (self->collision_flags & 8) {
        self->unk5 = 3;
        self->unk6 = 0;
        self->air_state = 0;
        return;
    }
    move_with_gravity(ANIMATED_OBJECT(self));
}

// slope_skier_jump_start

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_80055F1C(struct MainObj* arg0);
void func_80056054(struct MainObj* arg0);
void func_800562AC(struct MainObj* arg0);
void func_800564B4(struct MainObj* arg0);
#endif

void func_80055F1C(struct MainObj* arg0)
{
    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->ext.main_23.unk80 & 0x80) {
        arg0->y_speed = 0x40000;
        arg0->x_speed = arg0->unk15 != 0 ? 0x30000 : -0x30000;
    } else {
        arg0->y_speed = 0x38000;
        arg0->x_speed = arg0->unk15 != 0 ? 0x48000 : -0x48000;
    }
    arg0->gravity = 0x4200;
    arg0->air_state = 1;
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->unk6++;
        set_animation(arg0, 0x11);
    }
    move_with_gravity(ANIMATED_OBJECT(arg0));
}

void slope_skier_jump_rise(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_with_gravity(ANIMATED_OBJECT(self));
    if (self->y_speed < 0) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void slope_skier_jump(struct MainObj* self)
{
    slope_skier_jump_funcs[self->unk6](self);
}

// slope_skier_step_5
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_23_slope_skier", func_80056054);
#else
void func_80056054(struct MainObj* arg0)
{
    struct VisualObj* visual;
    u8 i;
    s32 x;
    s32 new_x;
    struct VisualSpawnOffset* offsets;

    switch (arg0->unk6) {
    case 0:
        arg0->unk6++;
        set_animation(arg0, arg0->ext.main_23.unk80 + 0xA);
        break;
    case 1:
        animate_object(ANIMATED_OBJECT(arg0));
        move_object(MOVING_OBJECT(arg0));
        if (arg0->animation_step.fields.event == 1) {
            if (arg0->ext.main_23.unk82 & 1) {
                arg0->unk5 = 1;
                arg0->unk6 = 0;
                arg0->ext.main_23.unk82 &= 0xFE;
                arg0->unk15 ^= PLAYER_FACING_RIGHT;
            }
        } else if (arg0->animation_step.fields.event == 2) {
            offsets = D_800FCE90;
            for (i = 0; i < 5; i++) {
                visual = find_free_visual_obj();
                if (visual != NULL) {
                    visual->active = 0x41;
                    visual->id = 3;
                    visual->unk2 = 5;
                    visual->bg_offset = arg0->bg_offset;
                    visual->unk15 = arg0->unk15 ^ 0x40;
                    visual->unk40 = arg0->unk40;
                    visual->unk3C = (void*)arg0->sprite_frames;
                    visual->animation_table = (u32**)arg0->animation_table;
                    visual->unk42 = arg0->unk42;
                    x = (s16)arg0->x_pos.i.hi;
                    if (arg0->unk15 != 0) {
                        new_x = x - offsets[i].x;
                    } else {
                        new_x = x + offsets[i].x;
                    }
                    visual->x_pos.i.hi = new_x;
                    visual->y_pos.i.hi = (u16)arg0->y_pos.i.hi + D_800FCE90[i].y;
                    visual->unk16 = arg0->unk16;
                    arg0->animation_step.fields.event = 0;
                }
            }
        }
        break;
    }
}
#endif

void slope_skier_slide_start(struct MainObj* self)
{
    self->unk6++;
    slope_skier_read_slope(self);
    self->x_speed = self->unk15 != 0 ? FIXED(4.5) : FIXED(-4.5);
    set_animation(self, (self->ext.main_23.unk80 & 0x7F) + 4);
    func_8001540C(2, SATURN_SOUND(0x3A, 0x3C), self);
}

// slope_skier_slide_move
#if defined(VERSION_EU) && !defined(MMX4_PC)
INCLUDE_ASM("main/nonmatchings/mains/main_23_slope_skier", func_800562AC);
#else
void func_800562AC(struct MainObj* arg0)
{
    struct VisualObj* visual;
    u8 hit = 0;
    u8 wall;
    s32 x;

    move_object(MOVING_OBJECT(arg0));
    animate_object(ANIMATED_OBJECT(arg0));
    slope_skier_read_slope(arg0);
    if (arg0->ext.main_23.unk81 != arg0->ext.main_23.unk80) {
        if (arg0->ext.main_23.unk80 == 3 || (arg0->ext.main_23.unk80 & 0x80)) {
            arg0->unk5 = 4;
            arg0->unk6 = 0;
            set_animation(arg0, arg0->ext.main_23.unk81 + 0xD);
        } else {
            set_animation(arg0, (arg0->ext.main_23.unk80 & 0x7F) + 4);
        }
    }
    if (arg0->unk15 != 0)
        wall = arg0->collision_flags & 1;
    else
        wall = arg0->collision_flags & 2;
    if (wall)
        hit = 1;
    if (hit) {
        arg0->unk5 = 5;
        arg0->unk6 = 0;
        arg0->ext.main_23.unk82 |= 1;
    }
    if (--arg0->unk7C == 0) {
        visual = find_free_visual_obj();
        if (visual != NULL) {
            visual->active = 0x41;
            visual->id = 3;
            visual->unk2 = 5;
            visual->bg_offset = arg0->bg_offset;
            visual->unk15 = arg0->unk15;
            visual->unk40 = arg0->unk40;
            visual->unk3C = (void*)arg0->sprite_frames;
            visual->animation_table = (u32**)arg0->animation_table;
            visual->unk42 = arg0->unk42;
            x = (s16)arg0->x_pos.i.hi;
            visual->x_pos.i.hi = arg0->unk15 != 0 ? x - 0x28 : x + 0x28;
#ifdef MMX4_PC
            visual->y_pos.i.hi = (u16)arg0->y_pos.i.hi + (s8)(arg0->ext.main_23.unk80 < 0x80 ? ((u8*)D_800FCE9C)[arg0->ext.main_23.unk80] : ((u8*)jet_drone_anim_3)[arg0->ext.main_23.unk80 - 0x80]);
#else
            visual->y_pos.i.hi = arg0->y_pos.i.hi + ((s8*)D_800FCE9C)[arg0->ext.main_23.unk80];
#endif
            visual->unk16 = arg0->unk16;
            arg0->unk7C = 5;
        }
    }
}
#endif

void slope_skier_slide_idle(void)
{
}

void slope_skier_slide(struct MainObj* self)
{
    slope_skier_slide_funcs[self->unk6](self);
}

// slope_skier_init
void func_800564B4(struct MainObj* arg0)
{
    arg0->unk5 = 1;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    switch (arg0->unk2) {
    case 0:
        arg0->unk15 = arg0->x_pos.val > g_Player.x_pos.val ? 0 : PLAYER_FACING_RIGHT;
        break;
    case 1:
        arg0->unk15 = 0;
        break;
    case 2:
        arg0->unk15 = PLAYER_FACING_RIGHT;
        break;
    }
    arg0->animation_table = (const u8* const*)slope_skier_animations;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->terrain_box = slope_skier_hurt_box;
    arg0->hurt_box = &slope_skier_terrain_box;
    arg0->attack_box = &slope_skier_terrain_box;
    arg0->hp = 3;
    arg0->contact_damage = 1;
    arg0->collision_data = (const u16*)D_80106DF4;
    arg0->ext.main_23.unk80 = 0;
    arg0->x_speed = 0;
    arg0->x_accel = 0;
    arg0->y_speed = 0;
    arg0->gravity = 0;
    arg0->air_state = 0;
    arg0->unk7C = 10;
    arg0->ext.main_23.unk81 = 0;
    arg0->ext.main_23.unk82 = 0;
    set_animation(arg0, arg0->ext.main_23.unk80 + 4);
}

void slope_skier_wait_for_player(struct MainObj* self)
{
    if (g_Player.x_pos.i.hi - self->x_pos.i.hi > 0xC0) {
        self->unk5 = 1;
    }
}

void slope_skier_main(struct MainObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    if (self->air_state == 0 && !(self->collision_flags & 8)) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
    if (func_8002DD04(self) < 0) {
        spawn_explosion(BASE_OBJECT(self));
        spawn_debris(7, slope_skier_debris, self);
        drop_item(BASE_OBJECT(self), 0x16);
    } else {
        func_8002D9BC(self);
        slope_skier_step_funcs[self->unk5](self);
        if (func_8002B1E8(BASE_OBJECT(self), 0x60, 0x40) == 0) {
            update_on_screen(BASE_OBJECT(self), 0x30, 0x30);
            return;
        }
    }
    self->state = (u8)self->state + 1;
}

void slope_skier_despawn(struct MainObj* self)
{
    despawn_object(OBJECT_HEADER(self));
}

void slope_skier_update(struct MainObj* self)
{
    slope_skier_state_funcs[self->state](self);
    CollisionRelated((struct PlayerObj*)self);
}

struct Unk_unk68 slope_skier_hurt_box[] = {
    { 0, 12, 16, 2 },
};

struct Unk_unk68 slope_skier_terrain_box = { -11, -16, 21, 29 };

struct Unk_unk68 D_800FCB50 = { 3, 3, 3, 0 };

union AnimationStep slope_skier_anim_0[] = {
    { 1, 0, 0, 0x06 },
};

union AnimationStep slope_skier_anim_1[] = {
    { 3, 0, 1, 0x07 },
    { 3, 0, 1, 0x08 },
    { 3, 0, 1, 0x09 },
    { 9, 0, 1, 0x0A },
    { 3, 0, 1, 0x09 },
    { 3, 0, 1, 0x08 },
    { 3, 0, 0, 0x01 },
};

union AnimationStep slope_skier_anim_2[] = {
    { 3, 0, 1, 0x07 },
    { 3, 0, 1, 0x0D },
    { 3, 0, 1, 0x0E },
    { 9, 0, 1, 0x0F },
    { 3, 0, 1, 0x0E },
    { 3, 0, 1, 0x0D },
    { 3, 0, 0, 0x03 },
};

union AnimationStep slope_skier_anim_3[] = {
    { 3, 0, 1, 0x07 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 9, 0, 1, 0x14 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 0, 0x05 },
};

union AnimationStep slope_skier_anim_4[] = {
    { 3, 0, 1, 0x00 },
    { 3, 0, -1, 0x01 },
};

union AnimationStep slope_skier_anim_5[] = {
    { 3, 0, 1, 0x02 },
    { 3, 0, -1, 0x03 },
};

union AnimationStep slope_skier_anim_6[] = {
    { 3, 0, 1, 0x04 },
    { 3, 0, -1, 0x05 },
};

union AnimationStep slope_skier_anim_7[] = {
    { 3, 0, 1, 0x08 },
    { 3, 0, 1, 0x09 },
    { 15, 0, 1, 0x0A },
    { 3, 0, 1, 0x09 },
    { 3, 0, 1, 0x08 },
    { 3, 0, 1, 0x0B },
    { 3, 0, 0, 0x0C },
};

union AnimationStep slope_skier_anim_8[] = {
    { 3, 0, 1, 0x0D },
    { 3, 0, 1, 0x0E },
    { 15, 0, 1, 0x0F },
    { 3, 0, 1, 0x0E },
    { 3, 0, 1, 0x0D },
    { 3, 0, 1, 0x10 },
    { 3, 0, 0, 0x11 },
};

union AnimationStep slope_skier_anim_9[] = {
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 15, 0, 1, 0x14 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x15 },
    { 3, 0, 0, 0x16 },
};

union AnimationStep slope_skier_anim_13[] = {
    { 1, 0, 1, 0x08 },
    { 1, 0, 1, 0x09 },
    { 2, 0, 1, 0x0A },
    { 2, 0, 1, 0x09 },
    { 1, 0, 0, 0x08 },
};

union AnimationStep slope_skier_anim_14[] = {
    { 3, 0, 1, 0x0D },
    { 3, 0, 1, 0x0E },
    { 12, 0, 1, 0x0F },
    { 3, 0, 1, 0x0E },
    { 3, 0, 0, 0x08 },
};

union AnimationStep slope_skier_anim_15[] = {
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 12, 0, 1, 0x14 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 0, 0x0D },
};

union AnimationStep slope_skier_anim_16[] = {
    { 3, 0, 1, 0x24 },
    { 9, 0, 1, 0x25 },
    { 3, 0, 1, 0x24 },
    { 3, 0, 1, 0x2B },
    { 3, 0, 1, 0x2C },
    { 21, 0, 1, 0x2D },
    { 3, 0, 1, 0x2C },
    { 3, 0, 1, 0x2B },
    { 3, 0, 1, 0x24 },
    { 3, 0, 0, 0x25 },
};

union AnimationStep slope_skier_anim_17[] = {
    { 3, 0, 1, 0x24 },
    { 9, 0, 1, 0x25 },
    { 3, 0, 1, 0x24 },
    { 3, 0, 1, 0x26 },
    { 3, 0, 1, 0x27 },
    { 21, 0, 1, 0x28 },
    { 3, 0, 1, 0x27 },
    { 3, 0, 1, 0x26 },
    { 3, 0, 1, 0x24 },
    { 3, 0, 0, 0x25 },
};

union AnimationStep slope_skier_anim_18[] = {
    { 3, 0, 1, 0x1E },
    { 15, 0, 1, 0x1F },
    { 3, 0, 1, 0x1E },
    { 2, 0, 1, 0x01 },
    { 1, 1, 0, 0x01 },
};

union AnimationStep slope_skier_anim_19[] = {
    { 3, 0, 1, 0x20 },
    { 15, 0, 1, 0x21 },
    { 3, 0, 1, 0x22 },
    { 2, 0, 1, 0x05 },
    { 1, 1, 0, 0x05 },
};

union AnimationStep slope_skier_anim_20[] = {
    { 3, 0, 1, 0x22 },
    { 15, 0, 1, 0x23 },
    { 3, 0, 1, 0x22 },
    { 2, 0, 1, 0x05 },
    { 1, 1, 0, 0x05 },
};

union AnimationStep slope_skier_anim_10[] = {
    { 3, 0, 1, 0x08 },
    { 3, 0, 1, 0x17 },
    { 3, 2, 1, 0x18 },
    { 3, 0, 1, 0x19 },
    { 3, 0, 1, 0x18 },
    { 15, 0, 1, 0x19 },
    { 3, 0, 1, 0x18 },
    { 3, 0, 1, 0x1A },
    { 3, 0, 1, 0x1B },
    { 15, 0, 1, 0x1C },
    { 3, 0, 1, 0x1B },
    { 3, 0, 1, 0x1A },
    { 3, 1, 0, 0x1D },
};

union AnimationStep slope_skier_anim_11[] = {
    { 3, 0, 1, 0x0D },
    { 3, 0, 1, 0x0E },
    { 9, 0, 1, 0x0F },
    { 3, 0, 1, 0x0E },
    { 3, 0, 1, 0x17 },
    { 3, 2, 1, 0x18 },
    { 3, 0, 1, 0x19 },
    { 3, 0, 1, 0x18 },
    { 15, 0, 1, 0x19 },
    { 3, 0, 1, 0x18 },
    { 3, 0, 1, 0x1A },
    { 3, 0, 1, 0x1B },
    { 15, 0, 1, 0x1C },
    { 3, 0, 1, 0x1B },
    { 3, 0, 1, 0x1A },
    { 3, 1, 0, 0x1D },
};

union AnimationStep slope_skier_anim_12[] = {
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 9, 0, 1, 0x14 },
    { 3, 0, 1, 0x13 },
    { 3, 0, 1, 0x17 },
    { 3, 2, 1, 0x18 },
    { 3, 0, 1, 0x19 },
    { 3, 0, 1, 0x18 },
    { 15, 0, 1, 0x19 },
    { 3, 0, 1, 0x18 },
    { 3, 0, 1, 0x1A },
    { 3, 0, 1, 0x1B },
    { 15, 0, 1, 0x1C },
    { 3, 0, 1, 0x1B },
    { 3, 0, 1, 0x1A },
    { 3, 1, 0, 0x1D },
};

union AnimationStep slope_skier_anim_21[] = {
    { 2, 0, 1, 0x29 },
    { 2, 0, 1, 0x2A },
    { 2, 0, 1, 0x29 },
    { 2, 0, 1, 0x2A },
    { 18, 0, -4, 0x29 },
};

union AnimationStep slope_skier_anim_22[] = {
    { 1, 0, 0, 0x2A },
};

union AnimationStep slope_skier_anim_23[] = {
    { 2, 0, 1, 0x2E },
    { 2, 0, 1, 0x2F },
    { 2, 0, 1, 0x30 },
    { 2, 0, 1, 0x31 },
    { 2, 0, 1, 0x32 },
    { 2, 0, 1, 0x33 },
    { 2, 0, 1, 0x34 },
    { 2, 0, 1, 0x35 },
    { 2, 0, 1, 0x36 },
    { 2, 0, 1, 0x37 },
    { 2, 0, 1, 0x38 },
    { 2, 0, 1, 0x39 },
    { 2, 0, 1, 0x3A },
    { 2, 0, 1, 0x3B },
    { 2, 0, -1, 0x3C },
};

union AnimationStep slope_skier_anim_24[] = {
    { 1, 0, 0, 0x3D },
};

union AnimationStep slope_skier_anim_25[] = {
    { 1, 0, 0, 0x3E },
};

union AnimationStep slope_skier_anim_26[] = {
    { 1, 0, 0, 0x3F },
};

union AnimationStep slope_skier_anim_27[] = {
    { 1, 0, 0, 0x40 },
};

union AnimationStep slope_skier_anim_28[] = {
    { 1, 0, 0, 0x41 },
};

union AnimationStep slope_skier_anim_29[] = {
    { 1, 0, 0, 0x42 },
};

union AnimationStep slope_skier_anim_30[] = {
    { 1, 0, 0, 0x43 },
};

union AnimationStep* slope_skier_animations[] = {
    slope_skier_anim_0,
    slope_skier_anim_1,
    slope_skier_anim_2,
    slope_skier_anim_3,
    slope_skier_anim_4,
    slope_skier_anim_5,
    slope_skier_anim_6,
    slope_skier_anim_7,
    slope_skier_anim_8,
    slope_skier_anim_9,
    slope_skier_anim_10,
    slope_skier_anim_11,
    slope_skier_anim_12,
    slope_skier_anim_13,
    slope_skier_anim_14,
    slope_skier_anim_15,
    slope_skier_anim_16,
    slope_skier_anim_17,
    slope_skier_anim_18,
    slope_skier_anim_19,
    slope_skier_anim_20,
    slope_skier_anim_21,
    slope_skier_anim_22,
    slope_skier_anim_23,
    slope_skier_anim_24,
    slope_skier_anim_25,
    slope_skier_anim_26,
    slope_skier_anim_27,
    slope_skier_anim_28,
    slope_skier_anim_29,
    slope_skier_anim_30,
};

u8 slope_skier_debris[] = {
    0x18,
    0x19,
    0x1A,
    0x1B,
    0x1C,
    0x1D,
    0x1E,
    0x00,
};

void (*slope_skier_jump_funcs[])() = {
    func_80055F1C,
    slope_skier_jump_rise,
};

struct VisualSpawnOffset D_800FCE90[5] = {
    { -23, -5 },
    { -23, 2 },
    { -29, 1 },
    { -29, 4 },
    { -39, -2 },
};

struct Unk_unk68 D_800FCE9C[] = {
    { -1, -6, 246, 0 },
};

void (*slope_skier_slide_funcs[])() = {
    slope_skier_slide_start,
    func_800562AC,
    slope_skier_slide_idle,
};

void (*slope_skier_step_funcs[])() = {
    enemy_hit_reaction,
    slope_skier_slide,
    slope_skier_fall,
    slope_skier_land,
    slope_skier_jump,
    func_80056054,
    slope_skier_wait_for_player,
};

void (*slope_skier_state_funcs[])() = {
    func_800564B4,
    slope_skier_main,
    slope_skier_despawn,
};

#if defined(MMX4_PC) || defined(MMX4_SATURN)
static struct VisualObj* main_23_spawn_visual(struct MainObj* arg0, u8 facing)
{
    struct VisualObj* visual = find_free_visual_obj();

    if (visual == NULL)
        return NULL;
    visual->active = 0x41;
    visual->id = 3;
    visual->unk2 = 5;
    visual->bg_offset = arg0->bg_offset;
    visual->unk15 = facing;
    visual->unk40 = arg0->unk40;
    visual->unk3C = (void*)arg0->sprite_frames;
    visual->animation_table = (u32**)arg0->animation_table;
    visual->unk42 = arg0->unk42;
    return visual;
}
#endif
