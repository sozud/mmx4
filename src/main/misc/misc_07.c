// MiscObj, misc_object_update_funcs[7]
// 800C938C..800C9510
#include "common.h"

void func_800C938C(struct MiscObj* arg0)
{
    D_8010DC70[arg0->state](arg0);
}

void func_800C93C8(struct MiscObj* arg0)
{
    s16 x;

    func_80015D60(arg0, 0xA);
    arg0->x_pos.val = ((struct FixedPointPosition*)arg0->ext.misc_7.position)->x;
    arg0->y_pos.val = ((struct FixedPointPosition*)arg0->ext.misc_7.position)->y;
    if (arg0->unk2 != 0) {
        if (arg0->unk15 != 0) {
            x = arg0->x_pos.u.hi + 3;
        } else {
            x = arg0->x_pos.u.hi - 3;
        }
        arg0->x_pos.i.hi = x;
    }
    arg0->state = 1;
}

void func_800C9450(struct MiscObj* self)
{
    s16 x_pos;
    func_80015DC8(ANIMATED_OBJECT(self));
    self->x_pos.val = ((struct FixedPointPosition*)self->ext.misc_7.position)->x;
    self->y_pos.val = ((struct FixedPointPosition*)self->ext.misc_7.position)->y;
    if (self->unk2 != 0) {
        if (self->unk15 != 0) {
            x_pos = (u16)self->x_pos.i.hi + 3;
        } else {
            x_pos = (u16)self->x_pos.i.hi - 3;
        }
        self->x_pos.i.hi = x_pos;
    }
    if (self->animation_step.fields.event != 0) {
        self->state = 2;
    }
    func_8002B318(BASE_OBJECT(self), 0x40, 0x40);
}

void func_800C94F0(struct MiscObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}
