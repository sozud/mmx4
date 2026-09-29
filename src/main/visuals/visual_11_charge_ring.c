// VisualObj, visual_object_update_funcs[11]
// 800B17CC..800B19BC
#include "common.h"

void charge_ring_update(struct VisualObj* arg0)
{
    charge_ring_state_funcs[arg0->state](arg0);
}

void charge_ring_init(struct VisualObj* arg0)
{
    arg0->unk15 = arg0->unk50->unk15;
    set_animation(arg0, arg0->unk2);
    arg0->on_screen = 1;
    arg0->state++;
    update_on_screen(arg0, 0x50, 0x50);
}

// charge_ring_main
INCLUDE_ASM("main/nonmatchings/visuals/visual_11_charge_ring", func_800B1864);

void charge_ring_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*charge_ring_state_funcs[])(struct VisualObj*) = {
    charge_ring_init,
    func_800B1864,
    charge_ring_despawn,
};
