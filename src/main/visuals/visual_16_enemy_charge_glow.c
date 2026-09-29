// VisualObj, visual_object_update_funcs[16]
// 800B1EA4..800B2090
#include "common.h"

void enemy_charge_glow_update(struct VisualObj* arg0)
{
    enemy_charge_glow_state_funcs[arg0->state](arg0);
}

void enemy_charge_glow_init(struct VisualObj* arg0)
{
    struct PlayerObj* owner;

    if (arg0->unk2 == 0) {
        owner = arg0->unk50;
        arg0->unk15 = owner->unk15;
        if (owner->id == 0x26) {
            set_animation(arg0, 0x14);
        } else {
            set_animation(arg0, 8);
        }
    } else {
        arg0->unk15 = arg0->unk50->unk15;
        set_animation(arg0, 0xD);
    }
    arg0->on_screen = 1;
    arg0->state = 1;
    arg0->unk42 &= 0x7FFF;
}

// enemy_charge_glow_main
INCLUDE_ASM("main/nonmatchings/visuals/visual_16_enemy_charge_glow", func_800B1F78);

void enemy_charge_glow_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*enemy_charge_glow_state_funcs[])(struct VisualObj*) = {
    enemy_charge_glow_init,
    func_800B1F78,
    enemy_charge_glow_despawn,
};
