// MiscObj, misc_object_update_funcs[24]
// 800CBECC..800CC460
#include "common.h"
#include "main/misc/misc_24_enemy_hatch.h"
#include "main/objects.h"
#include "main/55C4.h"

// enemy_hatch_state_funcs
extern void (*enemy_hatch_state_funcs[])(struct MiscObj*);
void func_800CBF14(struct MiscObj*);
void enemy_hatch_main(struct MiscObj*);
void enemy_hatch_despawn(struct MiscObj*);

// enemy_hatch_step_funcs
extern void (*enemy_hatch_step_funcs[])(struct MiscObj*);
void enemy_hatch_wait(struct MiscObj*);
void enemy_hatch_release(struct MiscObj*);
void enemy_hatch_close(struct MiscObj*);

// enemy_hatch_wait_funcs
extern void (*enemy_hatch_wait_funcs[])(struct MiscObj*);
void enemy_hatch_wait_start(struct MiscObj*);
void func_800CC114(struct MiscObj*);

// enemy_hatch_release_funcs
extern void (*enemy_hatch_release_funcs[])(struct MiscObj*);
void enemy_hatch_release_spawn(struct MiscObj*);
void enemy_hatch_release_wait(struct MiscObj*);

// enemy_hatch_close_funcs
extern void (*enemy_hatch_close_funcs[])(struct MiscObj*);
void enemy_hatch_close_start(struct MiscObj*);
void enemy_hatch_close_finish(struct MiscObj*);
#include "weapon_resources.h"

extern union AnimationStep* enemy_hatch_animations[4];

void enemy_hatch_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    enemy_hatch_state_funcs[self->state](self);
}

// enemy_hatch_init
void func_800CBF14(struct MiscObj* self)
{
    u8 bg_offset;
    u8 state;

    if (self->x_pos.i.hi - g_Player.x_pos.i.hi <= 0) {
        self->unk15 = PLAYER_FACING_RIGHT;
    } else {
        self->unk15 = 0;
    }
    self->unk40 = OBJECT_STAGE_TEXTURE(func_8002938C(0x8F));
    self->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, func_8002938C(0x8F));
    self->unk42 = OBJECT_STAGE_CLUT(0x8F);
    bg_offset = g_Player.bg_offset;
    state = self->state;
    self->animation_table = (u32**)enemy_hatch_animations;
    self->unk5 = 0;
    self->unk16 = VISUAL_SATURN_LAYER(5);
    self->unk6 = 0;
    self->bg_offset = bg_offset;
    self->ext.misc_24.child_active = 0;
    self->state = state + 1;
}

void enemy_hatch_main(struct MiscObj* self)
{
    enemy_hatch_step_funcs[self->unk5](self);
    if (func_8002B160(self) == 0) {
        is_on_screen(self);
    } else {
        self->state = 2;
    }
}

void enemy_hatch_wait(struct MiscObj* self)
{
    enemy_hatch_wait_funcs[self->unk6](self);
}

void enemy_hatch_wait_start(struct MiscObj* self)
{
    self->unk6++;
    set_animation(self, 0);
}

// enemy_hatch_wait_player
void func_800CC114(struct MiscObj* self)
{
    struct MiscObj* child;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.relative_step != 0) {
        return;
    }
    self->unk6 = 0;
    self->unk5 = 1;
    child = find_free_misc_obj();
    if (child == NULL) {
        return;
    }
    child->active = 0x41;
    child->id = 0xB;
    child->unk2 = 3;
    child->unk16 = 3;
    child->unk15 = self->unk15;
    child->unk40 = self->unk40;
    child->unk42 = self->unk42;
    child->unk3C = self->unk3C;
    child->animation_table = ANIMATED_OBJECT(self)->animation_table;
    child->bg_offset = self->bg_offset;
    child->x_pos.val = self->x_pos.val;
    child->y_pos.val = self->y_pos.val;
    set_animation(child, 2);
    child->ext.misc_11.active = 0;
    self->ext.misc_24.child = child;
    self->ext.misc_24.child_active = 1;
}

void enemy_hatch_release(struct MiscObj* self)
{
    enemy_hatch_release_funcs[self->unk6](self);
}

void enemy_hatch_release_spawn(struct MiscObj* self)
{
    struct MainObj* main;

    set_animation(self, 1);
    animate_object(ANIMATED_OBJECT(self));
    main = find_free_main_obj();
    if (main != NULL) {
        main->active = 0x41;
        if (self->unk2 != 0) {
            main->id = 3;
        } else {
            main->id = 0x30;
        }
        main->unk2 = -0x80;
        main->unk15 = self->unk15;
        main->x_pos.val = self->x_pos.val;
        if (main->id == 3) {
            main->y_pos.val = self->y_pos.val - FIXED(4);
        } else {
            main->y_pos.val = self->y_pos.val;
        }
        self->ext.misc_5.owner = main;
        self->ext.misc_24.timer = 0x20;
        self->unk6++;
        func_8001540C(2, SATURN_SOUND(0xE7, 0xA8), self);
    }
}

void enemy_hatch_release_wait(struct MiscObj* self)
{
    animate_object((struct AnimatedObj*)self);

    if (--self->ext.misc_24.timer == 0) {
        self->unk5 = 2;
        self->unk6 = 0;
    }
}

void enemy_hatch_close(struct MiscObj* self)
{
    enemy_hatch_close_funcs[self->unk6](self);
}

void enemy_hatch_close_start(struct MiscObj* self)
{
    self->unk6++;
    set_animation(self, 3);
    self->ext.misc_24.child_active = 0;
    self->ext.misc_24.child->ext.misc_11.active = 1;
}

void enemy_hatch_close_finish(struct MiscObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.relative_step == 0) {
        self->state = 2;
        self->unk5 = 0;
        self->unk6 = 0;
    }
}

void enemy_hatch_despawn(struct MiscObj* self)
{
    if (self->ext.misc_24.child_active != 0) {
        ZeroObjectState(OBJECT_HEADER(self->ext.misc_24.child));
    }
    despawn_object(OBJECT_HEADER(self));
}

union AnimationStep enemy_hatch_anim_0[16] = {
    { 2, 0, 1, 0x00 },
    { 2, 0, 1, 0x01 },
    { 2, 0, 1, 0x02 },
    { 2, 0, 1, 0x03 },
    { 1, 0, 1, 0x04 },
    { 5, 0, 1, 0x05 },
    { 1, 0, 1, 0x04 },
    { 5, 0, 1, 0x06 },
    { 1, 0, 1, 0x04 },
    { 4, 0, 1, 0x07 },
    { 1, 0, 1, 0x04 },
    { 4, 0, 1, 0x08 },
    { 6, 0, 1, 0x09 },
    { 4, 0, 1, 0x0A },
    { 4, 0, 1, 0x0B },
    { 3, 0, 0, 0x0C },
};

union AnimationStep enemy_hatch_anim_1[8] = {
    { 3, 0, 1, 0x0D },
    { 3, 0, 1, 0x0E },
    { 3, 0, 1, 0x0F },
    { 3, 0, 1, 0x10 },
    { 3, 0, 1, 0x11 },
    { 3, 0, 1, 0x12 },
    { 3, 0, 1, 0x13 },
    { 3, 0, -7, 0x14 },
};

union AnimationStep enemy_hatch_anim_2[8] = {
    { 3, 0, 1, 0x15 },
    { 3, 0, 1, 0x16 },
    { 3, 0, 1, 0x17 },
    { 3, 0, 1, 0x18 },
    { 3, 0, 1, 0x19 },
    { 3, 0, 1, 0x1A },
    { 3, 0, 1, 0x1B },
    { 3, 0, -7, 0x1C },
};

union AnimationStep enemy_hatch_anim_3[16] = {
    { 3, 0, 1, 0x0C },
    { 4, 0, 1, 0x0B },
    { 4, 0, 1, 0x0A },
    { 6, 0, 1, 0x09 },
    { 4, 0, 1, 0x08 },
    { 1, 0, 1, 0x04 },
    { 4, 0, 1, 0x07 },
    { 1, 0, 1, 0x04 },
    { 5, 0, 1, 0x06 },
    { 1, 0, 1, 0x04 },
    { 5, 0, 1, 0x05 },
    { 1, 0, 1, 0x04 },
    { 2, 0, 1, 0x03 },
    { 2, 0, 1, 0x02 },
    { 1, 0, 1, 0x01 },
    { 1, 0, 0, 0x00 },
};

union AnimationStep* enemy_hatch_animations[4] = {
    enemy_hatch_anim_0,
    enemy_hatch_anim_1,
    enemy_hatch_anim_2,
    enemy_hatch_anim_3,
};

void (*enemy_hatch_state_funcs[])(struct MiscObj*) = {
    func_800CBF14,
    enemy_hatch_main,
    enemy_hatch_despawn,
};

void (*enemy_hatch_step_funcs[])(struct MiscObj*) = {
    enemy_hatch_wait,
    enemy_hatch_release,
    enemy_hatch_close,
};

void (*enemy_hatch_wait_funcs[])(struct MiscObj*) = {
    enemy_hatch_wait_start,
    func_800CC114,
};

void (*enemy_hatch_release_funcs[])(struct MiscObj*) = {
    enemy_hatch_release_spawn,
    enemy_hatch_release_wait,
};

void (*enemy_hatch_close_funcs[])(struct MiscObj*) = {
    enemy_hatch_close_start,
    enemy_hatch_close_finish,
};
