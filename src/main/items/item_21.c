// ItemObj, item_object_update_funcs[21]
// 800C52CC..800C5544
#include "common.h"

INCLUDE_ASM("main/nonmatchings/items/item_21", func_800C52CC);

s32 func_800C53A0(struct ItemObj* arg0)
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

void func_800C5444(struct ItemObj* arg0)
{
    if (arg0->unk5 == 0) {
        if (func_800C53A0(arg0) == 0) {
            return;
        }
        func_800DABE4(arg0->unk2, 0, 0);
        arg0->unk5 = 1;
        func_80015D60(arg0, 0xE);
    } else {
        if (arg0->animation_step.fields.relative_step == 0) {
            arg0->on_screen = 0;
            arg0->state = 2;
            return;
        }
        func_80015DC8(ANIMATED_OBJECT(arg0));
    }
    is_on_screen(BASE_OBJECT(arg0));
}

void func_800C54DC(struct ItemObj* arg0)
{
    func_8002B108(OBJECT_HEADER(arg0));
}

void func_800C54FC(struct ItemObj* arg0)
{
    arg0->unk18.val = arg0->x_pos.val;
    arg0->unk1C.val = arg0->y_pos.val;
    D_8010D250[arg0->state](arg0);
}

u8 D_8010D24C[4] = { 0, 0, 8, 0x0E };

void (*D_8010D250[])(struct ItemObj*) = {
    func_800C52CC,
    func_800C5444,
    func_800C54DC,
};
