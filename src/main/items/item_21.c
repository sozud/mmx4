// ItemObj, item_object_update_funcs[21]
// 800C52CC..800C5544
#include "common.h"

// hopper_switch_init
INCLUDE_ASM("main/nonmatchings/items/item_21", func_800C52CC);

s32 hopper_switch_hopper_touching(struct ItemObj* arg0)
{
    struct MainObj* object;

    for (object = main_objects; object < main_objects + COUNT(main_objects); object++) {
        if (object->active == 0 || object->id != 0x29) {
            continue;
        }
        if (func_8002C160(COLLISION_OBJECT(arg0), COLLISION_OBJECT(object)) == 0) {
            continue;
        }
        return 1;
    }
    return 0;
}

void hopper_switch_main(struct ItemObj* arg0)
{
    if (arg0->unk5 == 0) {
        if (hopper_switch_hopper_touching(arg0) == 0) {
            return;
        }
        apply_tile_effect(arg0->unk2, 0, 0);
        arg0->unk5 = 1;
        set_animation(arg0, 0xE);
    } else {
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->on_screen = 0;
            arg0->state = 2;
            return;
        }
        animate_object(ANIMATED_OBJECT(arg0));
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void hopper_switch_despawn(struct ItemObj* arg0)
{
    despawn_object_permanently(OBJECT_HEADER(arg0));
}

void hopper_switch_update(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    hopper_switch_state_funcs[arg0->state](arg0);
}

u8 hopper_switch_box[4] = { 0, 0, 8, 0x0E };

void (*hopper_switch_state_funcs[])(struct ItemObj*) = {
    func_800C52CC,
    hopper_switch_main,
    hopper_switch_despawn,
};
