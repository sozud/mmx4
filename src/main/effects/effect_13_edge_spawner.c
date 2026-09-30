// EffectObj, effect_object_update_funcs[13]
// 800B84DC..800B89B4
#include "common.h"

void edge_spawner_update(struct EffectObj* self)
{
    edge_spawner_state_funcs[self->state](self);
}

void edge_spawner_init(struct EffectObj* self)
{
    self->ext.unk_effect.unk14 = 0;
    func_800B8630(self);
    self->ext.unk_effect.unk15 = 0;
    self->state++;
}

void edge_spawner_main(struct EffectObj* self)
{
    s16 pos;

    pos = self->x_pos.i.hi - 0x10;
    if (background_objects[0].x_pos.i.hi - 0x10 <= pos && background_objects[0].x_pos.i.hi + 0x150 >= pos) {
        pos = self->y_pos.i.hi;
        if (background_objects[0].y_pos.i.hi - 0x10 <= pos && background_objects[0].y_pos.i.hi + 0x100 >= pos) {
            func_800B875C(self, background_objects[0].x_pos.i.hi);
            self->ext.unk_effect.unk15++;
        }
    }

    if (self->ext.unk_effect.unk15 > 0x1E) {
        self->state++;
    }
}

void edge_spawner_despawn(struct EffectObj* self)
{
    despawn_object_permanently(OBJECT_HEADER(self));
}

// edge_spawner_spawn_enemy
INCLUDE_ASM("main/nonmatchings/effects/effect_13_edge_spawner", func_800B8630);

// edge_spawner_try_spawn
INCLUDE_ASM("main/nonmatchings/effects/effect_13_edge_spawner", func_800B875C);

// edge_spawner_spawn_items
void func_800B887C(s16 x_min, s16 x_max, s16 y_min, s16 y_max)
{
    struct Effect1314ItemSpawn* entry;
    struct ItemObj* item;

    for (entry = edge_spawner_items; entry->id != 0xFF; entry++) {
        if (entry->reserved == 0) {
            if (WITHIN_BOUNDS(x_min, entry->x, x_max)) {
                if (WITHIN_BOUNDS(y_min, entry->y, y_max)) {
                    item = find_free_item_obj();
                    if (item != NULL) {
                        item->active = 0x41;
                        item->id = 7;
                        item->unk2 = entry->id;
                        item->x_pos.val = FIXED(entry->x);
                        item->y_pos.val = FIXED(entry->y);
                        item->backref = entry;
                        entry->reserved = 1;
                    }
                }
            }
        }
    }
}

void (*edge_spawner_state_funcs[])(struct EffectObj*) = {
    edge_spawner_init,
    edge_spawner_main,
    edge_spawner_despawn,
};

extern u16 edge_spawner_padding;
