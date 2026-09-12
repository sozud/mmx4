// VisualObj, visual_object_update_funcs[16]
// 800B1EA4..800B2090
#include "common.h"

void func_800B1EA4(struct VisualObj* arg0)
{
    D_8010A544[arg0->state](arg0);
}

void func_800B1EE0(struct VisualObj* arg0)
{
    struct PlayerObj* owner;

    if (arg0->unk2 == 0) {
        owner = arg0->unk50;
        arg0->unk15 = owner->unk15;
        if (owner->id == 0x26) {
            func_80015D60(arg0, 0x14);
        } else {
            func_80015D60(arg0, 8);
        }
    } else {
        arg0->unk15 = arg0->unk50->unk15;
        func_80015D60(arg0, 0xD);
    }
    arg0->on_screen = 1;
    arg0->state = 1;
    arg0->unk42 &= 0x7FFF;
}

INCLUDE_ASM("main/nonmatchings/visuals/visual_16", func_800B1F78);

void func_800B2070(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*D_8010A544[])(struct VisualObj*) = {
    func_800B1EE0,
    func_800B1F78,
    func_800B2070,
};
