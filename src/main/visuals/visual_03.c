// VisualObj, visual_object_update_funcs[3]
// 800AF6A0..800AFB50
#include "common.h"

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_03", func_800AF6A0);

void func_800AF808(struct Unk* arg0)
{
    func_800AF828(arg0, 0);
}

void func_800AF828(struct Unk* arg0, s8 arg1)
{
    func_800AFAB4(arg1, arg0->base.x_pos.i.hi, arg0->base.y_pos.i.hi, (get_random() & 1) ^ 1);
}

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_03", func_800AF878);

INCLUDE_ASM("asm/us/main/nonmatchings/visuals/visual_03", func_800AF95C);

struct Unk* func_800AFAB4(s8 arg0, s16 x, s16 y, u8 arg3)
{
    struct VisualObj* temp_v0 = find_free_visual_obj();
    if (temp_v0 != NULL) {
        temp_v0->base.active = 0x21;
        temp_v0->base.id = 4;
        temp_v0->base.unk2 = arg0;
        temp_v0->base.state = 0;
        temp_v0->base.unk5 = 0;
        temp_v0->base.unk6 = 0;
        temp_v0->unk5C = arg3;
        temp_v0->base.x_pos.i.hi = x;
        temp_v0->base.x_pos.i.lo = 0;
        temp_v0->base.y_pos.i.hi = y;
        temp_v0->base.y_pos.i.lo = 0;
        temp_v0->base.unk15 = 0;
        temp_v0->base.bg_offset = 0;
        temp_v0->base.unk16 = 1;
    }
    return temp_v0;
}
