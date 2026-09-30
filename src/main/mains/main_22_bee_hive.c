// MainObj, main_object_update_funcs[22]
// 80054FE8..80055C54
#include "common.h"
#include "func_tables.h"

void bee_hive_update(struct MainObj* self)
{
    bee_hive_state_funcs[self->state](self);
}

// bee_hive_init
INCLUDE_ASM("main/nonmatchings/mains/main_22_bee_hive", func_80055024);

// bee_hive_main
INCLUDE_ASM("main/nonmatchings/mains/main_22_bee_hive", func_80055164);

void bee_hive_despawn(struct MainObj* self)
{
    self->ext.main_22.saved_unk5 = 0;
    self->ext.main_22.unk84 = 0;
    self->ext.main_22.parts_mask = 0;
    despawn_object(OBJECT_HEADER(self));
}

void bee_hive_resume_step(struct MainObj* self)
{
    self->unk5 = self->ext.main_22.saved_unk5;
}

void bee_hive_open(struct MainObj* self)
{
    bee_hive_open_funcs[self->unk6](self);
}

void bee_hive_open_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 1);
    self->ext.main_22.unk84 = 8;
    self->ext.main_22.unk90 = 0;
    self->unk6++;
}

// bee_hive_open_move
INCLUDE_ASM("main/nonmatchings/mains/main_22_bee_hive", func_80055358);

void bee_hive_open_end(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.main_22.unk84 == 0) {
        set_animation(self, 0);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void bee_hive_wait(struct MainObj* self)
{
    bee_hive_wait_funcs[self->unk6](self);
}

void bee_hive_wait_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->ext.main_22.unk84 = 0x28;
    self->unk6++;
}

void bee_hive_wait_watch(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.main_22.unk84 != 0) {
        self->ext.main_22.unk84 = 0x28;
        if (self->ext.main_22.unk8C != 0) {
            self->unk5 = 4;
            self->unk6 = 0;
        }
    }
}

void bee_hive_release(struct MainObj* self)
{
    bee_hive_release_funcs[self->unk6](self);
}

void bee_hive_release_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 1);
    self->ext.main_22.unk84 = 0x31;
    self->unk6++;
}

void func_800559BC(struct MainObj*);

void bee_hive_release_wait(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.main_22.unk84 == 0) {
        func_800559BC(self);
        self->ext.main_22.unk84 = 0x1E;
        self->unk6++;
    }
}

void bee_hive_release_pause(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.main_22.unk84 == 0) {
        self->unk6 = 0;
        self->unk5++;
    }
}

void bee_hive_shake(struct MainObj* self)
{
    bee_hive_shake_funcs[self->unk6](self);
}

void bee_hive_shake_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    set_animation(self, 2);
    self->ext.main_22.unk84 = 0x12;
    self->unk6++;
}

void bee_hive_shake_end(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.main_22.unk84 == 0) {
        set_animation(self, 0);
        self->unk5 = 3;
        self->unk6 = 0;
    }
}

void bee_hive_explode(struct MainObj* self)
{
    bee_hive_explode_funcs[self->unk6](self);
}

void bee_hive_explode_start(struct MainObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    self->ext.main_22.unk84 = 0x28;
    self->unk6++;
}

void bee_hive_explode_smoke(struct MainObj* self)
{
    if (--self->ext.main_22.unk84 != 0) {
        if ((D_80141BD8.unk0 & 3) == 0) {
            func_800AF878(BASE_OBJECT(self), 1, 0x18, 0x30);
        }
    } else {
        self->unk6++;
    }
}

void bee_hive_explode_done(void)
{
}

// bee_hive_spawn_bees
INCLUDE_ASM("main/nonmatchings/mains/main_22_bee_hive", func_800559BC);

struct Unk_unk68 bee_hive_hurt_box = { -19, -48, 37, 92 };

union AnimationStep bee_hive_anim_0[] = {
    { 0x00000001 },
};

union AnimationStep bee_hive_anim_1[] = {
    { 0x01010003 },
    { 0x02010004 },
    { 0x03010005 },
    { 0x02010004 },
    { 0x01010003 },
    { 0x00010014 },
    { 0x04010002 },
    { 0x05010002 },
    { 0x06010002 },
    { 0x07010001 },
    { 0x08010001 },
    { 0x09010001 },
    { 0x0A000001 },
};

union AnimationStep bee_hive_anim_2[] = {
    { 0x09010003 },
    { 0x08010003 },
    { 0x07010003 },
    { 0x06010003 },
    { 0x05010003 },
    { 0x04000003 },
};

union AnimationStep bee_hive_anim_3[] = {
    { 0x0B000003 },
};

union AnimationStep bee_hive_anim_4[] = {
    { 0x0C000003 },
};

union AnimationStep bee_hive_anim_5[] = {
    { 0x0D000003 },
};

union AnimationStep bee_hive_anim_6[] = {
    { 0x0E000003 },
};

union AnimationStep bee_hive_anim_7[] = {
    { 0x0F000003 },
};

union AnimationStep* bee_hive_animations[8] = {
    bee_hive_anim_0,
    bee_hive_anim_1,
    bee_hive_anim_2,
    bee_hive_anim_3,
    bee_hive_anim_4,
    bee_hive_anim_5,
    bee_hive_anim_6,
    bee_hive_anim_7,
};

u8 bee_hive_debris[8] = { 4, 5, 6, 7, 4, 5, 6, 7 };

#ifdef MMX4_WIN32
s16 D_800FCAB0[] = { -48, 10, 3, 48, 10, 3, -22, 69, 4, 22, 69, 4, -40, -16, 3, 40, -16, 3, -40, 36, 4, 40, 36, 4, -26, -28, 3, 26, -28, 3 };
#else
s16 D_800FCAB0 = (s16)0xFFD0;

s16 D_800FCAB2 = (s16)0x000A;

u8 D_800FCAB4[56] = { 0x03, 0x00, 0x30, 0x00, 0x0A, 0x00, 0x03, 0x00, 0xEA, 0xFF, 0x45, 0x00, 0x04, 0x00, 0x16, 0x00, 0x45, 0x00, 0x04, 0x00, 0xD8, 0xFF, 0xF0, 0xFF, 0x03, 0x00, 0x28, 0x00, 0xF0, 0xFF, 0x03, 0x00, 0xD8, 0xFF, 0x24, 0x00, 0x04, 0x00, 0x28, 0x00, 0x24, 0x00, 0x04, 0x00, 0xE6, 0xFF, 0xE4, 0xFF, 0x03, 0x00, 0x1A, 0x00, 0xE4, 0xFF, 0x03, 0x00 };
#endif

void (*bee_hive_state_funcs[])(struct MainObj*) = {
    func_80055024,
    func_80055164,
    bee_hive_despawn,
};

void (*bee_hive_step_funcs[])() = {
    enemy_hit_reaction,
    bee_hive_resume_step,
    bee_hive_open,
    bee_hive_wait,
    bee_hive_release,
    bee_hive_shake,
    bee_hive_explode,
};

void (*bee_hive_open_funcs[])() = {
    bee_hive_open_start,
    func_80055358,
    bee_hive_open_end,
};

void (*bee_hive_wait_funcs[])() = {
    bee_hive_wait_start,
    bee_hive_wait_watch,
};

void (*bee_hive_release_funcs[])() = {
    bee_hive_release_start,
    bee_hive_release_wait,
    bee_hive_release_pause,
};

void (*bee_hive_shake_funcs[])() = {
    bee_hive_shake_start,
    bee_hive_shake_end,
};

void (*bee_hive_explode_funcs[])() = {
    bee_hive_explode_start,
    bee_hive_explode_smoke,
    bee_hive_explode_done,
};
