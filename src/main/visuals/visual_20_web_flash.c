// VisualObj, visual_object_update_funcs[20]
// 800B2D48..800B2E98
#include "common.h"

void web_flash_update(struct VisualObj* arg0)
{
    web_flash_state_funcs[arg0->state](arg0);
}

void web_flash_init(struct VisualObj* arg0)
{
    arg0->state = 1;
    arg0->on_screen = 1;
    arg0->unk16 = 4;
    if (arg0->unk2 == 0) {
        set_animation(arg0, 0x11);
    } else {
        arg0->unk54 = 0;
        set_animation(arg0, 0x15);
    }
}

void web_flash_main(struct VisualObj* arg0)
{
    struct ShotObj* temp_v1;
    struct WeaponObj* temp_a0;

    animate_object(arg0);
    if (arg0->unk2 == 0) {
        temp_v1 = (struct ShotObj*)arg0->unk50;
        temp_a0 = temp_v1->unk7C;
        arg0->x_pos.val = temp_a0->x_pos.val;
        arg0->y_pos.val = temp_a0->y_pos.val;
        if (temp_v1->unk2 != 0) {
            is_on_screen(arg0);
        } else {
            ZeroObjectState(OBJECT_HEADER(arg0));
        }
    } else {
        temp_a0 = (struct WeaponObj*)arg0->unk50;
        if (arg0->animation_step.fields.relative_step >= 0 && temp_a0->state == 1 && (temp_a0->unk5 == 3 || temp_a0->unk5 == 5)) {
            is_on_screen(arg0);
        } else {
            ZeroObjectState(OBJECT_HEADER(arg0));
        }
    }
}

void (*web_flash_state_funcs[])(struct VisualObj*) = {
    web_flash_init,
    web_flash_main,
};
