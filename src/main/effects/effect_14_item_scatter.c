// EffectObj, effect_object_update_funcs[14]
// 800B89B4..800B8AF8
#include "common.h"

void item_scatter_init(struct EffectObj* self)
{
    self->state++;
    self->ext.effect_14.unk16 = 0;
    self->ext.effect_14.unk14 = 0;
}

void item_scatter_spawn(struct EffectObj* self)
{
    struct Effect1314ItemSpawn* entry;
    struct ItemObj* item;
    entry = edge_spawner_items;

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

void item_scatter_despawn(struct EffectObj* self)
{
    ZeroObjectState(OBJECT_HEADER(self));
}

void item_scatter_update(struct EffectObj* self)
{
    item_scatter_state_funcs[self->state](self);
}

void (*item_scatter_state_funcs[])(struct EffectObj*) = {
    item_scatter_init,
    item_scatter_spawn,
    item_scatter_despawn,
};
