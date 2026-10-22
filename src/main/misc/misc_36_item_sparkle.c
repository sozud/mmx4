// MiscObj, misc_object_update_funcs[36]
// 800CF2B8..800CF4B8
#include "common.h"
#include "main/misc/misc_36_item_sparkle.h"
#include "main/55C4.h"
#include "main/object_motion.h"
#include "main/objects.h"

// item_sparkle_state_funcs
extern void (*item_sparkle_state_funcs[])(struct MiscObj*);

void item_sparkle_move(struct MiscObj*);
void item_sparkle_despawn(struct MiscObj*);

void item_sparkle_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    item_sparkle_state_funcs[self->state](self);
}

// item_sparkle_init
#ifdef MMX4_PC
void func_800CF300(struct MiscObj* self);
#endif

#ifdef MMX4_PC
// src/main/misc/misc_36_item_sparkle.c

void func_800CF300(struct MiscObj* self)
{
    struct AnimatedObj* owner = ANIMATED_OBJECT(self->ext.pointer.unk50);

    self->unk16 = 5;
    self->unk40 = owner->unk40;
    owner->unk42 &= 0x7FFF;
    self->unk42 = owner->unk42;
    self->unk3C = owner->unk3C;
    self->animation_table = owner->animation_table;
    self->bg_offset = owner->bg_offset;
    switch ((s8)self->unk2) {
    case 0:
        self->y_vel.val = 0x8000;
        set_animation(self, 9);
        break;
    case 1:
        self->y_vel.val = (get_random() & 1) ? 0x10000 : 0x18000;
        set_animation(self, 8);
        break;
    case 2:
        self->y_vel.val = (get_random() & 1) ? 0x20000 : 0x28000;
        set_animation(self, 7);
        break;
    }
    self->x_vel.val = 0;
    self->unk28 = 0;
    self->unk2C = 0;
    self->state = (u8)self->state + 1;
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_36_item_sparkle", func_800CF300);
#endif

void item_sparkle_move(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    move_object(MOVING_OBJECT(self));
    if ((func_8002B160(BASE_OBJECT(self)) == 0) && (self->animation_step.fields.relative_step != 0)) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state++;
}

void item_sparkle_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*item_sparkle_state_funcs[3])(struct MiscObj*) = {
    func_800CF300,
    item_sparkle_move,
    item_sparkle_despawn,
};
