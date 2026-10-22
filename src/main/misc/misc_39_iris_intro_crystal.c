// MiscObj, misc_object_update_funcs[39]
// 800CF790..800CFB70
#include "common.h"
#include "main/misc/misc_39_iris_intro_crystal.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

// iris_intro_crystal_state_funcs
extern void (*iris_intro_crystal_state_funcs[])(struct MiscObj*);
void iris_intro_crystal_run(struct MiscObj* arg0);
void iris_intro_crystal_despawn(struct MiscObj*);

// iris_intro_crystal_step_funcs
extern void (*iris_intro_crystal_step_funcs[])(struct MiscObj*);
void iris_intro_crystal_start(struct MiscObj*);
void iris_intro_crystal_rise(struct MiscObj*);
void iris_intro_crystal_charge(struct MiscObj*);

void iris_intro_crystal_wait(struct MiscObj*);
void iris_intro_crystal_leave(struct MiscObj*);

void iris_intro_crystal_update(struct MiscObj* self)
{
    iris_intro_crystal_state_funcs[self->state](self);
}

void iris_intro_crystal_run(struct MiscObj* self)
{
    iris_intro_crystal_step_funcs[self->unk5](self);
    update_on_screen(BASE_OBJECT(self), 0x20, 0x20);
}

void iris_intro_crystal_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void iris_intro_crystal_start(struct MiscObj* self)
{
    self->unk16 = 0;
    self->unk15 = 0x40;
    self->x_vel.val = 0;
    self->y_vel.val = FIXED(0.5);
    self->ext.misc_39.timer = 0xD6;
    set_animation(self, 0xB);
    self->unk5 = 1;
}

void iris_intro_crystal_rise(struct MiscObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if (--self->ext.misc_39.timer == 0) {
        self->ext.misc_39.timer = 0x78;
        self->unk5 = 2;
    }
}

void iris_intro_crystal_charge(struct MiscObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.misc_39.timer == 0) {
        set_animation(self, 0xC);
        set_animation(self->ext.misc_39.related, 0x21);
        self->unk5 = 3;
    }
}

// iris_intro_crystal_transform
#ifdef MMX4_PC
void func_800CF950(struct MiscObj* self);
#endif

#ifdef MMX4_PC
void func_800CF950(struct MiscObj* self)
{
    struct MiscObj* piece;
    s32 i;

    animate_object(ANIMATED_OBJECT(self));
    if (self->animation_step.fields.event == 0) {
        return;
    }
    set_animation(self, 0x10);
    set_animation(((struct MainObj*)self->ext.misc_39.related), 0x24);
    func_8001540C(2, 0xDE, ((struct MainObj*)self->ext.misc_39.related));
    ((struct MainObj*)self->ext.misc_39.related)->unk6 = 8;
    for (i = 0; i < 5; i++) {
        piece = find_free_misc_obj();
        if (piece == NULL) {
            continue;
        }
        piece->active = 0x41;
        piece->id = 0x16;
        piece->unk2 = 8;
        switch (i) {
        case 0:
        case 2:
            piece->unk16 = 0x21;
            break;
        case 1:
        case 3:
            piece->unk16 = 0;
            break;
        case 4:
            piece->unk16 = 0x20;
            break;
        }
        piece->x_pos.val = self->x_pos.val + 0x10000;
        piece->y_pos.val = self->y_pos.val + 0x400000;
        piece->bg_offset = self->bg_offset;
        piece->animation_table = self->animation_table;
        piece->unk40 = self->unk40;
        piece->unk3C = self->unk3C;
        piece->ext.unk.unk56.byte = 0x30;
        piece->unk42 = self->unk42 & 0x7FFF;
        set_animation(piece, i + 0x12);
        piece->unk5 = 0;
        piece->unk6 = 0;
    }
    self->ext.misc_39.timer = 0x88;
    self->unk5 = 4;
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_39_iris_intro_crystal", func_800CF950);
#endif

void iris_intro_crystal_wait(struct MiscObj* self)
{

    animate_object(ANIMATED_OBJECT(self));
    if (--self->ext.misc_39.timer == 0) {
        self->ext.misc_39.timer = 0x76;
        self->y_vel.val = FIXED(-1);
        self->unk5 = 5;
    }
}

void iris_intro_crystal_leave(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    self->ext.misc_39.timer -= 1;
    if (self->ext.misc_39.timer == 0) {
        self->state = 1;
    }
}

void (*iris_intro_crystal_state_funcs[2])(struct MiscObj*) = {
    iris_intro_crystal_run,
    iris_intro_crystal_despawn,
};

void (*iris_intro_crystal_step_funcs[6])(struct MiscObj*) = {
    iris_intro_crystal_start,
    iris_intro_crystal_rise,
    iris_intro_crystal_charge,
    func_800CF950,
    iris_intro_crystal_wait,
    iris_intro_crystal_leave,
};
