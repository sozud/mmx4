// MiscObj, misc_object_update_funcs[20]
// 800CB8F8..800CBA80
#include "common.h"

void scroll_prop_update(struct MiscObj* self)
{
    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    scroll_prop_state_funcs[self->state](self);
}

void scroll_prop_init(struct MiscObj* self)
{
    u8 state, bg;

    self->unk16 = 0x12;
    self->unk15 = 0;
    self->unk40 = (s16)((u32)*D_801406A8 >> 7);
    self->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 0);
    self->unk42 = 0x7987;
    self->x_pos.i.hi = background_objects[0].x_pos.u.hi + 0x160;
    self->y_pos.i.hi = background_objects[0].y_pos.u.hi + 0x80;
    self->animation_step.fields.frame_index = 0;
    state = self->state + 1;
    self->bg_offset = g_Player.bg_offset;
    self->state = state;
}

void scroll_prop_scroll(struct MiscObj* self)
{
    s32 offset;

    if (self->ext.misc_20.owner->unk18.val != 0) {
        offset = self->ext.misc_20.owner->unk18.val + FIXED(1);
        self->x_pos.val -= offset;
    }
    if (g_Player.x_pos.i.hi > 0x16B8 && g_Player.x_pos.i.hi < 0x1DE8) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    if (func_8002B160(BASE_OBJECT(self)) == 0) {
        is_on_screen(BASE_OBJECT(self));
        return;
    }
    self->state++;
}

void scroll_prop_despawn(struct MiscObj* self)
{
    self->ext.misc_20.owner->private_state.misc_20_active = 0;
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*scroll_prop_state_funcs[])(struct MiscObj*) = {
    scroll_prop_init,
    scroll_prop_scroll,
    scroll_prop_despawn,
};
