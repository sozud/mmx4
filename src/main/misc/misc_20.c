// MiscObj, misc_object_update_funcs[20]
// 800CB8F8..800CBA80
#include "common.h"

void func_800CB8F8(struct MiscObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010E830[arg0->state](arg0);
}

void func_800CB940(struct MiscObj* arg0)
{
    u8 state, bg;

    arg0->unk16 = 0x12;
    arg0->unk15 = 0;
    arg0->unk40 = (s16)((u32)*D_801406A8 >> 7);
    arg0->unk3C = SP_ARCHIVE_ENTRY(SP_MENU_FRAMES, 0);
    arg0->unk42 = 0x7987;
    arg0->x_pos.i.hi = background_objects[0].x_pos.u.hi + 0x160;
    arg0->y_pos.i.hi = background_objects[0].y_pos.u.hi + 0x80;
    arg0->animation_step.fields.frame_index = 0;
    state = arg0->state + 1;
    bg = g_Player.bg_offset;
    arg0->state = state;
    arg0->bg_offset = bg;
}

INCLUDE_ASM("main/nonmatchings/misc/misc_20", func_800CB9C4);

void func_800CBA5C(struct MiscObj* arg0)
{
    arg0->ext.misc_20.owner->private_state.misc_20_active = 0;
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void (*D_8010E830[])(struct MiscObj*) = {
    func_800CB940,
    func_800CB9C4,
    func_800CBA5C,
};
