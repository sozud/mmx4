// VisualObj, visual_object_update_funcs[25]
// 800B3D3C..800B3E7C
#include "common.h"

// flame_jet_fx_init
void func_800B3D3C(struct VisualObj* self)
{
    struct MainObj* owner = (struct MainObj*)self->unk50;

    self->unk40 = owner->unk40;
    self->unk42 = owner->unk42 & 0x7FFF;
    self->animation_table = ANIMATED_OBJECT(owner)->animation_table;
    self->unk3C = ANIMATED_OBJECT(owner)->unk3C;
    self->unk15 = owner->unk15;
    self->bg_offset = owner->bg_offset;
    if (self->unk2 != 0) {
        self->unk16 = 1;
    } else {
        self->unk16 = 6;
    }
    set_animation(self, self->unk2);
    self->state++;
}

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
