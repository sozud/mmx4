// VisualObj, visual_object_update_funcs[28]
// 800B3E7C..800B41CC
#include "common.h"
#include "main/visuals/visual_28_storm_owl_fx.h"
#include "main/55C4.h"
#include "main/objects.h"

// storm_owl_fx_state_funcs
extern void (*storm_owl_fx_state_funcs[])(struct VisualObj*);

void storm_owl_fx_despawn(struct VisualObj*);
#include "weapon_resources.h"

#ifdef VERSION_DEMO
extern void (*camera_trigger_state_funcs[])(struct EffectObj*);

void storm_owl_fx_update(struct VisualObj* arg0)
{
    camera_trigger_state_funcs[arg0->state]((struct EffectObj*)arg0);
}
#else
void storm_owl_fx_update(struct VisualObj* arg0)
{
    storm_owl_fx_state_funcs[arg0->state](arg0);
}
#endif

#ifndef VERSION_DEMO
void storm_owl_fx_init(struct VisualObj* obj)
{
    s8 type;
    s8 mode;
    struct MainObj* owner = MAIN_OBJECT(obj->unk50);

    obj->unk15 = owner->unk15;
    obj->unk42 &= 0x7FFF;
    obj->on_screen = 1;
    type = obj->unk2;

    switch (type) {
    case 0:
        set_animation(obj, 0xA);
        obj->unk54 = 9;
        break;
    case 1:
        set_animation(obj, 0x1A);
        mode = obj->unk5C.fields.mode;
        switch (mode) {
        case 0:
            obj->unk54 = 0x20;
        case 1:
        case 2:
            obj->unk54 = 0x28;
            break;
        }
        break;
    case 2:
        set_animation(obj, 0x19);
        owner->ext.main_60.storm_active = 2;
        break;
    case 3:
        set_animation(obj, 0xE);
        break;
    }

    obj->unk5C.value = 0;
    obj->state++;
}
#endif

#ifndef VERSION_DEMO
void storm_owl_fx_main(struct VisualObj* arg0)
{
    struct MainObj* owner = MAIN_OBJECT(arg0->unk50);

    animate_object(ANIMATED_OBJECT(arg0));
    if (arg0->unk2 >= 2) {
        if (arg0->unk2 == 2) {
            if (owner->ext.main_60.storm_active == 0) {
                arg0->state++;
                return;
            }
        } else {
            arg0->x_pos.val = owner->x_pos.val;
            arg0->y_pos.val = owner->y_pos.val;
            if (owner->ext.main_60.flash_mode == 0) {
                arg0->state++;
                return;
            }
        }
    } else if (--arg0->unk54 == 0) {
        if (arg0->unk2 == 0) {
            arg0->state++;
        } else {
            switch (arg0->unk5C.value) {
            case 0:
                set_animation(arg0, 0x1B);
                arg0->unk5C.value++;
                arg0->unk54 = 0xC;
                break;
            case 1:
                set_animation(arg0, 0x1D);
                arg0->unk5C.value++;
                arg0->unk54 = 0x3E;
                break;
            case 2:
                set_animation(arg0, 0x1C);
                arg0->unk5C.value++;
                arg0->unk54 = 0xC;
                break;
            default:
                arg0->state++;
                break;
            }
        }
    }
    if (owner->active == 0 || owner->state == 2 || (arg0->unk2 == 2 && owner->unk5 == 0xB)) {
        arg0->state++;
        return;
    }
    if (arg0->unk2 == 0) {
        update_on_screen(BASE_OBJECT(arg0), 0x20, 0x20);
    } else {
        update_on_screen(BASE_OBJECT(arg0), 0x20, 0x80);
    }
}
#endif

#ifndef VERSION_DEMO
void storm_owl_fx_despawn(struct VisualObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}
#endif

#ifdef VERSION_DEMO
extern void (*storm_owl_fx_state_funcs[])(struct VisualObj*);
#else
void (*storm_owl_fx_state_funcs[])(struct VisualObj*) = {
    storm_owl_fx_init,
    storm_owl_fx_main,
    storm_owl_fx_despawn,
};
#endif
