// MiscObj, misc_object_update_funcs[24]
// 800CBECC..800CC460
#include "common.h"

void enemy_hatch_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    enemy_hatch_state_funcs[self->state](self);
}

// enemy_hatch_init
INCLUDE_ASM("main/nonmatchings/misc/misc_24_enemy_hatch", func_800CBF14);

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
INCLUDE_ASM("main/nonmatchings/misc/misc_24_enemy_hatch", func_800CC114);

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
        if (self->unk2 == 0) {
            main->id = 0x30;
        } else {
            main->id = 3;
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
        func_8001540C(2, 0xE7, self);
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
    { .packed = 0x00010002 },
    { .packed = 0x01010002 },
    { .packed = 0x02010002 },
    { .packed = 0x03010002 },
    { .packed = 0x04010001 },
    { .packed = 0x05010005 },
    { .packed = 0x04010001 },
    { .packed = 0x06010005 },
    { .packed = 0x04010001 },
    { .packed = 0x07010004 },
    { .packed = 0x04010001 },
    { .packed = 0x08010004 },
    { .packed = 0x09010006 },
    { .packed = 0x0A010004 },
    { .packed = 0x0B010004 },
    { .packed = 0x0C000003 },
};

union AnimationStep enemy_hatch_anim_1[8] = {
    { .packed = 0x0D010003 },
    { .packed = 0x0E010003 },
    { .packed = 0x0F010003 },
    { .packed = 0x10010003 },
    { .packed = 0x11010003 },
    { .packed = 0x12010003 },
    { .packed = 0x13010003 },
    { .packed = 0x14F90003 },
};

union AnimationStep enemy_hatch_anim_2[8] = {
    { .packed = 0x15010003 },
    { .packed = 0x16010003 },
    { .packed = 0x17010003 },
    { .packed = 0x18010003 },
    { .packed = 0x19010003 },
    { .packed = 0x1A010003 },
    { .packed = 0x1B010003 },
    { .packed = 0x1CF90003 },
};

union AnimationStep enemy_hatch_anim_3[16] = {
    { .packed = 0x0C010003 },
    { .packed = 0x0B010004 },
    { .packed = 0x0A010004 },
    { .packed = 0x09010006 },
    { .packed = 0x08010004 },
    { .packed = 0x04010001 },
    { .packed = 0x07010004 },
    { .packed = 0x04010001 },
    { .packed = 0x06010005 },
    { .packed = 0x04010001 },
    { .packed = 0x05010005 },
    { .packed = 0x04010001 },
    { .packed = 0x03010002 },
    { .packed = 0x02010002 },
    { .packed = 0x01010001 },
    { .packed = 0x00000001 },
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
