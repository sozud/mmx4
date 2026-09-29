// VisualObj, visual_object_update_funcs[25]
// 800B3D3C..800B3E7C
#include "common.h"

// flame_jet_fx_init
INCLUDE_ASM("main/nonmatchings/visuals/visual_25_flame_jet_fx", func_800B3D3C);

void flame_jet_fx_main(struct VisualObj* arg0)
{
    animate_object(arg0);
    update_on_screen((struct BaseObj*)arg0, 0x30, 0x30);
}

void flame_jet_fx_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void flame_jet_fx_update(struct VisualObj* arg0)
{
    flame_jet_fx_state_funcs[arg0->state](arg0);
}

void (*flame_jet_fx_state_funcs[])(struct VisualObj*) = {
    func_800B3D3C,
    flame_jet_fx_main,
    flame_jet_fx_despawn,
};
