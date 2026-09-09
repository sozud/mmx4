// VisualObj, visual_object_update_funcs[25]
// 800B3D3C..800B3E7C
#include "common.h"

INCLUDE_ASM("main/nonmatchings/visuals/visual_25", func_800B3D3C);

void func_800B3DE8(struct VisualObj* arg0)
{
    func_80015DC8();
    func_8002B318((struct BaseObj*)arg0, 0x30, 0x30);
}

void func_800B3E20(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800B3E40(struct VisualObj* arg0)
{
    D_8010A694[arg0->state](arg0);
}

void (*D_8010A694[])(struct VisualObj*) = {
    func_800B3D3C,
    func_800B3DE8,
    func_800B3E20,
};
