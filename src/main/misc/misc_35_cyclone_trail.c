// MiscObj, misc_object_update_funcs[35]
// 800CF144..800CF2B8
#include "common.h"

void cyclone_trail_update(struct MiscObj* self)
{
    if (self->state == 0) {
        func_800CF184(self);
    } else {
        cyclone_trail_animate(self);
    }
}

// cyclone_trail_init
INCLUDE_ASM("main/nonmatchings/misc/misc_35_cyclone_trail", func_800CF184);

void cyclone_trail_animate(struct MiscObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.relative_step == 0) {
        ZeroObjectState(OBJECT_HEADER(self));
    } else {
        is_on_screen(BASE_OBJECT(self));
    }
}
