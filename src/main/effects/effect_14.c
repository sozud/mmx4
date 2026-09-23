// EffectObj, effect_object_update_funcs[14]
// 800B89B4..800B8AF8
#include "common.h"

void func_800B89B4(struct EffectObj* arg0)
{
    arg0->ext.effect_14.unk16 = 0;
    arg0->ext.effect_14.unk14 = 0;
    arg0->state++;
}

void func_800B89CC(struct EffectObj* self)
{
    struct Effect14ItemSpawn* entry;
    struct ItemObj* item;
    entry = D_8010B644;

    if (entry->id != 0xFF) {
        do {
            item = find_free_item_obj();
            if (item != NULL) {
                item->active = 0x41;
                item->id = 7;
                item->unk2 = entry->id;
                item->x_pos.i.hi = entry->x;
                item->y_pos.i.hi = entry->y;
            }
            entry++;
        } while (entry->id != 0xFF);
    }
    self->state++;
}

void func_800B8A9C(struct EffectObj* arg0)
{
    ZeroObjectState(OBJECT_HEADER(arg0));
}

void func_800B8ABC(struct EffectObj* arg0)
{
    D_8010B6B8[arg0->state](arg0);
}

void (*D_8010B6B8[])(struct EffectObj*) = {
    func_800B89B4,
    func_800B89CC,
    func_800B8A9C,
};
