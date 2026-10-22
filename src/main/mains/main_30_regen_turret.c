// MainObj, main_object_update_funcs[30]
// 8005B3FC..8005B894
#include "common.h"
#include "weapon_resources.h"
#include "main/mains/main_30_regen_turret.h"
#include "main/objects.h"
#include "main/1E1BC.h"
#include "main/55C4.h"

extern void (*regen_turret_rebuild_funcs[])(struct MainObj*);

void regen_turret_main(struct MainObj*);

// regen_turret_step_funcs
extern void (*regen_turret_step_funcs[])(struct MainObj*);
void regen_turret_start_idle(struct MainObj* arg0);
void regen_turret_idle(struct MainObj* arg0);

// regen_turret_rebuild_funcs
void regen_turret_rebuild_break(struct MainObj*);
void regen_turret_rebuild_wait(struct MainObj*);
void regen_turret_rebuild_finish(struct MainObj*);

extern void (*regen_turret_state_funcs[])(struct MainObj*);

void regen_turret_update(struct MainObj* self)
{
    regen_turret_state_funcs[self->state](self);
}

// regen_turret_init

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005B438(struct MainObj* arg0);
extern union AnimationStep* regen_turret_animations[];
extern struct Unk_unk68 regen_turret_hurt_box[];
extern struct Unk_unk68 regen_turret_terrain_box[];
extern struct Unk_unk68 D_80107174[];
#endif

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_8005B438(struct MainObj* arg0)
{
    arg0->unk5 = 2;
    arg0->state++;
    arg0->bg_offset = g_Player.bg_offset;
    arg0->unk15 = arg0->unk2 != 0 ? PLAYER_FACING_RIGHT : 0;
    arg0->animation_table = (const u8* const*)regen_turret_animations;
    arg0->collision_data = (const u16*)D_80107174;
    arg0->hurt_box = (const u8*)regen_turret_terrain_box;
    arg0->attack_box = (const u8*)regen_turret_hurt_box;
    arg0->unk16 = VISUAL_SATURN_LAYER(6);
    arg0->terrain_box = NULL;
    arg0->invincibility_timer = 0;
    arg0->hp = 6;
    arg0->contact_damage = 3;
    arg0->air_state = 0;
    arg0->unk7C = 0;
    set_animation(arg0, 0);
    update_on_screen(BASE_OBJECT(arg0), 0x50, 0x50);
}
#else
INCLUDE_ASM("main/nonmatchings/mains/main_30_regen_turret", func_8005B438);
#endif

void regen_turret_start_idle(struct MainObj* self)
{
    self->unk5 = 2;
    set_animation(self, 10);
}

void regen_turret_idle(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5++;
        set_animation(self, 1);
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void regen_turret_fire(struct MainObj* self)
{
    struct ShotObj* shot;

    if (self->animation_step.fields.relative_step < 0) {
        self->unk5--;

        if (self->unk15 == 0
                ? self->x_pos.i.hi < g_Player.x_pos.i.hi
                : self->x_pos.i.hi > g_Player.x_pos.i.hi) {
            shot = find_free_shot_obj();
            if (shot != NULL) {
                shot->active = 0x41;
                shot->id = 0xF;
                shot->unk7C = WEAPON_OBJECT(self);
                shot->state = 0;
                shot->unk5 = 0;
                shot->unk6 = 0;
            }
        }

        set_animation(self, 0xA);
        return;
    }

    animate_object(ANIMATED_OBJECT(self));
}

void regen_turret_main(struct MainObj* self)
{
    s32 hit;

    hit = func_8002DD04(self);
    if (hit < 0) {
        self->active |= 4;
        self->state++;
        self->unk5 = 0;
        self->unk42 &= 0x7FFF;
        return;
    }

    regen_turret_step_funcs[self->unk5](self);
    func_8002D9BC(self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
        return;
    }
    despawn_object(OBJECT_HEADER(self));
}

void regen_turret_rebuild_break(struct MainObj* self)
{
    self->unk5++;
    spawn_explosion(BASE_OBJECT(self));
    spawn_debris(5, regen_turret_debris, self);
    set_animation(self, 2);
}

void regen_turret_rebuild_wait(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        self->unk5++;
        set_animation(self, 3);
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void regen_turret_rebuild_finish(struct MainObj* self)
{
    if (self->animation_step.fields.relative_step < 0) {
        self->state = 1;
        self->unk5 = 2;
        self->hp = 6;
        set_animation(self, 0);
        self->active &= ~4;
    } else {
        animate_object(ANIMATED_OBJECT(self));
    }
}

void regen_turret_rebuild(struct MainObj* self)
{
    regen_turret_rebuild_funcs[self->unk5](self);
    if (func_8002B1E8(BASE_OBJECT(self), 0x80, 0x80) == 0) {
        update_on_screen(BASE_OBJECT(self), 0x50, 0x50);
    } else {
        despawn_object(OBJECT_HEADER(self));
    }
}

struct Unk_unk68 regen_turret_hurt_box[] = {
    { -22, -13, 0x14, 0x19 },
};

struct Unk_unk68 regen_turret_terrain_box[] = {
    { -27, -20, 0x1A, 0x28 },
};

union AnimationStep regen_turret_anim_0[] = {
    { 8, 0, 1, 0x00 },
    { 8, 0, 1, 0x01 },
    { 8, 0, 1, 0x02 },
    { 8, 0, 1, 0x03 },
    { 8, 0, 1, 0x04 },
    { 6, 0, 1, 0x05 },
    { 15, 0, 1, 0x06 },
    { 6, 0, 1, 0x07 },
    { 8, 0, 1, 0x08 },
    { 6, 0, 1, 0x07 },
    { 119, 0, 1, 0x06 },
    { 1, 0, -1, 0x06 },
};

union AnimationStep regen_turret_anim_1[] = {
    { 5, 0, 1, 0x06 },
    { 6, 0, 1, 0x09 },
    { 8, 0, 1, 0x0A },
    { 6, 0, 1, 0x09 },
    { 4, 0, 1, 0x06 },
    { 1, 0, -5, 0x06 },
};

union AnimationStep regen_turret_anim_2[] = {
    { 119, 0, 1, 0x0B },
    { 1, 0, -1, 0x0B },
};

union AnimationStep regen_turret_anim_3[] = {
    { 4, 0, 1, 0x0B },
    { 5, 0, 1, 0x0C },
    { 7, 0, 1, 0x0D },
    { 5, 0, 1, 0x0C },
    { 21, 0, 1, 0x0B },
    { 6, 0, 1, 0x0E },
    { 5, 0, 1, 0x0F },
    { 4, 0, 1, 0x10 },
    { 3, 0, 1, 0x11 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x00 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x00 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x00 },
    { 1, 0, 1, 0x14 },
    { 1, 0, 1, 0x00 },
    { 1, 0, 1, 0x14 },
    { 1, 0, -20, 0x00 },
};

union AnimationStep regen_turret_anim_4[] = {
    { 2, 0, 1, 0x15 },
    { 2, 0, 1, 0x16 },
    { 2, 0, 1, 0x17 },
    { 2, 0, 1, 0x18 },
    { 2, 0, 1, 0x19 },
    { 1, 0, 1, 0x1A },
    { 1, 0, -6, 0x1A },
};

union AnimationStep regen_turret_anim_10[] = {
    { 119, 0, 1, 0x06 },
    { 1, 0, -1, 0x06 },
};

union AnimationStep regen_turret_anim_5[] = {
    { 1, 0, 0, 0x1B },
};

union AnimationStep regen_turret_anim_6[] = {
    { 1, 0, 0, 0x1C },
};

union AnimationStep regen_turret_anim_7[] = {
    { 1, 0, 0, 0x1D },
};

union AnimationStep regen_turret_anim_8[] = {
    { 1, 0, 0, 0x1E },
};

union AnimationStep regen_turret_anim_9[] = {
    { 1, 0, 0, 0x1F },
};

union AnimationStep* regen_turret_animations[] = {
    regen_turret_anim_0,
    regen_turret_anim_1,
    regen_turret_anim_2,
    regen_turret_anim_3,
    regen_turret_anim_4,
    regen_turret_anim_5,
    regen_turret_anim_6,
    regen_turret_anim_7,
    regen_turret_anim_8,
    regen_turret_anim_9,
    regen_turret_anim_10,
};

u8 regen_turret_debris[] = {
    0x05,
    0x06,
    0x07,
    0x08,
    0x09,
    0x00,
    0x00,
    0x00,
};

void (*regen_turret_state_funcs[])(struct MainObj*) = {
    func_8005B438,
    regen_turret_main,
    regen_turret_rebuild,
};

void (*regen_turret_step_funcs[])(struct MainObj*) = {
    enemy_hit_reaction,
    regen_turret_start_idle,
    regen_turret_idle,
    regen_turret_fire,
};

void (*regen_turret_rebuild_funcs[])(struct MainObj*) = {
    regen_turret_rebuild_break,
    regen_turret_rebuild_wait,
    regen_turret_rebuild_finish,
};
