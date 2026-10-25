// MiscObj, misc_object_update_funcs[26]
// 800CC7BC..800CC908
#include "common.h"
#include "main/misc/misc_26_slash_beast_afterimage.h"
#include "main/objects.h"

// slash_beast_afterimage_state_funcs
extern void (*slash_beast_afterimage_state_funcs[])(struct MiscObj*);

void slash_beast_afterimage_despawn(struct MiscObj*);

void slash_beast_afterimage_update(struct MiscObj* self)
{
    slash_beast_afterimage_state_funcs[self->state](self);
}

// slash_beast_afterimage_fade

#if defined(MMX4_PC) || defined(MMX4_SATURN)
void func_800CC7F8(struct MiscObj* arg0);
#endif

#ifdef VERSION_EU
INCLUDE_ASM("main/nonmatchings/misc/misc_26_slash_beast_afterimage", func_800CC7F8);
#else
void func_800CC7F8(struct MiscObj* arg0)
{
    struct MainObj* owner;

    if (arg0->unk2 == 0) {
        arg0->x_pos.val = arg0->ext.misc_26.owner->x_pos.val;
        arg0->y_pos.val = arg0->ext.misc_26.owner->y_pos.val;
        arg0->unk15 = arg0->ext.misc_26.owner->unk15;
        arg0->unk42 = arg0->ext.misc_26.owner->unk42;
        arg0->animation_step.fields.frame_index = arg0->ext.misc_26.owner->animation_step.fields.frame_index + 0x3C;
        if (arg0->ext.misc_26.owner->state >= 2 || arg0->ext.misc_26.owner->ext.main_54.powered_up == 0) {
            arg0->state = 1;
            return;
        }
        is_on_screen(BASE_OBJECT(arg0));
        return;
    }
    owner = arg0->ext.misc_26.owner;
    arg0->ext.misc_26.timer--;
    if (owner->state >= 2 || (s8)arg0->ext.misc_26.timer == 0) {
        arg0->state = 1;
        return;
    }
    if (!(arg0->ext.misc_26.timer & 3))
        is_on_screen(BASE_OBJECT(arg0));
    else
        arg0->on_screen = 0;
}
#endif

void slash_beast_afterimage_despawn(struct MiscObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void (*slash_beast_afterimage_state_funcs[])(struct MiscObj*) = {
    func_800CC7F8,
    slash_beast_afterimage_despawn,
};
