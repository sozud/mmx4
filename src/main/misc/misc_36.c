// MiscObj, misc_object_update_funcs[36]
// 800CF2B8..800CF4B8
#include "common.h"

void item_sparkle_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    item_sparkle_state_funcs[self->state](self);
}

// item_sparkle_init
INCLUDE_ASM("main/nonmatchings/misc/misc_36", func_800CF300);

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
