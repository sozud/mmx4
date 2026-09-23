// ItemObj, item_object_update_funcs[7]
// 800C16F0..800C1994
#include "common.h"

INCLUDE_ASM("main/nonmatchings/items/item_07", func_800C16F0);

void func_800C1820(struct ItemObj* self)
{
    struct ItemObj* item;
    s32 x_pos;

    self->unk18.val = self->x_pos.val;
    self->unk1C.val = self->y_pos.val;
    func_8002B718(MOVING_OBJECT(self));
    CollisionRelated(PLAYER_OBJECT(self));
    if (self->unk70 & 4) {
        if (self->on_screen != 0) {
            func_8001540C(5, 2, self);
            func_800C833C(8, D_8010CB54[0], MISC_OBJECT(self), FIXED(40), FIXED(8));
        }
        self->state++;
        return;
    }

    func_8002E184(self);
    if (self->unk7C.value == 0 && self->y_pos.i.hi < 0x5B1) {
        item = find_free_item_obj();
        if (item != NULL) {
            item->active = 0x41;
            item->id = 7;
            x_pos = self->x_pos.val;
            item->y_pos.val = FIXED(2320);
            item->x_pos.val = x_pos;
            self->unk7C.value = 1;
        }
    }
    func_8002B318(BASE_OBJECT(self), 0x60, 0x30);
}

void func_800C1938(struct ItemObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800C1958(struct ItemObj* arg0)
{
    D_8010CB5C[arg0->state](arg0);
}

void (*D_8010CB5C[])(struct ItemObj*) = {
    func_800C16F0,
    func_800C1820,
    func_800C1938,
};
