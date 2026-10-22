// MiscObj, misc_object_update_funcs[35]
// 800CF144..800CF2B8
#include "common.h"
#include "main/misc/misc_35_cyclone_trail.h"
#include "main/55C4.h"
#include "main/objects.h"

void cyclone_trail_animate(struct MiscObj*);

void cyclone_trail_update(struct MiscObj* self)
{
    if (self->state == 0) {
        func_800CF184(self);
    } else {
        cyclone_trail_animate(self);
    }
}

// cyclone_trail_init
#ifdef MMX4_PC
void func_800CF184(struct MiscObj* arg0);
#endif

#ifdef MMX4_PC
void func_800CF184(struct MiscObj* arg0)
{
    struct BaseObj* source = arg0->ext.pointer.unk50;

    arg0->on_screen = 1;
    arg0->unk16 = 6;
    arg0->state++;
    if ((u8)arg0->unk2 < 5)
        set_animation(arg0, 0x14 + arg0->unk2);
    arg0->x_pos.i.hi = source->x_pos.i.hi;
    arg0->y_pos.i.hi = source->y_pos.i.hi;
    arg0->x_vel.val = 0;
    arg0->y_vel.val = 0;
    arg0->unk15 = source->unk15;
    is_on_screen(BASE_OBJECT(arg0));
}
#else
INCLUDE_ASM("main/nonmatchings/misc/misc_35_cyclone_trail", func_800CF184);
#endif

void cyclone_trail_animate(struct MiscObj* self)
{
    animate_object(self);
    if (self->animation_step.fields.relative_step == 0) {
        ZeroObjectState(OBJECT_HEADER(self));
    } else {
        is_on_screen(BASE_OBJECT(self));
    }
}
