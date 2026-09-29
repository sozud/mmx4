// EffectObj, effect_object_update_funcs[6]
// 800B6A0C..800B6B18
#include "common.h"

void checkpoint_trigger_update(struct EffectObj* self)
{
    checkpoint_trigger_state_funcs[self->state](self);
}

void checkpoint_trigger_init(struct EffectObj* self)
{
    self->ext.unk_effect.unk14 = 0;
    self->state++;
    if ((self->unk2 & 0xF) == engine_obj.checkpoint) {
        despawn_object(self);
    }
}

void checkpoint_trigger_wait(struct EffectObj* self)
{
    if (func_8002B160(self) == 0) {
        if (self->unk2 & 0xF0) {
            if (self->y_pos.i.hi <= g_Player.y_pos.i.hi) {
                engine_obj.checkpoint = self->unk2 & 0xF;
                despawn_object(self);
            }
        } else {
            if (self->x_pos.i.hi <= g_Player.x_pos.i.hi) {
                engine_obj.checkpoint = self->unk2 & 0xF;
                despawn_object(self);
            }
        }
    } else {
        despawn_object(self);
    }
}

void (*tile_scanner_state_funcs[2])(struct EffectObj*) = {
    tile_scanner_init,
    func_800B64BC,
};

void (*tile_scanner_fill_funcs[1])(struct EffectObj*) = { func_800B6660 };

void (*checkpoint_trigger_state_funcs[])(struct EffectObj*) = {
    checkpoint_trigger_init,
    checkpoint_trigger_wait,
};
