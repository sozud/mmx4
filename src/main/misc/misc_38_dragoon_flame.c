// MiscObj, misc_object_update_funcs[38]
// 800CF4B8..800CF790
#include "common.h"

// dragoon_flame_init
INCLUDE_ASM("main/nonmatchings/misc/misc_38_dragoon_flame", func_800CF4B8);

void dragoon_flame_burn(struct MiscObj* self)
{
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
    if (self->animation_step.fields.relative_step == 0) {
        self->state++;
    }
}

void dragoon_flame_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

// dragoon_flame_attach_init
INCLUDE_ASM("main/nonmatchings/misc/misc_38_dragoon_flame", func_800CF660);

void dragoon_flame_attached(struct MiscObj* self)
{
    struct ObjectHeader* target = self->ext.pointer.unk50;
    self->x_pos.val = target->x_pos.val;
    self->y_pos.val = target->y_pos.val;
    animate_object(ANIMATED_OBJECT(self));
    is_on_screen(BASE_OBJECT(self));
}

void dragoon_flame_update(struct MiscObj* self)
{
    dragoon_flame_state_funcs[self->state](self);
}

void (*dragoon_flame_state_funcs[5])(struct MiscObj*) = {
    func_800CF4B8,
    dragoon_flame_burn,
    dragoon_flame_despawn,
    func_800CF660,
    dragoon_flame_attached,
};
