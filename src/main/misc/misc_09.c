// MiscObj, misc_object_update_funcs[9]
// 800C9D64..800C9EAC
#include "common.h"

void func_800C9D64(struct MiscObj* arg0)
{
    if (arg0->state == 0) {
        func_800C9DA4(arg0);
    } else {
        func_800C9E34(arg0);
    }
}

void func_800C9DA4(struct MiscObj* arg0)
{
    arg0->on_screen = 1;
    arg0->unk3C = (void*)arg0->ext.misc_2.owner->sprite_frames;
    arg0->animation_table = (u32**)arg0->ext.misc_2.owner->animation_table;
    arg0->unk40 = arg0->ext.misc_2.owner->unk40;
    arg0->unk42 = arg0->ext.misc_2.owner->unk42 & 0x7FFF;
    arg0->unk16 = 5;
    arg0->bg_offset = (s8)(u8)arg0->ext.misc_2.owner->bg_offset;
    func_80015D60(arg0, arg0->unk2);
    arg0->state = (u8)arg0->state + 1;
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800C9E34(struct MiscObj* arg0)
{
    u8 on_screen;

    if (arg0->ext.misc_2.owner->ext.raw[0] == 0) {
        func_80015DC8(ANIMATED_OBJECT(arg0));
        on_screen = arg0->on_screen ^ 1;
        arg0->on_screen = on_screen;
        if (on_screen != 0) {
            is_on_screen(BASE_OBJECT(arg0));
        }
        if (arg0->animation_step.fields.event != 1) {
            return;
        }
    }
    ZeroObjectState(OBJECT_HEADER(arg0));
}
