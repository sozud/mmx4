// VisualObj, visual_object_update_funcs[10]
// 800B14E8..800B17CC
#include "common.h"

void dragon_fx_update(struct VisualObj* arg0)
{
    dragon_fx_state_funcs[arg0->state](arg0);
}

void dragon_fx_flash_init(struct VisualObj* arg0)
{
    if (arg0->unk2 == 0) {
        arg0->unk15 = 0;
    } else {
        arg0->unk15 = 0x40;
    }
    set_animation(arg0, 5);
    arg0->state++;
    update_on_screen(arg0, 0xA0, 0xA0);
}

// dragon_fx_flash
INCLUDE_ASM("main/nonmatchings/visuals/visual_10", func_800B158C);

void dragon_fx_trail_init(struct VisualObj* arg0)
{
    struct PlayerObj* temp_v1;

    temp_v1 = arg0->unk50;
    arg0->unk38 = 0;
    arg0->state++;
    arg0->unk3C = temp_v1->unk3C;
    arg0->animation_table = temp_v1->animation_table;
    arg0->unk40 = temp_v1->unk40;
    arg0->unk42 = temp_v1->unk42;
    arg0->unk16 = 0x10;
    arg0->x_pos.val = temp_v1->x_pos.val;
    arg0->y_pos.val = temp_v1->y_pos.val;
    arg0->bg_offset = -1;
    arg0->unk15 = temp_v1->unk15;
    set_animation(arg0, 8);
    update_on_screen((struct BaseObj*)arg0, 0x20, 0x20);
}

void dragon_fx_animate(struct VisualObj* arg0)
{
    animate_object(arg0);
    if (arg0->animation_step.fields.relative_step < 0) {
        arg0->state++;
    }
    update_on_screen(arg0, 0x20, 0x20);
}

void dragon_fx_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void (*dragon_fx_state_funcs[])(struct VisualObj*) = {
    dragon_fx_flash_init,
    func_800B158C,
    dragon_fx_trail_init,
    dragon_fx_animate,
    dragon_fx_despawn,
};
