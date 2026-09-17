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

INCLUDE_ASM("main/nonmatchings/items/item_21", func_800C5444);

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
