// VisualObj, visual_object_update_funcs[23]
// 800B322C..800B35B8
#include "common.h"

void jet_stingray_fx_init(struct VisualObj* arg0)
{
    arg0->state = 1;
    switch (arg0->unk2) {
    case 0:
        arg0->unk5C.value = 0;
        arg0->x_pos.i.hi -= arg0->unk15 ? -0x33 : 0x33;
        arg0->y_pos.i.hi -= 4;
        set_animation(arg0, 0x13);
        break;
    case 1:
        set_animation(arg0, 0x1E);
        break;
    case 2:
        // see water_wake_init & func_8003D4C8 for a similar pattern
        arg0->unk42 = SOME_COORDINATE_CONVERSION(func_8002938C(0x84));
        set_animation(arg0, 0x2B);
        break;
    }
    arg0->unk42 &= ~0x8000;
}

void jet_stingray_fx_vortex(struct VisualObj* arg0)
{
    struct MainObj* owner = MAIN_OBJECT(arg0->unk50);

    switch (arg0->unk5) {
    case 0:
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk5++;
            set_animation(arg0, 0x14);
        }
        break;
    case 1:
        if (owner->ext.main_56.vortex_result != 0) {
            arg0->unk5++;
            set_animation(arg0, 0x15);
        }
        break;
    case 2:
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->state = 2;
        }
        break;
    }
    if (owner->state >= 2) {
        arg0->state = 2;
    }
}

void jet_stingray_fx_splash(struct VisualObj* arg0)
{
    struct PlayerObj* entity = arg0->unk50;

    switch (arg0->unk5) {
    case 0:
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->unk5++;
            set_animation(arg0, 0x20);
        }
        break;
    case 1:
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->state = 2;
        }
        break;
    }

    if (entity->state == 2) {
        arg0->state = 2;
    }
    move_object((struct MovingObj*)arg0);
}

void jet_stingray_fx_oneshot(struct VisualObj* arg0)
{
    if (arg0->animation_step.fields.relative_step == 0) {
        arg0->state = 2;
    }
}

void jet_stingray_fx_main(struct VisualObj* arg0)
{
    animate_object(arg0);
    jet_stingray_fx_funcs[arg0->unk2](arg0);
    is_on_screen(arg0);
}

void jet_stingray_fx_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(arg0);
}

void jet_stingray_fx_update(struct VisualObj* arg0)
{
    jet_stingray_fx_state_funcs[arg0->state](arg0);
}

void (*jet_stingray_fx_funcs[])(struct VisualObj*) = {
    jet_stingray_fx_vortex,
    jet_stingray_fx_splash,
    jet_stingray_fx_oneshot,
};

void (*jet_stingray_fx_state_funcs[])(struct VisualObj*) = {
    jet_stingray_fx_init,
    jet_stingray_fx_main,
    jet_stingray_fx_despawn,
};
