// MainObj, main_object_update_funcs[30]
// 8005B3FC..8005B894
#include "common.h"
#include "func_tables.h"

void regen_turret_update(struct MainObj* self)
{
    regen_turret_state_funcs[self->state](self);
}

// regen_turret_init
INCLUDE_ASM("main/nonmatchings/mains/main_30_regen_turret", func_8005B438);

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
    { 0x00010008 },
    { 0x01010008 },
    { 0x02010008 },
    { 0x03010008 },
    { 0x04010008 },
    { 0x05010006 },
    { 0x0601000F },
    { 0x07010006 },
    { 0x08010008 },
    { 0x07010006 },
    { 0x06010077 },
    { 0x06FF0001 },
};

union AnimationStep regen_turret_anim_1[] = {
    { 0x06010005 },
    { 0x09010006 },
    { 0x0A010008 },
    { 0x09010006 },
    { 0x06010004 },
    { 0x06FB0001 },
};

union AnimationStep regen_turret_anim_2[] = {
    { 0x0B010077 },
    { 0x0BFF0001 },
};

union AnimationStep regen_turret_anim_3[] = {
    { 0x0B010004 },
    { 0x0C010005 },
    { 0x0D010007 },
    { 0x0C010005 },
    { 0x0B010015 },
    { 0x0E010006 },
    { 0x0F010005 },
    { 0x10010004 },
    { 0x11010003 },
    { 0x12010003 },
    { 0x13010003 },
    { 0x14010001 },
    { 0x00010001 },
    { 0x14010001 },
    { 0x00010001 },
    { 0x14010001 },
    { 0x00010001 },
    { 0x14010001 },
    { 0x00010001 },
    { 0x14010001 },
    { 0x00EC0001 },
};

union AnimationStep regen_turret_anim_4[] = {
    { 0x15010002 },
    { 0x16010002 },
    { 0x17010002 },
    { 0x18010002 },
    { 0x19010002 },
    { 0x1A010001 },
    { 0x1AFA0001 },
};

union AnimationStep regen_turret_anim_10[] = {
    { 0x06010077 },
    { 0x06FF0001 },
};

union AnimationStep regen_turret_anim_5[] = {
    { 0x1B000001 },
};

union AnimationStep regen_turret_anim_6[] = {
    { 0x1C000001 },
};

union AnimationStep regen_turret_anim_7[] = {
    { 0x1D000001 },
};

union AnimationStep regen_turret_anim_8[] = {
    { 0x1E000001 },
};

union AnimationStep regen_turret_anim_9[] = {
    { 0x1F000001 },
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
