// VisualObj, visual_object_update_funcs[4]
// 800AFB50..800AFC9C
#include "common.h"

u8 D_8010A254[19][4] = {
    { 1, 0, 1, 0 },
    { 2, 0, 1, 1 },
    { 2, 0, 1, 2 },
    { 2, 0, 1, 3 },
    { 2, 0, 1, 4 },
    { 2, 0, 1, 5 },
    { 2, 0, 1, 6 },
    { 2, 0, 1, 7 },
    { 2, 0, 1, 8 },
    { 2, 0, 1, 9 },
    { 2, 0, 1, 10 },
    { 2, 0, 1, 11 },
    { 2, 0, 1, 12 },
    { 3, 0, 1, 13 },
    { 3, 0, 1, 14 },
    { 4, 0, 1, 15 },
    { 5, 0, 1, 16 },
    { 6, 0, 1, 17 },
    { 0x60, 0, 0xFF, 17 },
};

u8* D_8010A2A0[1] = { D_8010A254 };

void func_800AFB50(struct VisualObj* arg0)
{
    if (arg0->state == 0) {
        func_800AFB90(arg0);
    } else {
        func_800AFC4C(arg0);
    }
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_04", func_800AFB90);

void func_800AFC4C(struct VisualObj* arg0)
{
    func_80015DC8(arg0);
    if (arg0->animation_step.fields.relative_step < 0) {
        ZeroObjectState(arg0);
    } else {
        is_on_screen(arg0);
    }
}
